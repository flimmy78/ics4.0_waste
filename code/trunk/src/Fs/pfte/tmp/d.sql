select DtlSeq, TaxTyp, PrjNam, LvlNam, TaxDt, DtlAmt, TSubCd
        from PftSec202Dtl446
       where MsgFmt ='SEC202'
         and ClrDat ='20090323'
         and RcvCod ='61'
         and ClrSce ='0001'
         and FilSeq ='5'
    order by DtlSeq;
