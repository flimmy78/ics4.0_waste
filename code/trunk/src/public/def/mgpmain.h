/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : mgpmain.h
 Author         : ̷��
 Version        : V 1.0
 Date           : 2003-04-12
 Description    : �����ط������Ϲ���������ͷ�ļ�
 Others         : 
 History        : ���±�

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
   01   2003-04-12  ̷��        ����
******************************************************************************/

#ifndef _MGPMAIN_H_
#define _MGPMAIN_H_

#include "himng.h"

#define PPPAIMROT "SomamAim"	/* P�˹�����������ļ����ڵ� */
#define PPPMNGROT "SomamMan"	/* P�˹�����������ļ����ڵ� */
#define LOGINCODE "090000"		/* ��½������ */
#define GETIPCODE "090912"		/* ȡ������IP������ */


#define VALUE_LEN      32
#define MEAN_LEN       128
#define GROUP_NAME_LEN 32
#define USER_ID_LEN    6
#define USER_NAME_LEN  32
#define USER_SEX_LEN   1
#define USER_PWD_LEN   10
#define TEXT_LEN	  1024	 
#define BUSID_LEN      3 
#define BUSNAM_LEN     60
#define IP_LEN         15
#define PORT_LEN       6
#define TIMEOUT_LEN       6

typedef struct _aim_node {						/* ·�ɽڵ� */
	char * aim_id;								/* Ŀ������Ĵ��� */
	char * aim_ip;								/* Ŀ�������IP */
	long aim_port;								/* Ŀ������Ķ˿� */
	char * ftp_user;							/* ���ں�̨FTPȡ��־�ļ����û���*/
	char * password;							/* ���ں�̨FTPȡ��־�ļ����û�����*/
    struct _aim_node * next;					/* ��һ���ڵ� */
} AimNode;

/*
typedef struct _timeout_node {						// ���׳�ʱʱ�����ýڵ�
	char * code;								// ������
	char * timeout;								// ��ʱʱ��
    struct _timeout_node * next;				// ��һ���ڵ�
} TimeOutNode;
*/

extern AimNode * createAimNode();				/* ����·�ɽڵ� */
extern void destroyAimNode(AimNode *);			/* ����·�ɽڵ����� */
extern int printAimNode(AimNode *, char *);		/* ��ʾ·�ɽڵ� */
extern int setAimInfo(XmlNode *);				/* ��ȡ·����Ϣ */
/* ���Ŀ�������IP��Port */
extern int getAimInfo(char * aim, char *ip, char *port, char *username, char *password);	
extern int doLogin(Message *, XmlNode *);		/* �����½���� */
extern int writeLog(Message *, XmlNode *);		/* ��¼��־ */

#endif	/* _MGPMAIN_H_ */
