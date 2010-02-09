/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: pub_msg1.h
 Author			: peng_wh
 Version		: 1.0.0
 Date			: 2003.04.07
 Description	: ����ͳһ�涨��ǰ��ҵ��ƽ̨ʹ�õķ����룬ʹ�÷�Χ�Ǵ�ǰ���ڲ�
				  
 Others			: 
 History		: 
				  ���ݼ���

  No.	Date		Author		Modification
  ===	==========	========	==============================================

******************************************************************************/

#define		_SUCCEED               "000000"		/*  �ɹ�					*/
		    	                       		   		            	          
#define		_INVA_LOGON            "101400"		/*  ע�᷽ʽ��Ч			*/
#define		_INVA_LOGOUT           "101401"		/*  ע����ʽ��Ч			*/
#define		_FULL_LOGTAB           "101402"		/*  ע�����				*/
#define		_PROC_ALRE_LOGON       "101403"		/*  ͬһ������ע��			*/
#define		_APP_ALRE_LOGON        "101404"		/*  ͬһӦ�ñ�ʶ��ע��		*/
#define		_PROC_APP_CLASH        "101405"		/*  ���̺�Ӧ�ñ�ʶ��ͻ		*/
#define		_NOT_FOUND_APP         "101406"		/*  δ�ҵ�ע��Ӧ��			*/
#define		_INVA_SOUR_LOGON       "101407"		/*  ԴӦ��δ��Чע��		*/
#define		_INVA_TRAG_LOGON       "101408"		/*  Ŀ��Ӧ��δ��Чע��		*/
#define		_RE_START              "101409"		/*  ������������			*/
#define		_RE_START_ERR          "101410"		/*  ������������ʧ��		*/
#define		_LOST_INSIDE_DATA      "101411"		/*  �ڲ����ݶ�ʧ			*/
#define		_GRAV_PROC_ERR         "101412"		/*  ���س������			*/
#define		_START_APP_ERR         "101415"		/*  �ⲿ��������ʧ��    	*/
#define		_SYS_EXIT              "101416"		/*  ϵͳ�˳�            	*/
#define		_TOO_MANY_APP          "101417"		/*  Ӧ�ý���̫��			*/
#define		_INVA_APP              "101418"		/*  ��ЧӦ�ñ�ʶ			*/
#define		_APP_CHAN_ERR          "101419"		/*  Ӧ�ñ�ʶת������		*/
#define		_TOO_MANY_ROU          "101420"		/*  ·�ɱ�����̫��      	*/
#define		_INEXIST_ROU_TAB       "101421"		/*  ·�ɱ�δ����        	*/
#define		_RE_START_PROC         "101422"		/*  ������������ 			*/
#define		_FOUND_DIE_PROC        "101424"		/*  ���ֽ����� 				*/
#define		_LOST_INS_DATA         "101425"		/*  �ڲ����ݶ�ʧ			*/
#define		_NOT_ENV_VARI          "101440"		/*  û�����û�������		*/
#define		_PARA_NO_ASCII         "101450"		/*  ������ASCI�ַ�			*/
#define		_PARA_LEN_ERR          "101451"		/*  �����ֽڳ��ȴ�			*/
#define		_PARA_NO_NUM           "101452"		/*  �����������ַ�			*/
#define		_GET_PARA_ERR          "101453"		/*  ������ȡ����			*/
                                              		                          

#define		_PROCESSING            "120001"		/*  ���ڴ�����				*/
#define		_ASK_AUTH              "120002"		/*  Ҫ����Ȩ				*/
#define		_ACCT_NULL             "120003"		/*  �ʺŲ���Ϊ��			*/
#define		_INVALID_ACCT          "120004"		/*  ��Ч�ʺ�				*/
#define		_FREEZE_ACCT           "120005"		/*  �ʺţ����ţ�����		*/
#define		_NAME_ACCT_UNCONF      "120006"		/*  �ʺţ����ţ���������	*/
#define		_ERR_TRAN_STAT         "120007"		/*  ����״̬��				*/
#define		_INVALID_CARD          "120008"		/*  ��Ч����				*/
#define		_INVALID_AMOUNT        "120009"		/*  ��Ч���				*/
#define		_VIP_TRAN              "120010"		/*  �������				*/
#define		_PASSWD_ERR            "120011"		/*  �ֿ��˻����Ա�����	*/
#define		_INVALID_TRAN          "120012"		/*  ��Ч����				*/
#define		_IRREGU_TRAN           "120013"		/*  �Ƿ�����				*/
#define		_PACK_ERR              "120014"		/*  ���ݰ���ʽ����			*/
#define		_INEXIST_ORA_RECORD    "120015"		/*  �޴�ԭ����				*/
#define		_NOT_ENOUGH_INTEG      "120020"		/*  ���ֲ���				*/
#define		_CLEAN_INTEG_ERR       "120021"		/*  �����������			*/
#define		_INVA_CARD_KIND        "120022"		/*  ���ִ�					*/
#define		_PRINT_CLASH           "120023"		/*  ��ӡ��ͻ				*/
#define		_DATA_ERR              "120024"		/*  ���ݸ�ʽ��				*/
#define		_REQU_STAT_ERR         "120026"		/*  ����״̬����			*/
#define		_INVA_SEQU             "120027"		/*  ��ˮ�ź����Ͳ���		*/
#define		_INVA_PAGE_REQU        "120028"		/*  ����ʶ���ҳ����		*/
#define		_INVA_PAGE_APPLY       "120029"		/*  ҳ�����������			*/
#define		_CREAT_PRETRACE_ERR    "120031"		/*  ����ǰ����ˮ�Ŵ�		*/
#define		_GET_PRETRACE_ERR      "120032"		/*  ȡǰ����ˮ�Ŵ�			*/
#define		_NOT_ISSUE_CARD        "120033"		/*  δ����					*/
#define		_INVA_PRINT_REQU       "120034"		/*  ��Ч�Ĵ�ӡ����			*/
#define		_INEXIST_AUTH_AMOUNT   "120036"		/*  ��Ч��Ȩ���			*/
#define		_ASK_PRINT             "120037"		/*  Ҫ���ȴ�ӡ���ʱ���		*/
#define		_ENTER_LOGNO_ERR       "120038"		/*  ¼����ˮ�Ŵ�			*/
#define		_VOUDATE_LIMIT         "120039"		/*  ƾ֤���ڲ��ܴ��ڵ���	*/
#define		_OUTBANK_ERR           "120040"		/*  ����кŻ򷢱��кŴ�	*/
#define		_INBANK_ERR            "120041"		/*  �����кŻ��ձ��кŴ�	*/
#define		_INEXIST_RECORD        "120042"		/*  �޴˽�����ϸ			*/
#define		_NOT_APPLY_SERV        "120043"		/*  δ�������				*/
#define		_REPEAT_PACK           "120044"		/*  �ر�					*/
#define		_INEXIST_HOST_RECORD   "120045"		/*  �����޽��׼�¼			*/
#define		_INVA_FIELD            "120046"		/*  ��Ϣ�д��ڲ��Ϸ�����	*/
#define		_NULL_FIELD_ERR        "120047"		/*  �涨�ǿյ���Ϊ��		*/
#define		_ERR_AMOUNT            "120048"		/*  ���׽��Ϸ�			*/
#define		_AMOUNT_LIMIT          "120049"		/*  ת�ʽ��׽��С�ڹ涨	*/
#define		_TRUST_DATE_ERR        "120050"		/*  ί�����ڲ���ȷ			*/
#define		_OUT_SAME_IN           "120051"		/*  ���������������ͬ		*/
#define		_BANKNO_ERR            "120052"		/*  �кŴ�					*/
#define		_REQU_AREA_ERR         "120053"		/*  ��ѯ��Χ����ȷ			*/
#define		_INVA_MSG_CONT         "120054"		/*  ��Ϣ�����������Ϣ����	*/
#define		_INEXIST_COLLATE       "120055"		/*  ������Ϣ������			*/
#define		_INVALID_MCHANT        "120056"		/*  ��Ч������̻���		*/
#define		_INVA_FUNCTYPE         "120057"		/*  ��Ч����(��Ϣ���ʹ�)	*/
#define		_NOT_OBLIGATE_PIN      "120058"		/*  ���д���δԤ������		*/
#define		_ACCT_NOT_SET          "120059"		/*  �ʻ�δ����				*/
#define		_ACCT_ALRE_SET         "120060"		/*  �ʻ��ѿ���				*/
#define		_CALL_ISSUE            "120061"		/*  ��ϵ������				*/
#define		_SPEC_CALL             "120062"		/*  �ر���ϵ				*/
#define		_INVA_DATE             "120063"		/*  ��Ч����				*/
#define		_INVA_FEE_KIND         "120064"		/*  ��Ч�����������		*/
#define		_INVA_OPER             "120065"		/*  ��Ч����Ա��			*/
#define		_CHECK_PIN_ERR         "120066"		/*  ��������У���			*/
#define		_REPA_STOCK_SEQU       "120067"		/*  �ظ���֤ȯ��ˮ��		*/
#define		_SHORTAG_STOCK_BALA    "120068"		/*  ȯ���ʻ�����		*/
#define		_STOCKACC_ERRSTAT      "120069"		/*  ȯ���ʻ�״̬��			*/
#define		_SEQU_ERR              "120070"		/*  ���в�����ˮ�Ŵ���		*/
#define		_CROSS_ACCT_CLOSE      "120071"		/*  ͨ��ͨ�ұ��ر�			*/
#define		_INVA_STOCK_ACCT       "120072"		/*  ȯ���ʻ�������			*/
#define		_PRINT_BANKBOOK        "120073"		/*  �뵽���в������		*/
#define		_AMOUNT_OVER_LIMIT     "120074"		/*  ���ʽ��׽���		*/
#define		_INVA_FUNC             "120080"		/*  �˽���δ��ͨ			*/
#define		_INEXIST_STOCK         "120081"		/*  �޴�ȯ��				*/
#define		_CHECK_PASSERR         "120082"		/*  �ʽ�����У���			*/
#define		_SHORTAG_BALAN         "120083"		/*  �ͻ��ʽ��ʻ�����	*/
#define		_OVER_SUMLIMIT         "120084"		/*  �ۼƽ���			*/
#define		_REPEAT_SEQU           "120085"		/*  �ظ���������ˮ��		*/
#define		_INEXIST_REVE_RECORD   "120086"		/*  ��������ˮ������		*/
#define		_ALREAD_REVE           "120087"		/*  ����ˮ�ѳ���			*/
#define		_UNCONFOR_REVETRAN     "120088"		/*  ������ˮ����			*/
#define		_BALA_REFU_REVE        "120089"		/*  ����,���������		*/
#define		_INVA_BANKNO           "120090"		/*  ��Ч���к�				*/
#define		_FUNDACC_ERRSTAT       "120091"		/*  �ʽ��ʻ�״̬��			*/
#define		_INEXIST_FUNDACC       "120092"		/*  �ʽ��ʻ�������			*/
#define		_ACCT_ALRE_CLOSED      "120093"		/*  ���ʻ�������			*/
#define		_NOT_BASED_PARA        "120094"		/*  ֤ȯ�����ж�Ӧ��ϵδ��	*/
#define		_BASED_PARA            "120095"		/*  ֤ȯ�����ж�Ӧ��ϵ�ѽ�	*/
#define		_DISALLOW_TRANSFER     "120096"		/*  �ÿͻ�ת�ʹ���δ����	*/
#define		_CLOSE_TRANSFER        "120097"		/*  �ÿͻ�ת�ʹ����ѹر�	*/
#define		_ASSET_OVER_LIMIT      "120098"		/*  �ÿͻ��ʲ���ֵ��������	*/
#define		_SERIAL_UNCON          "120099"		/*  ֤ȯ��˾��Ų���		*/
#define		_DISALLOW_FUNC         "120100"		/*  �˽���δ��ͨ			*/
#define		_STOCK_NO_SIGN         "120101"		/*  ֤ȯ��˾δǩ��			*/
#define		_STOCK_LOGOUT          "120102"		/*  ֤ȯ��˾��ǩ��			*/
#define		_NO_TRANSFER_FUNC      "120103"		/*  ת�ʹ���δ����			*/
#define		_STOCK_SERV_ERR        "120104"		/*  ֤ȯ��˾������ϵͳ����	*/
#define		_POSSIB_OPERERR        "120105"		/*  ���ɲ�����				*/
#define		_AGAIN_ENTRY           "120106"		/*  �����½���				*/
#define		_PART_HONOR            "120107"		/*  ���ֳж�				*/
#define		_REFUSE_BUSIN          "120108"		/*  �ܾ�����				*/
#define		_INFRACT_SECU          "120109"		/*  Υ����ȫ�涨			*/
#define		_NO_VOID_RECORD        "120110"		/*  ��������ˮ������		*/
#define		_ALRE_VOID             "120111"		/*  ��������ˮ�ѳ���		*/
#define		_UNCONFOR_TRAN         "120112"		/*  ��������ˮ����			*/
#define		_NO_RECORD             "120113"		/*  ����ѯ��ˮ������		*/
#define		_REFU_REVERSAL         "120114"		/*  �ܾ�����				*/
#define		_AVALID_TERMNO         "120115"		/*  ��Ч�ն�				*/
#define		_REFU_HONOR            "120116"		/*  ���ж�					*/
#define		_ERROR                 "120117"		/*  ���					*/
#define		_LABLE_HONOR           "120118"		/*  ��ʶ�ж�				*/
#define		_INQU_RESP             "120119"		/*  ��ѯ��Ӧ��				*/
#define		_PART_AUTH             "120120"		/*  ������׼				*/
#define		_LEAD_AUTH             "120121"		/*  �쵼��׼				*/
#define		_INVALID_ISSU          "120122"		/*  �޴˷�����				*/
#define		_UPDATE_TRACK3         "120123"		/*  ����3�ŵ�				*/
#define		_CLIENT_VOID           "120124"		/*  �ͻ�ȡ��				*/
#define		_CLIENT_DISPUTED       "120125"		/*  �ͻ�����ִ				*/
#define		_REPEAT_TRAN           "120126"		/*  �ظ�����				*/
#define		_AVALID_RET            "120127"		/*  ��Ч��Ӧ				*/
#define		_NO_ACTION             "120128"		/*  ����ȡ�ж�				*/
#define		_SUSP_FAIL             "120129"		/*  ���ϻ���				*/
#define		_ERR_FEE               "120130"		/*  �Ƿ����׷�				*/
#define		_REFU_UPDATE           "120131"		/*  ��֧�ָ���				*/
#define		_REPEAT_UPDATE         "120132"		/*  �ظ�����				*/
#define		_UPDATE_FIELD_ERR      "120133"		/*  �����ֶδ�				*/
#define		_TARNSACT              "120134"		/*  ���ڴ���				*/
#define		_UPDATE_ERR            "120135"		/*  ����ʧ��				*/
#define		_NOJOIN_BANK           "120136"		/*  δ��������				*/
#define		_PARTIAL               "120137"		/*  �������				*/
#define		_OVER_EXPIRE           "120138"		/*  ����,û��				*/
#define		_CHEAT_CARD            "120139"		/*  ���,û��				*/
#define		_CALL_BANK             "120140"		/*  ��ϵ,û��				*/
#define		_LIMIT_CARD            "120141"		/*  ����,û��				*/
#define		_PICKUP_CARD           "120142"		/*  ��ʧ,û��				*/
#define		_LOCK_RECORD           "120143"		/*  ��¼����				*/
#define		_ERR_ACCOUNT           "120144"		/*  �޴����ʻ�				*/
#define		_LOSE_CARD             "120145"		/*  ��ʧ��û��				*/
#define		_ERR_CURR_ACC          "120146"		/*  ��ͨ���ʻ�				*/
#define		_ERR_INVEST_ACC        "120147"		/*  ��Ͷ���ʻ�				*/
#define		_LACK_BALANCE          "120148"		/*  �ʽ���				*/
#define		_ERR_CHEQUE_ACC        "120149"		/*  ��֧Ʊ�ʻ�				*/
#define		_ERR_SAVING_ACC        "120150"		/*  �޴����ʻ�				*/
#define		_OVER_EXPI_CARD        "120151"		/*  ���ڿ�					*/
#define		_PIN_ERR               "120152"		/*  ���������				*/
#define		_NO_CARD_RECORD        "120153"		/*  �޿���¼				*/
#define		_DISALLOW_TRAN         "120154"		/*  ��������				*/
#define		_DISALLOW_DEAL         "120155"		/*  ��������				*/
#define		_POSSIB_CHEAT          "120156"		/*  �������				*/
#define		_CALL_SUPPLY           "120157"		/*  ��ϵ����				*/
#define		_OVER_DRAW             "120158"		/*  ������޶�				*/
#define		_OVER_FEE              "120159"		/*  ���ó����޶�			*/
#define		_IMP_SECU              "120160"		/*  �ַ���ȫ				*/
#define		_ORI_AMOUNT_ERR        "120161"		/*  ԭʼ����				*/
#define		_OVER_TIMES            "120162"		/*  ��������				*/
#define		_CALL_SECU             "120163"		/*  ֪ͨ����				*/
#define		_SEIZURE_CARD          "120164"		/*  �����̿�				*/
#define		_BELATE_ANSW           "120165"		/*  ��Ӧ��ʱ				*/
#define		_OVER_PIN_TIMES        "120166"		/*  �������				*/
#define		_END_PROC              "120167"		/*  ����������				*/
#define		_NOT_FOUND_NET         "120168"		/*  �Ҳ�������				*/
#define		_REPT_ENTRY            "120169"		/*  �ظ�����				*/
#define		_ID_ERR                "120170"		/*  ֤����					*/
#define		_MCHANT_NO_HONOR       "120171"		/*  �̻�δ�ж�				*/
#define		_NO_HONOR_ORIG         "120172"		/*  ԭ����δ�ж�			*/
#define		_ASK_FAILURE           "120173"		/*  ��������ʧ��			*/
#define		_ISSU_FAILURE          "120174"		/*  ����������				*/
#define		_REPEAT_ANSWER         "120175"		/*  �ظ�Ӧ��				*/
#define		_NO_CENTER_ANSWER      "120176"		/*  ������Ӧ��				*/
#define		_NO_ISSU_ANSWER        "120177"		/*  ��������Ӧ��			*/
#define		_ACQU_TIMEOUT          "120178"		/*  ������ʱӦ��			*/
#define		_ACQU_FAILURE          "120179"		/*  ��������				*/
#define		_COUNT_ERR             "120180"		/*  ��������				*/
#define		_ORIG_CHANGE           "120181"		/*  ԭ���׸ı�				*/
#define		_BOOKIN_LIMIT_ERR      "120182"		/*  ��������				*/
#define		_NO_OBTAIN             "120183"		/*  �޷�����				*/
#define		_DONOT_OPER            "120184"		/*  �޷�����				*/
#define		_CHANGE_DATE           "120185"		/*  �����л�				*/
#define		_END_REQU              "120186"		/*  ��ѯ������־			*/
#define		_HOST_TRACE_NULL       "120187"		/*  ������ˮ��Ϊ��      	*/
#define		_ABSENT_FIT_CARD       "120188"		/*  FIT�����޴˿�       	*/
#define		_CASHBOX_STAT_ERR      "120189"		/*  ����״̬����        	*/
#define		_REVE_ERR              "120190"		/*  �������׷����쳣    	*/
#define		_INVA_MSG              "120191"		/*  �������ݷǷ�			*/
#define		_FOUND_TIMEOUT         "120192"		/*  ���ֽ��׳�ʱ			*/
#define		_TOO_MANY_REVE         "120193"		/*  ��������̫��			*/
#define		_INVA_TIME             "120194"		/*  ʱ��Ƿ�				*/
#define		_TOO_LARGE_VALUE       "120195"		/*  ��ֵ̫�� 				*/
#define		_INVA_REVE_MAKE        "120196"		/*  �������ı�ʶ����𲻷�	*/
#define		_INVA_SIGN             "120197"		/*  ���ִ��������Ŵ���		*/
#define		_INVA_OFFSET           "120200"		/*  ��ЧBitMap����ƫ����	*/
#define		_BM_OPEN_ERR           "120201"		/*  BitMap�����ļ���		*/
#define		_BM_FILE_ERR           "120202"		/*  BitMap�����ļ���ʽ		*/
#define		_8583_DATA_LEN         "120203"		/*  8583���ݳ���			*/
#define		_8583_HEAD_ERR         "120204"		/*  8583�ṹ���� 			*/
#define		_INVA_BUSS_TYPE        "120300"		/*  ҵ�����Ͳ����� 			*/
#define		_INVA_UNIT_CODE        "120301"		/*  ��λ���벻���� 			*/
#define		_INVA_TRAN_TYPE        "120302"		/*  ��������޶��� 			*/
#define		_INQU_RECV_FAIL        "120303"		/*  ���ս�������ʧ��		*/
#define		_INQU_LEN_ERR          "120304"		/*  �����������ݰ����ȳ��� 	*/
#define		_INQU_FORM_ERR         "120305"		/*  �����������ݰ���ʽ���� 	*/
#define		_SEND_RETU_FAIL        "120306"		/*  ���ͽ��׽��ʧ�� 		*/
#define		_DATA_OVER_RANGE       "120307"		/*  ���ݳ�����Χ	 		*/
#define		_GET_ACDAT_ERR	       "120308"		/*  ��ȡ������ڴ��� 		*/
#define		_GET_SYSDAT_ERR	       "120309"		/*  ��ȡϵͳ���ڴ��� 		*/
#define		_BAT_STATUS_ERR	       "120310"		/*  ������״̬����	 		*/
#define		_BAT_PROC_NOW	       "120311"		/*  �������ڴ�����	 		*/
#define		_ELE_NOT_ENOUGH	       "120312"		/*  ����Ҫ�ز�ȫ	 		*/
#define		_AUTH_CHECK_ERR	       "120313"		/*  ��Ȩ����		 		*/
#define		_REPLY_NODE_ERR	       "120314"		/*  ���ɻظ��Ǳ�������Ϣ	*/
#define		_REPLY_ALRE_ERR	       "120315"		/*  �ѻظ�					*/
#define		_CANCEL_ALRE_ERR	   "120316"		/*  ��ȡ��					*/
#define		_ALRE_PUR_ERR	   	   "120317"		/*  �Ѿ��и�Ӧ�÷�����Ȩ��  */
#define		_NO_PUR_ERR	   		   "120318"		/*  �����ڸ�Ӧ�÷�����Ȩ��  */
#define		_ALRE_ORG_PUR	   	   "120319"		/*  ���иû�����Ȩ�޼�¼  */
#define		_ALRE_TLR_PUR	   	   "120320"		/*  ���иù�Ա��Ȩ�޼�¼  */
#define		_ALRE_TXN_AUTH	   	   "120321"		/*  ���иý��׵Ľ����Ȩ��Ϣ*/
#define		_NO_TXN_AUTH	   	   "120322"		/*  û�иý��׵Ľ����Ȩ��Ϣ*/
#define		_REPLY_NO_ERR	       "120323"		/*  δ�ظ�					*/
#define		_RETU_NO_ERR	       "120324"		/*  ��δ�յ���ִ			*/
#define		_INACCT_SQN_ERR	       "120325"		/*  ���ʰ��Ŵ�  			*/
#define		_WAIT_PROC_NOW	       "120326"		/*  ��δ���������ڴ������Ժ�*/

#define		_RCV_RTCBK_ERR	       "120400"		/*  �����кŴ�              */
#define		_RCV_BANK_ERR	       "120401"		/*  �����кŴ�              */
#define		_RCV_SETTBK_ERR	       "120402"		/*  ���������кŴ�          */
#define		_RPC_CODE_ERR	       "120403"		/*  �ձ����Ĵ����          */
#define		_NO_CTL_NODE	       "120404"		/*  ��ͨ���������          */
#define		_SYS_STAT_ERR1	       "120405"		/*  ֻ�����ռ估����״̬����*/
#define		_SYS_STAT_ERR2	       "120406"		/*  ֻ�������㡢�ռ估����״̬*/
#define		_AMT_LESS_LIMIT	       "120407"		/*  ���С�ڴ�����ƽ��,��Ҫ�Ӽ� */
#define		_SND_NM_EMPTY	       "120408"		/*  ������������            */
#define		_RCV_NM_EMPTY	       "120409"		/*  ������������            */
#define		_SUMMARY_EMPTY	       "120410"		/*  ժҪ����                */
#define		_BUS_UNEXHAUST	       "120411"		/*  ��δ����ҵ��            */
#define		_NO_RTC_NODE	       "120412"		/*  ��ͨ������          	*/
#define		_LOG_NO_ERR	       	   "120413"		/*  ��ˮ�Ŵ�          		*/
#define		_TRACE_NO_ERR	       "120414"		/*  ��Ʊ�Ŵ�          		*/
#define		_TRAN_NODE_ERR	       "120415"		/*  �Ǳ���������       		*/
#define		_ALLOW_FUND_REMIT	   "120416"		/*  ��ҵ����������ʽ�㻮	*/
#define		_SBK_EQUAL_RBK		   "120417"		/*  �����в������ձ�����ͬ	*/
#define		_STCBK_EQUAL_RTCBK	   "120418"		/*  ����в������������ͬ	*/
#define		_NODE_INFO_ERR	   	   "120419"		/*  �����Ӧ�к���������	*/
#define		_UNGRAT_PRINT_CONDI	   "120420"		/*  �в������ӡ�����ļ�¼	*/
#define		_DATE_ERR              "120421"		/*  ¼�����ڻ�ƾ֤���ڴ�	*/
#define		_SND_RTCBK_ERR	       "120422"		/*  ����кŴ�              */
#define		_SND_OBANK_ERR	       "120423"		/*  ������кŴ�          */
#define		_FEE_TYPE_ERR	       "120424"		/*  �շ�ѡ���뱨�����ȼ�����*/
                                               		                          
#define		_PRE_ERR_CODE          "120900"		/*  ǰ��Ԥ�ô�����			*/
#define		_NO_EXPECT_MSG         "120901"		/*  �յ�����Ϣ����Ԥ��		*/
#define		_NEED_ONLY_CONFIG      "120902"		/*  ����������Ψһ			*/
#define		_QUERY_END             "120903"		/*  ��ѯ����				*/
                                              		                          
#define		_MSG_FMTNAME_ERR       "120905"		/*  ��Ϣ��ʽ���ƴ���		*/
#define		_MSG_LABEL_ERR         "120906"		/*  ��Ϣ�Ի���ʶ����		*/
#define		_MSG_SEQU_ERR          "120907"		/*  ��Ϣ˳��Ŵ���			*/
#define		_INVA_ORAMSG_SEQU      "120908"		/*  ԭ��Ϣ˳��Ų��Ϸ�		*/
#define		_INVA_MSG_SEQU         "120909"		/*  ��Ϣ˳��Ų��Ϸ�		*/
#define		_FIELD_NUM_ERR         "120910"		/*  ��Ϣ�а�������Ŀ��		*/
#define		_FIELD_LEN_ERR         "120911"		/*  ��Ϣʵ�ʳ��Ȳ���		*/
#define		_MAX_FIELD_SEQU        "120913"		/*  �Ѵ������Ϣ���к�		*/
#define		_OVER_ERR_NUM          "120914"		/*  �������������			*/
#define		_INVA_VOID_MSG         "120915"		/*  Ҫ��������Ϣ��֧����Ϣ	*/
#define		_WAIT_TIME_OUT         "120916"		/*  �ȴ�ʱ�����			*/
                                              		                          
#define		_DB_OPER_ERR           "131000"		/*  ���ݿ��������			*/
#define		_DB_FEAR_ERR           "131001"		/*  ���ݿ�������			*/
#define		_DB_CONN_ERR           "131002"		/*  �������ݿ�ʧ��			*/
#define		_DB_INIT_ERR           "131003"		/*  ��ʼ�����ݿ��豸��		*/
#define		_DB_LOGIN_ERR          "131004"		/*  ��¼���ݿ�ʧ��			*/
#define		_DB_OPEN_ERR           "131005"		/*  ���û����ݿ�ʧ��		*/
#define		_DB_EXEC_ERR           "131006"		/*  ִ�����ݿ��������	*/
#define		_DB_RESULT_ERR         "131007"		/*  �������ݿ�ִ�н����	*/
#define		_DB_INS_ERR            "131008"		/*  ��¼����ʧ�� 			*/
#define		_DB_PROC_ERR           "131009"		/*  �洢���̳���			*/
#define		_DB_REPT_REC           "131010"		/*  �ظ��Ĳ����¼ 			*/
#define		_DB_UPDATE_ERR         "131011"		/*  ���¼�¼ʧ��			*/
#define		_DB_NO_RECORD          "131012"		/*  ���ݿ��޶�Ӧ��¼		*/
#define		_DB_QUERY_ERR          "131013"		/*  ���ݿ��ѯʧ��			*/
                                              		                          
#define		_SYS_BUSY_DELAY        "141200"		/*  ��ϵͳ��æ���ӳ�		*/
#define		_INSIDE_PROBLEM        "141201"		/*  ���ڲ����ⲻ����ɴ���	*/
#define		_PIGEONHOLE_MSG        "141202"		/*  ��Ϣ��ϸ��¼�ѱ��鵵	*/
#define		_SYS_BUSY_REFU         "141203"		/*  ���ϵͳ��æ���ױ��ܾ�	*/
#define		_ABSE_LOGON_HOST       "141204"		/*  ��δ��¼����			*/
#define		_ABSE_LOGON_APP        "141205"		/*  ��δ��¼Ӧ��ϵͳ		*/
#define		_REFU_ACCE             "141206"		/*  ��ǰ�������ڲ�������Ϣ	*/
#define		_ID_PASS_ERR           "141207"		/*  �û���ʶ������ȷ	*/
#define		_ALRE_LOGON            "141208"		/*  �ѵ�¼					*/
#define		_ALRE_LOGOUT           "141209"		/*  ���˳�					*/
#define		_PASS_EXPIRE           "141210"		/*  ������Чʹ�������ѹ�	*/
#define		_LOGON_SEQU_ERR        "141211"		/*  ��¼˳�����			*/
#define		_DISALLOW_LOGON        "141212"		/*  �������¼				*/ 
#define		_LOGON_TYPE_ERR        "141213"		/*  ��¼���ʹ���			*/
#define		_INVA_USEID            "141214"		/*  �Ƿ��û���ʶ���¼����	*/
#define		_PRE_ABSE_LOGON        "141215"		/*  ǰ�û�δǩ��			*/
#define		_SYS_CUT_OFF           "141218"		/*  ϵͳ��ֹ				*/
#define		_START_TIME_LIMIT      "141219"		/*  ��ʼʱ����ڽ���ʱ��	*/
#define		_NODE_NO_CLOSE         "141220"		/*  ����δ�ر�				*/
#define		_SYS_NO_CLOSE          "141221"		/*  ϵͳδ�ر�				*/
#define		_PMS_NO_CLOSE          "141222"		/*  ֧��ϵͳ״̬δ�ر�		*/
                                              		                          
#define		_FILE_OPEN_ERR         "141500"		/*  ���ļ���				*/
#define		_FILE_INEX_CONF        "141501"		/*  �������ļ�				*/
#define		_FILE_ERR_UPDA         "141502"		/*  �ļ����´�				*/
#define		_FILE_ERR_FIELD        "141503"		/*  �ļ��������			*/
#define		_FILE_AGAIN_UPDA       "141504"		/*  �ظ��ļ�����			*/
#define		_FILE_NO_RECORD        "141505"		/*  ���ļ���¼				*/
#define		_FILE_REFU_UPDA        "141506"		/*  �ܾ��ļ�����			*/
#define		_FILE_LOCK             "141507"		/*  �ļ�����				*/
#define		_FILE_NAME_NULL        "141508"		/*  ǰ�������ļ�������Ϊ��	*/
#define		_FILE_INEXIST          "141509"		/*  ǰ���޴��ļ�,�������ϴ�	*/
#define		_FILE_REPEAT           "141510"		/*  ���ϴ��ļ�,�����ظ��ϴ�	*/
#define		_FILE_INVA_FORM        "141511"		/*  �ϴ��ļ��޶�Ӧ��ʽ����	*/
#define		_FILE_PARSE_ERR        "141512"		/*  ǰ���ϴ��ļ�����ʧ��	*/
#define		_FILE_SUCC_RETU        "141513"		/*  �ļ������������ɻ����ļ�*/
#define		_FILE_SERIAL_FAIL      "141514"		/*  �������������ļ����ʧ��*/
#define		_FILE_PARSE_FAIL       "141515"		/*  �ļ�����ʧ��			*/
#define		_FILE_CREAT_FAIL       "141516"		/*  �ļ�����ʧ��			*/
#define		_FILE_INEXI_FRETU      "141517"		/*  ǰ�û����ļ�δ����		*/
#define		_FILE_INEXI_HRETU      "141518"		/*  ���������ļ�δ����		*/
#define		_FILE_SUM_FINQ         "141519"		/*  ǰ���ϴ��ļ��ܽ���	*/
#define		_FILE_COUNT_FINQ       "141520"		/*  ǰ���ϴ��ļ��ܱ�������	*/
#define		_FILE_SUM_HRETU        "141521"		/*  ���������ļ��ܽ���	*/
#define		_FILE_COUNT_HRETU      "141522"		/*  ���������ļ��ܱ�������	*/
#define		_FILE_ERR_HRETU        "141523"		/*  ���������ļ�����		*/
#define		_FILE_PARSE_HRETU      "141524"		/*  ���������ļ�����ʧ��	*/
#define		_FILE_AMT_ERR          "141525"		/*  ��ǰ�ļ�����		*/
#define		_FILE_SEQU_ERR         "141526"		/*  ��ǰ�ļ�˳��Ų���		*/
#define		_FILE_SUCC_REPEAT      "141527"		/*  �ļ��Ѵ���ɹ�,�������ٴ���	*/
#define		_FILE_PROC_REPEAT      "141528"		/*  �ļ����ղ������ٴδ���	*/
#define		_FILE_ALRE_AFFIRM      "141529"		/*  ������ȷ��,�����ظ�����	*/
#define		_FILE_ACTDAT_ERR       "141530"		/*  �ļ����ܼ�¼���ļ������ڲ���*/
#define		_FILE_NO_DATA          "141531"		/*  ���������ݣ������ļ�ʧ��*/
                                              		                          
#define		_BRAN_INEXIST          "141600"		/*  ����Ų����ڻ��������ô�*/
#define		_BRAN_NET_ERR          "141601"		/*  ����վ���				*/
#define		_BRAN_AREA_ERR         "141602"		/*  �Ǳ�֧������			*/
#define		_BRAN_AUTH_CON         "141603"		/*  �޸�������Ȩ����		*/
#define		_OPER_LEVEL_LIMIT      "141650"		/*  ��Ա���𲻹�			*/
#define		_OPER_ERR              "141651"		/*  ���׹�Ա��				*/
#define		_OPER_INEXIST          "141652"		/*  �޴˹�Ա				*/
#define		_OPER_NEED_DIFF        "141653"		/*  ��Ҫ��ͬ��Ա			*/
#define		_OPER_PUR_ERR          "141654"		/*  ��Ա�޴�Ȩ��			*/
#define		_OPER_ORA_ERR          "141655"		/*  ��ԭ���׹�Ա			*/
#define		_OPER_PASS_ERR         "141656"		/*  ��Ա�����				*/
                                              		                          
#define		_HOST_TIMEOUT          "141702"		/*  ������ʱ				*/
#define		_NET_ERR               "141703"		/*  �������				*/
#define		_NEED_REQU             "141704"		/*  ���ѯ�ϱʽ����Ƿ�ɹ�	*/
#define		_BANK_OTHER_ERR        "141705"		/*  ���з�����������		*/
#define		_SEND_HOST_ERR         "141707"		/*  ��������ʧ��			*/
#define		_PRE_OTHER_ERR         "141708"		/*  ǰ�û���������			*/
#define		_COMM_TIMEOUT          "141795"		/*  ͨѶ��ʱ				*/
#define		_SYSTEM_ERR            "141796"		/*  ϵͳ����				*/
#define		_ERR_CORTROL           "141797"		/*  ���ƴ�					*/
#define		_NET_VER_ERR           "141798"		/*  ����汾������			*/
                                              		                          
#define		_QPAIR_OPER_ERR        "111800"		/*  QPAIR����ʧ��       	*/
#define		_INVA_COMM_MODE        "111801"		/*  ��֧�ֵ�ͨѶ��ʽ		*/
#define		_CREAT_MSG_FAIL        "111803"		/*  MSG��������ʧ��     	*/
#define		_SAVE_MSGH_FAIL        "111804"		/*  MSG����ͷ����ʧ��   	*/
#define		_SEND_ERR_FAIL         "111805"		/*  Ӧ�ô�����Ϣ����ʧ��	*/
#define		_XML_OPER_ERR          "111806"		/*  XML��������      		*/
#define		_HICALL_TIMEOUT        "111807"		/*  HICALL���ó�ʱ   		*/
#define		_HICALL_FAIL           "111808"		/*  HICALL����ʧ��   		*/
#define		_GET_ENV_FAIL          "111809"		/*  ȡ�û�������ʧ��    	*/
#define		_MALLOC_ERR            "111810"		/*  �ڴ�������			*/
#define		_INVALID_LEN           "111811"		/*  ͨѶ��Ϣ�ĳ������		*/
#define		_READ_TIMEOUT          "111812"		/*  ͨѶ����Ϣ����ʱ		*/
#define		_FINGER_NULL           "111813"		/*  ��Ϣָ��Ϊ��			*/
#define		_OPER_MSG_ERR          "111814"		/*  ��Ϣ����ʧ��			*/
#define		_CLONE_MSG_ERR         "111815"		/*  �޷�������Ϣ			*/
#define		_DLL_OPER_ERR          "111816"		/*  ��̬�����ʧ��   		*/
#define		_APP_RET_ERR           "111817"		/*  Ӧ�÷��س���     		*/
#define		_MUTEX_OPER_ERR        "111818"		/*  �߳�������ʧ��   		*/
#define		_MODE_ERR              "111819"		/*  ���ͻ����ģʽ����		*/
#define		_SET_PIPE_ERR          "111820"		/*  �����ܵ�ʧ��        	*/
#define		_READ_PIPE_ERR         "111821"		/*  ���ܵ���ʧ�� 			*/
#define		_MSG_INIT_ERR          "111830"		/*  ��Ϣ���г�ʼ������		*/
#define		_MSG_PUR_ERR           "111831"		/*  ��Ϣ����Ȩ�޴���		*/
#define		_MSG_EXIST             "111832"		/*  ��Ϣ�����Ѵ���			*/
#define		_MSG_INEXIST           "111833"		/*  ��Ϣ���в�����			*/
#define		_MSG_OPER_ERR          "111834"		/*  ��Ϣ���в�������		*/
#define		_MSG_INVA_ID           "111835"		/*  ��Ϣ���б�ʶ����		*/
#define		_MSG_FULL              "111836"		/*  ��Ϣ������Ϣ����    	*/
#define		_MSG_GET_ERR           "111837"		/*  ��Ϣ����ȡ�ô���    	*/
#define		_MSG_SEND_ERR          "111838"		/*  ��Ϣ���з��ʹ���    	*/
#define		_MSG_RECV_ERR          "111839"		/*  ��Ϣ���н��մ���		*/
#define		_SHM_INIT_ERR          "111850"		/*  �����ڴ��ʼ������		*/
#define		_SHM_PUR_ERR           "111851"		/*  �����ڴ�Ȩ�޴���		*/
#define		_SHM_EXT_ERR           "111852"		/*  �����ڴ��Ѵ���			*/
#define		_SHM_SIZE_ERR          "111853"		/*  �����ڴ泤�ȴ���		*/
#define		_SHM_NOEXT             "111854"		/*  �����ڴ治����			*/
#define		_SHM_NOMEM             "111855"		/*  �����ڴ�ռ䲻��		*/
#define		_SHM_OPER_ERR          "111856"		/*  �����ڴ�������� 		*/
#define		_SHM_GET_ERR           "111857"		/*  �����ڴ�ȡ�ô���		*/
#define		_SEM_INIT_ERR          "111870"		/*  ��ʼ���źŵƴ� 			*/
#define		_SEM_GET_ERR           "111871"		/*  �źŵ�ȡ�ô���			*/
#define		_SEM_P_ERR             "111872"		/*  �źŵ� P ����ʧ�� 		*/
#define		_SEM_V_ERR             "111873"		/*  �źŵ� V ����ʧ��		*/
#define		_SEM_RM_ERR            "111874"		/*  ɾ���ź�ʧ��			*/
#define		_IP_ADDR_ERR           "111880"		/*  IP��ַ����				*/
#define		_IP_INVA_ADDR          "111881"		/*  IP��ַδ�Ǽ�			*/
#define		_IP_REPE_ADDR          "111882"		/*  IP��ַ�ظ�				*/
#define		_NET_TIME_OUT          "111883"		/*  ���糬ʱ����			*/
#define		_NET_ACCE_RET          "111884"		/*  ����Ӧ�����ʧ��		*/
#define		_NET_INVA_HAND         "111885"		/*  ��������Э����Ч		*/
#define		_NET_INVA_TRSP         "111886"		/*  ���紫��Э����Ч		*/
#define		_SOCK_OPEN_ERR         "111890"		/*  �׽��ִ򿪴���			*/
#define		_SOCK_READ_ERR         "111891"		/*  �׽��ֶ�����			*/
#define		_SOCK_WRIT_ERR         "111892"		/*  �׽���д����			*/
#define		_SOCK_CONN_ERR         "111893"		/*  �׽���connect����		*/
#define		_SOCK_BIND_ERR         "111894"		/*  �׽���bind����			*/
#define		_SOCK_ACCE_ERR         "111895"		/*  �׽���accept����		*/
#define		_SOCK_OPER_ERR         "111896"		/*  �׽��ֲ�������			*/
#define		_NODE_OPER_ERR         "111910"		/*  �ڵ��������			*/
#define		_NODE_GET_ERR          "111911"		/*  ȡ���ݽڵ��			*/
#define		_NODE_ROOT_NULL        "111912"		/*  ���ڵ�Ϊ��				*/
#define		_SYNC_OUT_FAIL         "111930"		/*  ���ͬ��ʧ��			*/
#define		_SYNC_CYCLE            "111931"		/*  ����ͬ������			*/
#define		_SYNC_NEED_SEND        "111932"		/*  ��Ҫͬ������			*/
#define		_SYNC_NOT_SIGN         "111933"		/*  ��ͬ���Ի���־			*/
#define		_SYNC_NOT_SEQU         "111934"		/*  ��ͬ����Ϣ˳���		*/
#define		_CSER_INIT_FAIL        "111950"		/*  CommunicationServer��ʼ��ʧ��*/
#define		_APPC_SESS_FAIL        "111951"		/*  ���� APPC SESSION ʧ��	*/
#define		_SNA_SEND_FAIL         "111952"		/*  SNA ͨ������ʧ��		*/
#define		_SNA_RECV_FAIL         "111953"		/*  SNA ͨ�Ž���ʧ��		*/
#define		_SNA_TIME_OUT          "111954"		/*  SNA ͨ�Ž���ͨ�ų�ʱ	*/
#define		_SNA_CONFIRM_FAIL      "111955"		/*  SNA ͨ��ȷ��ʧ��		*/
#define		_SNA_INIT_ERR	       "111956"		/*  SNA��ʼ������			*/
#define		_SNA_ALLOCATE_FAIL     "111957"		/*  SNA����SESSIONʧ��		*/
#define		_SNA_FREE_FAIL 	       "111958"		/*  ��������ABEND�����ͷ�SESSIONʧ��	*/
#define		_SNA_FINDLU_ERR 	   "111959"		/*  SNA����LUʧ��			*/
#define		_ETF_GET_ERR	       "111970"		/*  ��ȡETF�ڵ����			*/
                                              		                          
#define		_MAC_ERR               "152000"		/*  MAC����					*/
#define		_DECRY_ERR             "152001"		/*  ���ܴ���				*/
#define		_ENCRY_CHECK_ERR       "152002"		/*  ����У���ִ�			*/
#define		_AUTH_CODE_ERR         "152003"		/*  ��������֤���			*/
#define		_PAY_CODE_ERR          "152004"		/*  ֧�����				*/
#define		_CODESEAL_ERR          "152005"		/*  ����ӡ����				*/
#define		_CHECKSUM_ERR          "152006"		/*  Checksum����ȷ			*/
#define		_KEY_UPDATE_ERR        "152007"		/*  ��Կ���³ɹ�			*/
#define		_KEY_UPDATE_FAIL       "152008"		/*  ��Կ����ʧ��			*/
#define		_SYS_UPDATE_KEY        "152009"		/*  ϵͳ����������Կ		*/
#define		_OUT_UPDATE_KEY        "152010"		/*  �ⲿҪ��������Կ		*/
#define		_KEY_ERR               "152011"		/*  ��Կ����				*/
#define		_NEED_INIT_KEY         "152012"		/*  û�г�װ��Կ			*/
#define		_PIN_FAILURE           "152013"		/*  PIN��ʽ��				*/
#define		_CENTER_SECU_ERR       "152014"		/*  ���ı��ܴ�				*/
#define		_ENMACH_STAT_ERR       "152015"		/*  ���ܻ�״̬����      	*/
                                              		                          
#define		_IN_LEDGER_UNCONF      "163000"		/*  ����(��)����			*/
#define		_OUT_LEDGER_UNCONF     "163001"		/*  ����(��)����			*/
#define		_SUM_LEDGER_UNCONF     "163002"		/*  ������ͳ�ƶ���			*/
#define		_INEXIST_LEDGER_LIST   "163003"		/*  ������ϸδ����			*/
#define		_SUM_AMOUNT_UNCONF     "163004"		/*  �ܽ���				*/
#define		_SUM_COUNT_UNCONF      "163005"		/*  �ܱ�������				*/
#define		_DEBIT_CNT_ERR         "163006"		/*  ��Ǳ�������			*/
#define		_CREDIT_CNT_ERR        "163007"		/*  ���Ǳ�������			*/
#define		_DEBIT_AMT_ERR         "163008"		/*  ��ǽ���			*/
#define		_CREDIT_AMT_ERR        "163009"		/*  ���ǽ���			*/
#define		_CAN_NOT_SETT          "163010"		/*  �˶Բ�����������		*/
#define		_TODAY_ALRE_SETT       "163011"		/*  ����������				*/
#define		_INVA_SETT_DATE        "163012"		/*  ������������			*/
#define		_BUSS_NOT_SETT         "163013"		/*  ҵ��δ��ɲ�������		*/
#define		_PMS_NOT_SETT          "163014"		/*  ����֧��ϵͳδ����		*/
                                             		                          
#define		_AUTH_CLOSE_CHECK      "FA0001"		/*  ���ż��Ҫ����Ȩ		*/
#define		_AUTH_VOID		       "FA0002"		/*  Ĩ�˽���Ҫ����Ȩ		*/
#define		_AUTH_TABLE_MAIN       "FA0003"		/*  ����ά��Ҫ����Ȩ		*/
#define		_AUTH_TEMP_ACCT        "FA0004"		/*  ����Ҫ����Ȩ			*/
#define		_AUTH_PRINT_AGAIN      "FA0005"		/*  �ظ���ӡҪ����Ȩ		*/
#define		_AUTH_HAND_FEE		   "FA0006"		/*  �������ֹ�����Ҫ����Ȩ	*/
#define		_AUTH_EXIGENCY_MSG     "FA0007"		/*  �Ӽ�����Ҫ����Ȩ		*/
#define		_AUTH_VOID_APPLY	   "FA0008"		/*  �������뽻��Ҫ����Ȩ	*/
#define		_AUTH_BACK_APPLY	   "FA0009"		/*  �˻����뽻��Ҫ����Ȩ	*/
#define		_AUTH_MODI_STATUS	   "FA0010"		/*  �޸Ľ���״̬Ҫ����Ȩ	*/
#define		_AUTH_REPT_DIFF		   "FA0011"		/*  �������Ҫ����Ȩ		*/
                                              		                          
#define		_UNKNOW_ERR            "999999"		/*  δ֪����				*/

/* ��־��Ϣ���� */
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
 * ����Ϊ������Ϣ����
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
