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
#define   TVchNoLen     20   /*电子税票号(凭证号)*/
#define   PrtCntLen      2   /*打印次数*/
#define   SmrLen       200   /*备注*/
/*打印内容横坐标*/
#define   VchNamLoc     50   /*凭证名称*/
#define   ActDatLoc     50   /*记帐日期*/
#define   ActNamLoc     12   /*付款人全称*/
#define   TCrpNmLoc     72   /*征收机关名称*/
#define   RcvActLoc     12   /*付款人帐号*/
#define   SndActLoc     72   /*收款人帐号*/
#define   FskNamLoc     72   /*收款国库(银行)名称*/
#define   RcvBNmLoc     12   /*经收处银行行名*/
#define   TxnAmtLoc     12   /*交易金额小写*/
#define   CapAmtLoc     72   /*大写金额*/
#define   TLogNoLoc     12   /*征收机关流水号*/
#define   TaxNoLoc      12   /*纳税人编码*/
#define   TaxNamLoc     72   /*纳税人全称*/

#define   MaxRow        10   /*最多明细记录数*/
#define   TaxTypLoc     12   /*税种*/
#define   TaxDtLoc      50   /*所属时期*/
#define   DtlAmtLoc     80   /*明细金额*/
#define   PrtCntLoc     12   /*打印次数*/
#define   PrtDatLoc     72   /*打印日期*/
/*广州市ETS*/
#define   PftFilLen     60   /*文件名*/
#define   ErrNumLen      6   /*错误笔数*/
#define   ErrAmtLen     15   /*错误金额*/
#define   LogNoLen      14   /*前置流水号*/
#define   TCrpCdLen     11   /*征收机关代码*/
#define   TActDtLen      8   /*征收机关日期*/
#define   FskCodLen     11   /*国库代码*/
#define   TTxnTpLen      2   /*交易类型*/
#define   RtnCodLen      8   /*处理返回码*/
#define   TPayTpLen      1   /*缴款方式代码*/
#define   PrtFlgLen      1   /*打印完税标志*/
#define   CrpKndLen      4   /*企业注册类型*/
#define   TRtnCdLen     10   /*退库原因代码*/
#define   Rmk1Len        7   /*保留域一*/
#define   Rmk2Len       16   /*保留域二*/
/*打印内容横坐标*/
#define   GzCapAmtLoc   12   /*大写金额*/
#define   GzTxnAmtLoc   72   /*交易金额小写*/
#define   GzSmrLoc      12   /*款项内容*/
#define   GzTLogNoLoc   72   /*征收机关流水号*/
#define   GzTaxNamLoc   12   /*纳税人全称*/
#define   GzTaxNoLoc    72   /*纳税人编码*/
