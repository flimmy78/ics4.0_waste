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

/*TIA结构*/
typedef	struct
{
	char CCSCod[CCSCOD_LEN + 1];		/*CICS交易码          */
	char TTxnCd[TXNCOD_LEN + 1];		/*第三方交易码        */
	char FeCod [TXNCOD_LEN + 1];		/*操作码              */
	char TrmNo [TRMNO_LEN  + 1]; 		/*终端号              */
	char TxnSrc[TXNSRC_LEN  + 1];		/*交易来源            */	
	char LogNo [LOGNO_LEN  + 1];		/*前置流水号          */
	char TlrId [TLRID_LEN  + 1]; 		/*柜员号              */
	char TIATyp[TIATYP_LEN + 1];		/*请求类型	T: 正常交易	A: 授权交易包 P: 多页数据包*/
	char AthLvl[ATHLVL_LEN  + 1];		/*授权级别            */
	char Sup1Id[SUPID_LEN  + 1]; 		/*主管号              */
	char Sup2Id[SUPID_LEN  + 1]; 		/*主管号              */
	char Sup1Pw[PIN_LEN  + 1];			/*主管密码            */
	char Sup2Pw[PIN_LEN  + 1];			/*主管密码            */
	char Sup1Dv[SUPDEV_LEN  + 1];		/*主管密码输入设备    */
	char Sup2Dv[SUPDEV_LEN  + 1];		/*主管密码输入设备    */	 
	char AthTbl[ATHTBL_LEN + 1 ];		/*授权原因          */	   
	char AthLog[FLAG_LEN  + 1];			/*授权LOG标志         */	
	char HLogNo[HLOGNO_LEN  + 1]; 		/*最后一笔交易日志号  */
	char CprInd[FLAG_LEN  + 1];			/*压缩标志            */
	char EnpInd[FLAG_LEN  + 1];			/*加密标志            */
	char NodNo [NODNO_LEN  + 1]; 		/*交易机构号          */
	char OprLvl[OPRLVL_LEN  + 1];		/*柜员级别            */
	char TrmVer[TRMVER_LEN  + 1];		/*前端版本号          */	
	char OutSys[FLAG_LEN  + 1];			/*数据超长标志        */	
	char Fil   [FIL_LEN  + 1];   		/*                    */	
} TIAHEAD;

/*TOA结构*/
typedef	struct
{
	char  Fil1  [FIL1_LEN  + 1];	/*CICS功能信息头                 */		
	char  MsgTyp[MSGTYP_LEN  + 1];	/*交易类型  N: 正确包  E:　错误包*/		
	char  RspCod[RSPCOD_LEN  + 1];	/*信息码                         */		
	char  ErrFld[ERRFLD_LEN  + 1];	/*错误输入场                     */
	char  TrmNo [TRMNO_LEN  + 1];	/*终端号                         */		
	char  TrmSqn[TRMSQN_LEN  + 1];	/*终端序号                       */		
	char  STxnCd[STXNCD_LEN  + 1];	/*后续交易码                     */		
	char  SAplCd[SAPLCD_LEN  + 1];	/*后续应用码                     */		
	char  TxnSym[TXNSYM_LEN  + 1];	/*交易符                         */		
	char  TxnDat[DATE_LEN  + 1];	/*交易日期                       */
	char  TxnTm [TIME_LEN  + 1];	/*交易时间                       */
	char  ActDat[DATE_LEN  + 1];	/*会计日期                       */
	char  HLogNo[HLOGNO_LEN  + 1];	/*日志号                         */
	char  TckNo	[TCKNO_LEN + 1];	/*传票号                         */
	char  PagId[PAGID_LEN  + 1];	/*多页标志                       */
	char  CprInd[FLAG_LEN  + 1];	/*压缩标志                       */
	char  EnpInd[FLAG_LEN  + 1];	/*加密标志                       */
	char  NodNo	[NODNO_LEN  + 1];	/*交易网点号                     */
	char  AthLog[FLAG_LEN  + 1];	/*授权LOG标志                    */		
	char  FinFlg[FLAG_LEN  + 1];	/*金融传票标志                   */		
	char  AthLvl[ATHLVL_LEN  + 1];	/*授权级别						 */
	char  Sup1Id[SUPID_LEN  + 1];	/*主管号                         */		
	char  Sup2Id[SUPID_LEN  + 1];	/*主管号                         */		
	char  Fil2  [FIL2_LEN  + 1];	/*                               */		
	char  DatLen[DATlEN_LEN  + 1];	/*输出数据长度(不包括自身长度)   */
} TOAHEAD;

/*授权表结构定义 */
typedef struct
{
	int  num;									/*授权原因个数  */
	char AthCod[ATHREC_NUM][ATHCOD_LEN + 1]; 	/*授权级别码    */
	char AthMsg[ATHREC_NUM][ATHMSG_LEN + 1];	/*授权信息      */
	char AthDat[ATHREC_NUM][ATHDAT_LEN + 1];	/*授权附加信息  */
} AUTHTABLE;

/*报表管理发往文件服务器的列表 */
struct _rpt_file_list
{
	int  num;								/*列表文件个数  */
	char FilNam[RPTFIL_NUM][FILNAM_LEN]; 	/* 文件名  */
};
typedef struct _rpt_file_list  RPTFILLIST;

/* SQLDA保存结构 */
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

/* FTP信息结构 */
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
