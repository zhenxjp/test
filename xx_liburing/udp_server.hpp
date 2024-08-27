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
        e_cqe_recv = 1,
        e_cqe_send_ntf = 2,
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

        return true;
    }

    // 开始接收
    bool post_recv()
    {
        msghdr* msg = recv_.writer_get_msg();
        CHECK_RETV(msg != nullptr,false);

        uint64_t cqe_type = e_cqe_recv;
        return r_.uring_recvmsg(s_.sock_, msg, 0,(void*)cqe_type,false);
    }


    void check_once(int timeout_ms = -1)
    {

    }
public:
    uint64_t cqe_user_data_ = 0;

    xliburing r_;
    xsock s_;
    msghdr_bufer recv_;
    msghdr_bufer send_;
};