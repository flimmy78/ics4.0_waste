/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : mgpmain.h
 Author         : 谭亮
 Version        : V 1.0
 Date           : 2003-04-12
 Description    : 管理监控服务器上管理服务程序头文件
 Others         : 
 History        : 见下表

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
   01   2003-04-12  谭亮        创建
******************************************************************************/

#ifndef _MGPMAIN_H_
#define _MGPMAIN_H_

#include "himng.h"

#define PPPAIMROT "SomamAim"	/* P端管理服务配置文件根节点 */
#define PPPMNGROT "SomamMan"	/* P端管理服务配置文件根节点 */
#define LOGINCODE "090000"		/* 登陆交易码 */
#define GETIPCODE "090912"		/* 取服务器IP交易码 */


#define VALUE_LEN      32
#define MEAN_LEN       128
#define GROUP_NAME_LEN 32
#define USER_ID_LEN    6
#define USER_NAME_LEN  32
#define USER_SEX_LEN   1
#define USER_PWD_LEN   10
#define TEXT_LEN	  1024	 
#define BUSID_LEN      3 
#define BUSNAM_LEN     60
#define IP_LEN         15
#define PORT_LEN       6
#define TIMEOUT_LEN       6

typedef struct _aim_node {						/* 路由节点 */
	char * aim_id;								/* 目标机器的代号 */
	char * aim_ip;								/* 目标机器的IP */
	long aim_port;								/* 目标机器的端口 */
	char * ftp_user;							/* 用于后台FTP取日志文件的用户名*/
	char * password;							/* 用于后台FTP取日志文件的用户密码*/
    struct _aim_node * next;					/* 下一个节点 */
} AimNode;

/*
typedef struct _timeout_node {						// 交易超时时间设置节点
	char * code;								// 交易码
	char * timeout;								// 超时时间
    struct _timeout_node * next;				// 下一个节点
} TimeOutNode;
*/

extern AimNode * createAimNode();				/* 创建路由节点 */
extern void destroyAimNode(AimNode *);			/* 销毁路由节点链表 */
extern int printAimNode(AimNode *, char *);		/* 显示路由节点 */
extern int setAimInfo(XmlNode *);				/* 获取路由信息 */
/* 获得目标服务器IP和Port */
extern int getAimInfo(char * aim, char *ip, char *port, char *username, char *password);	
extern int doLogin(Message *, XmlNode *);		/* 处理登陆交易 */
extern int writeLog(Message *, XmlNode *);		/* 记录日志 */

#endif	/* _MGPMAIN_H_ */
