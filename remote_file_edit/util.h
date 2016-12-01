#ifndef __UTIL_H__
#define __UTIL_H__
#include <string>
#include <vector>

using namespace std;
namespace remote_file_edit
{
    int SpiltString(const string& in_str,const string& in_divideStr,vector<string>*out_list);

    bool IsEndWith(const string str, const char cChar);

    string TrimSpace(string s);

}

#endif /* __UTIL_H__ */