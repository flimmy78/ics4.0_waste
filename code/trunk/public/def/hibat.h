/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hibat.h
 Author         : Song Jing Yi
 Version        : 1.0
 Date           : 2003-04-12
 Description    : ҵ��ƽ̨����ͷ�ļ�
 Others         : ��
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-04-12  SongJY      ���
  002   2005-12-19  LiangWJ     ʡ�߼����и��죬������Ϣ�����ӷ��д���
  003	2006-02-22	LiangWJ     ��Сͨ���ط����Ƹ���

******************************************************************************/
#ifndef  _HIBAT_H_
#define  _HIBAT_H_

#include "hionline.h"
#include "hiafp.h"
/*
 * deleted by kixiong at 2008-10-15 13:15
 * ���ݿ�������
#include "hidbt.h"
EXEC SQL INCLUDE "hirdo.h";
*/
#include "hirdo.h"
#include "hidbds.h"
 
#define BATCH_CONFIG          "BatConfig"
#define BATCH_FORMAT          "BatFormat"
#define PRIVATE_BATCHINFO     "BatchInfo"
#define PROCESS               "Process"
#define BEGIN_IGNORE_LINE     "begin_ignore_line"
#define END_IGNORE_LINE       "end_ignore_line"
#define STAT_FLAG             "stat_flag"
#define EXT_FLAG              "extend_flag"
#define BUSTYP                "BusTyp"
#define CRPCOD                "CrpCod"
#define DEFINE                "define"
#define NAME                  "name"
#define CODE                  "code"
#define SOURCE                "source"
#define ITEM                  "Item"
#define HEADLINE              "Head"
#define ENDLINE               "End"
#define RECORD                "Data"
#define TYPE                  "position"
#define WRAP                  "line_wrap"
#define REC_LEN               "record_length"
#define TOTAL_CNT             "OrnCnt"
#define TOTAL_AMT             "OrnAmt"
#define TXN_AMT               "TxnAmt"
#define SIGN_FLAG             "Sign"
#define STOP_FLAG             "Stop"
#define JUMP_FLAG             "Jump"
#define THIRD_RETCODE_LEN     10             /*���ص������Ļ��̽������󳤶�*/
#define ITV_TIME              "10"                /* �ط���ѯ���ʱ�� */
#define TIME_OUT              "10"                /* �ط���ʱʱ�� */
#define MAX_TMS               "300"               /* ����ط����� */
#define BATCH_FILENAME_LEN    100                 /* �����ļ������� */
#define BATCH_TABLENAME_LEN   30                  /* ����ҵ�����ݿ�������� */
#define MAX_STAT_ITEM_NUM     10                  /* ����ļ���ϸ�ۼ�ͳ������ */
#define TRAN_SUCCESS          "S"                 /* ǰ�óɹ����� */
#define TRAN_FAIL             "F"                 /* ǰ��ʧ�ܽ��� */
#define TRAN_CANCEL           "C"                 /* ǰ�ó������� */
#define TRAN_REVERSE          "R"                 /* ǰ�ñ��������� */
#define TRAN_UNKNOW           "U"                 /* ǰ��Ԥ�ǽ���(״̬δ֪) */
#define TRAN_ERROR            "E"                 /* ǰ�ò���� */
#define HOST_TRAN_SUCCESS     "N"                 /* �����ɹ����� */
#define HOST_TRAN_FAIL        "E"                 /* ����ʧ�ܽ��� */
#define HOST_TRAN_CANCEL      "C"                 /* ������������ */
#define HOST_TRAN_REVERSE     "R"                 /* �������������� */
#define SUCC_FLAG             "0000"              /* �����ɹ����������λ */
#define BAT_QUERY_MSGTYP      "CHN001"            /* ��Сͨ����ѯ��Ϣ���� */
#define BAT_HOST_MSGTYP       "CHN002"            /* ��Сͨ����������Ϣ���� */

/* ���ӷ��д��� Added by liangwj at 2005-12-19 */
#define PUB_BATCHINFO_BRNO_LEN 6
/* ���ӷ��ʹ������ϴη���ʱ�� Added by liangwj at 2006-02-22 */
#define PUB_BATCHINFO_SNDCNT_LEN 3
#define PUB_BATCHINFO_LSTTIM_LEN 10

#define PUB_BATCHINFO_DSKNO_LEN 12
#define PUB_BATCHINFO_DSKNAM_LEN 50
#define PUB_BATCHINFO_BUSTYP_LEN 6
#define PUB_BATCHINFO_CRPCOD_LEN 10
#define PUB_BATCHINFO_ACTDAT_LEN 8
#define PUB_BATCHINFO_TXNMOD_LEN 1
#define PUB_BATCHINFO_FILNAM_LEN 50
#define PUB_BATCHINFO_CCYCOD_LEN 3
#define PUB_BATCHINFO_SNDTLR_LEN 7
#define PUB_BATCHINFO_NODNO_LEN 6
#define PUB_BATCHINFO_RCVTM_LEN 14
#define PUB_BATCHINFO_CHKTLR_LEN 7
#define PUB_BATCHINFO_HSTTM_LEN 14
#define PUB_BATCHINFO_RTNTM_LEN 14
#define PUB_BATCHINFO_DNTLR_LEN 7
#define PUB_BATCHINFO_ORNCNT_LEN 8
#define PUB_BATCHINFO_ORNAMT_LEN 15
#define PUB_BATCHINFO_SUCCNT_LEN 8
#define PUB_BATCHINFO_SUCAMT_LEN 15
#define PUB_BATCHINFO_FALCNT_LEN 8
#define PUB_BATCHINFO_FALAMT_LEN 15
#define PUB_BATCHINFO_FRSPCD_LEN 6
#define PUB_BATCHINFO_TXNSQN_LEN 3
#define PUB_BATCHINFO_STATUS_LEN 1
#define PUB_BATCHINFO_CMTFLG_LEN 1
#define PUB_BATCHINFO_SNDTMS_LEN 3
#define PUB_BATCHINFO_FTXNCD_LEN 6
#define PUB_BATCHINFO_OBJSVR_LEN 8
#define PUB_BATCHINFO_TRDTBL_LEN 16
#define PUB_BATCHINFO_CHKFLG_LEN 1
#define PUB_BATCHINFO_SUMFLG_LEN 1
#define PUB_BATCHINFO_UPDFLG_LEN 1
#define PUB_BATCHINFO_RSVFLD_LEN 256

#define PUB_BATCHHOSTRESULT_LOGNO_LEN 14
#define PUB_BATCHHOSTRESULT_DSKNO_LEN 12
#define PUB_BATCHHOSTRESULT_BUSTYP_LEN 6
#define PUB_BATCHHOSTRESULT_CRPCOD_LEN 10
#define PUB_BATCHHOSTRESULT_ACTNO_LEN 21
#define PUB_BATCHHOSTRESULT_CRDNO_LEN 30
#define PUB_BATCHHOSTRESULT_CCYCOD_LEN 3
#define PUB_BATCHHOSTRESULT_TXNAMT_LEN 15
#define PUB_BATCHHOSTRESULT_HLOGNO_LEN 9
#define PUB_BATCHHOSTRESULT_HRSPCD_LEN 6
#define PUB_BATCHHOSTRESULT_HTXNST_LEN 1
#define PUB_BATCHHOSTRESULT_CHKFLG_LEN 1

/*deleted by kixiong at 2008-10-30 17:01
#ifdef	SYBASE
EXEC SQL BEGIN DECLARE SECTION;
#endif
*/
struct _pub_batchinfo
{
/* ���ӷ��д��� Added by liangwj in 20051219 */
	char    BrNo[PUB_BATCHINFO_BRNO_LEN + 1];
/* ���ӷ��ʹ������ϴη���ʱ�� Added by liangwj at 2006-02-22 */
	char    SndCnt[PUB_BATCHINFO_SNDCNT_LEN + 1];
	char    LstTim[PUB_BATCHINFO_LSTTIM_LEN + 1];
	char    DskNo[PUB_BATCHINFO_DSKNO_LEN + 1];
	char    DskNam[PUB_BATCHINFO_DSKNAM_LEN + 1];
	char    BusTyp[PUB_BATCHINFO_BUSTYP_LEN + 1];
	char    CrpCod[PUB_BATCHINFO_CRPCOD_LEN + 1];
	char    ActDat[PUB_BATCHINFO_ACTDAT_LEN + 1];
	char    TxnMod[PUB_BATCHINFO_TXNMOD_LEN + 1];
	char    FilNam[PUB_BATCHINFO_FILNAM_LEN + 1];
	char    CcyCod[PUB_BATCHINFO_CCYCOD_LEN + 1];
	char    SndTlr[PUB_BATCHINFO_SNDTLR_LEN + 1];
	char    NodNo[PUB_BATCHINFO_NODNO_LEN + 1];
	char    RcvTm[PUB_BATCHINFO_RCVTM_LEN + 1];
	char    ChkTlr[PUB_BATCHINFO_CHKTLR_LEN + 1];
	char    HstTm[PUB_BATCHINFO_HSTTM_LEN + 1];
	char    RtnTm[PUB_BATCHINFO_RTNTM_LEN + 1];
	char    DnTlr[PUB_BATCHINFO_DNTLR_LEN + 1];
	char    OrnCnt[PUB_BATCHINFO_ORNCNT_LEN + 1];
	char    OrnAmt[PUB_BATCHINFO_ORNAMT_LEN + 1];
	char    SucCnt[PUB_BATCHINFO_SUCCNT_LEN + 1];
	char    SucAmt[PUB_BATCHINFO_SUCAMT_LEN + 1];
	char    FalCnt[PUB_BATCHINFO_FALCNT_LEN + 1];
	char    FalAmt[PUB_BATCHINFO_FALAMT_LEN + 1];
	char    FRspCd[PUB_BATCHINFO_FRSPCD_LEN + 1];
	char    TxnSqn[PUB_BATCHINFO_TXNSQN_LEN + 1];
	char    Status[PUB_BATCHINFO_STATUS_LEN + 1];
	char    CmtFlg[PUB_BATCHINFO_CMTFLG_LEN + 1];
	char    SndTms[PUB_BATCHINFO_SNDTMS_LEN + 1];
	char    FTxnCd[PUB_BATCHINFO_FTXNCD_LEN + 1];
	char    ObjSvr[PUB_BATCHINFO_OBJSVR_LEN + 1];
	char    TrdTbl[PUB_BATCHINFO_TRDTBL_LEN + 1];
	char    ChkFlg[PUB_BATCHINFO_CHKFLG_LEN + 1];
	char    SumFlg[PUB_BATCHINFO_SUMFLG_LEN + 1];
	char    UpdFlg[PUB_BATCHINFO_UPDFLG_LEN + 1];
	char    RsvFld[PUB_BATCHINFO_RSVFLD_LEN + 1];
};
typedef struct _pub_batchinfo ST_PubBatchInfo;

struct _pub_batchhostresult
{
	char	LogNo[PUB_BATCHHOSTRESULT_LOGNO_LEN + 1];
	char	DskNo[PUB_BATCHHOSTRESULT_DSKNO_LEN + 1];
	char	BusTyp[PUB_BATCHHOSTRESULT_BUSTYP_LEN + 1];
	char	CrpCod[PUB_BATCHHOSTRESULT_CRPCOD_LEN + 1];
	char	ActNo[PUB_BATCHHOSTRESULT_ACTNO_LEN + 1];
	char	CrdNo[PUB_BATCHHOSTRESULT_CRDNO_LEN + 1];
	char	CcyCod[PUB_BATCHHOSTRESULT_CCYCOD_LEN + 1];
	char	TxnAmt[PUB_BATCHHOSTRESULT_TXNAMT_LEN + 1];
	char	HLogNo[PUB_BATCHHOSTRESULT_HLOGNO_LEN + 1];
	char	HRspCd[PUB_BATCHHOSTRESULT_HRSPCD_LEN + 1];
	char    HTxnSt[PUB_BATCHHOSTRESULT_HTXNST_LEN + 1];
	char	ChkFlg[PUB_BATCHHOSTRESULT_CHKFLG_LEN + 1];
};
typedef struct _pub_batchhostresult ST_PubBatchHostResult;

/*
 * deleted by kixiong at 2008-10-30 17:01
#ifdef	SYBASE
EXEC SQL END DECLARE SECTION;
#endif
*/

struct _pri_batchInfo
{
	char             FileCurr[BATCH_FILENAME_LEN + 1];
	char             FilIn[BATCH_FILENAME_LEN + 1];
	char             FilOut[BATCH_FILENAME_LEN + 1];
	char             FormatName[BATCH_FILENAME_LEN + 1];
	char             TableName[BATCH_TABLENAME_LEN + 1];
	char             TxnCode[TXNCOD_LEN + 1];
	int              ApplyLogNoFlag;
	ST_PubBatchInfo  sBatchInfo;
};
typedef struct _pri_batchInfo ST_PriBatchInfo;

XmlNode * findFormatNode( ETF *, TranData *);
#endif /* _HIBAT_H_ */
