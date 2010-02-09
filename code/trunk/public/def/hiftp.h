/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: hiftp.h 
 Author			: LiangWenJian 
 Version		: V1.0 
 Date			: 2004.03.20 
 Description	: ��ͷ�ļ������ļ�����ӿ�
				 
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
 * ����: hiftpset
 * ����: ���ô�����Ϣ
 */
int hiftpset (
    HIFTP * hiftp,           /* FTP������Ϣ */
    char  * ip,              /* Զ�̷�����IP */
    int   port,              /* Զ�̷������˿� */
    int   mode);             /* �ļ�����ģʽ */

/* 
 * ����: hiftpopen
 * ����: ���ļ������������������
 */
int hiftpopen (
    HIFTP * hiftp);          /* FTP������Ϣ */

/* 
 * ����: hiftpclose
 * ����: �ر����ļ����������������
 */
int hiftpclose (
    HIFTP * hiftp);          /* FTP������Ϣ */

/* 
 * ����: hiftpget
 * ����: ��Զ�̷����������ļ�
 */
int hiftpget (
    HIFTP * hiftp,           /* FTP������Ϣ */
    char  * local_file,      /* ���浽���ص��ļ��� */
    char  * remote_dir,      /* Զ��Ŀ¼ */
    char  * remote_file,     /* Զ���ļ��� */
    char  * msg_data,        /* ֪ͨ��Ϣ���� */
    int   msg_len);          /* ��Ϣ���ݳ��� */

/* 
 * ����: hiftpput
 * ����: �ϴ������ļ���Զ�̷�����
 */
int hiftpput (
    HIFTP * hiftp,           /* FTP������Ϣ */
    char  * local_file,      /* �ϴ��ı����ļ��� */
    char  * remote_dir,      /* Զ��Ŀ¼ */
    char  * remote_file,     /* Զ���ļ��� */
    char  * msg_data,        /* ֪ͨ��Ϣ���� */
    int   msg_len);          /* ��Ϣ���ݳ��� */

#endif /* _HI_FTP_ */

