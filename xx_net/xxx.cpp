
#include <iostream>

#include "tcp_acc.hpp"
#include "tcp_con.hpp"
#include "para.hpp"



int main(int argc, char** argv)
{
    init_para(argc,argv);

    
    if("tcp_acc" == type){
        tcp_acc(argc,argv);
    }

    if("tcp_con" == type){
        tcp_con::tcp_con(argc,argv);
    }
    if("tcp_acc_close_now" == type){
        tcp_acc_close_now(argc,argv);
    }
    return 0;
}


