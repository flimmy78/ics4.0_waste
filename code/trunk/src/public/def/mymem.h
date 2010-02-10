/******************************************************************************

				Copyright (C),1998-2008,Hisuntech Co.,Ltd.
 
 File name		: mymem.h
 Author			: Liang Wen Jian 
 Version		: V1.0 
 Date			: 2009-02-12
 Description	: ������Ϊ�ڴ�����װ�Ķ����ļ�
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001   2009-02-12  LiangWJ     ����

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
 * �����ڴ�
 */
EXTERN 
void * 
m_malloc(
		int sz, 			/* �����ڴ��С */
		char *file, 		/* ��������Դ�ļ��� */
		int line 			/* ��������Դ�ļ����к� */	
);

/*
 * ���������ڴ�
 */
EXTERN 
void * 
m_realloc(
		void *old_addr,		/* �ϴ������ڴ�ĵ�ַ */
		int sz, 			/* ����������ڴ��С */
		char *file, 		/* ��������Դ�ļ��� */
		int line  			/* ��������Դ�ļ����к� */	
);

/*
 * �ͷ��ڴ�
 */
EXTERN 
void 
m_free(
		void *p, 			/* ��Ҫ�ͷŵ��ڴ��ַ */
		char *file, 		/* ��������Դ�ļ��� */
		int line  			/* ��������Դ�ļ����к� */	
);

/*
 * �Ǽ��ڴ�
 */
EXTERN 
int 
m_add(
		void *p, 			/* ��Ҫ�Ǽǵ��ڴ��ַ */
		int	sz,				/* �ڴ��С */
		char *file, 		/* ��������Դ�ļ��� */
		int line  			/* ��������Դ�ļ����к� */	
);

/*
 * ɾ���ѵǼ��ڴ�
 */
EXTERN 
void 
m_delete(
		void *p, 			/* �ѵǼǵ��ڴ��ַ */
		char *file, 		/* ��������Դ�ļ��� */
		int line  			/* ��������Դ�ļ����к� */	
);

/*
 * �鿴�ѷ�����ڴ�
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

