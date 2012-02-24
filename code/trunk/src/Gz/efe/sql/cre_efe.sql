
-- ============================================================
--   电力电费业务
--   Table: efeinfctl   (银电开工控制表)
-- ============================================================
CREATE TABLE efeinfctl
(
  BrNo          CHAR(6)         DEFAULT ' ',
--分行号  
  StrAddr       CHAR(12)        DEFAULT ' ',
--源地址
  DstAddr       CHAR(12)        DEFAULT ' ',
--目的地址
  WdoDat        CHAR(8)         DEFAULT ' ',
--工作日期
  ECD           CHAR(8)         DEFAULT ' ',
--收付费企业代码
  CreOrg        CHAR(12)        DEFAULT ' ',
--委托节点代码
  OprCod        CHAR(8)         DEFAULT ' ',
--操作柜员代码
  DLIP          CHAR(15)        DEFAULT ' ',
--供电局前置IP
  DlTxt         CHAR(128)       DEFAULT ' ',
--电力备注
  Status        CHAR(1)         DEFAULT '1'
--电力签到签退标志 0-签退；1-签到
) ;


-- ============================================================
--   电力电费业务
--   Table: efechkinf   (银电对账信息表)
-- ============================================================
CREATE TABLE efechkinf(  
  BrNo        CHAR(6)         DEFAULT ' ',
--分行号
  CAgtNo      CHAR(10)        DEFAULT ' ',
--单位编号
  LogNo       CHAR(14)        DEFAULT ' ',
--前置流水号
  TLogNo      CHAR(30)        DEFAULT ' ',
--电力流水号
  TckNo       CHAR(12)        DEFAULT ' ',
--会计流水号
  ECD         CHAR(12)         DEFAULT ' ',
--收付费企业代码
  WDO         CHAR(8)         DEFAULT ' ',
--工作日期
  EDD         CHAR(3)         DEFAULT ' ',
--费项代码  
  JFH         CHAR(32)        DEFAULT ' ',
--缴费号
  KKB         CHAR(12)        DEFAULT ' ',
--扣款行行号
  ActNo       CHAR(32)        DEFAULT ' ',
--扣款账户/卡号
  KAT         CHAR(1)         DEFAULT ' ',
--扣款账户类型 0—对公帐户 1—对私储蓄 2—对私信用卡 3—对私借记卡 4—外币
  CUN         CHAR(3)         DEFAULT ' ',
--货币类型
  TxnAmt      CHAR(12)        DEFAULT ' ',
--扣款金额
  KFG         CHAR(1)         DEFAULT '0', 
--扣款方式 0-余额不足不扣款，1-余额不足亦扣款(缺省为0)
  ActNam      CHAR(64)        DEFAULT ' ', 
--客户名称                              
  PCF         CHAR(1)         DEFAULT ' ', 
--部分缴费标志 1 允许部分缴费 2 必须全部缴费                                      
  MNT         CHAR(2)         DEFAULT ' ', 
--资金种别 付款方式 默认01现金
  JBR         CHAR(8)         DEFAULT ' ', 
--经办人编号
  GDO         CHAR(16)        DEFAULT ' ', 
--供电操作员代码                                   
  WYSB        CHAR(30)        DEFAULT ' ', 
--唯一识别码                                      
  SFF         CHAR(2)         DEFAULT ' ', 
--收费方式  
--01-单笔现金 02-汇总现金 03-批量代扣 04-实时代扣 05-POS机划扣
--06-支票 07-汇票 08-网银 09-ATM机                                   
  TxnCod      CHAR(6)         DEFAULT ' ', 
--交易码
  Status      CHAR(1)         DEFAULT 'U'
--状态 S记账成功；U初始；T可疑；C冲正；X冲销
);

-- ============================================================
--   电力电费业务
--   Table: efechkdtl   (银电对账明细表)
-- ============================================================
CREATE TABLE efechkdtl(  
  BrNo        CHAR(6)         DEFAULT ' ',
--分行号
  LogNo       CHAR(14)        DEFAULT ' ',
--前置流水号
  TLogNo      CHAR(30)        DEFAULT ' ',
--电力流水号
  JFXH        CHAR(2)         DEFAULT ' ',
--缴费项序号
  JFJE        CHAR(12)        DEFAULT ' ',
--缴费项金额
  MON         CHAR(6)         DEFAULT ' ',
--月份  
  JLD         CHAR(5)         DEFAULT ' ',
--计量点号
  YSH         CHAR(16)        DEFAULT ' ',
--应收凭证号
  CPS         CHAR(12)        DEFAULT ' ',
--本金
  MNS         CHAR(2)         DEFAULT ' ',
--电费次数
  PCC         CHAR(12)        DEFAULT ' '
--违约金
);

-- ============================================================
--   电力电费业务
--   Table: efecusagt   (银电客户签约表)
-- ============================================================
CREATE TABLE efecusagt(  
  BrNo        CHAR(6)         DEFAULT ' ',
--分行号
  PAgtNo      CHAR(13)        DEFAULT ' ',
--客户协议编号
  CAgtNo      CHAR(10)        DEFAULT ' ',
--单位编号
  SBN         CHAR(12)        DEFAULT ' ',
--发起行行号/收付费企业代码/清算中心编号
  ECD         CHAR(12)        DEFAULT ' ',
--收付费企业代码
  WDO         CHAR(8)         DEFAULT ' ',
--工作日期  
  EDD         CHAR(3)         DEFAULT ' ',
--费项代码
  JFH         CHAR(32)        DEFAULT ' ',
--缴费号
  UsrNam      CHAR(64)        DEFAULT ' ',
--用户名称
  KKB         CHAR(12)        DEFAULT ' ',
--行号
  ActNo       CHAR(32)        DEFAULT ' ',
--账户/卡号
  KAT         CHAR(1)         DEFAULT ' ',
--账户类型
  ActNam      CHAR(64)        DEFAULT ' ',
--客户名称
  GPF         CHAR(1)         DEFAULT ' ',
--个人/集团标志 G:集团；P:个人
  IdTyp       CHAR(2)         DEFAULT ' ',
--证件类型
  IdNo        CHAR(32)        DEFAULT ' ',
--证件号码
  ZPF         CHAR(1)         DEFAULT ' ',
--账单邮寄类型
  FPF         CHAR(1)         DEFAULT ' ',
--发票邮寄类型
  JLD         CHAR(5)         DEFAULT ' ',
--计量点号
  FPM         CHAR(40)        DEFAULT ' ',
--发票邮寄人
  FPC         CHAR(6)         DEFAULT ' ',
--发票邮寄邮编
  FPA         CHAR(60)        DEFAULT ' ',
--发票邮寄地址
  ZPM         CHAR(40)        DEFAULT ' ',
--帐单邮寄人
  ZPC         CHAR(6)         DEFAULT ' ',
--帐单邮寄邮编
  ZPA         CHAR(60)        DEFAULT ' ',
--帐单邮寄地址
  YBZ         CHAR(1)         DEFAULT ' ',
--余额不足通知方式
  EML	        CHAR(64)        DEFAULT ' ',
--E-MAIL
  MOB         CHAR(30)        DEFAULT ' ',
--联系手机号
  TEL         CHAR(60)        DEFAULT ' ',
--联系电话
  TXT         CHAR(64)        DEFAULT ' ',
--备注
  Status      CHAR(1)         DEFAULT ' '
--状态  0:正常;1:注销
);


-- ============================================================
--   电力电费业务
--   Table: efebatinf   (银电批扣表)
-- ============================================================
CREATE TABLE efebatinf(  
  BrNo        CHAR(6)         DEFAULT ' ',
--分行号
  CAgtNo      CHAR(10)        DEFAULT ' ',
--单位编号
  LogNo       CHAR(14)        DEFAULT ' ',
--前置流水号
  TLogNo      CHAR(30)        DEFAULT ' ',
--第三方流水号
  DskNo       CHAR(12)        NOT NULL,
--批次号
  TckNo       CHAR(12)        DEFAULT ' ',
--会计流水号
  ActDat      CHAR(8)         DEFAULT ' ',
--工作日期
  PID         CHAR(20)        DEFAULT ' ',
--批量代收信息标识
  EDD         CHAR(3)         DEFAULT ' ',
--费项代码
  PNO         CHAR(10)        DEFAULT ' ',
--编号
  JFH         CHAR(32)        DEFAULT ' ',
--缴费号
  KKB         CHAR(12)        DEFAULT ' ',
--扣款行行号
  ActNo       CHAR(32)        DEFAULT ' ',
--扣款账户/卡号
  ActNam      CHAR(64)        DEFAULT ' ', 
--账号客户名称
  CUN         CHAR(3)         DEFAULT ' ',
--货币类型
  TxnAmt      CHAR(12)        DEFAULT ' ',
--扣款金额 
  KFG         CHAR(1)         DEFAULT ' ', 
--扣款方式 1-余额不足亦扣款，2-余额不足不扣款
  DMO         CHAR(40)        DEFAULT ' ',
--说明
  DEPT        CHAR(8)         DEFAULT ' ',
--供电企业
  MON         CHAR(6)         DEFAULT ' ',
--月份
  MNS         CHAR(2)         DEFAULT ' ',
--电费次数
  CusNam      CHAR(40)        DEFAULT ' ',
--客户名称
  GDZH        CHAR(32)        DEFAULT ' ',
--供电企业账号 
  YKDF        CHAR(12)        DEFAULT ' ',
--应扣电费  
  PCC         CHAR(12)        DEFAULT ' ',
--违约金
  JLD         CHAR(5)         DEFAULT ' ',
--计量点号
  YSH         CHAR(16)        DEFAULT ' ',
--应收凭证号                           
  WYSB        CHAR(30)        DEFAULT ' ', 
--唯一识别码                                                                    
  TxnCod      CHAR(6)         DEFAULT ' ', 
--交易码
  Status      CHAR(1)         DEFAULT 'U'
--状态 S记账成功；U初始；T可疑；C冲正；X冲销
);

-- ============================================================
--   电力电费业务
--   Table: efechkrec   (银电对账记录表)
-- ============================================================
CREATE TABLE efechkrec(  
  BrNo        CHAR(6)         DEFAULT ' ',
--分行号
  ActDat      CHAR(8)         DEFAULT ' ',
--会计日期
  SndTim      CHAR(14)        DEFAULT ' ',
--发送时间
  LogNo       CHAR(14)        DEFAULT ' ',
--查询流水号
  ChkFil      CHAR(30)        DEFAULT ' ',
--对账文件名 
  TRspCd      CHAR(2)         DEFAULT ' ',
--供电局返回代码
  RtnMsg      CHAR(60)        DEFAULT ' '
--供电局返回信息    
);