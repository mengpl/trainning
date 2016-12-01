#include "util.h"

namespace remote_file_edit
{

    int SpiltString(const string& in_str,const string& in_divideStr,vector<string>*out_list)
    {
        string   strBuf, sDiv;
        string::size_type begin_pos = 0, end_pos = 0, i = 0;

        if (!out_list->empty())
            out_list->clear();

        if (in_str.empty())
            return 0;

        if (in_divideStr.empty())
        {
            out_list->push_back(in_str);
            return 1;
        }
        
        sDiv = in_divideStr.substr(i,1);
        while( in_str.find_first_of(sDiv) == string::npos )
        {
            if ( i < ( in_divideStr.length()-1) )
            {
                i++;
                sDiv = in_divideStr.substr(i,1);
            }
            else
            {
                out_list->push_back(in_str);
                return 1;
            }
        }
        

        while (begin_pos < in_str.length())
        {
            end_pos = in_str.find(sDiv, begin_pos);
            if (end_pos == string::npos)
            {
                strBuf = in_str.substr(begin_pos, in_str.length()-begin_pos);
                begin_pos = in_str.length();
            }
            else
            {
                if (begin_pos == end_pos)
                    strBuf = " ";
                else
                    strBuf = in_str.substr(begin_pos, end_pos-begin_pos);
                begin_pos = end_pos + 1;
            }
            if ((!strBuf.empty()) && (strBuf.length()>0))
                out_list->push_back(strBuf);
        }

        return out_list->size();
    }

    bool IsEndWith(const string str, const char cChar)
    {
        const char * szLine = str.c_str();
        
        int iLen = str.size();
        if(szLine[iLen -1] == cChar)
            return true;

        return false;
    }

    string TrimSpace(string s)
    {
        int i=0;
        while (s[i]==' '||s[i]=='\t')//开头处为空格或者Tab，则跳过
        {
            i++;
        }
        s = s.substr(i);
        i = s.size()-1;
        while(s[i]==' '||s[i]==' ')////结尾处为空格或者Tab，则跳过
        {
            i--;
        }
        s = s.substr(0,i+1);
        return s;
    }
}