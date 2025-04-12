#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>
#include <link.h>


#include "FtdcTraderApi.h"
#include "xhook.hpp"
#include "xanti_debug.hpp"

using namespace std;


void *so_addr = 0;
// 回调函数，用于获取共享库的加载地址
static int callback(struct dl_phdr_info *info, size_t size, void *data) {
    const char *so_name = (const char *)data;
    if (strstr(info->dlpi_name, so_name) != NULL) {
        printf("共享库 %s 的加载地址: 0x%lx\n", info->dlpi_name, (unsigned long)info->dlpi_addr);
        so_addr = (char*)info->dlpi_addr;
    }
    return 0;
}

// 函数用于打印指定共享库的加载信息
void* get_so_location(const char *so_name) {
    dl_iterate_phdr(callback, (void *)so_name);
    return so_addr;
}

int my_sleep(useconds_t usec)
{
    printf("usleep %u\n",usec);
    return 0;
}


class CSimpleHandler : public CShfeFtdcTraderSpi
{
public:
    bool connected = false;
    CShfeFtdcTraderApi *m_pUserApi;
public:
    void hack_login_1()
    {
        *(int *)((char *)m_pUserApi + 0x29F0) = 0;
    }

    // hook api
    // 0x00007ffff7a9bd22 <+1858>:  call   0x7ffff7a4c8f0 <usleep@plt>
    void hack_login_2()
    {
        long page_size = sysconf(_SC_PAGESIZE);
        char *addr = (char*)get_so_location("libtraderapi.so") + 0x9BD22;
        void *addr_paged = (void*)((uint64_t)addr / page_size * page_size);
        
        printf("hack_login_2 %p %p\n",addr,addr_paged);
        
        if (mprotect(addr_paged, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1)
        {
            printf("mprotect error %u\n",errno);
            return;
        }
        for (int i = 0; i < 5; i++)
        {
            addr[i] = 0x90;
        }
    }

    
    void hack_login_3()
    {
        long page_size = sysconf(_SC_PAGESIZE);
        void *addr = (void*)&usleep;
        void *addr_paged = (void*)((uint64_t)addr / page_size * page_size);
        printf("hack_login_2 %p %p\n",addr,addr_paged);
        
        if (mprotect(addr_paged, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1)
        {
            printf("mprotect error %u\n",errno);
            return;
        }

        xx_setjmp(addr,(void*)&my_sleep);
        usleep(1000);
    }

    CSimpleHandler(CShfeFtdcTraderApi *pUserApi) : m_pUserApi(pUserApi) {}

    virtual void OnFrontConnected() override
    {
        printf("threadid:%u,FrontConnected\n", std::this_thread::get_id());
        connected = true;
    }

    
};
long long get_ms()
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

int login_test();

int order_test();

int main()
{
    login_test();
    // order_test();
    return 0;
}

int login_test()
{
    // 创建CShfeFtdcTraderApi实例
    CShfeFtdcTraderApi *pUserApi = CShfeFtdcTraderApi::CreateFtdcTraderApi();
    // 创建事件处理实例
    CSimpleHandler sh(pUserApi);
    // 注册回调实例
    pUserApi->RegisterSpi(&sh);

    // 设置心跳超时时间
    pUserApi->SetHeartbeatTimeout(6000);

    // 设置交易前置NameServer地址
    pUserApi->RegisterFront("tcp://127.0.0.1:8888"); // 示例地址，可根据实际情况修改

    // 初始化API
    pUserApi->Init();

    // 主线程等待连接成功
    while (!sh.connected)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // 构建登录请求结构体
    CShfeFtdcReqUserLoginField reqUserLogin;
    printf("Login size = %ju\n",sizeof(reqUserLogin));

    // sh.hack_login_2();
    sh.hack_login_3();

    // rbx         0x55555558E290 =0x55555558bd10+0x2580
    // this		   0x55555558b8a0
    for (size_t i = 0; i < 5; i++)
    {
        // sh.hack_login_1();
        auto start = get_ms();

        auto ret = sh.m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
        printf("ReqUserLogin ret:%d,cost:%lld,\n", ret, get_ms() - start);
    }
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    

    exit(0);
    return 0;
}



int order_test()
{
    is_being_debugged_test();
    // 创建CShfeFtdcTraderApi实例
    CShfeFtdcTraderApi *pUserApi = CShfeFtdcTraderApi::CreateFtdcTraderApi();
    // 创建事件处理实例
    CSimpleHandler sh(pUserApi);
    // 注册回调实例
    pUserApi->RegisterSpi(&sh);

    // 设置心跳超时时间
    pUserApi->SetHeartbeatTimeout(6000);

    // 设置交易前置NameServer地址
    pUserApi->RegisterFront("tcp://127.0.0.1:8888"); // 示例地址，可根据实际情况修改

    // 初始化API
    pUserApi->Init();

    // 主线程等待连接成功
    while (!sh.connected)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // 构建报单请求结构体
    CShfeFtdcInputOrderField ord;
    
    memset(&ord, 0, sizeof(ord));
    strcpy(ord.InstrumentID, "InstrumentID");
    strcpy(ord.IPAddress, "IPAddress");
    strcpy(ord.MacAddress, "MacAddress");

    printf("order size = %ju\n",sizeof(ord));
    for(int i = 0; i < 3; i++)
    {
        // 主线程发送报单请求
        auto start = get_ms();
        int ret = pUserApi->ReqOrderInsert(&ord, 1);
        printf("order insert ret:%d,cost:%lld,\n", ret, get_ms() - start);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    

    exit(0);
    return 0;
}