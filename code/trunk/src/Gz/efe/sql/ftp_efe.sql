delete from pubftpcfg where ftpid like 'EFE_RCV%';
delete from pubftpcfg where ftpid like 'EFE_SND%';
insert into pubftpcfg values('441999','EFE_RCV_441','182.53.13.13','gy','gy','./','$FilNam','dat/efe','$LclFil','asc',' ','广州电力文件接收');
insert into pubftpcfg values('441999','EFE_SND_441','182.53.13.13','gy','gy','./','$SndFil','dat/efe','$LclFil','asc',' ','广州电力文件返回');
insert into pubftpcfg values('485999','EFE_RCV_485','182.139.200.33','jyydlw','jyydlw','./007','$FilNam','dat/efe','$LclFil','asc',' ','揭阳电力文件接收');
insert into pubftpcfg values('485999','EFE_SND_485','182.139.200.33','jyydlw','jyydlw','./007','$SndFil','dat/efe','$LclFil','asc',' ','揭阳电力文件返回');

insert into pubftpcfg values('445999','EFE_RCV_445','182.55.4.23','hsftp','1qa2ws','./','$FilNam','dat/efe','$LclFil','asc',' ','汕头电力文件接收');
insert into pubftpcfg values('445999','EFE_SND_445','182.55.4.23','hsftp','1qa2ws','./','$SndFil','dat/efe','$LclFil','asc',' ','汕头电力文件返回');
