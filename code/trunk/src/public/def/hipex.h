/******************************************************************************

Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: hipex.h
 Author			: wang_mg
 Version		: 1.0
 Date			: 2003-04-04
 Description	: 表达式解析头文件
 Others			: 无
 History		: 
 1. DATE		: 2003-04-04
	Author		: wang_mg
	Modification: 创建
 2. ...
******************************************************************************/
#ifndef _PUB_EXP_H_
#define _PUB_EXP_H_

#include "hietf.h"
#include "hidll.h"

#define FLOAT_EQUAL         1E-5            /*浮点型数据比较差值*/
#define NUM_LEN				30				/*数的长度*/
#define LIBNAM_LEN			128				/*动态库别名长度*/
#define FUNNAM_LEN			128				/*函数名长度*/
//modified by kixiong at 2008-12-8 12:39:41
//支持一个别名对应多个动态库
//#define DEF_DLLNAM			"dll/hipex.so"  /*默认的公共动态库别名*/
#define DEF_DLLNAM			"PEX"
#define DEF_DLLFIL			"dll/hipex.so"	/*默认的公共动态库别名*/
#define MAX_PARA_LEN		3072			/*解析的表达式的最大长度*/
#define MAX_PARA			20				/*解析的表达式中函数的参数最多个数*/
#define TYPE_STRING			0				/*表达式是常量字符串*/
#define TYPE_VARIABLE		1				/*表达式是变量*/
#define TYPE_FUNCTION		2				/*表达式是函数*/
#define ERR_EXPINVALID		-1				/*表达式字符串不合法*/		
#define ERR_LENLESS			-2				/*接收处理结果的空间长度不够*/
#define ERR_DLLNULL			-3				/*表达式处理结构不合法*/
#define ERR_LOADFUNC		-4				/*调用dllLoadFunc函数失败*/
#define ERR_CHILDFUNC		-5				/*功能处理函数返回失败*/
#define ERR_NOETFFIELD		-6				/*在ETF树上没找到节点*/
#define ERR_DLLALIAS		-7				/*动态库别名不正确*/
#define ERR_MALLOC			-9				/*分配空间出错*/
#define BUFFER_SIZE			1024			/*缓冲区长度*/
#define PUB_DEF_NAME_LEN	128				/*动态库别名长度*/
#define PUB_DEF_VALUE_LEN	128				/*真实库名长度*/

#define ISNULLNODEFUNC	    "ISNULLNODE"	/*是否空节点函数*/

/* 动态库别名和实际名对照表 */
struct _pub_define_rec {
    char     define_name[PUB_DEF_NAME_LEN+1];
    char     define_value[PUB_DEF_VALUE_LEN+1];
    struct   _pub_define_rec * next;
};
typedef struct _pub_define_rec PubDefineRec;


/*
 * 动态库文件结构，支持一个别名对应多个文件
 * Added by liangwj at 2006-12-5
 */
struct _lib_define_rec {
	char	alias[16+1];
	int		file_num;
	char 	**filename;
	struct _lib_define_rec *next;
};
typedef struct _lib_define_rec LibDefineRec;

/*表达式处理结构*/
struct   _exp_dll_handle{
	XDllReg			* pDllReg;				/*动态库登记结构*/
	//modified by kixiong at 2008-12-5 14:34:03
	//PubDefineRec	* pDefRec;				/*动态库别名和实际名对照表*/
	LibDefineRec	* pDefRec;				/*动态库别名和实际名对照表*/
	int				(* pFunc )(void *);		/*函数指针*/
};
typedef	struct _exp_dll_handle ExpDllHandle;


#ifdef PUB_EXP_EXTERN
/*
pexParserExtend参数分别为：
  ETF树头节点,表达式,表达式处理结构指针, 接收处理结果的空间和接收处理结果空间的长度
  返回值：
		>=0,表示处理结果字符串的长度
		< 0 表示出错
*/
int    pexParserExtend(ETF *, char *, ExpDllHandle*, char *, int);

/*
pexParser参数分别为：
  ETF树头节点,表达式,表达式处理结构指针, 处理结果字符串的长度
  返回值：一个字符串,在内部申请了空间,要求在外部释放.  NULL 表示出错
*/
char * pexParser(ETF *, char *,	ExpDllHandle*, int *);
#else
extern  int    pexParserExtend(ETF *, char *, ExpDllHandle*, char *, int);
extern  char * pexParser(ETF *, char *,	ExpDllHandle*, int *);
#endif
#endif/* _PUB_EXP_H_ */
