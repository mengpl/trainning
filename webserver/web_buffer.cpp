#include <string.h>
#include "web_buffer.h"

namespace webserver
{
    #define MIN_BUFFER_SIZE 4

    void CBuffer::_buffer_create(size_t size)
    {
        size = (size  < MIN_BUFFER_SIZE) ? MIN_BUFFER_SIZE : size;

        m_szBuffer = new char[size + 1];
        m_szBuffer[0] = '\0';
        m_iSize = size;
    }

    // 构造函数
    CBuffer::CBuffer(size_t size){
        _buffer_create(size);
        m_iLen = 0;
    }

    // 无参构造函数
    CBuffer::CBuffer(){
        _buffer_create(MIN_BUFFER_SIZE);
        m_iLen = 0;
    }

    // str构造函数
    CBuffer::CBuffer(const char * str){
        if(str == NULL)
        {
            _buffer_create(0);
            m_iLen = 0;
        }
        else
        {
            int len = strlen(str);
            _buffer_create(len+1);
            strcpy(m_szBuffer,str);
            m_iLen = len;
        }
    }

    // 析构函数
    CBuffer::~CBuffer()
    {
        if(m_szBuffer != NULL)
        {
            delete[] m_szBuffer;
            m_szBuffer = NULL;
        }
        m_iSize = 0;
        m_iLen = 0;
    }

    // copy 构造
    CBuffer::CBuffer(const CBuffer & other){
        m_iSize = other.get_size();
        _buffer_create(m_iSize);
        if(other.get_buffer() != NULL)
            strcpy(m_szBuffer,other.get_buffer());
        m_iLen = other.get_len();
    };

    // 赋值运算符
    CBuffer & CBuffer::operator= (CBuffer & other){
        if(this == &other)
            return *this;
        
        delete[] m_szBuffer;
        m_iSize = other.get_size();
        _buffer_create(m_iSize);
        if(other.get_buffer() != NULL)
            strcpy(m_szBuffer,other.get_buffer());
        m_iLen = other.get_len();
        return *this;
    }

    // 预分配空间
    int CBuffer::reserve(size_t size){
        _buffer_create(size);
    }

    // append
    CBuffer CBuffer::append(char * str){
        int len = strlen(str);
        m_iSize += len;
        m_iLen += len;
        char * buffertmp = m_szBuffer;
        _buffer_create(m_iSize);
        strcat(m_szBuffer,str);
    }

    // append
    CBuffer CBuffer::append(CBuffer & cbuffer){
        append(cbuffer.m_szBuffer);
    }
}