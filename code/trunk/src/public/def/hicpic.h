/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: appc.h 
 Author			: CaiJunJie 
 Version		: V1.0 
 Date			: 2003.05.09 
 Description	: ��ͷ�ļ�����ǰ��������ͨ�ź���ԭ�ͼ�������Ϣ������
				 
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================
   01   2003-05-09  �̿���        ����
   02   2003-06-27  ̷��          �޸�
******************************************************************************/


#ifndef _APPC_H_
	#define _APPC_H_

#include <pthread.h>
#include <memory.h>

#ifdef	_AIX_SYSTEM_
#include <sna.h>
#endif

#ifdef	_HP_SYSTEM_
#include <appc_c.h>
#include <cmc.h>
#endif

#define		TP_NAME_LEN			4

#define		APPC_TIME_OUT		999

/* ���� APPC ͨ���Ƿ���Ҫ confirm ��־ */
#define		APPC_NOT_CONFIRM	0
#define		APPC_NEED_CONFIRM	1


/* APPC ͨ�Žӿں��� */
int	 appcComm(unsigned char *pchDestName, unsigned char *pcTpName, 
			  unsigned char *pcSendData, int iSendLen,
			  unsigned char *pcRecvBuf, int iBufSize, 
			  int *piRecvLen, int *piErrFlag);
int	 appcComm2(pthread_mutex_t *pMutex, int *piRetCode, 
				unsigned char *pcConvId,
				unsigned char *pchDestName, unsigned char *pcTpName, 
				unsigned char *pcSendData, int iSendLen,
				unsigned char *pcRecvBuf, int iBufSize, int *piRecvLen);

int  appcInit(unsigned char *pcDestName, unsigned char *pcConvId,
			  unsigned char *pcTpName );
int  appcAllocate(unsigned char *pcConvId);
int  appcSend(unsigned char *pcConvId, unsigned char *pcSendData,
				 int iSendLen );
int  appcRecv(unsigned char *pcConvId, unsigned char *pcRecvBuf,
				 int iBufSize, int *piRecvLen, int *piConfirmFlag );
int  appcRecv2(pthread_mutex_t *mutex, int *piRetCode,
				unsigned char *pcConvId,
				unsigned char *pcRecvBuf, int iBufSize,
				int *piRecvLen, int *piConfirmFlag );
int	 appcConfirm(unsigned char *pcConvId);
int  appcCancel(unsigned char *pcConvId );
int  appcEnd(unsigned char *pcConvId );
int	 appcWait(unsigned char *pcConvId, int *piRetCode );


#endif
