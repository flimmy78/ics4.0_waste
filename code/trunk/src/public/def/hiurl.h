/******************************************************************************

				Copyright (C),1998-2008,Hisuntech Co.,Ltd.
 
 File name		: hiurl.h
 Author			: LiangWenJian 
 Version		: V1.0 
 Date			: 2008.10.27 
 Description	: ������Ϊ�ļ�URL���ʷ�ʽ�Ķ����ļ�
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001   2008-10-27  LiangWJ     ����

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
 * �ֽ��ļ�URL
 */
EXTERN 
int hiurl_unpack(
		char *url, 			/* URL��ʾ�ַ��� */
		char *nodeid, 		/* ��ʵ�ļ����ڽڵ�ID */
		char *path, 		/* ��ʵ�ļ��������·�� */	
		char *file			/* �ļ��� */
);

/*
 * ����ļ�URL
 */
EXTERN 
int hiurl_pack(
		char *url, 			/* URL��ʾ�ַ��� */
		char *nodeid, 		/* ��ʵ�ļ����ڽڵ�ID */
		char *path, 		/* ��ʵ�ļ��������·�� */	
		char *file			/* �ļ��� */
);

/*
 * ȡ�����ļ���
 */
EXTERN 
int hiurl_getlocalfile(
		char *fullpath,		/* URL��ʾ�ַ��� */
		char *nodeid, 		/* ��ʵ�ļ����ڽڵ�ID */
		char *path, 		/* ��ʵ�ļ��������·�� */	
		char *file			/* �ļ��� */
);

/*
 * ��URL�ļ�
 */
EXTERN 
FILE * hiurl_fopen(
		char *url,			/* �ļ�URL */
		char *mode,			/* ��ģʽ */
		int	 *myerrno		/* ������ */
);


/*
 * �ر�URL�ļ�
 */
EXTERN 
void hiurl_fclose(FILE *fp);

#undef	EXTERN

#endif /* _HI_URL_ */

