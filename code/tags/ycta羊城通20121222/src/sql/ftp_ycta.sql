--delete from pubftpcfg where ftpid = 'YCT_JYF_441';
--delete from pubftpcfg where ftpid = 'YCT_CZF_441';
--delete from pubftpcfg where ftpid = 'YCT_RZF_441';
insert into pubftpcfg values('441999','YCT_JYF_441','10.240.1.7','jh','jh123','./detail','$JYFile','dat/ycta','$JYFile','asc',' ','羊城通交易文件');
insert into pubftpcfg values('441999','YCT_CZF_441','10.240.1.7','jh','jh123','./detail','$CZFile','dat/ycta','$CZFile','asc',' ','羊城通冲正文件');
insert into pubftpcfg values('441999','YCT_RZF_441','10.240.1.7','jh','jh123','./detail','$LclFil','dat/ycta','$LclFil','asc',' ','羊城通审计文件');
