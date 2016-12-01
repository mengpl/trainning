#ifndef __LOG_DEIFNE_H__
#define __LOG_DEIFNE_H__
#include <string.h>
#include "log_api.h"

using remote_file_edit::CLog; 
extern CLog g_log;

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

#define LOG_TRACE(fmt, ...) \
    {\
        g_log.log_trace("<%s>|<%d>|<%s>," fmt, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
    }

#define LOG_INFO(fmt, ...) \
    {\
        g_log.log_info("<%s>|<%d>|<%s>," fmt, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
    }

#define LOG_DEBUG(fmt, ...) \
    {\
        g_log.log_debug("<%s>|<%d>|<%s>," fmt, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
    }

#define LOG_ERROR(fmt, ...) \
    {\
        g_log.log_error("<%s>|<%d>|<%s>," fmt, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
    }

#define LOG_WARN(fmt, ...) \
    {\
        g_log.log_warn("<%s>|<%d>|<%s>," fmt, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
    }

#define LOG_FATAL(fmt, ...) \
    {\
        g_log.log_fatal("<%s>|<%d>|<%s>," fmt, __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
    }

#endif /*__LOG_DEIFNE_H__*/