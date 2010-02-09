/******************************************************************************

				Copyright (C),1998-2005,Hisuntech Co.,Ltd.

 File name		: hionline.h
 Author			: Chen Yinggang
 Version		: 1.0
 Date			: 2003-03-28
 Description	: 联机交易主控头文件
 Others			: 
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2003-3-28	CYG 		完成
  002	2007-6-5	LiangWJ 	支持指定组件输出区功能，修改TranData结构。
  003	2007-6-28	LiangWJ 	修改TranData结构，增加系统错误标志
  004	2007-8-27	LiangWJ 	去掉业务代码，同一个应用主控支持装载多个CTL

******************************************************************************/
#ifndef  _HI_ONLINE_H
#define  _HI_ONLINE_H


#include <math.h>
#include "hiserver.h"
#include "hidll.h"
#include "hibppubdef.h"
#include "hietf.h"
#include "hipex.h"
#include "hidsm.h"
#include "hipra.h"
#include "hash.h"
#include "hilgr.h"
#include "hash.h"

/*动态查询语句结构*/
struct _txn_condition {
	char 	txn_cod[MAX_SERVICE_NAME_LEN + 1];
	char 	con_cod[CONCOD_LEN + 1];
	char *	query;
	char *	fields;
	struct 	_txn_condition * next;
};
typedef struct _txn_condition TxnCondition;

/*公共信息表项结构*/
struct _pb_item_data {
	char 	** 	data;
	char 	** 	item_name;
	int	 	*	size;
	int			item_num;
};

typedef struct _pb_item_data  PbItemData;

/* 应用配置文件信息结构 */
struct _cfg_define_rec {
	//name为文件的绝对路径
	//配置文件的别名由PubDefRec来对照
	char    * 	name;
	XmlNode *	node;
	/*
	 * 支持个性配置文件
	 * Added by liangwj at 2006-11-27
	 */
	int			type;
	void	*	pointer;
	void (* done_func)(void *);
};
typedef struct _cfg_define_rec CfgDefineRec;

/*
 * 函数节点
 * Added by liangwj at 2006-01-10
 * 增加输入输出,Modified by liangwj at 2007-3-16
 */
struct _function_node {
	char 			* name;				/* 函数名 */
	InterfaceDefine	* input;			/* 输入接口 */
	InterfaceDefine	* output;			/* 输出接口 */
	TxnCondition	* sentence_head;	/* 首动态语句 */
	XmlNode			* process;			/* 函数步骤 */
	//deleted by kixiong at 2008-12-4 15:50:18
	//package优化改造
	//struct 	_function_node * next;		/* 下一个函数 */
};
typedef struct _function_node FunctionNode;
 
/*
 * 程序包节点
 * Added by liangwj at 2006-01-10
 */
struct _package_node {
	/*
	 * deleted by kixiong at 2008-12-4 15:43:43
	 * package 优化改造
	char 			* serv_name;		// 应用名 
	Added by liangwj at 2007-8-27
	char 			* serv_sqn;		    // 应用程序序号
	char 			* name;				// 程序包名 
	FunctionNode	* func_head;		// 程序包首函数节点
	struct 	_package_node * next;		// 下一个程序包 
	*/
	
	int			  free_flag;			// 是否需要释放根节点 
	char          * filename;			/* 文件名名(绝对路径) */
	XmlNode		  * pkg_root;			/* 程序包根节点 */

	//added by kixiong at 2008-12-4 15:46:47
	short		  	cfgdef_num;
	short			busdef_num;
	short			pkgdef_num;
	PubDefineRec  * cfgdefmsg;			//配置文件与实际的文件名的对照
	LibDefineRec  * librarymsg;			//库别名和实际的库和函数的对照
	PubDefineRec  * busdefmsg;			//应用
	PubDefineRec  * pkgdefmsg;			//包别名和实际包的对照
	hash_t			* func_container;  //程序包中的函数容器
};
typedef struct _package_node PackageNode;

/* 服务配置信息结构 */
struct _serv_config_msg {
	char     		serv_name[SERV_NAME_LEN+1];
	char     		serv_code[SERV_CODE_LEN+1];
	char     		list_tbl[TBLNAM_LEN+1];
	char	 		errlog_nam [LOG_NAME_LEN+1];				/*错误日志名*/
	char	 		trclog_nam [LOG_NAME_LEN+1];				/*调试日志名*/
	short    		serv_permit_flag;
	short	 		trace_flag;
	short	 		cfgdef_num;
	short	 		busdef_num;
	/* 增加前端调试的IP和PORT add by liangwj in 2004-02-16 */
	char			trace_ip[IPADR_LEN+1];						/*前端调试机器IP*/
	int				trace_port;									/*前端调试端口*/
	//modified by kixiong at 2008-12-4 15:56:11
	//Package优化
	//CfgDefineRec  * cfgdefmsg;
	PubDefineRec  * cfgdefmsg; //配置文件别名和实际文件名的对照
	LibDefineRec  * librarymsg;
	PubDefineRec  * busdefmsg;
	/* 
	 * Package定义信息 
	 * Added by liangwj at 2006-01-09 
	 */
	short			pkgdef_num;
	PubDefineRec  * pkgdefmsg;
};
typedef struct _serv_config_msg ServConfigMsg;

/*冲正、重发属性*/
struct _reltran_atr {
	char    txn_cod[MAX_SERVICE_NAME_LEN+1];			/*交易码*/
	char	interval[INTERVAL_LEN + 1];		/*轮询间隔时间*/
	char	time_out[TIMEOUT_LEN + 1];		/*超时时间*/
	char	max_times[MAXTIMES_LEN + 1];	/*最大次数*/
	char	obj_svr[SVRNAM_LEN + 1];			/*目标服务器*/
};
typedef struct _reltran_atr RelTranAtr;

/* 交易配置结构 */
struct _tran_config_rec {
	ServConfigMsg	* 	serv_msg;
	char     			txn_cod[MAX_SERVICE_NAME_LEN+1];
	RelTranAtr 			integrity_atr;
	short    			tran_permit_flag;
	char     			attribute[ATTRIBUTE_LEN+1];
	short	 			trace_flag;
	int      			tran_step_num;
	/* 增加前端调试的socket描述符 add by liangwj in 2004-02-16 */
	int					trace_sockfd;
	TxnCondition 	*	txn_cond;
	XmlNode			*	tran_step;
	/*
	 * 交易首函数节点
	 * Added by liangwj at 2006-01-09 
	 */
	//modified by kixiong at 2008-12-4 21:41:06
	//FunctionNode	* 	func_head;
	PackageNode		*	tran_pkg;
};
typedef struct _tran_config_rec TranConfigRec;

/*交易属性结构*/
struct _tranattrpos {
   char 	attr_name[ATTRNAME_LEN + 1];
   char 	pos[FLAG_LEN + 1];
   struct 	_tranattrpos * next;
};
typedef struct _tranattrpos TranAttrPos;

/*平台公共系统信息结构*/
struct _tran_pub_env {
	int              	serv_num;
	int              	tran_num;
	char	 			act_dat [DATE_LEN  + 1];
	char	 			sys_id [SYSID_LEN  + 1];
	char				sys_err_log[LOG_NAME_LEN+1];
	char				sys_trc_log[LOG_NAME_LEN+1];
	short				sys_trc_flag;
	XmlDocument    **	con_root_node;
	XmlNode    		*	sys_cfg;
	XmlNode    		*	bus_cfg;
	ServConfigMsg 	*	aps_con_msg;
	TranConfigRec 	*	tran_con_rec;
	TranAttrPos		* 	tran_attr_pos;
	XmlNode		 	*	trlst_cols_nods;
	XmlNode		 	*	table_cols_nods;
	XDllReg				PartDLLs;
	/* Added by liangwj at 2006-01-10 
	 * modified by kixiong at 2008-12-4 15:38:49
	PackageNode		*	external_pkg;
	PackageNode		*	inner_pkg;
	*/
	hash_t			*	external_pkg;
	hash_t			*	inner_pkg;
	hash_t			*	cfg_container;	//配置文件容器
	
	SystemParaSpace	*	para_space;
	
	/*added by kixiong at 2008-10-20 15:26*/
	short				statistics_switch;	/*信息统计开关*/
	pthread_rwlock_t	switch_lock;		/*开关锁*/
	
	/*added by liangwj at 2008-11-20 16:28*/
	LoggerMessage	* 	logger_msg;			/*日志信息管理器*/
};

typedef struct _tran_pub_env TranPubEnv;

struct _serv_env {
	TranPubEnv   * _PubEnvCurr;
	TranPubEnv   * _PubEnvBak;
};

typedef struct _serv_env ServEnv;

struct _pri_item {
	void			 *	data;
	char			 	name[PRI_ITEM_NAME_LEN +1];
	int				 	size;
	struct _pri_item *	next_item;
};

typedef struct _pri_item PriItemNode;

struct _pri_item_data {
	PriItemNode		*	item;
	PriItemNode		*	last_item;
	int					item_num;
};

typedef struct _pri_item_data  PriItemData;

/*
 * added by kixiong at 2008-11-14 10:54
 * 数据源打开的游标序号管理
 */
struct _connection_cursor_index {
	short	ds_id;						 /*数据源ID*/
	char	cursor_seq[MAX_OPEN_CURSOR]; /* 打开的游标序号 */
};
typedef struct _connection_cursor_index ConnectionCursorIndex;

/*交易信息结构*/
struct _tran_data {
	int						ret_cod;						/* 原子函数返回值 */
	char					sys_id [SYSID_LEN + 1];			/* 系统标识号     */
	char					req_id [RQST_ID_LEN + 1];		/* 交易跟踪号     */
	char					svr_name [SVRNAM_LEN +1];		/* 服务器名       */
	char				  *	bus_name;						/* 业务名         */
	char					log_no[LOGNO_LEN+1];			/* 前置流水号     */
	char					act_dat[DATE_LEN+1];			/* 会计日期       */
	char				  errlog_nam[LOG_NAME_LEN+1];		/* 交易错误日志名 */
	char				  trclog_nam[LOG_NAME_LEN+1];		/* 交易调试日志名 */
	char				  *	txn_cod;						/* 交易码         */
	char				  *	list_tbl;						/* 应用流水表名   */
	char				  *	attribute;						/* 交易属性       */
	char				  	run_status[RUN_STATUS_LEN+1];	/* 交易运行状态   */
	short					trace_flag;						/* 调试日志开关   */
	Message				  *	in_msg;							/* 消息           */
	XmlNode		 		  *	trlst_cols_nods;				/* 流水表结构树   */
	XmlNode		 		  *	table_cols_nods;				/* 业务表结构树   */
	RelTranAtr			  *	integrity_atr;					/* 完整性交易属性 */
	ServConfigMsg	 	  * serv_msg;						/* 服务定义信息   */
	TranPubEnv   		  * pub_env;						/* 全局公共信息   */
	struct _pb_item_data	bus_def;						/* 自定义信息     */
	struct _pb_item_data	txn_jnl;						/* 流水表         */
	DataSource				*data_source;					/* 应用数据源     */
	TranParaSpace		  * para_space;	    			    /* 参数空间 */
	ETF					  * input_etf;			     		/* 当前输入ETF    */
	ETF					  * output_etf;				    	/* 当前输出ETF    */
	char				  output_area[20+1];				/* 当前输出区名称 */
	int					  sys_err_flag;						/* 系统错误标志 */
	int					  add_msg_flag;						/* 添加信息标志 */
	/*added by kixiong at 2008-10-20 15:34 */
	hash_t				  * comp_ctx_info;					/* 组件统计信息*/
	/*added by kixiong at 2008-10-20 15:26*/
	short				  statistics_switch;				/* 信息统计开关*/
	
	struct timeval		  start_time;						/* 交易开始时间*/
	struct timeval		  dead_time;						/* 交易截至时间*/
	ConnectionCursorIndex conn_cursor[MAX_OPEN_CONN];		/* 打开的游标序号 */
	
	/*added by liangwj at 2008-11-20 16:38*/
	Logger				* logger;							/* 交易日志器 */
	int					  log_level;						/* 日志级别 */
};

typedef struct _tran_data TranData;

/* 交易信息结构 */
struct _tran_inf_rec {
	TranConfigRec	*	txn_config;
	ETF				*	in_node;
	TranData		*	trdata;
	DBConHandle		*	db_hndl;
	XmlNode			*	head_node;
	XmlNode			*	curr_node;
	char			*	goto_label;
	char     		default_errdll_file[DLL_FILE_NAME_LEN+1];
	char     		default_errfunc_name[FUNC_NAME_LEN+1];
	char     		errdll_file[DLL_FILE_NAME_LEN+1];
	char     		errfunc_name[FUNC_NAME_LEN+1];
	int				break_flag;
	int				ret_cod;
	/*
	 * 当前Package名字
	 * Added by liangwj at 2006-01-24 
	 */
	//modified by kixiong at 2008-12-4 20:11:17
	//char			* 	pkg_name;
	PackageNode		*	curr_pkg;			//当前Package
	
	//added by kixiong at 2008-12-4 16:16:25
	//Package优化
	PubDefineRec  * curr_cfgdefmsg;			//当前配置文件与实际的文件名的对照
	LibDefineRec  * curr_librarymsg;		//当前库别名和实际的库和函数的对照
	PubDefineRec  * curr_busdefmsg;			//当前应用
	PubDefineRec  * curr_pkgdefmsg;			//当前包别名和实际包的对照
};
typedef struct _tran_inf_rec TranInfRec;

struct _obj_msg
{
	char NodNo[NODNO_LEN+1];
	char TlrNo[MSGTLRID_LEN+1];
	struct 	_obj_msg * next;
};
typedef struct _obj_msg ObjMsg;

/*InformMessage*/
/*
 * 增加本地文件名LclFil
 * Added by liangwj at 2006-03-21
 */
typedef	struct
{
	char  MsgTyp[FLAG_LEN  + 1];		/*消息类型1通知;2广播;3文件;4打印*/		
	char  BusTyp[MSGBUSTYP_LEN  + 1];	/*应用类型                       */		
	char  AplCod[MSGAPLCOD_LEN  + 1];	/*应用代码                       */
	char  FilNam[MSGFILNAM_LEN  + 1];	/*文件名                         */		
	char  LclFil[MSGFILNAM_LEN  + 1];	/*本地文件名                     */		
	char  MsgSmr[MSGFILNAM_LEN  + 1];	/*消息摘要                       */		
	char  HLogNo[MSGHLOGNO_LEN  + 1];	/*主机流水号,前置创建消息无用    */		
	char  OrgNo[MSGORGNO_LEN  + 1];		/*发起交易机构代码               */		
	char  TlrId[MSGTLRID_LEN  + 1];		/*发起交易柜员代码               */		
	char  BgnDat[DATE_LEN  + 1];		/*发起交易日期                   */		
	char  BgnTm[TIME_LEN  + 1];			/*发起交易时间                   */		
	char  EprDat[DATE_LEN  + 1];		/*失效日期   	                 */		
	char  EprTm[TIME_LEN  + 1];			/*失效时间                       */		
	char  ProFlg[FLAG_LEN  + 1];		/*失效后续处理标志0 删除 1送监控 */		
	char  Data[MSGDATA_LEN  + 1];		/*应用数据区                     */		
	int   RecNum;						/*接收目的数                     */		
	ObjMsg * obj_msg;	 				/*目的网点、目的柜员             */
} InformMessage;

#ifdef BPNOEXTERN

ServEnv	    * _ServEnv;

/* 
 * 增加下面的变量实现动态更新功能 
 * Added by liangwj in 20051202
 */
int					_Argc;
char				** _Argv;
pthread_rwlock_t	_UpdateRWLock;

#else  /* BPNOEXTERN */

extern ServEnv	    * _ServEnv;
extern XmlNode	* 	_TrTabCfg;	/*应用流水表字典*/

/* 增加下面的变量实现动态更新功能 */
extern int			_Argc;
extern char			** _Argv;
extern pthread_rwlock_t	_UpdateRWLock;

#endif /* BPNOEXTERN */


#endif /* _HI_ONLINE_H */

void * get_dll_handle( TranPubEnv *, char * );
void * get_dll_handle_all( TranPubEnv *, char * );

#ifdef	_LIB_BPONLBS_
#define	EXTERN
#else
#define	EXTERN	extern
#endif /* _LIB_BPONLBS_ */

EXTERN void free_pointer_array(char **, int);
EXTERN char **names_parser(char *, char, int *);
EXTERN char **separate_names(char *, char);
EXTERN char *findRealNameByAlias(ETF *, TranData *, char *);
EXTERN int bpGetRealValue(char *, char *, TranData *, ETF *);
EXTERN int bpGetArgument(PbItemData, char *, char *, int);
/* 
 * 以下两个函数为新增接口
 * Added by liangwj in 20041026
 */
EXTERN char * bpReturnArgument(PbItemData, char *, int *);
EXTERN char * bpReturnChildValue(ETF *, char *, int *);
/* 
 * 以下两个函数为新增接口
 * Added by liangwj at 2006-01-11
 * Modified by liangwj at 2007-8-27
 */
//EXTERN PackageNode * findPackageNode(PackageNode *, char *, char *, char *);
//EXTERN FunctionNode * findFunctionNode(FunctionNode *, char *);
EXTERN PackageNode * findPackageNode(TranPubEnv * env, TranInfRec * ctx, char *pkg_name);
EXTERN FunctionNode * findFunctionNode(PackageNode * pkg, char * name);
#undef	EXTERN

#ifdef	_LIB_BPTRANDATA_
#define	EXTERN
#else
#define	EXTERN	extern
#endif /* _LIB_HIBPTRANDATA_ */

EXTERN void bpFreeMem(void *);
EXTERN void bpFreeMsg(void *);
EXTERN void bpFreeEtf(void *);
EXTERN void bpFreeXml(void *);

EXTERN int bpAddNamedData(TranData *, char *, char *, char *, int, int);
EXTERN int bpGetNamedData(TranData *, char *, char *, char *, int);
EXTERN void bpDelNamedData(TranData *, char *, char *);

EXTERN int bpAddBasData(TranData *, char *, char *, int, int);
EXTERN int bpGetBasData(TranData *, char *, char *, int);
EXTERN void bpDelBasData(TranData *, char *);

EXTERN int bpAddEtfData(TranData *, char *, char *, int);
EXTERN int bpGetEtfData(TranData *, char *, char *, int);
EXTERN void bpDelEtfData(TranData *, char *);

EXTERN int bpAddMsgHead(TranData *, char *, char *, int);
EXTERN int bpGetMsgHead(TranData *, char *, char *, int);
EXTERN void bpDelMsgHead(TranData *, char *);

EXTERN int bpAddAliasData(TranData *, char *, char *, int, int);
EXTERN int bpGetAliasData(TranData *, char *, char *, int);
EXTERN int bpDelAliasData(TranData *, char *);

EXTERN int bpAddDataSource(TranData *, char *, int, void **, int, void (*)(void *));
EXTERN int bpSetDataSource(TranData *, char *, int, void **, int, void (*)(void *));
EXTERN int bpGetDataSource(TranData *, char *, void **);
EXTERN void bpDelDataSource(TranData *, char *);

EXTERN int bpAddData(TranData *, char *, char *, char *, int, int);
EXTERN int bpGetData(TranData *, char *, char *, char *, int);
EXTERN int bpDelData(TranData *, char *, char *);

EXTERN XmlNode * bpGetConfigRootNode(TranData *, char *, char *);
EXTERN XmlNode * bpGetConfigNodeByAttr(TranData *, char *, char *, char *, char *);
EXTERN int bpDump(TranData *);

/*added by kixiong at 2008-11-3 15:59*/
EXTERN int	bpQueryRec(DBConHandle *handle, \
						char * aSqlCmd, 	\
						int  pairs,			\
						char * name, 		\
						char * value, 		\
						long maxlen,		\
						...);
#undef	EXTERN

/*设置数据库上下文*/
int bpSetDBContext(DBConHandle *);
/*取ETF节点，如果节点不存在或长度为0，则返回-1*/
int bpGetChildValue( ETF *, char *, char *, int );
/*记录错误代码和错误信息*/
int	bpAddResult(ETF *, char *, char * );
/*记录调试日志*/
int bpTraceLog( TranData *, char *, ...);
/*记录错误日志*/
int bpErrorLog( TranData *, char *, ...);
/*根据查询语句名组织查询语句*/
int bpReadCondition( ETF *, TranData *, char *, char *, int);
int CreateStatement( ETF *, TranData *, char *, char *, char *, int );
int SetAccPub( void * );
int SetAccPubAll( void * );

/*
 *added by kixiong at 2009-6-5 12:39:00
 *新增一组函数接口
 */
char * bpCloneEtfData(TranData *trdata, char *name, int * datalen);
char * bpCloneNamedData(TranData *trdata, char *src_name, char *dat_name, int *datalen);
char * bpCloneBasData(TranData *trdata, char *name, int *datalen);
char * usfCloneMsgHeadValue(Message * msg, char * fld_name, int * datalen);
char * bpCloneMsgHead(TranData *trdata, char *name, int *datalen);
char * bpCloneData(TranData *trdata, char *src_name, char *dat_name, int *datalen);
char * bpClonePara(TranData *trdata, char *name, int *datalen);
char * bpCloneAliasData(TranData *trdata, char *alias, int * datalen);
/*added end at 2009-6-5 12:40:54*/
