/*原子函数返回值定义*/
#define   MsgTypLen      1   /*返回码类型*/
#define   RspCodLen      6   /*返回码*/
#define   RspMsgLen     56   /*返回信息*/
/*程序常量*/
#define   RPTPTH         "dat/term/send"
#define   PrtBufLen    180   /*打印缓冲*/
#define   AmtBufLen     20   /*大写金额*/
#define   BufLen        80   /*临时变量*/
/*传入参数*/
#define   NodNoLen       6   /*部门号*/
#define   BrNoLen        6   /*分行号*/
#define   MsgFmtLen      6   /*信息格式码*/
#define   ClrDatLen      8   /*清算日期*/
#define   SndCodLen     12   /*发送方代码*/
#define   RcvCodLen     12   /*接收方代码*/
#define   ClrSceLen      4   /*清算场次*/
#define   ActTypLen      1   /*帐号类型*/
#define   ActNoLen      21   /*交易帐号*/
#define   FilNamLen     32   /*报表文件名*/
#define   PrtDatLen      8   /*打印日期*/
#define   RptFilLen    256   /*报表文件完整路径*/
/*游标变量*/
#define   FilSeqLen     10   /*文件序号*/
#define   RcvBNoLen     11   /*经收处银行行号*/
#define   RcvBNmLen     60   /*经收处银行行名*/
#define   ActDatLen      8   /*银行提交日期*/
#define   SndActLen     35   /*收款帐号*/
#define   RcvActLen     35   /*缴款帐号*/
#define   ActNamLen     60   /*付款人名称*/
#define   TxnAmtLen     15   /*交易金额*/
#define   TaxNoLen      20   /*纳税人识别号*/
#define   TaxNamLen    100   /*纳税人名称*/
#define   TCrpNmLen     60   /*征收机关名称*/
#define   TLogNoLen     16   /*征收机关流水号*/
#define   FskNamLen     60   /*收款单位(国库)名称*/
#define   DtlNumLen      3   /*明细数目*/
#define   DtlSeqLen      3   /*明细顺序号*/
#define   TaxTypLen     40   /*税种名称*/
#define   PrjNamLen     60   /*品目名称*/
#define   LvlNamLen     40   /*预算级次名称*/
#define   TaxDtLen      17   /*税款所属日期*/
#define   DtlAmtLen     15   /*明细金额*/
#define   TSubCdLen     12   /*预算科目代码*/
#define   TVchNoLen     24   /*电子税票号(凭证号)*/
#define   PrtCntLen      2   /*打印次数*/
#define   SmrLen       200   /*备注*/
/*缴税打印内容横坐标*/
#define   PrtDatLoc     16 	 /*填发日期*/
#define	 	TVchNoLoc	    72   /*电子税票号*/ 
#define   TaxNoLoc      18   /*纳税人编码*/
#define   TaxNamLoc     18   /*纳税人全称*/
#define   RcvActLoc     18   /*付款人帐号*/
#define   TCrpNmLoc     68   /*征收机关名称*/
#define   RcvBNmLoc     68   /*经收处银行行名*/
#define   FskNamLoc     68   /*收款国库(银行)名称*/

#define   CapAmtLoc     42   /*大写金额*/
#define   TxnAmtLoc     84 	 /*交易金额小写*/

#define		ItmNamLoc			44	 /*款项内容*/ 
#define		TActDtLoc			74	 /*缴款日期*/
#define   PrtCntLoc     95   /*打印次数*/

#define   MaxRow        10   /*最多明细记录数*/
#define   TaxTypLoc     12   /*税种*/
#define 	LvlNamLoc		  36   /*预算科目、预算级次*/
#define   TaxDtLoc      62   /*所属时期*/
#define   DtlAmtLoc     84   /*明细金额*/

/*退库打印内容横坐标*/
#define   PrtDatLoc_Rt  12 	 /*填发日期*/
#define   TaxNoLoc_Rt   12   /*纳税人编码*/
#define   TaxNamLoc_Rt  12   /*纳税人全称*/
#define   RcvActLoc_Rt  12   /*付款人帐号*/
#define	 	TLogNoLoc_Rt	62   /*电子税票号*/ 
#define   TCrpNmLoc_Rt  62   /*征收机关名称*/
#define   RcvBNmLoc_Rt  62   /*经收处银行行名*/
#define   FskNamLoc_Rt  62   /*收款国库(银行)名称*/

#define		TSubCdLoc_Rt	12	 /*预算科目*/
#define   LvlNamLoc_Rt	23	 /*预算级次（退库）*/
#define		TRtnCdLoc_Rt	37	 /*退库原因*/
#define   DtlAmtLoc_Rt  68   /*明细金额*/

#define   CapAmtLoc_Rt  12   /*大写金额*/
#define   TxnAmtLoc_Rt  68 	 /*交易金额小写*/

#define		ItmNamLoc_Rt	12	 /*款项内容*/ 
#define		TActDtLoc_Rt	40	 /*缴款日期*/
#define   PrtCntLoc_Rt  62   /*打印次数*/

#define 	NodNoLoc_Rt	  12	 /*打印网点*/
#define 	TlrIdLoc_Rt	  40	 /*打印柜员*/

/*佛山 ETS*/
#define   PftFilLen     60   /*文件名*/
#define   ErrNumLen      6   /*错误笔数*/
#define   ErrAmtLen     15   /*错误金额*/
#define   LogNoLen      14   /*前置流水号*/
#define   TCrpCdLen     11   /*征收机关代码*/
#define   TCrpTpLen      1   /*征收机关类型*/
#define   TActDtLen      8   /*征收机关日期*/
#define   FskCodLen     11   /*国库代码*/
#define   TTxnTpLen      2   /*交易类型*/
#define   RtnCodLen      8   /*处理返回码*/
#define   TPayTpLen      1   /*缴款方式代码*/
#define   PrtFlgLen      1   /*打印完税标志*/
#define   CrpKndLen      4   /*企业注册类型*/
#define   TRtnCdLen     10   /*退库原因代码*/
#define		TRtnNmLen			30	 /*退库原因*/
#define	  TRtnTpLen      1   /*退税类型*/
#define   Rmk1Len        7   /*保留域一*/
#define   Rmk2Len       16   /*保留域二*/
