#include <iostream>
#include <string.h>

/**
 * 该程序是为测试stl的string在某种情况下，发生了core
 * 当构造函数的写法为写法一的情况，程序发生了core
 * 测试环境为 
 * Linux mengpl-virtual-machine 3.2.0-23-generic #36-Ubuntu SMP Tue Apr 10 20:39:51 UTC 2012 x86_64 x86_64 x86_64 GNU/Linux
 * 编译器为
 * g++ (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3
 * core信息如下：
 * (gdb) where
    #0  0x00007ffff7b78bca in ?? () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
    #1  0x00007ffff7b79ff6 in std::string::assign(std::string const&) () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
    #2  0x0000000000400ca9 in StringTest::set_phone (this=0x7fffffffdb60, strPhone=...) at stlstringtest.cpp:26
    #3  0x0000000000400b3e in main (argc=1, argv=0x7fffffffdc78) at stlstringtest.cpp:38
 * 当修改为写法二的情况时，未发生core
 */
class StringTest
{
public:
    // 写法一
    StringTest()
    {
        memset(this, 0, sizeof(*this));
    }

    // // 写法二
    // StringTest():iSize(0),phone("")
    // {
    // }

    inline int get_size() const
    {
        return m_iSize;
    }
    inline std::string get_phone() const
    {
        return m_strPhone;
    }
    inline void set_size(const int & iSize)
    {
        m_iSize = iSize;
    }
    inline void set_phone(const std::string & strPhone)
    {
        m_strPhone = strPhone;
    }

private:
    int m_iSize;
    std::string m_strPhone;
};

int main(int argc,char * argv[])
{
    StringTest sTest;
    sTest.set_size(1);
    sTest.set_phone("");
    std::cout << sTest.get_size() << std::endl; 
}