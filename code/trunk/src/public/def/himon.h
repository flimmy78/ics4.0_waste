#ifndef _HIMON_H_
#define _HIMON_H_

#define _HI_VARARGS
#include "hiserver.h"

#define MON_MSG_TYPE	"SYSMON"
#define MONSVR			"S.MONSVR"

#define MAX_HEAD_LEN  256
#define MAX_LEN       8096
#define FILE_NAME_LEN 64
#define DATE_TIME_LEN 32
#define TTXNCD_LEN    30

#ifdef	_HIMON_LIB_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

EXTERN int monTranStatus(int , char *, char *, int );
EXTERN int monServerStatus(int , char *, int );
EXTERN int monConnStatus(int , char *, int );
EXTERN int monSpecailInfo(int , char *, int );
EXTERN int monBypassStatus(int, char *, int); /* ByPass ������ */
EXTERN int monByPassInfo(int, char *, int);   /* ByPass ������ϸ��Ϣ */

/* monTranStatus: ���׼����Ϣ���� */
/* ����˵��: int iOnOff:    ��־���� (1,��¼; ����,����¼);
             char *cTxnCod: ���׼����Ϣ�Ľ�����
			 char *cTxnDat: ���׼����Ϣ������
			 int iDatLen:   ���׼����Ϣ�ĳ���
   ����ֵ:   0,��ʾ�ɹ�; -1,��ʾʧ��;	*/

/* monServerStatus: ��������Ϣ���� */
/* ����˵��: int iOnOff:    ��־���� (1,��¼; ����,����¼);
			 char *cTxnDat: ��������Ϣ������
			 int iDatLen:   ��������Ϣ�ĳ���
   ����ֵ:   0,��ʾ�ɹ�; -1,��ʾʧ��;	*/

/* monConnStatus: ͨѶ�����Ϣ���� */
/* ����˵��: int iOnOff:    ��־���� (1,��¼; ����,����¼);
			 char *cTxnDat: ͨѶ�����Ϣ������
			 int iDatLen:   ͨѶ�����Ϣ�ĳ���
   ����ֵ:   0,��ʾ�ɹ�; -1,��ʾʧ��;	*/

/* monSpecialInfo: ������Ϣ���� */
/* ����˵��: int iOnOff:    ��־���� (1,��¼; ����,����¼);
			 char *cTxnDat: ������Ϣ������
			 int iDatLen:   ������Ϣ�ĳ���
   ����ֵ:   0,��ʾ�ɹ�; -1,��ʾʧ��;	*/

#endif /* _HIMON_H_ */
