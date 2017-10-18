#ifndef __UTIL_H__
#define __UTIL_H__
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include "lock.h"

class CRefObject
{
public:
    CRefObject();
    virtual ~CRefObject();

    void SetLock(CLock* lock) { m_lock = lock; }
    void AddRef();
    void ReleaseRef();
    private:
    int				m_refCount;
    CLock*	m_lock;
};

class CBuffer
{
public:
    // 构造函数
    CBuffer(size_t size);

    // 无参构造函数
    CBuffer();

    // str构造函数
    CBuffer(const char * str);

    // 析构函数
    ~CBuffer();

    // copy 构造
    CBuffer(const CBuffer & other);

    // 赋值运算符
    CBuffer & operator= (CBuffer & other);

public:
    // 获取字符长度
    inline size_t get_len() const { return m_iLen; };

    //设置Buffer长度
    inline void set_len(size_t len) { m_iLen = len; };

    // 获取分配的字符空间
    inline size_t get_size() const { return m_iSize; };
    // 获取字符数组
    inline const char * get_buffer() const { return m_szBuffer; };
    // 预分配
    int reserve(size_t size);
    // 增加
    CBuffer append(char * str);
    CBuffer append(CBuffer & cBuffer);


private:
    void _buffer_create(size_t size);

public:
    size_t m_iSize;        // allocation size of buffer, in bytes
    size_t m_iLen;     // current data length in buffer, in bytes
    char * m_szBuffer;   // the buffer itself

};

static inline uint32_t simple_hash(const char *name) 
{
    unsigned char *s = (unsigned char *) name;
    uint32_t hval = 0x811c9dc5;
    while (*s) {
        hval *= 16777619;
        hval ^= (uint32_t) *s++;
    }
    return hval;
};

uint64_t get_tick_count();
void writePid();

#endif