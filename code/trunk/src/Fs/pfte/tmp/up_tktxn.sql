update pftsec203sum446 set bilsts='U' where clrdat='20090417' and BilSts='F';
update pftfilinf446 set filsts='1' where PFTFIL='SEC203_61_0001.20090417.txt';
delete from pfttxnjnl446 where clrdat='20090417' and  BilSts='F';
