/*
 * History: Date        Position        Author                Action
 * ----------------------------------------------------------------------------
 *          2004-02-13  ShangHai        LiangWenJian          Create
 ******************************************************************************/

#ifndef _HI_ICSCLI_H_
#define _HI_ICSCLI_H_

#include	<stdio.h>
#include	<stdlib.h>
#include	<errno.h>

#define	FLD_NAME_LEN	3	/* ��Ϣͷ���ֵĳ��� */
#define RQST_ID_LEN		20	/* �����ŵĳ��� */
#define MSG_TYPE_LEN	6	/* ��Ϣ���͵ĳ��� */


/* ��Ϣͷ��� */
struct _msg_head_node {
    char   fld_name[FLD_NAME_LEN+1];  /* ������ */
    short  fld_id;                    /* ��ʵ���� */
    short  fld_len;                   /* ��ֵ���� */
    char * fld_val;                   /* ��ֵ���� */
    struct _msg_head_node * next;     /* ָ����һ�ӵ��ָ�� */
};
typedef struct _msg_head_node MsgHeadNode;

/* ��Ϣ */
struct _message {
    char   request_id[RQST_ID_LEN+1];  /* ������ */
    char   msg_type[MSG_TYPE_LEN+1];   /* ��Ϣ���� */
    short  msg_priority;               /* ��Ϣ���ȼ��� */
    short  msg_splited;                /* ��Ϣ��ֱ�־ */
    long   msg_id;                     /* ��ϢID  */
    long   msg_size;                   /* ��Ϣ��С */
    MsgHeadNode * msg_head;            /* ��Ϣͷ */
    char * msg_text;                   /* ��Ϣ�ı� */
};
typedef struct _message Message;

/* ����ȫ�ֱ��� */
#ifdef	_ICSCLI_EXTERN_
#define	EXTERN	extern
#else
#define	EXTERN
#endif

EXTERN	char	gaIcsIP[15+1];
EXTERN	int		giIcsPort;
#undef	EXTERN

/* �������� */
#ifdef	_LIB_ICSCLI_	
#define	EXTERN
#else
#define	EXTERN	extern
#endif

EXTERN int usfInit();
EXTERN int usfSetEnv(char *, int);
EXTERN void usfClose();
EXTERN int usfGetMsgHeadValue(Message *, char *, char *);
EXTERN int usfAddMsgHeadValue(Message *, char *, char *, short);
EXTERN int usfSetMsgHeadValue(Message *, char *, char *, short);
EXTERN void usfDelMsgHeadValue(Message *, char *);
EXTERN int usfSetMsgData(Message *, char *, long);
EXTERN void usfFreeMsgData(Message *);
EXTERN void usfDestroyMsg(Message *);
EXTERN Message * usfDupMsgFrame(Message *);
EXTERN Message * usfCreateMsg(char *);
EXTERN Message * usfCreateMsgByString(char *, long);
EXTERN int usfMsgToString(Message *, char **, long *);
EXTERN Message * usfCreateMsgByHeadString(char *, long);
EXTERN int usfMsgToHeadString(Message *, char **, long *);
EXTERN int usfSendRequest(Message *);
EXTERN int usfSendRequestToLeft(Message *);
EXTERN int usfSendRequestToRight(Message *);
EXTERN int usfSendRequestAndWaitResponse(Message *, long, Message **);
EXTERN int usfNotify(Message *);
EXTERN int usfNotifyToLeft(Message *);
EXTERN int usfNotifyToRight(Message *);
EXTERN int usfSetNotify(Message *);

#undef	EXTERN

#ifndef SPLITED
#define SPLITED                1        /* �����Ϣ */
#endif
#ifndef UN_SPLITED
#define UN_SPLITED        0        /* û�����Ϣ */
#endif

#ifndef END_FLAG
#define END_FLAG        0x7ffffffe        /* ������־ */
#endif

#ifndef ERR_FLAG
#define ERR_FLAG        0x7fffffff        /* �����־ */
#endif

#define usfSetMsgType(msg, type) {\
 strncpy(msg->msg_type, type, MSG_TYPE_LEN); }
#define usfSetMsgID(msg, id) {\
 msg->msg_id = id; }
#define usfSetMsgSplited(msg, sp_flg) {\
 msg->msg_splited = sp_flg; }
#define usfSetMsgPriority(msg, priority) {\
 msg->msg_priority = priority; }
#define usfSetMsgEndFlag(msg, end_flag) {\
 msg->msg_id = end_flag; }
#define usfSetMsgErrFlag(msg, err_flag) {\
 msg->msg_id = err_flag; }

#endif /* _HI_ICSCLI_H_ */
