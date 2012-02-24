
-- ============================================================
--   电力电费业务
--   Table: efeaclrtbl   (广州电力清算日期表)
-- ============================================================
CREATE TABLE efeaclrtbl
(
  BrNo          CHAR(6)         DEFAULT ' ',
--分行号  
  ClrDat        CHAR(8)         DEFAULT ' ',
--清算日期
  ClrTim        CHAR(6)         DEFAULT ' ',
--清算时间
  ClrSts        CHAR(1)         DEFAULT ' ',
--清算状态  0:交易状态；1:清算状态
  AutFlg        CHAR(1)         DEFAULT ' '
--系统定时自动清算标志  0:自动清算生效；1:禁止自动清算  
) ;


-- ============================================================
--   电力电费业务
--   Table: efeaclrlog   (广州电力清算日期表修改日志)
-- ============================================================
CREATE TABLE efeaclrlog
(
  BrNo          CHAR(6)         DEFAULT ' ',
--分行号 
  NodNo         CHAR(6)         DEFAULT ' ',
--网点号  
  ClrDat        CHAR(8)         DEFAULT ' ',
--修改清算日期
  ClrTim        CHAR(6)         DEFAULT ' ',
--修改清算时间
  ClrSts        CHAR(1)         DEFAULT ' ',
--修改清算状态  0:交易状态；1:清算状态
  AutFlg        CHAR(1)         DEFAULT ' ',
--修改系统定时自动清算标志  0:自动清算生效；1:禁止自动清算  
  TlrId         CHAR(8)         DEFAULT ' ',
--修改柜员
  LogDat        CHAR(8)         DEFAULT ' ',
--修改日期时间
  LogTim        CHAR(6)         DEFAULT ' '
--修改清算时间
) ;


-- ============================================================
--   电力电费业务
--   Table: efeaclrdtl   (广州电力清算明细表)
-- ============================================================
CREATE TABLE efeaclrdtl
(
  BrNo          CHAR(6)         DEFAULT ' ',
--分行号
  NodNo         CHAR(6)         DEFAULT ' ',
--网点号 
  TlrId         CHAR(8)         DEFAULT ' ',
--清算柜员
  CAgtNo        CHAR(10)        DEFAULT ' ',
--清算单位协议号
  ClrDat        CHAR(8)         DEFAULT ' ',
--清算日期
  ClrTim        CHAR(6)         DEFAULT ' ',
--清算时间
  ClrRst        CHAR(1)         DEFAULT ' ',
--清算情况  0:未清算；1:已清算
  ClrTyp        CHAR(1)         DEFAULT ' ',
--清算类型  0:自动清算；1:手工清算
  ClrTot        CHAR(8)         DEFAULT ' ',
--清算笔数
  ClrAmt        CHAR(15)        DEFAULT ' '
--清算金额
) ;
