drop table PntPjNum;
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
