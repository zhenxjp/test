#pragma once
#include <iostream>
#include <string>
#include "../../common/all.hpp"
#include "../../common/xliburing.hpp"
#include "../../common/xsock.hpp"
#include "msg.hpp"

class udp_server
{
public:
    enum cqe_type
    {
        e_cqe_recv_done = 1, // 收数据完成
        e_cqe_send_ntf = 2,  // 有数据需要发送
        e_cqe_send_done = 3, // 发数据完成
        e_cqe_timer1 = 4,    // 定时1秒的timer
        e_cqe_end
    };
    bool init()
    {
        r_.init();

        // 监听8888
        s_.udp_create();
        s_.xbind("0.0.0.0", 8888);

        // 收发数据的rb，1024*1024
        recv_.init_msg(1024, 1024);
        send_.init_msg(1024, 1024);

        // 开始异步接收
        post_recv();

        // 初始化event fd（可发送的数据）
        uint64_t cqe_type = e_cqe_send_ntf;
        r_.uring_event_fd(send_.efd_, EPOLLIN, (void *)cqe_type, true);

        // 初始化定时器
        cqe_type = e_cqe_timer1;
        r_.uring_timeout(1000, 0, IORING_TIMEOUT_MULTISHOT, (void *)cqe_type);

        return true;
    }

    // 异步接收
    bool post_recv()
    {
        msghdr *msg = recv_.writer_get_msg();
        CHECK_RETV(msg != nullptr, false);
        msg->msg_iov[0].iov_len = recv_.size_;

        uint64_t cqe_type = e_cqe_recv_done;
        bool ret = r_.uring_recvmsg(s_.sock_, msg, 0, (void *)cqe_type, false);
        CHECK_RETV(ret, false);
        // cout<<"post_recv ok"<<endl;;
        return true;
    }

    // 网络线程，处理事件
    void check_once(int timeout_ms = -1)
    {
        // 获取事件
        io_uring_cqe *cqe = r_.get_cqe(100);
        if (nullptr == cqe)
            return;

        // 获取类型，通过设置的user data来设置
        uint64_t type = io_uring_cqe_get_data64(cqe);
        // cout<<"net uring cqe type = "<<type<<endl;
        // printf("cqe %p,res = %d\n",cqe,cqe->res);
        
        // 接收完毕
        if (e_cqe_recv_done == type)
        {
            msghdr *msg = recv_.writer_get_msg();
            msg->msg_iov[0].iov_len = cqe->res;
            recv_.msg_write_done(1);
            post_recv();
        }
        // 待发送数据准备好
        else if (e_cqe_send_ntf == type)
        {
            while (send_rb_ridx_ < send_.writer_get_idx())
            {
                msghdr *send_msg = send_.get_msg(send_rb_ridx_);
                // log
                if (0)
                {
                    send_.print_info("send before send");
                    iovec &iov = send_msg->msg_iov[0];
                    string addr = get_addr_str((sockaddr_in *)send_msg->msg_name);
                    printf("send %s,len:%ju,to %s \n",
                           (char *)iov.iov_base, iov.iov_len, addr.c_str());
                    send_.print_info();
                }

                // send
                ++send_rb_ridx_;
                uint64_t cqe_type = e_cqe_send_done;
                bool send_ret = r_.uring_sendmsg(s_.sock_, send_msg, 0, (void *)cqe_type);
                if(!send_ret)
                {
                    cout<<"send error"<<endl;
                    exit(0);
                }
                // send_.print_info("send after send");
            }
        }
        // 发送完毕，可以移动rb
        else if (e_cqe_send_done == type)
        {
            // 发完才能删
            send_.reader_done(1);
        }
        // 定时事件
        else if (e_cqe_timer1 == type)
        {
            if (1)
            {
                recv_.print_info("recv");
                send_.print_info("send");
                r_.print_ring_info("net ring");
            }
        }

        r_.cqe_seen(1);
    }

public:
    uint64_t send_rb_ridx_ = 0; // 发到哪了
    xliburing r_;
    xsock s_;
    msghdr_bufer recv_; // 接收rb
    msghdr_bufer send_; // 发送rb
};

// 网络线程
void *net_thread(void *arg)
{
    udp_server *s = (udp_server *)arg;
    s->init();

    while (true)
    {
        s->check_once(100);
    }
    return nullptr;
}

// 业务线程：数据处理函数
void do_recv(udp_server &s,xliburing &r)
{
    // 数据处理干净
    while (1)
    {
        msghdr *msg = s.recv_.reader_get_msg();
        if (nullptr == msg)
        {
            break;
        }
        iovec &iov = msg->msg_iov[0];
        // =========================================================================================
        // 发数据rb获取数据
        msghdr *send_msg = s.send_.writer_get_msg();
        if (nullptr == send_msg)
        {
            cout << "send for write nullptr" << endl;
            exit(0);
        }

        // copy data
        memcpy(send_msg->msg_iov[0].iov_base, iov.iov_base, iov.iov_len);
        send_msg->msg_iov[0].iov_len = iov.iov_len;
        send_msg->msg_iovlen = 1;

        memcpy(send_msg->msg_name, msg->msg_name, msg->msg_namelen);
        send_msg->msg_namelen = msg->msg_namelen;

        send_msg->msg_controllen = 0;
        send_msg->msg_control = nullptr;

        send_msg->msg_flags = 0;

        string addr = get_addr_str((sockaddr_in *)msg->msg_name);
        printf("recv %s,len:%ju,from %s \n",
               (char *)iov.iov_base, iov.iov_len, addr.c_str());

        // =========================================================================================
        // write over
        s.send_.msg_write_done(1);

        // read over
        s.recv_.reader_done(1);

        // cqe seen
        r.cqe_seen(1);
    }
}
// 业务线程
void test_aync()
{
    // 启动网络线程
    udp_server s;
    pthread_t tid = 0; // 线程ID
    pthread_create(&tid, NULL, net_thread, &s);

    sleep_ms(1000);

    // 创建uring
    xliburing r;
    r.init();

    // event fd：网络线程通知业务线程：收到数据
    r.uring_event_fd(s.recv_.efd_, POLLIN, nullptr, true);

    while (1)
    {
        // 读数据
        io_uring_cqe *cqe = r.get_cqe(100);
        if (nullptr == cqe)
            continue;
        // 处理
        do_recv(s,r);
    }
}
