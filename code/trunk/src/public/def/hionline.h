/******************************************************************************

				Copyright (C),1998-2005,Hisuntech Co.,Ltd.

 File name		: hionline.h
 Author			: Chen Yinggang
 Version		: 1.0
 Date			: 2003-03-28
 Description	: ������������ͷ�ļ�
 Others			: 
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2003-3-28	CYG 		���
  002	2007-6-5	LiangWJ 	֧��ָ�������������ܣ��޸�TranData�ṹ��
  003	2007-6-28	LiangWJ 	�޸�TranData�ṹ������ϵͳ�����־
  004	2007-8-27	LiangWJ 	ȥ��ҵ����룬ͬһ��Ӧ������֧��װ�ض��CTL

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

/*��̬��ѯ���ṹ*/
struct _txn_condition {
	char 	txn_cod[MAX_SERVICE_NAME_LEN + 1];
	char 	con_cod[CONCOD_LEN + 1];
	char *	query;
	char *	fields;
	struct 	_txn_condition * next;
};
typedef struct _txn_condition TxnCondition;

/*������Ϣ����ṹ*/
struct _pb_item_data {
	char 	** 	data;
	char 	** 	item_name;
	int	 	*	size;
	int			item_num;
};

typedef struct _pb_item_data  PbItemData;

/* Ӧ�������ļ���Ϣ�ṹ */
struct _cfg_define_rec {
	//nameΪ�ļ��ľ���·��
	//�����ļ��ı�����PubDefRec������
	char    * 	name;
	XmlNode *	node;
	/*
	 * ֧�ָ��������ļ�
	 * Added by liangwj at 2006-11-27
	 */
	int			type;
	void	*	pointer;
	void (* done_func)(void *);
};
typedef struct _cfg_define_rec CfgDefineRec;

/*
 * �����ڵ�
 * Added by liangwj at 2006-01-10
 * �����������,Modified by liangwj at 2007-3-16
 */
struct _function_node {
	char 			* name;				/* ������ */
	InterfaceDefine	* input;			/* ����ӿ� */
	InterfaceDefine	* output;			/* ����ӿ� */
	TxnCondition	* sentence_head;	/* �׶�̬��� */
	XmlNode			* process;			/* �������� */
	//deleted by kixiong at 2008-12-4 15:50:18
	//package�Ż�����
	//struct 	_function_node * next;		/* ��һ������ */
};
typedef struct _function_node FunctionNode;
 
/*
 * ������ڵ�
 * Added by liangwj at 2006-01-10
 */
struct _package_node {
	/*
	 * deleted by kixiong at 2008-12-4 15:43:43
	 * package �Ż�����
	char 			* serv_name;		// Ӧ���� 
	Added by liangwj at 2007-8-27
	char 			* serv_sqn;		    // Ӧ�ó������
	char 			* name;				// ������� 
	FunctionNode	* func_head;		// ������׺����ڵ�
	struct 	_package_node * next;		// ��һ������� 
	*/
	
	int			  free_flag;			// �Ƿ���Ҫ�ͷŸ��ڵ� 
	char          * filename;			/* �ļ�����(����·��) */
	XmlNode		  * pkg_root;			/* ��������ڵ� */

	//added by kixiong at 2008-12-4 15:46:47
	short		  	cfgdef_num;
	short			busdef_num;
	short			pkgdef_num;
	PubDefineRec  * cfgdefmsg;			//�����ļ���ʵ�ʵ��ļ����Ķ���
	LibDefineRec  * librarymsg;			//�������ʵ�ʵĿ�ͺ����Ķ���
	PubDefineRec  * busdefmsg;			//Ӧ��
	PubDefineRec  * pkgdefmsg;			//��������ʵ�ʰ��Ķ���
	hash_t			* func_container;  //������еĺ�������
};
typedef struct _package_node PackageNode;

/* ����������Ϣ�ṹ */
struct _serv_config_msg {
	char     		serv_name[SERV_NAME_LEN+1];
	char     		serv_code[SERV_CODE_LEN+1];
	char     		list_tbl[TBLNAM_LEN+1];
	char	 		errlog_nam [LOG_NAME_LEN+1];				/*������־��*/
	char	 		trclog_nam [LOG_NAME_LEN+1];				/*������־��*/
	short    		serv_permit_flag;
	short	 		trace_flag;
	short	 		cfgdef_num;
	short	 		busdef_num;
	/* ����ǰ�˵��Ե�IP��PORT add by liangwj in 2004-02-16 */
	char			trace_ip[IPADR_LEN+1];						/*ǰ�˵��Ի���IP*/
	int				trace_port;									/*ǰ�˵��Զ˿�*/
	//modified by kixiong at 2008-12-4 15:56:11
	//Package�Ż�
	//CfgDefineRec  * cfgdefmsg;
	PubDefineRec  * cfgdefmsg; //�����ļ�������ʵ���ļ����Ķ���
	LibDefineRec  * librarymsg;
	PubDefineRec  * busdefmsg;
	/* 
	 * Package������Ϣ 
	 * Added by liangwj at 2006-01-09 
	 */
	short			pkgdef_num;
	PubDefineRec  * pkgdefmsg;
};
typedef struct _serv_config_msg ServConfigMsg;

/*�������ط�����*/
struct _reltran_atr {
	char    txn_cod[MAX_SERVICE_NAME_LEN+1];			/*������*/
	char	interval[INTERVAL_LEN + 1];		/*��ѯ���ʱ��*/
	char	time_out[TIMEOUT_LEN + 1];		/*��ʱʱ��*/
	char	max_times[MAXTIMES_LEN + 1];	/*������*/
	char	obj_svr[SVRNAM_LEN + 1];			/*Ŀ�������*/
};
typedef struct _reltran_atr RelTranAtr;

/* �������ýṹ */
struct _tran_config_rec {
	ServConfigMsg	* 	serv_msg;
	char     			txn_cod[MAX_SERVICE_NAME_LEN+1];
	RelTranAtr 			integrity_atr;
	short    			tran_permit_flag;
	char     			attribute[ATTRIBUTE_LEN+1];
	short	 			trace_flag;
	int      			tran_step_num;
	/* ����ǰ�˵��Ե�socket������ add by liangwj in 2004-02-16 */
	int					trace_sockfd;
	TxnCondition 	*	txn_cond;
	XmlNode			*	tran_step;
	/*
	 * �����׺����ڵ�
	 * Added by liangwj at 2006-01-09 
	 */
	//modified by kixiong at 2008-12-4 21:41:06
	//FunctionNode	* 	func_head;
	PackageNode		*	tran_pkg;
};
typedef struct _tran_config_rec TranConfigRec;

/*�������Խṹ*/
struct _tranattrpos {
   char 	attr_name[ATTRNAME_LEN + 1];
   char 	pos[FLAG_LEN + 1];
   struct 	_tranattrpos * next;
};
typedef struct _tranattrpos TranAttrPos;

/*ƽ̨����ϵͳ��Ϣ�ṹ*/
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
	hash_t			*	cfg_container;	//�����ļ�����
	
	SystemParaSpace	*	para_space;
	
	/*added by kixiong at 2008-10-20 15:26*/
	short				statistics_switch;	/*��Ϣͳ�ƿ���*/
	pthread_rwlock_t	switch_lock;		/*������*/
	
	/*added by liangwj at 2008-11-20 16:28*/
	LoggerMessage	* 	logger_msg;			/*��־��Ϣ������*/
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
 * ����Դ�򿪵��α���Ź���
 */
struct _connection_cursor_index {
	short	ds_id;						 /*����ԴID*/
	char	cursor_seq[MAX_OPEN_CURSOR]; /* �򿪵��α���� */
};
typedef struct _connection_cursor_index ConnectionCursorIndex;

/*������Ϣ�ṹ*/
struct _tran_data {
	int						ret_cod;						/* ԭ�Ӻ�������ֵ */
	char					sys_id [SYSID_LEN + 1];			/* ϵͳ��ʶ��     */
	char					req_id [RQST_ID_LEN + 1];		/* ���׸��ٺ�     */
	char					svr_name [SVRNAM_LEN +1];		/* ��������       */
	char				  *	bus_name;						/* ҵ����         */
	char					log_no[LOGNO_LEN+1];			/* ǰ����ˮ��     */
	char					act_dat[DATE_LEN+1];			/* �������       */
	char				  errlog_nam[LOG_NAME_LEN+1];		/* ���״�����־�� */
	char				  trclog_nam[LOG_NAME_LEN+1];		/* ���׵�����־�� */
	char				  *	txn_cod;						/* ������         */
	char				  *	list_tbl;						/* Ӧ����ˮ����   */
	char				  *	attribute;						/* ��������       */
	char				  	run_status[RUN_STATUS_LEN+1];	/* ��������״̬   */
	short					trace_flag;						/* ������־����   */
	Message				  *	in_msg;							/* ��Ϣ           */
	XmlNode		 		  *	trlst_cols_nods;				/* ��ˮ��ṹ��   */
	XmlNode		 		  *	table_cols_nods;				/* ҵ���ṹ��   */
	RelTranAtr			  *	integrity_atr;					/* �����Խ������� */
	ServConfigMsg	 	  * serv_msg;						/* ��������Ϣ   */
	TranPubEnv   		  * pub_env;						/* ȫ�ֹ�����Ϣ   */
	struct _pb_item_data	bus_def;						/* �Զ�����Ϣ     */
	struct _pb_item_data	txn_jnl;						/* ��ˮ��         */
	DataSource				*data_source;					/* Ӧ������Դ     */
	TranParaSpace		  * para_space;	    			    /* �����ռ� */
	ETF					  * input_etf;			     		/* ��ǰ����ETF    */
	ETF					  * output_etf;				    	/* ��ǰ���ETF    */
	char				  output_area[20+1];				/* ��ǰ��������� */
	int					  sys_err_flag;						/* ϵͳ�����־ */
	int					  add_msg_flag;						/* �����Ϣ��־ */
	/*added by kixiong at 2008-10-20 15:34 */
	hash_t				  * comp_ctx_info;					/* ���ͳ����Ϣ*/
	/*added by kixiong at 2008-10-20 15:26*/
	short				  statistics_switch;				/* ��Ϣͳ�ƿ���*/
	
	struct timeval		  start_time;						/* ���׿�ʼʱ��*/
	struct timeval		  dead_time;						/* ���׽���ʱ��*/
	ConnectionCursorIndex conn_cursor[MAX_OPEN_CONN];		/* �򿪵��α���� */
	
	/*added by liangwj at 2008-11-20 16:38*/
	Logger				* logger;							/* ������־�� */
	int					  log_level;						/* ��־���� */
};

typedef struct _tran_data TranData;

/* ������Ϣ�ṹ */
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
	 * ��ǰPackage����
	 * Added by liangwj at 2006-01-24 
	 */
	//modified by kixiong at 2008-12-4 20:11:17
	//char			* 	pkg_name;
	PackageNode		*	curr_pkg;			//��ǰPackage
	
	//added by kixiong at 2008-12-4 16:16:25
	//Package�Ż�
	PubDefineRec  * curr_cfgdefmsg;			//��ǰ�����ļ���ʵ�ʵ��ļ����Ķ���
	LibDefineRec  * curr_librarymsg;		//��ǰ�������ʵ�ʵĿ�ͺ����Ķ���
	PubDefineRec  * curr_busdefmsg;			//��ǰӦ��
	PubDefineRec  * curr_pkgdefmsg;			//��ǰ��������ʵ�ʰ��Ķ���
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
 * ���ӱ����ļ���LclFil
 * Added by liangwj at 2006-03-21
 */
typedef	struct
{
	char  MsgTyp[FLAG_LEN  + 1];		/*��Ϣ����1֪ͨ;2�㲥;3�ļ�;4��ӡ*/		
	char  BusTyp[MSGBUSTYP_LEN  + 1];	/*Ӧ������                       */		
	char  AplCod[MSGAPLCOD_LEN  + 1];	/*Ӧ�ô���                       */
	char  FilNam[MSGFILNAM_LEN  + 1];	/*�ļ���                         */		
	char  LclFil[MSGFILNAM_LEN  + 1];	/*�����ļ���                     */		
	char  MsgSmr[MSGFILNAM_LEN  + 1];	/*��ϢժҪ                       */		
	char  HLogNo[MSGHLOGNO_LEN  + 1];	/*������ˮ��,ǰ�ô�����Ϣ����    */		
	char  OrgNo[MSGORGNO_LEN  + 1];		/*�����׻�������               */		
	char  TlrId[MSGTLRID_LEN  + 1];		/*�����׹�Ա����               */		
	char  BgnDat[DATE_LEN  + 1];		/*����������                   */		
	char  BgnTm[TIME_LEN  + 1];			/*������ʱ��                   */		
	char  EprDat[DATE_LEN  + 1];		/*ʧЧ����   	                 */		
	char  EprTm[TIME_LEN  + 1];			/*ʧЧʱ��                       */		
	char  ProFlg[FLAG_LEN  + 1];		/*ʧЧ���������־0 ɾ�� 1�ͼ�� */		
	char  Data[MSGDATA_LEN  + 1];		/*Ӧ��������                     */		
	int   RecNum;						/*����Ŀ����                     */		
	ObjMsg * obj_msg;	 				/*Ŀ�����㡢Ŀ�Ĺ�Ա             */
} InformMessage;

#ifdef BPNOEXTERN

ServEnv	    * _ServEnv;

/* 
 * ��������ı���ʵ�ֶ�̬���¹��� 
 * Added by liangwj in 20051202
 */
int					_Argc;
char				** _Argv;
pthread_rwlock_t	_UpdateRWLock;

#else  /* BPNOEXTERN */

extern ServEnv	    * _ServEnv;
extern XmlNode	* 	_TrTabCfg;	/*Ӧ����ˮ���ֵ�*/

/* ��������ı���ʵ�ֶ�̬���¹��� */
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
 * ������������Ϊ�����ӿ�
 * Added by liangwj in 20041026
 */
EXTERN char * bpReturnArgument(PbItemData, char *, int *);
EXTERN char * bpReturnChildValue(ETF *, char *, int *);
/* 
 * ������������Ϊ�����ӿ�
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

/*�������ݿ�������*/
int bpSetDBContext(DBConHandle *);
/*ȡETF�ڵ㣬����ڵ㲻���ڻ򳤶�Ϊ0���򷵻�-1*/
int bpGetChildValue( ETF *, char *, char *, int );
/*��¼�������ʹ�����Ϣ*/
int	bpAddResult(ETF *, char *, char * );
/*��¼������־*/
int bpTraceLog( TranData *, char *, ...);
/*��¼������־*/
int bpErrorLog( TranData *, char *, ...);
/*���ݲ�ѯ�������֯��ѯ���*/
int bpReadCondition( ETF *, TranData *, char *, char *, int);
int CreateStatement( ETF *, TranData *, char *, char *, char *, int );
int SetAccPub( void * );
int SetAccPubAll( void * );

/*
 *added by kixiong at 2009-6-5 12:39:00
 *����һ�麯���ӿ�
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
