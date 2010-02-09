/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: hiipchk.h
 Author			: 谭亮
 Version		: V1.0 
 Date			: 2003.08.23 
 Description	: 检查 IP 地址安全性
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================
   01   2003-08-23  谭亮        整理
******************************************************************************/

#ifndef _HIIPCHK_H_
#define _HIIPCHK_H_

#include "hixml.h"
#include "hiconstant.h"

#ifdef _HIIPCHK_LIB_
	#define EXTERN
#else
	#define EXTERN extern
#endif /* _HIIPCHK_ */

EXTERN int ecnInitIpList(char *, QuickSearchList **, XmlNode **);
EXTERN int ecnCheckIp(QuickSearchList *, char *);
EXTERN void ecnFreeIpList(QuickSearchList *, XmlNode *);

#undef EXTERN

#endif /* _HIIPCHK_H_ */
