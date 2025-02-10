#pragma once
#include "../../common/all.hpp"

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