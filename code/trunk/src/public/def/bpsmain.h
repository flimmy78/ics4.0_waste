/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: bpsmain.h 
 Author			: CaiJunJie 
 Version		: V1.0 
 Date			: 2003.05.06 
 Description	: ��ͷ�ļ����� BYPASS ��ϵͳʹ�õ���ͨ��ͳ�������ݽṹ
				 
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================
   01   2003-05-06  �̿���		����
   02   2003-06-27  ̷��		  �޸�
******************************************************************************/


#ifndef _BYPASS_H_
	#define _BYPASS_H_

#include <memory.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/socket.h>
#include <sys/signal.h>

#ifdef	_AIX_SYSTEM
#include <sys/select.h>
#endif

#include <netinet/in.h>
#include <signal.h>
#include "hibase.h"
#include "hilgr.h"
#include "hicpic.h"
#include "hibusmsg.h"
#include "mac3des_api.h"

#define		TIA_HEAD_LEN			171
#define		TOA_HEAD_LEN			114

#define		TCKNO_POS				67
#define		FINFLG_POS				88
#define		TURN_OFF				0
#define		TURN_ON					1

/* �����߳��ǿ��л�����ִ�н��״��� */
#define 	BYPASS_IDEL				0
#define		BYPASS_BUSY				1

/* ����������������л��ǽ��������� */
#define		BYPASS_NORMAL			0
#define		BYPASS_TO_END			1

/* ����ͨ�ŵȴ���־ */
#define		BYPASS_NO_WAIT			0
#define		BYPASS_WAIT				1

/* ���彻��ͨ�Ŵ��������������쳣 */
#define		BYPASS_TXN_NORMAL		'N'
#define		BYPASS_TXN_ABEND		'E'

/* ͨ�ż�ء�ͳ�������ݽṹ��ÿ���߳�ʹ�ö�����ͳ���������ܵó��ۼ����� */
typedef struct
{
	pthread_mutex_t	mutex;		/* ͨ�ŵȴ�������� */
	unsigned char cConvId[8];	/* ��ǰ����ʹ�õ� Conversation ID */
	int		iRetCode;			/* ͨ�Ŵ���ķ����� */
	long	lTotalTxn; 			/* �ܽ��ױ���������ʱ�������ױ��� */
	long	lErrTxn;			/* �����ױ��� */
	long	lTimeOutTxn;		/* ��ʱ���ױ��� */
	long	lExTxn1;			/* ��������ͨ��ʱ��1������ 2 �룩�Ľ��ױ��� */
	long	lExTxn2;			/* ��������ͨ��ʱ��2������ 5 �룩�Ľ��ױ��� */
	long	lExTxn3;			/* ��������ͨ��ʱ��3������ 10 �룩�Ľ��ױ��� */
	float   fCurrTime;			/* ��ǰ����ͨ��ʱ�� */
	double  dTotalTime; 		/* �ܽ���ͨ��ʱ�䣬������ʱ��ͨ���쳣�Ľ��� */
	double  dExTime;	 		/* ͨ��ʱ��ϳ�������ʱ��1���Ľ���ͨ��ʱ���ܺ� */
	double	dTotalLen;			/* ͨ���ܳ��� */
	int		iBusyFlag;			/* ��ǰ�߳��Ƿ����ڴ����ױ�־ 0:���� 1:������ */
	int		iWaitFlag;			/* ��ǰ�߳��Ƿ����ڵȴ�ͨ�ŷ��ر�־ 0:�� 1:�ȴ� */
	struct	timeb  sLastTime;	/* ���߳�ִ����һ�ʽ��׵Ŀ�ʼʱ�� */
	int		iTimeOut;			/* ��ǰ���׵ĳ�ʱʱ�䣬����Ϊ��λ */
	int		iErrorCode;			/* ����ϱʽ��׳���ͨ�ų������ */
	long	lTcpErrTxn;			/* TCP/IP ͨ�ų������ */
} MonitorData;


/* ���� BYPASS ͨ�� TIA ���ṹ */ 
typedef struct
{
	/* ���ݳ��ȴ����� TIA �ṹ�У����ǲ���������������ڴ��� */
	/* char	cDataLen[8];		   �������ݰ��������� */ 
	char	cTxnType[8 + 1];		/* ������� */
	char	cCicsTxn[TP_NAME_LEN + 1];		/* ���������� */
	char	cTxnCode[8 + 1];		/* Ӧ�ý����� */
	char	cTellerNo[8 + 1];		/* ���׹�Ա�� */ 
	char	cTxnTerm[8 + 1];		/* �����ն˺� */
	char	cTimeOut[3 + 1];		/* ���׳�ʱʱ�� */ 
	char	cReserved[19 + 1];		/* �����ֶ� */
	char	cTxnData[16*1024];		/* �������ݰ� */
} TIA;

/* ���� BYPASS ͨ�� TOA ���ṹ */ 
typedef struct
{
	/* ���ݳ��ȴ����� TOA �ṹ�У����ǲ���������������ڴ��� */
	/* char	cDataLen[8];		   �������ݰ��������� */ 
	char	cTxnFlag[1 + 1];		/* ���״����ʶ */
	char	cMsgCode[6 + 1];		/* ������Ϣ�� */
	char	cReserved[19 + 1];		/* �����ֶ� */
	char	cTxnData[16*1024];		/* �������ݰ� */
} TOA;

/* ���彻�׵���Ҫ��Ϣ�ṹ */ 
typedef struct
{
	char	cTTxnCd[8 + 1];		   /* ���״��� */
	char	cTlrId[10 + 1];		   /* ��Ա */
	char	cNodNo[6 + 1];		   /* ���� */
	char	cTxnTm[14 + 1];		   /* ʱ�� */
	char	cFinFlg[1 + 1];		   /* ���� */
	char	cTckNo[12 + 1];		   /* ������־�� */
	char	cHRspCd[6 + 1];		   /* ������ */
} TXN_INF;

#endif
