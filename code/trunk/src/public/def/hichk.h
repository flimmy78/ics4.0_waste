/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hichk.h
 Author         : Song Jing Yi
 Version        : 1.0
 Date           : 2003-04-12
 Description    : ҵ��ƽ̨����ͷ�ļ�
 Others         : ��
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-04-12  SongJY      ���

******************************************************************************/
#ifndef  _HI_CHECK_H
#define  _HI_CHECK_H

/*modified by kixiong at 2008-10-30 17:01
EXEC SQL INCLUDE "hibat.h";
*/
#include "hibat.h"

#define HOST_CHECKACCOUNT_TXNCOD  "888888"  /* �������ʽ��״��� */
#define MAX_OUTTIME_ERR_NUM_PER   10        /* ÿ�����ʱ,������� */
#define DELAY_TIME                120       /* �������ط�����ֹ�����ʱ */
#define MAX_NUM_LIST_TABLE        100       /* ǰ��ҵ����ˮ��������� */
#define CHK_INTERVAL              300       /* ��ֹ�������ط���ڶ��ζ��ʵļ��ʱ�� */

int checkHostAccount(ETF *, TranData *, PbItemData, DBConHandle *, char *, char *, char *, char *);

#endif
