create table lshjzd441(
BRNO char(6) not null,
NodNo char(6) not null,
TlrId1 char(7) not null,
TlrId2 char(7) not null,
IPAdr char(17) not null,
TrmNo char(8),
TRANTRM char(8) not null,
primary key(NodNo,TlrId1);

create table YTK_YCT(
FTxnTm char(14) not null,
ActDat char(8),
cagtno char(10),
ActNo char(21),
TCUSID char(32),
LogNo char(32),
TckNo char(32),
RsFld1 char(15),
RsFld2 char(15),
TxnAmt char(15),
RsFld3 char(15),
zt char(32),
ThdChk char(3),
primary key(FTxnTm)
);

insert into pubaplbus values('441999', '410','','LSHJ1','‘¡Õ®ø®≥‰÷µ');
insert into pubaplmng values('441999', '410', 'LSHJ1','','9999999999');
insert into pubjnldef values('441999', 'LSHJ1',' ','afetxnjnl',' ','1','1');
