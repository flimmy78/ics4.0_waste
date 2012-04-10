--delete from pubftpcfg where ftpid = 'GZ_ICSCH01';
--delete from pubftpcfg where ftpid = 'GZ_ICSCH02';
--insert into pubftpcfg values('441999','GZ_ICSCH01','137.28.45.27','bank_boc','boc2010!@#','./','$SndFil','dat/icca','$LclFil','asc',' ','广州大学城IC联名卡对账文件上传');
insert into pubftpcfg values('441999','GZ_ICSCH02','182.53.13.13','gy','gy','./','$SndFil','dat/icca','$FilNam','asc',' ','电子现金圈存对账文件格式自动触发');
