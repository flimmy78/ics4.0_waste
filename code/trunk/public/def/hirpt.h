/******************************************************************************

 Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: hirpt.h
 Author			: yu_qj
 Version		: 1.0
 Date			: 2003-04-02
 Description	: ����������ͷ�ļ�
 History		: 
 1. DATE		: 2003-04-02
	Author		: yu_qj
	Modification: ����
 2. DATE		: 2003-05-07
	Author		: wang_mg
	Modification: �޸����
******************************************************************************/
#ifndef _RPTMAKER_H_
#define _RPTMAKER_H_

/*���ε�stdarg.h*/
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

#define VAR_NAME_LEN	128				//����������󳤶�
#define RPTFILENAME_LEN	128				//�ļ�������
#define RPTNAME_LEN		128				//����������
#define VALUE_LEN		1024			//����ֵ����󳤶�
#define	TYPE_LEN		32				//�������������͵���󳤶�
#define BUFFER_SIZE		1024			//����������
#define LINEBUFF		5120			//������ݳ���
#define PART_NUM		9				//���屨���Ϊ��������
#define	SUB_ITEM_MAX	10				//ͳ�Ʋ�ε����ֵ
#define FORMATSEQ_LEN   10				//��ʽ��ų���

#define TMPROOTNAME 	"rootrec"
#define HIRPTLOG		"HIRPT.trc"     //Ĭ�ϵ�����־��

/*���¶����������Դ�ļ��������ݵ����ͱ�ʾ*/
#define HEAD_PH			"[0]"	/*ҳü*/
#define HEAD_RH			"[1]"	/*����ͷ*/
#define HEAD_TH			"[2]"	/*��ü*/
#define HEAD_ITER		"[3]"	/*��¼*/
#define HEAD_ST			"[4]"	/*С��*/
#define HEAD_SUM		"[5]"	/*�ܼ�*/
#define HEAD_TF			"[6]"	/*���*/
#define HEAD_RF			"[7]"	/*����β*/
#define HEAD_PF			"[8]"	/*ҳ��*/

/*���¶����������������*/
#define TYPE_PH			0		/*ҳü*/
#define TYPE_RH			1		/*����ͷ*/
#define TYPE_TH			2		/*��ü*/
#define TYPE_ITER		3		/*��¼*/
#define TYPE_ST			4		/*С��*/
#define TYPE_SUM		5		/*�ܼ�*/
#define TYPE_TF			6		/*���*/
#define TYPE_RF			7		/*����β*/
#define TYPE_PF			8		/*ҳ��*/
#define TYPE_COMMENT	99		/*ע��*/


/*����������������֮��ķָ���*/
#define DATA_HEADDELI	':'	

/*ע�ͷ���*/
#define DATA_COMMENT	'#'

/*��������ֵ�ָ���*/
#define DATA_EVALUATE	'=' 

/*����֮��ķָ���*/
#define DATA_DELIMITER	"|"	

/*���ݽ�����־*/
#define	DATA_EOL		10	//���з�

/*�����ļ�����д���ݵ�λ�ñ�ʾ��*/
#define	LOCALIZER		'#'	

/*���з�*/
//#define FORM_FEED		'\f'		/* ^L */
#define FORM_FEED	    12			/* ^L */

/*��ҳ��־*/
#define	NOFEED			1
#define FEED			0

/*ϵͳĬ�ϱ���*/
#define DATE			"DATE"		/*����*/
#define	TIME			"TIME"		/*ʱ��*/
#define	PAGEROWS		"PAGEROWS"	/*һҳ��ӡ������*/
#define PAGENUM			"PAGENUM"	/*ҳ��*/
#define PAGESUM			"PAGESUM"	/*��ҳ��*/
#define RPTNAME			"RPTNAME"	/*������*/
#define RECNUM			"RECNUM"	/*��¼������*/

/*�������ṹ*/
typedef struct _vardef
{
	char	alias[VAR_NAME_LEN];	/*��������*/
	char	name[VAR_NAME_LEN];		/*������*/
	char	value[VALUE_LEN];		/*������ֵ*/
	struct  _vardef *next;			/*ָ����һ���ڵ��ָ��*/

} VarDef;

/*�������ṹ*/
typedef struct _para
{
	int		num;					/*���������в����ĸ���*/
	char	alias[VAR_NAME_LEN];	/*��������*/
	char	value[VALUE_LEN];		/*����ֵ*/
	char	type[TYPE_LEN];			/*�������뷽ʽ*/
	struct  _para *next;			/*ָ����һ���ڵ��ָ��*/
} Para;

/*С�ƽṹ*/
//typedef struct _sub_total
//{
//	char	groupby[VAR_NAME_LEN];		/*ͳ�Ƶ�����*/
//	char	fmtseq[FORMATSEQ_LEN];		/*��ʽ���*/
//	char	count[VALUE_LEN];			/*����*/
//	char	cntname[VAR_NAME_LEN];      /*��������*/
//	VarDef	*suminf;					/*�����Ϣ*/
//	struct  _sub_total *next;			/*ָ����һ���ڵ��ָ��*/
//} SubTotal;

/*������ͳ��*/
typedef struct _cond_sum
{
	char	cntname[VAR_NAME_LEN];		/*��������*/
	char	count[VALUE_LEN];			/*����*/
	VarDef	*suminf;					/*�����Ϣ*/
	VarDef  *where;						/*����С�Ƶ�����*/
	struct  _cond_sum *next;			/*ָ����һ���ڵ��ָ��*/
} CondSum;

/*С�ƽṹ*/
typedef struct _sub_total
{
	char	groupby[VAR_NAME_LEN];		/*ͳ�Ƶ�����*/
	char	fmtseq[FORMATSEQ_LEN];		/*��ʽ���*/
	CondSum	*condsum;					/*�����Ϣ*/
	struct  _sub_total *next;			/*ָ����һ���ڵ��ָ��*/
} SubTotal;

//���ݶ��ձ�
typedef struct _Value_Cmp
{
	char	value[VALUE_LEN];		/*������ֵ*/
	char	msg[VALUE_LEN];			/*����ֵ��Ӧ��ת����Ϣ*/
	struct  _Value_Cmp *next;		/*ָ����һ���ڵ��ָ��*/
} ValCmp;


//����ת���ṹ
typedef struct _Msg_Convert
{
	char	alias[VAR_NAME_LEN];		/*��������*/
	ValCmp	*valcmp;					/*ֵ��ת����Ϣ���ձ�*/
	struct  _Msg_Convert *next;			/*ָ����һ���ڵ��ָ��*/
} MsgConvert;

#ifdef _RPT_API_EXTERN
#define RPT_EXTERN extern
extern int  _page_num;				//��ӡҳ��
extern int	_rec_num;						//��¼��
extern char * _pDeli;               //�ָ����ַ���
extern int _rptTraceFlag;					//������־����
#else
#define RPT_EXTERN 
int  _page_num = 1;					//��ӡҳ��
int	_rec_num = 1;					//��¼��
char * _pDeli = NULL;               //�ָ����ַ���
int _rptTraceFlag = 0;				//������־����
#endif

RPT_EXTERN ExpDllHandle  _rpt_exp_dll;			//���ʽ����ṹ����
RPT_EXTERN MsgConvert	*_pMsg;					//��Ϣת���ṹ����
RPT_EXTERN char	_rptTraceLog[RPTFILENAME_LEN];

#undef RPT_EXTERN
#ifdef _RPT_API_EXTERN
#define RPT_EXTERN
#else
#define RPT_EXTERN extern
#endif

RPT_EXTERN int	rptNewRecord();			/*va_list- �����б�������NULL��β */
RPT_EXTERN int	rptAppendRecord();		/*va_list- �����б�������NULL��β */
RPT_EXTERN int	rptMaker( XmlNode *, char *,char *, int, ETF *, DBConHandle *); //��������API
#endif   /*_RPTMAKER_H_*/
