drop table PntFccz;
drop table pntFcgk;
drop table PntHzfczh;

--财政专户分成信息文件
create table PntFccz
(
  BankCd       char(30)   default '',
--银行编码                           
  RcvAct       char(50)   default '',
--汇缴账户                           
  TxnDat       char(8)    not null,
--分成日期                           
  CityCd       char(12)   default '',
--节段标识(行政区域编码)             
  TotNum       char(10)   default '',
--总笔数                             
  TotAmt       char(16)   default '',
--总金额                             
  ActNam       char(50)   default '',
--账户名称                           
  ActBnk       char(100)  default '',
--账户所在银行                       
  ActNo        char(50)   default '',
--账号                               
  TitNum       char(10)   default '',
--笔数                               
  TitAmt       char(16)   default '',
--分成总金额                         
  TCrpCd       char(30)   default '',
--执收单位编码
  TCrpNm       char(100)  default '',
--执行单位名称                       
  PrjCod       char(14)   default '',
--收费项目编码                       
  PrjNam       char(100)  default '',
--收费项目名称                       
  DtlAmt       char(16)   default '',
--分成金额                           
  DtlSts       char(1)    default '',
--分成标识(1未分成,2已分成)
  DtlDat       char(8)    default '',
--达账日期
  DtAmt        char(16)   default ''
--达账金额  
);

--国库分成信息文件
create table PntFcgk
(
  BankCd       char(30)   default '',
--银行编码
  RcvAct       char(50)   default '',
--汇缴账户
  TxnDat       char(8)     not null,
--分成日期
  CityCd       char(12)   default '',
--节段标识(行政区域编码)
  TotNum       char(10)   default '',
--总笔数
  TotAmt       char(16)   default '',
--总金额
  ActNam       char(50)   default '',
--账户名称
  ActBnk       char(100)  default '',
--账户所在银行
  ActNo        char(50)   default '',
--账号
  TitNum       char(10)   default '',
--总笔数
  TitAmt       char(16)   default '',
--分成总金额
  SubCod       char(9)    default '',
--预算科目编码
  SubNam       char(100)  default '',
--预算科目名称
  PrjCod       char(14)   default '',
--收费项目编码
  PrjNam       char(100)  default '',
--收费项目名称
  DtlAmt       char(16)   default '',
--分成金额
  DtlSts       char(1)    default '',
--分成标识(1未分成,2已分成)
  DtlDat       char(8)    default '',
--达账日期
  DtAmt        char(16)   default ''
--达账金额  
);

--非税系统产生的汇总分成国库文件
create table PntHzfczh
(
  ZHBankCd    char(30)   default '',
--专户银行编码
  ZHBankNm    char(100)  default '',
--专户银行名称
  TxnDat      char(8)     not null,
--分成日期
  TotNum      char(12)   default '',
--节段行数
  ZHActNo     char(100)  default '',
--专户账户名称
  ZHActNm     char(50)   default '',
--专户账号
  TotAmt       char(16)   default '',
--分成总金额
  DSBankNo    char(30)    default '',
--代收银行编码
  DSBankNm    char(100)   default '',
--代收银行名称
  DSActNo     char(50)    default '',
--代收账号
  ZCKM        char(20)    default '',
--支出科目
  JJCK        char(20)    default '',
--经济科目
  TitNum       char(10)   default '',
--总笔数
  TitAmt       char(16)   default '',
--分成金额
  TCrpCd       char(20)   default '',
--执收单位编码
  TCrpNm       char(100)  default '',
--执行单位名称                       
  PrjCod       char(14)   default '',
--收费项目编码                       
  PrjNam       char(100)  default '',
--收费项目名称                       
  DtlAmt       char(16)   default '',
--分成金额 
  RevDat       char(10)   default '',
--收费日期 
  DtlSts       char(1)    default ''
--分成标识(1未分成,2已分成)                        
);
		
