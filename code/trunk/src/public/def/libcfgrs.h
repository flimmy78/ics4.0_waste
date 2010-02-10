#ifndef _CFG_RECV_SEND_
#define _CFG_RECV_SEND_

#include "ecnmain.h"

//ȱʡ��ʱʱ��
#define DEFAULT_TIMEOUT 120

//��־λ��󳤶�
#define FLAG_MAX_LEN  16

#define LONG_CONN     1
#define SHORT_CONN    0
#define MAX_CONN      50
#define MAX_DAT_LEN   16*1024

//ֵ����
#define CHAR          1
#define	INT			      2
#define ASCII         3
#define STRING        4
#define SHORT         5

//�����ļ��ڵ��
#define Node_ConnTyp					"ConnTyp"
#define Node_MaxConn					"MaxConn"
#define Node_IpLstFil					"IpLstFil"
#define Node_TmOut						"TmOut"
#define Node_MsgHead					"MsgHead"
#define Node_Request					"Receive"
#define Node_MsgHeadLen 			    "MsgHeadLen"
#define Node_MsgBodyLen					"MsgBodyLen"
#define Node_HaveNextMsg				"HaveNextMsg"
#define Node_Response					"Send"
#define Node_DestPort					"DestPort"
#define Node_DestIp                     "DestIp"
#define Node_BindPort                   "BindPort"
#define ATTR_Length						"length"
#define ATTR_SAVE                       "save"
#define ATTR_StartPos					"startpos"
#define ATTR_ValueType					"value_type"
#define ATTR_Value						"value"
#define ATTR_IncludeHeadLen             "is_include_headlen"
#define ATTR_IncludeBodyLenLen			"is_include_bodylenlen"
#define ATTR_TrueValue					"true_value"
#define ATTR_FalseValue					"false_value"
#define ATTR_EndValue					"end_value"
#define ATTR_EndValueLen				"end_value_len"
#define ATTR_EndValueType				"end_value_Type"

typedef struct _connect_param_
{
    int			haveMsgHead;              	 			/* �Ƿ��ǰ�ó��� 0:Y 1:N    */
    int         isSaveMsgHead;                          /* �Ƿ񱣴��ͷ*/
    int			haveNextMsg;				 			/* �Ƿ�����һ���� */
    int			haveResponseMsgHead;		 			/* ������Ϣ�Ƿ��ǰ�ó���*/

    int			msgHeadLen;                  			/* ����ͷ����				  */
    int			msgBodyLen;								/* �����峤��*/
    int			msgBodyLenStartPos;			 			/* ���峤���ڱ���ͷ����ʼλ��*/
    int			msgBodyLenLength;			 			/* ���峤�ȵĳ���			  */
    //added by kixiong on 2006-06-11 at shanghai
    int			isInclHeadLen;							/* ���峤�ȵĳ����Ƿ������ͷ����*/
    //added end
    //added by kixiong on 2006-06-26 at shanghai
    int			isInclBodyLenLen;						/* ���峤�ȵĳ����Ƿ������ͷ����*/
    //added end
    int			msgBodyLenLengthValueType;	 			/* ���峤�ȵĳ��ȵ���������  */
    int			haveNextMsgFlgStartPos;		 			/* �Ƿ������һ���ְ���־�ڱ���ͷ����ʼλ��*/
    int			haveNextMsgFlgLen;		 	 			/* �Ƿ������һ���ְ���־�ĳ���*/
    char		true_value[FLAG_MAX_LEN+1];	 			/* ������һ���ְ��ı�־*/
    char		false_value[FLAG_MAX_LEN+1]; 			/* ��������һ���ְ��ı�־*/
    int			flag_value_type;						/* ��־ֵ������(CHAR��INT��ASCII), Ĭ��ΪCHAR��*/
    char		endValue[FLAG_MAX_LEN];		 			/* ���ս�����־ֵ*/
    int			endValueLen;				 			/* ���ս�����־ֵ�ĳ���*/
    int			endValueType;				 			/* ���ս�����־ֵ����������*/
    int			rpMsgHeadLen;				 			/* ��Ӧ���Ƿ���Ҫǰ�ó���*/
    
    int         haveMsgTail;                            /*�Ƿ��а�β*/
    int         isSaveMsgTail;                          /*�Ƿ񱣴��β*/
    int			msgTailLen;                             /*��β����*/

    int         syncConType;                 			    /* �������� 0:������ 1:������ */
    char        ipConFile[FILENAME_LEN + 1]; 			    /* ip�����ļ�������           */
    char        msgType[MSGLEN +1 ];         			    /* ��Ϣ����                   */
    int         port;                        			    /* ��������ʱ�����˿ں�       */
    int         thread_num;                  			    /* ���������Ľ�������������   */
    int		    maxConn;					 			/* ��������� */
    int         timeout;					 				/* ��ʱʱ�� */
    int         bind_port;                                  /* �󶨶˿�*/
    char        dest_ip[IPADDR_LEN + 1];                        /*��Ŀ��IP */
    int         dest_port;                                  /* Ŀ��˿� */
    
} CONN_PARAM_CFGABLE;

#ifdef _LIB_SOURCR_
#define EXTERN 
#else
#define EXTERN extern
#endif

EXTERN int getCfg(CONN_PARAM_CFGABLE *cfg, char *cfgFile);
EXTERN int sendDataToThird(CONN_PARAM_CFGABLE *cfg, int sockfd, char *send_buf, long len, int timeout);
EXTERN int recvDataFromThird(CONN_PARAM_CFGABLE *cfg, int sockfd, char **p_recv_buf, long *p_recvlen, int p_timeout);

#endif
