/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : mngmain.h
 Author         : ̷��
 Version        : V 1.0
 Date           : 2003-04-08
 Description    : ǰ���Ϲ���������ͷ�ļ�
 Others         : 
 History        : ���±�

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
   01   2003-04-08  ̷��        ����
******************************************************************************/

#ifndef _MNGMAIN_H_
#define _MNGMAIN_H_
#include "himng.h"

#define CRCSVRGRP "crc"			/* �������������� */
#define CRCSVRNAM "S.CRCSVR"	/* ������������ */
#define RDOSVRGRP "rdo"			/* �ط����������� */
#define RDOSVRNAM "S.RDOSVR"	/* �ط��������� */
#define TIMSVRGRP "tim"			/* ��ʱ�������������� */
#define TIMSVRNAM "S.SCHSVR"	/* ��ʱ������������ */
#define STSSVRNAM "S.STSSVR"	/* ״̬�������� */
#define GETALLSVR "090803"		/* ��þ�̬�����б����� */
#define GETRUNSVR "090804"		/* ����Ѿ����������б����� */
#define FNTMNGROT "FrontMan"	/* ǰ�ù�����������ļ����ڵ� */
#define RPTMNGFIL "RPTMNG_PUB.XML"	/* ������������ļ���*/
#define TXNTRCFIL "TXNTRC.lst"	/* ���׸�����־�ļ���*/
#define BUSCFGFIL "BUSCFG.XML"	/* ҵ��ƽ̨���������ļ�*/
#define SYSCFGFIL "SYSCFG.XML"	/* ϵͳ�����ļ�*/
#define SYSROTNOD "ParaList"    //ϵͳ�����ļ����ڵ���

#define SYSMNGMSG "SYSMNG"		/* ƽ̨������Ϣ���� */
#define STATUSMSG "STATUS"		/* ״̬������Ϣ���� */

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
