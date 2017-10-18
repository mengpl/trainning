#include "util.h"

CRefObject::CRefObject()
{
	m_lock = NULL;
	m_refCount = 1;
}

CRefObject::~CRefObject()
{

}

void CRefObject::AddRef()
{
	if (m_lock)
	{
		m_lock->lock();
		m_refCount++;
		m_lock->unlock();
	}
	else
	{
		m_refCount++;
	}
}

void CRefObject::ReleaseRef()
{
	if (m_lock)
	{
		m_lock->lock();
		m_refCount--;
		if (m_refCount == 0)
		{
			delete this;
			return;
		}
		m_lock->unlock();
	}
	else
	{
		m_refCount--;
		if (m_refCount == 0)
			delete this;
	}
}

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
    return size;
}

// append
CBuffer CBuffer::append(char * str){
    int len = strlen(str);
    m_iSize += len;
    m_iLen += len;
    char * buffertmp = m_szBuffer;
    _buffer_create(m_iSize);
    strcat(m_szBuffer,str);

    return *this;
}

// append
CBuffer CBuffer::append(CBuffer & cbuffer){
    return append(cbuffer.m_szBuffer);
}

uint64_t get_tick_count()
{
#ifdef _WIN32
    LARGE_INTEGER liCounter; 
    LARGE_INTEGER liCurrent;

    if (!QueryPerformanceFrequency(&liCounter))
        return GetTickCount();

    QueryPerformanceCounter(&liCurrent);
    return (uint64_t)(liCurrent.QuadPart * 1000 / liCounter.QuadPart);
#else
    struct timeval tval;
    uint64_t ret_tick;

    gettimeofday(&tval, NULL);

    ret_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
    return ret_tick;
#endif
}

void writePid()
{
	uint32_t curPid;
#ifdef _WIN32
	curPid = (uint32_t) GetCurrentProcess();
#else
	curPid = (uint32_t) getpid();
#endif
    FILE* f = fopen("server.pid", "w");
    assert(f);
    char szPid[32];
    snprintf(szPid, sizeof(szPid), "%d", curPid);
    fwrite(szPid, strlen(szPid), 1, f);
    fclose(f);
}