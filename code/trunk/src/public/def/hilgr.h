/******************************************************************************

				Copyright (C),1998-2008,Hisuntech Co.,Ltd.

 File name		: hilgr.h
 Author			: Liang WenJian
 Version		: 1.0
 Date			: 2008-8-11
 Description	: ��־������ͷ�ļ�
 Others			: ��
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2008-8-11	LiangWJ     ����
  002	2009-1-18	LiangWJ     ����UDP���ͼ�ع���

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
 * ��־��Ϣ������
 */
struct _logger_message {
	DataSource	* msg_space;
};
typedef struct _logger_message LoggerMessage;

/*
 * ��־��Ϣ�����ṹ
 */
struct _logger_para {
	int		seq;					//��ǰ�������
	char	* data;					//��������֮�����־��ϢƬ��
	struct _logger_para * next;		//��һ���ڵ�
};
typedef struct _logger_para LoggerPara;

/*
 * ��־��������
 */
struct _log_buffer {
	int		len;					//��־���ݳ���
	char	* data;					//��־����
	struct _log_buffer * next;		//��һ���ڵ�
};
typedef struct _log_buffer LogBuffer;

/*
 * ��־��¼���ṹ
 */
struct _logger {
	int				level;			//��ǰ��־����
	int				max_size;		//��־�ļ��������
	int				max_buffer;		//��־�ļ���󻺴�
	int				curr_buffer;	//��ǰ������־�����ܳ���
	int				format;			//��־ʱ��ĸ�ʽ
	int				path_mode;		//����Ŀ¼ģʽ
	char			* path;			//����Ŀ¼
	char			* filename;		//��־�ļ���
#ifdef	_PTHREAD_
	pthread_mutex_t	lock;			//���Ʋ�����
#endif
	FILE			* fp;			//��־�ļ����
	LogBuffer		* buffer_head;	//������־���������׽ڵ�
	LogBuffer		* buffer_tail;	//������־���������׽ڵ�
	LoggerMessage	* msg_mng;		//��־��Ϣ������
	/*
	 * ����UDP���ͼ�ع��� 
	 * Added by liangwj at 2009-1-18
	 */
	int				mon_flag;		//���ͼ�ر�־
	char			mon_ip[15+1];	//��ط���IP
	int				mon_port;		//��ط���˿�
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

