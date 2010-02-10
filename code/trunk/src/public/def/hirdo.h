/******************************************************************************


				Copyright (C),1998-2008,Hisuntech Co.,Ltd.

 File name		: hirdo.h
 Author			: WangXiaoDong
 Version		: 1.0
 Date			: 2003-04-16
 Description	: �����ط��������ͷ�ļ���     
 Others			: ��
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2003-04-16	WXD         ����
  002	2008-11-12	LiangWJ     Ӧ�ø������
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
 * ���ݿ�������
#ifdef	SYBASE
EXEC SQL BEGIN DECLARE SECTION; 
#endif
 */

/*
 * �����ط���ˮ��ṹ
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
 * �ط���ˮ��
 */

typedef struct 
{
        char    LogNo[RDO_RDOJNL_LOGNO_LEN + 1];        /*�ط���ˮ��  */
        char    TxnCod[RDO_RDOJNL_TXNCOD_LEN + 1];      /*ԭ������    */
        char    OprClk[RDO_RDOJNL_OPRCLK_LEN + 1];      /*�ط�����ʱ�� */
        char    Itv[RDO_RDOJNL_ITV_LEN + 1];            /*��ѯ���ʱ�� */
        char    TmOut[RDO_RDOJNL_TMOUT_LEN + 1];        /*��ʱʱ��     */
        char    FalTms[RDO_RDOJNL_FALTMS_LEN + 1];      /*�ط�ʧ�ܴ��� */
        char    MaxTms[RDO_RDOJNL_MAXTMS_LEN + 1];      /*����ط����� */
        char    RvsSts[RDO_RDOJNL_RVSSTS_LEN + 1];      /*�ط�״̬     */
        char    ObjSvr[RDO_RDOJNL_OBJSVR_LEN + 1];      /* Ŀ�������  */
        char    ActDat[RDO_RDOJNL_ACTDAT_LEN + 1];      /*�������     */
}RDO_RDOJNL_TYPE; 

/*
 * deleted by kixiong at 2008-10-30 13:18
 * ���ݿ�������
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
 * �ط��ǼǺ���
 * �������ṹ����
 * ����: 0:�ɹ� 
 *       1:��ˮ��,ԭ������ͷ������룬��ѯ���ʱ�䡢����ط���������ʱʱ��Ϊ��Ŀ *         ���������,����������п�ֵ
 *       2:��ѯ���ʱ�䡢����ط���������ʱʱ�����зǷ�����
 *    ����:SQL�Ĵ�����
  
 */

EXTERN int rdoTranRegister(RDO_RDOJNL_TYPE * , DBConHandle *);

/*
 * �ط��޸�״̬����
 * ����:��ˮ��,������(����Ϊ��),״̬(1:��Ҫ�ط� 9:�ط��ɹ�)
 * ����: 0:�ɹ� 
 *       1:��ˮ�Ż�״̬�ǿ�ֵ
 *       2:״̬��������
 *    ����:SQL�Ĵ�����
 */

EXTERN int rdoTranUpdate(char * ,char *,char * ,DBConHandle *);

/*
 * ȡ�ط�״̬���������ƣ�rdoGetStatus
 * ��������ˮ��, �ط�״̬
 * ����: SQLCODE
 */
EXTERN int rdoGetstatus(char *, char *, DBConHandle *);

/*
 * �ط�ȡ�����������ƣ�rdoCancel
 * ��������ˮ��, �ύ��־
 * ����: 0:�ɹ�
 *    ����:SQL�Ĵ�����
 */
EXTERN int rdoCancel(char *, int, DBConHandle *);

#undef	EXTERN

/*
 * deleted by kixiong at 2008-10-30 13:21
#endif	* SYBASE *
*/

/* 
 * ���²���ΪӦ�ø����������� 
 * Added by liangwj at 2008-11-12
 */
#ifndef	TABLENAME_MAX_LEN
#define	TABLENAME_MAX_LEN	20
#endif

/* ȫ�ֱ��� */
#ifndef HIRDO_EXTERN
#define HIRDO_EXTERN
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN char _RdoJnl[TABLENAME_MAX_LEN+1];    /* �ط���־���� */
#undef	EXTERN

#define	RDO_JNL_NAME	"ics.plt.rdojnl_tablename"

#endif /* _HIRDO_H_ */
