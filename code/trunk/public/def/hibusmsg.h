/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: pub_msg.h
 Author			: peng_wh
 Version		: 1.0.0
 Date			: 2003.04.07
 Description	: 用于统一规定大前置外接系统和中间业务使用的返回码，使用范围是大前置内部
				  
 Others			: 
 History		: 
				  内容简述

  No.	Date		Author		Modification
  ===	==========	========	==============================================

******************************************************************************/

#define		_SUCCEED               "000000"		/*  成功					*/

#define		_INVA_LOGON            "301400"		/*  注册方式无效			*/
#define		_INVA_LOGOUT           "301401"		/*  注销方式无效			*/
#define		_FULL_LOGTAB           "301402"		/*  注册表满				*/
#define		_PROC_ALRE_LOGON       "301403"		/*  同一进程已注册			*/
#define		_APP_ALRE_LOGON        "301404"		/*  同一应用标识已注册		*/
#define		_PROC_APP_CLASH        "301405"		/*  进程和应用标识冲突		*/
#define		_NOT_FOUND_APP         "301406"		/*  未找到注册应用			*/
#define		_INVA_SOUR_LOGON       "301407"		/*  源应用未有效注册		*/
#define		_INVA_TRAG_LOGON       "301408"		/*  目的应用未有效注册		*/
#define		_RE_START              "301409"		/*  重新引导进程			*/
#define		_RE_START_ERR          "301410"		/*  重新引导进程失败		*/
#define		_LOST_INSIDE_DATA      "301411"		/*  内部数据丢失			*/
#define		_GRAV_PROC_ERR         "301412"		/*  严重程序错误			*/
#define		_START_APP_ERR         "301415"		/*  外部进程引导失败    	*/
#define		_SYS_EXIT              "301416"		/*  系统退出            	*/
#define		_TOO_MANY_APP          "301417"		/*  应用进程太多			*/
#define		_INVA_APP              "301418"		/*  无效应用标识			*/
#define		_APP_CHAN_ERR          "301419"		/*  应用标识转换错误		*/
#define		_TOO_MANY_ROU          "301420"		/*  路由表数据太多      	*/
#define		_INEXIST_ROU_TAB       "301421"		/*  路由表未配置        	*/
#define		_RE_START_PROC         "301422"		/*  重新引导进程 			*/
#define		_FOUND_DIE_PROC        "301424"		/*  发现进程死 				*/
#define		_LOST_INS_DATA         "301425"		/*  内部数据丢失			*/
#define		_NOT_ENV_VARI          "301440"		/*  没有设置环境变量		*/
#define		_PARA_NO_ASCII         "301450"		/*  参数非ASCI字符			*/
#define		_PARA_LEN_ERR          "301451"		/*  参数字节长度错			*/
#define		_PARA_NO_NUM           "301452"		/*  参数非数字字符			*/
#define		_GET_PARA_ERR          "301453"		/*  参数获取错误			*/
                                              		                          

#define		_PROCESSING            "320001"		/*  正在处理中				*/
#define		_ASK_AUTH              "320002"		/*  要求授权				*/
#define		_ACCT_NULL             "320003"		/*  帐号不能为空			*/
#define		_INVALID_ACCT          "320004"		/*  无效帐号				*/
#define		_FREEZE_ACCT           "320005"		/*  帐号（卡号）冻结		*/
#define		_NAME_ACCT_UNCONF      "320006"		/*  帐号（卡号）户名不符	*/
#define		_ERR_TRAN_STAT         "320007"		/*  交易状态错				*/
#define		_INVALID_CARD          "320008"		/*  无效卡号				*/
#define		_INVALID_AMOUNT        "320009"		/*  无效金额				*/
#define		_VIP_TRAN              "320010"		/*  贵宾交易				*/
#define		_PASSWD_ERR            "320011"		/*  持卡人或操作员密码错	*/
#define		_INVALID_TRAN          "320012"		/*  无效交易				*/
#define		_IRREGU_TRAN           "320013"		/*  非法交易				*/
#define		_PACK_ERR              "320014"		/*  数据包格式错误			*/
#define		_INEXIST_ORA_RECORD    "320015"		/*  无此原交易				*/
#define		_NOT_ENOUGH_INTEG      "320020"		/*  积分不够				*/
#define		_CLEAN_INTEG_ERR       "320021"		/*  积分清除出错			*/
#define		_INVA_CARD_KIND        "320022"		/*  卡种错					*/
#define		_PRINT_CLASH           "320023"		/*  打印冲突				*/
#define		_DATA_ERR              "320024"		/*  数据格式错				*/
#define		_REQU_STAT_ERR         "320026"		/*  请求状态错误			*/
#define		_INVA_SEQU             "320027"		/*  流水号和类型不符		*/
#define		_INVA_PAGE_REQU        "320028"		/*  不可识别的页请求		*/
#define		_INVA_PAGE_APPLY       "320029"		/*  页操作申请错误			*/
#define		_CREAT_PRETRACE_ERR    "320031"		/*  产生前置流水号错		*/
#define		_GET_PRETRACE_ERR      "320032"		/*  取前置流水号错			*/
#define		_NOT_ISSUE_CARD        "320033"		/*  未发卡					*/
#define		_INVA_PRINT_REQU       "320034"		/*  无效的打印请求			*/
#define		_INEXIST_AUTH_AMOUNT   "320036"		/*  无效授权金额			*/
#define		_ASK_PRINT             "320037"		/*  要求先打印来帐报单		*/
#define		_ENTER_LOGNO_ERR       "320038"		/*  录入流水号错			*/
#define		_VOUDATE_LIMIT         "320039"		/*  凭证日期不能大于当日	*/
#define		_OUTBANK_ERR           "320040"		/*  汇出行号或发报行号错	*/
#define		_INBANK_ERR            "320041"		/*  汇入行号或收报行号错	*/
#define		_INEXIST_RECORD        "320042"		/*  无此交易明细			*/
#define		_NOT_APPLY_SERV        "320043"		/*  未申请服务				*/
#define		_REPEAT_PACK           "320044"		/*  重报					*/
#define		_INEXIST_HOST_RECORD   "320045"		/*  主机无交易记录			*/
#define		_INVA_FIELD            "320046"		/*  信息中存在不合法的域	*/
#define		_NULL_FIELD_ERR        "320047"		/*  规定非空的域为空		*/
#define		_ERR_AMOUNT            "320048"		/*  交易金额不合法			*/
#define		_AMOUNT_LIMIT          "320049"		/*  转帐交易金额小于规定	*/
#define		_TRUST_DATE_ERR        "320050"		/*  委托日期不正确			*/
#define		_OUT_SAME_IN           "320051"		/*  发起行与接收行相同		*/
#define		_BANKNO_ERR            "320052"		/*  行号错					*/
#define		_REQU_AREA_ERR         "320053"		/*  查询范围不正确			*/
#define		_INVA_MSG_CONT         "320054"		/*  信息内容与对照信息不符	*/
#define		_INEXIST_COLLATE       "320055"		/*  对照信息不存在			*/
#define		_INVALID_MCHANT        "320056"		/*  无效网点或商户号		*/
#define		_INVA_FUNCTYPE         "320057"		/*  无效交易(信息类型错)	*/
#define		_NOT_OBLIGATE_PIN      "320058"		/*  银行存折未预留密码		*/
#define		_ACCT_NOT_SET          "320059"		/*  帐户未开户				*/
#define		_ACCT_ALRE_SET         "320060"		/*  帐户已开户				*/
#define		_CALL_ISSUE            "320061"		/*  联系发卡方				*/
#define		_SPEC_CALL             "320062"		/*  特别联系				*/
#define		_INVA_DATE             "320063"		/*  无效日期				*/
#define		_INVA_FEE_KIND         "320064"		/*  无效费用种类代号		*/
#define		_INVA_OPER             "320065"		/*  无效操作员号			*/
#define		_CHECK_PIN_ERR         "320066"		/*  银行密码校验错			*/
#define		_REPA_STOCK_SEQU       "320067"		/*  重复的证券流水号		*/
#define		_SHORTAG_STOCK_BALA    "320068"		/*  券商帐户余额不足		*/
#define		_STOCKACC_ERRSTAT      "320069"		/*  券商帐户状态错			*/
#define		_SEQU_ERR              "320070"		/*  银行产生流水号错误		*/
#define		_CROSS_ACCT_CLOSE      "320071"		/*  通存通兑被关闭			*/
#define		_INVA_STOCK_ACCT       "320072"		/*  券商帐户不存在			*/
#define		_PRINT_BANKBOOK        "320073"		/*  请到银行补打存折		*/
#define		_AMOUNT_OVER_LIMIT     "320074"		/*  单笔交易金额超限		*/
#define		_INVA_FUNC             "320080"		/*  此交易未开通			*/
#define		_INEXIST_STOCK         "320081"		/*  无此券商				*/
#define		_CHECK_PASSERR         "320082"		/*  资金密码校验错			*/
#define		_SHORTAG_BALAN         "320083"		/*  客户资金帐户余额不足	*/
#define		_OVER_SUMLIMIT         "320084"		/*  累计金额超限			*/
#define		_REPEAT_SEQU           "320085"		/*  重复的银行流水号		*/
#define		_INEXIST_REVE_RECORD   "320086"		/*  被冲正流水不存在		*/
#define		_ALREAD_REVE           "320087"		/*  该流水已冲正			*/
#define		_UNCONFOR_REVETRAN     "320088"		/*  冲正流水不符			*/
#define		_BALA_REFU_REVE        "320089"		/*  余额不足,不允许冲正		*/
#define		_INVA_BANKNO           "320090"		/*  无效银行号				*/
#define		_FUNDACC_ERRSTAT       "320091"		/*  资金帐户状态错			*/
#define		_INEXIST_FUNDACC       "320092"		/*  资金帐户不存在			*/
#define		_ACCT_ALRE_CLOSED      "320093"		/*  该帐户已销户			*/
#define		_NOT_BASED_PARA        "320094"		/*  证券与银行对应关系未建	*/
#define		_BASED_PARA            "320095"		/*  证券与银行对应关系已建	*/
#define		_DISALLOW_TRANSFER     "320096"		/*  该客户转帐功能未开启	*/
#define		_CLOSE_TRANSFER        "320097"		/*  该客户转帐功能已关闭	*/
#define		_ASSET_OVER_LIMIT      "320098"		/*  该客户资产总值低于下限	*/
#define		_SERIAL_UNCON          "320099"		/*  证券公司编号不符		*/
#define		_DISALLOW_FUNC         "320100"		/*  此交易未开通			*/
#define		_STOCK_NO_SIGN         "320101"		/*  证券公司未签到			*/
#define		_STOCK_LOGOUT          "320102"		/*  证券公司已签退			*/
#define		_NO_TRANSFER_FUNC      "320103"		/*  转帐功能未开启			*/
#define		_STOCK_SERV_ERR        "320104"		/*  证券公司服务器系统错误	*/
#define		_POSSIB_OPERERR        "320105"		/*  怀疑操作错				*/
#define		_AGAIN_ENTRY           "320106"		/*  请重新交易				*/
#define		_PART_HONOR            "320107"		/*  部分承兑				*/
#define		_REFUSE_BUSIN          "320108"		/*  拒绝交易				*/
#define		_INFRACT_SECU          "320109"		/*  违反安全规定			*/
#define		_NO_VOID_RECORD        "320110"		/*  被撤销流水不存在		*/
#define		_ALRE_VOID             "320111"		/*  被撤销流水已撤销		*/
#define		_UNCONFOR_TRAN         "320112"		/*  被撤销流水不符			*/
#define		_NO_RECORD             "320113"		/*  被查询流水不存在		*/
#define		_REFU_REVERSAL         "320114"		/*  拒绝冲正				*/
#define		_AVALID_TERMNO         "320115"		/*  无效终端				*/
#define		_REFU_HONOR            "320116"		/*  不承兑					*/
#define		_ERROR                 "320117"		/*  差错					*/
#define		_LABLE_HONOR           "320118"		/*  标识承兑				*/
#define		_INQU_RESP             "320119"		/*  查询响应方				*/
#define		_PART_AUTH             "320120"		/*  部分批准				*/
#define		_LEAD_AUTH             "320121"		/*  领导批准				*/
#define		_INVALID_ISSU          "320122"		/*  无此发卡方				*/
#define		_UPDATE_TRACK3         "320123"		/*  更新3磁道				*/
#define		_CLIENT_VOID           "320124"		/*  客户取消				*/
#define		_CLIENT_DISPUTED       "320125"		/*  客户有争执				*/
#define		_REPEAT_TRAN           "320126"		/*  重复交易				*/
#define		_AVALID_RET            "320127"		/*  无效响应				*/
#define		_NO_ACTION             "320128"		/*  不采取行动				*/
#define		_SUSP_FAIL             "320129"		/*  故障怀疑				*/
#define		_ERR_FEE               "320130"		/*  非法交易费				*/
#define		_REFU_UPDATE           "320131"		/*  不支持更新				*/
#define		_REPEAT_UPDATE         "320132"		/*  重复更新				*/
#define		_UPDATE_FIELD_ERR      "320133"		/*  更新字段错				*/
#define		_TARNSACT              "320134"		/*  正在处理				*/
#define		_UPDATE_ERR            "320135"		/*  更新失败				*/
#define		_NOJOIN_BANK           "320136"		/*  未联网银行				*/
#define		_PARTIAL               "320137"		/*  部分完成				*/
#define		_OVER_EXPIRE           "320138"		/*  过期,没收				*/
#define		_CHEAT_CARD            "320139"		/*  舞弊,没收				*/
#define		_CALL_BANK             "320140"		/*  联系,没收				*/
#define		_LIMIT_CARD            "320141"		/*  受限,没收				*/
#define		_PICKUP_CARD           "320142"		/*  挂失,没收				*/
#define		_LOCK_RECORD           "320143"		/*  记录被锁				*/
#define		_ERR_ACCOUNT           "320144"		/*  无贷记帐户				*/
#define		_LOSE_CARD             "320145"		/*  遗失卡没收				*/
#define		_ERR_CURR_ACC          "320146"		/*  无通用帐户				*/
#define		_ERR_INVEST_ACC        "320147"		/*  无投资帐户				*/
#define		_LACK_BALANCE          "320148"		/*  资金不足				*/
#define		_ERR_CHEQUE_ACC        "320149"		/*  无支票帐户				*/
#define		_ERR_SAVING_ACC        "320150"		/*  无储蓄帐户				*/
#define		_OVER_EXPI_CARD        "320151"		/*  过期卡					*/
#define		_PIN_ERR               "320152"		/*  个人密码错				*/
#define		_NO_CARD_RECORD        "320153"		/*  无卡记录				*/
#define		_DISALLOW_TRAN         "320154"		/*  不允许交易				*/
#define		_DISALLOW_DEAL         "320155"		/*  不允许处理				*/
#define		_POSSIB_CHEAT          "320156"		/*  舞弊嫌疑				*/
#define		_CALL_SUPPLY           "320157"		/*  联系代理方				*/
#define		_OVER_DRAW             "320158"		/*  超提款限额				*/
#define		_OVER_FEE              "320159"		/*  费用超过限额			*/
#define		_IMP_SECU              "320160"		/*  侵犯安全				*/
#define		_ORI_AMOUNT_ERR        "320161"		/*  原始金额错				*/
#define		_OVER_TIMES            "320162"		/*  超提款次数				*/
#define		_CALL_SECU             "320163"		/*  通知安保				*/
#define		_SEIZURE_CARD          "320164"		/*  命令吞卡				*/
#define		_BELATE_ANSW           "320165"		/*  响应过时				*/
#define		_OVER_PIN_TIMES        "320166"		/*  密码错超限				*/
#define		_END_PROC              "320167"		/*  正在做日终				*/
#define		_NOT_FOUND_NET         "320168"		/*  找不到网络				*/
#define		_REPT_ENTRY            "320169"		/*  重复交易				*/
#define		_ID_ERR                "320170"		/*  证件错					*/
#define		_MCHANT_NO_HONOR       "320171"		/*  商户未承兑				*/
#define		_NO_HONOR_ORIG         "320172"		/*  原交易未承兑			*/
#define		_ASK_FAILURE           "320173"		/*  发送请求失败			*/
#define		_ISSU_FAILURE          "320174"		/*  发卡方故障				*/
#define		_REPEAT_ANSWER         "320175"		/*  重复应答				*/
#define		_NO_CENTER_ANSWER      "320176"		/*  中心无应答				*/
#define		_NO_ISSU_ANSWER        "320177"		/*  发卡方无应答			*/
#define		_ACQU_TIMEOUT          "320178"		/*  受理方超时应答			*/
#define		_ACQU_FAILURE          "320179"		/*  受理方故障				*/
#define		_COUNT_ERR             "320180"		/*  计数器错				*/
#define		_ORIG_CHANGE           "320181"		/*  原交易改变				*/
#define		_BOOKIN_LIMIT_ERR      "320182"		/*  登折限制				*/
#define		_NO_OBTAIN             "320183"		/*  无法到达				*/
#define		_DONOT_OPER            "320184"		/*  无法操作				*/
#define		_CHANGE_DATE           "320185"		/*  日期切换				*/
#define		_END_REQU              "320186"		/*  查询结束标志			*/
#define		_HOST_TRACE_NULL       "320187"		/*  主机流水号为空      	*/
#define		_ABSENT_FIT_CARD       "320188"		/*  FIT表中无此卡       	*/
#define		_CASHBOX_STAT_ERR      "320189"		/*  钞箱状态不对        	*/
#define		_REVE_ERR              "320190"		/*  冲正交易发生异常    	*/
#define		_INVA_MSG              "320191"		/*  报文内容非法			*/
#define		_FOUND_TIMEOUT         "320192"		/*  发现交易超时			*/
#define		_TOO_MANY_REVE         "320193"		/*  冲正交易太多			*/
#define		_INVA_TIME             "320194"		/*  时间非法				*/
#define		_TOO_LARGE_VALUE       "320195"		/*  数值太大 				*/
#define		_INVA_REVE_MAKE        "320196"		/*  冲正报文标识与类别不符	*/
#define		_INVA_SIGN             "320197"		/*  数字串正负符号错误		*/
#define		_INVA_OFFSET           "320200"		/*  无效BitMap配置偏移量	*/
#define		_BM_OPEN_ERR           "320201"		/*  BitMap配置文件打开		*/
#define		_BM_FILE_ERR           "320202"		/*  BitMap配置文件格式		*/
#define		_8583_DATA_LEN         "320203"		/*  8583数据超长			*/
#define		_8583_HEAD_ERR         "320204"		/*  8583结构错误 			*/
#define		_INVA_BUSS_TYPE        "320300"		/*  业务类型不存在 			*/
#define		_INVA_UNIT_CODE        "320301"		/*  单位代码不存在 			*/
#define		_INVA_TRAN_TYPE        "320302"		/*  交易类别无定义 			*/
#define		_INQU_RECV_FAIL        "320303"		/*  接收交易请求失败		*/
#define		_INQU_LEN_ERR          "320304"		/*  交易请求数据包长度出错 	*/
#define		_INQU_FORM_ERR         "320305"		/*  交易请求数据包格式出错 	*/
#define		_SEND_RETU_FAIL        "320306"		/*  回送交易结果失败 		*/
#define		_DATA_OVER_RANGE       "320307"		/*  数据超出范围	 		*/
#define		_GET_ACDAT_ERR	       "320308"		/*  获取会计日期错误 		*/
#define		_GET_SYSDAT_ERR	       "320309"		/*  获取系统日期错误 		*/
#define		_BAT_STATUS_ERR	       "320310"		/*  本批次状态错误	 		*/
#define		_BAT_PROC_NOW	       "320311"		/*  批量正在处理中	 		*/
#define		_ELE_NOT_ENOUGH	       "320312"		/*  交易要素不全	 		*/
#define		_AUTH_CHECK_ERR	       "320313"		/*  授权检查错		 		*/
#define		_REPLY_NODE_ERR	       "320314"		/*  不可回复非本网点信息	*/
#define		_REPLY_ALRE_ERR	       "320315"		/*  已回复					*/
#define		_CANCEL_ALRE_ERR	   "320316"		/*  已取消					*/
#define		_ALRE_PUR_ERR	   	   "320317"		/*  已经有该应用分类码权限  */
#define		_NO_PUR_ERR	   		   "320318"		/*  不存在该应用分类码权限  */
#define		_ALRE_ORG_PUR	   	   "320319"		/*  已有该机构的权限纪录  */
#define		_ALRE_TLR_PUR	   	   "320320"		/*  已有该柜员的权限纪录  */
#define		_ALRE_TXN_AUTH	   	   "320321"		/*  已有该交易的金额授权信息*/
#define		_NO_TXN_AUTH	   	   "320322"		/*  没有该交易的金额授权信息*/
#define		_REPLY_NO_ERR	       "320323"		/*  未回复					*/
#define		_RETU_NO_ERR	       "320324"		/*  尚未收到回执			*/
#define		_INACCT_SQN_ERR	       "320325"		/*  来帐包号错  			*/
#define		_WAIT_PROC_NOW	       "320326"		/*  有未入帐往帐在处理，请稍候*/

#define		_RCV_RTCBK_ERR	       "320400"		/*  汇入行号错              */
#define		_RCV_BANK_ERR	       "320401"		/*  接收行号错              */
#define		_RCV_SETTBK_ERR	       "320402"		/*  接收清算行号错          */
#define		_RPC_CODE_ERR	       "320403"		/*  收报中心代码错          */
#define		_NO_CTL_NODE	       "320404"		/*  非通汇控制网点          */
#define		_SYS_STAT_ERR1	       "320405"		/*  只能在日间及特殊状态操作*/
#define		_SYS_STAT_ERR2	       "320406"		/*  只能在清算、日间及特殊状态*/
#define		_AMT_LESS_LIMIT	       "320407"		/*  金额小于大额限制金额,需要加急 */
#define		_SND_NM_EMPTY	       "320408"		/*  发起人姓名空            */
#define		_RCV_NM_EMPTY	       "320409"		/*  接收人姓名空            */
#define		_SUMMARY_EMPTY	       "320410"		/*  摘要栏空                */
#define		_BUS_UNEXHAUST	       "320411"		/*  有未处理业务            */
#define		_NO_RTC_NODE	       "320412"		/*  非通汇网点          	*/
#define		_LOG_NO_ERR	       	   "320413"		/*  流水号错          		*/
#define		_TRACE_NO_ERR	       "320414"		/*  传票号错          		*/
#define		_TRAN_NODE_ERR	       "320415"		/*  非本网点账务       		*/
#define		_ALLOW_FUND_REMIT	   "320416"		/*  该业务可走行内资金汇划	*/
#define		_SBK_EQUAL_RBK	   	   "320417"		/*  发报行不能与收报行行号相同*/
#define		_STCBK_EQUAL_RTCBK	   "320418"		/*  汇出行不能与汇入行相同	*/
#define		_NODE_INFO_ERR	   	   "320419"		/*  网点对应行号资料有误	*/
#define		_UNGRAT_PRINT_CONDI	   "320420"		/*  有不满足打印条件的记录	*/
#define		_DATE_ERR              "320421"		/*  录入日期或凭证日期错	*/
#define		_SND_RTCBK_ERR	       "320422"		/*  汇出行号错              */
#define		_SND_OBANK_ERR	       "320423"		/*  付款开户行号错          */
#define		_FEE_TYPE_ERR	       "320424"		/*  收费选项与报文优先级不符*/
                                              		                          
#define		_PRE_ERR_CODE          "320900"		/*  前置预置错误码			*/
#define		_NO_EXPECT_MSG         "320901"		/*  收到的信息并非预期		*/
#define		_NEED_ONLY_CONFIG      "320902"		/*  配置条件不唯一			*/
#define		_QUERY_END             "320903"		/*  查询结束				*/
                                              		                          
#define		_MSG_FMTNAME_ERR       "320905"		/*  信息格式名称错误		*/
#define		_MSG_LABEL_ERR         "320906"		/*  信息对话标识错误		*/
#define		_MSG_SEQU_ERR          "320907"		/*  信息顺序号错误			*/
#define		_INVA_ORAMSG_SEQU      "320908"		/*  原信息顺序号不合法		*/
#define		_INVA_MSG_SEQU         "320909"		/*  信息顺序号不合法		*/
#define		_FIELD_NUM_ERR         "320910"		/*  信息中包含域数目错		*/
#define		_FIELD_LEN_ERR         "320911"		/*  信息实际长度不符		*/
#define		_MAX_FIELD_SEQU        "320913"		/*  已达最大信息序列号		*/
#define		_OVER_ERR_NUM          "320914"		/*  超过允许错误数			*/
#define		_INVA_VOID_MSG         "320915"		/*  要撤销的信息非支付信息	*/
#define		_WAIT_TIME_OUT         "320916"		/*  等待时间过长			*/
                                              		                          
#define		_DB_OPER_ERR           "331000"		/*  数据库操作错误			*/
#define		_DB_FEAR_ERR           "331001"		/*  数据库致命错			*/
#define		_DB_CONN_ERR           "331002"		/*  连接数据库失败			*/
#define		_DB_INIT_ERR           "331003"		/*  初始化数据库设备错		*/
#define		_DB_LOGIN_ERR          "331004"		/*  登录数据库失败			*/
#define		_DB_OPEN_ERR           "331005"		/*  打开用户数据库失败		*/
#define		_DB_EXEC_ERR           "331006"		/*  执行数据库命令串错误	*/
#define		_DB_RESULT_ERR         "331007"		/*  返回数据库执行结果错	*/
#define		_DB_INS_ERR            "331008"		/*  记录插入失败 			*/
#define		_DB_PROC_ERR           "331009"		/*  存储过程出错			*/
#define		_DB_REPT_REC           "331010"		/*  重复的插入记录 			*/
#define		_DB_UPDATE_ERR         "331011"		/*  更新记录失败			*/
#define		_DB_NO_RECORD          "331012"		/*  数据库无对应记录		*/
#define		_DB_QUERY_ERR          "331013"		/*  数据库查询失败			*/
                                              		                          
#define		_SYS_BUSY_DELAY        "341200"		/*  因系统繁忙而延迟		*/
#define		_INSIDE_PROBLEM        "341201"		/*  因内部问题不能完成处理	*/
#define		_PIGEONHOLE_MSG        "341202"		/*  信息详细记录已被归档	*/
#define		_SYS_BUSY_REFU         "341203"		/*  外接系统繁忙交易被拒绝	*/
#define		_ABSE_LOGON_HOST       "341204"		/*  尚未登录主机			*/
#define		_ABSE_LOGON_APP        "341205"		/*  尚未登录应用系统		*/
#define		_REFU_ACCE             "341206"		/*  当前操作窗口不接受信息	*/
#define		_ID_PASS_ERR           "341207"		/*  用户标识或口令不正确	*/
#define		_ALRE_LOGON            "341208"		/*  已登录					*/
#define		_ALRE_LOGOUT           "341209"		/*  已退出					*/
#define		_PASS_EXPIRE           "341210"		/*  口令有效使用期限已过	*/
#define		_LOGON_SEQU_ERR        "341211"		/*  登录顺序错误			*/
#define		_DISALLOW_LOGON        "341212"		/*  不允许登录				*/ 
#define		_LOGON_TYPE_ERR        "341213"		/*  登录类型错误			*/
#define		_INVA_USEID            "341214"		/*  非法用户标识或登录类型	*/
#define		_PRE_ABSE_LOGON        "341215"		/*  前置机未签到			*/
#define		_SYS_CUT_OFF           "341218"		/*  系统截止				*/
#define		_START_TIME_LIMIT      "341219"		/*  开始时间大于结束时间	*/
#define		_NODE_NO_CLOSE         "341220"		/*  部门未关闭				*/
#define		_SYS_NO_CLOSE          "341221"		/*  系统未关闭				*/
#define		_PMS_NO_CLOSE          "341222"		/*  支付系统状态未关闭		*/
                                              		                          
#define		_FILE_OPEN_ERR         "341500"		/*  打开文件错				*/
#define		_FILE_INEX_CONF        "341501"		/*  无配置文件				*/
#define		_FILE_ERR_UPDA         "341502"		/*  文件更新错				*/
#define		_FILE_ERR_FIELD        "341503"		/*  文件更新域错			*/
#define		_FILE_AGAIN_UPDA       "341504"		/*  重复文件更新			*/
#define		_FILE_NO_RECORD        "341505"		/*  无文件记录				*/
#define		_FILE_REFU_UPDA        "341506"		/*  拒绝文件更新			*/
#define		_FILE_LOCK             "341507"		/*  文件锁定				*/
#define		_FILE_NAME_NULL        "341508"		/*  前端上送文件名不能为空	*/
#define		_FILE_INEXIST          "341509"		/*  前置无此文件,请重新上传	*/
#define		_FILE_REPEAT           "341510"		/*  已上传文件,不能重复上传	*/
#define		_FILE_INVA_FORM        "341511"		/*  上传文件无对应格式描述	*/
#define		_FILE_PARSE_ERR        "341512"		/*  前端上传文件解析失败	*/
#define		_FILE_SUCC_RETU        "341513"		/*  文件处理完已生成回盘文件*/
#define		_FILE_SERIAL_FAIL      "341514"		/*  申请批量磁盘文件编号失败*/
#define		_FILE_PARSE_FAIL       "341515"		/*  文件解析失败			*/
#define		_FILE_CREAT_FAIL       "341516"		/*  文件生成失败			*/
#define		_FILE_INEXI_FRETU      "341517"		/*  前置回盘文件未生成		*/
#define		_FILE_INEXI_HRETU      "341518"		/*  主机回盘文件未生成		*/
#define		_FILE_SUM_FINQ         "341519"		/*  前端上传文件总金额不符	*/
#define		_FILE_COUNT_FINQ       "341520"		/*  前端上传文件总笔数不符	*/
#define		_FILE_SUM_HRETU        "341521"		/*  主机返回文件总金额不符	*/
#define		_FILE_COUNT_HRETU      "341522"		/*  主机返回文件总笔数不符	*/
#define		_FILE_ERR_HRETU        "341523"		/*  主机返回文件有误		*/
#define		_FILE_PARSE_HRETU      "341524"		/*  主机返回文件解析失败	*/
#define		_FILE_AMT_ERR          "341525"		/*  当前文件余额不符		*/
#define		_FILE_SEQU_ERR         "341526"		/*  当前文件顺序号不符		*/
#define		_FILE_SUCC_REPEAT      "341527"		/*  文件已处理成功,不允许再处理	*/
#define		_FILE_PROC_REPEAT      "341528"		/*  文件当日不允许再次处理	*/
#define		_FILE_ALRE_AFFIRM      "341529"		/*  批次已确认,不能重复发起	*/
#define		_FILE_ACTDAT_ERR       "341530"		/*  文件汇总记录与文件名日期不符*/
#define		_FILE_NO_DATA          "341531"		/*  当日无数据，生成文件失败*/
                                              		                          
#define		_BRAN_INEXIST          "341600"		/*  网点号不存在或网点设置错*/
#define		_BRAN_NET_ERR          "341601"		/*  入网站点错				*/
#define		_BRAN_AREA_ERR         "341602"		/*  非本支行网点			*/
#define		_BRAN_AUTH_CON         "341603"		/*  无该网点授权设置		*/
#define		_OPER_LEVEL_LIMIT      "341650"		/*  柜员级别不够			*/
#define		_OPER_ERR              "341651"		/*  交易柜员错				*/
#define		_OPER_INEXIST          "341652"		/*  无此柜员				*/
#define		_OPER_NEED_DIFF        "341653"		/*  需要不同柜员			*/
#define		_OPER_PUR_ERR          "341654"		/*  柜员无此权限			*/
#define		_OPER_ORA_ERR          "341655"		/*  非原交易柜员			*/
#define		_OPER_PASS_ERR         "341656"		/*  柜员密码错				*/
                                              		                          
#define		_HOST_TIMEOUT          "341702"		/*  主机超时				*/
#define		_NET_ERR               "341703"		/*  网络故障				*/
#define		_NEED_REQU             "341704"		/*  请查询上笔交易是否成功	*/
#define		_BANK_OTHER_ERR        "341705"		/*  银行返回其它错误		*/
#define		_SEND_HOST_ERR         "341707"		/*  上送主机失败			*/
#define		_PRE_OTHER_ERR         "341708"		/*  前置机其它错误			*/
#define		_COMM_TIMEOUT          "341795"		/*  通讯超时				*/
#define		_SYSTEM_ERR            "341796"		/*  系统故障				*/
#define		_ERR_CORTROL           "341797"		/*  控制错					*/
#define		_NET_VER_ERR           "341798"		/*  网络版本不兼容			*/
                                              		                          
#define		_QPAIR_OPER_ERR        "311800"		/*  QPAIR操作失败       	*/
#define		_INVA_COMM_MODE        "311801"		/*  不支持的通讯方式		*/
#define		_CREAT_MSG_FAIL        "311803"		/*  MSG报文生成失败     	*/
#define		_SAVE_MSGH_FAIL        "311804"		/*  MSG报文头保存失败   	*/
#define		_SEND_ERR_FAIL         "311805"		/*  应用错误信息回送失败	*/
#define		_XML_OPER_ERR          "311806"		/*  XML操作错误      		*/
#define		_HICALL_TIMEOUT        "311807"		/*  HICALL调用超时   		*/
#define		_HICALL_FAIL           "311808"		/*  HICALL调用失败   		*/
#define		_GET_ENV_FAIL          "311809"		/*  取得环境变量失败    	*/
#define		_MALLOC_ERR            "311810"		/*  内存分配错误			*/
#define		_INVALID_LEN           "311811"		/*  通讯信息的长度域错		*/
#define		_READ_TIMEOUT          "311812"		/*  通讯层信息读超时		*/
#define		_FINGER_NULL           "311813"		/*  消息指针为空			*/
#define		_OPER_MSG_ERR          "311814"		/*  消息操作失败			*/
#define		_CLONE_MSG_ERR         "311815"		/*  无法复制消息			*/
#define		_DLL_OPER_ERR          "311816"		/*  动态库操作失败   		*/
#define		_APP_RET_ERR           "311817"		/*  应用返回出错     		*/
#define		_MUTEX_OPER_ERR        "311818"		/*  线程锁操作失败   		*/
#define		_MODE_ERR              "311819"		/*  发送或接收模式错误		*/
#define		_SET_PIPE_ERR          "311820"		/*  建立管道失败        	*/
#define		_READ_PIPE_ERR         "311821"		/*  读管道流失败 			*/
#define		_MSG_INIT_ERR          "311830"		/*  消息队列初始化错误		*/
#define		_MSG_PUR_ERR           "311831"		/*  消息队列权限错误		*/
#define		_MSG_EXIST             "311832"		/*  消息队列已存在			*/
#define		_MSG_INEXIST           "311833"		/*  消息队列不存在			*/
#define		_MSG_OPER_ERR          "311834"		/*  消息队列操作错误		*/
#define		_MSG_INVA_ID           "311835"		/*  消息队列标识错误		*/
#define		_MSG_FULL              "311836"		/*  消息队列消息数满    	*/
#define		_MSG_GET_ERR           "311837"		/*  消息队列取得错误    	*/
#define		_MSG_SEND_ERR          "311838"		/*  消息队列发送错误    	*/
#define		_MSG_RECV_ERR          "311839"		/*  消息队列接收错误		*/
#define		_SHM_INIT_ERR          "311850"		/*  共享内存初始化错误		*/
#define		_SHM_PUR_ERR           "311851"		/*  共享内存权限错误		*/
#define		_SHM_EXT_ERR           "311852"		/*  共享内存已存在			*/
#define		_SHM_SIZE_ERR          "311853"		/*  共享内存长度错误		*/
#define		_SHM_NOEXT             "311854"		/*  共享内存不存在			*/
#define		_SHM_NOMEM             "311855"		/*  共享内存空间不够		*/
#define		_SHM_OPER_ERR          "311856"		/*  共享内存操作错误 		*/
#define		_SHM_GET_ERR           "311857"		/*  共享内存取得错误		*/
#define		_SEM_INIT_ERR          "311870"		/*  初始化信号灯错 			*/
#define		_SEM_GET_ERR           "311871"		/*  信号灯取得错误			*/
#define		_SEM_P_ERR             "311872"		/*  信号灯 P 操作失败 		*/
#define		_SEM_V_ERR             "311873"		/*  信号灯 V 操作失败		*/
#define		_SEM_RM_ERR            "311874"		/*  删除信号失败			*/
#define		_IP_ADDR_ERR           "311880"		/*  IP地址错误				*/
#define		_IP_INVA_ADDR          "311881"		/*  IP地址未登记			*/
#define		_IP_REPE_ADDR          "311882"		/*  IP地址重复				*/
#define		_NET_TIME_OUT          "311883"		/*  网络超时错误			*/
#define		_NET_ACCE_RET          "311884"		/*  网络应答接收失败		*/
#define		_NET_INVA_HAND         "311885"		/*  网络握手协议无效		*/
#define		_NET_INVA_TRSP         "311886"		/*  网络传输协议无效		*/
#define		_SOCK_OPEN_ERR         "311890"		/*  套接字打开错误			*/
#define		_SOCK_READ_ERR         "311891"		/*  套接字读错误			*/
#define		_SOCK_WRIT_ERR         "311892"		/*  套接字写错误			*/
#define		_SOCK_CONN_ERR         "311893"		/*  套接字connect错误		*/
#define		_SOCK_BIND_ERR         "311894"		/*  套接字bind错误			*/
#define		_SOCK_ACCE_ERR         "311895"		/*  套接字accept错误		*/
#define		_SOCK_OPER_ERR         "311896"		/*  套接字操作错误			*/
#define		_NODE_OPER_ERR         "311910"		/*  节点操作错误			*/
#define		_NODE_GET_ERR          "311911"		/*  取数据节点错			*/
#define		_NODE_ROOT_NULL        "311912"		/*  根节点为空				*/
#define		_SYNC_OUT_FAIL         "311930"		/*  输出同步失败			*/
#define		_SYNC_CYCLE            "311931"		/*  处于同步周期			*/
#define		_SYNC_NEED_SEND        "311932"		/*  需要同步发送			*/
#define		_SYNC_NOT_SIGN         "311933"		/*  非同步对话标志			*/
#define		_SYNC_NOT_SEQU         "311934"		/*  非同步信息顺序号		*/
#define		_CSER_INIT_FAIL        "311950"		/*  CommunicationServer初始化失败*/
#define		_APPC_SESS_FAIL        "311951"		/*  申请 APPC SESSION 失败	*/
#define		_SNA_SEND_FAIL         "311952"		/*  SNA 通信上送失败		*/
#define		_SNA_RECV_FAIL         "311953"		/*  SNA 通信接收失败		*/
#define		_SNA_TIME_OUT          "311954"		/*  SNA 通信接收通信超时	*/
#define		_SNA_CONFIRM_FAIL      "311955"		/*  SNA 通信确认失败		*/
#define		_SNA_INIT_ERR	       "311956"		/*  SNA初始化错误			*/
#define		_SNA_ALLOCATE_FAIL     "311957"		/*  SNA分配SESSION失败		*/
#define		_SNA_FREE_FAIL 	       "311958"		/*  主机交易ABEND引起释放SESSION失败	*/
#define		_SNA_FINDLU_ERR 	   "311959"		/*  SNA查找LU失败			*/
#define		_ETF_GET_ERR	       "311970"		/*  获取ETF节点错误			*/
                                               		                          
#define		_MAC_ERR               "352000"		/*  MAC错误					*/
#define		_DECRY_ERR             "352001"		/*  解密错误				*/
#define		_ENCRY_CHECK_ERR       "352002"		/*  加密校检字错			*/
#define		_AUTH_CODE_ERR         "352003"		/*  核帐务认证码错			*/
#define		_PAY_CODE_ERR          "352004"		/*  支令码错				*/
#define		_CODESEAL_ERR          "352005"		/*  编码印鉴错				*/
#define		_CHECKSUM_ERR          "352006"		/*  Checksum不正确			*/
#define		_KEY_UPDATE_ERR        "352007"		/*  密钥更新成功			*/
#define		_KEY_UPDATE_FAIL       "352008"		/*  密钥更新失败			*/
#define		_SYS_UPDATE_KEY        "352009"		/*  系统请求重置密钥		*/
#define		_OUT_UPDATE_KEY        "352010"		/*  外部要求重置密钥		*/
#define		_KEY_ERR               "352011"		/*  密钥错误				*/
#define		_NEED_INIT_KEY         "352012"		/*  没有初装密钥			*/
#define		_PIN_FAILURE           "352013"		/*  PIN格式错				*/
#define		_CENTER_SECU_ERR       "352014"		/*  中心保密错				*/
#define		_ENMACH_STAT_ERR       "352015"		/*  加密机状态错误      	*/
                                              		                          
#define		_IN_LEDGER_UNCONF      "363000"		/*  来帐(包)不符			*/
#define		_OUT_LEDGER_UNCONF     "363001"		/*  往帐(包)不符			*/
#define		_SUM_LEDGER_UNCONF     "363002"		/*  往、来统计都错			*/
#define		_INEXIST_LEDGER_LIST   "363003"		/*  总帐明细未生成			*/
#define		_SUM_AMOUNT_UNCONF     "363004"		/*  总金额不符				*/
#define		_SUM_COUNT_UNCONF      "363005"		/*  总笔数不符				*/
#define		_DEBIT_CNT_ERR         "363006"		/*  借记笔数不符			*/
#define		_CREDIT_CNT_ERR        "363007"		/*  贷记笔数不符			*/
#define		_DEBIT_AMT_ERR         "363008"		/*  借记金额不符			*/
#define		_CREDIT_AMT_ERR        "363009"		/*  贷记金额不符			*/
#define		_CAN_NOT_SETT          "363010"		/*  核对不符不能清算		*/
#define		_TODAY_ALRE_SETT       "363011"		/*  当日已清算				*/
#define		_INVA_SETT_DATE        "363012"		/*  错误清算日期			*/
#define		_BUSS_NOT_SETT         "363013"		/*  业务未完成不能清算		*/
#define		_PMS_NOT_SETT          "363014"		/*  当日支付系统未清算		*/

#define		_AGR_NOT_FOUND         "400001"		/*  协议不存在		*/
#define		_AGR_NOT_EFFECT        "400002"		/*  协议未生效		*/
#define		_AGR_INVALID           "400003"		/*  协议已到期		*/
#define		_AGR_ERROR             "400004"		/*  协议不符		*/
#define		_AGR_EXISTS            "400005"		/*  协议已存在		*/
#define		_AGT_NOT_EXISTS        "400006"		/*  代理服务不存在		*/
#define		_AGT_CLOSED            "400007"		/*  代理服务已关闭		*/
#define		_AGT_EXISTS            "400008"		/*  代理服务已存在		*/
                                              		                          
#define		_CIM_OVR_TLRLVL        "450101"     /*  柜员级别超出范围,应为0-4 */
#define     _CIM_OVR_ORGPRV        "450102"     /*  超出柜员所属机构应用权限 */

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
