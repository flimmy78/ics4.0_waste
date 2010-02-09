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

#define	FLD_NAME_LEN	3	/* 消息头名字的长度 */
#define RQST_ID_LEN		20	/* 请求编号的长度 */
#define MSG_TYPE_LEN	6	/* 消息类型的长度 */


/* 消息头结点 */
struct _msg_head_node {
    char   fld_name[FLD_NAME_LEN+1];  /* 域名字 */
    short  fld_id;                    /* 域实例号 */
    short  fld_len;                   /* 域值长度 */
    char * fld_val;                   /* 域值内容 */
    struct _msg_head_node * next;     /* 指向下一接点的指针 */
};
typedef struct _msg_head_node MsgHeadNode;

/* 消息 */
struct _message {
    char   request_id[RQST_ID_LEN+1];  /* 请求编号 */
    char   msg_type[MSG_TYPE_LEN+1];   /* 消息类型 */
    short  msg_priority;               /* 消息优先级别 */
    short  msg_splited;                /* 消息拆分标志 */
    long   msg_id;                     /* 消息ID  */
    long   msg_size;                   /* 消息大小 */
    MsgHeadNode * msg_head;            /* 消息头 */
    char * msg_text;                   /* 消息文本 */
};
typedef struct _message Message;

/* 定义全局变量 */
#ifdef	_ICSCLI_EXTERN_
#define	EXTERN	extern
#else
#define	EXTERN
#endif

EXTERN	char	gaIcsIP[15+1];
EXTERN	int		giIcsPort;
#undef	EXTERN

/* 函数声明 */
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
#define SPLITED                1        /* 拆分消息 */
#endif
#ifndef UN_SPLITED
#define UN_SPLITED        0        /* 没拆分消息 */
#endif

#ifndef END_FLAG
#define END_FLAG        0x7ffffffe        /* 结束标志 */
#endif

#ifndef ERR_FLAG
#define ERR_FLAG        0x7fffffff        /* 错误标志 */
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
