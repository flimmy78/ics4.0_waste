/******************************************************************************

				Copyright (C),1998-2008,Hisuntech Co.,Ltd.
 
 File name		: hiurl.h
 Author			: LiangWenJian 
 Version		: V1.0 
 Date			: 2008.10.27 
 Description	: 本程序为文件URL访问方式的定义文件
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001   2008-10-27  LiangWJ     创建

******************************************************************************/

#ifndef _HI_URL_
#define _HI_URL_

#include "hiserver.h"


#ifdef _LIB_HIURL
#define	EXTERN
#else
#define	EXTERN extern
#endif
/*
 * 分解文件URL
 */
EXTERN 
int hiurl_unpack(
		char *url, 			/* URL表示字符串 */
		char *nodeid, 		/* 真实文件所在节点ID */
		char *path, 		/* 真实文件所在相对路径 */	
		char *file			/* 文件名 */
);

/*
 * 组合文件URL
 */
EXTERN 
int hiurl_pack(
		char *url, 			/* URL表示字符串 */
		char *nodeid, 		/* 真实文件所在节点ID */
		char *path, 		/* 真实文件所在相对路径 */	
		char *file			/* 文件名 */
);

/*
 * 取本地文件名
 */
EXTERN 
int hiurl_getlocalfile(
		char *fullpath,		/* URL表示字符串 */
		char *nodeid, 		/* 真实文件所在节点ID */
		char *path, 		/* 真实文件所在相对路径 */	
		char *file			/* 文件名 */
);

/*
 * 打开URL文件
 */
EXTERN 
FILE * hiurl_fopen(
		char *url,			/* 文件URL */
		char *mode,			/* 打开模式 */
		int	 *myerrno		/* 错误码 */
);


/*
 * 关闭URL文件
 */
EXTERN 
void hiurl_fclose(FILE *fp);

#undef	EXTERN

#endif /* _HI_URL_ */

