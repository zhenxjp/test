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
        e_cqe_recv_done = 100,
        e_cqe_send_ntf = 2,
        e_cqe_send_done = 3,
        e_cqe_end
    };
    bool init()
    {
        r_.init();

        s_.udp_create();
        s_.xbind("0.0.0.0", 8888);

        recv_.init_msg(1024,1024);
        send_.init_msg(1024,1024);

        post_recv();

        uint64_t cqe_type = e_cqe_send_ntf;
        r_.uring_event_fd(send_.efd_,EPOLLIN,(void*)cqe_type,true);

        return true;
    }

    // 开始接收
    bool post_recv()
    {
        msghdr* msg = recv_.writer_get_msg();
        CHECK_RETV(msg != nullptr,false);

        uint64_t cqe_type = e_cqe_recv_done;
        return r_.uring_recvmsg(s_.sock_, msg, 0,(void*)cqe_type,false);
    }


    void check_once(int timeout_ms = -1)
    {
        // read data
        io_uring_cqe* cqe = r_.get_cqe(100);
        if(nullptr == cqe)
            return;
        
        uint64_t type = io_uring_cqe_get_data64(cqe);
        cout<<"net uring cqe type = "<<type<<endl;
        printf("cqe %p,res = %d\n",cqe,cqe->res);
        r_.cqe_seen(1);

        if(e_cqe_recv_done == type)  
        {
            msghdr* msg = recv_.writer_get_msg();
            msg->msg_iov[0].iov_len = cqe->res;
            recv_.msg_write_done(1);
            post_recv();
        }else if(e_cqe_send_ntf == type)
        {
            msghdr *send_msg = send_.reader_get_msg();
            if(nullptr == send_msg)
            {
                cout<<"send for write nullptr"<<endl;
                return;
            }
            uint64_t cqe_type = e_cqe_send_done;
            r_.uring_sendmsg(s_.sock_,send_msg,0,(void*)cqe_type);
        }else if(e_cqe_send_done == type)
        {
            // 发完才能删
            send_.reader_done(1);
        }

    }
public:
    uint64_t cqe_user_data_ = 0;

    xliburing r_;
    xsock s_;
    msghdr_bufer recv_;
    msghdr_bufer send_;
};






void* net_thread(void *arg)
{
    udp_server *s = (udp_server*)arg;
    s->init();


    while (true)
    {
        s->check_once(100);
    }
    return nullptr;
}
void test_aync()
{
    // 启动网络线程
    udp_server s;
    pthread_t tid = 0; // 线程ID
    pthread_create(&tid, NULL, net_thread, &s);

    sleep_ms(1000);


    xliburing r;
    r.init();
    r.uring_event_fd(s.recv_.efd_,POLLIN,nullptr,true);

    while(1)
    {
        // read data
        io_uring_cqe* cqe = r.get_cqe(100);
        if(nullptr == cqe)
            continue;
        msghdr *msg = s.recv_.reader_get_msg();
        if(nullptr == msg)
        {
            cout<<"recv for read nullptr"<<endl;
            continue;
        }
        iovec &iov = msg->msg_iov[0];
        cout<<"recv: "<<string((char*)iov.iov_base)<<",len="<<iov.iov_len<<endl;
        // =========================================================================================
        // send data
        msghdr *send_msg = s.send_.writer_get_msg();
        if(nullptr == send_msg)
        {
            cout<<"send for write nullptr"<<endl;
            continue;
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

        // =========================================================================================
        // write over
        s.send_.msg_write_done(1);

        // read over
        s.recv_.reader_done(1);

        // cqe seen
        r.cqe_seen(1);
    }
}
