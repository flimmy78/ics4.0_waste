文件每个字段用"|"分隔。
第一行结构说明：
  1  char date[8]  ;       /* 清算日期 CCYYMMDD */
  2  char round[1];        /* 清算场次 */
  3  char sendnum[4];      /* 发起方系统号 */
  4  char sendcode[12];    /* 发起方代码 */
  5  char recvnum[4];      /* 接收方系统号 */
  6  char recvcode[12];    /* 接收方代码 */
  7  char transtype[4];    /* 交易种类 */
  8  char filename[60];    /* 文件名 */
  9  char referfile[60];   /* 参照文件名 */
  10 char batchserial[8];  /* 批量包序号 */
  11 char referserial[8];  /* 参考批量包序号 */
  12 char customserial[8]; /* 客户批量包序号 */
  13 char transnum[10];    /* 交易总笔数 */
  14 char transmoney[16];  /* 交易总金额 */
  15 char refusenum[10];   /* 拒绝支付总笔数 */
  16 char refusemoney[16]; /* 拒绝支付总金额 */
  17 char returncode[8];   /* 返回码 */
  18 char reserved[16];    /* 预留位 */
  
第二行（含）以下结构说明：
 0  sysrefer char(16),       /* 信息序号(R) */
 0  sysrefer1  char(16)      /* 参照 */
 1  msgid  char(4) ,         /* 报文类型标识符 */
 2  transtype char(6) ,      /*  3 交易种类细分类型 */
 3  transmoney char(15) ,    /*  4 交易金额 */
 4  datetime char(10) ,      /*  7 交易发起日期和时间  char(MMDDhhmmss)*/
 5  directbank char(12) ,    /* 11 直接清算行 */
 6  wtdate char(14) ,        /* 12 委托日期 char(CCYYMMDDhhmmss) */
 7  qsdate char(8) ,         /* 15 清算日期 char(CCYYMMDD) */
 8  kindid char(3) ,         /* 24 查询/通知种类标识 000：银行帐户情况查询
                                                 001：客户授权余额查询
                                                 002：户名查询/核对查询 
                                                 999：通用查询  */
 9  district char(4) ,       /* 26 地区号 */ 
 10 currency char(32) ,      /* 30 交易货币代码 CNY:人民币 HKD:港币 USD:美圆 */
 11 inputmode char(3) ,      /* 40 服务点输入方式码 021 磁条读入，且带PIN；
                                                022 磁条读入，且不带PIN；
                                                011 手工方式，且带PIN；
                                                012 手工方式，且不带PIN */
 12 centercustomer char(18) , /*43.1 中心客户号 */
 13 enterprise char(18) ,     /*43.2 企业客户号 :客户在企业的唯一标识 */
 14 acceptdate char(14) ,    /* 44.1 中心交易受理日期时间 char(CCYYMMDDhhmmss)*/
 15 acceptno char(16) ,      /* 44.2 中心交易受理号 */
 16 processdate char(14) ,  /* 44.3 业务处理方处理日期时间char(CCYYMMDDhhmmss)*/
 17 serial char(16) ,        /* 44.4 业务处理方流水号 */
 18 returncode char(8) ,     /* 44.5 返回码 */
 19 ctflag char(1) ,         /* 48.1 现金/转账标识 : 0-现金,1-转帐 */
 20 resume char(4) ,         /* 48.2 摘要代码 */
 21 purpose char(3) ,        /* 48.3 资金用途代码 */
 22 retry char(1) ,          /* 48.4 重发标识 */
 23 customer char(1) ,       /* 48.5 对公/对私标识 */
 24 bussinesskind char(5) ,  /* 48.6 业务种类 :0-对公，1－对私 */
 25 accounttype char(2) ,    /* 48.7 卡/折标识 01：存折,02：卡 */
 26 moneytype char(1) ,      /* 48.8 钞户/汇户标识 0-汇户，1－钞户 */
 27 feemode char(3) ,        /* 48.9 手续费方式 固定填写SHA */
 28 deliver char(3) ,        /* 48.10 支付工具 */
 29 authcode char(6) ,       /* 48.11 授权码 */
 30 deliverclass char(1) ,   /* 48.12 支付优先级 0：普通  */
 31 oldbussid char(32),      /* 56 原交易业务唯一标识 */
 32 sendbankid char(12) ,    /* 62.1 发起行行号 */
 33 sendopenbank char(12) ,  /* 62.2 发起人开户行行号 */
 34 sendbanknet char(9) ,    /* 62.3 发起行网点号 */
 35 sendaccount char(35) ,   /* 62.4 发起人账号 */
 36 sendername char(60) ,    /* 62.5 发起人名称 */
 37 referserial char(8) ,    /* 62.6 凭证提交号（发起交易序号） */
 38 recvbank char(12) ,      /* 63.1 接收行行号 */
 39 recvbankname char(12) ,  /* 63.2 接收人开户行行号 */
 40 recvnet char(9) ,        /* 63.3 接收行网点号 */
 41 recvaccount char(35) ,   /* 63.4 接收人账号 */
 42 recvcustomer char(60) ,  /* 63.5 接收人名称 */
 43 contractno char(60) ,   /* 66 扣款合同号（多方协议号）,用于定期借记报文。 */
 44 systemstat char(2) ,     /* 67 系统运行状态 */
 45 creditmoney char(15) ,   /* 74.1 贷方金额 */
 46 creditcount char(10) ,   /* 74.2 贷方笔数 */
 47 debitmoney char(15) ,    /* 74.7 借方金额 */
 48 debitcount char(10) ,    /* 74.8 借方笔数 */
 49 transkind char(4) ,      /* 93 交易种类 */
 50 oldid char(20) ,         /* 102 旧登陆标识 */
 51 newid char(20) ,         /* 103 新登陆标识 */
 52 resumemsg char(255) ,    /* 111 交易摘要(300) */
 53 passcard char(40) ,      /* 112.1 密押 */
 54 enterpriseid char(12) ,  /* 113.1 企业机构代码 */
 55 servicemsgtype char(1) ,  /* 115.1 服务信息类型 */
 56 servicemsginfo char(255) ,  /* 115.2 服务信息内容(512) */
 57 appendsender char(80) ,  /* 124 附加发起人名称 */
 58 sendaddr char(60) ,      /* 125 发起人地址 */
 59 appendrecver char(80) ,  /* 126 附加接收人名称 */
 60 recvaddr char(60) ,    /* 127 接收人地址 */
