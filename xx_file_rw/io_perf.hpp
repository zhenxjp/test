#pragma once
#include "io_comm.hpp"



static int io_writer_io(io_tester *gt_ptr )
{
    io_tester &GT = *gt_ptr;

    GT.ctx.rw_type_ = io_rw_type::rw_write;
    GT.ctx.init_type_ = io_init_type::init_new;

    io iow;
    auto ret = iow.init(GT.ctx);
    CHECK0_RETV(ret,0);

    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->reader_get_blk(cnt);
            
        cnt = std::min(cnt,(uint64_t)1024);

        uint32_t written = 0;
        auto io_ret = iow.write_data(iov,cnt,written);
        if (io_ret != 0)
        {
            printf("io_ret = %d\n",io_ret);
            exit(0);
        }

        
        GT.rb->reader_done(written);
        GT.io_w_cnt += written;
        if (GT.io_w_cnt >= GT.max)
            break;
    }

    return 0;
}

static void io_reader_io(io_tester *gt_ptr )
{
    sleep_ms(3000);
    io_tester &GT = *gt_ptr;
    GT.ctx.rw_type_ = io_rw_type::rw_read;

    io ior;
    auto ret = ior.init(GT.ctx);

    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb2->writer_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);

        uint32_t readed = 0;
        auto io_ret = ior.read_data(iov,cnt,GT.io_r_cnt,readed);
        if (io_ret != 0)
        {
            printf("io_ret = %d\n",io_ret);
            exit(0);
        }
        
        GT.rb2->writer_done(readed);
        GT.io_r_cnt += readed;
        if (GT.io_r_cnt >= GT.max)
            break;
    }
}


static void io_perf_test()
{
    io_tester GT;
    GT.rb = new rb_iov;
    GT.rb->init(RB_CNT,RB_SIZE,true);
    GT.rb2 = new rb_iov;
    GT.rb2->init(RB_CNT,RB_SIZE,true);

    io_meta m;
    m.blk_cnt_max_ = IO_ONE;
    m.blk_size_ = RB_SIZE;
    m.io_type_ = 0;

    io_context ctx;
    ctx.meta_ = m;

    ctx.rw_type_ = io_rw_type::rw_write;
    ctx.init_type_ = io_init_type::init_new;

    GT.ctx = ctx;

    std::thread t1(rb_writer,&GT);
    std::thread t2(io_writer_io,&GT);
    std::thread t3(io_reader_io,&GT);
    std::thread t4(rb_reader,&GT);

    io_tester last;
    while(GT.rb_r_cnt < GT.max)
    {
        io_test_data_ok_w_r_p(GT,last);
    }
    io_test_data_ok_w_r_p(GT,last);


    t1.join();
    t2.join();
    t3.join();
    t4.join();
}










