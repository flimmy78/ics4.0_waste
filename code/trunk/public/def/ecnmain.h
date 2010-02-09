/********************************************************************
Copyright (C),1998-2003,Hisuntech Co.,Ltd.
  File name:      // ecnmain.h
  Author:         // Wangxd
  Version:        // 1.0¾
  Date:           // 20030327
  Description:    // ÕâÊÇÍâ²¿Í¨Ñ¶Ä£¿éÓÃµ½µÄÎ¨Ò»µÄÍ·ÎÄ¼ş
                  // Ö÷Òª¶¨ÒåIPÅäÖÃ½á¹¹¡¢Òì²½Í¨Ñ¶Á¬½Ó×´Ì¬ĞÅÏ¢±í½á¹¹
                  // Í¬²½Í¨Ñ¶Á¬½ÓµÇ¼Ç±í½á¹¹¡¢ÏßË÷ĞÅÏ¢½á¹¹µÈ
  Others:         // ÆäËüÄÚÈİµÄËµÃ÷
  Function List:  // Ö÷Òªº¯ÊıÁĞ±í£¬Ã¿Ìõ¼ÇÂ¼Ó¦°üÀ¨º¯ÊıÃû¼°¹¦ÄÜ¼òÒªËµÃ÷
    1. ....
  History:        // ĞŞ¸ÄÀúÊ·¼ÇÂ¼ÁĞ±í£¬Ã¿ÌõĞŞ¸Ä¼ÇÂ¼Ó¦°üÀ¨ĞŞ¸ÄÈÕÆÚ¡¢
                  // ĞŞ¸ÄÕß¼°ĞŞ¸ÄÄÚÈİ¼òÊö  
    1. Date:
       Author:
       Modification:
    2. ...
********************************************************************/

#ifndef	_ECNMAIN_H_
#define	_ECNMAIN_H_
#include "hibase.h"
#include "hiserver.h"
#include "hiipchk.h"
#include "hilgr.h"


#define IPADDR_LEN               15
#define SOCKFD_LEN               10
#define FILENAME_LEN             50
#define MSGLEN                   6
#define MAX_DATA_LEN             8192
#define NET_ERROR_RQ             "100501"
#define NET_ERROR_RP             "100502"
#define NET_OK                   "000000"
#define KEY_LEN                  16
#define ERRCODE                  0
#define TIME_OUT                 30
#define PORT_LEN                 10
#define MSGTYPE_LEN              1
#define PRELEN_LEN               8
#define READ_FILE_LEN            8192

#define HAVE_PRELEN              1
#define NO_PRELEN                0

#define DEFAULT_CONN_SERVER_NUM  20
#define TERMFILESEND             "dat/term/send"

/*
 *  ´æ·Å¿Í»§¶ËIPµØÖ·ºÍ¶Ë¿ÚºÅµÄ±í½á¹¹£¬ÓÃÓÚIP¼ì²éºÍÒì²½Í¨Ñ¶
struct	_ip_table {
	char	ip[IPADDR_LEN + 1];                  ipµØÖ· 
    int     port;                                ¶Ë¿ÚºÅ 
	struct	_ip_table	*next;                   Ö¸ÏòÏÂÒ»¸ö½Úµã
};
typedef	struct _ip_table	IPNODE;
*/


/*
 * Òì²½Í¨Ñ¶Á¬½Ó×´Ì¬ĞÅÏ¢±í£¬ÓÃÓÚÒì²½³¤Á¬½Óµ¥¹¤/Ë«¹¤
 */
struct async_ip_sockfd{   
     char                   ip_addr[IPADDR_LEN + 1];   /* ipµØÖ·  */
     short                  sockfd;                    /* socket¾ä±ú  */
     int                    port;                      /* ¶Ë¿ÚºÅ */    
     short                  active;                    /* 1: active; 0:closed*/ 
     pthread_mutex_t        fd_lock;                   /*  Ëø */    
     struct async_ip_sockfd *next;                     /* Ö¸ÏòÏÂÒ»½Úµã  */
};
typedef struct async_ip_sockfd ASYNC_IP_SOCKFD;


/*
 * Í¬²½Á¬½ÓµÇ¼Ç±í½á¹¹£¬ÓÃÓÚÍ¬²½³¤/¶ÌÁ¬½ÓÖĞµÄÆ¥Åä Î´ÓÃµ½
struct _sync_conn_node {
     char  ip[IPADDR_LEN+1];                      IPµØÖ· 
     int   sockfd;                                Í¨Ñ¶ÃèÊö·û 
     char  key[KEY_LEN +1];                       Á¬½ÓKEYÖµ 
     struct _sync_conn_node * next;               Ö¸ÏòÏÂÒ»¸ö½Úµã 
};
typedef struct _sync_conn_node SyncConnNode;
*/


/*
 *  ÏßË÷µÇ¼Ç½Úµã,ÓÃÓÚ×ÊÔ´ÊÍ·Å Î´ÓÃµ½

struct thread_node{    
    pthread_t          tid;                       ÏßË÷id 
    int                sockfd;                    socketÃèÊö·û 
    struct thread_node *next;                     Ö¸ÏòÏÂÒ»¸ö½Úµã
};
typedef struct thread_node THREAD_NODE;
*/


/*
 *ÁÙÊ±´«µİ²ÎÊıµÄ½á¹¹
 */
struct conn_desp{    
    char        ipAddr[IPADDR_LEN+1];        /* ipµØÖ·     */
    int         sockfd;                      /* socket¾ä±ú */
    char        key[KEY_LEN +1];             /* keyÖµ      */
    int         slot;                        /* Æ¥Åä½ÚµãÔÚÆ¥Åä½Úµã±íÖĞµÄ²ÛÎ»*/
    int			timeout;					 /* ³¬Ê±Ê±¼ä */
};
typedef struct conn_desp CONN_DESP;

/*
 * È«¾Ö±äÁ¿²ÎÊı½á¹¹
 */
struct conn_param
{
    int         havePreLen;                  /* ÊÇ·ñ´øÇ°ÖÃ³¤¶È 0:Y 1:N */
    int         preLenLen;                   /* Ç°ÖÃ³¤¶ÈÓòµÄ³¤¶È       */
    int         syncConType;                 /* Á¬½ÓÀàĞÍ 0:¶ÌÁ¬½Ó 1:³¤Á¬½Ó */
    char        ipConFile[FILENAME_LEN + 1]; /* ipÅäÖÃÎÄ¼şÃû³¤¶È           */
    char        msgType[MSGLEN +1 ];         /* ÏûÏ¢ÀàĞÍ                   */
    int         port;                        /* ·şÎñÆô¶¯Ê±¼àÌı¶Ë¿ÚºÅ       */
    int         thread_num;                  /* ·şÎñÆô¶¯µÄ½ÓÊÕÇëÇóÏßË÷Êı   */
    int			maxConn;					 /* ×î´óÁ¬½ÓÊı */
    int         timeout;					 /* ³¬Ê±Ê±¼ä */
};
typedef struct conn_param CONN_PARAM;

/*
 * scaÒì²½³¤Á¬½Óµ¥¹¤´«µİ²ÎÊıÁÙÊ±½á¹¹
 */
struct scaLongAsyncOnePara
{
    char        msgType[MSGLEN + 1];           /* ÏûÏ¢ÀàĞÍ     */
    char        clientIpAddr[IPADDR_LEN + 1];  /* ÓëccaÍ¨Ñ¶µÄ¿Í»§¶ËipµØÖ· */
    char        key[KEY_LEN + 1];              /* ccaÎªÍ¬²½Á¬½ÓÊ±Ê±¼ä´Á   */
    char        ccaSockFd[SOCKFD_LEN +1];      /* ccaÓë¿Í»§¶ËÍ¨Ñ¶µÄÁ¬½ÓÃèÊö·û*/
    int         scaSockFd;                     /* scaÓëÍâÁª·şÎñÆ÷Í¨Ñ¶µÄÁ¬½Ó×Ö*/
};
typedef struct scaLongAsyncOnePara SCA_LONG_ASYNC_ONE_PARA;

/*
 * ¿Í»§¶ËÁ¬½ÓĞÅÏ¢±í
 */
struct server_conf
{
    char            serverIp[IPADDR_LEN + 1];    /* ·şÎñ¶ËipµØÖ· */
    int             port;                        /* ·şÎñ¶Ë¶Ë¿ÚºÅ */
    int             sockFd;                      /* Á¬½ÓÃèÊö·û   */
    pthread_mutex_t conn_lock;                   /* Á¬½ÓËø       */
};
typedef struct server_conf SERVER_CONF;

char            gLogFileName[20];

#ifdef	_ECNCOMBAS_LIB_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

EXTERN ASYNC_IP_SOCKFD * loadIpTableAsync(char *);
EXTERN int             checkIpAsync(ASYNC_IP_SOCKFD * , char *);
EXTERN void            freeIpTableAsync(ASYNC_IP_SOCKFD *);
EXTERN int			   tmm_socketreadbylen(int sockfd, char ** ptr, int hlen);
EXTERN Logger *		   ecnCreateLogger(void);
#undef	EXTERN

#endif /* _ECNMAIN_H_ */
