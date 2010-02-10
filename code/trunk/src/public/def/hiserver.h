/*
 * History: Date        Position        Author                Action
 * ----------------------------------------------------------------------------
 *             2000-12-11        ShenZhen        L.Ben                Create
 ******************************************************************************/

#ifndef _HI_SERVER_H_
#define _HI_SERVER_H_

#define _H_LOCALEDEF

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <stdarg.h>
#include "hixml.h"
#include "himempool.h"
#include "hithread.h"
#include "hidsm.h"
#include "himmg.h"
#include "hilgr.h"
#include "hash.h"
#include "hiconstant.h"
#include "hipubpra.h"

#ifndef TRUE
#define TRUE           1
#endif
#ifndef FALSE
#define FALSE          0
#endif

#define	TRACE_OFF	   0    /* ������־�ر�״̬ */
#define	TRACE_ON	   1    /* ������־��״̬ */

#define NAMES_LEN      60   /* ���ֵĳ��� */
#define PRIORITYS      5    /* ���ȼ����� */
#define RQST_ID_LEN    20   /* �����ų� */
#define MSG_TYPE_LEN   6    /* ��Ϣ���ͳ� */
#define FLD_NAME_LEN   3    /* ��Ϣͷ��������֮���� */
#define SVR_ADDR_LEN   15   /* ��������ַ���� */
#define SVR_NAME_LEN   8    /* ���������ֳ��� */
#define SVR_ID_LEN     6    /* ������ID���� */
#define SVR_TYPE_LEN   3    /* ���������ͳ��� */
#define POS_ID_LEN     4    /* ������Ϣ���λ�ó��� */
#define MSG_ID_LEN     4    /* ��ϢID���� */
#define MAX_QPAIR_NUM  5    /* һ���������������õ����Q-Pair�� */

#include "hidbdsc.h"
#include "hiusfdbapi.h"
#include "hidatabase.h"

/* ��¼����ID�Ľӵ� */
struct _thread_id_node {
    short     cancel_flg;           /* �����Ƿ�ȡ�� */
    pthread_t tid;                  /* ������ */
    struct _thread_id_node * next;  /* ָ����һ�ӵ��ָ�� */
};
typedef struct _thread_id_node ThreadIdNode;

/* ��¼���е�����ID */
struct _thread_id_rec {
    short total;              /* �ӵ���Ŀ */
    ThreadIdNode * head;      /* ����ͷָ�� */
    ThreadIdNode * tail;      /* ����βָ�� */
    pthread_mutex_t id_lock;  /* ����������� */
};
typedef struct _thread_id_rec ThreadIdRec;

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

/* ͬ������Ǽ����� */
struct _syn_request_node {
    short           qpair_id;                  /* ͬ������Ŀ��Q-Pair */
    short           slot_id;                   /* ������ */
    char            request_id[RQST_ID_LEN+1]; /* ������ */
    long            bgn_exist_time;            /* ���������ʱ�� */
    Message *       response_msg;              /* Ӧ����Ϣ(�����صİ�) */
    pthread_mutex_t notify_lock;               /* ֪ͨ�� - �����������ʹ�� */
    pthread_cond_t  notify_cond;               /* ֪ͨ���������� */
};
typedef struct _syn_request_node SynRequestNode;

/* ��Ϣ�������� */
struct _msg_cache_node {
    Message * q_msg;                /* ����Ϣ */
    struct _msg_cache_node * next;  /* ָ����һ������Ϣ��ָ�� */
};
typedef struct _msg_cache_node MsgCacheNode;

/* ����Ϣ�Ǽ����� */
struct _big_msg_node {
    char            msg_type[MSG_TYPE_LEN+1];   /* ��Ϣ���� */
    char            request_id[RQST_ID_LEN+1];  /* ������ */
    MsgCacheNode *  msg_link_head;              /* ��Ϣ��������ͷ */
    pthread_mutex_t msg_link_lock;              /* ����Ϣ����������� */
    pthread_cond_t  notify_cond;                /* ֪ͨ���������� */
    long            bgn_exist_time;             /* ���������ʱ�� */
};
typedef struct _big_msg_node BigMsgNode;

/* ��Ϣ-����ģ����ձ�ӵ� */
struct _msg_task_node {
    char msg_type[MSG_TYPE_LEN+1];  /* ��Ϣ���� */
    char p_module[NAMES_LEN+1];     /* ����ģ������ */
    int (* p_task)(Message *);      /* ����ģ��ĺ���ָ�� */
    struct _msg_task_node * next;   /* ָ����һ�ӵ��ָ�� */
};
typedef struct _msg_task_node MsgTaskNode;

/* Queue */
struct _queue {
    pthread_t       deliver_tid;                /* ������еķַ���������ID */
    short           q_high_water;               /* ��ˮλ */
    short           q_low_water;                /* ��ˮλ */
    short           q_max_length;               /* �����г��� */
    short           max_serv_worker;            /* �������ڸö��еĹ������� */
    short           serving_worker;             /* �������ڸö��еĹ������� */
    Message **      msg_q[PRIORITYS];           /* ��Ϣ���� */
    short           q_queue_head[PRIORITYS];    /* ����ͷ */
    short           q_queue_tail[PRIORITYS];    /* ����β */
    short           q_curr_length[PRIORITYS];   /* ��ǰ���г��� */
    short           q_water_flag[PRIORITYS];    /* ����ˮλ��־ */
    short           q_de_priority[PRIORITYS];   /* ���г��Ӹ���-�������ȴ��� */
    pthread_mutex_t en_de_lock;                 /* ��������� */
    pthread_cond_t  en_notify_cond[PRIORITYS];  /* ֪ͨд���������� */
    pthread_cond_t  de_notify_cond;             /* ֪ͨ������������ */
    MemoryPool *    big_msg_list;               /* ����Ϣ�Ǽ����� */
    pthread_mutex_t big_msg_lock;               /* ����Ϣ�Ǽ�������� */
    MsgTaskNode *   msg_tasks;                  /* �����ڸö��е�����ģ�� */
    pthread_mutex_t msg_tasks_lock;             /* ����ģ������д�� */
    char            default_module[NAMES_LEN+1];/* Ĭ��ִ��ģ������ */
    int (* default_task)(Message *);            /* Ĭ��ִ��ģ�� */
    pthread_mutex_t xxx_lock;                   /* ��������� */
    pthread_cond_t  xxx_cond;                   /* ֪ͨд���������� */
};
typedef struct _queue Queue;

/* Q-Pair */
struct _queue_pair {
    short           qpair_id;                 /* Q-Pair��ID */
    char            qpair_name[NAMES_LEN+1];  /* Q-Pair���� */
    Queue           request_q;                /* ������� */
    Queue           response_q;               /* Ӧ����� */
    MemoryPool *    syn_request_list;         /* ͬ������Ǽ� */
    pthread_mutex_t syn_list_lock;            /* ����ͬ������ǼǱ���� */
};
typedef struct _queue_pair QueuePair;

/* ���б��� */
struct _queue_alias {
    short qpair_id;                 /* Q-Pair��� */
    char  qpair_name[NAMES_LEN+1];  /* Q-Pair���� */
    short queue_type;               /* �������� */
};
typedef struct _queue_alias QueueAlias;

/* ��̬��ǼǱ� */
struct _dll_node {
    char   lib_name[NAMES_LEN+1];  /* ������ */
    void * lib_handle;             /* ����ʾ�� */
    void (* donefunc)();           /* ��ر�ʱִ�еĺ��� */
    struct _dll_node * next;       /* ָ����һ���ӵ�ָ�� */
};
typedef struct _dll_node DllNode;

/* ���������ǼǱ� */
struct _worker_thread_rec {
    pthread_t       worker_tid;              /* ��������������ID */
    Message *       processed_msg;           /* ����ģ��Ҫ�������Ϣ */
    QueueAlias *    calling_qpair;           /* �����Լ���Q-Pair���� */
    long            bgn_exec_time;           /* ��ʼִ��ʱ�� */
    char *          executing_module;        /* ����ִ�е�ģ������� */
    DBConnRec       * using_db_conn; 		 /* ʹ�ù������ݿ����Ӻ� */  
    DBConnRec       * curr_db_conn; 		 /* ��ǰ����ʹ�õ����ݿ����Ӻ� */       
    short           cleaner_num;             /* ��ջ�е���������Ŀ */
    pthread_mutex_t notify_lock;             /* �����Ⱥ���ָ����� */
    pthread_cond_t  notify_cond;             /* �����Ⱥ���ָ����������� */
};
typedef struct _worker_thread_rec  WorkerThreadRec;

/* �����ع���ṹ */
struct _thread_pool_rec {
    pthread_t manager_tid;       /* �ع���������������ID */
    short     min_thread_num;    /* Ҫ���������ٹ��������� */
    short     max_thread_num;    /* �������пɹ������������� */
    short     curr_thread_num;   /* ��ǰ���������� */
    short     busy_thread_num;   /* æ�������� */
    short     allot_policy;      /* ������������ */
    short     polling_time;      /* ÿ����ѯ��ʱ���� */
    short     tuning_or_not;     /* �Ƿ�̬�������������� */
    short     high_load_level;   /* �߸��ɱ�׼ */
    short     high_load_point;   /* �߸��� */
    short     high_load_times;   /* �߸���ά���˶��ٸ���ѯʱ�� */
    short     low_load_level;    /* �͸��ɱ�׼ */
    short     low_load_point;    /* �͸��� */
    short     low_load_times;    /* �͸���ά���˶��ٸ���ѯʱ�� */
    short     start_thread_step; /* ÿ���������ٸ����� */
    short     stop_thread_step;  /* ÿ��ֹͣ���ٸ����� */
    short     be_tuned_num;      /* �������� */
};
typedef struct _thread_pool_rec ThreadPoolRec;

/* ���й��������ǼǱ� */
struct _idler_thread_rec {
    short           first_idler;  /* ��һ�����еĹ���������������λ�� */
    short           last_idler;   /* ���һ�����еĹ���������������λ�� */
    short *         idler_list;   /* ���������ļ�¼������ */
    pthread_mutex_t idler_lock;   /* ������ */
    pthread_cond_t  idler_cond;   /* �������� - ���ڶ�æʱ�ȴ� */
};
typedef struct _idler_thread_rec IdlerThreadRec;

/* ��λ�õǼǱ� */
struct _empty_pos_rec {
        short    first_pos;  /* ��һ����λ�� */
        short    last_pos;   /* ���һ����λ�� */
        short *  pos_list;   /* ��λ�õǼǱ� */
};
typedef struct _empty_pos_rec EmptyPosRec;

/* ����������� */
struct _thread_spec_data {
        short worker_id;
        short qpair_id;
        short queue_type;
};
typedef struct _thread_spec_data ThreadSpecData;

struct _pub_runtime_env_rec {
        char               svr_addr[SVR_ADDR_LEN+1];  /* IP address */
        char               svr_name[SVR_NAME_LEN+1];  /* ���������� */
        char               svr_type[SVR_TYPE_LEN+1];  /* ���������� */
        short              svr_id;                    /* ������ID */
        QueuePair **       qarray;                    /* Q-Pair���� */
        short              q_num;                     /* Q-Pair�� */
        long               seq_no;                    /* �����ŵ����к� */
        pthread_mutex_t    seq_lock;                  /* ���кŵ��� */
        long               clock;                     /* ʱ�Ӽ��� */
        pthread_mutex_t    clock_lock;                /* ʱ���� */
        pthread_cond_t     clock_cond;                /* ʱ���������� */
        long               tr_count;                  /* �ѷ����Ľ����� */
        short *            cancel_flags;              /* ȡ����־ */
        short *            busy_flags;                /* æ��־ */
        pthread_mutex_t    cancel_lock;               /* ȡ����־������ */
        long               max_timeout;               /* �������ʱʱ�� */
        ThreadPoolRec      tpool;                     /* ���������� */
        WorkerThreadRec ** tworkers;                  /* �������� */
        IdlerThreadRec     tidlers;                   /* ���������Ǽ� */
        long               portal;                    /* ���Ĺ����˿� */
        short              is_closing;                /* �Ƿ����ڹر� */
		char *             workdir;                   /* ����·���������� */
		int                log_flag;                  /* ��־���ر�־ */
		char			   syslog_file[NAMES_LEN+1];  /* ������������־�ļ� */
		char			   errlog_file[NAMES_LEN+1];  /* ������������־�ļ� */
		XmlNode *          region_node;               /* ����������Ϣ */
		/* 
		 * ƽ̨�������� 
		 * Added by liangwj at 2008-11-03
		 */
		char			   ap_name[SVR_NAME_LEN+1];	  /* Ӧ���� */
		LoggerMessage	*  logger_msg;				  /* ��־��Ϣ */
		Logger 			*  sys_logger;				  /* ϵͳ��־�� */
		Logger 			*  trc_logger;				  /* ������־�� */
		Logger 			*  err_logger;				  /* ������־�� */
};
typedef struct _pub_runtime_env_rec PubRuntimeEnvRec;

/*
 * Queue��Ϣ
 * Added by liangwj at 2006-10-30
 */
typedef struct _QueueInformation{
	long	ServingNum;
	long	QueueNum[PRIORITYS];
}QueueInformation;

/*
 * QueuePair��Ϣ
 * Added by liangwj at 2006-10-30
 */
typedef struct _QPairInformation{
	QueueInformation	Request;
	QueueInformation	Response;	
}QPairInformation;

/*
 * ����������Ϣ
 * Added by liangwj at 2006-10-30
 */
typedef struct _ServerInformation{
	char 				* Name;	
	long 				Status;
	long				StartTime;
	long				ServerID;
	long				ProcessID;
	char				IPAddr[15+1];
	long				Portal;
	long				TraceSwitch;
	long				MaxWorkerNum;
	long				BusyWorkerNum;
	long				QPairNum;
	QPairInformation	QPair[MAX_QPAIR_NUM];
}ServerInformation;

/*
 * �����Ľӿڶ���
 * Added by liangwj at 2006-10-30
 */
typedef struct _InterfaceDefine{
	char 					* Name;	
	struct _InterfaceDefine	* Next;
}InterfaceDefine;


/*
 * ���ִ��ͳ����Ϣ
 * added by kixiong at 2008-10-20 15:31
 */
struct _comp_ctx_info
{
	char			comp_name[64];
	struct timeval	total_time;
	long			total_count;
};
typedef struct _comp_ctx_info CompCtxInfo;

/*
 * ������Ϣ
 * Added by liangwj at 2006-10-30
 */
typedef struct _ServiceInformation{
	char 			* Name;	
	char			* ServerName;
	long 			Status;
	long            Monitor;
	InterfaceDefine * MustInput;
	InterfaceDefine	* OptionInput;
	InterfaceDefine	* Output;
	InterfaceDefine	* Fault;
	double			CurrTime;
	double			TotalTime;
	long			InvokeCount;
	long			FaultCount;
	long			UnsuccessfulCount;
	long			SuccessfulCount;
	/*
	 * added by kixiong at 2008-10-21 9:28
	 *���ͳ����Ϣ
	 */
	hash_t			* comps_ctx_info;
}ServiceInformation;

/*
 * ȫ����Ϣ
 * Added by liangwj at 2006-10-30
 */
typedef struct {
	pthread_rwlock_t	ServersLock;
	DataSource			* Servers;
	int					ServersFlag;
	
	pthread_rwlock_t	LocalServicesLock;
	int					UpdateLocalService;
	DataSource			* LocalServices;
	DataSource			* BakLocalServices;
	
	pthread_rwlock_t	RemoteServicesLock;
	DataSource			* RemoteServices;
}GlobalInformation;

/* ȫ�ֱ��� */
#ifndef SERVER_EXTERN
#define SERVER_EXTERN
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN PubRuntimeEnvRec * _PubRuntimeEnv;    /* ���������л��� */
EXTERN EmptyPosRec        _EmptyPosReg;      /* ��λ�õǼ� */
EXTERN pthread_key_t *    _CallingQPair;     /* ���ø�ģ���Q-Pair */
EXTERN pthread_attr_t     _ThreadAttr;
EXTERN XmlDocument *      _DomTreeRootNode;  /* �����ļ�DOM���ĸ���� */
EXTERN XmlNode *          _RegionNode;       /* ��ڵ� */
EXTERN XmlNode *          _ServerNode;       /* �������ڵ� */
EXTERN DllNode *          _DllOpenRegList;   /* �򿪵Ķ�̬�����б� */
EXTERN ThreadIdRec        _ThreadIdList;     /* ����ID�ļ�¼ */
EXTERN DataSourceContainer *   _DBConnectionPool; /* ���ݿ����ӳ� */
/*
 * ȫ����Ϣ
 * Added by liangwj at 2006-10-30
 */
EXTERN GlobalInformation * _GlobalInf;    /* ���������л��� */
#undef	EXTERN

#ifdef _LIB_SOME_CLEANER
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN void parserCleaner(void *);
EXTERN void documentCleaner(void *);
EXTERN void nodeCleaner(void *);
EXTERN void builderCleaner(void *);
EXTERN void charCleaner(void *);
EXTERN void clockCleaner(void *);
#undef EXTERN

#ifdef _LIB_MSG_OP1
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int  usfGetMsgHeadValue(Message *, char *, char *);
EXTERN int  usfAddMsgHeadValue(Message *, char *, char *, short);
EXTERN int  usfSetMsgHeadValue(Message *, char *, char *, short);
EXTERN int  usfSetMsgData(Message *, char *, long);
EXTERN void usfFreeMsgData(Message *);
EXTERN void usfDelMsgHeadValue(Message *, char *);
EXTERN void usfDestroyMsg(Message *);
EXTERN Message * usfDupMsgFrame(Message * msg);
EXTERN Message * usfCreateMsg(char * msg_type);
EXTERN XmlNode * usfGetRegionNode();
EXTERN char * usfGetRegionName();
EXTERN int usfGetRequestID(char *);
#undef	EXTERN

#ifdef _LIB_MSG_OP2
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN Message * usfCreateMsgByString(char *, long);
EXTERN Message * usfCreateMsgByHeadString(char *, long);
EXTERN int usfMsgToString(Message *, char **, long *);
EXTERN int usfMsgToHeadString(Message *, char **, long *);
#undef	EXTERN

#ifdef _LIB_QPAIR_OP1
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int usfAddNodeInBigmsgRegLink(Queue *, char *, char *);
EXTERN int usfAddNodeInMsgLink(Queue *, Message *);
EXTERN int usfMsgEnQueue(Queue *, Message *);
EXTERN int usfGetNextMsgFromQueue(Queue * , Message *, long, Message **, short *);
EXTERN int usfPutMsgInQueueAsyn(Queue *, Message *);
EXTERN int usfPutMsgInQueueSyn(QueuePair *, Message *, long, Message **);
EXTERN int usfReceiveResponseFromQPair(QueuePair *, SynRequestNode *, long, Message **);
EXTERN int usfSendRequest(Message *);
EXTERN int usfSendRequestToLeft(Message *);
EXTERN int usfSendRequestToRight(Message *);
EXTERN int usfSendResponse(Message *);
EXTERN int usfSendResponseToLeft(Message *);
EXTERN int usfSendResponseToRight(Message *);
EXTERN int usfReceiveResponse(SynRequestNode *, long, Message **);
EXTERN int usfRetrieveNextRequestMsg(Message *, long, Message **, short *);
EXTERN int usfRetrieveNextResponseMsg(Message *, long, Message **, short *);
EXTERN int usfSendRequestAndWaitResponse(Message *, long, Message **);
EXTERN int usfSendRequestToRightAndWaitResponse(Message *, long, Message **);
EXTERN int usfSetPubRuntimeEnv(void *);
EXTERN int usfSendResponseWhenError(Message *, char *, char *);
EXTERN int usfIsNotify(Message *);
EXTERN int usfIsRequest(Message *);
EXTERN int usfSetNotify(Message *);
EXTERN int usfSetTrace(Message *);
#undef	EXTERN

#ifdef _LIB_QPAIR_OP2
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int usfCall(Message *, char *, void *, char *, long, long, void **, char *, long *, Message **);
EXTERN int usfGetReply(SynRequestNode * synd, long timeout, void ** out_data, char * out_type, long * out_len, Message ** rpmsg);
EXTERN int usfForward(Message *, char *, void *, char *, long);
EXTERN int usfReturn(Message *, void *, char *, long);
EXTERN int usfNotify(Message *);
EXTERN int usfNotifyToLeft(Message *);
EXTERN int usfNotifyToRight(Message *);
EXTERN int usfParsing(Message *, void **);
EXTERN void usfRemoveAllSubMsg(Message *);
EXTERN SynRequestNode * usfCallAsyn(Message *, char *, void *, char *, long);
#undef	EXTERN

#ifdef _LIB_THREAD_BASE
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int createThread(pthread_t *, const pthread_attr_t *, void * (*)(void *), void *);
EXTERN int cancelThread(pthread_t);
EXTERN void waitNSecond(int);
EXTERN void waitNMilliSecond(long);
#undef	EXTERN

#ifdef _LIB_INF_MNG
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int	initGlobalInformation();
EXTERN void	freeGlobalInformation();
EXTERN int  lockWriteLocalServices();
EXTERN int  lockReadLocalServices();
EXTERN int  unlockLocalServices();
EXTERN int  lockWriteRemoteServices();
EXTERN int  lockReadRemoteServices();
EXTERN int  unlockRemoteServices();
EXTERN void	freeInterfaceDefine(InterfaceDefine *);
EXTERN void freeServers(DataSource *);
EXTERN void	freeServerInformation(ServerInformation *);
EXTERN InterfaceDefine * createInterfaceDefine(char *);
EXTERN ServerInformation * newServerInformation(char *, long);
EXTERN ServerInformation * addServerInformation(char *, long);
EXTERN ServerInformation * getServerInformation(char *, long);
EXTERN void deleteServerInformation(char *, long);
EXTERN ServiceInformation * newServiceInformation(char *);
EXTERN ServiceInformation * addServiceInformation(DataSource *, char *);
EXTERN ServiceInformation * addLocalService(char *);
EXTERN ServiceInformation * addRemoteService(char *);
EXTERN ServiceInformation * getServiceInformation(DataSource *, char *);
EXTERN ServiceInformation * getLocalService(char *);
EXTERN ServiceInformation * getRemoteService(char *);
EXTERN void deleteServiceInformation(DataSource *, char *);
EXTERN void deleteLocalService(char *);
EXTERN void deleteRemoteService(char *);
EXTERN void	freeServiceInformation(ServiceInformation *);
EXTERN void freeServices(DataSource *);
#undef	EXTERN

#ifdef _LIB_XML_OP
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int xmlchg(XmlDocument *, char *, int, char *);
EXTERN int xmladd(XmlDocument *, char *, char *);
EXTERN int xmldel(XmlDocument *, char *, int);
EXTERN int xmldelall(XmlDocument *, char *);
EXTERN int xmlget(XmlDocument *, char *, int, char *);
EXTERN int xmlnum(XmlDocument *, char *);
EXTERN XmlDocument * xmlalloc();
#undef	EXTERN

/* add app trace and errlog, modified by jek.yu 2003-8-18 */
#ifdef _LIB_ERRLOG
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int	usfTrace(char *, ...);
EXTERN int	usfTraceX(char *, ...);
EXTERN int	usfErrlog(char *, ...);
#undef	EXTERN

#ifdef _LIB_USF_DB_API_
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN void * openDll(char * lib_name, DllNode ** d_node);
#undef	EXTERN

/* �����궨�� */
#ifndef HIGH_WATER
#define HIGH_WATER        1        /* ��ˮλ */
#endif
#ifndef NORMAL_WATER
#define NORMAL_WATER        0        /* ����ˮλ */
#endif
#ifndef EMPTY_QUEUE
#define EMPTY_QUEUE        -1        /* �ն��� */
#endif

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

#define ERRLOG(errno, errmsg) {\
 xmlSetErrno(errno); \
 errlog("#%d-%s", errno, errmsg); }

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

#endif /* _HI_SERVER_H_ */
