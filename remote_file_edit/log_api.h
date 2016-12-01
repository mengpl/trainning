#ifndef __LOG_API_H__
#define __LOG_API_H__

#include <stdio.h>

namespace remote_file_edit
{
class CLogObject;

class CLog
{
public:
    CLog();
    virtual ~CLog();
    
    void log_trace(const char* format, ...);
    void log_debug(const char* format, ...);
    void log_info(const char* format, ...);
    void log_warn(const char* format, ...);
    void log_error(const char* format, ...);
    void log_fatal(const char* format, ...);
private:
    CLogObject* m_log;
};
}

#endif /* __LOG_API_H__ */