#pragma once
#include "../../common/all.hpp"

struct io_tester
{
    uint64_t rb_w_cnt = 0;
    uint64_t rb_r_cnt = 0;

    uint64_t io_w_cnt = 0;
    uint64_t io_r_cnt = 0;

    std::string path = "";

    rb_iov *rb = nullptr;
    rb_iov *rb2 = nullptr;

    uint64_t max = 10*1000*1000;
};
static io_tester GT;

///////////////////////////////////////////////////////////////////
static void write_iov(iovec *iov,uint64_t val)
{
    uint64_t *p = (uint64_t *)iov->iov_base;
    for (int j = 0; j < 1024/8; j++)
    {
        p[j] = val;
    }
}

static void rb_writer()
{
    int idx = 0;
    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->writer_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);
        for(int i = 0; i < cnt; i++)
        {
            write_iov(iov+i,idx++);

        }
        GT.rb->writer_done(cnt);
        GT.rb_w_cnt += cnt;
        if (GT.rb_w_cnt >= GT.max)
            break;
    }
}
///////////////////////////////////////////////////////////////////

static void read_iov(iovec *iov,uint64_t val)
{
    uint64_t *p = (uint64_t *)iov->iov_base;
    for (int j = 0; j < 1024/8; j++)
    {
        if(p[j] != val)
            printf("read_iov error val = %ju\n",val);
    }
}

static void rb_reader(rb_iov *rb)
{
    int idx = 0;
    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = rb->reader_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);
        for(int i = 0; i < cnt; i++)
        {
            read_iov(iov+i,idx++);
        }
        rb->reader_done(cnt);
        GT.rb_r_cnt += cnt;
        if (GT.rb_r_cnt >= GT.max)
            break;
    }
}





///////////////////////////////////////////////////////////////////
static void io_writer()
{
    int fd = open(GT.path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(-1);
    }

    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->reader_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);

        ssize_t bytes_written = writev(fd, iov, cnt);
        if (bytes_written != cnt * GT.rb->blk_size_) {
            printf("writev err : wrote %ld bytes,except : %ju \n", 
                bytes_written,cnt * GT.rb->blk_size_);
            exit(-1);
        }

        
        GT.rb->reader_done(cnt);
        GT.io_w_cnt += cnt;
        if (GT.io_w_cnt >= GT.max)
            break;
    }
    
}
///////////////////////////////////////////////////////////////////
static void io_writer_mmap()
{
    int fd;
    void *mmap_ptr;
    struct stat file_stat;

    // 打开文件，如果文件不存在则创建
    fd = open(GT.path.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return ;
    }
    uint64_t offset = 0;

    
    size_t len = GT.max * GT.rb->blk_size_;

    // 将文件映射到内存
    mmap_ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mmap_ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return ;
    }
    lseek(fd,len-1,SEEK_SET);
    write(fd, "", 1);

    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->reader_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);

        for(int i = 0; i < cnt ; i++)
        {
            memcpy((char *)mmap_ptr + offset, iov[i].iov_base, iov[i].iov_len);
            offset += iov[i].iov_len;
        }

        
        GT.rb->reader_done(cnt);
        GT.io_w_cnt += cnt;
        if (GT.io_w_cnt >= GT.max)
            break;
    }

    munmap(mmap_ptr, len);

}
///////////////////////////////////////////////////////////////////
static void io_reader()
{
    int fd = open(GT.path.c_str(), O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(-1);
    }


    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb2->writer_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);

        ssize_t bytes_read = readv(fd, iov, cnt);
        auto left = bytes_read % GT.rb->blk_size_;
        cnt = bytes_read / GT.rb->blk_size_;
        if(0 != left)
        {
            printf("readv err : read %ld left,except : %ju \n", 
                bytes_read,left);
        }

        
        GT.rb2->writer_done(cnt);
        GT.io_r_cnt += cnt;
        if (GT.io_r_cnt >= GT.max)
            break;
    }
}

///////////////////////////////////////////////////////////////////

static void iov_w()
{
    GT.rb = new rb_iov;
    GT.rb->init(1024*1024,1024,true);
    GT.rb2 = new rb_iov;
    GT.rb2->init(1024*1024,1024,true);

    GT.path = "./io_test";

    // 启动线程
    std::thread t1(rb_writer);
    std::thread t2(io_writer);


    sleep_ms(1000);
    io_tester last = {0};
    while ( false
        || (GT.rb_w_cnt < GT.max)
        || (GT.io_w_cnt < GT.max)
        )
    {
        io_tester cur = GT;
        // 打印last和cur的变化值
        printf("rb_w_cnt diff: %ju,rb_r_cnt diff: %ju,io_w_cnt diff: %ju,io_r_cnt diff: %ju\n", 
            cur.rb_w_cnt - last.rb_w_cnt,
            cur.rb_r_cnt - last.rb_r_cnt,
            cur.io_w_cnt - last.io_w_cnt,
            cur.io_r_cnt - last.io_r_cnt);

        //  打印cur信息
        printf("rb_w_cnt: %ju,rb_r_cnt: %ju,io_w_cnt: %ju,io_r_cnt: %ju\n", 
            cur.rb_w_cnt,
            cur.rb_r_cnt,
            cur.io_w_cnt,
            cur.io_r_cnt);

        last = cur;

        sleep_ms(1000);
    }

    t1.join();
    t2.join();
}


static void iov_r()
{
    GT.rb = new rb_iov;
    GT.rb->init(1024*1024,1024,true);
    GT.rb2 = new rb_iov;
    GT.rb2->init(1024*1024,1024,true);

    GT.path = "./io_test";

    // 启动线程
    std::thread t3(io_reader);
    std::thread t4(rb_reader,GT.rb2);

    sleep_ms(1000);
    io_tester last = {0};
    while ( false
        || (GT.io_r_cnt < GT.max)
        || (GT.rb_r_cnt < GT.max)
        )
    {
        io_tester cur = GT;
        // 打印last和cur的变化值
        printf("rb_w_cnt diff: %ju,rb_r_cnt diff: %ju,io_w_cnt diff: %ju,io_r_cnt diff: %ju\n", 
            cur.rb_w_cnt - last.rb_w_cnt,
            cur.rb_r_cnt - last.rb_r_cnt,
            cur.io_w_cnt - last.io_w_cnt,
            cur.io_r_cnt - last.io_r_cnt);

        //  打印cur信息
        printf("rb_w_cnt: %ju,rb_r_cnt: %ju,io_w_cnt: %ju,io_r_cnt: %ju\n", 
            cur.rb_w_cnt,
            cur.rb_r_cnt,
            cur.io_w_cnt,
            cur.io_r_cnt);

        last = cur;

        sleep_ms(1000);
    }
    
    t3.join();
    t4.join();

}


static void iov_rw()
{
    iov_r();
}