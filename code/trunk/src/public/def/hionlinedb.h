#include "hibppubdef.h"

/*
#ifdef	SYBASE
EXEC SQL BEGIN DECLARE SECTION;
#endif
*/

/*流水表公共结构*/
struct _pubtxnjnl {
	char  LogNo  [LOGNO_LEN   + 1];
	char  TTxnCd [TTXNCD_LEN  + 1];
	char  TxnCod [TXNCOD_LEN  + 1];
	char  TxnTyp [FLAG_LEN  + 1];
	char  BusTyp [BUSTYP_LEN  + 1];
	char  CrpCod [CRPCOD_LEN  + 1];
	char  ActDat [DATE_LEN  + 1];
	char  CcyCod [CCYCOD_LEN + 1 ];
	char  TxnAmt [AMOUNT_LEN  + 1];
	char  Fee    [AMOUNT_LEN  + 1];
	char  ActNo  [ACTNO_LEN   + 1];
	char  CrdNo  [CRDNO_LEN   + 1];
	char  OrgNo  [ORGNO_LEN   + 1];
	char  NodNo  [NODNO_LEN   + 1];
	char  TlrId  [TLRID_LEN   + 1];
	char  CntRId [CNTRID_LEN   + 1];
	char  NodTrc [NODTRC_LEN  + 1];
	char  TxnCnl [TXNCNL_LEN  + 1];
	char  ItgTyp [FLAG_LEN  + 1];
	char  FTxnTm [DATETIME_LEN  + 1];
	char  FRspCd [FRSPCD_LEN + 1];
	char  HLogNo [HLOGNO_LEN  + 1];
	char  HRspCd [HRSPCD_LEN + 1];
	char  HTxnSt [FLAG_LEN  + 1];
	char  HPrChk [FLAG_LEN  + 1];
	char  HstChk [FLAG_LEN  + 1];
	char  TCusId [TCUSID_LEN  + 1];
	char  TCusNm [TCUSNM_LEN + 1];
	char  TActDt [DATE_LEN  + 1];
	char  TLogNo [TLOGNO_LEN  + 1];
	char  TRspCd [TRSPCD_LEN + 1];
	char  TTxnSt [FLAG_LEN  + 1];
	char  ThdChk [FLAG_LEN  + 1];
	char  TxnSts [FLAG_LEN  + 1];
	char  TxnAtr [ATTRIBUTE_LEN  + 1];
	char  MstChk [FLAG_LEN  + 1];
	char  LChkTm [LCHKTM_LEN  + 1];
};

typedef struct _pubtxnjnl PubTxnJnl;

/*代理服务信息结构*/
struct _pubcrpagt {
	char BusTyp   [BUSTYP_LEN    + 1];
	char CrpCod   [CRPCOD_LEN    + 1];
	char CrpSub   [CRPSUB_LEN    + 1];
	char BusNam   [BUSNAM_LEN    + 1];
	char AgtNod   [AGTNOD_LEN    + 1];
	char OpnMod   [FLAG_LEN    + 1];
	char TxnMod   [FLAG_LEN    + 1];
	char SStrDt	  [DATE_LEN + 1];
	char SClsDt	  [DATE_LEN + 1];
	char SvrCnl   [SVRCNL_LEN    + 1];
	char SvrSts   [FLAG_LEN    + 1];
};

typedef struct _pubcrpagt PubCrpAgt;

/*协议信息公共结构*/
struct _pubcusagr {
	char BusTyp [BUSTYP_LEN  + 1];      
	char CrpCod [CRPCOD_LEN  + 1];      
	char CusId  [CUSID_LEN   + 1];     
	char ActTyp [ACTTYP_LEN  + 1];      
	char ActNo  [ACTNO_LEN   + 1];     
	char CrdNo  [CRDNO_LEN   + 1];     
	char ActSqn [ACTSQN_LEN  + 1];      
	char TCusId [TCUSID_LEN  + 1];      
	char TCusNm[TCUSNM_LEN + 1];       
	char TlrId  [TLRID_LEN   + 1];     
	char NodNo  [NODNO_LEN   + 1];     
	char CnlSts [CNLSTS_LEN  + 1];
	char OpnDat [DATE_LEN  + 1];      
	char EffDat [DATE_LEN  + 1];      
	char IvdDat [DATE_LEN  + 1];      
	char Bal    [AMOUNT_LEN + 1];
	char QutFlg [FLAG_LEN + 1];
	char QutAmt [AMOUNT_LEN + 1];
	char ActFlg [FLAG_LEN + 1];
	char Status [FLAG_LEN  + 1];
	char CTblNm [TBLNAM_LEN + 1];
};

typedef struct _pubcusagr PubCusAgr;      

/*客户信息结构*/
struct _pubcusinf {
	char CusId [CUSID_LEN  + 1];
	char CusNam[CUSNAM_LEN + 1];
	char ActTyp[ACTTYP_LEN + 1];
	char CrdNo [CRDNO_LEN  + 1];
	char ActNo [ACTNO_LEN  + 1];
	char TlrId [TLRID_LEN  + 1];
	char NodNo [NODNO_LEN  + 1];
	char IdTyp [IDTYP_LEN  + 1];
	char IdCrd [IDCRD_LEN  + 1];
	char Addr  [ADDR_LEN   + 1];
	char PostNo[POSTNO_LEN + 1];
	char FixTel[FIXTEL_LEN + 1];
	char MobTel[MOBTEL_LEN + 1];
	char Status[FLAG_LEN + 1];
};

typedef struct _pubcusinf PubCusInf;

/*公司信息结构*/
struct _pubcrpinf {
	char CrpCod[CRPCOD_LEN + 1];
	char CrpNam[CRPNAM_LEN + 1];
	char Addr  [ADDR_LEN   + 1];
	char TelNo [TELNO_LEN  + 1];
	char ComMan[COMMAN_LEN + 1];
	char PostNo[POSTNO_LEN + 1];
	char CrpInf[CRPINF_LEN + 1];
};

typedef struct _pubcrpinf PubCrpInf;

/*第三方系统信息结构*/
struct _pubthdinf {
	char BusTyp[BUSTYP_LEN + 1];
	char CrpCod[CRPCOD_LEN + 1];
	char TrmNo [TRMNO_LEN  + 1];
	char TlrId [TLRID_LEN  + 1];
	char IsMust[FLAG_LEN + 1];
	char WhoSgn[FLAG_LEN + 1];
	char Status[FLAG_LEN + 1];
	char SgnDat[DATE_LEN + 1];
	char SgnTm [TIME_LEN  + 1];
	char McKey1[MCKEY1_LEN + 1];
	char McKey2[MCKEY2_LEN + 1];
	char ProCod[PROCOD_LEN + 1];
	char IpAdr [IPADR_LEN  + 1];
	char IpPort[IPPORT_LEN + 1];
};

typedef struct _pubthdinf PubThdInf;

/*平台信息结构*/
struct _pubpltinf {
	char SysId [SYSID_LEN  + 1];
	char LogNo [LOGNO_LEN  + 1];
	char BLogNo[BLOGNO_LEN  + 1];
	char ActDat[DATE_LEN + 1];
	char DatEnd[DATEND_LEN + 1];
	char EleBk [BKNO_LEN + 1];
};

typedef struct _pubpltinf PubPltInf;

/*业务数据存储*/
struct _pubusrdat {
	char RecKey[RECKEY_LEN + 1];
	char UsrDat[USRDAT_LEN + 1];
	char CurPag[PAGNUM_LEN + 1];
	char EndPag[PAGNUM_LEN + 1];
};

typedef struct _pubusrdat PubUsrDat;

/*网点信息表*/
struct _pubnodinf {
	char Status[FLAG_LEN + 1];
	char NodNo [NODNO_LEN + 1];
	char SBkNo [SBKNO_LEN + 1];
	char SRtcBk[BKNO_LEN + 1];
	char OPCCod[OPCCOD_LEN + 1];
	char SetBk [SETBK_LEN + 1];
	char RetNod[NODNO_LEN + 1];
	char CtlNod[NODNO_LEN + 1];
	char NodNam[NODNAM_LEN + 1];
	char OrgNo [ORGNO_LEN + 1];
};

typedef struct _pubnodinf PubNodInf;

/*网点协议表*/
struct _pubnodagr {
	char NodNo [NODNO_LEN + 1];
	char BusTyp[BUSTYP_LEN + 1];
	char CrpCod[CRPCOD_LEN + 1];
	char NodNam[NODNAM_LEN + 1];
	char BusNam[BUSNAM_LEN + 1];
	char OrgNo [ORGNO_LEN + 1];
	char ActNo [ACTNO_LEN + 1];
};

/*临时数据缓存表*/
struct _pubtdstbl {
	char TxnCod[TXNCOD_LEN + 1];
	char RecKey[RECKEY_LEN + 1];
	char RecIdx[RECIDX_LEN + 1];
	char Rec   [ETFREC_LEN + 1];
};
typedef struct _pubtdstbl PubTdsTbl;

/*业务管理表*/
struct _pubaplmng {
	char AplCls[APLCLS_LEN + 1];
	char BusTyp[BUSTYP_LEN + 1];
	char BusSub[BUSSUB_LEN + 1];
	char CrpCod[CRPCOD_LEN + 1];
};
typedef struct _pubaplmng PubAplMng;

/*
#ifdef	SYBASE
EXEC SQL END DECLARE SECTION;
#endif
*/

