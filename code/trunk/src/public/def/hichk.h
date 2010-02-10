/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hichk.h
 Author         : Song Jing Yi
 Version        : 1.0
 Date           : 2003-04-12
 Description    : 业务平台批量头文件
 Others         : 无
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-04-12  SongJY      完成

******************************************************************************/
#ifndef  _HI_CHECK_H
#define  _HI_CHECK_H

/*modified by kixiong at 2008-10-30 17:01
EXEC SQL INCLUDE "hibat.h";
*/
#include "hibat.h"

#define HOST_CHECKACCOUNT_TXNCOD  "888888"  /* 主机对帐交易代码 */
#define MAX_OUTTIME_ERR_NUM_PER   10        /* 每次最大超时,错误笔数 */
#define DELAY_TIME                120       /* 冲正或重发被截止后的延时 */
#define MAX_NUM_LIST_TABLE        100       /* 前置业务流水表的最大个数 */
#define CHK_INTERVAL              300       /* 截止冲正或重发后第二次对帐的间隔时间 */

int checkHostAccount(ETF *, TranData *, PbItemData, DBConHandle *, char *, char *, char *, char *);

#endif
