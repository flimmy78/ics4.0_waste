/******************************************************************************

 Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: hirpt.h
 Author			: yu_qj
 Version		: 1.0
 Date			: 2003-04-02
 Description	: 报表生成器头文件
 History		: 
 1. DATE		: 2003-04-02
	Author		: yu_qj
	Modification: 创建
 2. DATE		: 2003-05-07
	Author		: wang_mg
	Modification: 修改完成
******************************************************************************/
#ifndef _RPTMAKER_H_
#define _RPTMAKER_H_

/*屏蔽掉stdarg.h*/
#ifndef _H_STDARG
#define _H_STDARG
#endif

#include "hixml.h"
#include "hidll.h"
#include "hidbdsc.h"
#include "hidatabase.h"
#include "hilgr.h"

#ifndef _RPT_BUSONL
#include "hipex.h"
#endif

#define VAR_NAME_LEN	128				//变量名的最大长度
#define RPTFILENAME_LEN	128				//文件名长度
#define RPTNAME_LEN		128				//报表名长度
#define VALUE_LEN		1024			//变量值的最大长度
#define	TYPE_LEN		32				//参数区参数类型的最大长度
#define BUFFER_SIZE		1024			//缓冲区长度
#define LINEBUFF		5120			//输出数据长度
#define PART_NUM		9				//定义报表分为几个部分
#define	SUB_ITEM_MAX	10				//统计层次的最大值
#define FORMATSEQ_LEN   10				//格式序号长度

#define TMPROOTNAME 	"rootrec"
#define HIRPTLOG		"HIRPT.trc"     //默认调试日志名

/*以下定义的是数据源文件中行数据的类型表示*/
#define HEAD_PH			"[0]"	/*页眉*/
#define HEAD_RH			"[1]"	/*报表头*/
#define HEAD_TH			"[2]"	/*表眉*/
#define HEAD_ITER		"[3]"	/*记录*/
#define HEAD_ST			"[4]"	/*小计*/
#define HEAD_SUM		"[5]"	/*总计*/
#define HEAD_TF			"[6]"	/*表脚*/
#define HEAD_RF			"[7]"	/*报表尾*/
#define HEAD_PF			"[8]"	/*页脚*/

/*以下定义的是行数据类型*/
#define TYPE_PH			0		/*页眉*/
#define TYPE_RH			1		/*报表头*/
#define TYPE_TH			2		/*表眉*/
#define TYPE_ITER		3		/*记录*/
#define TYPE_ST			4		/*小计*/
#define TYPE_SUM		5		/*总计*/
#define TYPE_TF			6		/*表脚*/
#define TYPE_RF			7		/*报表尾*/
#define TYPE_PF			8		/*页脚*/
#define TYPE_COMMENT	99		/*注释*/


/*行数据类型与数据之间的分隔符*/
#define DATA_HEADDELI	':'	

/*注释符号*/
#define DATA_COMMENT	'#'

/*变量名和值分隔符*/
#define DATA_EVALUATE	'=' 

/*变量之间的分隔符*/
#define DATA_DELIMITER	"|"	

/*数据结束标志*/
#define	DATA_EOL		10	//换行符

/*配置文件中填写数据的位置标示符*/
#define	LOCALIZER		'#'	

/*换行符*/
//#define FORM_FEED		'\f'		/* ^L */
#define FORM_FEED	    12			/* ^L */

/*换页标志*/
#define	NOFEED			1
#define FEED			0

/*系统默认变量*/
#define DATE			"DATE"		/*日期*/
#define	TIME			"TIME"		/*时间*/
#define	PAGEROWS		"PAGEROWS"	/*一页打印多少行*/
#define PAGENUM			"PAGENUM"	/*页码*/
#define PAGESUM			"PAGESUM"	/*总页数*/
#define RPTNAME			"RPTNAME"	/*报表名*/
#define RECNUM			"RECNUM"	/*记录计数器*/

/*变量区结构*/
typedef struct _vardef
{
	char	alias[VAR_NAME_LEN];	/*变量别名*/
	char	name[VAR_NAME_LEN];		/*变量名*/
	char	value[VALUE_LEN];		/*变量的值*/
	struct  _vardef *next;			/*指向下一个节点的指针*/

} VarDef;

/*参数区结构*/
typedef struct _para
{
	int		num;					/*参数链表中参数的个数*/
	char	alias[VAR_NAME_LEN];	/*参数别名*/
	char	value[VALUE_LEN];		/*参数值*/
	char	type[TYPE_LEN];			/*参数对齐方式*/
	struct  _para *next;			/*指向下一个节点的指针*/
} Para;

/*小计结构*/
//typedef struct _sub_total
//{
//	char	groupby[VAR_NAME_LEN];		/*统计的项名*/
//	char	fmtseq[FORMATSEQ_LEN];		/*格式序号*/
//	char	count[VALUE_LEN];			/*总数*/
//	char	cntname[VAR_NAME_LEN];      /*总数项名*/
//	VarDef	*suminf;					/*求和信息*/
//	struct  _sub_total *next;			/*指向下一个节点的指针*/
//} SubTotal;

/*按条件统计*/
typedef struct _cond_sum
{
	char	cntname[VAR_NAME_LEN];		/*总数项名*/
	char	count[VALUE_LEN];			/*总数*/
	VarDef	*suminf;					/*求和信息*/
	VarDef  *where;						/*进行小计的条件*/
	struct  _cond_sum *next;			/*指向下一个节点的指针*/
} CondSum;

/*小计结构*/
typedef struct _sub_total
{
	char	groupby[VAR_NAME_LEN];		/*统计的项名*/
	char	fmtseq[FORMATSEQ_LEN];		/*格式序号*/
	CondSum	*condsum;					/*求和信息*/
	struct  _sub_total *next;			/*指向下一个节点的指针*/
} SubTotal;

//数据对照表
typedef struct _Value_Cmp
{
	char	value[VALUE_LEN];		/*变量的值*/
	char	msg[VALUE_LEN];			/*变量值对应的转换信息*/
	struct  _Value_Cmp *next;		/*指向下一个节点的指针*/
} ValCmp;


//数据转换结构
typedef struct _Msg_Convert
{
	char	alias[VAR_NAME_LEN];		/*参数别名*/
	ValCmp	*valcmp;					/*值和转换信息对照表*/
	struct  _Msg_Convert *next;			/*指向下一个节点的指针*/
} MsgConvert;

#ifdef _RPT_API_EXTERN
#define RPT_EXTERN extern
extern int  _page_num;				//打印页数
extern int	_rec_num;						//记录数
extern char * _pDeli;               //分隔符字符串
extern int _rptTraceFlag;					//调试日志开关
#else
#define RPT_EXTERN 
int  _page_num = 1;					//打印页数
int	_rec_num = 1;					//记录数
char * _pDeli = NULL;               //分隔符字符串
int _rptTraceFlag = 0;				//调试日志开关
#endif

RPT_EXTERN ExpDllHandle  _rpt_exp_dll;			//表达式处理结构变量
RPT_EXTERN MsgConvert	*_pMsg;					//信息转换结构变量
RPT_EXTERN char	_rptTraceLog[RPTFILENAME_LEN];

#undef RPT_EXTERN
#ifdef _RPT_API_EXTERN
#define RPT_EXTERN
#else
#define RPT_EXTERN extern
#endif

RPT_EXTERN int	rptNewRecord();			/*va_list- 参数列表，必须以NULL结尾 */
RPT_EXTERN int	rptAppendRecord();		/*va_list- 参数列表，必须以NULL结尾 */
RPT_EXTERN int	rptMaker( XmlNode *, char *,char *, int, ETF *, DBConHandle *); //报表生成API
#endif   /*_RPTMAKER_H_*/
