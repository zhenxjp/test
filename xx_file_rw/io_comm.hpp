#pragma once
#include "xio.hpp"
#include "xrb.hpp"
#include "xtime.hpp"

#define RB_CNT 1024*1024
#define IO_MAX 1024*1024*10
#define IO_ONE 1024*1024
#define RB_SIZE 1024


#define IO_IDX_KEY_DEFAULT "./io_save/io_pre."

struct io_tester
{
    uint64_t rb_w_cnt = 0;
    uint64_t rb_r_cnt = 0;

    uint64_t io_w_cnt = 0;
    uint64_t io_r_cnt = 0;


    rb_iov *rb = nullptr;
    rb_iov *rb2 = nullptr;


    io_context ctx;

    uint64_t max = IO_MAX;
    string path;
};

static inline uint64_t get_cnt(uint64_t idx)
{
    return idx % 10+35;
}

static void write_iov_perf(iovec *iov,uint64_t val)
{
    //printf("writeiov val = %ju\n",val);
    uint64_t *p = (uint64_t *)iov->iov_base;
    auto xxcnt = get_cnt(val);
    for (int j = 0; j < xxcnt; j++)
    {
        p[j] = val;
    }
    iov->iov_len = xxcnt*sizeof(uint64_t);
    
}

static void read_iov_perf(iovec *iov,uint64_t val)
{
    //printf("read_iov val = %ju\n",val);
    auto xxcnt = get_cnt(val);
    if(iov->iov_len != xxcnt*sizeof(uint64_t))
    {
        printf("error iov_len=%lu,ok=%lu\n",iov->iov_len,xxcnt*sizeof(uint64_t));
    }
    uint64_t *p = (uint64_t *)iov->iov_base;
    
    for (int j = 0; j < xxcnt; j++)
    {
        if(p[j] != val)
        {
            printf("read_iov error val = %ju,real=%ju\n",val,p[j]);
            XASSERT(0);
        }
    }
    

}


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


static void io_test_data_ok_w_r_p(io_tester &GT,io_tester &last)
{
    sleep_ms(1000);
    io_tester cur = GT;

    printf("rb_w_cnt = %ju ",cur.rb_w_cnt-last.rb_w_cnt);
    printf("io_w_cnt = %ju ",cur.io_w_cnt-last.io_w_cnt);
    printf("io_r_cnt = %ju ",cur.io_r_cnt-last.io_r_cnt);
    printf("rb_r_cnt = %ju ",cur.rb_r_cnt-last.rb_r_cnt);

    printf("all = %ju ",cur.io_r_cnt);    
    printf("\n");
    GT.rb->print_info("rb1 ");
    GT.rb2->print_info("rb2 ");
    last = cur;
    
}