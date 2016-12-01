
#ifndef __OTL_SELF_H__
#define __OTL_SELF_H__

#include <sys/msg.h>

#if defined(DB_TYPE_MYSQL) //mysql

#define OTL_ODBC
#define OTL_ODBC_SELECT_STM_EXECUTE_BEFORE_DESCRIBE
#define OTL_ODBC_UNIX

#elif defined(DB_TYPE_ORA) //oracle

#if defined(OTL_ORA11G)
//����ú�ɽ����10G,11G������£�double���Ͳ�������������
#define OTL_ORA_LEGACY_NUMERIC_TYPES
#endif
#endif

#ifdef USE_OTL_BIGINT
#define OTL_BIGINT int64

/*This #define enables the mapping from <bigint> for 64-bit OCIs for LP64 platforms to signed 64-bit longs. 
It's a more efficient alternative to the char[XXX] binding and bigint-string / string-bigint conversion 
(see also the following #define's: OTL_BIGINT,  OTL_BIGINT_TO_STR,   OTL_STR_TO_BIGINT).*/
//��int64���䵽long�ϣ������ĺô��ǲ���Ҫ�ٶ���OTL_BIGINT_TO_STR��OTL_STR_TO_BIGINT������ת����
#define OTL_ORA_MAP_BIGINT_TO_LONG
#endif

#define OTL_DESTRUCTORS_DO_NOT_THROW 
#define OTL_STL

#include "otl.4.0.254.h"
#endif
