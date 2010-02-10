/******************************************************************************


				Copyright (C),1998-2008,Hisuntech Co.,Ltd.

 File name		: hisaf.h
 Author			: WangXiaoDong
 Version		: 1.0
 Date			: 2003-04-25
 Description	: 这是存储转发服务头文件。     
 Others			: 无
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2003-04-25	WXD         创建
  002	2008-11-12	LiangWJ     应用隔离改造
******************************************************************************/ 
#ifndef _HISAF_H_
#define _HISAF_H_

#include "hibase.h"
#include "hiserver.h"
#include "hidatabase.h"
#include "hietf.h"

/*
 * 定义ETF树各节点名字
 */
#define  NODE_MSGTYPE          "MsgTyp"            /* 消息类型            */
#define  NODE_FILENAM          "FilNam"            /* 文件名              */
#define  NODE_LOCALFILE        "LclFil"            /* 本地文件名              */
#define  NODE_GROUP            "Group"             /* 组                  */
#define  NODE_PRIID1           "NodNo"            /* 私有id1             */
#define  NODE_PRIID2           "TlrNo"            /* 私有id2             */
#define  NODE_EPRDAT           "EprDat"            /* 失效日期            */
#define  NODE_EPRTM            "EprTm"             /* 失效时间            */
#define  NODE_DATA             "Data"              /* 数据                */
#define  NODE_PROFLG           "ProFlg"            /* 失效后续处理标志    */
#define  NODE_TXNCOD           "AplCod"            /* 交易码              */
#define  NODE_RECNUM           "RecNum"            /* 循环记录条数        */

#define  ERRCODE               0                   /* 错误码起始数        */
#define  MSG_FROM_BUS          "SAFRQ0"            /* 来自业务平台消息类型*/
#define  SAF_INVOKER_MSG       "SAFRQ1"            /* 轮询请求消息类型    */
#define  SAF_CLEAN_MSG         "SAFRQ2"            /* 清理请求消息类型    */
#define  PRELEN_LEN            8                   /* 前置长度的长度      */
#define  MAX_REC_NUM           100                 /* 待发送目的地数      */
#define  PORT_LEN              5                   /* 端口号长度          */
#define  MSGTYPE_LEN           6                   /* 转发消息类型        */
#define  ERRCODE_LEN           6                   /* 错误码长度          */

#define  SAFJNL_RECKEY_LEN     8                   /* 记录唯一标识       */
#define  SAFJNL_MSGTYP_LEN     1                   /* 消息类型           */
#define  SAFJNL_FILNAM_LEN     50                  /* 文件名称           */
#define  SAFJNL_EPRDAT_LEN     8                   /* 数据失效日期       */
#define  SAFJNL_EPRTM_LEN      6                   /* 数据失效时间       */
#define  SAFJNL_PROFLG_LEN     1                   /* 数据失效后处理标志 */
#define  SAFJNL_DATA_LEN       3072                /* 数据               */
#define  SAFJNL_BORDNUM_LEN    3                   /* 广播网点数         */
#define  SAFJNL_PRIID1_LEN     6                   /* 目的网点代码       */
#define  SAFJNL_PRIID2_LEN     7                   /* 目的柜员代码       */
#define  SAFJNL_RVSSTS_LEN     1                   /* 状态               */
#define  SAFJNL_IPADDR_LEN     15                  /* 目的地ip地址长度   */
#define  SAFJNL_PORT_LEN       6                   /* 目的地通讯端口长度 */
#define  SAFJNL_TXNCOD_LEN     6                   /* 交易码长度         */
#define  SAFJNL_OBJSVR_LEN     8                   /* 目标服务器长度     */

//#ifdef	SYBASE
//EXEC     SQL BEGIN DECLARE SECTION; 
//#endif
typedef struct
{
        char    RecKey[ SAFJNL_RECKEY_LEN + 1];    /* 记录唯一标识        */
        char    MsgTyp[ SAFJNL_MSGTYP_LEN + 1];    /* 消息类型1:通知      */
                                                   /* 2:广播 3:文件 4:打印*/
        char    ObjSvr[ SAFJNL_OBJSVR_LEN + 1];    /* 目标服务器          */
        char    TxnCod[ SAFJNL_TXNCOD_LEN + 1];    /* 交易码              */
        char    FilNam[ SAFJNL_FILNAM_LEN + 1];    /* 文件名              */
        char    Data[   SAFJNL_DATA_LEN   + 1];    /* 通知或广播数据      */
        char    PriId1[ SAFJNL_PRIID1_LEN + 1];    /* 目的机构代码        */
        char    PriId2[ SAFJNL_PRIID2_LEN + 1];    /* 目的柜员代码        */
        char    EprDat[ SAFJNL_EPRDAT_LEN + 1];    /* 失效日期            */
        char    EprTm[  SAFJNL_EPRTM_LEN  + 1];    /* 失效时间            */
        char    ProFlg[ SAFJNL_PROFLG_LEN + 1];    /* 失效后续处理标志    */
                                                   /* 1：送监控 0：删除   */
        char    IpAdr[ SAFJNL_IPADDR_LEN + 1];    /* 目的地ip地址        */
        char    Port[ SAFJNL_PORT_LEN + 1];    /* 目的地通讯端口       */
        char    RvsSts[ SAFJNL_RVSSTS_LEN + 1];    /* 转发状态 0:需要转发 */
                                                   /* 1:正在转发 2:失效   */
                                                   /* 9:转发成功          */
}SAF_SAFJNL_TYPE; 

/*
 * 网点-柜员结构表
 */
typedef struct
{
   char aPriId1[SAFJNL_PRIID1_LEN + 1 ];           /* 键1                 */
   char aPriId2[SAFJNL_PRIID2_LEN + 1 ];           /* 键2                 */
}BORD_TLR;

//
//#ifdef	SYBASE
//EXEC SQL END DECLARE SECTION;
//#endif

#ifdef  _HISAF_LIB_
#define EXTERN
#else
#define EXTERN  extern
#endif

/*
 * 存储转发登记函数 名称：safTranRegister
 * 参数: ETF *          ：ETF数据树根节点
 *       char *         ：目标服务器名
 *       char *         ：交易码
 *       long           ：有效时间
 * 返回: 0:  成功
 *       <0: 失败
 */
EXTERN int safTranRegister(ETF *Root, char *ObjSvr, char *TxnCod, long EstTim, DBConHandle * DBHandle);

#undef	EXTERN

/* 
 * 以下部分为应用隔离改造而新增 
 * Added by liangwj at 2008-11-12
 */
#ifndef	TABLENAME_MAX_LEN
#define	TABLENAME_MAX_LEN	20
#endif

/* 全局变量 */
#ifndef HISAF_EXTERN
#define HISAF_EXTERN
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN char _SafID[TABLENAME_MAX_LEN+1];    	/* 存储转发ID生成表 */
EXTERN char _SafStsJnl[TABLENAME_MAX_LEN+1];    /* 存储转发状态日志表 */
EXTERN char _SafDatJnl[TABLENAME_MAX_LEN+1];    /* 存储转发数据日志表 */
#undef	EXTERN

#define	SAF_ID_NAME			"ics.plt.safid_tablename"
#define	SAF_STS_JNL_NAME	"ics.plt.safstsjnl_tablename"
#define	SAF_DAT_JNL_NAME	"ics.plt.safdatjnl_tablename"

#endif /* _HISAF_H_ */
