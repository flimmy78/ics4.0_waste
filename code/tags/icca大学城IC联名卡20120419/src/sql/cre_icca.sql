
-- ============================================================
--   大学城联名卡
--   Table: iccatxnjnl   (大学城联名卡充值流水表)
-- ============================================================
CREATE TABLE iccatxnjnl
(
  BrNo          CHAR(6)         DEFAULT ' ',
--分行号  
  LogNo         CHAR(14)        DEFAULT ' ',
--前置流水号
  TLogNo        CHAR(30)        DEFAULT ' ',
--第三方流水号
  HLogNo        CHAR(9)        DEFAULT ' ',
--主机流水号
  TckNo         CHAR(12)        DEFAULT ' ',
--会计流水号
  ActDat        CHAR(8)         DEFAULT ' ',
--会计日期
  CrdNo         CHAR(30)        DEFAULT ' ',
--卡号
  ActNo         CHAR(30)        DEFAULT ' ',
--帐号
  ICBak         CHAR(30)        DEFAULT ' ',
--银行电子钱包账号
  ICSch         CHAR(30)        DEFAULT ' ',
--校园卡电子钱包账号
  TCusID        CHAR(30)        DEFAULT ' ',
--客户标志
  TCusNm        CHAR(60)        DEFAULT ' ',
--客户姓名
  IDNo          CHAR(30)        DEFAULT ' ',
--证件号码
  TxnAmt        CHAR(15)        DEFAULT ' ',
--交易金额
  Fee           CHAR(15)        DEFAULT ' ',
--手续费
  OrgNo         CHAR(6)        DEFAULT ' ',
--机构号
  TlrId         CHAR(7)        DEFAULT ' ',
--交易柜员
  MchID         CHAR(6)         DEFAULT ' ',
--代理商编号
  CAgtNo        CHAR(10)        DEFAULT ' ',
--单位编号
  PosNo         CHAR(5)         DEFAULT ' ',
--圈存机编号
  FTxnTm        CHAR(14)        DEFAULT ' ',
--前置机时间
  TTxnTm        CHAR(14)        DEFAULT ' ',
--第三方时间
  TxnCod        CHAR(6)         DEFAULT ' ',
--交易码
  TTxnCd        CHAR(6)         DEFAULT ' ',
--第三方交易码
  BusCls        CHAR(2)         DEFAULT ' ',
--业务种类 01:圈存,02:消费
  ChkFlg        CHAR(1)         DEFAULT '0',
--对账标志
  HTxnSt        CHAR(1)         DEFAULT ' ',
--主机状态
  HRspCd        CHAR(6)         DEFAULT ' ',
--主机返回码
  TTxnSt        CHAR(1)         DEFAULT ' ',
--第三方状态
  TRspCd        CHAR(6)         DEFAULT ' ',
--第三方返回码
  TxnSts        CHAR(1)         DEFAULT 'U'
--交易状态 0交易成功；S记账成功；U初始；T可疑；C冲正
) ;


