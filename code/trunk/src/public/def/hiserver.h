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

#define	TRACE_OFF	   0    /* 调试日志关闭状态 */
#define	TRACE_ON	   1    /* 调试日志打开状态 */

#define NAMES_LEN      60   /* 名字的长度 */
#define PRIORITYS      5    /* 优先级别数 */
#define RQST_ID_LEN    20   /* 请求编号长 */
#define MSG_TYPE_LEN   6    /* 消息类型长 */
#define FLD_NAME_LEN   3    /* 消息头属性名字之长度 */
#define SVR_ADDR_LEN   15   /* 服务器地址长度 */
#define SVR_NAME_LEN   8    /* 服务器名字长度 */
#define SVR_ID_LEN     6    /* 服务器ID长度 */
#define SVR_TYPE_LEN   3    /* 服务器类型长度 */
#define POS_ID_LEN     4    /* 线索信息存放位置长度 */
#define MSG_ID_LEN     4    /* 消息ID长度 */
#define MAX_QPAIR_NUM  5    /* 一个服务器可以配置的最多Q-Pair数 */

#include "hidbdsc.h"
#include "hiusfdbapi.h"
#include "hidatabase.h"

/* 记录线索ID的接点 */
struct _thread_id_node {
    short     cancel_flg;           /* 线索是否被取消 */
    pthread_t tid;                  /* 线索号 */
    struct _thread_id_node * next;  /* 指向下一接点的指针 */
};
typedef struct _thread_id_node ThreadIdNode;

/* 记录所有的线索ID */
struct _thread_id_rec {
    short total;              /* 接点数目 */
    ThreadIdNode * head;      /* 链表头指针 */
    ThreadIdNode * tail;      /* 链表尾指针 */
    pthread_mutex_t id_lock;  /* 访问链表的锁 */
};
typedef struct _thread_id_rec ThreadIdRec;

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

/* 同步请求登记链表 */
struct _syn_request_node {
    short           qpair_id;                  /* 同步请求目标Q-Pair */
    short           slot_id;                   /* 请求编号 */
    char            request_id[RQST_ID_LEN+1]; /* 请求编号 */
    long            bgn_exist_time;            /* 进入链表的时间 */
    Message *       response_msg;              /* 应答消息(即返回的包) */
    pthread_mutex_t notify_lock;               /* 通知锁 - 配合条件变量使用 */
    pthread_cond_t  notify_cond;               /* 通知用条件变量 */
};
typedef struct _syn_request_node SynRequestNode;

/* 消息缓存链表 */
struct _msg_cache_node {
    Message * q_msg;                /* 子消息 */
    struct _msg_cache_node * next;  /* 指向下一个子消息的指针 */
};
typedef struct _msg_cache_node MsgCacheNode;

/* 大消息登记链表 */
struct _big_msg_node {
    char            msg_type[MSG_TYPE_LEN+1];   /* 消息类型 */
    char            request_id[RQST_ID_LEN+1];  /* 请求编号 */
    MsgCacheNode *  msg_link_head;              /* 消息缓存链表头 */
    pthread_mutex_t msg_link_lock;              /* 对消息缓存链表的锁 */
    pthread_cond_t  notify_cond;                /* 通知用条件变量 */
    long            bgn_exist_time;             /* 进入链表的时间 */
};
typedef struct _big_msg_node BigMsgNode;

/* 消息-任务模块对照表接点 */
struct _msg_task_node {
    char msg_type[MSG_TYPE_LEN+1];  /* 消息类型 */
    char p_module[NAMES_LEN+1];     /* 任务模块名字 */
    int (* p_task)(Message *);      /* 任务模块的函数指针 */
    struct _msg_task_node * next;   /* 指向下一接点的指针 */
};
typedef struct _msg_task_node MsgTaskNode;

/* Queue */
struct _queue {
    pthread_t       deliver_tid;                /* 请求队列的分发者线索的ID */
    short           q_high_water;               /* 高水位 */
    short           q_low_water;                /* 低水位 */
    short           q_max_length;               /* 最大队列长度 */
    short           max_serv_worker;            /* 最大服务于该队列的工作者数 */
    short           serving_worker;             /* 正服务于该队列的工作者数 */
    Message **      msg_q[PRIORITYS];           /* 消息队列 */
    short           q_queue_head[PRIORITYS];    /* 队列头 */
    short           q_queue_tail[PRIORITYS];    /* 队列尾 */
    short           q_curr_length[PRIORITYS];   /* 当前队列长度 */
    short           q_water_flag[PRIORITYS];    /* 队列水位标志 */
    short           q_de_priority[PRIORITYS];   /* 队列出队个数-控制优先处理 */
    pthread_mutex_t en_de_lock;                 /* 出队入对锁 */
    pthread_cond_t  en_notify_cond[PRIORITYS];  /* 通知写用条件变量 */
    pthread_cond_t  de_notify_cond;             /* 通知读用条件变量 */
    MemoryPool *    big_msg_list;               /* 大消息登记链表 */
    pthread_mutex_t big_msg_lock;               /* 大消息登记链表读锁 */
    MsgTaskNode *   msg_tasks;                  /* 服务于该队列的任务模块 */
    pthread_mutex_t msg_tasks_lock;             /* 任务模块链表写锁 */
    char            default_module[NAMES_LEN+1];/* 默认执行模块名字 */
    int (* default_task)(Message *);            /* 默认执行模块 */
    pthread_mutex_t xxx_lock;                   /* 出队入对锁 */
    pthread_cond_t  xxx_cond;                   /* 通知写用条件变量 */
};
typedef struct _queue Queue;

/* Q-Pair */
struct _queue_pair {
    short           qpair_id;                 /* Q-Pair的ID */
    char            qpair_name[NAMES_LEN+1];  /* Q-Pair名字 */
    Queue           request_q;                /* 请求队列 */
    Queue           response_q;               /* 应答队列 */
    MemoryPool *    syn_request_list;         /* 同步请求登记 */
    pthread_mutex_t syn_list_lock;            /* 访问同步请求登记表的锁 */
};
typedef struct _queue_pair QueuePair;

/* 队列别名 */
struct _queue_alias {
    short qpair_id;                 /* Q-Pair编号 */
    char  qpair_name[NAMES_LEN+1];  /* Q-Pair名字 */
    short queue_type;               /* 队列类型 */
};
typedef struct _queue_alias QueueAlias;

/* 动态库登记表 */
struct _dll_node {
    char   lib_name[NAMES_LEN+1];  /* 库名称 */
    void * lib_handle;             /* 库访问句柄 */
    void (* donefunc)();           /* 库关闭时执行的函数 */
    struct _dll_node * next;       /* 指向下一个接点指针 */
};
typedef struct _dll_node DllNode;

/* 工作线索登记表 */
struct _worker_thread_rec {
    pthread_t       worker_tid;              /* 工作线索的线索ID */
    Message *       processed_msg;           /* 任务模块要处理的消息 */
    QueueAlias *    calling_qpair;           /* 调用自己的Q-Pair别名 */
    long            bgn_exec_time;           /* 开始执行时间 */
    char *          executing_module;        /* 正在执行的模块的名字 */
    DBConnRec       * using_db_conn; 		 /* 使用过的数据库连接号 */  
    DBConnRec       * curr_db_conn; 		 /* 当前正在使用的数据库连接号 */       
    short           cleaner_num;             /* 在栈中的清理函数数目 */
    pthread_mutex_t notify_lock;             /* 线索等候工作指令的锁 */
    pthread_cond_t  notify_cond;             /* 线索等候工作指令的条件变量 */
};
typedef struct _worker_thread_rec  WorkerThreadRec;

/* 线索池管理结构 */
struct _thread_pool_rec {
    pthread_t manager_tid;       /* 池管理者线索的线索ID */
    short     min_thread_num;    /* 要启动的最少工作线索数 */
    short     max_thread_num;    /* 线索池中可管理的最大线索数 */
    short     curr_thread_num;   /* 当前池中线索数 */
    short     busy_thread_num;   /* 忙的线索数 */
    short     allot_policy;      /* 线索分配政策 */
    short     polling_time;      /* 每次轮询的时间间隔 */
    short     tuning_or_not;     /* 是否动态调整池中线索数 */
    short     high_load_level;   /* 高负荷标准 */
    short     high_load_point;   /* 高负荷 */
    short     high_load_times;   /* 高负荷维持了多少个轮询时间 */
    short     low_load_level;    /* 低负荷标准 */
    short     low_load_point;    /* 低负荷 */
    short     low_load_times;    /* 低负荷维持了多少个轮询时间 */
    short     start_thread_step; /* 每次启动多少个线索 */
    short     stop_thread_step;  /* 每次停止多少个线索 */
    short     be_tuned_num;      /* 调整次数 */
};
typedef struct _thread_pool_rec ThreadPoolRec;

/* 空闲工作线索登记表 */
struct _idler_thread_rec {
    short           first_idler;  /* 第一个空闲的工作线索在数组中位置 */
    short           last_idler;   /* 最后一个空闲的工作线索在数组中位置 */
    short *         idler_list;   /* 空闲线索的记录号数组 */
    pthread_mutex_t idler_lock;   /* 访问锁 */
    pthread_cond_t  idler_cond;   /* 条件变量 - 用于都忙时等待 */
};
typedef struct _idler_thread_rec IdlerThreadRec;

/* 空位置登记表 */
struct _empty_pos_rec {
        short    first_pos;  /* 第一个空位置 */
        short    last_pos;   /* 最后一个空位置 */
        short *  pos_list;   /* 空位置登记表 */
};
typedef struct _empty_pos_rec EmptyPosRec;

/* 线索相关数据 */
struct _thread_spec_data {
        short worker_id;
        short qpair_id;
        short queue_type;
};
typedef struct _thread_spec_data ThreadSpecData;

struct _pub_runtime_env_rec {
        char               svr_addr[SVR_ADDR_LEN+1];  /* IP address */
        char               svr_name[SVR_NAME_LEN+1];  /* 服务器名字 */
        char               svr_type[SVR_TYPE_LEN+1];  /* 服务器类型 */
        short              svr_id;                    /* 服务器ID */
        QueuePair **       qarray;                    /* Q-Pair数组 */
        short              q_num;                     /* Q-Pair数 */
        long               seq_no;                    /* 请求编号的序列号 */
        pthread_mutex_t    seq_lock;                  /* 序列号的锁 */
        long               clock;                     /* 时钟记数 */
        pthread_mutex_t    clock_lock;                /* 时钟锁 */
        pthread_cond_t     clock_cond;                /* 时钟条件变量 */
        long               tr_count;                  /* 已发生的交易数 */
        short *            cancel_flags;              /* 取消标志 */
        short *            busy_flags;                /* 忙标志 */
        pthread_mutex_t    cancel_lock;               /* 取消标志访问锁 */
        long               max_timeout;               /* 交易最大超时时间 */
        ThreadPoolRec      tpool;                     /* 线索池属性 */
        WorkerThreadRec ** tworkers;                  /* 工作线索 */
        IdlerThreadRec     tidlers;                   /* 空闲线索登记 */
        long               portal;                    /* 核心公共端口 */
        short              is_closing;                /* 是否正在关闭 */
		char *             workdir;                   /* 工作路径环境变量 */
		int                log_flag;                  /* 日志开关标志 */
		char			   syslog_file[NAMES_LEN+1];  /* 服务器调试日志文件 */
		char			   errlog_file[NAMES_LEN+1];  /* 服务器错误日志文件 */
		XmlNode *          region_node;               /* 基本配置信息 */
		/* 
		 * 平台升级改造 
		 * Added by liangwj at 2008-11-03
		 */
		char			   ap_name[SVR_NAME_LEN+1];	  /* 应用名 */
		LoggerMessage	*  logger_msg;				  /* 日志信息 */
		Logger 			*  sys_logger;				  /* 系统日志器 */
		Logger 			*  trc_logger;				  /* 调试日志器 */
		Logger 			*  err_logger;				  /* 错误日志器 */
};
typedef struct _pub_runtime_env_rec PubRuntimeEnvRec;

/*
 * Queue信息
 * Added by liangwj at 2006-10-30
 */
typedef struct _QueueInformation{
	long	ServingNum;
	long	QueueNum[PRIORITYS];
}QueueInformation;

/*
 * QueuePair信息
 * Added by liangwj at 2006-10-30
 */
typedef struct _QPairInformation{
	QueueInformation	Request;
	QueueInformation	Response;	
}QPairInformation;

/*
 * 服务容器信息
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
 * 服务报文接口定义
 * Added by liangwj at 2006-10-30
 */
typedef struct _InterfaceDefine{
	char 					* Name;	
	struct _InterfaceDefine	* Next;
}InterfaceDefine;


/*
 * 组件执行统计信息
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
 * 服务信息
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
	 *组件统计信息
	 */
	hash_t			* comps_ctx_info;
}ServiceInformation;

/*
 * 全局信息
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

/* 全局变量 */
#ifndef SERVER_EXTERN
#define SERVER_EXTERN
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN PubRuntimeEnvRec * _PubRuntimeEnv;    /* 服务器运行环境 */
EXTERN EmptyPosRec        _EmptyPosReg;      /* 空位置登记 */
EXTERN pthread_key_t *    _CallingQPair;     /* 调用该模块的Q-Pair */
EXTERN pthread_attr_t     _ThreadAttr;
EXTERN XmlDocument *      _DomTreeRootNode;  /* 配置文件DOM树的根结点 */
EXTERN XmlNode *          _RegionNode;       /* 域节点 */
EXTERN XmlNode *          _ServerNode;       /* 服务器节点 */
EXTERN DllNode *          _DllOpenRegList;   /* 打开的动态库句柄列表 */
EXTERN ThreadIdRec        _ThreadIdList;     /* 线索ID的记录 */
EXTERN DataSourceContainer *   _DBConnectionPool; /* 数据库连接池 */
/*
 * 全局信息
 * Added by liangwj at 2006-10-30
 */
EXTERN GlobalInformation * _GlobalInf;    /* 服务器运行环境 */
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

/* 公共宏定义 */
#ifndef HIGH_WATER
#define HIGH_WATER        1        /* 高水位 */
#endif
#ifndef NORMAL_WATER
#define NORMAL_WATER        0        /* 正常水位 */
#endif
#ifndef EMPTY_QUEUE
#define EMPTY_QUEUE        -1        /* 空队列 */
#endif

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
