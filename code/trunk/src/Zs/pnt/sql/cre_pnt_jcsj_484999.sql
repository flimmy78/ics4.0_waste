drop table PntSfxm;
drop table Pntdwxx;
drop table PntDwxm;
drop table PntPjlx;
drop table PntPjff;
drop table PntXmpj;
drop table PntQyxx;
drop table PntPjNum;
drop table PntPrgx;


--收费项目信息
create table PntSfxm
(
	BrNo          char(6)    not null,
--分行号
	PrjCod        char(14)   not null,
--收费项目编码
  PrjNam        char(200)  not null,
--收费项目名称
  SubCod        char(9)    default '',
--预算科目编码
  SubNam        char(100)  default '',
--预算科目名称
  SfxmSts       char(1)    not null
--状态
  
);

--单位信息
create table PntDwxx
(
	BrNo          char(6)    not null,
--分行号
  TCrpCd        char(30)   not null,
--单位编码
  TCrpNm        char(100)  not null,
--单位名称
  DwxxSts       char(1)    not null
--状态
);

--单位项目信息
create table PntDwxm
(
	BrNo          char(6)    not null,
--分行号
  TCrpCd        char(30)   not null,
--单位编码
	PrjCod        char(14)    not null
--收费项目编码
);

--票据类型信息
create table PntPjlx
(
	BrNo          char(6)    not null,
--分行号
	TBilTp        char(8)    not null,
--票据类型编码
	TBilNm        char(50)   not null,
--票据类型名称
  PjlxSts       char(1)    not null
--状态(0表示禁用,1为启用)

);

--票据发放信息
create table PntPjff
(
	BrNo          char(6)    not null,
--分行号
	TBilTp        char(8)    not null,
--票据类型编码
  TBilStar      char(20)   not null,
--票据起始号码
  TBilEnd       char(20)   not null,
--票据终止号码
  TBilTot       char(10)   not null,
-- 票据份数
  TBilSts       char(1)    not null,
--票据状态(1为正常,3为已禁止)
  TBilReSts     char(1)    not null
--票据分解状态(1为未分解,2为已分解)
 
);

--票据号码
create table PntPjNum
(
  TBilTp        char(8)    not null,
--票据类型编码
  TBilNo        char(20)   not null,
--票据号码
  TBilSts       char(1)    not null,
--票据状态(1为未使用,2为已使用,3为禁止使用,4为临时使用)
  TBilFFSts    char(1)     default '',
--票据发放状态(1为未分配,2为已分配)
  TBilNod      char(6)    default '',
--使用地点(记录网点号)
  TBilSeq      char(6)    default ''
--序号
);

--项目票据信息表
create table PntXmpj
(
	BrNo          char(6)    not null,
--分行号
	PrjCod        char(14)    not null,
--收费项目编码
	TBilTp        char(8)    not null
--票据类型编码

);

--区域信息
create table PntQyxx
(
	BrNo          char(6)    not null,
--分行号
  AreaNo        char(12)   not null,
--区域编码
  AreaNm        char(50)   not null
--区域名称

);

--通知书前缀与银行汇缴账户的关系
create table PntPrgx
(
	BrNo          char(6)    not null,
--分行号
  TCrpHD        char(2)    not null,
--通知书前缀
  PActNm        char(100)  not null,
--账户名称
  PActNo        char(50)   not null
--汇缴账户

);




