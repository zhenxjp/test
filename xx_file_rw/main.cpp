
#include <iostream>

#include "iov_rw.hpp"
#include "io_test.hpp"
#include "io_perf.hpp"
#include "rt_mgr.hpp"


int main(int argc, char** argv)
{
    // map_test();
    // iov_rw();
    // io_test();

    // io_perf_test();

    argc = 3;
    argv[1] = "-c";
    argv[2] = "./conf/conf.xml";
    
    rt_mgr rt;
    rt.run(argc,argv);
    return 0;
}


