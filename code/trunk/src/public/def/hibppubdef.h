/* 
 * History: Date        Position        Author                Action
 * ----------------------------------------------------------------------------
 *          2003-03-20  ShangHai        ChenYG                Create
 *          2007-05016  ShangHai        kixiong               Modify
 *          2007-7-17   TianJin         liangwj               ����Exit��ǩ
 ******************************************************************************/

#ifndef  _PUB_DEF_H
#define  _PUB_DEF_H

/*
 * modified by kixiong at 2007-5-16 17:32
 * ������Ҫ֧��һ��������Ӧ����ļ�������CallFunc�����Ĳ�����
 * ������ļ�����Ϊ����
 *
#define  PUB_DLL				"dll/pltatl.so"
#define  EXT_DLL				"dll/extatl.so"
*/
#define  PUB_DLL				"PUB"
#define  EXT_DLL				"EXT"
/*modified end*/

#define  EXP_DLL				"dll/hipex.so"
#define  MON_DLL				"dll/model.so"
#define  PUB_ERROR_PROC			"DefaultErrorProc"
#define  BATCH_CONFIG          	"BatConfig"
#define  GRANT_FLAG             0
#define  FORBID_FLAG            1
#define  CLSTRC_FLAG            0
#define  OPNTRC_FLAG            1
#define  STATISTIC_ON				1
#define  STATISTIC_OFF				0

#define  SYSDIVIDEBASE          256
#define  SYS_NOTEXIST	        127

#define	 LOADTRANMAXTIME		10
#define	 RECOVERY_MSGTYPE		"ONLRCV"
#define  PLT_OUT_MSGTYP         "PLTOUT"            /* �����ⷢ��Ϣ���� */

#define  AUTH_TXNCOD            "033311"            /* ��Ȩ���� */

#define  PUBDLLDEF_NAME         "PUB"
#define  EXTDLLDEF_NAME         "EXT"
#define  SYSTEMDEF_NAME         "SYS"
#define  EXPDLLDEF_NAME         "EXP"
#define  TXNFLGDEF_NAME         "TXN"
#define  MONSERV_NAME         	"MON"

#define  ERR_MSG_TYPE         	"E"
#define  SUCC_MSG_TYPE         	"N"
#define  AUTH_MSG_TYPE         	"A"
#define  WARN_MSG_TYPE         	"W"

/* ��������Դ���� */
#define	DS_MSG_TYP				1
#define	DS_ETF_TYP				2
#define	DS_XML_TYP				3
#define	DS_STRUCT_TYP			4
#define	DS_BUFFER_TYP			5

/* ���̿��Ʒ���ֵ */
#define  DLLFILE_NOTEXIST       -1000
#define	INVALID_CONFIG			-1001
#define	BREAK_VAL				100
#define	CONTINUE_VAL			101
#define	GOTO_VAL				102
#define	RETURN_VAL				103
/* ����Exit��ǩ Added by liangwj at 2007-7-17 */
#define	EXIT_VAL				104

/* �������̿��ƽڵ� */
#define	ARGS_NODE		"Args"
#define	ARG_NODE		"Arg"
#define	EXEC_NODE		"Exec"
#define	SET_NODE		"Set"
#define	DELETE_NODE		"Delete"
#define	GOTO_NODE		"Goto"
#define	RETURN_NODE		"Return"
/* ����Exit��ǩ Added by liangwj at 2007-7-17 */
#define	EXIT_NODE		"Exit"
#define	BREAK_NODE		"Break"
#define	CONTINUE_NODE	"Continue"
#define	SWITCH_NODE		"Switch"
#define	WHILE_NODE		"While"
#define	IF_NODE			"If"
#define	ELSEIF_NODE		"ElseIf"
#define	ELSE_NODE		"Else"
#define	SYSTEM_NODE		"System"
#define	CALL_NODE		"Call"
#define	LABEL_NODE		"Label"
#define	CASE_NODE		"Case"
#define	DEFAULT_NODE	"Default"
#define	INCLUDE_NODE	"Include"
#define	MACRO_NODE		"Macro"
#define	QUOTE_NODE		"Quote"

#define	EXPRESSION_ATTR	"expression"
#define	CONDITION_ATTR	"condition"
#define	FUNC_ATTR		"func"
#define	VALUE_ATTR		"value"
#define	COMMAND_ATTR	"command"
#define	PATH_ATTR		"path"
#define	NAME_ATTR		"name"
#define	FILE_ATTR		"file"

#define	BAS_TYPE		'~'
#define	ETF_TYPE		'$'
#define	BCFG_TYPE		'#'
#define	DS_TYPE			'@'
#define	MHED_TYPE		'%'
#define	PARA_TYPE		'#'
#define	ESC_CHAR		'\\'
#define	SEP_CHAR		'.'

#define  PUBTXNJNL_BASE_NUM		37		   /* Ӧ����ˮ�������������� */

#define  APPLICATION_MAX_NUM    10         /* ���������Ӧ����    */
#define  TRAN_MAX_NUM           300        /* �������������    */
#define  TRAN_STEP_MAX_NUM      50         /* �������ԭ�ӽ�����  */
#define  STEP_ATR_MAX_NUM       20         /* ���ײ������������  */
#define  LOG_NAME_LEN           50         /* ��־�ļ�����  */
#define  PRI_ITEM_NUM			32		   /* ���˽�������� */
#define  PRI_ITEM_NAME_LEN		32		   /* ���˽���������������� */

#define  MAX_COND_NUM			15		   /* ����������� */

#define  SQLCOD_LEN          	10 
#define  SQLCOD_PRE          	999999     /* Ԥ��SqlCod�ڵ�ֵ */

#define  LABEL_LEN          	10

#define  SERV_CODE_LEN          3 
#define  CONDITION_TYPE_LEN     4 
#define  CONDITION_VAR_LEN      128 
#define  CONDITION_CMP_SYM_LEN  3 
#define  CONDITION_VAL_LEN      15 
#define  DONE_FUNC_TYPE_LEN     30
#define  DONE_FUNC_ARG_LEN      60 
#define  STEP_SEQ_LEN           20 
#define  ATTRIBUTE_LEN          32 
#define  PRIV_SPACE_LEN         1024 
#define  FILE_NAME_LEN      	255 
#define  DLL_FILE_NAME_LEN      30 
#define  CON_FILE_NAME_LEN      50 
#define  CON_FILE_NUM_LEN       3 
#define  FUNC_NAME_LEN          30 
#define  TMP_BUF_LEN            1024 
#define  TTXNCD_LEN             10 
#define  TXNCOD_LEN             6 
#define  MAX_SERVICE_NAME_LEN   64 

#define  APLCLS_LEN             3 
#define  BUSSUB_LEN             15 

#define  LOGNO_LEN              14 
#define  FRSPCD_LEN             6 
#define  RESULT_MSG_LEN         60
#define  SVRTYP_LEN             6
#define  CRPCOD_LEN             10
#define  CRPSUB_LEN             20
#define  CRDNO_LEN              30
#define  ORGNO_LEN              6
#define  NODNO_LEN              6
#define  TLRID_LEN              10
#define  CNTRID_LEN             10
#define  NODTRC_LEN             20
#define  TXNCNL_LEN             3
#define  CNLSUB_LEN             10
#define  HLOGNO_LEN             9
#define  HRSPCD_LEN				6
#define  TCUSID_LEN             30
#define  TLOGNO_LEN             20
#define  TRSPCD_LEN				6
#define  BUSTYP_LEN             6
#define  AGTNOD_LEN             6
#define  SVRCNL_LEN             128
#define  CUSID_LEN              13
#define  ACTTYP_LEN             2
#define  ACTSQN_LEN             2
#define  CNLSTS_LEN             128
#define  SYSID_LEN              6
#define  BLOGNO_LEN             12
#define  DATEND_LEN             2
#define  TRMNO_LEN              10
#define  MCKEY1_LEN             40
#define  MCKEY2_LEN             40
#define  PROCOD_LEN             10
#define  IPADR_LEN              16
#define  IPPORT_LEN				6
#define  ADDR_LEN				60
#define  TELNO_LEN              20
#define  CRPINF_LEN             128
#define  IDTYP_LEN              2
#define  IDCRD_LEN              30
#define  POSTNO_LEN             6
#define  FIXTEL_LEN             20
#define  MOBTEL_LEN             15
#define  LCHKTM_LEN             10
#define	 BKNO_LEN				6
#define	 CCYCOD_LEN				3
#define	 DSKNO_LEN				12    /*���κų���*/

/*����ʱ���ඨ��*/
#define  DATE_LEN				8
#define  TIME_LEN				6
#define  DATETIME_LEN			14

/*�ļ�Ŀ¼����*/
#define  HOSTRECVDIR			"dat/host/recv"
#define  HOSTSENDDIR			"dat/host/send"
#define  TERMRECVDIR			"dat/term/recv"
#define  TERMSENDDIR			"dat/term/send"
#define  LOCALDATDIR			"dat/local"
#define  THRDFILEDIR			"dat"
#define  RPTDATDIR				"rpt"
#define  MULTIDATDIR			"tmp"
#define  DIR_LEN 				80

/*FTP����*/
#define  USERNAME_LEN			30
#define  USERPASSWD_LEN			30	

/*��Ϣ�ඨ��*/
#define  MSGBUSTYP_LEN			2
#define  MSGAPLCOD_LEN			6
#define  MSGFILNAM_LEN			50
#define  MSGHLOGNO_LEN			9
#define  MSGORGNO_LEN			6
#define  MSGTLRID_LEN			7
#define  MSGBLKNO_LEN			2
#define  MSGDATA_LEN			500

#define  BLKSTARTNO				1
#define  FILESTARTFLG			'S'
#define  FILEMIDFLG				'C'
#define  FILEENDFLG				'E'

#define  TXNSTSPRED				"U"        /*  Ԥ��״̬   */
#define  TXNSTSSERR				"X"        /*  ����ʧ��   */
#define  TXNSTSTOUT				"T"        /*  ���ͳ�ʱ   */
#define  TXNSTSSUCC				"S"        /*  ���׳ɹ�   */
#define  TXNSTSFAIL				"F"        /*  ����ʧ��   */
#define  TXNSTSCRCD				"C"        /*  ���ױ����� */
#define  TXNSTSCCLD				"D"        /*  ���ױ����� */
#define  TXNSTSERRD				"E"        /*  ��������   */

/*�����ඨ��*/
#define  FLAG_LEN				1
#define  ACTNO_LEN              21
#define  AMOUNT_LEN				15
#define  INTERVAL_LEN			3
#define  TIMEOUT_LEN			3
#define  MAXTIMES_LEN			4
#define  SQLST_LEN				4096    /*SQL�����󳤶�*/
#define  COLVAL_LEN				384     /*SQL�����󳤶�*/

/*���ƶ���*/
#define  CUSNAM_LEN             60		/*�ͻ����Ƴ���*/
#define  COMMAN_LEN             60		
#define  BUSNAM_LEN             60      
#define  TCUSNM_LEN             60		/*�������ͻ����Ƴ���*/
#define  NODNAM_LEN             60		/*�������Ƴ���*/
#define  CRPNAM_LEN             60		/*��˾���Ƴ���        */
#define  TBLNAM_LEN             30		/*��������            */
#define  SVRNAM_LEN				8		/*����������          */
#define  COLUMN_NAME_LEN		32		/*���ݿ��ֶ�����󳤶�*/
#define  ATTRNAME_LEN			20		/*�������Ƴ���        */
#define  SERV_NAME_LEN          3		/*����������          */
#define  FILNAM_LEN          	128	    /*����������          */

/*�û����ݴ洢���ֶγ��ȶ���*/
#define  RECKEY_LEN				100 
#define  USRDAT_LEN             3072
#define  PAGNUM_LEN             4

/*������Ϣ���ֶγ��ȶ���*/
#define OPCCOD_LEN				4				
#define SETBK_LEN				12
#define SBKNO_LEN				12

/*��ʱ���ݻ�����ֶγ��ȶ��� */
#define RECIDX_LEN				2
#define ETFREC_LEN				3072

/*TIA��TOA����*/
#define  CCSCOD_LEN				4
#define  TIATYP_LEN				1
#define  ATHLVL_LEN				2
#define  SUPID_LEN				7
#define  PIN_LEN				6
#define  SUPDEV_LEN				1
#define  ATHTBL_LEN				60
#define  OPRLVL_LEN				1
#define  TRMVER_LEN				8
#define  MSGTYP_LEN				1
#define  RSPCOD_LEN				6
#define  RSPMSG_LEN				60
#define  ERRFLD_LEN				4
#define  TRMSQN_LEN				6
#define  STXNCD_LEN				4
#define  SAPLCD_LEN				2
#define  TXNSYM_LEN				3
#define  TCKNO_LEN				11
#define  PAGID_LEN				1
#define  DATlEN_LEN				4
#define  TXNSRC_LEN				5
#define  FIL_LEN				2
#define  FIL1_LEN				3
#define  FIL2_LEN				5

/*��Ȩԭ��ṹ��Ϣ����*/
#define  ATHREC_NUM				10
#define  ATHCOD_LEN				2
#define  ATHMSG_LEN				2
#define  ATHDAT_LEN				60

#define	 INTERVAL				"10"		/*ȱʡ�������ط���ѯ���ʱ��*/
#define	 TIMEOUT				"60"		/*ȱʡ�������ط���ʱʱ��*/
#define	 MAXTIMES				"10"		/*ȱʡ�������ط�������*/
#define	 MAXTIMEOUT				300			/*�������ʱʱ��*/

/*������䶨��*/
#define CONCOD_LEN				20
#define SELECT_LEN				800
#define FROM_LEN				64
#define WHERE_LEN				512
#define FIELD_LEN				256

#ifdef MULTIQUERY
#define MAXRECORD				1000	/*��ҳ��ѯ����������ѯ���Ϊ1000����¼�Ĵ���*/
#define MAX_LINE_PER_PAGE	    19		/*ǰ��ÿҳ��ʾ������¼��*/
#define FILE_LINE_LEN			3072	/*�ļ���ÿ�����ݳ���*/
#define FIRST_PAGE_CODE			"6401"	/*ǰ����ʾ������ҳ��Ϣ��*/
#define END_PAGE_CODE			"6402"	/*ǰ����ʾ����βҳ��Ϣ��*/
#endif

/*�������Ͷ���*/
#define TXNTYP_NORMAL 	"N" 
#define TXNTYP_CRCT     "C" 
#define TXNTYP_RSND     "R" 
#define TXNTYP_CCLD     "D" 

#define RSND_CCLD		"9"

/*�������Զ���*/
#define ATTR_INTEGRITY "integrity" 
#define ATTR_INTEGRITY_POS 1
#define ATTR_NO_INTEGRITY	'0'		/*���������Կ���*/
#define ATTR_SYS_CRCT		'1'		/*���������������*/
#define ATTR_CND_CRCT		'2'		/*�����������������Ҫ�����Կ��ƣ�*/
#define ATTR_SYS_RSND		'6'		/*������������ط�*/
#define ATTR_CND_RSND		'7'		/*�����������ط�����Ҫ�����Կ��ƣ�*/


#define ATTR_NOCHK "nochk" 
#define ATTR_NOCHK_POS 2 
#define ATTR_NEED_CHK	'0'				/* ������� */
#define ATTR_NO_CHK		'1'				/* ��������� */


#define ATTR_SIGNON "signon" 
#define ATTR_SIGNON_POS 3 

#define ATTR_PROTOCAL "protocal" 
#define ATTR_PROTOCAL_POS 4 

#define ATTR_NORESPONSE "noresponse" 
#define ATTR_NORESPONSE_POS 5 
#define ATTR_NEED_RESP	'0'		/*��Ӧ*/
#define ATTR_NO_RESP	'1'		/*����Ӧ*/

#define ATTR_NODB	 "nodatabase" 
#define ATTR_NODB_POS 	6 
#define ATTR_NEED_DB		'0'		/* ������Ҫ���ݿ����� */
#define ATTR_NO_DB			'1'		/* ����Ҫ���ݿ����� */
#define ATTR_OPEN_DB		'2'		/* ȫ����Ҫ���ݿ����� */

#define ATTR_INTGTYPE "integtype" 
#define ATTR_INTGTYPE_POS 7 
#define ATTR_INTGTYPE_NO		'0'		/* �ǳ���\�ط����� */
#define ATTR_INTGTYPE_HAND		'1'		/* �ֹ��������� */
#define ATTR_INTGTYPE_SYS		'2'		/* ϵͳ�������� */
#define ATTR_INTGTYPE_RDR		'6'		/* �ط����� */
#define ATTR_INTGTYPE_CCL		'9'		/* �������� */

#define ATTR_MONITOR "monitor" 
#define ATTR_MONITOR_POS 8 
#define ATTR_MONITOR_NO		'0'			/* ���ͼ�� */
#define ATTR_MONITOR_YES		'1'		/* �ͼ��   */



/*��������״̬*/
#define RUN_STATUS_LEN	16
#define RUN_STS_CRCT run_status[0]		/*�Ƿ��ѵǼǳ��� 0:δ�Ǽ� 1:�ѵǼ�  BP��֧��Ԥ�Ǽ�*/
#define RUN_STS_SCRC run_status[1]		/*�Ƿ������������Կ��� 0:δ������1:����*/
#define RUN_STS_HOST run_status[2]		/*�������״���*/
#define RUN_STS_THRD run_status[3]		/*���������״���*/
#define RUN_STS_RSND run_status[4]		/*�Ƿ��ѵǼ��ط� 0:δ�Ǽ� 1:�ѵǼ� 2:Ԥ�Ǽ�*/
#define RUN_STS_RESP run_status[5]		/*�Ƿ��ѻ�Ӧ 0:��Ӧ 1:����Ӧ 2:�ѻ�Ӧ*/
#define RUN_STS_DB   run_status[6]		/*�Ƿ������ݿ�����*/

#define RUN_STS_INIT_VAL	'0'
#define RUN_STS_CRCT_REG	'1'
#define RUN_STS_RSND_REG	'1'
#define RUN_STS_RSND_PRE	'2'
#define RUN_STS_RESP_NORSP	'1'
#define RUN_STS_RESP_RSPED	'2'
#define RUN_STS_DB_ONL		'1'
#define RUN_STS_SCRC_START	'1'

/*���������붨��*/
#define ERRPRO_SUCCESS		0		/*������ɹ�*/
#define ERRPRO_CONTINUE		1		/*������ɹ���������������*/
#define ERRPRO_ERROR		-1		/*���������*/
#define TXNFAILED		    3		/* ���׷���ʧ�� */
#define TXNAUTHED		    -9		/* ������Ȩ���� */

/*ԭ�ӽ��׷����붨��*/
#define BP_SUCCESS		0		/*����ɹ�*/
#define BP_APPERR		-1		/*Ӧ�ô���*/
#define BP_SYSERR		-2		/*ϵͳ����*/
#define BP_NOPROC		-10		/*δִ��*/

/*added by kixiong at 2008-10-24 15:55
 *�α���ǿ����
 */
#define MAX_OPEN_CURSOR 10
#define MAX_OPEN_CONN   10

/* ��Ϣ�㲥���� */
#define MSG_INFORM		"1"
#define MSG_BROADCAST	"2"
#define MSG_FILE		"3"
#define MSG_PRINTFILE	"4"

#define SSCNETTIMEOUT	"100502"
#define SSCNETSENDERR	"100501"

/*�û��Զ�������ṹ*/
#define Bus_Def_num    bus_def.item_num 

#define Bus_Nam1  	args.item_name[0 ] 
#define Bus_Nam2   	args.item_name[1 ] 
#define Bus_Nam3  	args.item_name[2 ] 
#define Bus_Nam4   	args.item_name[3 ] 
#define Bus_Nam5   	args.item_name[4 ] 
#define Bus_Nam6   	args.item_name[5 ] 
#define Bus_Nam7  	args.item_name[6 ] 
#define Bus_Nam8  	args.item_name[7 ] 
#define Bus_Nam9  	args.item_name[8 ] 
#define Bus_Nam10 	args.item_name[9 ] 
#define Bus_Nam11 	args.item_name[10] 
#define Bus_Nam12 	args.item_name[11] 
#define Bus_Nam13 	args.item_name[12] 
#define Bus_Nam14 	args.item_name[13] 
#define Bus_Nam15 	args.item_name[14] 

#define Bus_Val1  	args.data[0 ] 
#define Bus_Val2   	args.data[1 ] 
#define Bus_Val3  	args.data[2 ] 
#define Bus_Val4   	args.data[3 ] 
#define Bus_Val5   	args.data[4 ] 
#define Bus_Val6   	args.data[5 ] 
#define Bus_Val7  	args.data[6 ] 
#define Bus_Val8  	args.data[7 ] 
#define Bus_Val9  	args.data[8 ] 
#define Bus_Val10 	args.data[9 ] 
#define Bus_Val11 	args.data[10] 
#define Bus_Val12 	args.data[11] 
#define Bus_Val13 	args.data[12] 
#define Bus_Val14 	args.data[13] 
#define Bus_Val15 	args.data[14] 

/*������ˮ�ṹ*/
#define Step_Args_Num  	args.item_num 

#define Step_Arg1_Nam  	args.item_name[0 ] 
#define Step_Arg2_Nam   args.item_name[1 ] 
#define Step_Arg3_Nam   args.item_name[2 ] 
#define Step_Arg4_Nam   args.item_name[3 ] 
#define Step_Arg5_Nam   args.item_name[4 ] 
#define Step_Arg6_Nam   args.item_name[5 ] 
#define Step_Arg7_Nam   args.item_name[6 ] 
#define Step_Arg8_Nam   args.item_name[7 ] 
#define Step_Arg9_Nam   args.item_name[8 ] 
#define Step_Arg10_Nam  args.item_name[9 ] 
#define Step_Arg11_Nam  args.item_name[10] 
#define Step_Arg12_Nam  args.item_name[11] 
#define Step_Arg13_Nam  args.item_name[12] 
#define Step_Arg14_Nam  args.item_name[13] 
#define Step_Arg15_Nam 	args.item_name[14] 

#define Step_Arg1    	args.data[0 ] 
#define Step_Arg2   	args.data[1 ] 
#define Step_Arg3   	args.data[2 ] 
#define Step_Arg4   	args.data[3 ] 
#define Step_Arg5   	args.data[4 ] 
#define Step_Arg6   	args.data[5 ] 
#define Step_Arg7   	args.data[6 ] 
#define Step_Arg8   	args.data[7 ] 
#define Step_Arg9    	args.data[8 ] 
#define Step_Arg10    	args.data[9 ] 
#define Step_Arg11    	args.data[10] 
#define Step_Arg12    	args.data[11] 
#define Step_Arg13    	args.data[12] 
#define Step_Arg14   	args.data[13] 
#define Step_Arg15   	args.data[14] 

/*������ˮ�ṹ*/
#define PubTr_ColNum   txn_jnl.item_num 
#define PubTr_LogNo    txn_jnl.data[0 ] 
#define PubTr_TTxnCd   txn_jnl.data[1 ] 
#define PubTr_TxnCod   txn_jnl.data[2 ] 
#define PubTr_TxnTyp   txn_jnl.data[3 ] 
#define PubTr_BusTyp   txn_jnl.data[4 ] 
#define PubTr_CrpCod   txn_jnl.data[5 ] 
#define PubTr_ActDat   txn_jnl.data[6 ] 
#define PubTr_CcyTyp   txn_jnl.data[7 ] 
#define PubTr_TxnAmt   txn_jnl.data[8 ] 
#define PubTr_Fee      txn_jnl.data[9 ] 
#define PubTr_ActNo    txn_jnl.data[10] 
#define PubTr_CrdNo    txn_jnl.data[11] 
#define PubTr_OrgNo    txn_jnl.data[12] 
#define PubTr_NodNo    txn_jnl.data[13] 
#define PubTr_TlrId    txn_jnl.data[14] 
#define PubTr_CntrId   txn_jnl.data[15] 
#define PubTr_NodTrc   txn_jnl.data[16] 
#define PubTr_TxnCnl   txn_jnl.data[17] 
#define PubTr_ItgTyp   txn_jnl.data[18] 
#define PubTr_FTxnTm   txn_jnl.data[19] 
#define PubTr_FRspCd   txn_jnl.data[20] 
#define PubTr_HLogNo   txn_jnl.data[21] 
#define PubTr_HRspCd   txn_jnl.data[22] 
#define PubTr_HTxnSt   txn_jnl.data[23] 
#define PubTr_HPrChk   txn_jnl.data[24] 
#define PubTr_HLsChk   txn_jnl.data[25] 
#define PubTr_TCusId   txn_jnl.data[26] 
#define PubTr_TCusNm   txn_jnl.data[27] 
#define PubTr_TActDt   txn_jnl.data[28] 
#define PubTr_TLogNo   txn_jnl.data[29] 
#define PubTr_TRspCd   txn_jnl.data[30] 
#define PubTr_TTxnSt   txn_jnl.data[31] 
#define PubTr_ThdChk   txn_jnl.data[32] 
#define PubTr_TxnSts   txn_jnl.data[33]
#define PubTr_TxnAtr   txn_jnl.data[34]
#define PubTr_MstChk   txn_jnl.data[35]
#define PubTr_LChkTm   txn_jnl.data[36]

#endif /* _PUB_DEF_H */

