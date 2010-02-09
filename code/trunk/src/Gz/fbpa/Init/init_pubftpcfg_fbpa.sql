--初始化应用信息
--FTP初始化说明：初始化按照下面方式初始化 dat/fbp,$FilNam,bin 三个变量不需修改，ftpid命名规则为业务名+分行行 如 water_484999 
delete from pubftpcfg where BrNo='441999' AND ftpid like 'GZ_FBP%';
insert into pubftpcfg values('441999','GZ_FBP01','182.53.13.13','zsxn','bx','up','$RcvFil','dat/fbp','$LclFil','bin',' ','广州文件批量代收付');
--对应 IP地址 用户名 密码 对方相对目录 
insert into pubftpcfg values('441999','GZ_FBP02','182.53.13.13','zsxn','bx','down','$SndFil','dat/fbp','$LclFil','bin',' ','广州文件批量代收付');
--对应 IP地址 用户名 密码 对方相对目录 
