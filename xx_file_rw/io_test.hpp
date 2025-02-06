#pragma once
#include "../../common/all.hpp"



// static void io_test2()
// {
//     io_context ctx;
    
//     io i;
//     i.init(ctx);

//     for (size_t idx = 0; idx < 20000; idx++)
//     {
//         i.idx_->add(idx);
//     }

//     for (size_t idx = 0; idx < 20000; idx++)
//     {
//         uint32_t len = i.idx_->get_len(idx);
//         if (len != idx)
//         {
//             cout<<"idx = "<<idx<<" len = "<<len<<endl;
//             exit(0);
//         }
        
//     }

//     i.idx_->release();

//     ctx.init_type_ = io_init_type::init_exist;
//     io i2;
//     i2.init(ctx);
//     for (size_t idx = 0; idx < 20000; idx++)
//     {
//         uint32_t len = i2.idx_->get_len(idx);
//         if (len != idx)
//         {
//             cout<<"idx = "<<idx<<" len = "<<len<<endl;
//             exit(0);
//         }
        
//     }

// }


static uint64_t get_cnt(uint64_t idx)
{
    return idx % 50+10;
}

static void write_iov2(iovec *iov,uint64_t val)
{
    uint64_t *p = (uint64_t *)iov->iov_base;
    for (int j = 0; j < get_cnt(val); j++)
    {
        p[j] = val;
    }
    iov->iov_len = get_cnt(val)*sizeof(uint64_t);
}

static void read_iov2(iovec *iov,uint64_t val)
{
    if(iov->iov_len != get_cnt(val)*sizeof(uint64_t))
    {
        printf("iov_len=%lu,ok=%lu\n",iov->iov_len,get_cnt(val)*sizeof(uint64_t));
    }
    uint64_t *p = (uint64_t *)iov->iov_base;
    for (int j = 0; j < get_cnt(val); j++)
    {
        if(p[j] != val)
            printf("read_iov error val = %ju\n",val);
    }
}



static int io_idx_test_w(uint32_t blkcnt)
{
    io_meta m;
    m.blk_cnt_max_ = 256;
    m.blk_size_ = 1024;
    m.io_type_ = 0;

    io_context ctx;
    ctx.meta_ = m;
    ctx.path_ = "./io_save/";
    ctx.prefix_ = "io_pre";
    ctx.rw_type_ = io_rw_type::rw_write;
    ctx.init_type_ = io_init_type::init_new;

    io iow;
    auto ret = iow.init(ctx);
    CHECK0_RETV(ret,0);


    rb_iov rb;
    rb.init(blkcnt,1024);

    uint64_t cnt = blkcnt;
    iovec *iov = rb.iov_;
    for(int i = 0; i < cnt; i++)
    {
        write_iov2(iov+i,i);

    }

    uint64_t start = 0;
    while(cnt > 0)
    {
        uint32_t written = 0;
        int wret = iow.write_data(iov+start,cnt,written);
        printf("written = %u ",written);
        printf("wret = %d ",wret);
        printf("cnt = %ju \n",cnt);

        if (wret == 0)
        {
            start += written;
            cnt -= written;
        }
        else
        {
            printf("wret = %d\n",wret);
            exit(0);
        }
    }
    return 0;
}





static int io_idx_test_r(uint32_t blkcnt)
{
    io_meta m;
    m.blk_cnt_max_ = 256;
    m.blk_size_ = 1024;
    m.io_type_ = 0;

    io_context ctx;
    ctx.meta_ = m;
    ctx.path_ = "./io_save/";
    ctx.prefix_ = "io_pre";
    ctx.rw_type_ = io_rw_type::rw_read;

    // read
    io ior;
    auto ret = ior.init(ctx);
    
    rb_iov rb;
    rb.init(blkcnt,1024);

    uint64_t cnt = blkcnt;
    iovec *iov = rb.iov_;


    uint64_t start = 0;

    while(cnt > 0)
    {
        uint32_t readed = 0;
        int rret = ior.read_data(iov+start,cnt,start,readed);
        printf("readed = %u ",readed);
        printf("rret = %d ",rret);
        printf("cnt = %ju \n",cnt);
        if (rret == 0)
        {
            start += readed;
            cnt -= readed;
        }
        else
        {
            printf("rret = %d\n",rret);
            exit(0);
        }
    }

    for(int i = 0; i < blkcnt; i++)
    {
        iovec *cur = iov+i;
        read_iov2(cur,i);
    }
    rb.release();

    

    return 0;
}
static int io_test_data_ok()
{
    io_idx_test_w(1024*1024);
    io_idx_test_r(1024*1024);
    printf("io_test_data_ok ok\n");
    return 0;
}



static void io_test_data_ok10000()
{
    for (size_t i = 0; i < 10000; i++)
    {
        io_idx_test_w(100);
        io_idx_test_r(100);
        printf("io_test_data_ok10000 ok %d\n",i);
    }
    printf("io_test_data_ok10000 ok\n");
}
static void io_test()
{
    //io_test2();
    io_test_data_ok();
    io_test_data_ok10000();

}