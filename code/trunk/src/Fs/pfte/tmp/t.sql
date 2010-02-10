--select LogNo, a.FilSeq, rtrim(a.RcvBNo), a.RcvBNm, a.ActDat, a.SndAct, a.RcvAct, a.TxnAmt, a.TaxNo, a.TaxNam, a.TCrpNm, a.FskNam, a.DtlNum, a.PrtCnt, a.Smr, b.TVchNo, substr(b.TCrpCd,1,1) from PftSec202Sum446 a, PftTxnJnl446 b where a.MsgFmt ='SEC202' and a.ClrDat ='20090323' and a.RcvCod ='61' and a.ClrSce ='0001' and ( a.ActTyp ='' or '' ='' ) and ( a.ActNo ='' or '' ='' ) and ( a.OpnNod=' ' or ' '=' ' ) and a.OpnBr='446999' and a.BTxnID=b.BTxnID order by a.ActNo;

--select OIFLag, ActDat TxnDat, BTxnID, RcvAct, TxnAmt, TaxNam, TLogNo, OpnBr TxnBr from PftSec202Sum446   where MsgFmt='SEC202' and ClrDat='20090323' and ClrSce='0001';

--select a.DtlSeq, a.TaxTyp, a.LvlNam, a.TSUBCD, rtrim(a.DtlAmt), a.TSubCd, a.TRtnCd, CoalEsce(b.TRtnNm,' ')
				from PftSec203Dtl446 a left join PftRtnCod446 b on a.TRtnCd=b.TRtnCd where PftFil ='SEC203_61_0001.20090414.txt';

select a.PFTFil, rtrim(a.RcvBNo), d.NodNam, a.ActDat, a.SndAct, a.RcvAct, a.TxnAmt, a.TaxNo, a.TaxNam, b.TCrpNm, a.FskCod, c.FskNam, a.DtlNum, a.PrtCnt, a.Smr, a.TVchNo, substr(a.TCrpCd,1,1),a.TCrpCd,substr(SndAct,33,1) from (PftSec203Sum446 a left join PftCrpInf446 b on a.TCrpCd=b.TCrpCd) left join pftFskInf446 c on  a.FskCod=c.FskCod , PftNodInf446 d where a.RcvBNo=d.RcvBNo and a.MsgFmt ='SEC203' and a.ClrDat ='20090416' and a.RcvCod ='61' and a.ClrSce ='1' and a.OpnBr='446999' and BilSts='S' order by a.ActNo;
