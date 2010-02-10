/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hisqnmng.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2003-10-25
 Description    : 流水号管理器头文件
 Others         : 无
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-10-25  LiangWJ     完成
  002   2005-12-29  LiangWJ     省逻辑集中改造

******************************************************************************/
#ifndef	_H_HISQNMNG_
#define	_H_HISQNMNG_

/* 函数声明 */
#ifdef	_LIB_HISQNMNG_
#define	EXTERN
#else
#define	EXTERN extern
#endif
EXTERN int sqnGetLogNo(char *, int);
/* 
 * 取虚拟柜员函数,增加分行代码参数
 * Modified by liangwj in 2005122
 */
EXTERN int sqnGetDumTlr(char *, char *, char *, char *);
EXTERN int sqnUpdActDat(char *, char *);
#undef	EXTERN

#endif /* _H_HISQNMNG_ */
