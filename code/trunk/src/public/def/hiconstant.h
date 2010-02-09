/******************************************************************************


				Copyright (C),1998-2008,Hisuntech Co.,Ltd.

 File name		: hiconstant.h   
 Author			: LiangWenJian
 Version		: 1.0
 Date			: 2008-11-11
 Description	: 平台公共常量定义文件。      
 Others			: 无
 History		:

  No.	Date		Author		Modification
  ===	==========	========	==============================================
  001	2008-11-11	LiangWJ     创建
  
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

//日志是否监控
#define ICS_PLT_LOG_MONFLAG		"ics.plt.log_mon_flag"
//日志监控发送目标 MP--监控平台 DP--开发平台
#define ICS_PLT_LOG_RECVOBJ		"ics.plt.log_recvobj"
//日志监控平台IP地址
#define ICS_PLT_LOG_MONIP		"ics.plt.log_mon_ip"
//日志监控平台端口
#define ICS_PLT_LOG_MONPORT		"ics.plt.log_mon_port"
//日志级别
#define ICS_PLT_LOGLEVEL		"ics.plt.loglevel"

//服务器状态管理相关参数
//状态服务器无条件广播的时间间隔(广播目标是本地节点所有服务器)
#define	STS_ISSUE_ITV			"ics.plt.status_issue_interval"
//状态服务器定时监测本地服务器进程状态的时间间隔
#define	STS_CHECK_ITV			"ics.plt.status_check_interval"
//状态服务器有条件同步的时间间隔(有条件是指本地服务器发生变化,同步目标是其他节点的状态服务器)
#define	STS_SYNC_COND_ITV		"ics.plt.status_sync_condition_interval"
//状态服务器无条件同步的时间间隔(无条件是指本地服务器无变化,同步目标是其他节点的状态服务器)
#define	STS_SYNC_AUTO_ITV		"ics.plt.status_sync_auto_interval"
//状态服务器有条件广播的时间间隔(有条件是指任何服务器发生变化,广播目标是本地节点的所有服务器)
#define	STS_ISSUE_COND_ITV		"ics.plt.status_issue_condition_interval"
//状态服务器无条件广播的时间间隔(无条件是指任何服务器无变化,广播目标是本地节点的所有服务器)
#define	STS_ISSUE_AUTO_ITV		"ics.plt.status_issue_auto_interval"
//状态服务器同步服务器信息时,等待应答的超时时间
#define	STS_SYNC_WAIT_TIME		"ics.plt.status_sync_wait_time"
#define	STS_REGISTER_WAIT_TIME	"ics.plt.server_register_wait_time"

//状态服务器之间的心跳检测时间间隔
#define	STS_HEART_THROB_ITV		"ics.plt.status_heart_throb_interval"

#define	PUBBATINF_NAME			"ics.plt.pubbatinf_tablename"
#define ICS_PLT_SERVERNAME		"ics.plt.servername"
#define ICS_PLT_APPNAME			"ics.plt.appname"

#define	GET_PATH_WORKDIR	1	/* 在WORKDIR下取文件 */
#define	GET_PATH_APPDIR		2	/* 在APP_DIR下取文件 */
#define	GET_PATH_X			3	/* 先在APP_DIR下取文件，取不到再到WORKDIR下取 */

#define	LOG_MESSAGE_INIT_SIZE	"ics.plt.log_msg_init_size"
#define DEFAULT_LOG_MESSAGE_SIZE 10240

/*ICS系统数据库参数名*/
#define ICS_SYSDB_PRANAM    "ics.plt.sysdb"

/*8583配置文件*/
#define ICS_8583_CFG "ics.app.8583_cfg_file"

/*
 * 信息统计开关
 * on -- 打开
 * off - 关闭
 */
#define ICS_STATISTIC_SWITCH "ics.plt.statistic_switch"

/*
 * 交易TRACE保存目录
 */
#define ICS_TXN_TRACE_DIR "ics.app.txn_trace_dir"

/*
 * 交易通讯报文保存目录
 */
#define ICS_COMM_DATA_DIR "ics.app.comm_data_dir"

/*
 * 是否记录交易通讯报文
 * 0-不保存 1-保存(默认)
 */
#define ICS_IF_SAVE_COMM_DATA "ics.app.if_save_comm_data"

/*
 * 事务管理器日志开关
 */
#define ICS_PLT_TRA_LOG_SWITCH "ics.plt.tra.logswitch"
//默认冲正间隔
#define ICS_PLT_TRA_DEFAULT_INTERVAL "ics.plt.tra.default_interval"
//默认交易事务超时时间
#define ICS_PLT_TRA_DEFAULT_TRANTMOUT "ics.plt.tra.default_tran_timout"
//默认补偿交易超时时间
#define ICS_PLT_TRA_DEFAULT_EXPTRANTMOUT "ics.plt.tra.default_exp_tran_timout"
//默认最大尝试次数
#define ICS_PLT_TRA_DEFAULT_MAXFALTMS "ics.plt.tra.default_max_fault_times"
//系统core文件存放路径
#define ICS_PLT_COREDUMP_PATH "ics.plt.coredump_path"
//
#define ICS_PLT_SYSLOGGER "ics.plt.syslogger"

//消息发送
#define ICS_SEND_MSG_TIMEOUT_CTL "ics.plt.send_msg_timeout_control"

//内存池自动调节开关，默认打开(on,off)
#define ICS_PLT_MMG_TURNING_SWITCH "ics.plt.mmg.turning_switch"
//内存池低负载百分比(1-100)
#define ICS_PLT_MMG_LOW_LOAD_LEVEL "ics.plt.mmg.low_load_level"
//内存池低负载持续次数
#define ICS_PLT_MMG_LOW_LOAD_POINT "ics.plt.mmg.low_load_point"


//added by kixiong at 2009-1-22 15:00:28
//UDP监控发送相关参数
#define DEVELOP_PLTFORM "DP"
#define MON_PLTFORM		"MP"

//调试相关参数
#define ICS_PLT_CTL_DEBUG_SWITCH      "ics.app.debug_switch"
#define ICS_PLT_CTL_DEBUG_IP          "ics.app.trace_ip"
#define ICS_PLT_CTL_DEBUG_PORT                "ics.app.trace_port"

//内部通讯发送超时时间
#define	ICS_PLT_SEND_TIMEOUT		"ics.plt.send_timeout"

#endif /* _HI_CONSTANT_H_ */
