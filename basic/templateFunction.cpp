#include<iostream>
#include<string>

//疑问：为何54行，使用std::string作为模板时
//max前面需要增加一个::,增加这个含义好像是std::为何是这样？
class CTest
{
public:
    CTest(){}
    ~CTest(){}

    bool operator <(const CTest& cTest) const
    {
        return m_iSize < cTest.get_size();
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

inline std::ostream& operator<<(std::ostream& str, const CTest& cTest)
{
    return str << "size = " << cTest.get_size();
}

template<typename T>
inline T const& max(T const& a, T const& b)
{
    return a < b ? b : a;
}

int main()
{
    int i = 42;
    std::cout<<"max(7, i): "<< max(7, i) <<std::endl;

    double f1 = 3.4;
    double f2 = 5.6;
    std::cout<<"max(f1, f2): "<< max(f1, f2)<<std::endl;
    
    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout<<"max(s1, s2): "<<::max(s1, s2)<<std::endl;

    std::cout<< "max<double>(4, 4.2)" << max<double>(4, 4.2) << std::endl;

    CTest test1;
    test1.set_size(1);
    CTest test2;
    test2.set_size(2);

    std::cout<< "max<cTest>(test1,test2)" << max<CTest>(test1,test2) << std::endl;
    return 0;
}