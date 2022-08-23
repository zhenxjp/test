#include <iostream>
#include "para.hpp"

namespace tcp_con
{
    static bool send = false;
    static uint64_t send_delay_ms = 0;

    static bool close_now = false;

    
    static int cnt = 1;
    struct xpkg
    {
        uint32_t len_ = 36;
        char body_[32];
    };
    static void tcp_con_one()
    {
        xsock s;
        s.tcp_create();
        s.set_nonblock(0);
        s.reuse_addr(1);
        s.reuse_port(1);
        bool ret = s.connect(ip, port);
        printf("connect!ret=%d\n", ret);
        if(!ret){
            printf("connect!err!\n");
            return;
        }        

        if (send)
        {
            sleep_ms(send_delay_ms);
            xpkg p;
            strcpy(p.body_, "msg123");
            int sret = s.sendto(&p, p.len_);
            printf("sendto!ret=%d\n", sret);
        }

        if (close_now)
        {
            s.close_rst();
            printf("close\n");
        }
    }

    static void tcp_con(int argc, char **argv)
    {
        if (xx_arg_have("-send"))
        {
            send = true;
        }

        if (xx_arg_have("-close_now"))
        {
            close_now = true;
        }

        if (xx_arg_have("-cnt"))
        {
            cnt = xx_arg_int("-cnt");
        }

        if (xx_arg_have("-send_delay_ms"))
        {
            send_delay_ms = xx_arg_int("-send_delay_ms");
        }

        cout << "send=" << send << endl;
        cout << "close_now=" << close_now << endl;
        cout << "cnt=" << cnt << endl;
        cout << "send_delay_ms=" << send_delay_ms << endl;

        for (int i = 0; i < cnt; ++i)
        {
            tcp_con_one();
            printf("i=%u\n",i);
        }
    }
}
