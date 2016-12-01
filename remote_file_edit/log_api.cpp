#include "log_api.h"
#include "log4cpp/Category.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/PropertyConfigurator.hh"

namespace remote_file_edit
{
    #define MAX_LOG_LENGTH 100000
    
    class CLogObject
    {
    public:
        CLogObject() {}
        virtual ~CLogObject() {}
        
        virtual void log_trace(const char* loginfo) {}
        virtual void log_debug(const char* loginfo) {}
        virtual void log_info(const char* loginfo) {}
        virtual void log_warn(const char* loginfo) {}
        virtual void log_error(const char* loginfo) {}
        virtual void log_fatal(const char* loginfo) {}
    };

    class CLog4CPP : public CLogObject
    {
    public:
        CLog4CPP();
        virtual ~CLog4CPP();
        
        void log_trace(const char* loginfo);
        void log_debug(const char* loginfo);
        void log_info(const char* loginfo);
        void log_warn(const char* loginfo);
        void log_error(const char* loginfo);
        void log_fatal(const char* loginfo);
    private:
        log4cpp::Category* m_logger;
    };

    CLog4CPP::CLog4CPP()
    {
        log4cpp::PropertyConfigurator::configure("log4cpp.conf");
        m_logger = &log4cpp::Category::getRoot();
    }

    CLog4CPP::~CLog4CPP()
    {
    }

    void CLog4CPP::log_trace(const char *loginfo)
    {
        m_logger->debug(loginfo);
    }

    void CLog4CPP::log_debug(const char *loginfo)
    {
        m_logger->debug(loginfo);
    }

    void CLog4CPP::log_info(const char *loginfo)
    {
        m_logger->info(loginfo);
    }

    void CLog4CPP::log_warn(const char *loginfo)
    {
        m_logger->warn(loginfo);
    }

    void CLog4CPP::log_error(const char *loginfo)
    {
        m_logger->error(loginfo);
    }

    void CLog4CPP::log_fatal(const char *loginfo)
    {
        m_logger->fatal(loginfo);
    }



    CLog::CLog()
    {
        m_log = new CLog4CPP();
    }

    CLog::~CLog()
    {
        delete m_log;
    }

    void CLog::log_trace(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        char szBuffer[MAX_LOG_LENGTH];
        vsnprintf(szBuffer, sizeof(szBuffer), format, args);
        va_end(args);
        m_log->log_trace(szBuffer);
    }

    void CLog::log_debug(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        char szBuffer[MAX_LOG_LENGTH];
        vsnprintf(szBuffer, sizeof(szBuffer) , format, args);
        va_end(args);
        m_log->log_debug(szBuffer);
    }

    void CLog::log_info(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        char szBuffer[MAX_LOG_LENGTH];
        vsnprintf(szBuffer, sizeof(szBuffer), format, args);
        va_end(args);
        m_log->log_info(szBuffer);
    }

    void CLog::log_warn(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        char szBuffer[MAX_LOG_LENGTH];
        vsnprintf(szBuffer, sizeof(szBuffer), format, args);
        va_end(args);
        m_log->log_warn(szBuffer);
    }

    void CLog::log_error(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        char szBuffer[MAX_LOG_LENGTH];
        vsnprintf(szBuffer, sizeof(szBuffer), format, args);
        va_end(args);
        m_log->log_error(szBuffer);
    }

    void CLog::log_fatal(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        char szBuffer[MAX_LOG_LENGTH];
        vsnprintf(szBuffer, sizeof(szBuffer), format, args);
        va_end(args);
        m_log->log_fatal(szBuffer);
    }
}