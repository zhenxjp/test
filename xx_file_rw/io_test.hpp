#pragma once
#include "../../common/all.hpp"
#include "io_comm.hpp"




static int io_idx_test_w(uint32_t blkcnt)
{

    io_context ctx;
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
        write_iov_perf(iov+i,i);

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

    io_context ctx;
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
        read_iov_perf(cur,i);
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
    for (size_t i = 0; i < 100; i++)
    {
        io_idx_test_w(100);
        io_idx_test_r(100);
        idx_op(IO_IDX_KEY_DEFAULT,"del");
    }
    printf("io_test_data_ok10000 ok\n");
}


// 删除指定文件后面 N 个字节的函数
static int delete_last_n_bytes(const char *filename, size_t n) {
    struct stat file_stat;
    // 获取文件的信息
    if (stat(filename, &file_stat) == -1) {
        perror("Failed to get file information");
        return -1;
    }
    // 检查文件大小是否足够减去 N 个字节
    if ((size_t)file_stat.st_size < n) {
        fprintf(stderr, "File size is less than %zu bytes.\n", n);
        return -1;
    }
    // 计算截断后的文件大小
    off_t new_size = file_stat.st_size - (off_t)n;
    // 截断文件
    if (truncate(filename, new_size) == -1) {
        perror("Failed to truncate file");
        return -1;
    }
    return 0;
}
static int io_test_haf_data()
{
    io_idx_test_w(2000);
    delete_last_n_bytes("./io_save/io_pre.index",3);

    idx_op(IO_IDX_KEY_DEFAULT,"del");

    io_context ctx;
    ctx.rw_type_ = io_rw_type::rw_write;
    ctx.init_type_ = io_init_type::init_exist;

    io iow;
    auto ret = iow.init(ctx);
    XASSERT(ret == 0);
    cout<<iow.idx_->cnt()<<endl;

    uint32_t readed = 0;
    int read_ret = 0;
    char sz[RB_SIZE];
    iovec iov;
    iov.iov_base = sz;
    iov.iov_len = RB_SIZE;

    io_context ctx2;
    ctx2.rw_type_ = io_rw_type::rw_read;

    // read
    io ior;
    ret = ior.init(ctx2);
    XASSERT(ret == 0);
    read_ret = ior.read_data(&iov,1,1999,readed);
    XASSERT(read_ret==0);
    XASSERT(readed==0);

    iovec iovw;
    iovw.iov_base=(void*)"hello";
    iovw.iov_len=5;
    uint32_t written = 0;
    auto wret = iow.write_data(&iovw,1,written);
    XASSERT(written==1);
    XASSERT(wret==0);

    {
        read_ret = ior.read_data(&iov,1,1999,readed);
        XASSERT(read_ret==0);
        XASSERT(readed==1);
        XASSERT(string((char*)iov.iov_base,iov.iov_len) == "hello");
    }

    printf("io_haf_data ok\n");
    return 0;
}


static int io_idx_test_w_xuxie(uint32_t blkcnt)
{

    io_context ctx;
    ctx.rw_type_ = io_rw_type::rw_write;
    ctx.init_type_ = io_init_type::init_exist;

    io iow;
    auto ret = iow.init(ctx);
    CHECK0_RETV(ret,0);


    rb_iov rb;
    rb.init(blkcnt,1024);

    uint64_t cnt = blkcnt;
    iovec *iov = rb.iov_;
    uint64_t already = iow.idx_->cnt();
    for(int i = 0; i < cnt; i++)
    {
        write_iov_perf(iov+i,i + already);

    }
    io_idx_test_r(10);

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

static int io_test_xuxie_data()
{
    io_idx_test_w(10);
    io_idx_test_r(10);
    idx_op(IO_IDX_KEY_DEFAULT,"del");
    io_idx_test_w_xuxie(10);
    io_idx_test_r(10);
    io_idx_test_r(20);

    printf("io_test_xuxie_data ok\n");

    return 0;
}   

static int io_test_xuxie_big()
{
    io_idx_test_w(100000);
    io_idx_test_r(100000);
    idx_op(IO_IDX_KEY_DEFAULT,"del");
    io_idx_test_w_xuxie(100000);
    io_idx_test_r(100000);
    io_idx_test_r(200000);

    printf("io_test_xuxie_data ok\n");

    return 0;
}   

static void io_test()
{
    if(1)
    {
        io_test_data_ok();
        idx_op(IO_IDX_KEY_DEFAULT,"del");
        io_test_data_ok10000();
        idx_op(IO_IDX_KEY_DEFAULT,"del");
        io_test_haf_data();
        idx_op(IO_IDX_KEY_DEFAULT,"del");
        io_test_xuxie_data();
        idx_op(IO_IDX_KEY_DEFAULT,"del");
    }
    
    

    io_test_xuxie_big();
}