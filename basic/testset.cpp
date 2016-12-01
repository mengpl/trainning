#include<iostream>
#include<string>
#include<set>

using namespace std;

/**
 * 重载<< 用于输出
 */
template<class Data>
inline ostream& operator<<(ostream& str, const set<Data>& data)
{
    str << "{\n\t";
    typedef typename set<Data>::const_iterator ConstIterator;
    for(ConstIterator iter = data.begin(); iter != data.end(); ++iter)
    {
        ConstIterator iterTmp = iter;
        iterTmp++;
        if(iterTmp == data.end())
        {
            str << *iter << "\n";
        }
        else
        {
            str << *iter << "\n\t";
        }
    }
    return str << "}";
}

/**
 * 测试类
 */
class CTest
{
public:
    CTest(){}
    ~CTest(){}

    bool operator <(const CTest& cTest) const
    {
#ifdef POS
        return m_iSize < cTest.get_size();
#endif
        return m_iSize > cTest.get_size();
    }

public:
    inline int get_size() const
    {
        return m_iSize;
    }

    inline void set_size(const int & iSize)
    {
        m_iSize = iSize;
    }

private:
    int m_iSize;
};

/**
 * 重载<< 用于输出
 */
inline ostream& operator<<(ostream& str, const CTest& data)
{
    return str << "[size = " << data.get_size() << "]";
}

int main(int args,char* argvs[])
{
    set<string> setStr;
    setStr.insert("ab");
    setStr.insert("1");
    setStr.insert("2");
    setStr.insert("abc");
    setStr.insert("aba");

    set<CTest> setClass;
    CTest cTest1;
    CTest cTest2;
    cTest1.set_size(1);
    cTest2.set_size(2);
    setClass.insert(cTest1);
    setClass.insert(cTest2);

    set<int> setInt;
    setInt.insert(1);
    setInt.insert(2);
    setInt.insert(2);

    cout << setStr << endl;
    cout << setClass << endl;
    cout << setInt << endl;
}