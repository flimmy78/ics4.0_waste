/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hisqnmng.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2003-10-25
 Description    : ��ˮ�Ź�����ͷ�ļ�
 Others         : ��
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-10-25  LiangWJ     ���
  002   2005-12-29  LiangWJ     ʡ�߼����и���

******************************************************************************/
#ifndef	_H_HISQNMNG_
#define	_H_HISQNMNG_

/* �������� */
#ifdef	_LIB_HISQNMNG_
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int sqnGetLogNo(char *, int);
/* 
 * ȡ�����Ա����,���ӷ��д������
 * Modified by liangwj in 2005122
 */
EXTERN int sqnGetDumTlr(char *, char *, char *, char *);
EXTERN int sqnUpdActDat(char *, char *);
#undef	EXTERN

#endif /* _H_HISQNMNG_ */
