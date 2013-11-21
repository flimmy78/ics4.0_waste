
-- ============================================================
--   广东烟草业务
--   Table: tbccusagt   (烟草客户签约表)
-- ============================================================
CREATE TABLE tbccusagt(  
  BrNo        CHAR(6)         DEFAULT ' ',
--分行号
  CAgtNo      CHAR(10)        DEFAULT ' ',
--单位编号
  CustId      CHAR(30)        ,
--烟草公司客户号
  DptId       CHAR(4)         DEFAULT ' ',
--银行公司编号
  ComId       CHAR(30)        DEFAULT ' ',
--公司编号
  TCusNm      CHAR(30)        DEFAULT ' ',
--客户姓名
  CusTyp      CHAR(2)         DEFAULT ' ',
--客户类型 01:私人客户,02:对公客户
  PasTyp      CHAR(2)         DEFAULT ' ',
--证件类型 0：身份证,1:护照,2:军官证,3:士兵证,4:回乡证,5:临时身份证,6:户口本,7:其他
  PasId      CHAR(18)        DEFAULT ' ',
--证件号码
  LiceId      CHAR(30)        DEFAULT ' ',
--营业执照号
  AccTyp      CHAR(2)         DEFAULT ' ',
--卡/账户类型 01:信用卡02:灵通卡,03:单位卡,04:储蓄账号,05:对公账户,06:金穗卡
  ActNo       CHAR(25)        DEFAULT ' ',
--卡/账户号码
  PasFlg      CHAR(1)         DEFAULT '0',
--密码校验标志
  PasWrd      CHAR(10)        DEFAULT ' ',
--密码
  Addres      CHAR(100)       DEFAULT ' ',
--联系地址
  TelNum      CHAR(20)        DEFAULT ' ',
--电话号码
  DevId       CHAR(20)        DEFAULT ' ',
--设备号
  Teller      CHAR(10)        DEFAULT ' ',
--烟草柜员号
  OpnDat      CHAR(8)         DEFAULT ' ',
--开户日期 
  ClsDat      CHAR(8)         DEFAULT ' ',
--销户日期
  Status      CHAR(1)         DEFAULT ' '
--状态  0:正常;1:注销
);



-- ============================================================
--   广东烟草业务
--   Table: tbcbasinf   (烟草基础信息表)
-- ============================================================
CREATE TABLE tbcbasinf(
  BrNo        CHAR(6)         DEFAULT ' ',
--分行号
  DptId       CHAR(4)         DEFAULT ' ',
--银行公司编号
  DptNam      CHAR(40)        DEFAULT ' ',
--公司单位全称  
  DevId       CHAR(15)        DEFAULT ' ',
--设备号
  Teller      CHAR(10)        DEFAULT ' ',
--操作号
  TranDt      CHAR(8)         DEFAULT ' ',
--交易日期
  ComKey      CHAR(16)        DEFAULT ' ',
--通讯密钥
  SigSts      CHAR(1)         DEFAULT ' '
--签到状态   0:签到，1:签退
);

