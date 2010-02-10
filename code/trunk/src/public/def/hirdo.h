/******************************************************************************


				Copyright (C),1998-2008,Hisuntech Co.,Ltd.

 File name		: hirdo.h
 Author			: WangXiaoDong
 Version		: 1.0
 Date			: 2003-04-16
 Description	: 这是重发管理服务头文件。     
 Others			: 无
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2003-04-16	WXD         创建
  002	2008-11-12	LiangWJ     应用隔离改造
******************************************************************************/ 

#ifndef	_HIRDO_H_
#define	_HIRDO_H_

#include "hiserver.h"

#define  ERRCODE              0
#define  RDO_INVOKER_MSG      "RDO001"
#define  RDO_CLEAN_MSG        "RDO002"
#define  MSG_TYPE_LEN         6
#define  RDO_SUCCESS          "000000"

#define  SSC_LEN              6

/*
 * deleted by kixiong at 2008-10-30 13:18
 * 数据库隔离改造
#ifdef	SYBASE
EXEC SQL BEGIN DECLARE SECTION; 
#endif
 */

/*
 * 定义重发流水表结构
 */
#define RDO_RDOJNL_LOGNO_LEN 80
#define RDO_RDOJNL_TXNCOD_LEN 6
#define RDO_RDOJNL_RTXNCD_LEN 6
#define RDO_RDOJNL_OPRCLK_LEN 20
#define RDO_RDOJNL_ITV_LEN 20
#define RDO_RDOJNL_TMOUT_LEN 20
#define RDO_RDOJNL_FALTMS_LEN 4
#define RDO_RDOJNL_MAXTMS_LEN 4
#define RDO_RDOJNL_RVSSTS_LEN 1
#define RDO_RDOJNL_OBJSVR_LEN 8
#define RDO_RDOJNL_ACTDAT_LEN 8
#define RDO_RDOJNL_DATLEN_LEN 6

/*
 * 重发流水表
 */

typedef struct 
{
        char    LogNo[RDO_RDOJNL_LOGNO_LEN + 1];        /*重发流水号  */
        char    TxnCod[RDO_RDOJNL_TXNCOD_LEN + 1];      /*原交易码    */
        char    OprClk[RDO_RDOJNL_OPRCLK_LEN + 1];      /*重发发起时间 */
        char    Itv[RDO_RDOJNL_ITV_LEN + 1];            /*轮询间隔时间 */
        char    TmOut[RDO_RDOJNL_TMOUT_LEN + 1];        /*超时时间     */
        char    FalTms[RDO_RDOJNL_FALTMS_LEN + 1];      /*重发失败次数 */
        char    MaxTms[RDO_RDOJNL_MAXTMS_LEN + 1];      /*最大重发次数 */
        char    RvsSts[RDO_RDOJNL_RVSSTS_LEN + 1];      /*重发状态     */
        char    ObjSvr[RDO_RDOJNL_OBJSVR_LEN + 1];      /* 目标服务名  */
        char    ActDat[RDO_RDOJNL_ACTDAT_LEN + 1];      /*会计日期     */
}RDO_RDOJNL_TYPE; 

/*
 * deleted by kixiong at 2008-10-30 13:18
 * 数据库隔离改造
#ifdef	SYBASE
EXEC SQL END DECLARE SECTION;
#endif
 */

#ifdef	_HIRDO_LIB_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

EXTERN long getSysSeconds();
EXTERN long getSysHours();

/*
 * deleted by kixiong at 2008-10-30 13:21
#ifdef	SYBASE
*/
/*
 * 重发登记函数
 * 参数：结构见上
 * 返回: 0:成功 
 *       1:流水号,原交易码和反交易码，轮询间隔时间、最大重发次数、超时时间为空目 *         标服务名称,会计日期中有空值
 *       2:轮询间隔时间、最大重发次数、超时时间中有非法数字
 *    其它:SQL的错误码
  
 */

EXTERN int rdoTranRegister(RDO_RDOJNL_TYPE * , DBConHandle *);

/*
 * 重发修改状态函数
 * 参数:流水号,交易码(可以为空),状态(1:需要重发 9:重发成功)
 * 返回: 0:成功 
 *       1:流水号或状态是空值
 *       2:状态不是数字
 *    其它:SQL的错误码
 */

EXTERN int rdoTranUpdate(char * ,char *,char * ,DBConHandle *);

/*
 * 取重发状态函数　名称：rdoGetStatus
 * 参数：流水号, 重发状态
 * 返回: SQLCODE
 */
EXTERN int rdoGetstatus(char *, char *, DBConHandle *);

/*
 * 重发取消函数　名称：rdoCancel
 * 参数：流水号, 提交标志
 * 返回: 0:成功
 *    其它:SQL的错误码
 */
EXTERN int rdoCancel(char *, int, DBConHandle *);

#undef	EXTERN

/*
 * deleted by kixiong at 2008-10-30 13:21
#endif	* SYBASE *
*/

/* 
 * 以下部分为应用隔离改造而新增 
 * Added by liangwj at 2008-11-12
 */
#ifndef	TABLENAME_MAX_LEN
#define	TABLENAME_MAX_LEN	20
#endif

/* 全局变量 */
#ifndef HIRDO_EXTERN
#define HIRDO_EXTERN
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN char _RdoJnl[TABLENAME_MAX_LEN+1];    /* 重发日志表名 */
#undef	EXTERN

#define	RDO_JNL_NAME	"ics.plt.rdojnl_tablename"

#endif /* _HIRDO_H_ */
