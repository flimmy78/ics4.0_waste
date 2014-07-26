-- ============================================================
--   电力电费业务
--    银电客户签约表
-- ============================================================
CREATE TABLE efekcusagt(
  BrNo        CHAR(6)         DEFAULT ' ',    --分行号
  NodNo       CHAR(6)         DEFAULT ' ',    --机构号
  CAgtNo      CHAR(10)        DEFAULT ' ',    --单位编号
  WDMC        CHAR(64)        DEFAULT ' ',    --网点名称
  QDBZ        CHAR(1)         DEFAULT ' ',    --签订标志
  JFH         CHAR(20)        DEFAULT ' ',    --缴费号
  JSHMC       CHAR(64)        DEFAULT ' ',    --结算户名称
  XQYYHDM     CHAR(4)         DEFAULT ' ',    --签约银行代码
  XQYZH       CHAR(32)        DEFAULT ' ',    --签约账户
  XQYZHMC     CHAR(128)       DEFAULT ' ',    --签约账户名称
  ZHLX        CHAR(2)         DEFAULT ' ',    --账户类型
  ZJLX        CHAR(2)         DEFAULT ' ',    --证件类型
  ZJHM        CHAR(32)        DEFAULT ' ',    --证件号码
  LXDH        CHAR(20)        DEFAULT ' ',    --联系电话
  SJHM        CHAR(20)        DEFAULT ' ',    --手机号码
  EMAIL       CHAR(64)        DEFAULT ' ',    --E-MAIL
  BZ          CHAR(128)       DEFAULT ' ',    --备注
);

-- ============================================================
--   电力电费业务
--    开工表
-- ============================================================
CREATE TABLE efekinfctl(
  BrNo        CHAR(6)         DEFAULT ' ',    --分行号
  NodNo       CHAR(6)         DEFAULT ' ',    --机构号
  CAgtNo      CHAR(10)        DEFAULT ' ',    --单位编号
  JYLSH       CHAR(24)        DEFAULT ' ',    --交易流水号
  JYRQ        CHAR（8）       DEFAULT ' ',    --交易日期
  JYSJ        CHAR (6)        DEFAULT ' ',    --交易时间
  GDDW        CHAR(8)         DEFAULT ' ',    --供电单位
  YWBSH       CHAR(6)         DEFAULT ' ',    --业务标识号
  DWBM        CHAR(8)         DEFAULT ' ',    --单位编码
  CZRY        CHAR(20)        DEFAULT ' ',    --操作人员
  ZT          CHAR(1)         DEFAULT ' ',    --状态
  BZ          CHAR(128)       DEFAULT ' ',    --备注
);

-- ============================================================
--   电力电费业务
--    交易明细表(冲正用)
-- ============================================================
CREATE TABLE efekchkdtl(
  BrNo        CHAR(6)         DEFAULT ' ',    --分行号
  LogNo       CHAR(14)        DEFAULT ' ',    --机构号
  TLogNo      CHAR(30)        DEFAULT ' ',    --单位编号
  ActTyp      CHAR(1)         DEFAULT ' ',    --扣款账户类型
  JYLSH       CHAR(24)        DEFAULT ' ',    --交易流水号
  JYRQ        CHAR(8)         DEFAULT ' ',    --交易日期
  JYSJ        CHAR(6)         DEFAULT ' ',    --交易时间
  SFFS        CHAR(3)         DEFAULT ' ',    --收费方式
  FYLX        CHAR(3)         DEFAULT ' ',    --费用类型
  RZYHDM      CHAR(4)         DEFAULT ' ',    --入账银行代码
  DWBM        CHAR(8)         DEFAULT ' ',    --单位编码
  JFH         CHAR(20)        DEFAULT ' ',    --缴费号
  JSHMC       CHAR(64)        DEFAULT ' ',    --结算户名称
  YDDZ        CHAR(128)       DEFAULT ' ',    --用电地址
  KKZH        CHAR(32)        DEFAULT ' ',    --扣款账户
  KKZHMC      CHAR(128)       DEFAULT ' ',    --扣款账户名称
  BFJFBZ      CHAR(1)         DEFAULT ' ',    --部分缴费标志
  ZWLSH       CHAR(16)        DEFAULT ' ',    --账务流水号
  DFNY        CHAR(6)         DEFAULT ' ',    --电费年月
  HBFH        CHAR(5)         DEFAULT ' ',    --货币符号
  SKJE        CHAR(16)        DEFAULT ' ',    --实扣金额
); 