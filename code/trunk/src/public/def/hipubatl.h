/*
 * History: Date        Position        Author                Action
 * ----------------------------------------------------------------------------
 *          2003-09-20  ShangHai        ChenYG                Create
 ******************************************************************************/

#ifndef  _HI_PUBATL_H
#define  _HI_PUBATL_H

#include	"hionline.h"
#include	"hibusmsg.h"
#include	"hibppubdef.h"
#include	"hirpt.h"
#include	"hiafp.h"
/*
#include	"hidbt.h"
*/
#include	"hidbdsc.h"
#include	"hiftp.h"

/*
 * modified by kixiong at 2008-10-23 15:20
 *
EXEC SQL INCLUDE "hichk.h";
EXEC SQL INCLUDE "hionlinedb.h";
EXEC SQL INCLUDE "hibat.h";
EXEC SQL INCLUDE "hichk.h";
EXEC SQL INCLUDE "hicrc.h";
EXEC SQL INCLUDE "hirdo.h";
EXEC SQL INCLUDE "hisaf.h";
*/
#include "hichk.h"
#include "hionlinedb.h"
#include "hibat.h"
#include "hichk.h"
#include "hicrc.h"
#include "hirdo.h"
#include "hisaf.h"

#define		RPTFIL_NUM	50

/*TIA�ṹ*/
typedef	struct
{
	char CCSCod[CCSCOD_LEN + 1];		/*CICS������          */
	char TTxnCd[TXNCOD_LEN + 1];		/*������������        */
	char FeCod [TXNCOD_LEN + 1];		/*������              */
	char TrmNo [TRMNO_LEN  + 1]; 		/*�ն˺�              */
	char TxnSrc[TXNSRC_LEN  + 1];		/*������Դ            */	
	char LogNo [LOGNO_LEN  + 1];		/*ǰ����ˮ��          */
	char TlrId [TLRID_LEN  + 1]; 		/*��Ա��              */
	char TIATyp[TIATYP_LEN + 1];		/*��������	T: ��������	A: ��Ȩ���װ� P: ��ҳ���ݰ�*/
	char AthLvl[ATHLVL_LEN  + 1];		/*��Ȩ����            */
	char Sup1Id[SUPID_LEN  + 1]; 		/*���ܺ�              */
	char Sup2Id[SUPID_LEN  + 1]; 		/*���ܺ�              */
	char Sup1Pw[PIN_LEN  + 1];			/*��������            */
	char Sup2Pw[PIN_LEN  + 1];			/*��������            */
	char Sup1Dv[SUPDEV_LEN  + 1];		/*�������������豸    */
	char Sup2Dv[SUPDEV_LEN  + 1];		/*�������������豸    */	 
	char AthTbl[ATHTBL_LEN + 1 ];		/*��Ȩԭ��          */	   
	char AthLog[FLAG_LEN  + 1];			/*��ȨLOG��־         */	
	char HLogNo[HLOGNO_LEN  + 1]; 		/*���һ�ʽ�����־��  */
	char CprInd[FLAG_LEN  + 1];			/*ѹ����־            */
	char EnpInd[FLAG_LEN  + 1];			/*���ܱ�־            */
	char NodNo [NODNO_LEN  + 1]; 		/*���׻�����          */
	char OprLvl[OPRLVL_LEN  + 1];		/*��Ա����            */
	char TrmVer[TRMVER_LEN  + 1];		/*ǰ�˰汾��          */	
	char OutSys[FLAG_LEN  + 1];			/*���ݳ�����־        */	
	char Fil   [FIL_LEN  + 1];   		/*                    */	
} TIAHEAD;

/*TOA�ṹ*/
typedef	struct
{
	char  Fil1  [FIL1_LEN  + 1];	/*CICS������Ϣͷ                 */		
	char  MsgTyp[MSGTYP_LEN  + 1];	/*��������  N: ��ȷ��  E:�������*/		
	char  RspCod[RSPCOD_LEN  + 1];	/*��Ϣ��                         */		
	char  ErrFld[ERRFLD_LEN  + 1];	/*�������볡                     */
	char  TrmNo [TRMNO_LEN  + 1];	/*�ն˺�                         */		
	char  TrmSqn[TRMSQN_LEN  + 1];	/*�ն����                       */		
	char  STxnCd[STXNCD_LEN  + 1];	/*����������                     */		
	char  SAplCd[SAPLCD_LEN  + 1];	/*����Ӧ����                     */		
	char  TxnSym[TXNSYM_LEN  + 1];	/*���׷�                         */		
	char  TxnDat[DATE_LEN  + 1];	/*��������                       */
	char  TxnTm [TIME_LEN  + 1];	/*����ʱ��                       */
	char  ActDat[DATE_LEN  + 1];	/*�������                       */
	char  HLogNo[HLOGNO_LEN  + 1];	/*��־��                         */
	char  TckNo	[TCKNO_LEN + 1];	/*��Ʊ��                         */
	char  PagId[PAGID_LEN  + 1];	/*��ҳ��־                       */
	char  CprInd[FLAG_LEN  + 1];	/*ѹ����־                       */
	char  EnpInd[FLAG_LEN  + 1];	/*���ܱ�־                       */
	char  NodNo	[NODNO_LEN  + 1];	/*���������                     */
	char  AthLog[FLAG_LEN  + 1];	/*��ȨLOG��־                    */		
	char  FinFlg[FLAG_LEN  + 1];	/*���ڴ�Ʊ��־                   */		
	char  AthLvl[ATHLVL_LEN  + 1];	/*��Ȩ����						 */
	char  Sup1Id[SUPID_LEN  + 1];	/*���ܺ�                         */		
	char  Sup2Id[SUPID_LEN  + 1];	/*���ܺ�                         */		
	char  Fil2  [FIL2_LEN  + 1];	/*                               */		
	char  DatLen[DATlEN_LEN  + 1];	/*������ݳ���(������������)   */
} TOAHEAD;

/*��Ȩ��ṹ���� */
typedef struct
{
	int  num;									/*��Ȩԭ�����  */
	char AthCod[ATHREC_NUM][ATHCOD_LEN + 1]; 	/*��Ȩ������    */
	char AthMsg[ATHREC_NUM][ATHMSG_LEN + 1];	/*��Ȩ��Ϣ      */
	char AthDat[ATHREC_NUM][ATHDAT_LEN + 1];	/*��Ȩ������Ϣ  */
} AUTHTABLE;

/*����������ļ����������б� */
struct _rpt_file_list
{
	int  num;								/*�б��ļ�����  */
	char FilNam[RPTFIL_NUM][FILNAM_LEN]; 	/* �ļ���  */
};
typedef struct _rpt_file_list  RPTFILLIST;

/* SQLDA����ṹ */
/*
 * modified by kixiong at 2008-10-23 15:21
 * 
typedef struct {
	char	name[60+1];
	SQLDA	*sqlda_p;
}BP_SQLDA;
*/
typedef struct {
	char			name[60+1];
	int				ds_index;
	int	    		cursor_seq;
	DBConHandle 	* DBHandle;
	void			* sqlda_p;
}BP_SQLDA;

/* FTP��Ϣ�ṹ */
typedef struct {
	char IpAdr[IPADR_LEN+1];
	char UsrNam[USERNAME_LEN+1];
	char UsrPwd[USERPASSWD_LEN+1];
	char Port[IPPORT_LEN+1];
	char Mode[5+1];
	char LclDir[DIR_LEN+1];
	char ObjDir[DIR_LEN+1];
	char LclFil[FILE_NAME_LEN+1];
	char ObjFil[FILE_NAME_LEN+1];
}FTP_CONFIG;

void bpFreeSqlda(void *p);
void bpAutoUnlock(void *p);
void bpCloseFile(void *p);
void bpCloseAfp(void *p);

#endif /* _HI_PUBATL_H */
