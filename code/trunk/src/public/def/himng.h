/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : himng.h
 Author         : 谭亮
 Version        : V 1.0
 Date           : 2003-04-08
 Description    : 管理监控系统公用头文件
 Others         : 
 History        : 见下表

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
   01   2003-04-08  谭亮        创建
******************************************************************************/

#ifndef _HIMNG_H_
#define _HIMNG_H_

#ifndef _HI_VARARGS
#define _HI_VARARGS
#endif

#include "hiserver.h"
#include "hidll.h"
#include "hiafp.h"

#define ROOTNOD   "root" /* 报文根节点 */
#define RETCODNOD "RspCod"	/* 返回码节点名 */
#define RETMSGNOD "RspMsg"	/* 返回消息节点名 */
#define SUCRETCOD "000000"	/* 返回成功节点值 */
#define CONERRCOD "100501"  /* 通讯错误返回码 */
#define CANTDOERR "211405"  /* 不能处理返回码 */
#define MSGTYPHED "SCH" /* 消息类型消息头 */
#define RPMSGTYP  "rp" /* 响应消息类型 */
#define RQMSGTYP  "rq" /* 请求消息类型 */
#define RETCODHED "SSC" /* 返回码消息头 */
#define RETMSGHED "SEM" /* 返回消息头 */
#define AIMSVRHED "SDT" /* 目标服务器头 */
#define CMDCODHED "CMD" /* 命令交易码头 */
#define FNTCODHED "STC" /* 前置交易码头 */
#define INIPADDR  "SIP" /* IP地址头 */
#define IPADDRHED "OIP" /* IP地址头 */
#define PORTHED   "OPT" /* 端口头 */
#define MONMSGTYP "SYSMON"
#define SYSSTSSVR "S.STSSVR" /* 状态服务器名称 */
#define SYSMNGSVR "S.MNGSVR" /* 前置管理服务名称 */
#define CCAMNGSVR "CMNGMGP1" /* 前置管理接入服务器名称 */
#define PPPMNGSVR "P.MNGSVR" /* P端管理服务名称 */
#define SYSMONSVR "S.MONSVR" /* 前置监控服务名称 */
#define CPPMONSVR "CMNGMNP1" /* P端监控接入服务器名称 */
#define CCPMONSVR "CMNGMNP2" /* P端监控接入服务器名称 */
#define PPPMONSVR "P.MONSVR" /* P端监控服务名称 */
#define FNTTABNOD "FrontTab" /* 前置服务配置表节点名 */
#define SVRLSTROT "FrontTab" /* 服务启动配置表根节点 */
#define SVRLSTGRP "Group" /* 服务启动配置表组节点 */
#define SVRGRPNAM "name" /* 服务启动配置表组节点名字属性 */
#define SVRGRPSVR "Server" /* 服务启动配置表组节点服务节点 */
#define SVRSVRNAM "name" /* 服务启动配置表组节点服务节点名字属性 */
#define SVRSVRCFG "config_file" /* 服务启动配置表组节点服务节点配置文件属性 */
#define SVRCFGROT "Region" /* 服务配置文件根节点 */
#define SVRCFGSVR "Server" /* 服务配置文件服务配置节点 */
#define SVRCFGNAM "name" /* 服务配置文件服务配置节点名字属性 */
#define SVRCFGTRC "trace" /* 服务日志开关标志 */
#define SVRCFGTYP "type" /* 服务类型标志 */
#define DPOOLROOT "DBConnectionPool" /* 数据库连接池配置的根节点 */
#define DPOOLUSER "UserName" /* 数据库连接池用户名配置 */
#define DPOOLPWD  "Password" /* 数据库连接池密码配置 */
#define DPOOLSIZE "PoolSize" /* 数据库连接池大小配置 */
#define CLTSVRTYP "CCA" /* 接入服务器的类型 */
#define SVRSVRTYP "SCA" /* 接出服务器的类型 */
#define BTASVRTYP "BTA" /* 批量主控服务器的类型 */
#define OTASVRTYP "OTA" /* 业务主控服务器的类型 */
#define TPOOLROOT "ThreadPool" /* 线索连接池配置的根节点 */
#define TPOOLANUM "MaxWorkerThreads" /* 线索连接池最大工作线索 */
#define TPOOLINUM "MinWorkerThreads" /* 线索连接池最小工作线索 */
#define TPOOLPTIM "PollingTime" /* 线索连接池检查时间间隔 */
#define TPOOLDTUN "DynamicTuning" /* 线索连接池动态调整标志 */
#define TPOOLHLEV "HighLoadLevel" /* 线索连接池高负载水位 */
#define TPOOLHPOT "HighLoadTunePoint" /* 线索连接池高负载调整点 */
#define TPOOLHSTP "HighLoadTuneStep" /* 线索连接池高负载调整步幅 */
#define TPOOLLLEV "LowLoadLevel" /* 线索连接池低负载水位 */
#define TPOOLLPOT "LowLoadTunePoint" /* 线索连接池低负载调整点 */
#define TPOOLLSTP "LowLoadTuneStep" /* 线索连接池低负载调整步幅 */
#define QPAIRROOT "QueuePair" /* 队列配置根节点 */
#define QPAIRNAME "name" /* 队列名称 */
#define QPAIRLEN  "QueueLength" /* 队列个数 */
#define CRCINTVAL "Inteval" /* 冲正的轮循时间间隔 */
#define CRCHODDAY "HoldDays" /* 冲正的保存天数 */
#define CRCCLNTIM "cleanHour" /* 冲正的清除时间 */
#define CRCMAXFLX "MaxFlux" /* 冲正的最大流量 */
#define RDRINTVAL "Inteval" /* 重发的轮循时间间隔 */
#define RDRHODDAY "HoldDays" /* 重发的保存天数 */
#define RDRCLNTIM "cleanHour" /* 重发的清除时间 */
#define RDRMAXFLX "MaxFlux" /* 重发的最大流量 */
#define SCHINTVAL "itv" /* 定时触发的轮循时间间隔 */
#define SCHCONFIL "confile" /* 定时触发的配置文件 */
#define SCHMAXFLX "MaxRec" /* 定时触发的最大流量 */
#define DLLCTLROT "DllPriDataCtrl" /* 动态库配置节点名 */
#define DLLCTLPAR "Para" /* 动态库参数配置节点名 */
#define DLLPARNAM "name" /* 动态库参数配置节点属性名 */
#define CTLCFGAPP "Application" /* 应用配置根节点 */
#define CTLAPPTRN "Transaction" /* 交易配置根节点 */
#define CTLAPPNAM "name" /* 应用名配置属性 */
#define CTLTRNCOD "code" /* 交易码配置属性 */

#define MNG_FILNAM_LEN  64
#define MAX_LINE_LEN   256
#define MAX_WORD_LEN   32
#define MAX_LEN        4096
#define FIELD_NAME_LEN 32
#define TRN_CODE_LEN   6
#define SVR_NAME_LEN   8
#define MAX_CODE_NUM   200
#define GROUP_ID_LEN   3
#define APPID_LEN      3
#define APPNAM_LEN     128
/*
typedef struct _prvg_node {						// 权限信息节点
	char group_id[GROUP_ID_LEN + 1];			// 角色ID 
	int code_num;								// 交易数量 
	char code[MAX_CODE_NUM][TRN_CODE_LEN + 1];	// 交易码数组 
    struct _prvg_node *next;					// 下一个节点
} PrvgNode;
*/
/*存放应用ID和应用名称的结构*/
typedef struct _appinfo
{
	char	AppID[APPID_LEN+1];			/*应用ID*/
	char	AppNam[APPNAM_LEN+1];		/*应用名称*/
	struct  _appinfo *next;				/*指向下一个节点的指针*/

} AppInfo;

#ifdef	_MNG_EXTERN_
extern	XmlNode * gCfgRoot;
#else
XmlNode * gCfgRoot = NULL;
#endif

#ifdef	_HIMNG_LIB_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

/*
EXTERN XmlNode * gCfgRoot = NULL;

EXTERN PrvgNode *createPrvgNode();				// 创建权限信息节点
EXTERN void destroyPrvgNode(PrvgNode *);		// 销毁权限信息节点链表
EXTERN int printPrvgNode(PrvgNode *, char *);	// 显示权限信息节点链表 
EXTERN int getPrvgInfo(PrvgNode **);			// 获得权限信息 
EXTERN int makePrvgCheck(PrvgNode *, char *, char *);	//权限校验
*/
EXTERN int setDllSelf(void *);
EXTERN int setDllGlobal(void *);				/* 设置下一级动态库的全局变量 */

/* 取服务器列表文件名 */
EXTERN char *getServerTabFile();

/* 导出交易处理函数指针 */
//EXTERN void *getCodeFunc(XDllReg *, XmlNode *, char **, PrvgNode *);
EXTERN void *getCodeFunc(XDllReg *, XmlNode *, char **);
/* 根据输入产生一个发送消息 */
EXTERN Message * createCmdMsg(Message *, char *, char *, char *, char *);
/* 发送消息并且接收返回 */
EXTERN Message * sendCmdAndWaitRet(Message *, char *, char *, char *, char *);
/* 发送消息但是不等待返回 */
EXTERN int sendCmdAndNoWait(Message *, char *, char *, char *, char *);
/* 判断返回结果 */
EXTERN int judgeReturn(Message *, Message *);
/* 转换返回消息 */
EXTERN int convertRetToMsg(Message *, Message *);
/* 处理一般交易，同步或者异步 */
EXTERN int doSynNormalTran(Message *, char *, char *, char *, char *);
EXTERN int doAsynNormalTran(Message *, char *, char *, char *, char *);
/* 取服务名的一般交易处理，一个服务 */
EXTERN int doServerTran(Message *, XmlNode *, char *, char *, char *);
/* 取服务名的一般交易处理，多个服务 */
EXTERN int doServerControl(Message *, XmlNode *, char *, char *);
/* 判断是否为系统服务 */
EXTERN int isSystemServer(char *);
/* 取服务名并且转换为大写 */
EXTERN int getServerName(XmlNode *, char *);
/* 获得服务配置文件路径 */
EXTERN int getServerConfigFile(char *, char *, char *);
/* 获得服务配置节点 */
EXTERN XmlNode * getServerConfigNode(XmlDocument *, char *);

EXTERN XmlNode *convertRetToXml(Message *, Message *);
EXTERN int xmlCreateRoot(XmlNode **);					/* 创建一个根节点 */
EXTERN int createXmlReturn(XmlNode **, char *, char *);	/* 创建一个XML返回节点 */
/* 创建一个错误返回消息 */
EXTERN int createErrReturn(char *, int, Message *, char *, char *, char *, ...);
EXTERN int MessageReturn(Message *, XmlNode *);			/* 转换返回XML节点为返回消息 */
#undef	EXTERN

#endif	/* _HIMNG_H_ */
