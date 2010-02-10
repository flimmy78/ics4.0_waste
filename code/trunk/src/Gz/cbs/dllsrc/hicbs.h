/*原子函数返回值定义*/
#define   MsgTypLen      1   /*返回码类型*/
#define   RspCodLen      6   /*返回码*/
#define   RspMsgLen     56   /*返回信息*/

/*手续费、邮电费计算变量定义*/
#define   TxnKndLen      6   /*交易类型细分代码*/
#define   UsgCodLen      3   /*资金用途代码*/
#define   LclFlgLen      1   /*本异地标志*/
#define   BrNoLen        6   /*分行号*/
#define   CcyCodLen      3   /*币种*/
#define   TxnAmtLen     15   /*交易金额*/
#define   FeeModLen      1   /*手续费收费模式*/
#define   FeeRatLen      6   /*手续费费率*/
#define   FeeAmtLen     15   /*手续费额度*/
#define   PstModLen      1   /*邮电费收费模式*/
#define   PstRatLen      6   /*邮电费费率*/
#define   PstAmtLen     15   /*邮电费额度*/

/*获取帐户类型变量定义*/
#define   BgnLocLen      2   /*卡中心地区号起始位置*/
#define   CenLenLen      2   /*地区号长度*/

/*判断或更新头寸变量定义*/
#define   UpdDirLen      1   /*更新借、贷标志*/
#define   TxnModLen      1   /*交易内容*/


/*行号获取变量定义*/
#define   CtlNodLen      6
#define   BusCodLen      6
#define   PBnkNoLen     12

/*判断帐户属性（对公、对私）变量定义*/
#define   RcvActLen     35   /*接收人帐号*/
#define   AccFlgLen      1   /*接收人帐号性质*/

/*批量文件解析变量定义*/
/*参数*/
#define   FilPthLen    128   /*文件路径*/
/*批量文件名变量*/
#define   FILMARK        "TXNTYP"   /*文件名标志*/
#define   RSPFILLEN      "00000337" /*收妥回应文件长度*/
#define   SYSID          "1006"     /*交通银行系统号*/
#define   DIRBNO         "301581000019"  /*交通银行直接参与行行号*/

#define   FNmLstLen     46   /*文件列表名长度*/
#define   FNameLen     128   /*文件名长度*/
#define   MsgIdLen       4   /*报文类型标识符*/
#define   SysIdLen       4   /*系统号*/
#define   WorkDtLen      8   /*工作日期*/
#define   BchNoLen       8   /*批号*/
#define   FSizeLen       8   /*文件长度*/
#define   MsgIdOffset    6
#define   TxnKndOffset   MsgIdOffset+MsgIdLen
#define   SysIdOffset    TxnKndOffset+TxnKndLen
#define   WorkDtOffset   SysIdOffset+SysIdLen
#define   BchNoOffset    WorkDtOffset+WorkDtLen
#define   FSizeOffset    BchNoOffset+BchNoLen

#define   F8583SizeOffset 84
/*批量应用报文头*/
#define   ClrDatLen      8   /*清算日期*/
#define   ClrSceLen      1   /*清算场次*/
#define   SSysIdLen      4   /*发起方系统号*/
#define   SndBNoLen     12   /*发起方代码*/
#define   RSysIdLen      4   /*接收方系统号*/
#define   RcvBNoLen     12   /*接收方代码*/
#define   TraKndLen      4   /*交易种类*/
#define   FilNamLen     60   /*文件名*/
#define   RefFilLen     60   /*参照文件名*/
#define   BchSqnLen      8   /*批量包序号*/
#define   RefSqnLen      8   /*参考批量包序号*/
#define   CusSqnLen      8   /*客户批量包序号*/
#define   TotNumLen     10   /*交易总笔数*/
#define   TotAmtLen     16   /*交易总金额*/
#define   RefNumLen     10   /*拒绝支付总笔数*/
#define   RefAmtLen     16   /*拒绝支付总金额*/
#define   RtnCodLen      8   /*返回码*/
#define   ReServLen     16   /*预留位*/
#define   BchStsLen      1   /*文件处理状态*/
/*批量记录应用报文头*/
#define   MsgSqnLen     16   /*信息序号*/
/*批量记录正文体*/
#define   SndTmLen      10   /*交易发起日期和时间*/
#define   ClrBNoLen     12   /*直接清算行*/
#define   SndDatLen      8   /*委托日期*/
/*报文头已定义
#define   ClrDatLen      8   *清算日期*
*/
#define   QryTypLen      3   /*查询通知种类*/
#define   AreaNoLen      4   /*地区号*/
#define   SvrCodLen      4   /*服务点输入方式码*/
#define   CenIdLen      18   /*中心客户号*/
#define   CusIdLen      18   /*企业客户号*/
#define   CenTmLen      14   /*中心受理日期时间*/
#define   CenLogLen     16   /*中心受理号*/ 
#define   ThdTmLen      14   /*业务处理方处理日期时间*/
#define   ThdLogLen     16   /*业务受理方流水号*/
#define   CshFlgLen      1   /*现金转帐标志*/
#define   SmrCodLen      4   /*摘要代码*/
#define   RSdFlgLen      1   /*重发标识*/
#define   AccFlgLen      1   /*对公对私标识*/
#define   TBusTpLen      5   /*业务种类*/
#define   CardFgLen      2   /*卡折标识*/
#define   BillFgLen      1   /*钞户汇户标识*/
#define   FeeTypLen      3   /*收费方式*/
#define   PayFucLen      3   /*支付工具*/
#define   AuthCdLen      6   /*授权码*/
#define   PayLvlLen      1   /*支付优先级*/
#define   OrgIdLen      32   /*原数据元*/
#define   SndBNoLen     12   /*发起行行号*/
#define   SOpnBkLen     12   /*发起人开户行行号*/
#define   SndNodLen      9   /*发起行网点号*/
#define   SndActLen     35   /*发起人账号*/
#define   SndNmLen      60   /*发起人名称*/
#define   VchIdLen       8   /*凭证提交号*/
#define   RcvBNoLen     12   /*接收行行号*/
#define   ROpnBkLen     12   /*接收人开户行行号*/
#define   RcvNodLen      9   /*接收行网点号*/
#define   RcvActLen     35   /*接收人账号*/
#define   RcvNmLen      60   /*接收人名称*/
#define   AgrNoLen      60   /*协议号*/
#define   SysStsLen      2   /*系统运行状态*/
#define   CreAmtLen     15   /*贷方金额*/
#define   CreCntLen     10   /*贷方笔数*/
#define   DebAmtLen     15   /*借方金额*/ 
#define   DebCntLen     10   /*借方笔数*/ 
#define   CTraKndLen     4   /*交易种类*/
#define   OSgnIdLen     20   /*旧登陆标识*/
#define   NSgnIdLen     20   /*新登陆标识*/
#define   SmrLen       300   /*交易摘要*/
#define   SecKeyLen     40   /*密押*/
#define   TCrpCdLen     12   /*企业机构代码*/
#define   SvrKndLen      1   /*服务信息类型*/
#define   TBilNoLen     30   /*税票号码*/
#define   TaxNoLen      20   /*纳税人编码*/
#define   TaxerLen      60   /*纳税人名称*/
#define   TaxLvlLen      2   /*预算级次*/
#define   TSubCdLen     12   /*预算科目*/
#define   TOrgCdLen     11   /*征收机关代码*/
#define   TActDtLen      8   /*税票限缴日期*/
#define   SvrMsgLen    300   /*服务信息内容*/
#define   SndNm2Len     80   /*附加发起人名称*/
#define   SndAdrLen     60   /*发起人地址*/
#define   RcvNm2Len     80   /*附加接收人名称*/
#define   RcvAdrLen     60   /*接收人地址*/
#define   TraTmLen      10   /*交易时间*/
/*
**大小通道变量定义
*/
#define   DskNoLen      12   /*磁盘号*/
#define   BchStsLen      1   /*批量记录状态*/
#define   OIFlagLen      1   /*往来标志*/
#define   BilStsLen      1   /*单笔记录状态*/
#define   AccKndLen      1   /*帐户类型*/
#define   NodNoLen       6   /*入帐或扣款内部帐务所属部门*/
#define   AccSeqLen      5   /*内部帐户序号*/
#define   LogNoLen      14   /*前置流水号*/
#define   BusTypLen      5   /*业务类型*/
#define   RgCFlgLen      1   /*贷方回执*/
#define   RgDFlgLen      1   /*借方回执*/
#define   TTxnCdLen      6   /*前置交易码*/
#define   HTxnCdLen      6   /*主机交易码*/
#define   HTxnSbLen      3   /*主机交易子码*/
#define   HLogNoLen      9   /*主机流水号*/
#define   HTxnStLen      1   /*主机交易状态*/
#define   ActDatLen      8   /*会计日期*/
#define   IsTxnLen       1
#define   HRspCdLen      6   /*主机返回码*/
#define   TxnCnlLen      3   /*交易渠道*/
#define   CnlSubLen      6   /*主机业务类型*/
#define   TxnObjLen      8   /*主机接入服务*/
#define   TlrIdLen       7   /*入帐柜员号*/
#define   TckNoLen      11   /*柜员号流水号*/
#define   ActNoLen      21   /*帐号*/
#define   CdFlagLen      1   /*借贷标志*/
#define   OrnCntLen      8   /*笔数*/
#define   UpdFlgLen      1   /*是否更新标志*/
#define   UpdFldLen    200   /*更新域*/

#define   TxnSubLen      3   /*交易子码*/
#define   CnlTypLen      1   /*交易方式*/
#define   VchCodLen      8   /*凭证号码*/
#define   PrtFlgLen      1   /*打印存折标志*/
#define   CcyTypLen      1   /*钞汇标志*/
#define   PayModLen      1   /*支付方式*/
#define   VchChkLen      1   /*零售监督标志*/
#define   VchTypLen      3   /*零售凭证类型*/
#define   TrkModLen      1   /*验磁标志*/
#define   MaskLen        4   /*摘要码*/
#define   FeeCodLen      4   /*费率代码*/

#define   AgrKndLen      1   /*协议类型*/
#define   ActFlgLen      1   /*帐务种类*/
#define   AreaCdLen      3   /*地区码*/
/*
**定期（批量）贷记数据文件
*/
#define   RecLen         449
#define   RecDatLen      447
#define   RcvBNoOffset   0
#define   ROpnBkOffset   RcvBNoOffset+RcvBNoLen
#define   RcvActOffset   ROpnBkOffset+ROpnBkLen
#define   RcvNmOffset    RcvActOffset+RcvActLen
#define   TxnAmtOffset   RcvNmOffset+RcvNmLen 
#define   TBusTpOffset   TxnAmtOffset+TxnAmtLen
#define   UsgCodOffset   TBusTpOffset+TBusTpLen
#define   SmrCodOffset   UsgCodOffset+UsgCodLen
#define   SmrOffset      SmrCodOffset+SmrCodLen
#define   AgrNoOffset    SmrOffset+SmrLen
/*
**交行代码
*/
#define   BOCSGN         "301"
/*
**信息文件数据
*/
#define   BankNoLen      12
#define   SwftNoLen      12
#define   CityCdLen      4
#define   BlAreaLen      4
#define   DirBNoLen      12
#define   BnkTypLen      3
#define   BankNmLen      60
#define   SimBNmLen      20
#define   SecBNoLen      12
#define   AdrLen         60
#define   PosCodLen      6
#define   TelNoLen       20
#define   FaxNoLen       20
#define   EMailLen       30
#define   CommanLen      16
#define   DirFlgLen      1
#define   CnpsFgLen      1
#define   EffDatLen      8
#define   IvdDatLen      8
#define   ReMarkLen      60

#define   CodTypLen      6
#define   CodeLen        18
#define   CodSmrLen      40

#define   SysNamLen      20
#define   IdTypeLen      1

#define   CityNmLen      40
#define   UpgCodLen      4
#define   CityFgLen      1

#define   OrgCodLen      12
#define   OrgNamLen      60
#define   OrgActLen      32
#define   OrgANmLen      60

#define   SucFlgLen      1   /*对帐成功标志*/
#define   ResultLen      40  /*对帐结果*/

#define   WebChvLen      8   /*网银流水号*/
#define   RecNoLen       14  /*系统流水号*/
#define   DrActLen       21  /*借方账号*/
#define   DrNamLen       60  /*借方户名*/ 
#define   CrActLen       32  /*贷方账号*/
#define   CrNamLen       60  /*贷方户名*/
#define   TxnAmtLen      15  /*交易金额*/
#define   RmkLen         60  /*摘要*/
#define   RvsNoLen       12  /*销帐号*/
#define   MsgLen         60  /*附言*/
#define   OppExcLen      10  /*交换号*/

#define   ErrMsgLen      60  /*提示信息*/

#define   TxnMonLen      6   /*交易月份*/
#define   TxnNumLen      6   /*明细笔数*/
#define   FeeFlgLen      1   /*扣收标志*/
