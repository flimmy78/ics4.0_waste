/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: hiftp.h 
 Author			: LiangWenJian 
 Version		: V1.0 
 Date			: 2004.03.20 
 Description	: 本头文件定义文件传输接口
				 
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	==============================================

******************************************************************************/
#ifndef _HI_FTP_
#define _HI_FTP_

/* Declare version */
#define	HIFTP_VERSION1			1
#define	HIFTP_CURRENT_VERSION	1
#define	HIFTP_VERSION_LEN		2

/* Length define */
#define	BLOCK_SIZE				4096
#define	PKG_SIZE				1024
#define	FLD_PRE_LEN				3
#define	FIL_PRE_LEN				8

/* Ftp command */
#define	FTP_CMD_LEN				1
#define	FTP_OPEN				'O'
#define	FTP_CLOSE				'C'
#define	FTP_GET					'G'
#define	FTP_PUT					'P'

/* Bitmap information */
#define	BITMAP_LEN				2
#define	BITMAP_NO				'0'
#define	BITMAP_YES				'1'

/* Transfer mode */
#define	MODE_BIN				1
#define	MODE_ASC				2

/* Result define */
#define	RESULT_LEN				2
#define	HIFTP_SUCCESS			"00"

/* Retuen code (For client) */
#define	HIFTP_OK				0
#define	HIFTP_VERSION_ERROR		1
#define	HIFTP_RECEIVE_ERROR		2
#define	HIFTP_SEND_ERROR		3
#define	HIFTP_OPEN_FILE_ERROR	4
#define	HIFTP_DATA_ERROR		5
#define	HIFTP_MALLOC_ERROR		6
#define	HIFTP_ICSSYS_ERROR		7

/* Package struct */
struct _ftp_package {
	int		Version;
	char	Command[FTP_CMD_LEN+1];
	int		Mode;
	char	BitMap[BITMAP_LEN+1];
	char	* pFilNam;
	char	* pSavDir;
	int		MsgDatLen;
	char	* pMsgDat;
};
typedef struct _ftp_package FtpPackage;

/* HIFTP struct */
struct _hi_ftp {
	char 	ip[15+1];
	int		port;
	int		mode;
	int		fd;
};
typedef struct _hi_ftp HIFTP;

/* 
 * 函数: hiftpset
 * 功能: 设置传输信息
 */
int hiftpset (
    HIFTP * hiftp,           /* FTP传输信息 */
    char  * ip,              /* 远程服务器IP */
    int   port,              /* 远程服务器端口 */
    int   mode);             /* 文件传输模式 */

/* 
 * 函数: hiftpopen
 * 功能: 与文件传输服务器建立连接
 */
int hiftpopen (
    HIFTP * hiftp);          /* FTP传输信息 */

/* 
 * 函数: hiftpclose
 * 功能: 关闭与文件传输服务器的连接
 */
int hiftpclose (
    HIFTP * hiftp);          /* FTP传输信息 */

/* 
 * 函数: hiftpget
 * 功能: 到远程服务器下载文件
 */
int hiftpget (
    HIFTP * hiftp,           /* FTP传输信息 */
    char  * local_file,      /* 保存到本地的文件名 */
    char  * remote_dir,      /* 远程目录 */
    char  * remote_file,     /* 远程文件名 */
    char  * msg_data,        /* 通知消息数据 */
    int   msg_len);          /* 消息数据长度 */

/* 
 * 函数: hiftpput
 * 功能: 上传本地文件到远程服务器
 */
int hiftpput (
    HIFTP * hiftp,           /* FTP传输信息 */
    char  * local_file,      /* 上传的本地文件名 */
    char  * remote_dir,      /* 远程目录 */
    char  * remote_file,     /* 远程文件名 */
    char  * msg_data,        /* 通知消息数据 */
    int   msg_len);          /* 消息数据长度 */

#endif /* _HI_FTP_ */

