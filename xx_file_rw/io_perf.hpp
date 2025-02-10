#pragma once
#include "../../common/all.hpp"
#include "io_comm.hpp"
namespace io_perf
{



static void rb_writer(io_tester *gt_ptr )
{
    io_tester &GT = *gt_ptr;
    int idx = 0;
    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->writer_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);
        for(int i = 0; i < cnt; i++)
        {
            write_iov_perf(iov+i,idx);
            ++idx;
        }
        GT.rb->writer_done(cnt);
        GT.rb_w_cnt += cnt;
        if (GT.rb_w_cnt >= GT.max)
            break;
    }
}

static int io_writer(io_tester *gt_ptr )
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

static void io_reader(io_tester *gt_ptr )
{
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


static void rb_reader(io_tester *gt_ptr)
{
    io_tester &GT = *gt_ptr;
    auto rb = GT.rb2;
    int idx = 0;
    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = rb->reader_get_blk(cnt);
        if(0 == cnt)
            continue;
        cnt = std::min(cnt,(uint64_t)1024);
        for(int i = 0; i < cnt; i++)
        {
            // printf("rb r idx:%d,len:%ju \n",idx,iov[i].iov_len);
            read_iov_perf(iov+i,idx);
            ++idx;

        }
        rb->reader_done(cnt);
        GT.rb_r_cnt += cnt;
        if (GT.rb_r_cnt >= GT.max)
            break;
    }
}


void io_test_data_ok_w_r_p(io_tester &GT,io_tester &last)
{
    sleep_ms(100);
    printf("rb_w_cnt = %ju ",GT.rb_w_cnt-last.rb_w_cnt);
    printf("io_w_cnt = %ju ",GT.io_w_cnt-last.io_w_cnt);
    printf("io_r_cnt = %ju ",GT.io_r_cnt-last.io_r_cnt);
    printf("rb_r_cnt = %ju ",GT.rb_r_cnt-last.rb_r_cnt);

    printf("all = %ju ",GT.io_r_cnt);    
    printf("\n");
    GT.rb->print_info("rb1 ");
    GT.rb2->print_info("rb2 ");
    last = GT;
    
}
static void test()
{
    io_tester GT;
    GT.rb = new rb_iov;
    GT.rb->init(RB_CNT,1024,true);
    GT.rb2 = new rb_iov;
    GT.rb2->init(RB_CNT,1024,true);

    io_meta m;
    m.blk_cnt_max_ = 1024*1024;
    m.blk_size_ = 1024;
    m.io_type_ = 0;

    io_context ctx;
    ctx.meta_ = m;
    ctx.path_ = "./io_save/";
    ctx.prefix_ = "io_pre";
    ctx.rw_type_ = io_rw_type::rw_write;
    ctx.init_type_ = io_init_type::init_new;

    GT.ctx = ctx;

    std::thread t1(rb_writer,&GT);
    std::thread t2(io_writer,&GT);
    //std::thread t3(io_reader,&GT);
    //std::thread t4(rb_reader,&GT);

    io_tester last;
    while(GT.rb_r_cnt < GT.max)
    {
        io_test_data_ok_w_r_p(GT,last);
    }
    io_test_data_ok_w_r_p(GT,last);


    t1.join();
    t2.join();
    //t3.join();
    //t4.join();
}












}