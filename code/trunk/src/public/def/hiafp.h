/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hiafp.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2003-05-10
 Description    : ���ĸ�ʽת��ͷ�ļ�
 Others         : ��
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-05-10  LiangWJ     ���

******************************************************************************/
#ifndef	_H_HIXMLAFP_
#define	_H_HIXMLAFP_
#include	"hibase.h"
#include	"hiserver.h"
#include	"hidll.h"
#include	"hietf.h"
#include	"lib8583.h"
#include	"hilgr.h"


/* ���峤�� */
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

/* ������Ϣͷ�����¼�Ľṹ */
struct _msg_head_rec {
	char * p_key;			/* ����ƥ��ļ�ֵ */
	long head_len;			/* ��Ϣͷ�ĳ��� */
	char * p_head_buff;		/* ��Ϣͷ���ַ��� */
	long clock;				/* ��Ϣͷ����ʱ�� */ 
	long timeout;			/* ��Ϣͷ���泬ʱʱ�� */
};
typedef struct _msg_head_rec MsgHeadRec;

/* ����ӿ�������Ϣ */
struct	_itf_info	{
	int				file_num;		/* �ӿ������ļ��� */
	char			** files;		/* �ӿ������ļ����� */
	int				seq_no;			/* �ӿ�������� */
	XmlNode  		* curr_root;	/* ��ǰ�ӿ����ø��ڵ� */
	XmlNode  		* bak_root;		/* �ϴα��ݵ����ø��ڵ� */
	long			upd_clock;		/* �ϴθ��µ�ʱ�� */
};
typedef struct _itf_info ItfInf;

/* ���嶯̬����Ϣ�ṹ */
struct	_dll_info	{
	XDllReg 		curr_list;		/* ��ǰ��̬���б� */
	XDllReg 		bak_list;		/* �ϴα��ݵĶ�̬���б� */
	long			upd_clock;		/* �ϴθ��µ�ʱ�� */
};
typedef struct _dll_info DllInf;

/* �������������Ϣ */
struct _code_tab_col_inf {
	char			name[NAMES_LEN+1];	/* ���� */
	char			* def_val;			/* ȱʡֵ */
	QuickSearchList	* list;				/* �����б� */
};
typedef	struct _code_tab_col_inf CodeTabColInf;

/* ��������Ľڵ� */
struct _code_tab_node {
	char					name[NAMES_LEN+1];	/* ���� */
	XmlNode					* root;				/* �������ڵ� */
	CodeTabColInf			col_inf[2];			/* ����Ϣ */
	struct	_code_tab_node	* next;				/* ��һ���ڵ� */
};
typedef	struct _code_tab_node CodeTabNode;

/* ���������������Ϣ */
struct _code_tab_inf {
	CodeTabNode		* curr_head;	/* ��ǰ�Ĵ�����ձ�ͷ�ڵ� */
	CodeTabNode		* bak_head;		/* ���ݵĴ�����ձ�ͷ�ڵ� */ 
	long			upd_clock;		/* �ϴεĸ���ʱ�� */
};
typedef	struct _code_tab_inf CodeTabInf;

/* ����ȫ�ֵ�������Ϣ�ṹ */
struct	_afp_config	{
	char			err_file[NAMES_LEN+1];	/* ������־�ļ� */
	char			trace_file[NAMES_LEN+1];/* ������־�ļ� */
	pthread_mutex_t	pub_lock;				/* ������ */
	ItfInf			itf_inf;				/* �ӿ�������Ϣ */
	DllInf			dll_inf;				/* ��̬����Ϣ */
	CodeTabInf		code_tab_inf;			/* ������ձ���Ϣ */
	MemoryPool 		* msg_head_mp;			/* ������Ϣͷ���ڴ�� */
	/* Namespace declare node*/
	XmlNode			* ns_node;
};
typedef	struct _afp_config AfpConfig;

/* ����ɼ̳�����ֵ�Ľṹ */
struct	_heritable_attr {
	char	type[10+1];						/* �򶨽������ */
	char	necessary[3+1];					/* �Ƿ������ */
	char	len_type[10+1];					/* ǰ�ó����������� */
	char	head_len[MAX_HEAD_LEN_LEN+1];	/* ǰ�ó��ȵĳ��� */
	char	include_len[3+1];				/* �Ƿ����ǰ�ó��ȵı�־ */
	char	deli_asc[10+1];					/* �ָ���ASCII�� */
	char	deli_str[10+1];					/* �ָ��ַ��� */
	char	align_mode[5+1];				/* �����ݶ��뷽ʽ(ȱʡΪleft) */
	char	fill_asc[10+1];					/* ���ASCII�� */
};
typedef	struct _heritable_attr HeritableAttr;

/* ���ƿռ䶨��ǼǱ� */
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

/* ���嵱ǰ��Ϣ�ṹ */
struct	_curr_inf {
	char			svr_name[SVR_NAME_LEN+1];			/* �������� */
	char			req_id[RQST_ID_LEN+1];				/* ��Ϣ������ */
	char			txn_code[MAX_TXN_CODE_LEN+1];		/* ������ */
	char			server[SVR_NAME_LEN+1];				/* Ŀ������� */
	char			service[MAX_SERVICE_LEN+1];			/* ���׷��� */
	int				timeout;							/* ���׳�ʱʱ�� */
	int				exist_txn_code;						/* �Ƿ��Ѵ��ڽ����� */
	int				rq_or_rp;							/* ����/Ӧ���־ */
	int				convert_flag;						/* ���ĸ�ʽת����־ */
	int				err_no;                             /* ������ */
	char			err_msg[ERR_MSG_LEN+1];				/* ������Ϣ */
	char			app_file[NAMES_LEN+1];				/* Ӧ����־�ļ� */
	char			err_file[NAMES_LEN+1];				/* ������־�ļ� */
	char			trace_file[NAMES_LEN+1];			/* ������־�ļ� */
	int				trace_flag;							/* ������־��־ */
	int				pass_flag;							/* ���״�͸��־ */
	char			* workdir;							/* ����·�� */
	int				prev_retcode;						/* ��һ���ķ����� */
	int				break_flag;							/* �жϱ�־ */
	AfpConfig		* afp_cfg;							/* ������Ϣ */
	HeritableAttr	heritable_attr;						/* �ɼ̳����� */
	CodeTabNode		* code_tab_head;					/* ������ձ�ͷ�ڵ� */
	MemoryPool 		* msg_head_mp;						/* ������Ϣͷ���ڴ�� */
	Message			* f_msg;							/* ��һ����Ϣָ�� */
	ETF				* data_root;						/* ETF���ڵ� */
	ETF				* curr_data_node;					/* ETF��ǰ���ڵ� */
	XmlNode			* cfg_root;							/* �ӿ����ø��ڵ� */
	XmlNode			* txn_node;							/* ���׽ӿ����ýڵ� */
	XmlNode			* curr_cfg_node;					/* ��ǰ���ýڵ� */
	int				sqn;                                /* ��ǰ���ɵĽڵ����*/
    XmlNode			* xmlDataTree;						/* XML����������ĸ���� */
    XmlNode			* xmlDataCurrNode;					/* xml���ĵ�ǰ�ڵ� */
	NSDecList		* nsdeclist;
	Logger			* logger;							/* ��־�� */
	int				log_level;							/* ��־���� */
};
typedef	struct _curr_inf CurrInf;

/* ������� */
#ifdef	_XMLAFP_EXTERN_
#define	EXTERN extern
#else
#define	EXTERN
#endif
EXTERN AfpConfig	_Config;
EXTERN Field8583  _Field8583[129]; 
#undef	EXTERN

/* �������� */
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
