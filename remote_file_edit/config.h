#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <map>
#include <string>
#include "log_define.h"

using namespace std;
namespace webserver
{
    class CReadConfig
    {
    public:
        CReadConfig(const string file)
        {
            init_config(file);
        };
        virtual ~CReadConfig(){};

    public:
        string read_config(const string key);

    private:
        void init_config(const string file);
        void pase_line(char * line);
        char * trim_space(char * line);
    private:
        map<string,string> m_config_map;
        bool m_load_ok;
    };

}

#endif// __CONFIG_H__