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
        printf("error iov_len=%lu,ok=%lu\n",iov->iov_len,get_cnt(val)*sizeof(uint64_t));
        exit(0);
    }
    uint64_t *p = (uint64_t *)iov->iov_base;
    for (int j = 0; j < get_cnt(val); j++)
    {
        if(p[j] != val)
        {
            printf("read_iov error val = %ju\n",val);
            exit(0);
        }
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
        // printf("written = %u ",written);
        // printf("wret = %d ",wret);
        // printf("cnt = %ju \n",cnt);

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
        // printf("readed = %u ",readed);
        // printf("rret = %d ",rret);
        // printf("cnt = %ju \n",cnt);
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
        printf("io_test_data_ok10000 ok %jd\n",i);
    }
    printf("io_test_data_ok10000 ok\n");
}



struct io_tester2
{
    uint64_t rb_w_cnt = 0;
    uint64_t rb_r_cnt = 0;

    uint64_t io_w_cnt = 0;
    uint64_t io_r_cnt = 0;


    rb_iov *rb = nullptr;
    rb_iov *rb2 = nullptr;

    uint64_t max = 100*1000;

    io_context ctx;
};

static void rb_writer(io_tester2 *gt_ptr )
{
    io_tester2 &GT = *gt_ptr;
    int idx = 0;
    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->writer_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);
        for(int i = 0; i < cnt; i++)
        {
            write_iov2(iov+i,idx);
            ++idx;
        }
        GT.rb->writer_done(cnt);
        GT.rb_w_cnt += cnt;
        if (GT.rb_w_cnt >= GT.max)
            break;
    }
}

static int io_writer(io_tester2 *gt_ptr )
{
    io_tester2 &GT = *gt_ptr;

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

static void io_reader(io_tester2 *gt_ptr )
{
    io_tester2 &GT = *gt_ptr;
    GT.ctx.rw_type_ = io_rw_type::rw_read;

    io ior;
    auto ret = ior.init(GT.ctx);

    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb2->writer_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);

        uint32_t readed = 0;
        auto io_ret = ior.read_data(iov,cnt,0,readed);
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


static void rb_reader(io_tester2 *gt_ptr)
{
    io_tester2 &GT = *gt_ptr;
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
            printf("rb r idx:%d,len:%ju \n",idx,iov[i].iov_len);
            read_iov2(iov+i,idx);
            ++idx;

        }
        rb->reader_done(cnt);
        GT.rb_r_cnt += cnt;
        if (GT.rb_r_cnt >= GT.max)
            break;
    }
}


void io_test_data_ok_w_r_p(io_tester2 &GT,io_tester2 &last)
{
    sleep_ms(1000);
    printf("rb_w_cnt = %ju ",GT.rb_w_cnt-last.rb_w_cnt);
    printf("io_w_cnt = %ju ",GT.io_w_cnt-last.io_w_cnt);
    printf("io_r_cnt = %ju ",GT.io_r_cnt-last.io_r_cnt);
    printf("rb_r_cnt = %ju ",GT.rb_r_cnt-last.rb_r_cnt);

    printf("all = %ju ",GT.io_r_cnt);
    printf("\n");
    last = GT;
    
}
static void io_test_data_ok_w_r()
{
    io_tester2 GT;
    GT.rb = new rb_iov;
    GT.rb->init(GT.max,1024,true);
    GT.rb2 = new rb_iov;
    GT.rb2->init(GT.max,1024,true);

    io_meta m;
    m.blk_cnt_max_ = 1024*100;
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
    std::thread t3(io_reader,&GT);
    std::thread t4(rb_reader,&GT);

    io_tester2 last;
    while(GT.rb_r_cnt < GT.max)
    {
        io_test_data_ok_w_r_p(GT,last);
    }
    io_test_data_ok_w_r_p(GT,last);


    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();
}



static void io_test()
{
    //io_test2();
    //io_test_data_ok();
    //io_test_data_ok10000();
    io_test_data_ok_w_r();
}