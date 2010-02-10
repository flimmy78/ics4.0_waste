/******************************************************************************

				Copyright (C),1998-2008,Hisuntech Co.,Ltd.
 
 File name		: mymem.h
 Author			: Liang Wen Jian 
 Version		: V1.0 
 Date			: 2009-02-12
 Description	: 本程序为内存分配封装的定义文件
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001   2009-02-12  LiangWJ     创建

******************************************************************************/

#ifndef _MY_MEM_
#define _MY_MEM_

#include "hash.h"

#ifdef _LIB_MYMEM_
#define	EXTERN
#else
#define	EXTERN extern
#endif

/*
 * 申请内存
 */
EXTERN 
void * 
m_malloc(
		int sz, 			/* 申请内存大小 */
		char *file, 		/* 代码所在源文件名 */
		int line 			/* 代码所在源文件的行号 */	
);

/*
 * 重新申请内存
 */
EXTERN 
void * 
m_realloc(
		void *old_addr,		/* 上次申请内存的地址 */
		int sz, 			/* 重新申请的内存大小 */
		char *file, 		/* 代码所在源文件名 */
		int line  			/* 代码所在源文件的行号 */	
);

/*
 * 释放内存
 */
EXTERN 
void 
m_free(
		void *p, 			/* 需要释放的内存地址 */
		char *file, 		/* 代码所在源文件名 */
		int line  			/* 代码所在源文件的行号 */	
);

/*
 * 登记内存
 */
EXTERN 
int 
m_add(
		void *p, 			/* 需要登记的内存地址 */
		int	sz,				/* 内存大小 */
		char *file, 		/* 代码所在源文件名 */
		int line  			/* 代码所在源文件的行号 */	
);

/*
 * 删除已登记内存
 */
EXTERN 
void 
m_delete(
		void *p, 			/* 已登记的内存地址 */
		char *file, 		/* 代码所在源文件名 */
		int line  			/* 代码所在源文件的行号 */	
);

/*
 * 查看已分配的内存
 */
EXTERN 
void m_show();

#undef	EXTERN

#ifdef	_DEBUG_
    #define	M_MALLOC(sz)	m_malloc(sz,__FILE__,__LINE__)
    #define	M_REALLOC(p, sz)	m_realloc(p, sz,__FILE__,__LINE__)
    #define	M_FREE(p)	m_free(p,__FILE__,__LINE__)
    #define	M_ADD(p, sz) m_add(p, sz, __FILE__, __LINE__)
    #define	M_DELETE(p) m_delete(p, __FILE__, __LINE__)
    #define	M_SHOW()	m_show()
#else
	#define	M_MALLOC(sz)	malloc(sz)
	#define	M_REALLOC(p, sz)	realloc(p, sz)
	#define	M_FREE(p)	free(p)
    #define	M_ADD(p, sz) hdonothing()
    #define	M_DELETE(p) hdonothing()
    #define	M_SHOW()	hdonothing()
#endif /* _DEBUG_ */

#endif /* _MY_MEM_ */

