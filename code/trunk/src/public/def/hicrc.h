/********************************************************************
Copyright (C),1998-2003,Hisuntech Co.,Ltd.
  File name:      // hicrc.h
  Author:         // Wangxd
  Version:        // 1.0
  Date:           // 20030416
  Description:    // 这是冲正管理服务用到的唯一的头文件
                  // 主要定义冲正流水表结构
  Others:         // 其它内容的说明
  Function List:  // 主要函数列表，每条记录应包括函数名及功能简要说明
    1. ....
  History:        // 修改历史记录列表，每条修改记录应包括修改日期、
                  // 修改者及修改内容简述  
    1. Date:
       Author:
       Modification:
    2. ...
********************************************************************/

#ifndef	_HICRC_H_
#define	_HICRC_H_

#include "hiserver.h"
#include "hidatabase.h"

#define  ERRCODE              0
#define  CRCT_INVOKER_MSG     "CRCT01"
#define  CRCT_CLEAN_MSG       "CRCT02"
#define  MSG_TYPE_LEN         6

#define  SSC_LEN              6
#define  CRC_SUCCESS          "000000"

/*
#ifdef	SYBASE
EXEC SQL BEGIN DECLARE SECTION; 
#endif
*/

/*
 * 定义冲正流水表结构
 */
#define CRC_CRCTJNL_LOGNO_LEN  14
#define CRC_CRCTJNL_TXNCOD_LEN 6
#define CRC_CRCTJNL_RTXNCD_LEN 6
#define CRC_CRCTJNL_OPRCLK_LEN 10
#define CRC_CRCTJNL_ITV_LEN    10
#define CRC_CRCTJNL_TMOUT_LEN  4
#define CRC_CRCTJNL_FALTMS_LEN 4
#define CRC_CRCTJNL_MAXTMS_LEN 4
#define CRC_CRCTJNL_RVSSTS_LEN 1
#define CRC_CRCTJNL_OBJSVR_LEN 8
#define CRC_CRCTJNL_ACTDAT_LEN 8
#define CRC_CRCTJNL_DATLEN_LEN 6

/*
 * 流水表记录状态
 */
#define CRC_ORIGIN             '0'
#define CRC_NEED_CORRECT       '1'
#define CRC_GOING_CORRECT      '2'
#define CRC_BEYOND_CORRECT     '4'
#define CRC_YESTERDAY_REC      '8'
#define CRC_SUCCESSFUL         '9'

/*
 * 冲正流水表
 */
typedef struct 
{
        char    LogNo[CRC_CRCTJNL_LOGNO_LEN + 1];        /*冲正流水号  */
        char    TxnCod[CRC_CRCTJNL_TXNCOD_LEN + 1];      /*原交易码    */
        char    RTxnCd[CRC_CRCTJNL_RTXNCD_LEN + 1];      /*冲正交易码  */
        char    OprClk[CRC_CRCTJNL_OPRCLK_LEN + 1];      /*冲正发起时间 */
        char    Itv[CRC_CRCTJNL_ITV_LEN + 1];            /*轮询间隔时间 */
        char    TmOut[CRC_CRCTJNL_TMOUT_LEN + 1];        /*超时时间     */
        char    FalTms[CRC_CRCTJNL_FALTMS_LEN + 1];      /*冲正失败次数 */
        char    MaxTms[CRC_CRCTJNL_MAXTMS_LEN + 1];      /*最大冲正次数 */
        char    RvsSts[CRC_CRCTJNL_RVSSTS_LEN + 1];      /*冲正状态     */
        char    ObjSvr[CRC_CRCTJNL_OBJSVR_LEN + 1];      /* 目标服务名  */
        char    ActDat[CRC_CRCTJNL_ACTDAT_LEN + 1];      /*会计日期     */
}CRC_CRCTJNL_TYPE; 

/*
#ifdef	SYBASE
EXEC SQL END DECLARE SECTION;
#endif
*/

#ifdef	_HICRCT_LIB_
#define	EXTERN	
#else
#define	EXTERN	extern
#endif

EXTERN long getSysSeconds();
EXTERN long getSysHours();

//#ifdef	SYBASE
/*
 * 冲正登记函数 名称：crcTranRegister
 * 参数: CRC_CRCTJNL_TYPE * crctJnl 结构见上
 * 返回: 0:成功
 *       1:流水号,原交易码和反交易码，轮询间隔时间、最大重发次数、超时时间为空目
 *         标服务名称,会计日期中有空值
 *       2:轮询间隔时间、最大重发次数、超时时间中有非法数字
 *    其它:SQL的错误码

 */
EXTERN int crcTranRegister(CRC_CRCTJNL_TYPE * , DBConHandle *);

/*
 * 冲正修改函数　名称：crcTranUpdate
 * 参数：流水号，原交易码(可以为空)，状态(1：需要冲正 9:不冲或冲正成功)
 * 返回: 0:成功
 *       1:流水号或状态是空值
 *       2:状态不是数字
 *    其它:SQL的错误码
 */
EXTERN int crcTranUpdate(char *,char *,char *, DBConHandle *);

/*
 * 取冲正状态函数　名称：crcGetStatus
 * 参数：流水号, 冲正状态
 * 返回: SQLCODE
 */
EXTERN int crcGetstatus(char *, char *, DBConHandle *);

/*
 * 冲正取消函数　名称：crcCancel
 * 参数：流水号, 提交标志
 * 返回: 0:成功
 *    其它:SQL的错误码
 */
EXTERN int crcCancel(char *, int, DBConHandle *);

#undef	EXTERN

//#endif /* SYBASE */

/* 
 * 以下部分为应用隔离改造而新增 
 * Added by liangwj at 2008-11-12
 */
#ifndef	TABLENAME_MAX_LEN
#define	TABLENAME_MAX_LEN	20
#endif

/* 全局变量 */
#ifndef HICRCT_EXTERN
#define HICRCT_EXTERN
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN char _CrcJnl[TABLENAME_MAX_LEN+1];    /* 冲正日志表名 */
#undef	EXTERN

#define	CRC_JNL_NAME	"ics.plt.crcjnl_tablename"


#endif /* _HICRC_H_ */
