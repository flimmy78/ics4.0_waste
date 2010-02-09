/********************************************************************
Copyright (C),1998-2003,Hisuntech Co.,Ltd.
  File name:      // ecnmain.h
  Author:         // Wangxd
  Version:        // 1.0�
  Date:           // 20030327
  Description:    // �����ⲿͨѶģ���õ���Ψһ��ͷ�ļ�
                  // ��Ҫ����IP���ýṹ���첽ͨѶ����״̬��Ϣ��ṹ
                  // ͬ��ͨѶ���ӵǼǱ�ṹ��������Ϣ�ṹ��
  Others:         // �������ݵ�˵��
  Function List:  // ��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��
    1. ....
  History:        // �޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ�
                  // �޸��߼��޸����ݼ���  
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
 *  ��ſͻ���IP��ַ�Ͷ˿ںŵı�ṹ������IP�����첽ͨѶ
struct	_ip_table {
	char	ip[IPADDR_LEN + 1];                  ip��ַ 
    int     port;                                �˿ں� 
	struct	_ip_table	*next;                   ָ����һ���ڵ�
};
typedef	struct _ip_table	IPNODE;
*/


/*
 * �첽ͨѶ����״̬��Ϣ�������첽�����ӵ���/˫��
 */
struct async_ip_sockfd{   
     char                   ip_addr[IPADDR_LEN + 1];   /* ip��ַ  */
     short                  sockfd;                    /* socket���  */
     int                    port;                      /* �˿ں� */    
     short                  active;                    /* 1: active; 0:closed*/ 
     pthread_mutex_t        fd_lock;                   /*  �� */    
     struct async_ip_sockfd *next;                     /* ָ����һ�ڵ�  */
};
typedef struct async_ip_sockfd ASYNC_IP_SOCKFD;


/*
 * ͬ�����ӵǼǱ�ṹ������ͬ����/�������е�ƥ�� δ�õ�
struct _sync_conn_node {
     char  ip[IPADDR_LEN+1];                      IP��ַ 
     int   sockfd;                                ͨѶ������ 
     char  key[KEY_LEN +1];                       ����KEYֵ 
     struct _sync_conn_node * next;               ָ����һ���ڵ� 
};
typedef struct _sync_conn_node SyncConnNode;
*/


/*
 *  �����Ǽǽڵ�,������Դ�ͷ� δ�õ�

struct thread_node{    
    pthread_t          tid;                       ����id 
    int                sockfd;                    socket������ 
    struct thread_node *next;                     ָ����һ���ڵ�
};
typedef struct thread_node THREAD_NODE;
*/


/*
 *��ʱ���ݲ����Ľṹ
 */
struct conn_desp{    
    char        ipAddr[IPADDR_LEN+1];        /* ip��ַ     */
    int         sockfd;                      /* socket��� */
    char        key[KEY_LEN +1];             /* keyֵ      */
    int         slot;                        /* ƥ��ڵ���ƥ��ڵ���еĲ�λ*/
    int			timeout;					 /* ��ʱʱ�� */
};
typedef struct conn_desp CONN_DESP;

/*
 * ȫ�ֱ��������ṹ
 */
struct conn_param
{
    int         havePreLen;                  /* �Ƿ��ǰ�ó��� 0:Y 1:N */
    int         preLenLen;                   /* ǰ�ó�����ĳ���       */
    int         syncConType;                 /* �������� 0:������ 1:������ */
    char        ipConFile[FILENAME_LEN + 1]; /* ip�����ļ�������           */
    char        msgType[MSGLEN +1 ];         /* ��Ϣ����                   */
    int         port;                        /* ��������ʱ�����˿ں�       */
    int         thread_num;                  /* ���������Ľ�������������   */
    int			maxConn;					 /* ��������� */
    int         timeout;					 /* ��ʱʱ�� */
};
typedef struct conn_param CONN_PARAM;

/*
 * sca�첽�����ӵ������ݲ�����ʱ�ṹ
 */
struct scaLongAsyncOnePara
{
    char        msgType[MSGLEN + 1];           /* ��Ϣ����     */
    char        clientIpAddr[IPADDR_LEN + 1];  /* ��ccaͨѶ�Ŀͻ���ip��ַ */
    char        key[KEY_LEN + 1];              /* ccaΪͬ������ʱʱ���   */
    char        ccaSockFd[SOCKFD_LEN +1];      /* cca��ͻ���ͨѶ������������*/
    int         scaSockFd;                     /* sca������������ͨѶ��������*/
};
typedef struct scaLongAsyncOnePara SCA_LONG_ASYNC_ONE_PARA;

/*
 * �ͻ���������Ϣ��
 */
struct server_conf
{
    char            serverIp[IPADDR_LEN + 1];    /* �����ip��ַ */
    int             port;                        /* ����˶˿ں� */
    int             sockFd;                      /* ����������   */
    pthread_mutex_t conn_lock;                   /* ������       */
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
