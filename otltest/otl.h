
#ifndef __OTL_SELF_H__
#define __OTL_SELF_H__

#include <sys/msg.h>

#if defined(DB_TYPE_MYSQL) //mysql

#define OTL_ODBC
#define OTL_ODBC_SELECT_STM_EXECUTE_BEFORE_DESCRIBE
#define OTL_ODBC_UNIX

#elif defined(DB_TYPE_ORA) //oracle

#if defined(OTL_ORA11G)
//定义该宏可解决在10G,11G的情况下，double类型不走索引的问题
#define OTL_ORA_LEGACY_NUMERIC_TYPES
#endif
#endif

#ifdef USE_OTL_BIGINT
#define OTL_BIGINT int64

/*This #define enables the mapping from <bigint> for 64-bit OCIs for LP64 platforms to signed 64-bit longs. 
It's a more efficient alternative to the char[XXX] binding and bigint-string / string-bigint conversion 
(see also the following #define's: OTL_BIGINT,  OTL_BIGINT_TO_STR,   OTL_STR_TO_BIGINT).*/
//将int64隐射到long上，这样的好处是不需要再定义OTL_BIGINT_TO_STR和OTL_STR_TO_BIGINT来进行转换。
#define OTL_ORA_MAP_BIGINT_TO_LONG
#endif

#define OTL_DESTRUCTORS_DO_NOT_THROW 
#define OTL_STL

#include "otl.4.0.254.h"
#endif
