drop table PntWtzw;

--问题账务信息文件
create table PntWtzw
(
  RevDt       char(8)    not null,
--收款日期
  TitNum       char(10)   not null,
--总笔数
  TBilTp        char(8)    not null,
--票据类型
  TBilNo        char(20)   not null,
--票据号码
  TError        char(100)  not null,
--出错原因
CONSTRAINT PK_PNTWTZW PRIMARY KEY( RevDt,TBilTp,TBilNo )
);
