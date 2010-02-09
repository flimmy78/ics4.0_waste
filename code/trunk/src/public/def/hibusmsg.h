/******************************************************************************

				Copyright (C),1998-2003,Hisuntech Co.,Ltd.
 
 File name		: pub_msg.h
 Author			: peng_wh
 Version		: 1.0.0
 Date			: 2003.04.07
 Description	: ����ͳһ�涨��ǰ�����ϵͳ���м�ҵ��ʹ�õķ����룬ʹ�÷�Χ�Ǵ�ǰ���ڲ�
				  
 Others			: 
 History		: 
				  ���ݼ���

  No.	Date		Author		Modification
  ===	==========	========	==============================================

******************************************************************************/

#define		_SUCCEED               "000000"		/*  �ɹ�					*/

#define		_INVA_LOGON            "301400"		/*  ע�᷽ʽ��Ч			*/
#define		_INVA_LOGOUT           "301401"		/*  ע����ʽ��Ч			*/
#define		_FULL_LOGTAB           "301402"		/*  ע�����				*/
#define		_PROC_ALRE_LOGON       "301403"		/*  ͬһ������ע��			*/
#define		_APP_ALRE_LOGON        "301404"		/*  ͬһӦ�ñ�ʶ��ע��		*/
#define		_PROC_APP_CLASH        "301405"		/*  ���̺�Ӧ�ñ�ʶ��ͻ		*/
#define		_NOT_FOUND_APP         "301406"		/*  δ�ҵ�ע��Ӧ��			*/
#define		_INVA_SOUR_LOGON       "301407"		/*  ԴӦ��δ��Чע��		*/
#define		_INVA_TRAG_LOGON       "301408"		/*  Ŀ��Ӧ��δ��Чע��		*/
#define		_RE_START              "301409"		/*  ������������			*/
#define		_RE_START_ERR          "301410"		/*  ������������ʧ��		*/
#define		_LOST_INSIDE_DATA      "301411"		/*  �ڲ����ݶ�ʧ			*/
#define		_GRAV_PROC_ERR         "301412"		/*  ���س������			*/
#define		_START_APP_ERR         "301415"		/*  �ⲿ��������ʧ��    	*/
#define		_SYS_EXIT              "301416"		/*  ϵͳ�˳�            	*/
#define		_TOO_MANY_APP          "301417"		/*  Ӧ�ý���̫��			*/
#define		_INVA_APP              "301418"		/*  ��ЧӦ�ñ�ʶ			*/
#define		_APP_CHAN_ERR          "301419"		/*  Ӧ�ñ�ʶת������		*/
#define		_TOO_MANY_ROU          "301420"		/*  ·�ɱ�����̫��      	*/
#define		_INEXIST_ROU_TAB       "301421"		/*  ·�ɱ�δ����        	*/
#define		_RE_START_PROC         "301422"		/*  ������������ 			*/
#define		_FOUND_DIE_PROC        "301424"		/*  ���ֽ����� 				*/
#define		_LOST_INS_DATA         "301425"		/*  �ڲ����ݶ�ʧ			*/
#define		_NOT_ENV_VARI          "301440"		/*  û�����û�������		*/
#define		_PARA_NO_ASCII         "301450"		/*  ������ASCI�ַ�			*/
#define		_PARA_LEN_ERR          "301451"		/*  �����ֽڳ��ȴ�			*/
#define		_PARA_NO_NUM           "301452"		/*  �����������ַ�			*/
#define		_GET_PARA_ERR          "301453"		/*  ������ȡ����			*/
                                              		                          

#define		_PROCESSING            "320001"		/*  ���ڴ�����				*/
#define		_ASK_AUTH              "320002"		/*  Ҫ����Ȩ				*/
#define		_ACCT_NULL             "320003"		/*  �ʺŲ���Ϊ��			*/
#define		_INVALID_ACCT          "320004"		/*  ��Ч�ʺ�				*/
#define		_FREEZE_ACCT           "320005"		/*  �ʺţ����ţ�����		*/
#define		_NAME_ACCT_UNCONF      "320006"		/*  �ʺţ����ţ���������	*/
#define		_ERR_TRAN_STAT         "320007"		/*  ����״̬��				*/
#define		_INVALID_CARD          "320008"		/*  ��Ч����				*/
#define		_INVALID_AMOUNT        "320009"		/*  ��Ч���				*/
#define		_VIP_TRAN              "320010"		/*  �������				*/
#define		_PASSWD_ERR            "320011"		/*  �ֿ��˻����Ա�����	*/
#define		_INVALID_TRAN          "320012"		/*  ��Ч����				*/
#define		_IRREGU_TRAN           "320013"		/*  �Ƿ�����				*/
#define		_PACK_ERR              "320014"		/*  ���ݰ���ʽ����			*/
#define		_INEXIST_ORA_RECORD    "320015"		/*  �޴�ԭ����				*/
#define		_NOT_ENOUGH_INTEG      "320020"		/*  ���ֲ���				*/
#define		_CLEAN_INTEG_ERR       "320021"		/*  �����������			*/
#define		_INVA_CARD_KIND        "320022"		/*  ���ִ�					*/
#define		_PRINT_CLASH           "320023"		/*  ��ӡ��ͻ				*/
#define		_DATA_ERR              "320024"		/*  ���ݸ�ʽ��				*/
#define		_REQU_STAT_ERR         "320026"		/*  ����״̬����			*/
#define		_INVA_SEQU             "320027"		/*  ��ˮ�ź����Ͳ���		*/
#define		_INVA_PAGE_REQU        "320028"		/*  ����ʶ���ҳ����		*/
#define		_INVA_PAGE_APPLY       "320029"		/*  ҳ�����������			*/
#define		_CREAT_PRETRACE_ERR    "320031"		/*  ����ǰ����ˮ�Ŵ�		*/
#define		_GET_PRETRACE_ERR      "320032"		/*  ȡǰ����ˮ�Ŵ�			*/
#define		_NOT_ISSUE_CARD        "320033"		/*  δ����					*/
#define		_INVA_PRINT_REQU       "320034"		/*  ��Ч�Ĵ�ӡ����			*/
#define		_INEXIST_AUTH_AMOUNT   "320036"		/*  ��Ч��Ȩ���			*/
#define		_ASK_PRINT             "320037"		/*  Ҫ���ȴ�ӡ���ʱ���		*/
#define		_ENTER_LOGNO_ERR       "320038"		/*  ¼����ˮ�Ŵ�			*/
#define		_VOUDATE_LIMIT         "320039"		/*  ƾ֤���ڲ��ܴ��ڵ���	*/
#define		_OUTBANK_ERR           "320040"		/*  ����кŻ򷢱��кŴ�	*/
#define		_INBANK_ERR            "320041"		/*  �����кŻ��ձ��кŴ�	*/
#define		_INEXIST_RECORD        "320042"		/*  �޴˽�����ϸ			*/
#define		_NOT_APPLY_SERV        "320043"		/*  δ�������				*/
#define		_REPEAT_PACK           "320044"		/*  �ر�					*/
#define		_INEXIST_HOST_RECORD   "320045"		/*  �����޽��׼�¼			*/
#define		_INVA_FIELD            "320046"		/*  ��Ϣ�д��ڲ��Ϸ�����	*/
#define		_NULL_FIELD_ERR        "320047"		/*  �涨�ǿյ���Ϊ��		*/
#define		_ERR_AMOUNT            "320048"		/*  ���׽��Ϸ�			*/
#define		_AMOUNT_LIMIT          "320049"		/*  ת�ʽ��׽��С�ڹ涨	*/
#define		_TRUST_DATE_ERR        "320050"		/*  ί�����ڲ���ȷ			*/
#define		_OUT_SAME_IN           "320051"		/*  ���������������ͬ		*/
#define		_BANKNO_ERR            "320052"		/*  �кŴ�					*/
#define		_REQU_AREA_ERR         "320053"		/*  ��ѯ��Χ����ȷ			*/
#define		_INVA_MSG_CONT         "320054"		/*  ��Ϣ�����������Ϣ����	*/
#define		_INEXIST_COLLATE       "320055"		/*  ������Ϣ������			*/
#define		_INVALID_MCHANT        "320056"		/*  ��Ч������̻���		*/
#define		_INVA_FUNCTYPE         "320057"		/*  ��Ч����(��Ϣ���ʹ�)	*/
#define		_NOT_OBLIGATE_PIN      "320058"		/*  ���д���δԤ������		*/
#define		_ACCT_NOT_SET          "320059"		/*  �ʻ�δ����				*/
#define		_ACCT_ALRE_SET         "320060"		/*  �ʻ��ѿ���				*/
#define		_CALL_ISSUE            "320061"		/*  ��ϵ������				*/
#define		_SPEC_CALL             "320062"		/*  �ر���ϵ				*/
#define		_INVA_DATE             "320063"		/*  ��Ч����				*/
#define		_INVA_FEE_KIND         "320064"		/*  ��Ч�����������		*/
#define		_INVA_OPER             "320065"		/*  ��Ч����Ա��			*/
#define		_CHECK_PIN_ERR         "320066"		/*  ��������У���			*/
#define		_REPA_STOCK_SEQU       "320067"		/*  �ظ���֤ȯ��ˮ��		*/
#define		_SHORTAG_STOCK_BALA    "320068"		/*  ȯ���ʻ�����		*/
#define		_STOCKACC_ERRSTAT      "320069"		/*  ȯ���ʻ�״̬��			*/
#define		_SEQU_ERR              "320070"		/*  ���в�����ˮ�Ŵ���		*/
#define		_CROSS_ACCT_CLOSE      "320071"		/*  ͨ��ͨ�ұ��ر�			*/
#define		_INVA_STOCK_ACCT       "320072"		/*  ȯ���ʻ�������			*/
#define		_PRINT_BANKBOOK        "320073"		/*  �뵽���в������		*/
#define		_AMOUNT_OVER_LIMIT     "320074"		/*  ���ʽ��׽���		*/
#define		_INVA_FUNC             "320080"		/*  �˽���δ��ͨ			*/
#define		_INEXIST_STOCK         "320081"		/*  �޴�ȯ��				*/
#define		_CHECK_PASSERR         "320082"		/*  �ʽ�����У���			*/
#define		_SHORTAG_BALAN         "320083"		/*  �ͻ��ʽ��ʻ�����	*/
#define		_OVER_SUMLIMIT         "320084"		/*  �ۼƽ���			*/
#define		_REPEAT_SEQU           "320085"		/*  �ظ���������ˮ��		*/
#define		_INEXIST_REVE_RECORD   "320086"		/*  ��������ˮ������		*/
#define		_ALREAD_REVE           "320087"		/*  ����ˮ�ѳ���			*/
#define		_UNCONFOR_REVETRAN     "320088"		/*  ������ˮ����			*/
#define		_BALA_REFU_REVE        "320089"		/*  ����,���������		*/
#define		_INVA_BANKNO           "320090"		/*  ��Ч���к�				*/
#define		_FUNDACC_ERRSTAT       "320091"		/*  �ʽ��ʻ�״̬��			*/
#define		_INEXIST_FUNDACC       "320092"		/*  �ʽ��ʻ�������			*/
#define		_ACCT_ALRE_CLOSED      "320093"		/*  ���ʻ�������			*/
#define		_NOT_BASED_PARA        "320094"		/*  ֤ȯ�����ж�Ӧ��ϵδ��	*/
#define		_BASED_PARA            "320095"		/*  ֤ȯ�����ж�Ӧ��ϵ�ѽ�	*/
#define		_DISALLOW_TRANSFER     "320096"		/*  �ÿͻ�ת�ʹ���δ����	*/
#define		_CLOSE_TRANSFER        "320097"		/*  �ÿͻ�ת�ʹ����ѹر�	*/
#define		_ASSET_OVER_LIMIT      "320098"		/*  �ÿͻ��ʲ���ֵ��������	*/
#define		_SERIAL_UNCON          "320099"		/*  ֤ȯ��˾��Ų���		*/
#define		_DISALLOW_FUNC         "320100"		/*  �˽���δ��ͨ			*/
#define		_STOCK_NO_SIGN         "320101"		/*  ֤ȯ��˾δǩ��			*/
#define		_STOCK_LOGOUT          "320102"		/*  ֤ȯ��˾��ǩ��			*/
#define		_NO_TRANSFER_FUNC      "320103"		/*  ת�ʹ���δ����			*/
#define		_STOCK_SERV_ERR        "320104"		/*  ֤ȯ��˾������ϵͳ����	*/
#define		_POSSIB_OPERERR        "320105"		/*  ���ɲ�����				*/
#define		_AGAIN_ENTRY           "320106"		/*  �����½���				*/
#define		_PART_HONOR            "320107"		/*  ���ֳж�				*/
#define		_REFUSE_BUSIN          "320108"		/*  �ܾ�����				*/
#define		_INFRACT_SECU          "320109"		/*  Υ����ȫ�涨			*/
#define		_NO_VOID_RECORD        "320110"		/*  ��������ˮ������		*/
#define		_ALRE_VOID             "320111"		/*  ��������ˮ�ѳ���		*/
#define		_UNCONFOR_TRAN         "320112"		/*  ��������ˮ����			*/
#define		_NO_RECORD             "320113"		/*  ����ѯ��ˮ������		*/
#define		_REFU_REVERSAL         "320114"		/*  �ܾ�����				*/
#define		_AVALID_TERMNO         "320115"		/*  ��Ч�ն�				*/
#define		_REFU_HONOR            "320116"		/*  ���ж�					*/
#define		_ERROR                 "320117"		/*  ���					*/
#define		_LABLE_HONOR           "320118"		/*  ��ʶ�ж�				*/
#define		_INQU_RESP             "320119"		/*  ��ѯ��Ӧ��				*/
#define		_PART_AUTH             "320120"		/*  ������׼				*/
#define		_LEAD_AUTH             "320121"		/*  �쵼��׼				*/
#define		_INVALID_ISSU          "320122"		/*  �޴˷�����				*/
#define		_UPDATE_TRACK3         "320123"		/*  ����3�ŵ�				*/
#define		_CLIENT_VOID           "320124"		/*  �ͻ�ȡ��				*/
#define		_CLIENT_DISPUTED       "320125"		/*  �ͻ�����ִ				*/
#define		_REPEAT_TRAN           "320126"		/*  �ظ�����				*/
#define		_AVALID_RET            "320127"		/*  ��Ч��Ӧ				*/
#define		_NO_ACTION             "320128"		/*  ����ȡ�ж�				*/
#define		_SUSP_FAIL             "320129"		/*  ���ϻ���				*/
#define		_ERR_FEE               "320130"		/*  �Ƿ����׷�				*/
#define		_REFU_UPDATE           "320131"		/*  ��֧�ָ���				*/
#define		_REPEAT_UPDATE         "320132"		/*  �ظ�����				*/
#define		_UPDATE_FIELD_ERR      "320133"		/*  �����ֶδ�				*/
#define		_TARNSACT              "320134"		/*  ���ڴ���				*/
#define		_UPDATE_ERR            "320135"		/*  ����ʧ��				*/
#define		_NOJOIN_BANK           "320136"		/*  δ��������				*/
#define		_PARTIAL               "320137"		/*  �������				*/
#define		_OVER_EXPIRE           "320138"		/*  ����,û��				*/
#define		_CHEAT_CARD            "320139"		/*  ���,û��				*/
#define		_CALL_BANK             "320140"		/*  ��ϵ,û��				*/
#define		_LIMIT_CARD            "320141"		/*  ����,û��				*/
#define		_PICKUP_CARD           "320142"		/*  ��ʧ,û��				*/
#define		_LOCK_RECORD           "320143"		/*  ��¼����				*/
#define		_ERR_ACCOUNT           "320144"		/*  �޴����ʻ�				*/
#define		_LOSE_CARD             "320145"		/*  ��ʧ��û��				*/
#define		_ERR_CURR_ACC          "320146"		/*  ��ͨ���ʻ�				*/
#define		_ERR_INVEST_ACC        "320147"		/*  ��Ͷ���ʻ�				*/
#define		_LACK_BALANCE          "320148"		/*  �ʽ���				*/
#define		_ERR_CHEQUE_ACC        "320149"		/*  ��֧Ʊ�ʻ�				*/
#define		_ERR_SAVING_ACC        "320150"		/*  �޴����ʻ�				*/
#define		_OVER_EXPI_CARD        "320151"		/*  ���ڿ�					*/
#define		_PIN_ERR               "320152"		/*  ���������				*/
#define		_NO_CARD_RECORD        "320153"		/*  �޿���¼				*/
#define		_DISALLOW_TRAN         "320154"		/*  ��������				*/
#define		_DISALLOW_DEAL         "320155"		/*  ��������				*/
#define		_POSSIB_CHEAT          "320156"		/*  �������				*/
#define		_CALL_SUPPLY           "320157"		/*  ��ϵ����				*/
#define		_OVER_DRAW             "320158"		/*  ������޶�				*/
#define		_OVER_FEE              "320159"		/*  ���ó����޶�			*/
#define		_IMP_SECU              "320160"		/*  �ַ���ȫ				*/
#define		_ORI_AMOUNT_ERR        "320161"		/*  ԭʼ����				*/
#define		_OVER_TIMES            "320162"		/*  ��������				*/
#define		_CALL_SECU             "320163"		/*  ֪ͨ����				*/
#define		_SEIZURE_CARD          "320164"		/*  �����̿�				*/
#define		_BELATE_ANSW           "320165"		/*  ��Ӧ��ʱ				*/
#define		_OVER_PIN_TIMES        "320166"		/*  �������				*/
#define		_END_PROC              "320167"		/*  ����������				*/
#define		_NOT_FOUND_NET         "320168"		/*  �Ҳ�������				*/
#define		_REPT_ENTRY            "320169"		/*  �ظ�����				*/
#define		_ID_ERR                "320170"		/*  ֤����					*/
#define		_MCHANT_NO_HONOR       "320171"		/*  �̻�δ�ж�				*/
#define		_NO_HONOR_ORIG         "320172"		/*  ԭ����δ�ж�			*/
#define		_ASK_FAILURE           "320173"		/*  ��������ʧ��			*/
#define		_ISSU_FAILURE          "320174"		/*  ����������				*/
#define		_REPEAT_ANSWER         "320175"		/*  �ظ�Ӧ��				*/
#define		_NO_CENTER_ANSWER      "320176"		/*  ������Ӧ��				*/
#define		_NO_ISSU_ANSWER        "320177"		/*  ��������Ӧ��			*/
#define		_ACQU_TIMEOUT          "320178"		/*  ������ʱӦ��			*/
#define		_ACQU_FAILURE          "320179"		/*  ��������				*/
#define		_COUNT_ERR             "320180"		/*  ��������				*/
#define		_ORIG_CHANGE           "320181"		/*  ԭ���׸ı�				*/
#define		_BOOKIN_LIMIT_ERR      "320182"		/*  ��������				*/
#define		_NO_OBTAIN             "320183"		/*  �޷�����				*/
#define		_DONOT_OPER            "320184"		/*  �޷�����				*/
#define		_CHANGE_DATE           "320185"		/*  �����л�				*/
#define		_END_REQU              "320186"		/*  ��ѯ������־			*/
#define		_HOST_TRACE_NULL       "320187"		/*  ������ˮ��Ϊ��      	*/
#define		_ABSENT_FIT_CARD       "320188"		/*  FIT�����޴˿�       	*/
#define		_CASHBOX_STAT_ERR      "320189"		/*  ����״̬����        	*/
#define		_REVE_ERR              "320190"		/*  �������׷����쳣    	*/
#define		_INVA_MSG              "320191"		/*  �������ݷǷ�			*/
#define		_FOUND_TIMEOUT         "320192"		/*  ���ֽ��׳�ʱ			*/
#define		_TOO_MANY_REVE         "320193"		/*  ��������̫��			*/
#define		_INVA_TIME             "320194"		/*  ʱ��Ƿ�				*/
#define		_TOO_LARGE_VALUE       "320195"		/*  ��ֵ̫�� 				*/
#define		_INVA_REVE_MAKE        "320196"		/*  �������ı�ʶ����𲻷�	*/
#define		_INVA_SIGN             "320197"		/*  ���ִ��������Ŵ���		*/
#define		_INVA_OFFSET           "320200"		/*  ��ЧBitMap����ƫ����	*/
#define		_BM_OPEN_ERR           "320201"		/*  BitMap�����ļ���		*/
#define		_BM_FILE_ERR           "320202"		/*  BitMap�����ļ���ʽ		*/
#define		_8583_DATA_LEN         "320203"		/*  8583���ݳ���			*/
#define		_8583_HEAD_ERR         "320204"		/*  8583�ṹ���� 			*/
#define		_INVA_BUSS_TYPE        "320300"		/*  ҵ�����Ͳ����� 			*/
#define		_INVA_UNIT_CODE        "320301"		/*  ��λ���벻���� 			*/
#define		_INVA_TRAN_TYPE        "320302"		/*  ��������޶��� 			*/
#define		_INQU_RECV_FAIL        "320303"		/*  ���ս�������ʧ��		*/
#define		_INQU_LEN_ERR          "320304"		/*  �����������ݰ����ȳ��� 	*/
#define		_INQU_FORM_ERR         "320305"		/*  �����������ݰ���ʽ���� 	*/
#define		_SEND_RETU_FAIL        "320306"		/*  ���ͽ��׽��ʧ�� 		*/
#define		_DATA_OVER_RANGE       "320307"		/*  ���ݳ�����Χ	 		*/
#define		_GET_ACDAT_ERR	       "320308"		/*  ��ȡ������ڴ��� 		*/
#define		_GET_SYSDAT_ERR	       "320309"		/*  ��ȡϵͳ���ڴ��� 		*/
#define		_BAT_STATUS_ERR	       "320310"		/*  ������״̬����	 		*/
#define		_BAT_PROC_NOW	       "320311"		/*  �������ڴ�����	 		*/
#define		_ELE_NOT_ENOUGH	       "320312"		/*  ����Ҫ�ز�ȫ	 		*/
#define		_AUTH_CHECK_ERR	       "320313"		/*  ��Ȩ����		 		*/
#define		_REPLY_NODE_ERR	       "320314"		/*  ���ɻظ��Ǳ�������Ϣ	*/
#define		_REPLY_ALRE_ERR	       "320315"		/*  �ѻظ�					*/
#define		_CANCEL_ALRE_ERR	   "320316"		/*  ��ȡ��					*/
#define		_ALRE_PUR_ERR	   	   "320317"		/*  �Ѿ��и�Ӧ�÷�����Ȩ��  */
#define		_NO_PUR_ERR	   		   "320318"		/*  �����ڸ�Ӧ�÷�����Ȩ��  */
#define		_ALRE_ORG_PUR	   	   "320319"		/*  ���иû�����Ȩ�޼�¼  */
#define		_ALRE_TLR_PUR	   	   "320320"		/*  ���иù�Ա��Ȩ�޼�¼  */
#define		_ALRE_TXN_AUTH	   	   "320321"		/*  ���иý��׵Ľ����Ȩ��Ϣ*/
#define		_NO_TXN_AUTH	   	   "320322"		/*  û�иý��׵Ľ����Ȩ��Ϣ*/
#define		_REPLY_NO_ERR	       "320323"		/*  δ�ظ�					*/
#define		_RETU_NO_ERR	       "320324"		/*  ��δ�յ���ִ			*/
#define		_INACCT_SQN_ERR	       "320325"		/*  ���ʰ��Ŵ�  			*/
#define		_WAIT_PROC_NOW	       "320326"		/*  ��δ���������ڴ������Ժ�*/

#define		_RCV_RTCBK_ERR	       "320400"		/*  �����кŴ�              */
#define		_RCV_BANK_ERR	       "320401"		/*  �����кŴ�              */
#define		_RCV_SETTBK_ERR	       "320402"		/*  ���������кŴ�          */
#define		_RPC_CODE_ERR	       "320403"		/*  �ձ����Ĵ����          */
#define		_NO_CTL_NODE	       "320404"		/*  ��ͨ���������          */
#define		_SYS_STAT_ERR1	       "320405"		/*  ֻ�����ռ估����״̬����*/
#define		_SYS_STAT_ERR2	       "320406"		/*  ֻ�������㡢�ռ估����״̬*/
#define		_AMT_LESS_LIMIT	       "320407"		/*  ���С�ڴ�����ƽ��,��Ҫ�Ӽ� */
#define		_SND_NM_EMPTY	       "320408"		/*  ������������            */
#define		_RCV_NM_EMPTY	       "320409"		/*  ������������            */
#define		_SUMMARY_EMPTY	       "320410"		/*  ժҪ����                */
#define		_BUS_UNEXHAUST	       "320411"		/*  ��δ����ҵ��            */
#define		_NO_RTC_NODE	       "320412"		/*  ��ͨ������          	*/
#define		_LOG_NO_ERR	       	   "320413"		/*  ��ˮ�Ŵ�          		*/
#define		_TRACE_NO_ERR	       "320414"		/*  ��Ʊ�Ŵ�          		*/
#define		_TRAN_NODE_ERR	       "320415"		/*  �Ǳ���������       		*/
#define		_ALLOW_FUND_REMIT	   "320416"		/*  ��ҵ����������ʽ�㻮	*/
#define		_SBK_EQUAL_RBK	   	   "320417"		/*  �����в������ձ����к���ͬ*/
#define		_STCBK_EQUAL_RTCBK	   "320418"		/*  ����в������������ͬ	*/
#define		_NODE_INFO_ERR	   	   "320419"		/*  �����Ӧ�к���������	*/
#define		_UNGRAT_PRINT_CONDI	   "320420"		/*  �в������ӡ�����ļ�¼	*/
#define		_DATE_ERR              "320421"		/*  ¼�����ڻ�ƾ֤���ڴ�	*/
#define		_SND_RTCBK_ERR	       "320422"		/*  ����кŴ�              */
#define		_SND_OBANK_ERR	       "320423"		/*  ������кŴ�          */
#define		_FEE_TYPE_ERR	       "320424"		/*  �շ�ѡ���뱨�����ȼ�����*/
                                              		                          
#define		_PRE_ERR_CODE          "320900"		/*  ǰ��Ԥ�ô�����			*/
#define		_NO_EXPECT_MSG         "320901"		/*  �յ�����Ϣ����Ԥ��		*/
#define		_NEED_ONLY_CONFIG      "320902"		/*  ����������Ψһ			*/
#define		_QUERY_END             "320903"		/*  ��ѯ����				*/
                                              		                          
#define		_MSG_FMTNAME_ERR       "320905"		/*  ��Ϣ��ʽ���ƴ���		*/
#define		_MSG_LABEL_ERR         "320906"		/*  ��Ϣ�Ի���ʶ����		*/
#define		_MSG_SEQU_ERR          "320907"		/*  ��Ϣ˳��Ŵ���			*/
#define		_INVA_ORAMSG_SEQU      "320908"		/*  ԭ��Ϣ˳��Ų��Ϸ�		*/
#define		_INVA_MSG_SEQU         "320909"		/*  ��Ϣ˳��Ų��Ϸ�		*/
#define		_FIELD_NUM_ERR         "320910"		/*  ��Ϣ�а�������Ŀ��		*/
#define		_FIELD_LEN_ERR         "320911"		/*  ��Ϣʵ�ʳ��Ȳ���		*/
#define		_MAX_FIELD_SEQU        "320913"		/*  �Ѵ������Ϣ���к�		*/
#define		_OVER_ERR_NUM          "320914"		/*  �������������			*/
#define		_INVA_VOID_MSG         "320915"		/*  Ҫ��������Ϣ��֧����Ϣ	*/
#define		_WAIT_TIME_OUT         "320916"		/*  �ȴ�ʱ�����			*/
                                              		                          
#define		_DB_OPER_ERR           "331000"		/*  ���ݿ��������			*/
#define		_DB_FEAR_ERR           "331001"		/*  ���ݿ�������			*/
#define		_DB_CONN_ERR           "331002"		/*  �������ݿ�ʧ��			*/
#define		_DB_INIT_ERR           "331003"		/*  ��ʼ�����ݿ��豸��		*/
#define		_DB_LOGIN_ERR          "331004"		/*  ��¼���ݿ�ʧ��			*/
#define		_DB_OPEN_ERR           "331005"		/*  ���û����ݿ�ʧ��		*/
#define		_DB_EXEC_ERR           "331006"		/*  ִ�����ݿ��������	*/
#define		_DB_RESULT_ERR         "331007"		/*  �������ݿ�ִ�н����	*/
#define		_DB_INS_ERR            "331008"		/*  ��¼����ʧ�� 			*/
#define		_DB_PROC_ERR           "331009"		/*  �洢���̳���			*/
#define		_DB_REPT_REC           "331010"		/*  �ظ��Ĳ����¼ 			*/
#define		_DB_UPDATE_ERR         "331011"		/*  ���¼�¼ʧ��			*/
#define		_DB_NO_RECORD          "331012"		/*  ���ݿ��޶�Ӧ��¼		*/
#define		_DB_QUERY_ERR          "331013"		/*  ���ݿ��ѯʧ��			*/
                                              		                          
#define		_SYS_BUSY_DELAY        "341200"		/*  ��ϵͳ��æ���ӳ�		*/
#define		_INSIDE_PROBLEM        "341201"		/*  ���ڲ����ⲻ����ɴ���	*/
#define		_PIGEONHOLE_MSG        "341202"		/*  ��Ϣ��ϸ��¼�ѱ��鵵	*/
#define		_SYS_BUSY_REFU         "341203"		/*  ���ϵͳ��æ���ױ��ܾ�	*/
#define		_ABSE_LOGON_HOST       "341204"		/*  ��δ��¼����			*/
#define		_ABSE_LOGON_APP        "341205"		/*  ��δ��¼Ӧ��ϵͳ		*/
#define		_REFU_ACCE             "341206"		/*  ��ǰ�������ڲ�������Ϣ	*/
#define		_ID_PASS_ERR           "341207"		/*  �û���ʶ������ȷ	*/
#define		_ALRE_LOGON            "341208"		/*  �ѵ�¼					*/
#define		_ALRE_LOGOUT           "341209"		/*  ���˳�					*/
#define		_PASS_EXPIRE           "341210"		/*  ������Чʹ�������ѹ�	*/
#define		_LOGON_SEQU_ERR        "341211"		/*  ��¼˳�����			*/
#define		_DISALLOW_LOGON        "341212"		/*  �������¼				*/ 
#define		_LOGON_TYPE_ERR        "341213"		/*  ��¼���ʹ���			*/
#define		_INVA_USEID            "341214"		/*  �Ƿ��û���ʶ���¼����	*/
#define		_PRE_ABSE_LOGON        "341215"		/*  ǰ�û�δǩ��			*/
#define		_SYS_CUT_OFF           "341218"		/*  ϵͳ��ֹ				*/
#define		_START_TIME_LIMIT      "341219"		/*  ��ʼʱ����ڽ���ʱ��	*/
#define		_NODE_NO_CLOSE         "341220"		/*  ����δ�ر�				*/
#define		_SYS_NO_CLOSE          "341221"		/*  ϵͳδ�ر�				*/
#define		_PMS_NO_CLOSE          "341222"		/*  ֧��ϵͳ״̬δ�ر�		*/
                                              		                          
#define		_FILE_OPEN_ERR         "341500"		/*  ���ļ���				*/
#define		_FILE_INEX_CONF        "341501"		/*  �������ļ�				*/
#define		_FILE_ERR_UPDA         "341502"		/*  �ļ����´�				*/
#define		_FILE_ERR_FIELD        "341503"		/*  �ļ��������			*/
#define		_FILE_AGAIN_UPDA       "341504"		/*  �ظ��ļ�����			*/
#define		_FILE_NO_RECORD        "341505"		/*  ���ļ���¼				*/
#define		_FILE_REFU_UPDA        "341506"		/*  �ܾ��ļ�����			*/
#define		_FILE_LOCK             "341507"		/*  �ļ�����				*/
#define		_FILE_NAME_NULL        "341508"		/*  ǰ�������ļ�������Ϊ��	*/
#define		_FILE_INEXIST          "341509"		/*  ǰ���޴��ļ�,�������ϴ�	*/
#define		_FILE_REPEAT           "341510"		/*  ���ϴ��ļ�,�����ظ��ϴ�	*/
#define		_FILE_INVA_FORM        "341511"		/*  �ϴ��ļ��޶�Ӧ��ʽ����	*/
#define		_FILE_PARSE_ERR        "341512"		/*  ǰ���ϴ��ļ�����ʧ��	*/
#define		_FILE_SUCC_RETU        "341513"		/*  �ļ������������ɻ����ļ�*/
#define		_FILE_SERIAL_FAIL      "341514"		/*  �������������ļ����ʧ��*/
#define		_FILE_PARSE_FAIL       "341515"		/*  �ļ�����ʧ��			*/
#define		_FILE_CREAT_FAIL       "341516"		/*  �ļ�����ʧ��			*/
#define		_FILE_INEXI_FRETU      "341517"		/*  ǰ�û����ļ�δ����		*/
#define		_FILE_INEXI_HRETU      "341518"		/*  ���������ļ�δ����		*/
#define		_FILE_SUM_FINQ         "341519"		/*  ǰ���ϴ��ļ��ܽ���	*/
#define		_FILE_COUNT_FINQ       "341520"		/*  ǰ���ϴ��ļ��ܱ�������	*/
#define		_FILE_SUM_HRETU        "341521"		/*  ���������ļ��ܽ���	*/
#define		_FILE_COUNT_HRETU      "341522"		/*  ���������ļ��ܱ�������	*/
#define		_FILE_ERR_HRETU        "341523"		/*  ���������ļ�����		*/
#define		_FILE_PARSE_HRETU      "341524"		/*  ���������ļ�����ʧ��	*/
#define		_FILE_AMT_ERR          "341525"		/*  ��ǰ�ļ�����		*/
#define		_FILE_SEQU_ERR         "341526"		/*  ��ǰ�ļ�˳��Ų���		*/
#define		_FILE_SUCC_REPEAT      "341527"		/*  �ļ��Ѵ���ɹ�,�������ٴ���	*/
#define		_FILE_PROC_REPEAT      "341528"		/*  �ļ����ղ������ٴδ���	*/
#define		_FILE_ALRE_AFFIRM      "341529"		/*  ������ȷ��,�����ظ�����	*/
#define		_FILE_ACTDAT_ERR       "341530"		/*  �ļ����ܼ�¼���ļ������ڲ���*/
#define		_FILE_NO_DATA          "341531"		/*  ���������ݣ������ļ�ʧ��*/
                                              		                          
#define		_BRAN_INEXIST          "341600"		/*  ����Ų����ڻ��������ô�*/
#define		_BRAN_NET_ERR          "341601"		/*  ����վ���				*/
#define		_BRAN_AREA_ERR         "341602"		/*  �Ǳ�֧������			*/
#define		_BRAN_AUTH_CON         "341603"		/*  �޸�������Ȩ����		*/
#define		_OPER_LEVEL_LIMIT      "341650"		/*  ��Ա���𲻹�			*/
#define		_OPER_ERR              "341651"		/*  ���׹�Ա��				*/
#define		_OPER_INEXIST          "341652"		/*  �޴˹�Ա				*/
#define		_OPER_NEED_DIFF        "341653"		/*  ��Ҫ��ͬ��Ա			*/
#define		_OPER_PUR_ERR          "341654"		/*  ��Ա�޴�Ȩ��			*/
#define		_OPER_ORA_ERR          "341655"		/*  ��ԭ���׹�Ա			*/
#define		_OPER_PASS_ERR         "341656"		/*  ��Ա�����				*/
                                              		                          
#define		_HOST_TIMEOUT          "341702"		/*  ������ʱ				*/
#define		_NET_ERR               "341703"		/*  �������				*/
#define		_NEED_REQU             "341704"		/*  ���ѯ�ϱʽ����Ƿ�ɹ�	*/
#define		_BANK_OTHER_ERR        "341705"		/*  ���з�����������		*/
#define		_SEND_HOST_ERR         "341707"		/*  ��������ʧ��			*/
#define		_PRE_OTHER_ERR         "341708"		/*  ǰ�û���������			*/
#define		_COMM_TIMEOUT          "341795"		/*  ͨѶ��ʱ				*/
#define		_SYSTEM_ERR            "341796"		/*  ϵͳ����				*/
#define		_ERR_CORTROL           "341797"		/*  ���ƴ�					*/
#define		_NET_VER_ERR           "341798"		/*  ����汾������			*/
                                              		                          
#define		_QPAIR_OPER_ERR        "311800"		/*  QPAIR����ʧ��       	*/
#define		_INVA_COMM_MODE        "311801"		/*  ��֧�ֵ�ͨѶ��ʽ		*/
#define		_CREAT_MSG_FAIL        "311803"		/*  MSG��������ʧ��     	*/
#define		_SAVE_MSGH_FAIL        "311804"		/*  MSG����ͷ����ʧ��   	*/
#define		_SEND_ERR_FAIL         "311805"		/*  Ӧ�ô�����Ϣ����ʧ��	*/
#define		_XML_OPER_ERR          "311806"		/*  XML��������      		*/
#define		_HICALL_TIMEOUT        "311807"		/*  HICALL���ó�ʱ   		*/
#define		_HICALL_FAIL           "311808"		/*  HICALL����ʧ��   		*/
#define		_GET_ENV_FAIL          "311809"		/*  ȡ�û�������ʧ��    	*/
#define		_MALLOC_ERR            "311810"		/*  �ڴ�������			*/
#define		_INVALID_LEN           "311811"		/*  ͨѶ��Ϣ�ĳ������		*/
#define		_READ_TIMEOUT          "311812"		/*  ͨѶ����Ϣ����ʱ		*/
#define		_FINGER_NULL           "311813"		/*  ��Ϣָ��Ϊ��			*/
#define		_OPER_MSG_ERR          "311814"		/*  ��Ϣ����ʧ��			*/
#define		_CLONE_MSG_ERR         "311815"		/*  �޷�������Ϣ			*/
#define		_DLL_OPER_ERR          "311816"		/*  ��̬�����ʧ��   		*/
#define		_APP_RET_ERR           "311817"		/*  Ӧ�÷��س���     		*/
#define		_MUTEX_OPER_ERR        "311818"		/*  �߳�������ʧ��   		*/
#define		_MODE_ERR              "311819"		/*  ���ͻ����ģʽ����		*/
#define		_SET_PIPE_ERR          "311820"		/*  �����ܵ�ʧ��        	*/
#define		_READ_PIPE_ERR         "311821"		/*  ���ܵ���ʧ�� 			*/
#define		_MSG_INIT_ERR          "311830"		/*  ��Ϣ���г�ʼ������		*/
#define		_MSG_PUR_ERR           "311831"		/*  ��Ϣ����Ȩ�޴���		*/
#define		_MSG_EXIST             "311832"		/*  ��Ϣ�����Ѵ���			*/
#define		_MSG_INEXIST           "311833"		/*  ��Ϣ���в�����			*/
#define		_MSG_OPER_ERR          "311834"		/*  ��Ϣ���в�������		*/
#define		_MSG_INVA_ID           "311835"		/*  ��Ϣ���б�ʶ����		*/
#define		_MSG_FULL              "311836"		/*  ��Ϣ������Ϣ����    	*/
#define		_MSG_GET_ERR           "311837"		/*  ��Ϣ����ȡ�ô���    	*/
#define		_MSG_SEND_ERR          "311838"		/*  ��Ϣ���з��ʹ���    	*/
#define		_MSG_RECV_ERR          "311839"		/*  ��Ϣ���н��մ���		*/
#define		_SHM_INIT_ERR          "311850"		/*  �����ڴ��ʼ������		*/
#define		_SHM_PUR_ERR           "311851"		/*  �����ڴ�Ȩ�޴���		*/
#define		_SHM_EXT_ERR           "311852"		/*  �����ڴ��Ѵ���			*/
#define		_SHM_SIZE_ERR          "311853"		/*  �����ڴ泤�ȴ���		*/
#define		_SHM_NOEXT             "311854"		/*  �����ڴ治����			*/
#define		_SHM_NOMEM             "311855"		/*  �����ڴ�ռ䲻��		*/
#define		_SHM_OPER_ERR          "311856"		/*  �����ڴ�������� 		*/
#define		_SHM_GET_ERR           "311857"		/*  �����ڴ�ȡ�ô���		*/
#define		_SEM_INIT_ERR          "311870"		/*  ��ʼ���źŵƴ� 			*/
#define		_SEM_GET_ERR           "311871"		/*  �źŵ�ȡ�ô���			*/
#define		_SEM_P_ERR             "311872"		/*  �źŵ� P ����ʧ�� 		*/
#define		_SEM_V_ERR             "311873"		/*  �źŵ� V ����ʧ��		*/
#define		_SEM_RM_ERR            "311874"		/*  ɾ���ź�ʧ��			*/
#define		_IP_ADDR_ERR           "311880"		/*  IP��ַ����				*/
#define		_IP_INVA_ADDR          "311881"		/*  IP��ַδ�Ǽ�			*/
#define		_IP_REPE_ADDR          "311882"		/*  IP��ַ�ظ�				*/
#define		_NET_TIME_OUT          "311883"		/*  ���糬ʱ����			*/
#define		_NET_ACCE_RET          "311884"		/*  ����Ӧ�����ʧ��		*/
#define		_NET_INVA_HAND         "311885"		/*  ��������Э����Ч		*/
#define		_NET_INVA_TRSP         "311886"		/*  ���紫��Э����Ч		*/
#define		_SOCK_OPEN_ERR         "311890"		/*  �׽��ִ򿪴���			*/
#define		_SOCK_READ_ERR         "311891"		/*  �׽��ֶ�����			*/
#define		_SOCK_WRIT_ERR         "311892"		/*  �׽���д����			*/
#define		_SOCK_CONN_ERR         "311893"		/*  �׽���connect����		*/
#define		_SOCK_BIND_ERR         "311894"		/*  �׽���bind����			*/
#define		_SOCK_ACCE_ERR         "311895"		/*  �׽���accept����		*/
#define		_SOCK_OPER_ERR         "311896"		/*  �׽��ֲ�������			*/
#define		_NODE_OPER_ERR         "311910"		/*  �ڵ��������			*/
#define		_NODE_GET_ERR          "311911"		/*  ȡ���ݽڵ��			*/
#define		_NODE_ROOT_NULL        "311912"		/*  ���ڵ�Ϊ��				*/
#define		_SYNC_OUT_FAIL         "311930"		/*  ���ͬ��ʧ��			*/
#define		_SYNC_CYCLE            "311931"		/*  ����ͬ������			*/
#define		_SYNC_NEED_SEND        "311932"		/*  ��Ҫͬ������			*/
#define		_SYNC_NOT_SIGN         "311933"		/*  ��ͬ���Ի���־			*/
#define		_SYNC_NOT_SEQU         "311934"		/*  ��ͬ����Ϣ˳���		*/
#define		_CSER_INIT_FAIL        "311950"		/*  CommunicationServer��ʼ��ʧ��*/
#define		_APPC_SESS_FAIL        "311951"		/*  ���� APPC SESSION ʧ��	*/
#define		_SNA_SEND_FAIL         "311952"		/*  SNA ͨ������ʧ��		*/
#define		_SNA_RECV_FAIL         "311953"		/*  SNA ͨ�Ž���ʧ��		*/
#define		_SNA_TIME_OUT          "311954"		/*  SNA ͨ�Ž���ͨ�ų�ʱ	*/
#define		_SNA_CONFIRM_FAIL      "311955"		/*  SNA ͨ��ȷ��ʧ��		*/
#define		_SNA_INIT_ERR	       "311956"		/*  SNA��ʼ������			*/
#define		_SNA_ALLOCATE_FAIL     "311957"		/*  SNA����SESSIONʧ��		*/
#define		_SNA_FREE_FAIL 	       "311958"		/*  ��������ABEND�����ͷ�SESSIONʧ��	*/
#define		_SNA_FINDLU_ERR 	   "311959"		/*  SNA����LUʧ��			*/
#define		_ETF_GET_ERR	       "311970"		/*  ��ȡETF�ڵ����			*/
                                               		                          
#define		_MAC_ERR               "352000"		/*  MAC����					*/
#define		_DECRY_ERR             "352001"		/*  ���ܴ���				*/
#define		_ENCRY_CHECK_ERR       "352002"		/*  ����У���ִ�			*/
#define		_AUTH_CODE_ERR         "352003"		/*  ��������֤���			*/
#define		_PAY_CODE_ERR          "352004"		/*  ֧�����				*/
#define		_CODESEAL_ERR          "352005"		/*  ����ӡ����				*/
#define		_CHECKSUM_ERR          "352006"		/*  Checksum����ȷ			*/
#define		_KEY_UPDATE_ERR        "352007"		/*  ��Կ���³ɹ�			*/
#define		_KEY_UPDATE_FAIL       "352008"		/*  ��Կ����ʧ��			*/
#define		_SYS_UPDATE_KEY        "352009"		/*  ϵͳ����������Կ		*/
#define		_OUT_UPDATE_KEY        "352010"		/*  �ⲿҪ��������Կ		*/
#define		_KEY_ERR               "352011"		/*  ��Կ����				*/
#define		_NEED_INIT_KEY         "352012"		/*  û�г�װ��Կ			*/
#define		_PIN_FAILURE           "352013"		/*  PIN��ʽ��				*/
#define		_CENTER_SECU_ERR       "352014"		/*  ���ı��ܴ�				*/
#define		_ENMACH_STAT_ERR       "352015"		/*  ���ܻ�״̬����      	*/
                                              		                          
#define		_IN_LEDGER_UNCONF      "363000"		/*  ����(��)����			*/
#define		_OUT_LEDGER_UNCONF     "363001"		/*  ����(��)����			*/
#define		_SUM_LEDGER_UNCONF     "363002"		/*  ������ͳ�ƶ���			*/
#define		_INEXIST_LEDGER_LIST   "363003"		/*  ������ϸδ����			*/
#define		_SUM_AMOUNT_UNCONF     "363004"		/*  �ܽ���				*/
#define		_SUM_COUNT_UNCONF      "363005"		/*  �ܱ�������				*/
#define		_DEBIT_CNT_ERR         "363006"		/*  ��Ǳ�������			*/
#define		_CREDIT_CNT_ERR        "363007"		/*  ���Ǳ�������			*/
#define		_DEBIT_AMT_ERR         "363008"		/*  ��ǽ���			*/
#define		_CREDIT_AMT_ERR        "363009"		/*  ���ǽ���			*/
#define		_CAN_NOT_SETT          "363010"		/*  �˶Բ�����������		*/
#define		_TODAY_ALRE_SETT       "363011"		/*  ����������				*/
#define		_INVA_SETT_DATE        "363012"		/*  ������������			*/
#define		_BUSS_NOT_SETT         "363013"		/*  ҵ��δ��ɲ�������		*/
#define		_PMS_NOT_SETT          "363014"		/*  ����֧��ϵͳδ����		*/

#define		_AGR_NOT_FOUND         "400001"		/*  Э�鲻����		*/
#define		_AGR_NOT_EFFECT        "400002"		/*  Э��δ��Ч		*/
#define		_AGR_INVALID           "400003"		/*  Э���ѵ���		*/
#define		_AGR_ERROR             "400004"		/*  Э�鲻��		*/
#define		_AGR_EXISTS            "400005"		/*  Э���Ѵ���		*/
#define		_AGT_NOT_EXISTS        "400006"		/*  ������񲻴���		*/
#define		_AGT_CLOSED            "400007"		/*  ��������ѹر�		*/
#define		_AGT_EXISTS            "400008"		/*  ��������Ѵ���		*/
                                              		                          
#define		_CIM_OVR_TLRLVL        "450101"     /*  ��Ա���𳬳���Χ,ӦΪ0-4 */
#define     _CIM_OVR_ORGPRV        "450102"     /*  ������Ա��������Ӧ��Ȩ�� */

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
