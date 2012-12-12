-- ============================================================
--   羊城通自助充值审计数据表
--   Table: yctafiletj
-- ============================================================
CREATE TABLE yctafiletj
(
  ActDat       CHAR(8)         not null,
--会计日期
  SNO          CHAR(5)         DEFAULT ' ',
--序列号,1:JY文件;2:CZ文件
  FNAME        CHAR(24)        DEFAULT ' ',
--文件名
  FRS          CHAR(10)        DEFAULT ' ',
--文件记录总数
  RFS          CHAR(12)        DEFAULT ' ',
--记录金额总数
);
create index ni1_yctafiletj on yctafiletj(ActDat, SNO);