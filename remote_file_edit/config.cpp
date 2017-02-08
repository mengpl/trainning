#include <errno.h>
#include "config.h"

namespace webserver
{
    void CReadConfig::init_config(string strFile)
    {
        FILE* fp = fopen(strFile.c_str(), "r");
        if (!fp)
        {
            // LOG_ERROR("can not open %s,errno = %d", strFile.c_str(),errno);
            return;
        }

        char buf[256];
        for (;;)
        {
            char* p = fgets(buf, 256, fp);
            if (!p)
                break;

            size_t len = strlen(buf);
            if (buf[len - 1] == '\n')
                buf[len - 1] = 0;           // remove \n at the end

            if (buf[len - 2] == '\r')
                buf[len - 2] = 0;           // remove \r at the end

            char* ch = strchr(buf, '#');    // remove string start with #
            if (ch)
                *ch = 0;

            if (strlen(buf) == 0)
                continue;

            pase_line(buf);
        }

        fclose(fp);
        m_load_ok = true;
    }

    void CReadConfig::pase_line(char * line)
    {
        char* p = strchr(line, '=');
        if (p == NULL)
            return;

        *p = 0;
        char* key =  trim_space(line);
        char* value = trim_space(p + 1);
        if (key && value)
        {
            m_config_map.insert(make_pair(key, value));
        }
    }

    char * CReadConfig::trim_space(char * name)
    {
        char* start_pos = name;
        while ( (*start_pos == ' ') || (*start_pos == '\t'))
        {
            start_pos++;
        }

        if (strlen(start_pos) == 0)
            return NULL;

        // remove ending space or tab
        char* end_pos = name + strlen(name) - 1;
        while ( (*end_pos == ' ') || (*end_pos == '\t'))
        {
            *end_pos = 0;
            end_pos--;
        }

        int len = (int)(end_pos - start_pos) + 1;
        if (len <= 0)
            return NULL;

        return start_pos;
    }

    string CReadConfig::read_config(const string strKey)
    {
        if (!m_load_ok)
            return "";

        map<string, string>::iterator it = m_config_map.find(strKey);
        if (it != m_config_map.end()) {
            return it->second;
        }

    return "";
    }
}