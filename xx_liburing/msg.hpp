#pragma once
#include <iostream>
#include <string>
#include "../../common/all.hpp"
#include "../../common/xliburing.hpp"
#include "../../common/xsock.hpp"

// msghdr的rb
struct msghdr_bufer:public rb_base
{
    // 初始化
    void init_msg(int cnt,int size)
    {
        size_ = size;
        print_change_ = false;

        msg_ = new msghdr[cnt];
        iovec *iov = new iovec[cnt];
        sockaddr_in *saddr = new sockaddr_in[cnt];


        for(int i = 0 ;i < cnt;++i)
        {
            char *buf = new char[size];
            memset(buf, 0, size);


            iov[i].iov_base = buf;
            iov[i].iov_len = size;

            msg_[i].msg_iov = &iov[i];
            msg_[i].msg_iovlen = 1;

            msg_[i].msg_name = &saddr[i];
            msg_[i].msg_namelen = sizeof(saddr[i]);

            msg_[i].msg_control = nullptr;
            msg_[i].msg_controllen = 0;
            msg_[i].msg_flags = 0;
        }
        rb_base::init(cnt);
        
        efd_ = eventfd(0, 0);

    }

    // 写入完成
    void msg_write_done(uint64_t cnt)
    {
        rb_base::writer_done(cnt);
        // 通知读者
        eventfd_write(efd_, cnt);
    }

    // 获取写buffer
    msghdr* writer_get_msg()
    {
        return get_msg(writer_get_idx());
    }

        // 获取写buffer
    msghdr* writer_get_the_msg()
    {
        return get_msg(writer_get_idx());
    }

    // 获取读buffer
    msghdr* reader_get_msg()
    {
        return get_msg(reader_get_idx());
    }

public:
    msghdr* get_msg(uint64_t idx)
    {
        if(-1 == idx){
            return nullptr;
        }
        idx = idx % blk_cnt_;// TODO
        return msg_ + idx ;
    }
    msghdr *msg_ = nullptr;

    int efd_ = -1;
    int size_ = 0;
};

