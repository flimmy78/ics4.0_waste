/********************************************************************
Copyright (C),1998-2003,Hisuntech Co.,Ltd.
  File name:      // hicrc.h
  Author:         // Wangxd
  Version:        // 1.0
  Date:           // 20030416
  Description:    // ���ǳ�����������õ���Ψһ��ͷ�ļ�
                  // ��Ҫ���������ˮ��ṹ
  Others:         // �������ݵ�˵��
  Function List:  // ��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��
    1. ....
  History:        // �޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ�
                  // �޸��߼��޸����ݼ���  
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
 * ���������ˮ��ṹ
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
 * ��ˮ���¼״̬
 */
#define CRC_ORIGIN             '0'
#define CRC_NEED_CORRECT       '1'
#define CRC_GOING_CORRECT      '2'
#define CRC_BEYOND_CORRECT     '4'
#define CRC_YESTERDAY_REC      '8'
#define CRC_SUCCESSFUL         '9'

/*
 * ������ˮ��
 */
typedef struct 
{
        char    LogNo[CRC_CRCTJNL_LOGNO_LEN + 1];        /*������ˮ��  */
        char    TxnCod[CRC_CRCTJNL_TXNCOD_LEN + 1];      /*ԭ������    */
        char    RTxnCd[CRC_CRCTJNL_RTXNCD_LEN + 1];      /*����������  */
        char    OprClk[CRC_CRCTJNL_OPRCLK_LEN + 1];      /*��������ʱ�� */
        char    Itv[CRC_CRCTJNL_ITV_LEN + 1];            /*��ѯ���ʱ�� */
        char    TmOut[CRC_CRCTJNL_TMOUT_LEN + 1];        /*��ʱʱ��     */
        char    FalTms[CRC_CRCTJNL_FALTMS_LEN + 1];      /*����ʧ�ܴ��� */
        char    MaxTms[CRC_CRCTJNL_MAXTMS_LEN + 1];      /*���������� */
        char    RvsSts[CRC_CRCTJNL_RVSSTS_LEN + 1];      /*����״̬     */
        char    ObjSvr[CRC_CRCTJNL_OBJSVR_LEN + 1];      /* Ŀ�������  */
        char    ActDat[CRC_CRCTJNL_ACTDAT_LEN + 1];      /*�������     */
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
 * �����ǼǺ��� ���ƣ�crcTranRegister
 * ����: CRC_CRCTJNL_TYPE * crctJnl �ṹ����
 * ����: 0:�ɹ�
 *       1:��ˮ��,ԭ������ͷ������룬��ѯ���ʱ�䡢����ط���������ʱʱ��Ϊ��Ŀ
 *         ���������,����������п�ֵ
 *       2:��ѯ���ʱ�䡢����ط���������ʱʱ�����зǷ�����
 *    ����:SQL�Ĵ�����

 */
EXTERN int crcTranRegister(CRC_CRCTJNL_TYPE * , DBConHandle *);

/*
 * �����޸ĺ��������ƣ�crcTranUpdate
 * ��������ˮ�ţ�ԭ������(����Ϊ��)��״̬(1����Ҫ���� 9:���������ɹ�)
 * ����: 0:�ɹ�
 *       1:��ˮ�Ż�״̬�ǿ�ֵ
 *       2:״̬��������
 *    ����:SQL�Ĵ�����
 */
EXTERN int crcTranUpdate(char *,char *,char *, DBConHandle *);

/*
 * ȡ����״̬���������ƣ�crcGetStatus
 * ��������ˮ��, ����״̬
 * ����: SQLCODE
 */
EXTERN int crcGetstatus(char *, char *, DBConHandle *);

/*
 * ����ȡ�����������ƣ�crcCancel
 * ��������ˮ��, �ύ��־
 * ����: 0:�ɹ�
 *    ����:SQL�Ĵ�����
 */
EXTERN int crcCancel(char *, int, DBConHandle *);

#undef	EXTERN

//#endif /* SYBASE */

/* 
 * ���²���ΪӦ�ø����������� 
 * Added by liangwj at 2008-11-12
 */
#ifndef	TABLENAME_MAX_LEN
#define	TABLENAME_MAX_LEN	20
#endif

/* ȫ�ֱ��� */
#ifndef HICRCT_EXTERN
#define HICRCT_EXTERN
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN char _CrcJnl[TABLENAME_MAX_LEN+1];    /* ������־���� */
#undef	EXTERN

#define	CRC_JNL_NAME	"ics.plt.crcjnl_tablename"


#endif /* _HICRC_H_ */
