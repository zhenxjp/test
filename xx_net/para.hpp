#pragma once
#include <iostream>
#include <string>
#include "../../common/all.hpp"


static string type;
static const char* ip = "127.0.0.1";
static port_t port = 8888;

static void init_para(int argc, char** argv)
{
    if(xx_arg_have("-type"))
    {
        type = xx_arg_str("-type");
    }
    cout<<"type="<<type<<endl;

    if(xx_arg_have("-ip"))
    {
        ip = xx_arg_str("-ip");
    }
    cout<<"ip="<<ip<<endl;

    if(xx_arg_have("-port"))
    {
        port = xx_arg_int("-port");
    }
    cout<<"port="<<port<<endl;
}

static string get_action(int idx,int argc, char** argv)
{
    string key = "action" + std::to_string(idx);
    if(!xx_arg_have(key.c_str()))
    {
        return "";
    }
    return xx_arg_str(key.c_str());
}