#pragma once
#include <iostream>
#include <string>
#include "../../common/all.hpp"
#include "../../common/xliburing.hpp"
#include "../../common/xsock.hpp"


/// @brief ////////////////////////////////////////////////////////////////////////////////////////////
void test_timeout()
{
    xliburing r;
    r.init();

    r.uring_timeout(100, 0, IORING_TIMEOUT_MULTISHOT, nullptr);

    while (1)
    {
        io_uring_cqe *cqe = nullptr;
        int ret = io_uring_wait_cqe(&r.ring_, &cqe);
        if (ret < 0)
        {
            fprintf(stderr, "%s: wait completion %d\n", __FUNCTION__, ret);
        }
        cout<<"timer called"<<endl;
        r.cqe_seen();
    }
}



// 线程函数，用于等待eventfd事件
void *thread_func(void *arg)
{
    int efd = *((int *)arg); // 从参数中获取eventfd

    sleep_ms(3000);
    // 给线程发送一个初始事件
    uint64_t val = 1;
    if (eventfd_write(efd, val) == -1)
    {
        perror("eventfd_write");
        exit(EXIT_FAILURE);
    }

    sleep_ms(3000);
    // 给线程发送一个初始事件
    if (eventfd_write(efd, val) == -1)
    {
        perror("eventfd_write");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
}
void test_liburing_eventfd()
{
    xliburing r;
    r.init();

    int efd;       // eventfd
    pthread_t tid; // 线程ID

    // 创建eventfd
    efd = eventfd(0, 0);
    if (efd == -1)
    {
        perror("eventfd");
        exit(EXIT_FAILURE);
    }

    // 创建线程
    if (pthread_create(&tid, NULL, thread_func, &efd) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    r.uring_event_fd(efd, POLLIN, nullptr, true);

    // peek方式
    // while(1)
    // {
    //     io_uring_cqe  *cqe = r.peek_cqe();
    //     if(nullptr == cqe)
    //     {
    //         sleep_ms(10);
    //         continue;
    //     }

    //     cout<<"cqe get\n";
    //     r.cqe_seen(cqe);
    // }

    // wait方式
    while (1)
    {
        unsigned num_completed = 0;
        unsigned head;

        io_uring_cqe *cqe = nullptr;
        int ret = r.get_cqes(&cqe, 10, 1000);
        cout << "get_cqes ret=" << ret << ",cqe=0x%ju" << cqe << endl;
        if (0 == ret && nullptr != cqe)
        {
            io_uring_for_each_cqe(&r.ring_, head, cqe)
            {
                ++num_completed;
                cout << "get eventd" << endl;
            }
            r.cqe_seen(num_completed);
        }
    }
}

void normal_udp()
{

    xsock s;
    s.udp_create();
    s.xbind("0.0.0.0", 8888);

    while (1)
    {
        char sz[4096] = {0};
        sockaddr addr_in;
        socklen_t len = sizeof(addr_in);
        int ret = s.recv_from(sz, 4096, 0, &addr_in, &len);

        printf("recv len = %d,val=%s\n", ret, sz);

        s.sendto(sz, ret, 0, &addr_in, len);
    }
}

void uring_udp_peek_one()
{
    xliburing r;
    r.init();

    xsock s;
    s.udp_create();
    s.xbind("0.0.0.0", 8888);

    while (1)
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
        bool ret = r.uring_recvmsg(s.sock_, &msg, 0);

        printf("uring_recv over \n");

        auto cqe = r.peek_cqe();
        while (nullptr == cqe)
        {
            sleep_ms(10);
            cqe = r.peek_cqe();
        }
        printf("uring_recvmsg cqe\n");
        r.cqe_seen();

        msg.msg_iov[0].iov_len = cqe->res;

        r.uring_sendmsg(s.sock_, &msg, 0);

        cqe = r.get_cqe();

        printf("uring_sendmsg cqe res = %u\n",cqe->res);
        r.cqe_seen();
    }
}

int kimi()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (sockfd < 0)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8888);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Failed to bind" << std::endl;
        close(sockfd);
        return -1;
    }

    // Setup liburing
    struct io_uring ring;
    if (io_uring_queue_init(128, &ring, 0) < 0)
    {
        std::cerr << "Failed to init ring" << std::endl;
        close(sockfd);
        return -1;
    }

    char buffer[1024];
    struct iovec iov = {
        .iov_base = buffer,
        .iov_len = sizeof(buffer)};
    sockaddr_in saddr;

    struct msghdr msg = {};
    msg.msg_name = &saddr;
    msg.msg_namelen = sizeof(struct sockaddr_in);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    while (true)
    {
        struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
        io_uring_prep_recvmsg(sqe, sockfd, &msg, 0);
        io_uring_submit(&ring);

        // Wait for completion
        struct io_uring_cqe *cqe;
        io_uring_wait_cqe(&ring, &cqe);

        if (cqe->res < 0)
        {
            std::cerr << "Error receiving message" << std::endl;
            break;
        }

        cout << "recv " << (char *)msg.msg_iov[0].iov_base << endl;
        cout << "cqe res " << cqe->res;

        msg.msg_iov[0].iov_len = cqe->res;

        io_uring_cqe_seen(&ring, cqe);
        // Echo the data back
        struct io_uring_sqe *send_sqe = io_uring_get_sqe(&ring);
        io_uring_prep_sendmsg(send_sqe, sockfd, &msg, 0);
        io_uring_submit(&ring);

        // Wait for completion
        io_uring_wait_cqe(&ring, &cqe);

        if (cqe->res < 0)
        {
            std::cerr << "Error sending message" << std::endl;
            break;
        }

        io_uring_cqe_seen(&ring, cqe);
    }

    io_uring_queue_exit(&ring);
    close(sockfd);
    return 0;
}
