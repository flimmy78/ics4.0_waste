#ifndef _HIMON_H_
#define _HIMON_H_

#define _HI_VARARGS
#include "hiserver.h"

#define MON_MSG_TYPE	"SYSMON"
#define MONSVR			"S.MONSVR"

#define MAX_HEAD_LEN  256
#define MAX_LEN       8096
#define FILE_NAME_LEN 64
#define DATE_TIME_LEN 32
#define TTXNCD_LEN    30

#ifdef	_HIMON_LIB_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

EXTERN int monTranStatus(int , char *, char *, int );
EXTERN int monServerStatus(int , char *, int );
EXTERN int monConnStatus(int , char *, int );
EXTERN int monSpecailInfo(int , char *, int );
EXTERN int monBypassStatus(int, char *, int); /* ByPass 交易量 */
EXTERN int monByPassInfo(int, char *, int);   /* ByPass 交易详细信息 */

/* monTranStatus: 交易监控信息发送 */
/* 参数说明: int iOnOff:    日志开关 (1,记录; 否则,不记录);
             char *cTxnCod: 交易监控信息的交易码
			 char *cTxnDat: 交易监控信息的内容
			 int iDatLen:   交易监控信息的长度
   返回值:   0,表示成功; -1,表示失败;	*/

/* monServerStatus: 服务监控信息发送 */
/* 参数说明: int iOnOff:    日志开关 (1,记录; 否则,不记录);
			 char *cTxnDat: 服务监控信息的内容
			 int iDatLen:   服务监控信息的长度
   返回值:   0,表示成功; -1,表示失败;	*/

/* monConnStatus: 通讯监控信息发送 */
/* 参数说明: int iOnOff:    日志开关 (1,记录; 否则,不记录);
			 char *cTxnDat: 通讯监控信息的内容
			 int iDatLen:   通讯监控信息的长度
   返回值:   0,表示成功; -1,表示失败;	*/

/* monSpecialInfo: 警告信息发送 */
/* 参数说明: int iOnOff:    日志开关 (1,记录; 否则,不记录);
			 char *cTxnDat: 警告信息的内容
			 int iDatLen:   警告信息的长度
   返回值:   0,表示成功; -1,表示失败;	*/

#endif /* _HIMON_H_ */
