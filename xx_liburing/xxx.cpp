
#include <iostream>
#include <string>
#include "../../common/all.hpp"
#include "../../common/xliburing.hpp"
#include "../../common/xsock.hpp"


void normal_udp()
{

    xsock s;
    s.udp_create();
    s.xbind("0.0.0.0",8888);

    while(1)
    {
        char sz[4096] = {0};
        sockaddr addr_in;
        socklen_t len = sizeof(addr_in);
        int ret = s.recv_from(sz, 4096,0,&addr_in,&len);

        printf("recv len = %d,val=%s\n",ret,sz);

        s.sendto(sz,ret,0,&addr_in,len);
    }
}

void uring_udp()
{
    xliburing r;
    r.init();

    xsock s;
    s.udp_create();
    s.xbind("0.0.0.0",8888);

    while(1)
    {

        char sz[4096] = {0};
        sockaddr_in saddr = {};

        struct iovec iov = {
            .iov_base = sz,
            .iov_len = 4096,
        };

        msghdr msg;
        memset(&msg, 0, sizeof(msg));

        msg.msg_name = &saddr;
        msg.msg_namelen = sizeof(saddr);

        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        bool ret = r.uring_recvmsg(s.sock_, msg, nullptr);

        printf("uring_recv over \n");

        auto cqe = r.get_cqe();
        while(nullptr == cqe)
        {
            sleep_ms(10);
            cqe = r.get_cqe();
        }
        printf("uring_recvmsg cqe\n");
        r.cqe_done(cqe);

        msg.msg_iov[0].iov_len = cqe->res;

        r.uring_sendmsg(s.sock_,msg,nullptr);

        cqe = r.get_cqe();
        while(nullptr == cqe)
        {
            sleep_ms(10);
            cqe = r.get_cqe();
        }
        printf("uring_sendmsg cqe\n");
        r.cqe_done(cqe);
    }
}


int kimi() ;
int main(int argc, char** argv)
{
    uring_udp();
    //doubao();
    //kimi();
    return 0;
}


int kimi() {
    int sockfd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8888);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind" << std::endl;
        close(sockfd);
        return -1;
    }

    // Setup liburing
    struct io_uring ring;
    if (io_uring_queue_init(128, &ring, 0) < 0) {
        std::cerr << "Failed to init ring" << std::endl;
        close(sockfd);
        return -1;
    }

    char buffer[1024];
    struct iovec iov = {
        .iov_base = buffer,
        .iov_len = sizeof(buffer)
    };
    sockaddr_in saddr;
    

    struct msghdr msg = {};
    msg.msg_name = &saddr;
    msg.msg_namelen = sizeof(struct sockaddr_in);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;


    while (true) {
        struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
        io_uring_prep_recvmsg(sqe, sockfd, &msg,0);
        io_uring_submit(&ring);

        // Wait for completion
        struct io_uring_cqe *cqe;
        io_uring_wait_cqe(&ring, &cqe);

        if (cqe->res < 0) {
            std::cerr << "Error receiving message" << std::endl;
            break;
        }

        cout<<"recv "<<(char*)msg.msg_iov[0].iov_base<<endl;

        msg.msg_iov[0].iov_len = cqe->res;

        io_uring_cqe_seen(&ring, cqe);
        // Echo the data back
        struct io_uring_sqe *send_sqe = io_uring_get_sqe(&ring);
        io_uring_prep_sendmsg(send_sqe, sockfd, &msg, 0);
        io_uring_submit(&ring);

        // Wait for completion
        io_uring_wait_cqe(&ring, &cqe);

        if (cqe->res < 0) {
            std::cerr << "Error sending message" << std::endl;
            break;
        }

        io_uring_cqe_seen(&ring, cqe);
    }

    io_uring_queue_exit(&ring);
    close(sockfd);
    return 0;
}

