#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;

template<class Key, class Value>
inline ostream& operator<<(ostream& str, const map<Key, Value>& data)
{
    str << "{\n\t";
    typedef typename map<Key, Value>::const_iterator ConstIterator;
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

template<class Key, class Value>
inline ostream& operator<<(ostream& str, const pair<Key, Value>& data)
{
    return str << "[key = " << data.first << "," << "value = " << data.second << "]";
}

class CTest
{
public:
    CTest(){}
    ~CTest(){}

    bool operator <(const CTest& cTest) const
    {
// #ifdef POS
//         return m_iSize < cTest.get_size();
// #endif
//         return m_iSize > cTest.get_size();

        if(m_iSize < cTest.get_size())
        {
            return true;
        }
        else
        {
            if(m_iFlag < cTest.get_flag())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
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
    inline int get_flag() const
    {
        return m_iFlag;
    }

    inline void set_flag(const int & iFlag)
    {
        m_iFlag = iFlag;
    }

private:
    int m_iSize;
    int m_iFlag;
};

inline ostream& operator<<(ostream& str, const CTest& data)
{
    return str << "[size = " << data.get_size() << ", flag = " << data.get_flag() <<"]";
}

int main(int args,char* argvs[])
{
    map<string,string> mapStr;
    mapStr.insert(make_pair("ab","ab"));
    mapStr.insert(make_pair("1","1"));
    mapStr.insert(make_pair("2","2"));
    mapStr.insert(make_pair("abc","abc"));
    mapStr.insert(make_pair("aba","aba"));

    map<CTest,int> mapClass;
    
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(1);
    v.push_back(2);

    for(vector<int>::iterator it = v.begin();
            it!= v.end(); ++it)
    {
        CTest cTest;
        cTest.set_size(*it);
        cTest.set_flag(*it);

        map<CTest,int>::iterator itFind = mapClass.find(cTest);
        if(itFind != mapClass.end())
        {
            itFind->second += *it;
        }
        else
        {
            mapClass.insert(make_pair(cTest,*it));
        }
    }

    cout << mapStr << endl;
    cout << mapClass << endl;
}