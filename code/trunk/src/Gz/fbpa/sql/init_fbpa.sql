--初始化应用信息
insert into cimaplinf values('441999','48','12','FBP','广州批量代收付');
--cimaplinf,本地应用码表(行号,主机应用码,本地应用码,应用标识,应用名)

insert into pubaplbus values('441999', '409','', 'FBP01','广州批量代收付');
--pubaplbus应用码业务类型对照表(行号,应用码、应用子码、业务类型、业务名称)

insert into pubaplmng values('441999', '409','FBP01','','9999999999');
--pubaplmng应用管理表(应用类别码、业务类型、业务子码、单位代码)

insert into pubjnldef values('441999', 'FBP01','9999999999','afebatrec','afebatrec','1','1');
--pubjnldef业务流水定义管理表(业务类型、、联机流水表名、批量流水表名、联机、批量对帐标记)

insert into pubdumtlr values('441999', 'FBP','','EFBPBI1');
--pubdumtlr虚拟柜员表(交易渠道、子渠道、银行虚拟柜员号)

insert into mngaplmon values('441999', 'FBP',   'FBP01',   'afebatrec',  '0',  'TTxnCd',  'TxnSts');

--FTP初始化说明：初始化按照下面方式初始化 dat/fbp,$FilNam,bin 三个变量不需修改，ftpid命名规则为业务名+分行行 如 water_484999 
delete from pubftpcfg where BrNo='441999' AND ftpid like 'GZ_FBP%';
insert into pubftpcfg values('441999','GZ_FBP01','182.53.13.13','zsxn','bx','up','$RcvFil','dat/fbp','$LclFil','bin',' ','广州文件批量代收付');
--对应 IP地址 用户名 密码 对方相对目录 
insert into pubftpcfg values('441999','GZ_FBP02','182.53.13.13','zsxn','bx','down','$SndFil','dat/fbp','$LclFil','bin',' ','广州文件批量代收付');
--对应 IP地址 用户名 密码 对方相对目录 
