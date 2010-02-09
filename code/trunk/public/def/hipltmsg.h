/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: pub_msg1.h
 Author			: peng_wh
 Version		: 1.0.0
 Date			: 2003.04.07
 Description	: 用于统一规定大前置业务平台使用的返回码，使用范围是大前置内部
				  
 Others			: 
 History		: 
				  内容简述

  No.	Date		Author		Modification
  ===	==========	========	==============================================

******************************************************************************/

#define		_SUCCEED               "000000"		/*  成功					*/
		    	                       		   		            	          
#define		_INVA_LOGON            "101400"		/*  注册方式无效			*/
#define		_INVA_LOGOUT           "101401"		/*  注销方式无效			*/
#define		_FULL_LOGTAB           "101402"		/*  注册表满				*/
#define		_PROC_ALRE_LOGON       "101403"		/*  同一进程已注册			*/
#define		_APP_ALRE_LOGON        "101404"		/*  同一应用标识已注册		*/
#define		_PROC_APP_CLASH        "101405"		/*  进程和应用标识冲突		*/
#define		_NOT_FOUND_APP         "101406"		/*  未找到注册应用			*/
#define		_INVA_SOUR_LOGON       "101407"		/*  源应用未有效注册		*/
#define		_INVA_TRAG_LOGON       "101408"		/*  目的应用未有效注册		*/
#define		_RE_START              "101409"		/*  重新引导进程			*/
#define		_RE_START_ERR          "101410"		/*  重新引导进程失败		*/
#define		_LOST_INSIDE_DATA      "101411"		/*  内部数据丢失			*/
#define		_GRAV_PROC_ERR         "101412"		/*  严重程序错误			*/
#define		_START_APP_ERR         "101415"		/*  外部进程引导失败    	*/
#define		_SYS_EXIT              "101416"		/*  系统退出            	*/
#define		_TOO_MANY_APP          "101417"		/*  应用进程太多			*/
#define		_INVA_APP              "101418"		/*  无效应用标识			*/
#define		_APP_CHAN_ERR          "101419"		/*  应用标识转换错误		*/
#define		_TOO_MANY_ROU          "101420"		/*  路由表数据太多      	*/
#define		_INEXIST_ROU_TAB       "101421"		/*  路由表未配置        	*/
#define		_RE_START_PROC         "101422"		/*  重新引导进程 			*/
#define		_FOUND_DIE_PROC        "101424"		/*  发现进程死 				*/
#define		_LOST_INS_DATA         "101425"		/*  内部数据丢失			*/
#define		_NOT_ENV_VARI          "101440"		/*  没有设置环境变量		*/
#define		_PARA_NO_ASCII         "101450"		/*  参数非ASCI字符			*/
#define		_PARA_LEN_ERR          "101451"		/*  参数字节长度错			*/
#define		_PARA_NO_NUM           "101452"		/*  参数非数字字符			*/
#define		_GET_PARA_ERR          "101453"		/*  参数获取错误			*/
                                              		                          

#define		_PROCESSING            "120001"		/*  正在处理中				*/
#define		_ASK_AUTH              "120002"		/*  要求授权				*/
#define		_ACCT_NULL             "120003"		/*  帐号不能为空			*/
#define		_INVALID_ACCT          "120004"		/*  无效帐号				*/
#define		_FREEZE_ACCT           "120005"		/*  帐号（卡号）冻结		*/
#define		_NAME_ACCT_UNCONF      "120006"		/*  帐号（卡号）户名不符	*/
#define		_ERR_TRAN_STAT         "120007"		/*  交易状态错				*/
#define		_INVALID_CARD          "120008"		/*  无效卡号				*/
#define		_INVALID_AMOUNT        "120009"		/*  无效金额				*/
#define		_VIP_TRAN              "120010"		/*  贵宾交易				*/
#define		_PASSWD_ERR            "120011"		/*  持卡人或操作员密码错	*/
#define		_INVALID_TRAN          "120012"		/*  无效交易				*/
#define		_IRREGU_TRAN           "120013"		/*  非法交易				*/
#define		_PACK_ERR              "120014"		/*  数据包格式错误			*/
#define		_INEXIST_ORA_RECORD    "120015"		/*  无此原交易				*/
#define		_NOT_ENOUGH_INTEG      "120020"		/*  积分不够				*/
#define		_CLEAN_INTEG_ERR       "120021"		/*  积分清除出错			*/
#define		_INVA_CARD_KIND        "120022"		/*  卡种错					*/
#define		_PRINT_CLASH           "120023"		/*  打印冲突				*/
#define		_DATA_ERR              "120024"		/*  数据格式错				*/
#define		_REQU_STAT_ERR         "120026"		/*  请求状态错误			*/
#define		_INVA_SEQU             "120027"		/*  流水号和类型不符		*/
#define		_INVA_PAGE_REQU        "120028"		/*  不可识别的页请求		*/
#define		_INVA_PAGE_APPLY       "120029"		/*  页操作申请错误			*/
#define		_CREAT_PRETRACE_ERR    "120031"		/*  产生前置流水号错		*/
#define		_GET_PRETRACE_ERR      "120032"		/*  取前置流水号错			*/
#define		_NOT_ISSUE_CARD        "120033"		/*  未发卡					*/
#define		_INVA_PRINT_REQU       "120034"		/*  无效的打印请求			*/
#define		_INEXIST_AUTH_AMOUNT   "120036"		/*  无效授权金额			*/
#define		_ASK_PRINT             "120037"		/*  要求先打印来帐报单		*/
#define		_ENTER_LOGNO_ERR       "120038"		/*  录入流水号错			*/
#define		_VOUDATE_LIMIT         "120039"		/*  凭证日期不能大于当日	*/
#define		_OUTBANK_ERR           "120040"		/*  汇出行号或发报行号错	*/
#define		_INBANK_ERR            "120041"		/*  汇入行号或收报行号错	*/
#define		_INEXIST_RECORD        "120042"		/*  无此交易明细			*/
#define		_NOT_APPLY_SERV        "120043"		/*  未申请服务				*/
#define		_REPEAT_PACK           "120044"		/*  重报					*/
#define		_INEXIST_HOST_RECORD   "120045"		/*  主机无交易记录			*/
#define		_INVA_FIELD            "120046"		/*  信息中存在不合法的域	*/
#define		_NULL_FIELD_ERR        "120047"		/*  规定非空的域为空		*/
#define		_ERR_AMOUNT            "120048"		/*  交易金额不合法			*/
#define		_AMOUNT_LIMIT          "120049"		/*  转帐交易金额小于规定	*/
#define		_TRUST_DATE_ERR        "120050"		/*  委托日期不正确			*/
#define		_OUT_SAME_IN           "120051"		/*  发起行与接收行相同		*/
#define		_BANKNO_ERR            "120052"		/*  行号错					*/
#define		_REQU_AREA_ERR         "120053"		/*  查询范围不正确			*/
#define		_INVA_MSG_CONT         "120054"		/*  信息内容与对照信息不符	*/
#define		_INEXIST_COLLATE       "120055"		/*  对照信息不存在			*/
#define		_INVALID_MCHANT        "120056"		/*  无效网点或商户号		*/
#define		_INVA_FUNCTYPE         "120057"		/*  无效交易(信息类型错)	*/
#define		_NOT_OBLIGATE_PIN      "120058"		/*  银行存折未预留密码		*/
#define		_ACCT_NOT_SET          "120059"		/*  帐户未开户				*/
#define		_ACCT_ALRE_SET         "120060"		/*  帐户已开户				*/
#define		_CALL_ISSUE            "120061"		/*  联系发卡方				*/
#define		_SPEC_CALL             "120062"		/*  特别联系				*/
#define		_INVA_DATE             "120063"		/*  无效日期				*/
#define		_INVA_FEE_KIND         "120064"		/*  无效费用种类代号		*/
#define		_INVA_OPER             "120065"		/*  无效操作员号			*/
#define		_CHECK_PIN_ERR         "120066"		/*  银行密码校验错			*/
#define		_REPA_STOCK_SEQU       "120067"		/*  重复的证券流水号		*/
#define		_SHORTAG_STOCK_BALA    "120068"		/*  券商帐户余额不足		*/
#define		_STOCKACC_ERRSTAT      "120069"		/*  券商帐户状态错			*/
#define		_SEQU_ERR              "120070"		/*  银行产生流水号错误		*/
#define		_CROSS_ACCT_CLOSE      "120071"		/*  通存通兑被关闭			*/
#define		_INVA_STOCK_ACCT       "120072"		/*  券商帐户不存在			*/
#define		_PRINT_BANKBOOK        "120073"		/*  请到银行补打存折		*/
#define		_AMOUNT_OVER_LIMIT     "120074"		/*  单笔交易金额超限		*/
#define		_INVA_FUNC             "120080"		/*  此交易未开通			*/
#define		_INEXIST_STOCK         "120081"		/*  无此券商				*/
#define		_CHECK_PASSERR         "120082"		/*  资金密码校验错			*/
#define		_SHORTAG_BALAN         "120083"		/*  客户资金帐户余额不足	*/
#define		_OVER_SUMLIMIT         "120084"		/*  累计金额超限			*/
#define		_REPEAT_SEQU           "120085"		/*  重复的银行流水号		*/
#define		_INEXIST_REVE_RECORD   "120086"		/*  被冲正流水不存在		*/
#define		_ALREAD_REVE           "120087"		/*  该流水已冲正			*/
#define		_UNCONFOR_REVETRAN     "120088"		/*  冲正流水不符			*/
#define		_BALA_REFU_REVE        "120089"		/*  余额不足,不允许冲正		*/
#define		_INVA_BANKNO           "120090"		/*  无效银行号				*/
#define		_FUNDACC_ERRSTAT       "120091"		/*  资金帐户状态错			*/
#define		_INEXIST_FUNDACC       "120092"		/*  资金帐户不存在			*/
#define		_ACCT_ALRE_CLOSED      "120093"		/*  该帐户已销户			*/
#define		_NOT_BASED_PARA        "120094"		/*  证券与银行对应关系未建	*/
#define		_BASED_PARA            "120095"		/*  证券与银行对应关系已建	*/
#define		_DISALLOW_TRANSFER     "120096"		/*  该客户转帐功能未开启	*/
#define		_CLOSE_TRANSFER        "120097"		/*  该客户转帐功能已关闭	*/
#define		_ASSET_OVER_LIMIT      "120098"		/*  该客户资产总值低于下限	*/
#define		_SERIAL_UNCON          "120099"		/*  证券公司编号不符		*/
#define		_DISALLOW_FUNC         "120100"		/*  此交易未开通			*/
#define		_STOCK_NO_SIGN         "120101"		/*  证券公司未签到			*/
#define		_STOCK_LOGOUT          "120102"		/*  证券公司已签退			*/
#define		_NO_TRANSFER_FUNC      "120103"		/*  转帐功能未开启			*/
#define		_STOCK_SERV_ERR        "120104"		/*  证券公司服务器系统错误	*/
#define		_POSSIB_OPERERR        "120105"		/*  怀疑操作错				*/
#define		_AGAIN_ENTRY           "120106"		/*  请重新交易				*/
#define		_PART_HONOR            "120107"		/*  部分承兑				*/
#define		_REFUSE_BUSIN          "120108"		/*  拒绝交易				*/
#define		_INFRACT_SECU          "120109"		/*  违反安全规定			*/
#define		_NO_VOID_RECORD        "120110"		/*  被撤销流水不存在		*/
#define		_ALRE_VOID             "120111"		/*  被撤销流水已撤销		*/
#define		_UNCONFOR_TRAN         "120112"		/*  被撤销流水不符			*/
#define		_NO_RECORD             "120113"		/*  被查询流水不存在		*/
#define		_REFU_REVERSAL         "120114"		/*  拒绝冲正				*/
#define		_AVALID_TERMNO         "120115"		/*  无效终端				*/
#define		_REFU_HONOR            "120116"		/*  不承兑					*/
#define		_ERROR                 "120117"		/*  差错					*/
#define		_LABLE_HONOR           "120118"		/*  标识承兑				*/
#define		_INQU_RESP             "120119"		/*  查询响应方				*/
#define		_PART_AUTH             "120120"		/*  部分批准				*/
#define		_LEAD_AUTH             "120121"		/*  领导批准				*/
#define		_INVALID_ISSU          "120122"		/*  无此发卡方				*/
#define		_UPDATE_TRACK3         "120123"		/*  更新3磁道				*/
#define		_CLIENT_VOID           "120124"		/*  客户取消				*/
#define		_CLIENT_DISPUTED       "120125"		/*  客户有争执				*/
#define		_REPEAT_TRAN           "120126"		/*  重复交易				*/
#define		_AVALID_RET            "120127"		/*  无效响应				*/
#define		_NO_ACTION             "120128"		/*  不采取行动				*/
#define		_SUSP_FAIL             "120129"		/*  故障怀疑				*/
#define		_ERR_FEE               "120130"		/*  非法交易费				*/
#define		_REFU_UPDATE           "120131"		/*  不支持更新				*/
#define		_REPEAT_UPDATE         "120132"		/*  重复更新				*/
#define		_UPDATE_FIELD_ERR      "120133"		/*  更新字段错				*/
#define		_TARNSACT              "120134"		/*  正在处理				*/
#define		_UPDATE_ERR            "120135"		/*  更新失败				*/
#define		_NOJOIN_BANK           "120136"		/*  未联网银行				*/
#define		_PARTIAL               "120137"		/*  部分完成				*/
#define		_OVER_EXPIRE           "120138"		/*  过期,没收				*/
#define		_CHEAT_CARD            "120139"		/*  舞弊,没收				*/
#define		_CALL_BANK             "120140"		/*  联系,没收				*/
#define		_LIMIT_CARD            "120141"		/*  受限,没收				*/
#define		_PICKUP_CARD           "120142"		/*  挂失,没收				*/
#define		_LOCK_RECORD           "120143"		/*  记录被锁				*/
#define		_ERR_ACCOUNT           "120144"		/*  无贷记帐户				*/
#define		_LOSE_CARD             "120145"		/*  遗失卡没收				*/
#define		_ERR_CURR_ACC          "120146"		/*  无通用帐户				*/
#define		_ERR_INVEST_ACC        "120147"		/*  无投资帐户				*/
#define		_LACK_BALANCE          "120148"		/*  资金不足				*/
#define		_ERR_CHEQUE_ACC        "120149"		/*  无支票帐户				*/
#define		_ERR_SAVING_ACC        "120150"		/*  无储蓄帐户				*/
#define		_OVER_EXPI_CARD        "120151"		/*  过期卡					*/
#define		_PIN_ERR               "120152"		/*  个人密码错				*/
#define		_NO_CARD_RECORD        "120153"		/*  无卡记录				*/
#define		_DISALLOW_TRAN         "120154"		/*  不允许交易				*/
#define		_DISALLOW_DEAL         "120155"		/*  不允许处理				*/
#define		_POSSIB_CHEAT          "120156"		/*  舞弊嫌疑				*/
#define		_CALL_SUPPLY           "120157"		/*  联系代理方				*/
#define		_OVER_DRAW             "120158"		/*  超提款限额				*/
#define		_OVER_FEE              "120159"		/*  费用超过限额			*/
#define		_IMP_SECU              "120160"		/*  侵犯安全				*/
#define		_ORI_AMOUNT_ERR        "120161"		/*  原始金额错				*/
#define		_OVER_TIMES            "120162"		/*  超提款次数				*/
#define		_CALL_SECU             "120163"		/*  通知安保				*/
#define		_SEIZURE_CARD          "120164"		/*  命令吞卡				*/
#define		_BELATE_ANSW           "120165"		/*  响应过时				*/
#define		_OVER_PIN_TIMES        "120166"		/*  密码错超限				*/
#define		_END_PROC              "120167"		/*  正在做日终				*/
#define		_NOT_FOUND_NET         "120168"		/*  找不到网络				*/
#define		_REPT_ENTRY            "120169"		/*  重复交易				*/
#define		_ID_ERR                "120170"		/*  证件错					*/
#define		_MCHANT_NO_HONOR       "120171"		/*  商户未承兑				*/
#define		_NO_HONOR_ORIG         "120172"		/*  原交易未承兑			*/
#define		_ASK_FAILURE           "120173"		/*  发送请求失败			*/
#define		_ISSU_FAILURE          "120174"		/*  发卡方故障				*/
#define		_REPEAT_ANSWER         "120175"		/*  重复应答				*/
#define		_NO_CENTER_ANSWER      "120176"		/*  中心无应答				*/
#define		_NO_ISSU_ANSWER        "120177"		/*  发卡方无应答			*/
#define		_ACQU_TIMEOUT          "120178"		/*  受理方超时应答			*/
#define		_ACQU_FAILURE          "120179"		/*  受理方故障				*/
#define		_COUNT_ERR             "120180"		/*  计数器错				*/
#define		_ORIG_CHANGE           "120181"		/*  原交易改变				*/
#define		_BOOKIN_LIMIT_ERR      "120182"		/*  登折限制				*/
#define		_NO_OBTAIN             "120183"		/*  无法到达				*/
#define		_DONOT_OPER            "120184"		/*  无法操作				*/
#define		_CHANGE_DATE           "120185"		/*  日期切换				*/
#define		_END_REQU              "120186"		/*  查询结束标志			*/
#define		_HOST_TRACE_NULL       "120187"		/*  主机流水号为空      	*/
#define		_ABSENT_FIT_CARD       "120188"		/*  FIT表中无此卡       	*/
#define		_CASHBOX_STAT_ERR      "120189"		/*  钞箱状态不对        	*/
#define		_REVE_ERR              "120190"		/*  冲正交易发生异常    	*/
#define		_INVA_MSG              "120191"		/*  报文内容非法			*/
#define		_FOUND_TIMEOUT         "120192"		/*  发现交易超时			*/
#define		_TOO_MANY_REVE         "120193"		/*  冲正交易太多			*/
#define		_INVA_TIME             "120194"		/*  时间非法				*/
#define		_TOO_LARGE_VALUE       "120195"		/*  数值太大 				*/
#define		_INVA_REVE_MAKE        "120196"		/*  冲正报文标识与类别不符	*/
#define		_INVA_SIGN             "120197"		/*  数字串正负符号错误		*/
#define		_INVA_OFFSET           "120200"		/*  无效BitMap配置偏移量	*/
#define		_BM_OPEN_ERR           "120201"		/*  BitMap配置文件打开		*/
#define		_BM_FILE_ERR           "120202"		/*  BitMap配置文件格式		*/
#define		_8583_DATA_LEN         "120203"		/*  8583数据超长			*/
#define		_8583_HEAD_ERR         "120204"		/*  8583结构错误 			*/
#define		_INVA_BUSS_TYPE        "120300"		/*  业务类型不存在 			*/
#define		_INVA_UNIT_CODE        "120301"		/*  单位代码不存在 			*/
#define		_INVA_TRAN_TYPE        "120302"		/*  交易类别无定义 			*/
#define		_INQU_RECV_FAIL        "120303"		/*  接收交易请求失败		*/
#define		_INQU_LEN_ERR          "120304"		/*  交易请求数据包长度出错 	*/
#define		_INQU_FORM_ERR         "120305"		/*  交易请求数据包格式出错 	*/
#define		_SEND_RETU_FAIL        "120306"		/*  回送交易结果失败 		*/
#define		_DATA_OVER_RANGE       "120307"		/*  数据超出范围	 		*/
#define		_GET_ACDAT_ERR	       "120308"		/*  获取会计日期错误 		*/
#define		_GET_SYSDAT_ERR	       "120309"		/*  获取系统日期错误 		*/
#define		_BAT_STATUS_ERR	       "120310"		/*  本批次状态错误	 		*/
#define		_BAT_PROC_NOW	       "120311"		/*  批量正在处理中	 		*/
#define		_ELE_NOT_ENOUGH	       "120312"		/*  交易要素不全	 		*/
#define		_AUTH_CHECK_ERR	       "120313"		/*  授权检查错		 		*/
#define		_REPLY_NODE_ERR	       "120314"		/*  不可回复非本网点信息	*/
#define		_REPLY_ALRE_ERR	       "120315"		/*  已回复					*/
#define		_CANCEL_ALRE_ERR	   "120316"		/*  已取消					*/
#define		_ALRE_PUR_ERR	   	   "120317"		/*  已经有该应用分类码权限  */
#define		_NO_PUR_ERR	   		   "120318"		/*  不存在该应用分类码权限  */
#define		_ALRE_ORG_PUR	   	   "120319"		/*  已有该机构的权限纪录  */
#define		_ALRE_TLR_PUR	   	   "120320"		/*  已有该柜员的权限纪录  */
#define		_ALRE_TXN_AUTH	   	   "120321"		/*  已有该交易的金额授权信息*/
#define		_NO_TXN_AUTH	   	   "120322"		/*  没有该交易的金额授权信息*/
#define		_REPLY_NO_ERR	       "120323"		/*  未回复					*/
#define		_RETU_NO_ERR	       "120324"		/*  尚未收到回执			*/
#define		_INACCT_SQN_ERR	       "120325"		/*  来帐包号错  			*/
#define		_WAIT_PROC_NOW	       "120326"		/*  有未入帐往帐在处理，请稍候*/

#define		_RCV_RTCBK_ERR	       "120400"		/*  汇入行号错              */
#define		_RCV_BANK_ERR	       "120401"		/*  接收行号错              */
#define		_RCV_SETTBK_ERR	       "120402"		/*  接收清算行号错          */
#define		_RPC_CODE_ERR	       "120403"		/*  收报中心代码错          */
#define		_NO_CTL_NODE	       "120404"		/*  非通汇控制网点          */
#define		_SYS_STAT_ERR1	       "120405"		/*  只能在日间及特殊状态操作*/
#define		_SYS_STAT_ERR2	       "120406"		/*  只能在清算、日间及特殊状态*/
#define		_AMT_LESS_LIMIT	       "120407"		/*  金额小于大额限制金额,需要加急 */
#define		_SND_NM_EMPTY	       "120408"		/*  发起人姓名空            */
#define		_RCV_NM_EMPTY	       "120409"		/*  接收人姓名空            */
#define		_SUMMARY_EMPTY	       "120410"		/*  摘要栏空                */
#define		_BUS_UNEXHAUST	       "120411"		/*  有未处理业务            */
#define		_NO_RTC_NODE	       "120412"		/*  非通汇网点          	*/
#define		_LOG_NO_ERR	       	   "120413"		/*  流水号错          		*/
#define		_TRACE_NO_ERR	       "120414"		/*  传票号错          		*/
#define		_TRAN_NODE_ERR	       "120415"		/*  非本网点账务       		*/
#define		_ALLOW_FUND_REMIT	   "120416"		/*  该业务可走行内资金汇划	*/
#define		_SBK_EQUAL_RBK		   "120417"		/*  发报行不能与收报行相同	*/
#define		_STCBK_EQUAL_RTCBK	   "120418"		/*  汇出行不能与汇入行相同	*/
#define		_NODE_INFO_ERR	   	   "120419"		/*  网点对应行号资料有误	*/
#define		_UNGRAT_PRINT_CONDI	   "120420"		/*  有不满足打印条件的记录	*/
#define		_DATE_ERR              "120421"		/*  录入日期或凭证日期错	*/
#define		_SND_RTCBK_ERR	       "120422"		/*  汇出行号错              */
#define		_SND_OBANK_ERR	       "120423"		/*  付款开户行号错          */
#define		_FEE_TYPE_ERR	       "120424"		/*  收费选项与报文优先级不符*/
                                               		                          
#define		_PRE_ERR_CODE          "120900"		/*  前置预置错误码			*/
#define		_NO_EXPECT_MSG         "120901"		/*  收到的信息并非预期		*/
#define		_NEED_ONLY_CONFIG      "120902"		/*  配置条件不唯一			*/
#define		_QUERY_END             "120903"		/*  查询结束				*/
                                              		                          
#define		_MSG_FMTNAME_ERR       "120905"		/*  信息格式名称错误		*/
#define		_MSG_LABEL_ERR         "120906"		/*  信息对话标识错误		*/
#define		_MSG_SEQU_ERR          "120907"		/*  信息顺序号错误			*/
#define		_INVA_ORAMSG_SEQU      "120908"		/*  原信息顺序号不合法		*/
#define		_INVA_MSG_SEQU         "120909"		/*  信息顺序号不合法		*/
#define		_FIELD_NUM_ERR         "120910"		/*  信息中包含域数目错		*/
#define		_FIELD_LEN_ERR         "120911"		/*  信息实际长度不符		*/
#define		_MAX_FIELD_SEQU        "120913"		/*  已达最大信息序列号		*/
#define		_OVER_ERR_NUM          "120914"		/*  超过允许错误数			*/
#define		_INVA_VOID_MSG         "120915"		/*  要撤销的信息非支付信息	*/
#define		_WAIT_TIME_OUT         "120916"		/*  等待时间过长			*/
                                              		                          
#define		_DB_OPER_ERR           "131000"		/*  数据库操作错误			*/
#define		_DB_FEAR_ERR           "131001"		/*  数据库致命错			*/
#define		_DB_CONN_ERR           "131002"		/*  连接数据库失败			*/
#define		_DB_INIT_ERR           "131003"		/*  初始化数据库设备错		*/
#define		_DB_LOGIN_ERR          "131004"		/*  登录数据库失败			*/
#define		_DB_OPEN_ERR           "131005"		/*  打开用户数据库失败		*/
#define		_DB_EXEC_ERR           "131006"		/*  执行数据库命令串错误	*/
#define		_DB_RESULT_ERR         "131007"		/*  返回数据库执行结果错	*/
#define		_DB_INS_ERR            "131008"		/*  记录插入失败 			*/
#define		_DB_PROC_ERR           "131009"		/*  存储过程出错			*/
#define		_DB_REPT_REC           "131010"		/*  重复的插入记录 			*/
#define		_DB_UPDATE_ERR         "131011"		/*  更新记录失败			*/
#define		_DB_NO_RECORD          "131012"		/*  数据库无对应记录		*/
#define		_DB_QUERY_ERR          "131013"		/*  数据库查询失败			*/
                                              		                          
#define		_SYS_BUSY_DELAY        "141200"		/*  因系统繁忙而延迟		*/
#define		_INSIDE_PROBLEM        "141201"		/*  因内部问题不能完成处理	*/
#define		_PIGEONHOLE_MSG        "141202"		/*  信息详细记录已被归档	*/
#define		_SYS_BUSY_REFU         "141203"		/*  外接系统繁忙交易被拒绝	*/
#define		_ABSE_LOGON_HOST       "141204"		/*  尚未登录主机			*/
#define		_ABSE_LOGON_APP        "141205"		/*  尚未登录应用系统		*/
#define		_REFU_ACCE             "141206"		/*  当前操作窗口不接受信息	*/
#define		_ID_PASS_ERR           "141207"		/*  用户标识或口令不正确	*/
#define		_ALRE_LOGON            "141208"		/*  已登录					*/
#define		_ALRE_LOGOUT           "141209"		/*  已退出					*/
#define		_PASS_EXPIRE           "141210"		/*  口令有效使用期限已过	*/
#define		_LOGON_SEQU_ERR        "141211"		/*  登录顺序错误			*/
#define		_DISALLOW_LOGON        "141212"		/*  不允许登录				*/ 
#define		_LOGON_TYPE_ERR        "141213"		/*  登录类型错误			*/
#define		_INVA_USEID            "141214"		/*  非法用户标识或登录类型	*/
#define		_PRE_ABSE_LOGON        "141215"		/*  前置机未签到			*/
#define		_SYS_CUT_OFF           "141218"		/*  系统截止				*/
#define		_START_TIME_LIMIT      "141219"		/*  开始时间大于结束时间	*/
#define		_NODE_NO_CLOSE         "141220"		/*  部门未关闭				*/
#define		_SYS_NO_CLOSE          "141221"		/*  系统未关闭				*/
#define		_PMS_NO_CLOSE          "141222"		/*  支付系统状态未关闭		*/
                                              		                          
#define		_FILE_OPEN_ERR         "141500"		/*  打开文件错				*/
#define		_FILE_INEX_CONF        "141501"		/*  无配置文件				*/
#define		_FILE_ERR_UPDA         "141502"		/*  文件更新错				*/
#define		_FILE_ERR_FIELD        "141503"		/*  文件更新域错			*/
#define		_FILE_AGAIN_UPDA       "141504"		/*  重复文件更新			*/
#define		_FILE_NO_RECORD        "141505"		/*  无文件记录				*/
#define		_FILE_REFU_UPDA        "141506"		/*  拒绝文件更新			*/
#define		_FILE_LOCK             "141507"		/*  文件锁定				*/
#define		_FILE_NAME_NULL        "141508"		/*  前端上送文件名不能为空	*/
#define		_FILE_INEXIST          "141509"		/*  前置无此文件,请重新上传	*/
#define		_FILE_REPEAT           "141510"		/*  已上传文件,不能重复上传	*/
#define		_FILE_INVA_FORM        "141511"		/*  上传文件无对应格式描述	*/
#define		_FILE_PARSE_ERR        "141512"		/*  前端上传文件解析失败	*/
#define		_FILE_SUCC_RETU        "141513"		/*  文件处理完已生成回盘文件*/
#define		_FILE_SERIAL_FAIL      "141514"		/*  申请批量磁盘文件编号失败*/
#define		_FILE_PARSE_FAIL       "141515"		/*  文件解析失败			*/
#define		_FILE_CREAT_FAIL       "141516"		/*  文件生成失败			*/
#define		_FILE_INEXI_FRETU      "141517"		/*  前置回盘文件未生成		*/
#define		_FILE_INEXI_HRETU      "141518"		/*  主机回盘文件未生成		*/
#define		_FILE_SUM_FINQ         "141519"		/*  前端上传文件总金额不符	*/
#define		_FILE_COUNT_FINQ       "141520"		/*  前端上传文件总笔数不符	*/
#define		_FILE_SUM_HRETU        "141521"		/*  主机返回文件总金额不符	*/
#define		_FILE_COUNT_HRETU      "141522"		/*  主机返回文件总笔数不符	*/
#define		_FILE_ERR_HRETU        "141523"		/*  主机返回文件有误		*/
#define		_FILE_PARSE_HRETU      "141524"		/*  主机返回文件解析失败	*/
#define		_FILE_AMT_ERR          "141525"		/*  当前文件余额不符		*/
#define		_FILE_SEQU_ERR         "141526"		/*  当前文件顺序号不符		*/
#define		_FILE_SUCC_REPEAT      "141527"		/*  文件已处理成功,不允许再处理	*/
#define		_FILE_PROC_REPEAT      "141528"		/*  文件当日不允许再次处理	*/
#define		_FILE_ALRE_AFFIRM      "141529"		/*  批次已确认,不能重复发起	*/
#define		_FILE_ACTDAT_ERR       "141530"		/*  文件汇总记录与文件名日期不符*/
#define		_FILE_NO_DATA          "141531"		/*  当日无数据，生成文件失败*/
                                              		                          
#define		_BRAN_INEXIST          "141600"		/*  网点号不存在或网点设置错*/
#define		_BRAN_NET_ERR          "141601"		/*  入网站点错				*/
#define		_BRAN_AREA_ERR         "141602"		/*  非本支行网点			*/
#define		_BRAN_AUTH_CON         "141603"		/*  无该网点授权设置		*/
#define		_OPER_LEVEL_LIMIT      "141650"		/*  柜员级别不够			*/
#define		_OPER_ERR              "141651"		/*  交易柜员错				*/
#define		_OPER_INEXIST          "141652"		/*  无此柜员				*/
#define		_OPER_NEED_DIFF        "141653"		/*  需要不同柜员			*/
#define		_OPER_PUR_ERR          "141654"		/*  柜员无此权限			*/
#define		_OPER_ORA_ERR          "141655"		/*  非原交易柜员			*/
#define		_OPER_PASS_ERR         "141656"		/*  柜员密码错				*/
                                              		                          
#define		_HOST_TIMEOUT          "141702"		/*  主机超时				*/
#define		_NET_ERR               "141703"		/*  网络故障				*/
#define		_NEED_REQU             "141704"		/*  请查询上笔交易是否成功	*/
#define		_BANK_OTHER_ERR        "141705"		/*  银行返回其它错误		*/
#define		_SEND_HOST_ERR         "141707"		/*  上送主机失败			*/
#define		_PRE_OTHER_ERR         "141708"		/*  前置机其它错误			*/
#define		_COMM_TIMEOUT          "141795"		/*  通讯超时				*/
#define		_SYSTEM_ERR            "141796"		/*  系统故障				*/
#define		_ERR_CORTROL           "141797"		/*  控制错					*/
#define		_NET_VER_ERR           "141798"		/*  网络版本不兼容			*/
                                              		                          
#define		_QPAIR_OPER_ERR        "111800"		/*  QPAIR操作失败       	*/
#define		_INVA_COMM_MODE        "111801"		/*  不支持的通讯方式		*/
#define		_CREAT_MSG_FAIL        "111803"		/*  MSG报文生成失败     	*/
#define		_SAVE_MSGH_FAIL        "111804"		/*  MSG报文头保存失败   	*/
#define		_SEND_ERR_FAIL         "111805"		/*  应用错误信息回送失败	*/
#define		_XML_OPER_ERR          "111806"		/*  XML操作错误      		*/
#define		_HICALL_TIMEOUT        "111807"		/*  HICALL调用超时   		*/
#define		_HICALL_FAIL           "111808"		/*  HICALL调用失败   		*/
#define		_GET_ENV_FAIL          "111809"		/*  取得环境变量失败    	*/
#define		_MALLOC_ERR            "111810"		/*  内存分配错误			*/
#define		_INVALID_LEN           "111811"		/*  通讯信息的长度域错		*/
#define		_READ_TIMEOUT          "111812"		/*  通讯层信息读超时		*/
#define		_FINGER_NULL           "111813"		/*  消息指针为空			*/
#define		_OPER_MSG_ERR          "111814"		/*  消息操作失败			*/
#define		_CLONE_MSG_ERR         "111815"		/*  无法复制消息			*/
#define		_DLL_OPER_ERR          "111816"		/*  动态库操作失败   		*/
#define		_APP_RET_ERR           "111817"		/*  应用返回出错     		*/
#define		_MUTEX_OPER_ERR        "111818"		/*  线程锁操作失败   		*/
#define		_MODE_ERR              "111819"		/*  发送或接收模式错误		*/
#define		_SET_PIPE_ERR          "111820"		/*  建立管道失败        	*/
#define		_READ_PIPE_ERR         "111821"		/*  读管道流失败 			*/
#define		_MSG_INIT_ERR          "111830"		/*  消息队列初始化错误		*/
#define		_MSG_PUR_ERR           "111831"		/*  消息队列权限错误		*/
#define		_MSG_EXIST             "111832"		/*  消息队列已存在			*/
#define		_MSG_INEXIST           "111833"		/*  消息队列不存在			*/
#define		_MSG_OPER_ERR          "111834"		/*  消息队列操作错误		*/
#define		_MSG_INVA_ID           "111835"		/*  消息队列标识错误		*/
#define		_MSG_FULL              "111836"		/*  消息队列消息数满    	*/
#define		_MSG_GET_ERR           "111837"		/*  消息队列取得错误    	*/
#define		_MSG_SEND_ERR          "111838"		/*  消息队列发送错误    	*/
#define		_MSG_RECV_ERR          "111839"		/*  消息队列接收错误		*/
#define		_SHM_INIT_ERR          "111850"		/*  共享内存初始化错误		*/
#define		_SHM_PUR_ERR           "111851"		/*  共享内存权限错误		*/
#define		_SHM_EXT_ERR           "111852"		/*  共享内存已存在			*/
#define		_SHM_SIZE_ERR          "111853"		/*  共享内存长度错误		*/
#define		_SHM_NOEXT             "111854"		/*  共享内存不存在			*/
#define		_SHM_NOMEM             "111855"		/*  共享内存空间不够		*/
#define		_SHM_OPER_ERR          "111856"		/*  共享内存操作错误 		*/
#define		_SHM_GET_ERR           "111857"		/*  共享内存取得错误		*/
#define		_SEM_INIT_ERR          "111870"		/*  初始化信号灯错 			*/
#define		_SEM_GET_ERR           "111871"		/*  信号灯取得错误			*/
#define		_SEM_P_ERR             "111872"		/*  信号灯 P 操作失败 		*/
#define		_SEM_V_ERR             "111873"		/*  信号灯 V 操作失败		*/
#define		_SEM_RM_ERR            "111874"		/*  删除信号失败			*/
#define		_IP_ADDR_ERR           "111880"		/*  IP地址错误				*/
#define		_IP_INVA_ADDR          "111881"		/*  IP地址未登记			*/
#define		_IP_REPE_ADDR          "111882"		/*  IP地址重复				*/
#define		_NET_TIME_OUT          "111883"		/*  网络超时错误			*/
#define		_NET_ACCE_RET          "111884"		/*  网络应答接收失败		*/
#define		_NET_INVA_HAND         "111885"		/*  网络握手协议无效		*/
#define		_NET_INVA_TRSP         "111886"		/*  网络传输协议无效		*/
#define		_SOCK_OPEN_ERR         "111890"		/*  套接字打开错误			*/
#define		_SOCK_READ_ERR         "111891"		/*  套接字读错误			*/
#define		_SOCK_WRIT_ERR         "111892"		/*  套接字写错误			*/
#define		_SOCK_CONN_ERR         "111893"		/*  套接字connect错误		*/
#define		_SOCK_BIND_ERR         "111894"		/*  套接字bind错误			*/
#define		_SOCK_ACCE_ERR         "111895"		/*  套接字accept错误		*/
#define		_SOCK_OPER_ERR         "111896"		/*  套接字操作错误			*/
#define		_NODE_OPER_ERR         "111910"		/*  节点操作错误			*/
#define		_NODE_GET_ERR          "111911"		/*  取数据节点错			*/
#define		_NODE_ROOT_NULL        "111912"		/*  根节点为空				*/
#define		_SYNC_OUT_FAIL         "111930"		/*  输出同步失败			*/
#define		_SYNC_CYCLE            "111931"		/*  处于同步周期			*/
#define		_SYNC_NEED_SEND        "111932"		/*  需要同步发送			*/
#define		_SYNC_NOT_SIGN         "111933"		/*  非同步对话标志			*/
#define		_SYNC_NOT_SEQU         "111934"		/*  非同步信息顺序号		*/
#define		_CSER_INIT_FAIL        "111950"		/*  CommunicationServer初始化失败*/
#define		_APPC_SESS_FAIL        "111951"		/*  申请 APPC SESSION 失败	*/
#define		_SNA_SEND_FAIL         "111952"		/*  SNA 通信上送失败		*/
#define		_SNA_RECV_FAIL         "111953"		/*  SNA 通信接收失败		*/
#define		_SNA_TIME_OUT          "111954"		/*  SNA 通信接收通信超时	*/
#define		_SNA_CONFIRM_FAIL      "111955"		/*  SNA 通信确认失败		*/
#define		_SNA_INIT_ERR	       "111956"		/*  SNA初始化错误			*/
#define		_SNA_ALLOCATE_FAIL     "111957"		/*  SNA分配SESSION失败		*/
#define		_SNA_FREE_FAIL 	       "111958"		/*  主机交易ABEND引起释放SESSION失败	*/
#define		_SNA_FINDLU_ERR 	   "111959"		/*  SNA查找LU失败			*/
#define		_ETF_GET_ERR	       "111970"		/*  获取ETF节点错误			*/
                                              		                          
#define		_MAC_ERR               "152000"		/*  MAC错误					*/
#define		_DECRY_ERR             "152001"		/*  解密错误				*/
#define		_ENCRY_CHECK_ERR       "152002"		/*  加密校检字错			*/
#define		_AUTH_CODE_ERR         "152003"		/*  核帐务认证码错			*/
#define		_PAY_CODE_ERR          "152004"		/*  支令码错				*/
#define		_CODESEAL_ERR          "152005"		/*  编码印鉴错				*/
#define		_CHECKSUM_ERR          "152006"		/*  Checksum不正确			*/
#define		_KEY_UPDATE_ERR        "152007"		/*  密钥更新成功			*/
#define		_KEY_UPDATE_FAIL       "152008"		/*  密钥更新失败			*/
#define		_SYS_UPDATE_KEY        "152009"		/*  系统请求重置密钥		*/
#define		_OUT_UPDATE_KEY        "152010"		/*  外部要求重置密钥		*/
#define		_KEY_ERR               "152011"		/*  密钥错误				*/
#define		_NEED_INIT_KEY         "152012"		/*  没有初装密钥			*/
#define		_PIN_FAILURE           "152013"		/*  PIN格式错				*/
#define		_CENTER_SECU_ERR       "152014"		/*  中心保密错				*/
#define		_ENMACH_STAT_ERR       "152015"		/*  加密机状态错误      	*/
                                              		                          
#define		_IN_LEDGER_UNCONF      "163000"		/*  来帐(包)不符			*/
#define		_OUT_LEDGER_UNCONF     "163001"		/*  往帐(包)不符			*/
#define		_SUM_LEDGER_UNCONF     "163002"		/*  往、来统计都错			*/
#define		_INEXIST_LEDGER_LIST   "163003"		/*  总帐明细未生成			*/
#define		_SUM_AMOUNT_UNCONF     "163004"		/*  总金额不符				*/
#define		_SUM_COUNT_UNCONF      "163005"		/*  总笔数不符				*/
#define		_DEBIT_CNT_ERR         "163006"		/*  借记笔数不符			*/
#define		_CREDIT_CNT_ERR        "163007"		/*  贷记笔数不符			*/
#define		_DEBIT_AMT_ERR         "163008"		/*  借记金额不符			*/
#define		_CREDIT_AMT_ERR        "163009"		/*  贷记金额不符			*/
#define		_CAN_NOT_SETT          "163010"		/*  核对不符不能清算		*/
#define		_TODAY_ALRE_SETT       "163011"		/*  当日已清算				*/
#define		_INVA_SETT_DATE        "163012"		/*  错误清算日期			*/
#define		_BUSS_NOT_SETT         "163013"		/*  业务未完成不能清算		*/
#define		_PMS_NOT_SETT          "163014"		/*  当日支付系统未清算		*/
                                             		                          
#define		_AUTH_CLOSE_CHECK      "FA0001"		/*  关门检查要求授权		*/
#define		_AUTH_VOID		       "FA0002"		/*  抹账交易要求授权		*/
#define		_AUTH_TABLE_MAIN       "FA0003"		/*  资料维护要求授权		*/
#define		_AUTH_TEMP_ACCT        "FA0004"		/*  挂账要求授权			*/
#define		_AUTH_PRINT_AGAIN      "FA0005"		/*  重复打印要求授权		*/
#define		_AUTH_HAND_FEE		   "FA0006"		/*  手续费手工输入要求授权	*/
#define		_AUTH_EXIGENCY_MSG     "FA0007"		/*  加急报文要求授权		*/
#define		_AUTH_VOID_APPLY	   "FA0008"		/*  撤销申请交易要求授权	*/
#define		_AUTH_BACK_APPLY	   "FA0009"		/*  退回申请交易要求授权	*/
#define		_AUTH_MODI_STATUS	   "FA0010"		/*  修改交易状态要求授权	*/
#define		_AUTH_REPT_DIFF		   "FA0011"		/*  重新清分要求授权		*/
                                              		                          
#define		_UNKNOW_ERR            "999999"		/*  未知故障				*/

/* 日志信息定义 */
#define		MSG_ENTER_OTA				"OTA0001"
#define		MSG_DISPLAY_TXN_CODE		"OTA0002"
#define		MSG_SEPARATE_LINE			"OTA0003"
#define		MSG_GOTO_LABEL				"OTA0004"
#define		MSG_END_STEP				"OTA0005"
#define		MSG_END_TRAN				"OTA0006"
#define		MSG_DISPLAY_APL_CLASS		"OTA0007"
#define		MSG_DISPLAY_TXN_ATTR		"OTA0008"
#define		MSG_STEP_START				"OTA0009"
#define		MSG_ERR_PROC_RESULT			"OTA0010"
#define		MSG_NO_CONDITION			"OTA0011"
#define		MSG_CONDITION_RESULT		"OTA0012"
#define		MSG_EXEC_FUNC				"OTA0013"
#define		MSG_EXEC_RESULT				"OTA0014"
#define		MSG_DO_SET					"OTA0015"
#define		MSG_DO_DELETE				"OTA0016"
#define		MSG_DO_GOTO					"OTA0017"
#define		MSG_DO_RETURN				"OTA0018"
#define		MSG_DO_EXIT					"OTA0019"
#define		MSG_DO_SWITCH				"OTA0020"
#define		MSG_SWITCH_BREAK			"OTA0021"
#define		MSG_SWITCH_DEFAULT			"OTA0022"
#define		MSG_WHILE_START				"OTA0023"
#define		MSG_WHILE_END_NOT_TRUE		"OTA0024"
#define		MSG_WHILE_END_BREAK			"OTA0025"
#define		MSG_SYSTEM_COMMAND			"OTA0026"
#define		MSG_SYSTEM_RESULT			"OTA0027"
#define		MSG_DO_CALL					"OTA0028"
#define		MSG_DISPLAY_COST_TIME		"OTA0029"
#define		MSG_DUMP_DS					"OTA0030"
#define		MSG_DISPLAY_TXNJNL_TITLE	"OTA0031"
#define		MSG_DISPLAY_TXNJNL_DETAIL	"OTA0032"
#define		MSG_DISPLAY_BUSDEF_TITLE	"OTA0033"
#define		MSG_DISPLAY_BUSDEF_DETAIL	"OTA0034"
#define		MSG_GET_BATCH_CONFIG_NAME	"OTA0035"
#define		MSG_READ_CONDITION			"OTA0036"
#define		MSG_DISP_TXN_RESULT			"OTA0037"
#define		MSG_DO_BREAK				"OTA0038"
#define		MSG_DISPLAY_ARGS			"OTA0039"

#define		MSG_INIT_STATISTIC_ERR		"OTA0040"
/*
#define		XXXXXXXXXXXXXXXXXX			"OTA0041"
#define		XXXXXXXXXXXXXXXXXX			"OTA0042"
#define		XXXXXXXXXXXXXXXXXX			"OTA0043"
#define		XXXXXXXXXXXXXXXXXX			"OTA0044"
#define		XXXXXXXXXXXXXXXXXX			"OTA0045"
#define		XXXXXXXXXXXXXXXXXX			"OTA0046"
#define		XXXXXXXXXXXXXXXXXX			"OTA0047"
#define		XXXXXXXXXXXXXXXXXX			"OTA0048"
#define		XXXXXXXXXXXXXXXXXX			"OTA0049"
#define		XXXXXXXXXXXXXXXXXX			"OTA0050"
#define		XXXXXXXXXXXXXXXXXX			"OTA0051"
#define		XXXXXXXXXXXXXXXXXX			"OTA0052"
#define		XXXXXXXXXXXXXXXXXX			"OTA0053"
#define		XXXXXXXXXXXXXXXXXX			"OTA0054"
#define		XXXXXXXXXXXXXXXXXX			"OTA0055"
#define		XXXXXXXXXXXXXXXXXX			"OTA0056"
#define		XXXXXXXXXXXXXXXXXX			"OTA0057"
#define		XXXXXXXXXXXXXXXXXX			"OTA0058"
#define		XXXXXXXXXXXXXXXXXX			"OTA0059"
*/

/*
 * 以下为错误信息定义
 */
#define		MSG_INIT_TXN_ERR			"OTA5000"
#define		MSG_BREAK_WHIT_SYSTEM_ERR	"OTA5001"
#define		MSG_BREAK_WHIT_INVALID_PROC	"OTA5002"
#define		MSG_LABEL_NOT_FOUND			"OTA5003"
#define		MSG_PUT_RESPONSE_ERR		"OTA5004"
#define		MSG_TXN_TIMEOUT				"OTA5005"
#define		MSG_INIT_DS_ERR				"OTA5006"
#define		MSG_CONNECT_DB_ERR			"OTA5007"
#define		MSG_INIT_BUSDEF_ERR			"OTA5008"
#define		MSG_ADD_DS_ERR				"OTA5009"
#define		MSG_INVALID_NODE			"OTA5010"
#define		MSG_NOT_ERR_PROC			"OTA5011"
#define		MSG_EXEC_ERR_PROC			"OTA5012"
#define		MSG_OPEN_DLL_ERR			"OTA5013"
#define		MSG_GET_ATTR_ERR			"OTA5014"
#define		MSG_INVALID_ATTR_VALUE		"OTA5015"
#define		MSG_GET_FUNC_PRA_ERR		"OTA5016"
#define		MSG_EXEC_FUNC_ERR			"OTA5017"
#define		MSG_GET_SET_ERR				"OTA5018"
#define		MSG_INVALID_SET_SENTENCE	"OTA5019"
#define		MSG_GET_REAL_VALUE_ERR		"OTA5020"
#define		MSG_DO_SET_ERR				"OTA5021"
#define		MSG_GET_DELETE_ERR			"OTA5022"
#define		MSG_GET_LABLE_ERR			"OTA5023"
#define		MSG_GET_SWITCH_EXPR_ERR		"OTA5024"
#define		MSG_DO_SWITCH_EXPR_ERR		"OTA5025"
#define		MSG_EXEC_SWITCH_BRANCH_ERR	"OTA5026"
#define		MSG_EXEC_WHILE_BRANCH_ERR	"OTA5027"
#define		MSG_GET_COMMAND_ERR			"OTA5028"
#define		MSG_SYSTEM_INIT_ARGS_ERR	"OTA5029"
#define		MSG_COMMAND_NOT_EXIST_ERR	"OTA5030"
#define		MSG_GET_TXN_PROC_ERR		"OTA5031"
#define		MSG_APP_IS_CLOSED			"OTA5032"	
#define		MSG_TXN_IS_CLOSED			"OTA5033"		
#define		MSG_GET_PKG_ATTR_ERR		"OTA5034"	
#define		MSG_MALLOC_ERR				"OTA5035"	
#define		MSG_ARGS_NOT_ATTR			"OTA5036"	
#define		MSG_INVALID_COND_EXPR		"OTA5037"	
#define		MSG_GET_CALL_FUNC_ERR		"OTA5038"	
#define		MSG_NEW_INPUT_ETF_ERR		"OTA5039"	
#define		MSG_GET_OUTPUT_ETF_ERR		"OTA5040"
#define		MSG_GET_PRI_CONFIG_ERR		"OTA5041"	
#define		MSG_GET_CONFIG_DS_ERR		"OTA5042"	
#define		MSG_INPUT_IS_NULL			"OTA0043"
#define		MSG_PARSE_EXPRESSION_ERR	"OTA0044"
#define		MSG_BUSTYP_CRPCOD_IS_NULL	"OTA0045"
#define		MSG_GET_BATCH_CONFIG_ERR	"OTA5046"	
#define		MSG_GET_BATCH_BUSTYP_ERR	"OTA5047"	
#define		MSG_GET_BATCH_CRPCOD_ERR	"OTA5048"	
#define		MSG_GET_BUSTYP_CRPCOD_ERR	"OTA5049"	
#define		MSG_FIND_BATCH_CONFIG_ERR	"OTA5050"
#define		MSG_GET_CRPCOD_DEFINE_ERR	"OTA5051"	
#define		MSG_GET_CRPCOD_VALUE_ERR	"OTA5052"	
#define		MSG_GET_SQL_DS_ERR			"OTA5053"	
#define		MSG_GET_SQL_ERR				"OTA5054"	
#define		MSG_SQL_FIELDS_INVALID		"OTA5055"	
#define		MSG_SQL_FIELDS_TOO_MANY		"OTA5056"	
#define		MSG_GET_SQL_VALUE_ERR		"OTA5057"	
#define		MSG_ALLOC_VALIST_ERR		"OTA5058"	
#define		MSG_SQL_TOO_LONG			"OTA5059"	
#define		MSG_RSPCOD_NOT_FOUND		"OTA5060"
/*
#define		XXXXXXXXXXXXXXXXXX			"OTA5061"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5062"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5063"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5064"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5065"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5066"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5067"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5068"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5069"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5070"
#define		XXXXXXXXXXXXXXXXXX			"OTA5071"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5072"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5073"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5074"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5075"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5076"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5077"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5078"	
#define		XXXXXXXXXXXXXXXXXX			"OTA5079"	
*/
