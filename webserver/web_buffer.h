#ifndef __WEB_BUFFER_H__
#define __WEB_BUFFER_H__
#include <stddef.h>

namespace webserver
{
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

        /*
        extern void buffer_strcat(BUFFER *wb, const char *txt);
        extern void buffer_rrd_value(BUFFER *wb, calculated_number value);

        extern void buffer_date(BUFFER *wb, int year, int month, int day, int hours, int minutes, int seconds);
        extern void buffer_jsdate(BUFFER *wb, int year, int month, int day, int hours, int minutes, int seconds);

        extern BUFFER *buffer_create(size_t size);
        extern void buffer_free(BUFFER *b);
        extern void buffer_increase(BUFFER *b, free_size_required);

        extern void buffer_snprintf(BUFFER *wb, size_t len, const char *fmt, ...);
        extern void buffer_vsprintf(BUFFER *wb, const char *fmt, va_list args);
        extern void buffer_sprintf(BUFFER *wb, const char *fmt, ...);
        extern void buffer_strcat_htmlescape(BUFFER *wb, const char *txt);

        extern void buffer_char_replace(BUFFER *wb, char from, char to);

        extern char *print_number_lu_r(char *str, unsigned long uvalue);
        extern char *print_number_llu_r(char *str, unsigned long long uvalue);

        extern void buffer_print_llu(BUFFER *wb, unsigned long long uvalue);
        */
    };
}

#endif