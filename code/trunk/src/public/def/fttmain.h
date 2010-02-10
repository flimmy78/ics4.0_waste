/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: fileRecv.h 
 Author			: CaiJunJie 
 Version		: V1.0 
 Date			: 2003.05.27 
 Description	: 本头文件定义文件接收服务使用到的数据结构
				 
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================

******************************************************************************/


#ifndef _HI_FTTMAIN_
	#define _HI_FTTMAIN_

#include "hibase.h"
#include "hiserver.h"
/*
#include "hilgr.h"
*/

#ifdef	_HP_SYSTEM_
#include <sys/stat.h>
#endif

#define		FILE_RECV_OK			0
#define 	FILE_RECV_ERR			-1

#define		FILE_RECV_OK_DATA		"000000040000"
#define 	FILE_RECV_ERR_DATA		"000000049999"

/* 文件传输请求包结构 */
struct _ftp_package {
	char	OpCode[1+1];
	char	BitMap[2+1];
	int		FilNamLen;
	char	* pFilNam;
	int		SavDirLen;
	char	* pSavDir;
	int		MsgDatLen;
	char	* pMsgDat;
};
typedef struct _ftp_package FtpPackage;

#endif /* _HI_FTTMAIN_ */
