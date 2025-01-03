#pragma once
#include "../../common/all.hpp"

struct io_tester
{
    uint64_t rb_w_cnt = 0;
    uint64_t rb_r_cnt = 0;

    std::string path;

    rb_iov *rb;
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
    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->writer_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);
        for(int i = 0; i < cnt; i++)
        {
            write_iov(iov+i,i);

        }
        GT.rb->writer_done(cnt);
        GT.rb_w_cnt += cnt;
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

static void rb_reader()
{
    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->reader_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);
        for(int i = 0; i < cnt; i++)
        {
            read_iov(iov+i,i);
        }
        GT.rb->reader_done(cnt);
        GT.rb_r_cnt += cnt;
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
    uint64_t file_blk_cnt = 1000000;
    write(fd, &file_blk_cnt, sizeof(uint64_t));
    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->reader_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);
        cnt = std::min(cnt,file_blk_cnt);

        ssize_t bytes_written = writev(fd, iov, cnt);
        if (bytes_written != cnt * GT.rb->blk_size_) {
            printf("writev err : wrote %ld bytes,except : %ju \n", 
                bytes_written,cnt * GT.rb->blk_size_);
            exit(-1);
        }

        
        GT.rb->reader_done(cnt);
        GT.rb_r_cnt += cnt;
        file_blk_cnt -= cnt;
        if(file_blk_cnt == 0)
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

    
    uint64_t file_blk_cnt = 1000000;
    size_t len = file_blk_cnt* GT.rb->blk_size_+ sizeof(uint64_t);

    // 将文件映射到内存
    mmap_ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mmap_ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return ;
    }
    lseek(fd,len-1,SEEK_SET);
    write(fd, "", 1);
    *(uint64_t*)mmap_ptr = file_blk_cnt;
    offset+= sizeof(uint64_t);

    while (true)
    {
        uint64_t cnt = 0;
        iovec *iov = GT.rb->reader_get_blk(cnt);
        cnt = std::min(cnt,(uint64_t)1024);
        cnt = std::min(cnt,file_blk_cnt);

        for(int i = 0; i < cnt ; i++)
        {
            memcpy((char *)mmap_ptr + offset, iov[i].iov_base, iov[i].iov_len);
            offset += iov[i].iov_len;
        }

        
        GT.rb->reader_done(cnt);
        GT.rb_r_cnt += cnt;
        file_blk_cnt -= cnt;
    }

    munmap(mmap_ptr, len);

}
///////////////////////////////////////////////////////////////////
static void io_reader()
{

}

///////////////////////////////////////////////////////////////////
static void iov_rw()
{
    GT.rb = new rb_iov;
    GT.rb->init(1024*1024,1024,true);
    GT.path = "./io_test";

    // 启动线程
    std::thread t1(rb_writer);
    std::thread t2(io_writer_mmap);
    //std::thread t3(io_reader);
    // std::thread t4(rb_reader);

    uint64_t last_w = 0;
    uint64_t last_r = 0;
    while (true)
    {
        
        auto w = GT.rb_w_cnt;
        auto r = GT.rb_r_cnt;
        auto w_diff = w - last_w;
        auto r_diff = r - last_r;

        printf("rb_writer %ju,rb_reader %ju,unread= %ju,wdiff %ju,rdiff %ju\n", 
            w, r,w-r,w_diff,r_diff);

        last_w = w;
        last_r = r;
        sleep_ms(1000);
    }
    

    t1.join();
    t2.join();
    //t3.join();
    //t4.join();

}