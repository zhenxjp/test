#pragma once
#include "../../common/all.hpp"



static void io_test2()
{
    io_context ctx;
    
    io i;
    i.init(ctx);

    for (size_t idx = 0; idx < 2000; idx++)
    {
        i.idx_.add(idx);
    }

    for (size_t idx = 0; idx < 2000; idx++)
    {
        uint32_t len = i.idx_.get_len(idx);
        if (len != idx)
        {
            cout<<"idx = "<<idx<<" len = "<<len<<endl;
        }
        
    }

}

static void io_test()
{
    io_test2();



}