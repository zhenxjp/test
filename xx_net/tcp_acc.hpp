#include <iostream>
#include "para.hpp"
class xcon : public xevent
{
public:
    virtual ~xcon() {}
    // EPOLLIN,EPOLLOUT
    virtual void handle_evt(uint32_t evt_type)
    {
        // printf("evt_type=%u\n",evt_type);
        while (1)
        {
            char sz[4096] = {0};
            int ret = s_.recv_from(sz, 4096);
            // printf("recv_from ret=%d\n", ret);
            if (ret <= 0)
            {
                on_disconnect();
                break;
            }
        }
    }
    virtual int32_t get_fd()
    {
        return s_.sock_;
    }
    virtual void on_connect()
    {
        sockaddr_in peer = s_.get_peer_addr();
        // printf("on_connect,addr=%s\n", get_addr_str(&peer).c_str());
    }
    virtual void on_disconnect()
    {
        sockaddr_in peer = s_.get_peer_addr();
        // printf("on_disconnect,addr=%s\n", get_addr_str(&peer).c_str());
        ee_->remove(this);
        s_.close();
        delete this;
    }

public:
    xepoll *ee_ = nullptr;
    xsock s_;
};

class xlistern : public xevent
{
public:
    bool listern(const char *ip, port_t port)
    {
        s_.close();
        s_.tcp_create();
        s_.reuse_addr(1);
        s_.reuse_port(1);
        s_.set_nonblock(1);
        s_.xbind(ip, port);
        s_.xlisten();

        ee_->insert(EPOLLIN | EPOLLET, this);
        return true;
    }

    virtual ~xlistern() {}
    // EPOLLIN,EPOLLOUT
    virtual void handle_evt(uint32_t evt_type)
    {
        // printf("evt_type=%u\n",evt_type);
        if (evt_type & EPOLLIN)
        {
            // printf("EPOLLIN\n");
            while (true)
            {
                int fd = s_.xaccept();
                if (-1 == fd)
                {
                    break;
                }
                xcon *con = new xcon;
                con->ee_ = this->ee_;
                con->s_.sock_ = fd;
                con->s_.set_nonblock(1);

                ee_->insert(EPOLLIN | EPOLLET, con);

                con->on_connect();
            }
        }
    }
    virtual int32_t get_fd() { return s_.sock_; }

public:
    xepoll *ee_ = nullptr;
    xsock s_;
};

static void tcp_acc(int argc, char **argv)
{
    xepoll ee;
    ee.init();

    xlistern l;
    l.ee_ = &ee;
    l.listern(ip, port);

    while (true)
    {
        ee.wait();
    }
}

static void tcp_acc_close_now(int argc, char **argv)
{
    xsock s_;

    s_.close();
    s_.tcp_create();
    s_.reuse_addr(1);
    s_.reuse_port(1);
    s_.set_nonblock(1);
    s_.xbind(ip, port);
    s_.xlisten();

    while(1)
    {
        auto new_sock = s_.xaccept();
        close(new_sock);
        printf("new_con\n");
    }
}