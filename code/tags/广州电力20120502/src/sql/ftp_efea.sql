--delete from pubftpcfg where ftpid = 'EFE_RCV_441';
delete from pubftpcfg where ftpid = 'EFE_SND_441';
--insert into pubftpcfg values('441999','EFE_RCV_441','182.53.13.13','gy','gy','./','$FilNam','dat/efea','$LclFil','asc',' ','广州电力文件接收');
insert into pubftpcfg values('441999','EFE_SND_441','172.31.9.108','jtyh','jtyh168','./','$SndFil','dat/efea','$LclFil','asc',' ','广州电力文件返回');
--insert into pubftpcfg values('441999','EFE_SND_441','182.53.13.13','gy','gy','./home/jtyh','$SndFil','dat/efea','$LclFil','asc',' ','广州电力文件返回');

