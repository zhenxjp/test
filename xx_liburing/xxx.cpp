
#include <iostream>
#include <string>
#include "../../common/all.hpp"
#include "../../common/xliburing.hpp"
#include "../../common/xsock.hpp"
#include "udp_server.hpp"
#include "test.hpp"



int main(int argc, char **argv)
{
    //test_timeout();
    // uring_udp_peek_one();

    //kimi();
    // test_liburing_eventfd();
    test_aync();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
