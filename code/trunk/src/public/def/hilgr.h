/******************************************************************************

				Copyright (C),1998-2008,Hisuntech Co.,Ltd.

 File name		: hilgr.h
 Author			: Liang WenJian
 Version		: 1.0
 Date			: 2008-8-11
 Description	: 日志管理器头文件
 Others			: 无
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2008-8-11	LiangWJ     创建
  002	2009-1-18	LiangWJ     增加UDP发送监控功能

******************************************************************************/
#ifndef	_HILGR_H_
#define	_HILGR_H_

#include "hibase.h"
#include "hixml.h"
#include "hidsm.h"
#include <pthread.h>

#define	LOG_INFINITY		-1

/* define the date-time's format in the log file */
#define	LOG_NO_DATETIME		0
#define	LOG_ONLY_TIME		1
#define	LOG_ALL_DATETIME	2

/* define the mode to save log file */
#define	LOG_MODE_NO_DAY		0
#define	LOG_MODE_HAVE_DAY	1

#define	LOG_OFF				0
#define	LOG_FATAL			1
#define	LOG_ERROR			2	
#define	LOG_WARN			3
#define	LOG_INFO			4
#define	LOG_INFO2			5
#define	LOG_INFO3			6
#define	LOG_DEBUG			7

#define	LOG_FATAL_S		"FATAL"
#define	LOG_ERROR_S		"ERROR"
#define	LOG_WARN_S		"WARN"
#define	LOG_INFO_S  	"INFO"
#define	LOG_INFO2_S  	"INFO2"
#define	LOG_INFO3_S  	"INFO3"
#define	LOG_DEBUG_S		"DEBUG"

#define LOG_COMM_SEND	"SEND"
#define LOG_COMM_RECV	"RECV"

#define	LOG_MAX_PARA	100

/*
 * 日志信息管理器
 */
struct _logger_message {
	DataSource	* msg_space;
};
typedef struct _logger_message LoggerMessage;

/*
 * 日志信息参数结构
 */
struct _logger_para {
	int		seq;					//当前参数序号
	char	* data;					//两个参数之间的日志信息片段
	struct _logger_para * next;		//下一个节点
};
typedef struct _logger_para LoggerPara;

/*
 * 日志内容链表
 */
struct _log_buffer {
	int		len;					//日志内容长度
	char	* data;					//日志内容
	struct _log_buffer * next;		//下一个节点
};
typedef struct _log_buffer LogBuffer;

/*
 * 日志记录器结构
 */
struct _logger {
	int				level;			//当前日志级别
	int				max_size;		//日志文件最大限制
	int				max_buffer;		//日志文件最大缓存
	int				curr_buffer;	//当前缓存日志内容总长度
	int				format;			//日志时间的格式
	int				path_mode;		//保存目录模式
	char			* path;			//保存目录
	char			* filename;		//日志文件名
#ifdef	_PTHREAD_
	pthread_mutex_t	lock;			//控制并发锁
#endif
	FILE			* fp;			//日志文件句柄
	LogBuffer		* buffer_head;	//缓存日志内容链表首节点
	LogBuffer		* buffer_tail;	//缓存日志内容链表首节点
	LoggerMessage	* msg_mng;		//日志信息管理器
	/*
	 * 增加UDP发送监控功能 
	 * Added by liangwj at 2009-1-18
	 */
	int				mon_flag;		//发送监控标志
	char			mon_ip[15+1];	//监控服务IP
	int				mon_port;		//监控服务端口
};
typedef struct _logger Logger;

#ifdef LIB_LGR_EXTERN
#define EXTERN
#else
#define EXTERN  extern
#endif /* LIB_LGR_EXTERN */

EXTERN LoggerMessage * logCreateMessage(int);
EXTERN void logDestroyMessage(LoggerMessage *);

EXTERN Logger * logCreate();
EXTERN void logDestroy(Logger *);

EXTERN int logSetFormat(Logger *, int);
EXTERN int logSetName(Logger *, char *);
EXTERN int logSetLevel(Logger *, int);
EXTERN int logSetMaxBuffer(Logger *, int);
EXTERN int logSetMaxSize(Logger *, int);
EXTERN int logSetMonitor(Logger *, int, char *, int);
EXTERN int logSetMessage(Logger *, LoggerMessage *);
EXTERN int logLevelS2N(char *, int *);
EXTERN char * logLevelN2S(int, char *);

EXTERN int logDebug(Logger *, char *, char *, ...);
EXTERN int logInfo(Logger *, char *, char *, ...);
EXTERN int logWarn(Logger *, char *, char *, ...);
EXTERN int logError(Logger *, char *, char *, ...);
EXTERN int logFatal(Logger *, char *, char *, ...);
EXTERN int logFlush(Logger *);
EXTERN int logComm(Logger *logger, char * req_id, char *type, char * addr, int text_len, char *text);
EXTERN int logSysDebug(char *, ...);
EXTERN int logSysInfo(char *, ...);
EXTERN int logSysWarn(char *, ...);
EXTERN int logSysError(char *, ...);
EXTERN int logSysFatal(char *, ...);

#undef	EXTERN

#endif /* _HILGR_H_ */

