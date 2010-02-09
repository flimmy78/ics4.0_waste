/******************************************************************************


				Copyright (C),1998-2008,Hisuntech Co.,Ltd.

 File name		: hiconstant.h   
 Author			: LiangWenJian
 Version		: 1.0
 Date			: 2008-11-11
 Description	: ƽ̨�������������ļ���      
 Others			: ��
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2008-11-11	LiangWJ     ����
  
******************************************************************************/
#ifndef _HI_CONSTANT_H_
#define _HI_CONSTANT_H_

#define	NODE_ID_LEN			20
#define	MSGHEAD_SSC_LEN		6

#define	ENV_WORKDIR				"WORKDIR"
#define	ENV_LOCAL_ID			"ICS_LOCAL_ID"
#define	ENV_APP_DIR				"ics.app.dir"
#define	ENV_URL_DIR				"ics.plt.url_dir"
#define	URL_RCV_TIMEOUT			"ics.plt.url_receive_timeout"
#define	SHARE_FILE_MODE			"ics.plt.share_file_mode"

#define	PLT_LOG_MESSAGE_FILE	"ics.plt.log_message_file"
#define	APP_LOG_MESSAGE_FILE	"ics.app.log_message_file"
#define	LOG_ERR_PATH			"ics.plt.log_error_path"
#define	LOG_TRC_PATH			"ics.plt.log_trace_path"
#define	LOG_PATH_MODE			"ics.plt.log_path_mode"
#define	LOG_MAX_BUFFER			"ics.plt.log_max_buffer"
#define	LOG_MAX_SIZE			"ics.plt.log_max_size"
#define	LOG_DATETIME_FORMAT		"ics.plt.log_datetime_format"

//��־�Ƿ���
#define ICS_PLT_LOG_MONFLAG		"ics.plt.log_mon_flag"
//��־��ط���Ŀ�� MP--���ƽ̨ DP--����ƽ̨
#define ICS_PLT_LOG_RECVOBJ		"ics.plt.log_recvobj"
//��־���ƽ̨IP��ַ
#define ICS_PLT_LOG_MONIP		"ics.plt.log_mon_ip"
//��־���ƽ̨�˿�
#define ICS_PLT_LOG_MONPORT		"ics.plt.log_mon_port"
//��־����
#define ICS_PLT_LOGLEVEL		"ics.plt.loglevel"

//������״̬������ز���
//״̬�������������㲥��ʱ����(�㲥Ŀ���Ǳ��ؽڵ����з�����)
#define	STS_ISSUE_ITV			"ics.plt.status_issue_interval"
//״̬��������ʱ��Ȿ�ط���������״̬��ʱ����
#define	STS_CHECK_ITV			"ics.plt.status_check_interval"
//״̬������������ͬ����ʱ����(��������ָ���ط����������仯,ͬ��Ŀ���������ڵ��״̬������)
#define	STS_SYNC_COND_ITV		"ics.plt.status_sync_condition_interval"
//״̬������������ͬ����ʱ����(��������ָ���ط������ޱ仯,ͬ��Ŀ���������ڵ��״̬������)
#define	STS_SYNC_AUTO_ITV		"ics.plt.status_sync_auto_interval"
//״̬�������������㲥��ʱ����(��������ָ�κη����������仯,�㲥Ŀ���Ǳ��ؽڵ�����з�����)
#define	STS_ISSUE_COND_ITV		"ics.plt.status_issue_condition_interval"
//״̬�������������㲥��ʱ����(��������ָ�κη������ޱ仯,�㲥Ŀ���Ǳ��ؽڵ�����з�����)
#define	STS_ISSUE_AUTO_ITV		"ics.plt.status_issue_auto_interval"
//״̬������ͬ����������Ϣʱ,�ȴ�Ӧ��ĳ�ʱʱ��
#define	STS_SYNC_WAIT_TIME		"ics.plt.status_sync_wait_time"
#define	STS_REGISTER_WAIT_TIME	"ics.plt.server_register_wait_time"

//״̬������֮����������ʱ����
#define	STS_HEART_THROB_ITV		"ics.plt.status_heart_throb_interval"

#define	PUBBATINF_NAME			"ics.plt.pubbatinf_tablename"
#define ICS_PLT_SERVERNAME		"ics.plt.servername"
#define ICS_PLT_APPNAME			"ics.plt.appname"

#define	GET_PATH_WORKDIR	1	/* ��WORKDIR��ȡ�ļ� */
#define	GET_PATH_APPDIR		2	/* ��APP_DIR��ȡ�ļ� */
#define	GET_PATH_X			3	/* ����APP_DIR��ȡ�ļ���ȡ�����ٵ�WORKDIR��ȡ */

#define	LOG_MESSAGE_INIT_SIZE	"ics.plt.log_msg_init_size"
#define DEFAULT_LOG_MESSAGE_SIZE 10240

/*ICSϵͳ���ݿ������*/
#define ICS_SYSDB_PRANAM    "ics.plt.sysdb"

/*8583�����ļ�*/
#define ICS_8583_CFG "ics.app.8583_cfg_file"

/*
 * ��Ϣͳ�ƿ���
 * on -- ��
 * off - �ر�
 */
#define ICS_STATISTIC_SWITCH "ics.plt.statistic_switch"

/*
 * ����TRACE����Ŀ¼
 */
#define ICS_TXN_TRACE_DIR "ics.app.txn_trace_dir"

/*
 * ����ͨѶ���ı���Ŀ¼
 */
#define ICS_COMM_DATA_DIR "ics.app.comm_data_dir"

/*
 * �Ƿ��¼����ͨѶ����
 * 0-������ 1-����(Ĭ��)
 */
#define ICS_IF_SAVE_COMM_DATA "ics.app.if_save_comm_data"

/*
 * �����������־����
 */
#define ICS_PLT_TRA_LOG_SWITCH "ics.plt.tra.logswitch"
//Ĭ�ϳ������
#define ICS_PLT_TRA_DEFAULT_INTERVAL "ics.plt.tra.default_interval"
//Ĭ�Ͻ�������ʱʱ��
#define ICS_PLT_TRA_DEFAULT_TRANTMOUT "ics.plt.tra.default_tran_timout"
//Ĭ�ϲ������׳�ʱʱ��
#define ICS_PLT_TRA_DEFAULT_EXPTRANTMOUT "ics.plt.tra.default_exp_tran_timout"
//Ĭ������Դ���
#define ICS_PLT_TRA_DEFAULT_MAXFALTMS "ics.plt.tra.default_max_fault_times"
//ϵͳcore�ļ����·��
#define ICS_PLT_COREDUMP_PATH "ics.plt.coredump_path"
//
#define ICS_PLT_SYSLOGGER "ics.plt.syslogger"

//��Ϣ����
#define ICS_SEND_MSG_TIMEOUT_CTL "ics.plt.send_msg_timeout_control"

//�ڴ���Զ����ڿ��أ�Ĭ�ϴ�(on,off)
#define ICS_PLT_MMG_TURNING_SWITCH "ics.plt.mmg.turning_switch"
//�ڴ�ص͸��ذٷֱ�(1-100)
#define ICS_PLT_MMG_LOW_LOAD_LEVEL "ics.plt.mmg.low_load_level"
//�ڴ�ص͸��س�������
#define ICS_PLT_MMG_LOW_LOAD_POINT "ics.plt.mmg.low_load_point"


//added by kixiong at 2009-1-22 15:00:28
//UDP��ط�����ز���
#define DEVELOP_PLTFORM "DP"
#define MON_PLTFORM		"MP"

//������ز���
#define ICS_PLT_CTL_DEBUG_SWITCH      "ics.app.debug_switch"
#define ICS_PLT_CTL_DEBUG_IP          "ics.app.trace_ip"
#define ICS_PLT_CTL_DEBUG_PORT                "ics.app.trace_port"

//�ڲ�ͨѶ���ͳ�ʱʱ��
#define	ICS_PLT_SEND_TIMEOUT		"ics.plt.send_timeout"

#endif /* _HI_CONSTANT_H_ */
