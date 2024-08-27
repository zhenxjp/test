
#include <iostream>
#include <string>
#include "../../common/all.hpp"
#include "../../common/xliburing.hpp"
#include "../../common/xsock.hpp"
#include "udp_server.hpp"


void test_aync();


int main(int argc, char **argv)
{
    //test_timeout();
    // uring_udp_peek_one();
    // doubao();
    // kimi();
    // test_liburing_eventfd();
    test_aync();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////



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
        cout<<"recv: "<<string((char*)msg->msg_iov[0].iov_base)<<",len="<<msg->msg_iov[0].iov_len<<endl;

        // send data
        msghdr *send_msg = s.send_.writer_get_msg();
        if(nullptr == send_msg)
        {
            cout<<"send for write nullptr"<<endl;
            continue;
        }

        memcpy(send_msg->msg_iov[0].iov_base, msg->msg_iov[0].iov_base, msg->msg_iov[0].iov_len);
        send_msg->msg_iov[0].iov_len = msg->msg_iov[0].iov_len;
        send_msg->msg_iovlen = 1;

        memcpy(send_msg->msg_name, msg->msg_name, msg->msg_namelen);
        send_msg->msg_namelen = msg->msg_namelen;
        
        send_msg->msg_controllen = 0;
        send_msg->msg_control = nullptr;

        send_msg->msg_flags = 0;

        // write over
        s.send_.writer_done(1);

        // read over
        s.recv_.reader_done(1);

        // cqe seen
        r.cqe_seen(1);
    }
}
