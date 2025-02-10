#pragma once
#include "../../common/all.hpp"

#define RB_CNT 1024*1024
#define IO_MAX 1024*1024*10

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
    auto xxcnt = get_cnt(val);
    if(iov->iov_len != xxcnt*sizeof(uint64_t))
    {
        printf("error iov_len=%lu,ok=%lu\n",iov->iov_len,xxcnt*sizeof(uint64_t));
        exit(0);
    }
    uint64_t *p = (uint64_t *)iov->iov_base;
    
    for (int j = 0; j < xxcnt; j++)
    {
        if(p[j] != val)
        {
            printf("read_iov error val = %ju\n",val);
            exit(0);
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