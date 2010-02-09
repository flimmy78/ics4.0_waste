/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hiafp_ctl.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2003-05-10
 Description    : 报文格式转换解析流程控制头文件
 Others         : 无
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-05-10  LiangWJ     完成

******************************************************************************/
#ifndef	_H_HIXMLAFP_CTL_
#define	_H_HIXMLAFP_CTL_


#define		MAX_DATA_LEN		512000	/* temporary */
#define		MIN_MP_SIZE			10
#define		MAX_MP_SIZE			500
#define		KEEP_TIME			60
#define		SWITCH_ON			1
#define		SWITCH_OFF			0

#ifndef		TRUE
#define		TRUE				1
#endif
#ifndef		FLASE
#define		FLASE				0
#endif

#ifdef INVALID_CONFIG
#undef INVALID_CONFIG
#endif
#ifdef BREAK_VAL
#undef BREAK_VAL
#endif
#ifdef RETURN_VAL
#undef RETURN_VAL
#endif
#ifdef CONTINUE_VAL
#undef CONTINUE_VAL
#endif
#define		INVALID_CONFIG		-100
#define		BREAK_VAL			100
#define		RETURN_VAL			101
#define		CONTINUE_VAL		102

#define		AFP_SUCCESS			0
#define		AFP_FAIL			-1
#define		NORMAL_BREAK		1

#define		DEFAULT_TIMEOUT		30

#define		MSGHEAD_SSC			"SSC"
#define		MSGHEAD_STC			"STC"
#define		MSGHEAD_SCH			"SCH"
#define		REQ_CODE			"rq"
#define		RSP_CODE			"rp"
#define		DP_REQ_ERR			"100501"
#define		DP_RSP_ERR			"100502"

#define		TRAN_SWITCH_ON		90811
#define		TRAN_SWITCH_OFF		90812
#define		LOG_SWITCH_ON		90813
#define		LOG_SWITCH_OFF		90814
#define		MON_SWITCH_ON		90815
#define		MON_SWITCH_OFF		90816
#define		QUERY_TRAN_STATUS	90819
#define		RELOAD_ITF			90823
#define		RELOAD_DLL			90824
#define		RELOAD_CODE_TABLE	90825


enum DelimiterType {
	DT_FIXED = 1,
	DT_DELI,
	DT_AHEAD_LEN,
	DT_DELI_STR,
	DT_INVAILD
};

enum ExchangeFlag {
	EF_EXTERNAL_TO_INNER = 1,
	EF_INNER_TO_EXTERNAL
};

enum GetTranConfigMode {
	BY_LOCAL_CODE = 1,
	BY_THIRD_CODE
};

enum SwitchKind {
	LK_LOG_SWITCH = 1,
	LK_MON_SWITCH
};

enum AlignMode {
	AM_LEFT = 1,
	AM_RIGHT
};


/* 配置节点定义 */
#define		APPLICATION_NODE	"Application"
#define		MEMPOOL_NODE		"MemPool"
#define		GETTXNCODE_NODE		"GetTxnCode"
#define		CODESWITCHING_NODE	"CodeSwitching"
#define		TABLE_NODE			"Table"
#define		COLUMN_NODE			"Column"
#define		MACRO_NODE			"Macro"
#define		DEFINE_NODE			"Define"
#define		QUOTE_NODE			"Quote"
#define		INCLUDE_NODE		"Include"
#define		TRANSACTION_NODE	"Transaction"
#define		REQUEST_NODE		"Request"
#define		RESPONSE_NODE		"Response"
#define		ITEM_NODE			"Item"
#define		GROUP_NODE			"Group"
/*added by kixiong*/
#define		READELEMENT_NODE		"ReadElement"
#define		READGROUPELEMENT_NODE 	"ReadGroupElement"
#define		WRITEELEMENT_NODE		"WriteElement"
#define		WRITEGROUPELEMENT_NODE 	"WriteGroupElement"
#define		NAMESPACEDECLARE_NODE	"NamespaceDeclare"
#define		READATTR_NODE			"ReadAttr"
#define		WRITEATTR_NODE			"WriteAttr"
#define		ETFNAME_ATTR			"ETF_name"
#define		NS_ATTR					"ns"
#define		GETELEMENT_NODE			"GetElement"
#define		ETFVALTYPE_ATTR 		"ETF_val_type"
#define		VALATTR_ATTR 			"attr_name"
#define		PATH_ATTR				"path"
#define		DEFAULT_ATTR			"default"

#define		PRESTACK_NODE		"PreStack"
#define		POSTSTACK_NODE		"PostStack"

#define		PACK8583_NODE			"Pack8583"    
#define		UNPACK8583_NODE			"UnPack8583"   

/*added by kixiong at 2007-4-24 17:01*/
#define     ERROR_NODE          "Error"
#define     DEFAULT_ERROR_NODE  "DefaultError"
#define     SYS_ERROR_CODE      "999999"
#define     SYS_ERROR_MSG       "SYSTEM ERROR"
#define     AFP_ERROR_CODE      "888888"
#define     AFP_ERROR_MSG       "DATA PARSE FAILED"
        	       	
#define		IF_NODE				"If"
#define		ELSEIF_NODE			"ElseIf"
#define		ELSE_NODE			"Else"
#define		SWITCH_NODE			"Switch"
#define		CASE_NODE			"Case"
#define		DEFAULT_NODE		"Default"
#define		RETURN_NODE			"Return"
#define		BREAK_NODE			"Break"
#define		WHILE_NODE			"While"
#define		CONTINUE_NODE		"Continue"
        	
#define		ADDITEM_NODE		"AddItem"
#define		DELITEM_NODE		"DelItem"
#define		COPYITEM_NODE		"CopyItem"
#define		PACKITEM_NODE		"PackItem"
#define		UNPACKITEM_NODE		"UnpackItem"
#define		SWITCHCODE_NODE		"SwitchCode"
#define		ADDHEAD_NODE		"AddHead"
#define		DELHEAD_NODE		"DelHead"
#define		GETHEAD_NODE		"GetHead"
#define		SAVEMSGHEAD_NODE	"SaveMsgHead"
#define		RESTOREMSGHEAD_NODE	"RestoreMsgHead"
#define		GETTRACE_NODE		"GetTrace"
#define		GETTELLER_NODE		"GetTeller"
#define		DEBUG_NODE			"Debug"
#define		IN_NODE				"In"
#define		OUT_NODE			"Out"
        	
/* 属性配置定义 */
#define		PREDLL_ATTR			"pre_dll"
#define		PREFUNC_ATTR		"pre_func"
#define		SPEDLL_ATTR			"spe_dll"
#define		SPEFUNC_ATTR		"spe_func"
#define		PRODLL_ATTR			"pro_dll"
#define		PROFUNC_ATTR		"pro_func"
#define		SEQNO_ATTR			"seq_no"
#define		NAME_ATTR			"name"
#define		CODE_ATTR			"code"
#define		APPLICATION_ATTR	"app"
#define		SERVER_ATTR			"server"
#define		SERVICE_ATTR		"service"
#define		TIMEOUT_ATTR		"timeout"
#define		TYPE_ATTR			"type"
#define		LENGTH_ATTR			"length"
#define		OFFSET_ATTR			"offset"
#define		POS_ATTR			"pos"
#define		HAVINGNS_ATTR			"having_ns"
#define		BODYNS_ATTR			"body_ns"
#define		DELIASC_ATTR		"deli_asc"
#define		DELISTR_ATTR		"deli_str"
#define		FILLASC_ATTR		"fill_asc"
#define		HEADLEN_ATTR		"head_len"
#define		INCLUDELEN_ATTR		"include_len"
#define		LENTYPE_ATTR		"len_type"
#define		ALIGNMODE_ATTR		"align_mode"
        	
#define		NECESSARY_ATTR		"necessary"
#define		REPEATNUM_ATTR		"repeat_num"
#define		REPEATNAME_ATTR		"repeat_name"
        	
#define		SOURNAME_ATTR		"sour_name"
#define		DESTNAME_ATTR		"dest_name"
        	
#define		VALUE_ATTR			"value"
#define		CONDITION_ATTR		"condition"
#define		EXPRESSION_ATTR		"expression"
        	
#define		ROOTNAME_ATTR		"root_name"
#define		TABNAME_ATTR		"tab_name"
#define		COLNAME_ATTR		"col_name"
#define		NEWNAME_ATTR		"new_name"
#define		HEADNAME_ATTR		"head_name"
#define		KEYNAME_ATTR		"key_name"
#define		XMLNAME_ATTR		"xml_name"
        	
#define		TITLE_ATTR			"title"
#define		FILE_ATTR			"file"
#define		DEBUGFILE_ATTR		"debug_file"
#define		ERRFILE_ATTR		"err_file"
        	
#define		INITSIZE_ATTR		"init_size"
#define		MAXSIZE_ATTR		"max_size"
#define		EXPANDSCALE_ATTR	"expand_scale"
        	
#define		TRANSWITCH_ATTR		"tran_switch"
#define		LOGSWITCH_ATTR		"log_switch"
#define		MONSWITCH_ATTR		"mon_switch"
#define		PASS_ATTR			"pass"
        	
#define		FIXED_VAL			"fixed"
#define		DELI_VAL			"deli"
#define		DELISTR_VAL			"deli_str"
#define		AHEADLEN_VAL		"ahead_len"
#define		ETF_VAL				"etf"
#define		MSG_VAL				"msg"
#define		MSGHEAD_VAL			"msg_head"
#define		MSGTEXT_VAL			"msg_text"

#define AFP_ERROR_CREATE_LOGGER_FAILED  "AFP0001" 
#define AFP_INFO_ENTERN_SVR             "AFP0002" 
#define AFP_ERROR_GET_SCH_FAILED        "AFP0003" 
#define AFP_INFO_REQUEST_TXN            "AFP0004" 
#define AFP_INFO_REPONSE_TXN            "AFP0005" 
#define AFP_ERROR_RECEIVE_MSG_FAILED    "AFP0006" 
#define AFP_INFO_GET_STC_SUCCESS        "AFP0007" 
#define AFP_ERROR_RETURN_CODE_FAILED    "AFP0008" 
#define AFP_INFO_EXTERN_TO_INNER        "AFP0009" 
#define AFP_INFO_INNER_TO_EXTERN        "AFP0011" 
#define AFP_ERROR_TRANSFORM_FAILED      "AFP0012" 
#define AFP_ERROR_SEND_MSG_FAILED       "AFP0013" 
#define AFP_INFO_AFP_DONE               "AFP0014" 
#define AFP_DEBUG_ENTERN_FUNC1          "AFP0015" 
#define AFP_ERROR_PRETREATE_ERROR       "AFP0016" 
#define AFP_DEBUG_PRETREATE_SUCCESS     "AFP0017" 
#define AFP_INFO_BYPASS                 "AFP0018" 
#define AFP_ERROR_GET_TXNCOD_FAILED     "AFP0019" 
#define AFP_INFO_GET_TXNCOD_SUCCESS     "AFP0020" 
#define AFP_ERROR_GET_TXN_CONFIG_FAILED "AFP0021" 
#define AFP_INFO_TXN_IS_CLOSED          "AFP0022" 
#define AFP_INFO_MSGHEAD                "AFP0025" 
#define AFP_INFO_EXTERN_DATA            "AFP0026" 
#define AFP_ERROR_PARSE_FAILED          "AFP0027" 
#define AFP_DEBUG_PARSE_SUCCESS         "AFP0028" 
#define AFP_ERROR_NO_MEMORY             "AFP0029" 
#define AFP_ERROR_ETF_STREAM_FAILED     "AFP0030" 
#define AFP_INFO_ETF_DATA               "AFP0032" 
#define AFP_DEBUG_DONE_FUNC_1           "AFP0033" 
#define AFP_DEBUG_ENTERN_FUNC_2         "AFP0034" 
#define AFP_ERROR_SPE_TREATE_FAILED     "AFP0036" 
#define AFP_INFO_POSTTREATE_SUCCESS     "AFP0037" 
#define AFP_ERROR_MATH_REQ_CFG_ERROR    "AFP0038" 
#define AFP_DEBUG_FUNC3_RETURN_SUCCESS  "AFP0040" 
#define APF_ERROR_GET_ECT_FAILED        "AFP0046" 
#define AFP_DEBUG_TREE_ETF              "AFP0047" 
#define AFP_ERROR_TREE_ETF_FAILED       "AFP0048" 
#define AFP_INFO_TREE_ETF_SUCCESS       "AFP0049" 
#define AFP_INFO_PACKET_DATA            "AFP0050" 
#define AFP_ERROR_PACKET_DATA_FAILED    "AFP0051" 
#define AFP_INFO_PACKET_DATA_SUCCESS    "AFP0052" 
#define AFP_INFO_SPECIAL_TREATE         "AFP0053" 
#define AFP_ERROR_ADD_XML_DECLARE_ERROR "AFP0056" 
#define AFP_DEBUG_DONE_FUNC_3           "AFP0058" 
#define AFP_INFO_START_PARSE            "AFP0059" 
#define AFP_INFO_END_PARSE              "AFP0060" 
#define AFP_INFO_START_PACKDATA         "AFP0061" 
#define AFP_INFO_END_PACKDATA           "AFP0063" 
#define AFP_INFO_XML_DECLARE_ADDED      "AFP0065" 
#define AFP_DEBUG_INNER_TO_EXTERN		"AFP0066" 
#define AFP_ERROR_SEND_RESPONSE_FAILED	"AFP0067" 
#define AFP_DEBUG_EXTERN_TO_INNER		"AFP0068" 
#define AFP_ERROR_CCA_RESPONSE_MSG		"AFP0069" 
#define AFP_INFO_START_PACK_ERROR_MSG	"AFP0070" 
#define AFP_ERROR_PACK_ERROR_MSG_FAILED	"AFP0071" 
#define AFP_INFO_END_PACK_ERROR_MSG		"AFP0072" 
#define AFP_DEBUG_ENTER_FUNC_4			"AFP0075" 
#define AFP_RECEIVE_NEXT_SUBMSG_FAILED	"AFP0077" 
#define AFP_DEBUG_END_FUNC_4			"AFP0078" 
#define AFP_ERROR_LOAD_SHARELIB_FAILED	"AFP0079" 
#define AFP_DEBUG_ENTER_FUNC_5			"AFP0080" 
#define AFP_DEBUG_ENTER_FUNC_6			"AFP0081" 
#define AFP_ERROR_TXNCOD_IS_NULL		"AFP0082" 
#define AFP_ERROR_GET_CFG_NODE_FAILED	"AFP0083" 
#define AFP_INFO_OBJECT_SERVER			"AFP0084" 
#define AFP_INFO_OBJECT_SERVICE			"AFP0085" 
#define AFP_INFO_TXN_TIMEOUT			"AFP0086" 
#define AFP_ERROR_GET_RQ_RP_NODE_FAILED	"AFP0087" 
#define AFP_DEBUG_ENTER_FUNC_7			"AFP0089" 
#define AFP_DEBUG_ENTER_FUNC_7_1		"AFP0090" 
#define AFP_DEBUG_ENTER_FUNC_7_2		"AFP0091" 
#define AFP_DEBUG_ENTER_FUNC_7_3		"AFP0092" 
#define AFP_DEBUG_ENTER_FUNC_7_4		"AFP0093" 
#define AFP_ERROR_SEQ_NOT_MATCH			"AFP0094" 
#define AFP_DEBUG_ENTER_FUNC_8			"AFP0095" 
#define AFP_ERROR_NOWITH_GETTXN_CFG		"AFP0096" 
#define AFP_DEBUG_FUNC_8_1				"AFP0097" 
#define AFP_DEBUG_SPE_GET_TXNCOD		"AFP0098" 
#define AFP_ERROR_GETTXN_ITEM_IS_NULL	"AFP0099" 
#define AFP_ERROR_XML_GET_TXNCOD		"AFP0010" 
#define AFP_ERROR_GETTXNCODEPART_FAILED "AFP0102" 
#define AFP_DEBUG_GETTXNCODE_DONE		"AFP0103" 
#define AFP_ERROR_GET_ATTR_TYPE_FAILED	"AFP0104" 
#define AFP_ERROR_GET_ATTR_FAILED 		"AFP0105" 
#define AFP_ERROR_INVALID_OFFSET_VALUE	"AFP0106" 
#define AFP_ERROR_INVALID_TYPE_VALUE	"AFP0107" 
#define AFP_ERROR_INVALID_LENGTH		"AFP0108" 
#define AFP_ERROR_INVOKE_PEX_FAILED		"AFP0110" 
#define AFP_INFO_EXPRESSION_VALUE		"AFP0111" 
#define AFP_DEBUG_CONDITION_EXP			"AFP0114" 
#define AFP_INFO_CONDITION_JUDGE		"AFP0115" 
#define AFP_ERROR_INVOKE_PEX2_FAILED	"AFP0116" 
#define AFP_INFO_CONDITION_JUDGE2		"AFP0117" 
#define AFP_ERROR_NULL_CFG_NODE			"AFP0120" 
#define AFP_ERROR_CREATE_DATA_ROOT		"AFP0121" 
#define AFP_DEBUG_ENTER_PACKDATA		"AFP0123" 
#define AFP_DEBUG_GETTXN_HERITABLEATTR	"AFP0124" 
#define AFP_DEBUG_DONE_PACKDATA			"AFP0125" 
#define AFP_ERROR_GET_NAMESPACE			"AFP0126" 
#define AFP_ERROR_GET_NAME_ATTR			"AFP0127" 
#define AFP_INFO_NOT_GET_NODE			"AFP0129" 
#define AFP_ERROR_NOT_CFG_NAME_ATTR		"AFP0130" 
#define AFP_ERROR_NOT_DECLARE_NAMESPACE	"AFP0131" 
#define AFP_ERROR_DECLARE_NAMESPACE		"AFP0132" 
#define AFP_ERROR_ETF_HAS_NOT_NODE		"AFP0133" 
#define AFP_ERROR_DO_EXPRESSION			"AFP0134" 
#define AFP_ERROR_ADD_ATTR				"AFP0135" 
#define AFP_ERROR_ADD_NAMESPACE_DECLARE	"AFP0136" 
#define AFP_INFO_ADD_ATTR				"AFP0137" 
#define AFP_ERROR_HAS_NOT_ATTR_VALUE	"AFP0139" 
#define AFP_ERROR_ADD_NODE				"AFP0140" 
#define AFP_INFO_PARSE_ATTR				"AFP0142" 
#define AFP_INFO_NO_XML_DECLARE			"AFP0143" 
#define AFP_ERROR_GET_XML_DECLARE		"AFP0144" 
#define AFP_ERROR_ADD_MSGHEAD			"AFP0145" 
#define AFP_ERROR_CUT_PROLOG			"AFP0146" 
#define AFP_ERROR_GET_XMLDATA_NODE		"AFP0147" 
#define AFP_INFO_INGNODE_NODE			"AFP0148" 
#define AFP_INFO_ADD_FIELD				"AFP0150" 
#define AFP_ERROR_ADD_FIELD				"AFP0151" 
#define AFP_INFO_8583_START_PARSE		"AFP0153" 
#define AFP_ERROR_CREATE_DATA_ROOT_NODE	"AFP0154" 
#define AFP_ERROR_UNPACKFROM8583_RETURN	"AFP0156" 
#define AFP_INFO_8583_MSG_TYPE			"AFP0023" 
#define AFP_INFO_ADD_8583_FIELD			"AFP0157" 
#define AFP_INFO_8583_END_PARSE			"AFP0158" 
#define AFP_ERROR_8583_GET_TYPECODE		"AFP0159" 
#define AFP_ERROR_8583_GET_FIELDS		"AFP0161" 
#define AFP_INFO_8583_MUST_FIELDS		"AFP0162" 
#define AFP_ERROR_CREATE8583_RETURN		"AFP0164" 
#define AFP_ERROR_FIELDS_IS_NOT_NUMBER	"AFP0165" 
#define AFP_ERROR_ETF_NO_FIELDS_DATA	"AFP0166" 
#define AFP_ERROR_ADD_8583_FIELDS		"AFP0167" 
#define AFP_INFO_8583_PACK_ADD_FIELDS	"AFP0168" 
#define AFP_INFO_NO_8583_OPT_FIELDS		"AFP0169" 
#define AFP_INFO_8583_OPT_FIELDS		"AFP0170" 
#define AFP_INFO_8583_NO_PACK_OPT_FIELD	"AFP0172" 
#define AFP_ERROR_PACKTO8583_RETURN		"AFP0175" 
#define AFP_DEBUG_ENTER_UNPACKSEGDAT	"AFP0177" 
#define AFP_DEBUG_START_UNPACKSEGDAT	"AFP0178" 
#define AFP_DEBUG_DONE_UNPACKSEGDAT		"AFP0180" 
#define AFP_ERROR_DATA_IS_TOO_SHORT		"AFP0181" 
#define AFP_ERROR_GET_ITEM_NAME_ATTR	"AFP0182" 
#define AFP_ERROR_GETITEMDATA			"AFP0183" 
#define AFP_ERROR_DEALFIELDDATA			"AFP0184" 
#define AFP_DEBUG_ENTER_GETITEMDATA		"AFP0186" 
#define AFP_ERROR_GET_DELI_TYPE			"AFP0187" 
#define AFP_ERROR_PARSE_LENGTH_EXPR		"AFP0188" 
#define AFP_ERROR_NO_LENGTH_ATTR		"AFP0189" 
#define AFP_ERROR_NO_HEADLEN_ATTR		"AFP0191" 
#define AFP_ERROR_NO_DELI_STRING		"AFP0192" 
#define AFP_ERROR_DATA_HAS_NO_DELI_STR	"AFP0193" 
#define AFP_ERROR_NO_DELI_CHAR			"AFP0194" 
#define AFP_ERROR_DATA_HAS_NO_DELI_CHAR	"AFP0195" 
#define AFP_ERROR_DONE_GETITEMDATA		"AFP0196" 
#define AFP_ERROR_TREE_XML				"AFP0198" 
#define AFP_ERROR_ITEM_GET_NAME_ATTR	"AFP0200" 
#define AFP_ERROR_GET_XMLGROUP_NODE		"AFP0201" 
#define AFP_INFO_DETAIL_COUNT			"AFP0203" 
#define AFP_ERROR_NO_EQUAL_DETAIL_COUNT	"AFP0204" 
#define AFP_ERROR_ADD_GROUP_NODE		"AFP0205" 
#define AFP_ERROR_GET_GROUP_NAME_ATTR	"AFP0207" 
#define AFP_ERROR_UNPACKSEGDATA_RETURN	"AFP0208" 
#define AFP_ERROR_NOT_MATCHING_DELI		"AFP0209" 
#define AFP_DEBUG_UNPACKGROUPDATA_DONE	"AFP0210" 
#define AFP_ERROR_GET_REPEAT_NUM		"AFP0211" 
#define AFP_ERROR_GETXMLFIELDDATA		"AFP0221" 
#define AFP_ERROR_ADD_XML_NODE			"AFP0223" 
#define AFP_INFO_ADD_FATHER_NODE		"AFP0224" 
#define AFP_ERROR_GETFIELDDATA			"AFP0225" 
#define AFP_ERROR_SETITEMDATA			"AFP0226" 
#define AFP_ERROR_GET_COND_EXPR			"AFP0228" 
#define AFP_ERROR_CALLPUBFUNC			"AFP0229" 
#define AFP_ERROR_PACKSEGDATA			"AFP0230" 
#define AFP_INFO_EXIT_PACK_BRANCH		"AFP0231" 
#define AFP_INFO_GOTO_DEFAULT_BRANCH	"AFP0233" 
#define AFP_DEBUG_END_PACKSWITCH		"AFP0234" 
#define AFP_DEBUG_END_UNPACKSWITCH		"AFP0237" 
#define AFP_DEBUG_WHILE					"AFP0240" 
#define AFP_DEBUG_WHILE_COND_NO_EQUAL	"AFP0241" 
#define AFP_DEBUG_WHILE_ERROR			"AFP0242" 
#define AFP_DEBUG_WHILE_NO_DATA			"AFP0246" 
#define AFP_INFO_RETURN_NOT_ZERO		"AFP0248" 
#define AFP_INFO_END_DORETURN			"AFP0249" 
#define AFP_INFO_END_DOBREAK			"AFP0250" 
#define AFP_INFO_END_DOCONTINUE			"AFP0251" 
#define AFP_INFO_GET_FIELD_DATA			"AFP0255" 
#define AFP_DEBUG_END_GETFIELDDATA		"AFP0256" 
#define AFP_ERROR_INVALID_DELI_TYPE		"AFP0259" 
#define AFP_ERROR_GET_PRELEN			"AFP0261" 
#define AFP_ERROR_GET_DELI_STR			"AFP0262" 
#define AFP_ERROR_GET_ASCII_DELI		"AFP0263" 
#define AFP_DEBUG_SETITEMDATA			"AFP0264" 
#define AFP_ERROR_NO_CFG_XML_NODE_NAME	"AFP0266" 
#define AFP_ERROR_ETF_GET_GRP_ATTR_VAL	"AFP0267" 
#define AFP_INFO_PARSE_GROUP_OVER		"AFP0268" 
#define AFP_INFO_PARSE_ADD_GROUP_NODE	"AFP0269" 
#define AFP_ERROR_CREATE_XML_NODE		"AFP0270" 
#define AFP_ERROR_CREATE_NAMESPACE		"AFP0271" 
#define AFP_ERROR_GET_REC_NODE			"AFP0274" 
#define AFP_DEBUG_END_PACKGROUPDATA		"AFP0276" 
#define AFP_INFO_PRE_VALUE				"AFP0278" 
#define AFP_INFO_AFTER_VALUE			"AFP0279" 
#define AFP_INFO_PRI_PRE_VALUE			"AFP0280" 
#define AFP_INFO_DATA_TOO_LONG			"AFP0281" 
#define AFP_INFO_PRI_AFTER_VALUE		"AFP0282" 
#define AFP_ERROR_INVALID_CONFIG		"AFP0285" 
#define AFP_ERROR_GET_ADDITEM_NAME_ATTR	"AFP0288" 
#define AFP_INFO_ADD_DEFAULT_FIELD		"AFP0289" 
#define AFP_ERROR_GET_DELITEM_NAME_ATTR	"AFP0292" 
#define AFP_INFO_DEL_FIELD				"AFP0293" 
#define AFP_ERROR_GET_DEST_SOURCE_NAME	"AFP0296" 
#define AFP_INFO_COPY_FIELD				"AFP0297" 
#define AFP_ERROR_GET_UNPACKITEM_NAME	"AFP0300" 
#define AFP_INFO_PARSE_FIELD			"AFP0302" 
#define AFP_ERROR_GET_PACKITEM_NAME		"AFP0306" 
#define AFP_ERROR_ADD_COMPLEX_FIELD		"AFP0308" 
#define AFP_ERROR_GET_MUST_ATTR			"AFP0311" 
#define AFP_ERROR_GET_CODE_NODE			"AFP0313" 
#define AFP_ERROR_GET_CODE_COLUMN		"AFP0314" 
#define AFP_INFO_CODE_TRANSFORM			"AFP0315" 
#define AFP_ERROR_GET_HEAD_NAME			"AFP0318" 
#define AFP_ERROR_GET_NAME_VALUE_ATTR	"AFP0319" 
#define AFP_ERROR_GET_VALUE_OR_FIELD	"AFP0320" 
#define AFP_ERROR_ADD_MSG_HEAD			"AFP0321" 
#define AFP_INFO_DEL_MSG_HEAD			"AFP0324" 
#define AFP_ERROR_GET_MSGHEAD			"AFP0327" 
#define AFP_INFO_GET_MSGHEAD			"AFP0328" 
#define AFP_ERROR_NOT_CREATE_MEMPOOL	"AFP0331" 
#define AFP_ERROR_GET_KEYNAM_TMOUT_ATTR "AFP0332" 
#define AFP_ERROR_MPLMALLOC_FAILED		"AFP0334" 
#define AFP_ERROR_USFMSGTOHEADSTRING	"AFP0335" 
#define AFP_INFO_SAVE_MSGHEAD			"AFP0336" 
#define AFP_ERROR_GET_KEYNAM			"AFP0339" 
#define AFP_INFO_RESTORE_MSGHEAD		"AFP0340" 
#define AFP_ERROR_RESTORE_MSGhEAD		"AFP0341" 
#define AFP_ERROR_GET_NODE_NAME_ATTR	"AFP0343" 
#define AFP_ERROR_GET_LOGNO				"AFP0344" 
#define AFP_ERROR_GETNODE_NAME_TXNCN	"AFP0345" 
#define AFP_ERROR_GETDUMTLR				"AFP0346" 
#define AFP_ERROR_GET_FILE_TYPE_ATTR	"AFP0348" 
#define AFP_INFO_NULL_PARA				"AFP0350" 
#define AFP_ERROR_NOT_CFG_ETFNAME_ATTR	"AFP0351" 
#define AFP_ERROR_GET_ATTR_NAME			"AFP0024" 
#define AFP_ERROR_EXCEED_LOCATION_DEEP	"AFP0352"
#define AFP_ERROR_CONFIG_NODE_ATTR		"AFP0353"
#define AFP_ERROR_CONFIG_PATH_ATTR		"AFP0354"
#define AFP_ERROR_DELETE_BOTH_SPACE		"AFP0355"
#define AFP_ERROR_GET_ATTR_CONFIG		"AFP0356"
#define AFP_ERROR_GET_DATA_NODE_ATTR	"AFP0357"
#define AFP_ERROR_ATTR_CONFIG			"AFP0358"
#define AFP_ERROR_ADD_ETF_NODE			"AFP0359"
#define AFP_ERROR_GET_CONFIG_ATTR		"AFP0361"
#define AFP_ERROR_PARSE_ATTR			"AFP0362"
#define AFP_ERROR_GET_NODE				"AFP0365"
#define AFP_INFO_DEFAULT_TEXT_ATTR		"AFP0366"
#define AFP_INFO_DEFAULT_2_ATTR			"AFP0367"
#define AFP_INFO_ADD_ETF_NODE_SUCCESS	"AFP0368"
#define AFP_INFO_POST_DEAL_ETF_NODE_OK	"AFP0369"
#define AFP_INFO_ADD_ETF_NODE_DEFAULT	"AFP0371"
#define AFP_INFO_NOT_GEN_ETF_NODE		"AFP0372"


#endif /* _H_HIAFP_CTL_ */
