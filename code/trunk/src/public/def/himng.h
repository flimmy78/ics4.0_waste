/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : himng.h
 Author         : ̷��
 Version        : V 1.0
 Date           : 2003-04-08
 Description    : ������ϵͳ����ͷ�ļ�
 Others         : 
 History        : ���±�

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
   01   2003-04-08  ̷��        ����
******************************************************************************/

#ifndef _HIMNG_H_
#define _HIMNG_H_

#ifndef _HI_VARARGS
#define _HI_VARARGS
#endif

#include "hiserver.h"
#include "hidll.h"
#include "hiafp.h"

#define ROOTNOD   "root" /* ���ĸ��ڵ� */
#define RETCODNOD "RspCod"	/* ������ڵ��� */
#define RETMSGNOD "RspMsg"	/* ������Ϣ�ڵ��� */
#define SUCRETCOD "000000"	/* ���سɹ��ڵ�ֵ */
#define CONERRCOD "100501"  /* ͨѶ���󷵻��� */
#define CANTDOERR "211405"  /* ���ܴ������� */
#define MSGTYPHED "SCH" /* ��Ϣ������Ϣͷ */
#define RPMSGTYP  "rp" /* ��Ӧ��Ϣ���� */
#define RQMSGTYP  "rq" /* ������Ϣ���� */
#define RETCODHED "SSC" /* ��������Ϣͷ */
#define RETMSGHED "SEM" /* ������Ϣͷ */
#define AIMSVRHED "SDT" /* Ŀ�������ͷ */
#define CMDCODHED "CMD" /* �������ͷ */
#define FNTCODHED "STC" /* ǰ�ý�����ͷ */
#define INIPADDR  "SIP" /* IP��ַͷ */
#define IPADDRHED "OIP" /* IP��ַͷ */
#define PORTHED   "OPT" /* �˿�ͷ */
#define MONMSGTYP "SYSMON"
#define SYSSTSSVR "S.STSSVR" /* ״̬���������� */
#define SYSMNGSVR "S.MNGSVR" /* ǰ�ù���������� */
#define CCAMNGSVR "CMNGMGP1" /* ǰ�ù��������������� */
#define PPPMNGSVR "P.MNGSVR" /* P�˹���������� */
#define SYSMONSVR "S.MONSVR" /* ǰ�ü�ط������� */
#define CPPMONSVR "CMNGMNP1" /* P�˼�ؽ������������ */
#define CCPMONSVR "CMNGMNP2" /* P�˼�ؽ������������ */
#define PPPMONSVR "P.MONSVR" /* P�˼�ط������� */
#define FNTTABNOD "FrontTab" /* ǰ�÷������ñ�ڵ��� */
#define SVRLSTROT "FrontTab" /* �����������ñ���ڵ� */
#define SVRLSTGRP "Group" /* �����������ñ���ڵ� */
#define SVRGRPNAM "name" /* �����������ñ���ڵ��������� */
#define SVRGRPSVR "Server" /* �����������ñ���ڵ����ڵ� */
#define SVRSVRNAM "name" /* �����������ñ���ڵ����ڵ��������� */
#define SVRSVRCFG "config_file" /* �����������ñ���ڵ����ڵ������ļ����� */
#define SVRCFGROT "Region" /* ���������ļ����ڵ� */
#define SVRCFGSVR "Server" /* ���������ļ��������ýڵ� */
#define SVRCFGNAM "name" /* ���������ļ��������ýڵ��������� */
#define SVRCFGTRC "trace" /* ������־���ر�־ */
#define SVRCFGTYP "type" /* �������ͱ�־ */
#define DPOOLROOT "DBConnectionPool" /* ���ݿ����ӳ����õĸ��ڵ� */
#define DPOOLUSER "UserName" /* ���ݿ����ӳ��û������� */
#define DPOOLPWD  "Password" /* ���ݿ����ӳ��������� */
#define DPOOLSIZE "PoolSize" /* ���ݿ����ӳش�С���� */
#define CLTSVRTYP "CCA" /* ��������������� */
#define SVRSVRTYP "SCA" /* �ӳ������������� */
#define BTASVRTYP "BTA" /* �������ط����������� */
#define OTASVRTYP "OTA" /* ҵ�����ط����������� */
#define TPOOLROOT "ThreadPool" /* �������ӳ����õĸ��ڵ� */
#define TPOOLANUM "MaxWorkerThreads" /* �������ӳ���������� */
#define TPOOLINUM "MinWorkerThreads" /* �������ӳ���С�������� */
#define TPOOLPTIM "PollingTime" /* �������ӳؼ��ʱ���� */
#define TPOOLDTUN "DynamicTuning" /* �������ӳض�̬������־ */
#define TPOOLHLEV "HighLoadLevel" /* �������ӳظ߸���ˮλ */
#define TPOOLHPOT "HighLoadTunePoint" /* �������ӳظ߸��ص����� */
#define TPOOLHSTP "HighLoadTuneStep" /* �������ӳظ߸��ص������� */
#define TPOOLLLEV "LowLoadLevel" /* �������ӳص͸���ˮλ */
#define TPOOLLPOT "LowLoadTunePoint" /* �������ӳص͸��ص����� */
#define TPOOLLSTP "LowLoadTuneStep" /* �������ӳص͸��ص������� */
#define QPAIRROOT "QueuePair" /* �������ø��ڵ� */
#define QPAIRNAME "name" /* �������� */
#define QPAIRLEN  "QueueLength" /* ���и��� */
#define CRCINTVAL "Inteval" /* ��������ѭʱ���� */
#define CRCHODDAY "HoldDays" /* �����ı������� */
#define CRCCLNTIM "cleanHour" /* ���������ʱ�� */
#define CRCMAXFLX "MaxFlux" /* ������������� */
#define RDRINTVAL "Inteval" /* �ط�����ѭʱ���� */
#define RDRHODDAY "HoldDays" /* �ط��ı������� */
#define RDRCLNTIM "cleanHour" /* �ط������ʱ�� */
#define RDRMAXFLX "MaxFlux" /* �ط���������� */
#define SCHINTVAL "itv" /* ��ʱ��������ѭʱ���� */
#define SCHCONFIL "confile" /* ��ʱ�����������ļ� */
#define SCHMAXFLX "MaxRec" /* ��ʱ������������� */
#define DLLCTLROT "DllPriDataCtrl" /* ��̬�����ýڵ��� */
#define DLLCTLPAR "Para" /* ��̬��������ýڵ��� */
#define DLLPARNAM "name" /* ��̬��������ýڵ������� */
#define CTLCFGAPP "Application" /* Ӧ�����ø��ڵ� */
#define CTLAPPTRN "Transaction" /* �������ø��ڵ� */
#define CTLAPPNAM "name" /* Ӧ������������ */
#define CTLTRNCOD "code" /* �������������� */

#define MNG_FILNAM_LEN  64
#define MAX_LINE_LEN   256
#define MAX_WORD_LEN   32
#define MAX_LEN        4096
#define FIELD_NAME_LEN 32
#define TRN_CODE_LEN   6
#define SVR_NAME_LEN   8
#define MAX_CODE_NUM   200
#define GROUP_ID_LEN   3
#define APPID_LEN      3
#define APPNAM_LEN     128
/*
typedef struct _prvg_node {						// Ȩ����Ϣ�ڵ�
	char group_id[GROUP_ID_LEN + 1];			// ��ɫID 
	int code_num;								// �������� 
	char code[MAX_CODE_NUM][TRN_CODE_LEN + 1];	// ���������� 
    struct _prvg_node *next;					// ��һ���ڵ�
} PrvgNode;
*/
/*���Ӧ��ID��Ӧ�����ƵĽṹ*/
typedef struct _appinfo
{
	char	AppID[APPID_LEN+1];			/*Ӧ��ID*/
	char	AppNam[APPNAM_LEN+1];		/*Ӧ������*/
	struct  _appinfo *next;				/*ָ����һ���ڵ��ָ��*/

} AppInfo;

#ifdef	_MNG_EXTERN_
extern	XmlNode * gCfgRoot;
#else
XmlNode * gCfgRoot = NULL;
#endif

#ifdef	_HIMNG_LIB_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

/*
EXTERN XmlNode * gCfgRoot = NULL;

EXTERN PrvgNode *createPrvgNode();				// ����Ȩ����Ϣ�ڵ�
EXTERN void destroyPrvgNode(PrvgNode *);		// ����Ȩ����Ϣ�ڵ�����
EXTERN int printPrvgNode(PrvgNode *, char *);	// ��ʾȨ����Ϣ�ڵ����� 
EXTERN int getPrvgInfo(PrvgNode **);			// ���Ȩ����Ϣ 
EXTERN int makePrvgCheck(PrvgNode *, char *, char *);	//Ȩ��У��
*/
EXTERN int setDllSelf(void *);
EXTERN int setDllGlobal(void *);				/* ������һ����̬���ȫ�ֱ��� */

/* ȡ�������б��ļ��� */
EXTERN char *getServerTabFile();

/* �������״�����ָ�� */
//EXTERN void *getCodeFunc(XDllReg *, XmlNode *, char **, PrvgNode *);
EXTERN void *getCodeFunc(XDllReg *, XmlNode *, char **);
/* �����������һ��������Ϣ */
EXTERN Message * createCmdMsg(Message *, char *, char *, char *, char *);
/* ������Ϣ���ҽ��շ��� */
EXTERN Message * sendCmdAndWaitRet(Message *, char *, char *, char *, char *);
/* ������Ϣ���ǲ��ȴ����� */
EXTERN int sendCmdAndNoWait(Message *, char *, char *, char *, char *);
/* �жϷ��ؽ�� */
EXTERN int judgeReturn(Message *, Message *);
/* ת��������Ϣ */
EXTERN int convertRetToMsg(Message *, Message *);
/* ����һ�㽻�ף�ͬ�������첽 */
EXTERN int doSynNormalTran(Message *, char *, char *, char *, char *);
EXTERN int doAsynNormalTran(Message *, char *, char *, char *, char *);
/* ȡ��������һ�㽻�״���һ������ */
EXTERN int doServerTran(Message *, XmlNode *, char *, char *, char *);
/* ȡ��������һ�㽻�״���������� */
EXTERN int doServerControl(Message *, XmlNode *, char *, char *);
/* �ж��Ƿ�Ϊϵͳ���� */
EXTERN int isSystemServer(char *);
/* ȡ����������ת��Ϊ��д */
EXTERN int getServerName(XmlNode *, char *);
/* ��÷��������ļ�·�� */
EXTERN int getServerConfigFile(char *, char *, char *);
/* ��÷������ýڵ� */
EXTERN XmlNode * getServerConfigNode(XmlDocument *, char *);

EXTERN XmlNode *convertRetToXml(Message *, Message *);
EXTERN int xmlCreateRoot(XmlNode **);					/* ����һ�����ڵ� */
EXTERN int createXmlReturn(XmlNode **, char *, char *);	/* ����һ��XML���ؽڵ� */
/* ����һ�����󷵻���Ϣ */
EXTERN int createErrReturn(char *, int, Message *, char *, char *, char *, ...);
EXTERN int MessageReturn(Message *, XmlNode *);			/* ת������XML�ڵ�Ϊ������Ϣ */
#undef	EXTERN

#endif	/* _HIMNG_H_ */
