/******************************************************************************

Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: hipex.h
 Author			: wang_mg
 Version		: 1.0
 Date			: 2003-04-04
 Description	: ���ʽ����ͷ�ļ�
 Others			: ��
 History		: 
 1. DATE		: 2003-04-04
	Author		: wang_mg
	Modification: ����
 2. ...
******************************************************************************/
#ifndef _PUB_EXP_H_
#define _PUB_EXP_H_

#include "hietf.h"
#include "hidll.h"

#define FLOAT_EQUAL         1E-5            /*���������ݱȽϲ�ֵ*/
#define NUM_LEN				30				/*���ĳ���*/
#define LIBNAM_LEN			128				/*��̬���������*/
#define FUNNAM_LEN			128				/*����������*/
//modified by kixiong at 2008-12-8 12:39:41
//֧��һ��������Ӧ�����̬��
//#define DEF_DLLNAM			"dll/hipex.so"  /*Ĭ�ϵĹ�����̬�����*/
#define DEF_DLLNAM			"PEX"
#define DEF_DLLFIL			"dll/hipex.so"	/*Ĭ�ϵĹ�����̬�����*/
#define MAX_PARA_LEN		3072			/*�����ı��ʽ����󳤶�*/
#define MAX_PARA			20				/*�����ı��ʽ�к����Ĳ���������*/
#define TYPE_STRING			0				/*���ʽ�ǳ����ַ���*/
#define TYPE_VARIABLE		1				/*���ʽ�Ǳ���*/
#define TYPE_FUNCTION		2				/*���ʽ�Ǻ���*/
#define ERR_EXPINVALID		-1				/*���ʽ�ַ������Ϸ�*/		
#define ERR_LENLESS			-2				/*���մ������Ŀռ䳤�Ȳ���*/
#define ERR_DLLNULL			-3				/*���ʽ����ṹ���Ϸ�*/
#define ERR_LOADFUNC		-4				/*����dllLoadFunc����ʧ��*/
#define ERR_CHILDFUNC		-5				/*���ܴ���������ʧ��*/
#define ERR_NOETFFIELD		-6				/*��ETF����û�ҵ��ڵ�*/
#define ERR_DLLALIAS		-7				/*��̬���������ȷ*/
#define ERR_MALLOC			-9				/*����ռ����*/
#define BUFFER_SIZE			1024			/*����������*/
#define PUB_DEF_NAME_LEN	128				/*��̬���������*/
#define PUB_DEF_VALUE_LEN	128				/*��ʵ��������*/

#define ISNULLNODEFUNC	    "ISNULLNODE"	/*�Ƿ�սڵ㺯��*/

/* ��̬�������ʵ�������ձ� */
struct _pub_define_rec {
    char     define_name[PUB_DEF_NAME_LEN+1];
    char     define_value[PUB_DEF_VALUE_LEN+1];
    struct   _pub_define_rec * next;
};
typedef struct _pub_define_rec PubDefineRec;


/*
 * ��̬���ļ��ṹ��֧��һ��������Ӧ����ļ�
 * Added by liangwj at 2006-12-5
 */
struct _lib_define_rec {
	char	alias[16+1];
	int		file_num;
	char 	**filename;
	struct _lib_define_rec *next;
};
typedef struct _lib_define_rec LibDefineRec;

/*���ʽ����ṹ*/
struct   _exp_dll_handle{
	XDllReg			* pDllReg;				/*��̬��Ǽǽṹ*/
	//modified by kixiong at 2008-12-5 14:34:03
	//PubDefineRec	* pDefRec;				/*��̬�������ʵ�������ձ�*/
	LibDefineRec	* pDefRec;				/*��̬�������ʵ�������ձ�*/
	int				(* pFunc )(void *);		/*����ָ��*/
};
typedef	struct _exp_dll_handle ExpDllHandle;


#ifdef PUB_EXP_EXTERN
/*
pexParserExtend�����ֱ�Ϊ��
  ETF��ͷ�ڵ�,���ʽ,���ʽ����ṹָ��, ���մ������Ŀռ�ͽ��մ������ռ�ĳ���
  ����ֵ��
		>=0,��ʾ�������ַ����ĳ���
		< 0 ��ʾ����
*/
int    pexParserExtend(ETF *, char *, ExpDllHandle*, char *, int);

/*
pexParser�����ֱ�Ϊ��
  ETF��ͷ�ڵ�,���ʽ,���ʽ����ṹָ��, �������ַ����ĳ���
  ����ֵ��һ���ַ���,���ڲ������˿ռ�,Ҫ�����ⲿ�ͷ�.  NULL ��ʾ����
*/
char * pexParser(ETF *, char *,	ExpDllHandle*, int *);
#else
extern  int    pexParserExtend(ETF *, char *, ExpDllHandle*, char *, int);
extern  char * pexParser(ETF *, char *,	ExpDllHandle*, int *);
#endif
#endif/* _PUB_EXP_H_ */
