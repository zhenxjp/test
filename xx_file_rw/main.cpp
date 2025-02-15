
#include <iostream>

#include "iov_rw.hpp"
#include "io_test.hpp"
#include "io_perf.hpp"


void map_test()
{
    unordered_map<string,string> map;
    map.insert(make_pair("a","b"));
}

int main(int argc, char** argv)
{
    map_test();
    // iov_rw();
    io_test();

    // io_perf_test();

    
    return 0;
}


