#ifndef _CFG_RECV_SEND_
#define _CFG_RECV_SEND_

#include "ecnmain.h"

//缺省超时时间
#define DEFAULT_TIMEOUT 120

//标志位最大长度
#define FLAG_MAX_LEN  16

#define LONG_CONN     1
#define SHORT_CONN    0
#define MAX_CONN      50
#define MAX_DAT_LEN   16*1024

//值类型
#define CHAR          1
#define	INT			      2
#define ASCII         3
#define STRING        4
#define SHORT         5

//配置文件节点别
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
    int			haveMsgHead;              	 			/* 是否带前置长度 0:Y 1:N    */
    int         isSaveMsgHead;                          /* 是否保存包头*/
    int			haveNextMsg;				 			/* 是否还有下一个包 */
    int			haveResponseMsgHead;		 			/* 返回消息是否带前置长度*/

    int			msgHeadLen;                  			/* 报文头长度				  */
    int			msgBodyLen;								/* 报文体长度*/
    int			msgBodyLenStartPos;			 			/* 包体长度在报文头中起始位置*/
    int			msgBodyLenLength;			 			/* 包体长度的长度			  */
    //added by kixiong on 2006-06-11 at shanghai
    int			isInclHeadLen;							/* 包体长度的长度是否包含包头长度*/
    //added end
    //added by kixiong on 2006-06-26 at shanghai
    int			isInclBodyLenLen;						/* 包体长度的长度是否包含包头长度*/
    //added end
    int			msgBodyLenLengthValueType;	 			/* 包体长度的长度的数据类型  */
    int			haveNextMsgFlgStartPos;		 			/* 是否存在下一个分包标志在报文头的起始位置*/
    int			haveNextMsgFlgLen;		 	 			/* 是否存在下一个分包标志的长度*/
    char		true_value[FLAG_MAX_LEN+1];	 			/* 存在下一个分包的标志*/
    char		false_value[FLAG_MAX_LEN+1]; 			/* 不存在下一个分包的标志*/
    int			flag_value_type;						/* 标志值的类型(CHAR、INT、ASCII), 默认为CHAR型*/
    char		endValue[FLAG_MAX_LEN];		 			/* 接收结束标志值*/
    int			endValueLen;				 			/* 接收结束标志值的长度*/
    int			endValueType;				 			/* 接收结束标志值的数据类型*/
    int			rpMsgHeadLen;				 			/* 响应包是否需要前置长度*/
    
    int         haveMsgTail;                            /*是否有包尾*/
    int         isSaveMsgTail;                          /*是否保存包尾*/
    int			msgTailLen;                             /*包尾长度*/

    int         syncConType;                 			    /* 连接类型 0:短连接 1:长连接 */
    char        ipConFile[FILENAME_LEN + 1]; 			    /* ip配置文件名长度           */
    char        msgType[MSGLEN +1 ];         			    /* 消息类型                   */
    int         port;                        			    /* 服务启动时监听端口号       */
    int         thread_num;                  			    /* 服务启动的接收请求线索数   */
    int		    maxConn;					 			/* 最大连接数 */
    int         timeout;					 				/* 超时时间 */
    int         bind_port;                                  /* 绑定端口*/
    char        dest_ip[IPADDR_LEN + 1];                        /*　目标IP */
    int         dest_port;                                  /* 目标端口 */
    
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
