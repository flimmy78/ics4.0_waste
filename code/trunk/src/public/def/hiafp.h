/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hiafp.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2003-05-10
 Description    : 报文格式转换头文件
 Others         : 无
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-05-10  LiangWJ     完成

******************************************************************************/
#ifndef	_H_HIXMLAFP_
#define	_H_HIXMLAFP_
#include	"hibase.h"
#include	"hiserver.h"
#include	"hidll.h"
#include	"hietf.h"
#include	"lib8583.h"
#include	"hilgr.h"


/* 定义长度 */
//modified by kixiong at 2009-2-13 14:59:17
//#define		MAX_TXN_CODE_LEN	20
//#define		MAX_SERVICE_LEN		20
#define		MAX_TXN_CODE_LEN	64
#define		MAX_SERVICE_LEN		64

#define		ERR_MSG_LEN			1024

#define		MAX_FIELD_LEN		51200
#define		NAMES_LEN			60
#define		MAX_HEAD_LEN_LEN	10
#define		MAX_KEY_LEN			50
#define		MAX_MSG_HEAD_LEN	1024
#define		MAX_DEPTH			100
/*added by kixiong*/
#define		PATH_LEN			1024
#define		FILENAME_LEN		512
#define		PASSWDLEN			512
#define		LOCATIONNAME_LEN	256

enum DataKind {
	DK_REQUEST_DATA = 1,
	DK_RESPONSE_DATA
};

/* 定义消息头保存记录的结构 */
struct _msg_head_rec {
	char * p_key;			/* 交易匹配的键值 */
	long head_len;			/* 消息头的长度 */
	char * p_head_buff;		/* 消息头的字符串 */
	long clock;				/* 消息头保存时间 */ 
	long timeout;			/* 消息头保存超时时间 */
};
typedef struct _msg_head_rec MsgHeadRec;

/* 定义接口配置信息 */
struct	_itf_info	{
	int				file_num;		/* 接口配置文件数 */
	char			** files;		/* 接口配置文件数组 */
	int				seq_no;			/* 接口配置序号 */
	XmlNode  		* curr_root;	/* 当前接口配置根节点 */
	XmlNode  		* bak_root;		/* 上次备份的配置根节点 */
	long			upd_clock;		/* 上次更新的时钟 */
};
typedef struct _itf_info ItfInf;

/* 定义动态库信息结构 */
struct	_dll_info	{
	XDllReg 		curr_list;		/* 当前动态库列表 */
	XDllReg 		bak_list;		/* 上次备份的动态库列表 */
	long			upd_clock;		/* 上次更新的时钟 */
};
typedef struct _dll_info DllInf;

/* 定义代码表的列信息 */
struct _code_tab_col_inf {
	char			name[NAMES_LEN+1];	/* 列名 */
	char			* def_val;			/* 缺省值 */
	QuickSearchList	* list;				/* 排序列表 */
};
typedef	struct _code_tab_col_inf CodeTabColInf;

/* 定义代码表的节点 */
struct _code_tab_node {
	char					name[NAMES_LEN+1];	/* 表名 */
	XmlNode					* root;				/* 代码表根节点 */
	CodeTabColInf			col_inf[2];			/* 列信息 */
	struct	_code_tab_node	* next;				/* 下一个节点 */
};
typedef	struct _code_tab_node CodeTabNode;

/* 定义代码表的配置信息 */
struct _code_tab_inf {
	CodeTabNode		* curr_head;	/* 当前的代码对照表头节点 */
	CodeTabNode		* bak_head;		/* 备份的代码对照表头节点 */ 
	long			upd_clock;		/* 上次的更新时钟 */
};
typedef	struct _code_tab_inf CodeTabInf;

/* 定义全局的配置信息结构 */
struct	_afp_config	{
	char			err_file[NAMES_LEN+1];	/* 错误日志文件 */
	char			trace_file[NAMES_LEN+1];/* 调试日志文件 */
	pthread_mutex_t	pub_lock;				/* 公共锁 */
	ItfInf			itf_inf;				/* 接口配置信息 */
	DllInf			dll_inf;				/* 动态库信息 */
	CodeTabInf		code_tab_inf;			/* 代码对照表信息 */
	MemoryPool 		* msg_head_mp;			/* 保存消息头的内存池 */
	/* Namespace declare node*/
	XmlNode			* ns_node;
};
typedef	struct _afp_config AfpConfig;

/* 定义可继承属性值的结构 */
struct	_heritable_attr {
	char	type[10+1];						/* 域定界符类型 */
	char	necessary[3+1];					/* 是否必需域 */
	char	len_type[10+1];					/* 前置长度数据类型 */
	char	head_len[MAX_HEAD_LEN_LEN+1];	/* 前置长度的长度 */
	char	include_len[3+1];				/* 是否包含前置长度的标志 */
	char	deli_asc[10+1];					/* 分隔符ASCII码 */
	char	deli_str[10+1];					/* 分隔字符串 */
	char	align_mode[5+1];				/* 域数据对齐方式(缺省为left) */
	char	fill_asc[10+1];					/* 填充ASCII码 */
};
typedef	struct _heritable_attr HeritableAttr;

/* 名称空间定义登记表 */
struct _ns_dec_rec {
	char * ns_alias;
	int have_declared;
	struct _ns_dec_rec * next;
};
typedef struct _ns_dec_rec NSDecRec;
int deleteNSDecRec(NSDecRec *rec);

struct _ns_dec_list {
	NSDecRec * list;
	NSDecRec * last;
};
typedef struct _ns_dec_list NSDecList;
int deleteNSDecList(NSDecList *declist);

/* 定义当前信息结构 */
struct	_curr_inf {
	char			svr_name[SVR_NAME_LEN+1];			/* 服务器名 */
	char			req_id[RQST_ID_LEN+1];				/* 消息请求编号 */
	char			txn_code[MAX_TXN_CODE_LEN+1];		/* 交易码 */
	char			server[SVR_NAME_LEN+1];				/* 目标服务器 */
	char			service[MAX_SERVICE_LEN+1];			/* 交易服务 */
	int				timeout;							/* 交易超时时间 */
	int				exist_txn_code;						/* 是否已存在交易码 */
	int				rq_or_rp;							/* 请求/应答标志 */
	int				convert_flag;						/* 报文格式转换标志 */
	int				err_no;                             /* 错误码 */
	char			err_msg[ERR_MSG_LEN+1];				/* 错误信息 */
	char			app_file[NAMES_LEN+1];				/* 应用日志文件 */
	char			err_file[NAMES_LEN+1];				/* 错误日志文件 */
	char			trace_file[NAMES_LEN+1];			/* 交易日志文件 */
	int				trace_flag;							/* 交易日志标志 */
	int				pass_flag;							/* 交易穿透标志 */
	char			* workdir;							/* 工作路径 */
	int				prev_retcode;						/* 上一步的返回码 */
	int				break_flag;							/* 中断标志 */
	AfpConfig		* afp_cfg;							/* 配置信息 */
	HeritableAttr	heritable_attr;						/* 可继承属性 */
	CodeTabNode		* code_tab_head;					/* 代码对照表头节点 */
	MemoryPool 		* msg_head_mp;						/* 保存消息头的内存池 */
	Message			* f_msg;							/* 第一个消息指针 */
	ETF				* data_root;						/* ETF根节点 */
	ETF				* curr_data_node;					/* ETF当前父节点 */
	XmlNode			* cfg_root;							/* 接口配置根节点 */
	XmlNode			* txn_node;							/* 交易接口配置节点 */
	XmlNode			* curr_cfg_node;					/* 当前配置节点 */
	int				sqn;                                /* 当前生成的节点计数*/
    XmlNode			* xmlDataTree;						/* XML报文树化后的根结点 */
    XmlNode			* xmlDataCurrNode;					/* xml报文当前节点 */
	NSDecList		* nsdeclist;
	Logger			* logger;							/* 日志器 */
	int				log_level;							/* 日志级别 */
};
typedef	struct _curr_inf CurrInf;

/* 定义变量 */
#ifdef	_XMLAFP_EXTERN_
#define	EXTERN extern
#else
#define	EXTERN
#endif
EXTERN AfpConfig	_Config;
EXTERN Field8583  _Field8583[129]; 
#undef	EXTERN

/* 函数声明 */
#ifdef	_LIB_HIXMLAFP_
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN XmlNode * getFirstConfigNode(XmlNode *);
EXTERN XmlNode * getNextConfigNode(XmlNode *);
EXTERN int getDelimiterType(CurrInf *);
EXTERN char * getDelimiterAsc(CurrInf *);
EXTERN char * getDelimiterStr(CurrInf *);
EXTERN void getHeritableAttr(CurrInf *);
EXTERN void * loadDllFunc(AfpConfig *, char *, char *);
EXTERN int pretreatData(CurrInf * p, char * in_data, int in_len, char ** out_data, int * out_len);
EXTERN int getTxnCode(CurrInf * p, char * data, int data_len); 	 
EXTERN int recvAllData(CurrInf * p, long timeout, char ** data, int * data_len);
EXTERN int getTranConfig(CurrInf * p, int seq_no);
EXTERN int unpackData(CurrInf * p, char * in_data, int in_len);
EXTERN int getItfRoot(CurrInf * p);
EXTERN int specialData(CurrInf * p, char * in_data, int in_len, char ** out_data, int * out_len);
EXTERN int packData(CurrInf * p, char ** out_data, int * out_len);
EXTERN int afpCreateTxnLogger(CurrInf * curr_inf);
#undef EXTERN
       
#ifdef _LIB_INIT_
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int createDataParser(AfpConfig *, int, char **);
EXTERN void freeDataParser(AfpConfig *);
EXTERN XmlNode * loadItfFiles(AfpConfig *, char *);
EXTERN int initCodeTabNode(CodeTabNode *);
EXTERN void freeCodeTabNode(CodeTabNode **);
EXTERN CodeTabNode * getCodeTabNode(CodeTabNode *, char *);
EXTERN CodeTabNode * loadCodeTable(XmlNode *, char *);

EXTERN MemoryPool * createMsgHeadMemoryPool(AfpConfig *);
EXTERN void	initCurrInf(CurrInf *, AfpConfig *);
EXTERN void	freeNouseMemory(AfpConfig *);
EXTERN int errorProcess(CurrInf *);
EXTERN int AFP_ERRLOG(CurrInf *, char *fmt, ...);
EXTERN int AFP_DEBUG(CurrInf *, char *fmt, ...);
EXTERN int AFP_TRACE(CurrInf *, char *fmt, ...);
EXTERN int AFP_APPLOG(CurrInf *, char *fmt, ...);
EXTERN int AFP_DUMP(CurrInf *);

EXTERN void setCurrInf(CurrInf * p, AfpConfig * afp_cfg);
#undef	EXTERN

#ifdef	_LIB_ONLINE_
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int putManageMsgResponse(Message *, XmlNode *, char *, char *);
EXTERN int logSwitch(Message *, XmlNode *, int);
EXTERN int monSwitch(Message *, XmlNode *, int);
EXTERN int tranSwitch(Message *, XmlNode *, int);
EXTERN int qryTranStatus(Message *, XmlNode *);
EXTERN int reloadItfConfig(Message *);
EXTERN int reloadDllLib(Message *);
EXTERN int reloadCodeTable(Message *);
EXTERN int onlineUpdateCtrl(Message * msg);
#undef	EXTERN

#ifdef	_APP_OP_
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int afpInit(AfpConfig *, XmlNode *, char *, char *);
EXTERN void afpClose(AfpConfig *);
EXTERN int afpUnpackData(AfpConfig *, Logger *, XmlNode *, XmlNode *, char *, int, ETF **);
EXTERN int afpPackData(AfpConfig *, Logger *, XmlNode *, XmlNode *, ETF *, char **, int *);
EXTERN int afpUnpackXmlData(AfpConfig *, XmlNode *, XmlNode *, char *, int, ETF **);
EXTERN int afpPackXmlData(AfpConfig *, XmlNode *, XmlNode *, ETF *, char **, int *);
EXTERN int afpConvertFileFormat(char *, char *, char *, char *, char *);
EXTERN int afpConvertDataFormat(AfpConfig *, XmlNode *, XmlNode *, XmlNode *, char *, int, char **, int *);
#undef	EXTERN


#endif /* _H_HIAFP_ */

/********************************  The End  ***********************************/
