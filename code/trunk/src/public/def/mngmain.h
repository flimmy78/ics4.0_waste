/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : mngmain.h
 Author         : 谭亮
 Version        : V 1.0
 Date           : 2003-04-08
 Description    : 前置上管理服务程序头文件
 Others         : 
 History        : 见下表

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
   01   2003-04-08  谭亮        创建
******************************************************************************/

#ifndef _MNGMAIN_H_
#define _MNGMAIN_H_
#include "himng.h"

#define CRCSVRGRP "crc"			/* 冲正服务器组名 */
#define CRCSVRNAM "S.CRCSVR"	/* 冲正服务器名 */
#define RDOSVRGRP "rdo"			/* 重发服务器组名 */
#define RDOSVRNAM "S.RDOSVR"	/* 重发服务器名 */
#define TIMSVRGRP "tim"			/* 定时触发服务器组名 */
#define TIMSVRNAM "S.SCHSVR"	/* 定时触发服务器名 */
#define STSSVRNAM "S.STSSVR"	/* 状态服务器名 */
#define GETALLSVR "090803"		/* 获得静态服务列表交易码 */
#define GETRUNSVR "090804"		/* 获得已经启动服务列表交易码 */
#define FNTMNGROT "FrontMan"	/* 前置管理服务配置文件根节点 */
#define RPTMNGFIL "RPTMNG_PUB.XML"	/* 报表管理配置文件名*/
#define TXNTRCFIL "TXNTRC.lst"	/* 交易跟踪日志文件名*/
#define BUSCFGFIL "BUSCFG.XML"	/* 业务平台公共配置文件*/
#define SYSCFGFIL "SYSCFG.XML"	/* 系统配置文件*/
#define SYSROTNOD "ParaList"    //系统配置文件根节点名

#define SYSMNGMSG "SYSMNG"		/* 平台管理消息类型 */
#define STATUSMSG "STATUS"		/* 状态管理消息类型 */

#define TABLE_NAME_LEN  32
#define COLUMN_NAME_LEN 32
#define COLUMN_MEAN_LEN 128
#define FLAG_LEN        1
#define MAX_COLUMN_NUM  32
#define IP_LEN         15

#define TBLTYP_LEN 	   1
#define BUSTYP_LEN	   6
#define CRPCOD_LEN	   10
#define MNG_TXNCOD_LEN	   32
#define TXNNAM_LEN     128
#define APPDES_LEN     128
#define TEXT_LEN	  1024
#define GRPID_LEN		6
#define APPID_LEN		3
#define SERVERID_LEN	8
#define THDTXNCOD_LEN     128

#endif	/* _MNGMAIN_H_ */
