/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: bpsmain.h 
 Author			: CaiJunJie 
 Version		: V1.0 
 Date			: 2003.05.06 
 Description	: 本头文件定义 BYPASS 子系统使用到的通信统计区数据结构
				 
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================
   01   2003-05-06  蔡俊杰		创建
   02   2003-06-27  谭亮		  修改
******************************************************************************/


#ifndef _BYPASS_H_
	#define _BYPASS_H_

#include <memory.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/socket.h>
#include <sys/signal.h>

#ifdef	_AIX_SYSTEM
#include <sys/select.h>
#endif

#include <netinet/in.h>
#include <signal.h>
#include "hibase.h"
#include "hilgr.h"
#include "hicpic.h"
#include "hibusmsg.h"
#include "mac3des_api.h"

#define		TIA_HEAD_LEN			171
#define		TOA_HEAD_LEN			114

#define		TCKNO_POS				67
#define		FINFLG_POS				88
#define		TURN_OFF				0
#define		TURN_ON					1

/* 定义线程是空闲还是在执行交易处理 */
#define 	BYPASS_IDEL				0
#define		BYPASS_BUSY				1

/* 定义服务是正常运行还是将结束运行 */
#define		BYPASS_NORMAL			0
#define		BYPASS_TO_END			1

/* 定义通信等待标志 */
#define		BYPASS_NO_WAIT			0
#define		BYPASS_WAIT				1

/* 定义交易通信处理是正常还是异常 */
#define		BYPASS_TXN_NORMAL		'N'
#define		BYPASS_TXN_ABEND		'E'

/* 通信监控、统计区数据结构，每个线程使用独立的统计区，汇总得出累计数据 */
typedef struct
{
	pthread_mutex_t	mutex;		/* 通信等待互斥变量 */
	unsigned char cConvId[8];	/* 当前交易使用的 Conversation ID */
	int		iRetCode;			/* 通信处理的返回码 */
	long	lTotalTxn; 			/* 总交易笔数，含超时、出错交易笔数 */
	long	lErrTxn;			/* 出错交易笔数 */
	long	lTimeOutTxn;		/* 超时交易笔数 */
	long	lExTxn1;			/* 超出警戒通信时间1（例如 2 秒）的交易笔数 */
	long	lExTxn2;			/* 超出警戒通信时间2（例如 5 秒）的交易笔数 */
	long	lExTxn3;			/* 超出警戒通信时间3（例如 10 秒）的交易笔数 */
	float   fCurrTime;			/* 当前交易通信时间 */
	double  dTotalTime; 		/* 总交易通信时间，不含超时、通信异常的交易 */
	double  dExTime;	 		/* 通信时间较长（超出时间1）的交易通信时间总和 */
	double	dTotalLen;			/* 通信总长度 */
	int		iBusyFlag;			/* 当前线称是否正在处理交易标志 0:空闲 1:处理中 */
	int		iWaitFlag;			/* 当前线程是否正在等待通信返回标志 0:不 1:等待 */
	struct	timeb  sLastTime;	/* 本线程执行上一笔交易的开始时间 */
	int		iTimeOut;			/* 当前交易的超时时间，以秒为单位 */
	int		iErrorCode;			/* 如果上笔交易出错，通信出错代码 */
	long	lTcpErrTxn;			/* TCP/IP 通信出错次数 */
} MonitorData;


/* 定义 BYPASS 通信 TIA 包结构 */ 
typedef struct
{
	/* 数据长度存在于 TIA 结构中，但是不保存该数据项在内存中 */
	/* char	cDataLen[8];		   交易数据包整包长度 */ 
	char	cTxnType[8 + 1];		/* 交易类别 */
	char	cCicsTxn[TP_NAME_LEN + 1];		/* 主机交易码 */
	char	cTxnCode[8 + 1];		/* 应用交易码 */
	char	cTellerNo[8 + 1];		/* 交易柜员号 */ 
	char	cTxnTerm[8 + 1];		/* 交易终端号 */
	char	cTimeOut[3 + 1];		/* 交易超时时间 */ 
	char	cReserved[19 + 1];		/* 保留字段 */
	char	cTxnData[16*1024];		/* 交易数据包 */
} TIA;

/* 定义 BYPASS 通信 TOA 包结构 */ 
typedef struct
{
	/* 数据长度存在于 TOA 结构中，但是不保存该数据项在内存中 */
	/* char	cDataLen[8];		   交易数据包整包长度 */ 
	char	cTxnFlag[1 + 1];		/* 交易处理标识 */
	char	cMsgCode[6 + 1];		/* 出错信息码 */
	char	cReserved[19 + 1];		/* 保留字段 */
	char	cTxnData[16*1024];		/* 交易数据包 */
} TOA;

/* 定义交易的主要信息结构 */ 
typedef struct
{
	char	cTTxnCd[8 + 1];		   /* 交易代码 */
	char	cTlrId[10 + 1];		   /* 柜员 */
	char	cNodNo[6 + 1];		   /* 网点 */
	char	cTxnTm[14 + 1];		   /* 时间 */
	char	cFinFlg[1 + 1];		   /* 性质 */
	char	cTckNo[12 + 1];		   /* 交易日志号 */
	char	cHRspCd[6 + 1];		   /* 返回码 */
} TXN_INF;

#endif
