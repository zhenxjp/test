
#include <iostream>

#include "iov_rw.hpp"
#include "io_test.hpp"
#include "io_perf.hpp"
#include "rt_mgr.hpp"

int demo_test(int argc, char** argv)
{
    argc = 3;
    argv[1] = "-c";
    argv[2] = "./conf/conf.xml";
    
    rt_mgr rt;
    rt.start(argc,argv);

    // biz code
    auto rb = rt.get_itc(2);
    auto ee = rt.get_ee("rb_reader");
    rb->set_cb(ee,[&](uint64_t ){
        uint64_t cnt = 0;
        iovec *iov = rb->reader_get_blk(cnt);
        if(0 == cnt)
            return;
        cnt = std::min(cnt,(uint64_t)1024);
        uint64_t ridx = rb->r_idx();
        for(int i = 0; i < cnt; i++)
        {
            LOG_INFO("rb r idx:{},len:{} \n",ridx + i,iov[i].iov_len);
            read_iov_perf(iov+i,ridx + i);

        }
        rb->reader_done(cnt);
    });

    rt.run_all_engine();

    auto rbw = rt.get_itc(1);
    while(true)
    {
        uint64_t cnt = 0;
        iovec *iov = rbw->writer_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);

        uint64_t w_idx = rbw->w_idx();
        for(int i = 0; i < cnt; i++)
        {
            LOG_INFO("rb w idx:{},len:{} \n",w_idx + i,iov[i].iov_len);

            write_iov_perf(iov+i,w_idx + i);
        }
        rbw->writer_done_ntf(cnt);
    }
    return 0;
}
int main(int argc, char** argv)
{
    //iov_rw();
    //io_test();

    //io_perf_test();

    demo_test(argc,argv);
    return 0;
}


