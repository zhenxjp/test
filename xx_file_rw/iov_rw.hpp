#pragma once
#include "../../common/all.hpp"
#include "io_comm.hpp"

static io_tester GT;




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
    std::thread t1(rb_writer,&GT);
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
    std::thread t4(rb_reader,&GT);

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
    iov_w();
}