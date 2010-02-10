/******************************************************************************


				Copyright (C),1998-2008,Hisuntech Co.,Ltd.

 File name		: hisaf.h
 Author			: WangXiaoDong
 Version		: 1.0
 Date			: 2003-04-25
 Description	: ���Ǵ洢ת������ͷ�ļ���     
 Others			: ��
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2003-04-25	WXD         ����
  002	2008-11-12	LiangWJ     Ӧ�ø������
******************************************************************************/ 
#ifndef _HISAF_H_
#define _HISAF_H_

#include "hibase.h"
#include "hiserver.h"
#include "hidatabase.h"
#include "hietf.h"

/*
 * ����ETF�����ڵ�����
 */
#define  NODE_MSGTYPE          "MsgTyp"            /* ��Ϣ����            */
#define  NODE_FILENAM          "FilNam"            /* �ļ���              */
#define  NODE_LOCALFILE        "LclFil"            /* �����ļ���              */
#define  NODE_GROUP            "Group"             /* ��                  */
#define  NODE_PRIID1           "NodNo"            /* ˽��id1             */
#define  NODE_PRIID2           "TlrNo"            /* ˽��id2             */
#define  NODE_EPRDAT           "EprDat"            /* ʧЧ����            */
#define  NODE_EPRTM            "EprTm"             /* ʧЧʱ��            */
#define  NODE_DATA             "Data"              /* ����                */
#define  NODE_PROFLG           "ProFlg"            /* ʧЧ���������־    */
#define  NODE_TXNCOD           "AplCod"            /* ������              */
#define  NODE_RECNUM           "RecNum"            /* ѭ����¼����        */

#define  ERRCODE               0                   /* ��������ʼ��        */
#define  MSG_FROM_BUS          "SAFRQ0"            /* ����ҵ��ƽ̨��Ϣ����*/
#define  SAF_INVOKER_MSG       "SAFRQ1"            /* ��ѯ������Ϣ����    */
#define  SAF_CLEAN_MSG         "SAFRQ2"            /* ����������Ϣ����    */
#define  PRELEN_LEN            8                   /* ǰ�ó��ȵĳ���      */
#define  MAX_REC_NUM           100                 /* ������Ŀ�ĵ���      */
#define  PORT_LEN              5                   /* �˿ںų���          */
#define  MSGTYPE_LEN           6                   /* ת����Ϣ����        */
#define  ERRCODE_LEN           6                   /* �����볤��          */

#define  SAFJNL_RECKEY_LEN     8                   /* ��¼Ψһ��ʶ       */
#define  SAFJNL_MSGTYP_LEN     1                   /* ��Ϣ����           */
#define  SAFJNL_FILNAM_LEN     50                  /* �ļ�����           */
#define  SAFJNL_EPRDAT_LEN     8                   /* ����ʧЧ����       */
#define  SAFJNL_EPRTM_LEN      6                   /* ����ʧЧʱ��       */
#define  SAFJNL_PROFLG_LEN     1                   /* ����ʧЧ�����־ */
#define  SAFJNL_DATA_LEN       3072                /* ����               */
#define  SAFJNL_BORDNUM_LEN    3                   /* �㲥������         */
#define  SAFJNL_PRIID1_LEN     6                   /* Ŀ���������       */
#define  SAFJNL_PRIID2_LEN     7                   /* Ŀ�Ĺ�Ա����       */
#define  SAFJNL_RVSSTS_LEN     1                   /* ״̬               */
#define  SAFJNL_IPADDR_LEN     15                  /* Ŀ�ĵ�ip��ַ����   */
#define  SAFJNL_PORT_LEN       6                   /* Ŀ�ĵ�ͨѶ�˿ڳ��� */
#define  SAFJNL_TXNCOD_LEN     6                   /* �����볤��         */
#define  SAFJNL_OBJSVR_LEN     8                   /* Ŀ�����������     */

//#ifdef	SYBASE
//EXEC     SQL BEGIN DECLARE SECTION; 
//#endif
typedef struct
{
        char    RecKey[ SAFJNL_RECKEY_LEN + 1];    /* ��¼Ψһ��ʶ        */
        char    MsgTyp[ SAFJNL_MSGTYP_LEN + 1];    /* ��Ϣ����1:֪ͨ      */
                                                   /* 2:�㲥 3:�ļ� 4:��ӡ*/
        char    ObjSvr[ SAFJNL_OBJSVR_LEN + 1];    /* Ŀ�������          */
        char    TxnCod[ SAFJNL_TXNCOD_LEN + 1];    /* ������              */
        char    FilNam[ SAFJNL_FILNAM_LEN + 1];    /* �ļ���              */
        char    Data[   SAFJNL_DATA_LEN   + 1];    /* ֪ͨ��㲥����      */
        char    PriId1[ SAFJNL_PRIID1_LEN + 1];    /* Ŀ�Ļ�������        */
        char    PriId2[ SAFJNL_PRIID2_LEN + 1];    /* Ŀ�Ĺ�Ա����        */
        char    EprDat[ SAFJNL_EPRDAT_LEN + 1];    /* ʧЧ����            */
        char    EprTm[  SAFJNL_EPRTM_LEN  + 1];    /* ʧЧʱ��            */
        char    ProFlg[ SAFJNL_PROFLG_LEN + 1];    /* ʧЧ���������־    */
                                                   /* 1���ͼ�� 0��ɾ��   */
        char    IpAdr[ SAFJNL_IPADDR_LEN + 1];    /* Ŀ�ĵ�ip��ַ        */
        char    Port[ SAFJNL_PORT_LEN + 1];    /* Ŀ�ĵ�ͨѶ�˿�       */
        char    RvsSts[ SAFJNL_RVSSTS_LEN + 1];    /* ת��״̬ 0:��Ҫת�� */
                                                   /* 1:����ת�� 2:ʧЧ   */
                                                   /* 9:ת���ɹ�          */
}SAF_SAFJNL_TYPE; 

/*
 * ����-��Ա�ṹ��
 */
typedef struct
{
   char aPriId1[SAFJNL_PRIID1_LEN + 1 ];           /* ��1                 */
   char aPriId2[SAFJNL_PRIID2_LEN + 1 ];           /* ��2                 */
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
 * �洢ת���ǼǺ��� ���ƣ�safTranRegister
 * ����: ETF *          ��ETF���������ڵ�
 *       char *         ��Ŀ���������
 *       char *         ��������
 *       long           ����Чʱ��
 * ����: 0:  �ɹ�
 *       <0: ʧ��
 */
EXTERN int safTranRegister(ETF *Root, char *ObjSvr, char *TxnCod, long EstTim, DBConHandle * DBHandle);

#undef	EXTERN

/* 
 * ���²���ΪӦ�ø����������� 
 * Added by liangwj at 2008-11-12
 */
#ifndef	TABLENAME_MAX_LEN
#define	TABLENAME_MAX_LEN	20
#endif

/* ȫ�ֱ��� */
#ifndef HISAF_EXTERN
#define HISAF_EXTERN
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN char _SafID[TABLENAME_MAX_LEN+1];    	/* �洢ת��ID���ɱ� */
EXTERN char _SafStsJnl[TABLENAME_MAX_LEN+1];    /* �洢ת��״̬��־�� */
EXTERN char _SafDatJnl[TABLENAME_MAX_LEN+1];    /* �洢ת��������־�� */
#undef	EXTERN

#define	SAF_ID_NAME			"ics.plt.safid_tablename"
#define	SAF_STS_JNL_NAME	"ics.plt.safstsjnl_tablename"
#define	SAF_DAT_JNL_NAME	"ics.plt.safdatjnl_tablename"

#endif /* _HISAF_H_ */
