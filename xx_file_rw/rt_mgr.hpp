#pragma once
#include "xio.hpp"
#include "xrb.hpp"
#include "xtime.hpp"
#include "xevt.hpp"
#include "xargs.hpp"
#include "json.hpp"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"


class rt_conf {
public:
typedef rapidxml::xml_node<char> xml_node_t;
    int read_conf(const string &conf_path)
    {
        read_xml_conf(conf_path);
        read_json_conf();



        return err_ok;
    }
    

    string get_xml_val(const string &xpath)
    {
        vector<string> xpath_vec = xsplit(xpath,"/");
        if(0 == xpath_vec.size())
        {
            return "";
        }
        xml_node_t * cur_node = xml_doc_;

        for (auto i = 0; i < xpath_vec.size(); i++)
        {
            cur_node = cur_node->first_node(xpath_vec[i].c_str());
            if(nullptr == cur_node)
            {
                return "";
            }
        }

        return cur_node->value();
    }


private:    
    int read_json_conf()
    {
        string json_path = get_xml_val("/root/json_path/");
        CHECK0_RETV(json_path.empty(),err_data_err);

        std::ifstream ifs(json_path);
        CHECK0_RETV(ifs.is_open(),err_data_err);

        try{
            json_ = nlohmann::json::parse(ifs);
        }catch(...)
        {
            LOG_ERROR("json parse err");
            xexit(1);
        }
        return err_ok;
    }
    int read_xml_conf(const string &conf_path)
    {
        xml_file_ = new rapidxml::file<char>(conf_path.c_str());
        xml_doc_ = new rapidxml::xml_document<char>();
        try{
            xml_doc_->parse<0>(xml_file_->data());
        }catch(...)
        {
            LOG_ERROR("xml parse err\n");
            xexit(1);
        }
        
        return err_ok;

    }


public:
    rapidxml::file<char> *xml_file_;
    rapidxml::xml_document<char> *xml_doc_;
    
    nlohmann::json json_;
};

class rt_mgr {
public:
    int run(int argc, char** argv)
    {
        string conf_path = xx_get_arg(argc,argv,"-c");
        conf_.read_conf(conf_path);

        create_engine();
        create_rb();

        return 0;
    }

    int create_engine()
    {
        
        return 0;
    }
    int create_rb()
    {
        return 0;
    }
    int create_plugs()
    {
        return 0;
    }
    
public:
    std::map<string,epoll_thread>   engines_;
    std::map<uint32_t,rb_iov*>      rbs_;
    
    std::map<uint32_t,io*>          ios_;

    rt_conf conf_;
};