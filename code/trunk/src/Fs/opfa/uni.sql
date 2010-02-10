--SELECT a.*,CrpNam,TActNo  FROM icsadm.afetxnjnl a,icsadm.savcrpagr b,icsadm.savcrpinf c WHERE a.BrNo='446999' AND substr(FTxnTm,1,8)='20080701' AND a.CAgtNo='4460000005' and a.CAgtNo=b.CAgtNo and a.BrNo=b.BrNo and b.BrNo=c.BrNo and b.CrpCod=c.CrpCod ;
SELECT a.*,CrpNam,TActNo  FROM icsadm.afetxnjnl a,icsadm.savcrpagr b,icsadm.savcrpinf c WHERE a.BrNo='446999' AND a.CAgtNo='4460000005' and a.CAgtNo=b.CAgtNo and a.BrNo=b.BrNo and b.BrNo=c.BrNo and b.CrpCod=c.CrpCod ;
~
