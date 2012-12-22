db2 connect to db2front
db2 "select * from afetxnjnl where cagtno='4410001099' and bustyp='YCTA1'"|more
db2 "select RsFld1 as TERMID, TLogNo as SYS_SEQ, RsFld2 as ICN, ChkTim as TIM, TxnAmt as TF, RsFld3 as BAL, '14' as TT from afetxnjnl where cagtno='4410001099' and bustyp='YCTA1'"|more
