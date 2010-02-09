/********************************************************************

		Copyright (C),1998-2003,Hisuntech Co.,Ltd.

	File name:			// pftclifil_gz.c
	Author:				 // WangXiaoDong
	Version:				// 1.0
	Date:					 // 20030327
	Description:		// 这是外部通讯模块中服务端同步短/长连接源文件。
	Others:				 // 目前只考虑一条连接
	Function List:	// 主要函数列表，每条记录应包括函数名及功能简要说明
										 serverSyncIn
										 serverSyncOut
										 initChannel
										 closeChannel
										 thread_main
										 syncSendRequest
	History:				// 修改历史记录列表，每条修改记录应包括修改日期、
									// 修改者及修改内容简述
		1. Date:			
			 Author:	 
			 Modification:
		2. ...
 No.	 Date				Author			Modification
===	 ==========	========		==============================================
001		2007-06-15	WangXF			修改
			注：针对财税系统文件接口需求，通讯采用短连接，一次连接多次交互信息，
			本通讯接口通过消息头SNC判断是否保留连接。
			修改通讯包最大长度。

********************************************************************/
#include "ecnmain.h"
#include "mac3des_api.h"

#define LONG_CONN		 1
#define SHORT_CONN		0

#define MAX_CONN			50
#define MAX_DAT_LEN	 512*1024

int						 _ListenFD = -1;
CONN_PARAM			_ConnPara;
pthread_t			 * _MainThreadRec = NULL;
MemoryPool			* _FDsList = NULL;
QuickSearchList * _IPsList = NULL;
XmlNode				 * _IPsTable = NULL;
int				_EncFlg = 0;
char			_FP[256] = "/app/ics/dat/pft/recv/"; /*文件存放路径*/
/********************************************************************
	Function:			 // initConnDesp
	Description:		// 初始化CONN_DESP结构
	Calls:					// 
	Called By:			// initChannel
	Table Accessed: // 
	Table Updated:	// 
	Input:					// arg:参数	
	Output:				 //
	Return:				 // 无
	Others:				 // 
********************************************************************/
void initConnDesp(void * arg)
{
	
		CONN_DESP * fdnode = (CONN_DESP *)arg;
		memset(fdnode, 0, sizeof(CONN_DESP));	
	
}
/********************************************************************
	Function:			 // peerCloseMonitor
	Description:		// 清理超时的同步连接匹配节点
	Calls:					// 
	Called By:			// initChannel
	Table Accessed: // 
	Table Updated:	// 
	Input:					// arg:参数	
	Output:				 //
	Return:				 // 无
	Others:				 // 
********************************************************************/
void * peerCloseMonitor(void * arg)
{
		int			 i,iTimeOut;
		CONN_DESP * fdnode = NULL;
		struct		timeval ct;
		struct		timezone zone;
		char			aKey[KEY_LEN + 1];
		long			iKey;

		iTimeOut	= (int)arg;
		
		thdSetCancelType(PTHREAD_CANCEL_DEFERRED, NULL);
		thdSetCancelState(PTHREAD_CANCEL_ENABLE, NULL);

		while ( 1 )
		{
				/*
				 * 加入线索退出点
				 */
				thdTestCancel();

				waitNSecond( 1*60 );
				gettimeofday(&ct, &zone);
				for (i = 0; i < _FDsList->cursize; i++)
				{

						if (_FDsList->allocedpos[i] == 1)
						{
								fdnode = (CONN_DESP *)_FDsList->addr[i];
								
								memset(aKey,0x0,sizeof(aKey));
								memcpy(aKey,fdnode->key,KEY_LEN - 6);
								iKey = atol( aKey );
								
								if ((ct.tv_sec - iKey) > iTimeOut)
								{
					usfErrlog("清除超时socket(%s.%d).[%d][%s][%ld][%ld]", fdnode->ipAddr, iTimeOut, i, fdnode->key, iKey, ct.tv_sec);
					del_conn_node(i);
								}
						}
				}
		}
}


/********************************************************************
	Function:			 // initChannel
	Description:		// 服务启动时运行的初始化函数，执行装载IP表及一些参数
	Calls:					// loadIPTable(char * filename) 装载ip表的函数
	Called By:			// 被服务框架调用?
	Table Accessed: // 
	Table Updated:	// 
	Input:					// argc:参数个数
									// argv:参数数组,包括参数：连接类型
									//												 配置文件名称
									//												 最大连接数
									//												 前置标志长度
									//												 最大超时时间
	Output:				 //
	Return:				 // 0:成功 !0:失败
	Others:				 // 
********************************************************************/
int initChannel(int argc,char **argv)
{
		pthread_t pTid;
		int			 ret;
		int			 iMaxConn;
		int			 iTimeOut = 0;

		//sprintf("%s_CHL.err", _PubRuntimeEnv->svr_name);
		if (argc < 2)
		{
			usfErrlog("[%d]请输入参数:连接类型,IP配置文件名,[最大连接数],[前置标志长度],[最大超时时间],[加密标志]",ERRCODE+1);
			 	return(-1);

		}
		memset(&_ConnPara, 0x0, sizeof(CONN_PARAM));
 
	/*
	 * 设置本地IP地址
	 * Added by liangwj in 20050127
	 */
		hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
		/*
		 * argv[0]:连接类型 0:短连接 1:长连接
		 * argv[1]:ip配置文件名称
		 * argv[2]:最大连接数
		 * argv[3]:前置长度的长度			
		 * argv[4]:最大超时时间
		 */


		_ConnPara.syncConType = SHORT_CONN;


		if (strlen(argv[1]) <= FILENAME_LEN )
		{
				 strcpy(_ConnPara.ipConFile,argv[1]);
		}
		else
		{
				 usfErrlog("[%d]配置文件参数超长", ERRCODE+2);
				 return(-1);
		}

		if (argc >= 3)
		{
				 iMaxConn = atoi( argv[2] );
				 if (iMaxConn <= 10)
				 {
						 iMaxConn = MAX_CONN;
				 }
		}
		else
		{
				 iMaxConn = MAX_CONN;
		}

		if (argc <	4)
		{
				_ConnPara.havePreLen = NO_PRELEN; /* 没有前置长度	*/
		}
		else 
		{
				_ConnPara.havePreLen = HAVE_PRELEN;/* 有前置长度	*/
				_ConnPara.preLenLen = atoi(argv[3]);
				if (_ConnPara.preLenLen <= 0)
				{
						 _ConnPara.havePreLen = NO_PRELEN; /* 没有前置长度	*/
				}
			 
		}

		hdelbothspace(argv[1]);
		if (strlen(argv[1]) > 0 && ecnInitIpList(argv[1], &_IPsList, &_IPsTable) < 0)
		{
				usfErrlog("[%d]装载IP配置文件[%s]失败", ERRCODE + 3, argv[1]);
				return( -1 );
		}

		_FDsList = mplCreate(10, iMaxConn, sizeof(CONN_DESP), 1, 1, initConnDesp);
		if ( _FDsList == NULL )
		{
				usfErrlog("[%d]创建同步连接匹配内存表失败", ERRCODE+4);
				return(-1);
		}

		/*
		 * 同步短连接才可以用超时判断
		 */
	if ( argc >= 5 )
	{
		iTimeOut = atoi(argv[4]);
		if (iTimeOut <= 0)
		{
			iTimeOut = 120;
		}
	}
	else
	{
		iTimeOut = 120;
	}

	ret = thdCreate(&pTid, NULL, peerCloseMonitor, (void *)iTimeOut);
	if (ret)
	{
		usfErrlog("[%d]创建同步连接轮询线索失败", ERRCODE + 5);
		return(-1);
	}


	if (argc > 5)
	{
		_EncFlg = atoi(argv[5]);
	}

		usfTraceX("[10]连接类型[%s] 配置文件[%s] 最大连接数[%d] 前置标志[%d] 前置长度[%s] 最大超时时间[%d] 加密标志[%d]", argv[0],argv[1],iMaxConn,_ConnPara.havePreLen,argv[3],iTimeOut, _EncFlg);

		return(0);
}

/********************************************************************
	Function:			 // closeChannel
	Description:		// 服务停止时运行的函数，执行释放IP表及一些资源
	Calls:					// freeIPTable(char * filename) 释放ip表的函数
	Called By:			// 被服务框架调用
	Table Accessed: // 
	Table Updated:	// 
	Input:					// 
									//
	Output:				 //
	Return:				 //
	Others:				 // 
********************************************************************/
void closeChannel()
{
		int					iCount;
		/*
		 * 释放主线索数组中的所有线索
		 */
		
		
		for (iCount = 0; iCount < _ConnPara.thread_num; iCount++)
		{
				 thdCancel(_MainThreadRec[iCount]);
		}

		if (_MainThreadRec != NULL )
		{
				 free(_MainThreadRec);
				 _MainThreadRec = NULL;
		}

		/*
		 * 释放同步连接登记结构表
		 */
		mplDestroy(_FDsList);
		/*
		 * 释放IP配置结构表和关闭监听句柄
		 */
		ecnFreeIpList(_IPsList, _IPsTable);
		hsocketclose(_ListenFD);

}
/********************************************************************
	Function:			 // serverSyncIn
	Description:		// 服务启动后接收渠道请求数据的入口函数，主要负责监听
	Calls:					// thread_main
									// syncSendRequest
	Called By:			// 被服务框架调用?
	Table Accessed: // 
	Table Updated:	// 
	Input:					// argc:参数个数
									// argv:参数数组
									// tid :线索id
	Output:				 //
	Return:				 // 0:成功 !0:失败
	Others:				 // 
********************************************************************/
int serverSyncIn(int argc,char **argv,pthread_t * tid)
{
		pthread_attr_t pAttr;
		pthread_t			thread_id;
		int						iCount;
		void					 * thread_main(void *);


		if (argc < 2)
		{
			 usfErrlog("[%d]请输入参数:消息类型、端口号、[主线索数目]", ERRCODE + 20);
			 return(-1);
		}
		
		if (strlen(argv[0]) <= MSGLEN)
		{
				strcpy(_ConnPara.msgType,argv[0]);
		}
		else
		{
				usfErrlog( "[%d]消息类型参数超长", ERRCODE+21);
				return(-1);
		}
		
		if ( atoi(argv[1]) > 0)
		{
				_ConnPara.port = atoi(argv[1]);
		}
		else
		{
				usfErrlog( "[%d]端口号必须为数字", ERRCODE + 22);
				return(-1);
		}

		if (argc == 2)	 
		{
			_ConnPara.thread_num = 5;
		}
		else
		{ 
				_ConnPara.thread_num = atoi(argv[2]);
				if (_ConnPara.thread_num <= 0)
				{
						 _ConnPara.thread_num = 5;
				}
		}

		usfTraceX("[10]消息类型[%s]端口号[%d]线索数[%d]",_ConnPara.msgType, _ConnPara.port, _ConnPara.thread_num);

		_ListenFD = hsocketbindlisten(_ConnPara.port);
		if (_ListenFD < 0)
		{
				usfErrlog( "[%d]监听网络连接失败", ERRCODE + 23);
				return(-1);
		}


		if (thdInitAttr(&pAttr) != 0)
		{
				usfErrlog( "[%d]初始化线索属性失败", ERRCODE + 24);
				return(-1);
		}

		thdSetDetachState(&pAttr, PTHREAD_CREATE_UNDETACHED);
		thdSetScope(&pAttr, PTHREAD_SCOPE_SYSTEM);

		_MainThreadRec = (pthread_t *)malloc(_ConnPara.thread_num * sizeof(pthread_t));
		if (_MainThreadRec == NULL)
		{
				usfErrlog("[%d]申请主线索ID内存失败", ERRCODE+25);
				thdDestroyAttr(&pAttr);
				return(-1);
		}

		for(iCount = 0; iCount < _ConnPara.thread_num; iCount++)
		{
				if (thdCreate(&thread_id, &pAttr, thread_main, NULL) != 0)
				{
						 usfErrlog("[%d]主线索创建失败", ERRCODE + 26);
						 thdDestroyAttr(&pAttr);
						 if (_MainThreadRec != NULL)
						 {
								 free(_MainThreadRec);
								 _MainThreadRec = NULL;
						 }
						 return(-1);
				}

				/*
				 * 保存主线索的id，以便于服务关闭时释放线索资源
				 */

				_MainThreadRec[iCount] = thread_id;
		}
				 
		thdDestroyAttr(&pAttr);
	 
		return(0);
}
/********************************************************************
	Function:			 // thread_main
	Description:		// 接收渠道连接请求，分配线索接收请求数据
	Calls:					// syncSendRequest
	Called By:			// serverSyncIn
	Table Accessed: // 
	Table Updated:	// 
	Input:					// args :空
									//
	Output:				 //
	Return:				 // 无
	Others:				 // 
********************************************************************/
void * thread_main(void * args)
{
		CONN_DESP					 connDesp;
		struct	sockaddr_in cli_addr;
		char								ipAddr[IPADDR_LEN+1];
		int								 sockFd = -1;
		socklen_t					 iCliLen;
		struct	timeval		 tv;
		char								key[KEY_LEN +1];
		int								 iNewSlot;
	 
		for (;;)
		{
				/*
				 * 线索退出点
				 */
				thdTestCancel();
	 		 	memset((char *)&cli_addr, 0, sizeof(struct sockaddr_in));
 
				/*
				 * 接受连接请求
				 */
				iCliLen = sizeof(cli_addr);
				sockFd = accept(_ListenFD, (struct sockaddr *)&cli_addr, &iCliLen);

				if (sockFd < 0)
				{
						continue;	
				}
				/*
				 * 取当时的时间，精确到毫秒
				 */
				memset(key, 0x0, sizeof(key));
				gettimeofday(&tv, NULL);
				sprintf(key, "%10d%6d", tv.tv_sec, tv.tv_usec);
					
				/*
				 * 设置连接描述信息
				 */				
				connDesp.sockfd = sockFd;
				sprintf(ipAddr,"%s", inet_ntoa(cli_addr.sin_addr));
				strcpy(connDesp.key , key);
				strcpy(connDesp.ipAddr, ipAddr);

				/*
				 * 进行IP合法性检查
				 */
				if (ecnCheckIp(_IPsList, connDesp.ipAddr))
				{
						usfErrlog( "[%d]注意:有非法Ip[%s]试图连接", ERRCODE + 32, connDesp.ipAddr);
						hsocketclose(sockFd);
						continue;
				}

				/*
				 * 保存连接匹配值
				 * 由于接口mplMalloc已经自加锁了，所以外面无需再加锁
				 */

				if (( iNewSlot = add_conn_node(&connDesp)) < 0 )
				{
						hsocketclose(sockFd);
						continue;
				}
				connDesp.slot = iNewSlot;
				syncSendRequest(&connDesp);
		}
		thdExit(NULL);
}

/********************************************************************
	Function:			 // syncSendRequest
	Description:		// 接收请求数据
	Calls:					// 
	Called By:			// thread_main
	Table Accessed: // 
	Table Updated:	// 
	Input:					// args:连接描述信息结构CONN_DESP
									//
	Output:				 //
	Return:				 // 
	Others:				 // 
********************************************************************/
int syncSendRequest(CONN_DESP * desp)
{
		char				* recv_buf = NULL;
		int				 recv_len;
		char				* p_buf = NULL;
		int				 buf_len;
		int				 result;
	int			optval;
		Message		 *msg;
		Message		 *rpmsg;
		char				tmp_str[20];
	long		stime;
	int			rc;
	char			* file_head_info;
	int			file_head_len;
	char		file_head_name[128];
	int			pos = 0;
	char				aContFlag[2];
	char		file_name[128], file_len[16];
	int			i = 0;
			

	optval = 1;
	recv_len = sizeof(optval);
	setsockopt(desp->sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, recv_len);

	p_buf = (char *)malloc(MAX_DAT_LEN+1);
	if (p_buf == NULL)
	{
		usfErrlog("申请内存空间失败![%d]", MAX_DAT_LEN+1);	
		return (-1);
	}
 
		/*
		 *	区分长短连接及带前置长度/不带前置长度
		 */
		for (;;)
		{
		result = hsocketselect(TIME_OUT, desp->sockfd);
		if (result < 0) 
		{
			usfErrlog("监听网络信号失败, 通讯连接已关闭! IP=[%s]", desp->ipAddr);	
			del_conn_node(desp->slot);
			break;
		}
		 
		if (result == 0)	/* 在超时时间内没有数据到达 */
		{
						if (_ConnPara.syncConType == LONG_CONN)
						{
								continue;
						}
						else
						{
							usfErrlog("接收数据等待超时! IP=[%s]", desp->ipAddr);	
								del_conn_node(desp->slot);
								break;
						}
		}

		recv_len = -1;
		
		/* 没有前置长度*/
		recv_buf = (char *)malloc(MAX_DAT_LEN + 1);			 	
		if (recv_buf != NULL)
		{
			memset( recv_buf, '\0', sizeof(recv_buf));
			/*recv_len = recv(desp->sockfd, recv_buf, MAX_DAT_LEN, 0);
			*/
			recv_len = read(desp->sockfd, recv_buf, MAX_DAT_LEN);
			
			memset(tmp_str,0x00,sizeof(tmp_str));
			memcpy(tmp_str,recv_buf+11,8);
			if ( recv_len != (19 + atoi(tmp_str)) )
			{
				usfErrlog("继续接收[接收长度=%d][信息体长度+19=[%d]\n", recv_len,atoi(tmp_str));
				while( 1 )
				{
					i = 0;
					usfErrlog("开始继续接收！！！\n");	
					i = read(desp->sockfd, recv_buf+recv_len, MAX_DAT_LEN);
					usfErrlog("继续接收[%s][%d]\n", recv_buf+recv_len,i);
					if ( i<= 0 )
						break;
					recv_len += i;
					if( recv_len == (19 + atoi(tmp_str)) )
						break;
				}
			}
			
			usfErrlog("接收完毕[%s][%d]\n", recv_buf,recv_len);	
		}

		if ( (recv_len <= 0) || (i < 0) )
		{
			usfErrlog("接收请求数据失败, 通讯连接已关闭! IP=[%s]", desp->ipAddr);	
			
			free(recv_buf);
			recv_buf = NULL;
			del_conn_node(desp->slot);
			
			break;
		}
		
		/* 解密处理 add by liangwj in 20040618 */
		if (_EncFlg == 1)
		{
			rc = mac3des_api(DECODE, recv_buf, &recv_len, p_buf, &buf_len);
			if (rc < 0)
			{
				usfErrlog("解密处理失败!IP=[%s] 数据=[%d][%s]", desp->ipAddr, recv_len, recv_buf);
			
				free(recv_buf);
				recv_buf = NULL;
				del_conn_node(desp->slot);
			
				break;
			 }
		 }

			 /*
				*	创建消息，发往左边的请求队列
				*/

		msg = (Message *)usfCreateMsg(_ConnPara.msgType);
		if (msg) 
		{
			if (_EncFlg == 1)
			{
				usfSetMsgData(msg, p_buf+14, buf_len-14);
				/* NID为加解密标识，需要保存，在响应时加密用 */
				/* add by liangwj in 20040618								*/
				usfAddMsgHeadValue(msg, "NID", p_buf+6, 8);
			}
			else
			{
				/*写入消息前过滤掉两位前导符*/
				usfSetMsgData(msg, recv_buf+2, recv_len - 2);
			}
			usfAddMsgHeadValue(msg, "SIP", desp->ipAddr, strlen(desp->ipAddr) );
			usfAddMsgHeadValue(msg, "SCH", "rq", 2);
			memset(tmp_str, 0, sizeof(tmp_str));
			sprintf(tmp_str, "%d", desp->slot);
			usfAddMsgHeadValue(msg, "SFD", tmp_str, strlen(tmp_str) );
			usfAddMsgHeadValue(msg, "SKY", desp->key, strlen(desp->key));
			stime = time(NULL);
			sprintf(tmp_str, "%ld", stime);
			usfAddMsgHeadValue(msg, "STM", tmp_str, strlen(tmp_str));
				
			usfTraceX("请求编号=[%s] 接收数据成功! IP=[%s]\n数据=[%d][%s]", msg->request_id, desp->ipAddr, recv_len, recv_buf);

			if (usfSendRequest(msg))
			{
				usfErrlog("发送请求消息失败!");
				usfDestroyMsg(msg);
				del_conn_node(desp->slot);
				
			}
		}
		else 
		{
			usfErrlog("创建请求消息失败! IP=[%s]\n数据=[%d][%s]", desp->ipAddr, recv_len, recv_buf);
			del_conn_node(desp->slot);
		}
		/*保存文件名和文件长度*/
		if ( strncmp(msg->msg_text,"shead",5) == 0 )
		{ 
			memset(tmp_str,0x00,sizeof(tmp_str));
			memcpy(tmp_str,msg->msg_text+9,8);
			
			file_head_len = atoi(tmp_str);
			file_head_info = (char *)malloc(file_head_len + 1);			 	
			if ( file_head_info == NULL )
			{
				usfErrlog("申请内存失败[%d]", file_head_len+1);
				free(recv_buf);
				recv_buf = NULL;
				del_conn_node(desp->slot);
				break;	
			}
		
			memset(file_head_info,0x00,sizeof(file_head_info));
			memset(file_name,0x00,sizeof(file_name));
			memset(file_len ,0x00,sizeof(file_len ));

			memcpy(file_head_info,msg->msg_text+17,file_head_len);
		
			for (pos=0;pos<file_head_len;pos++)
			{
				if ( file_head_info[pos] != '|')
					file_head_name[pos] = file_head_info[pos];
				else
					break;
			}
			strcpy(file_name,file_head_name);
			memcpy(file_len,file_head_info+pos+1,file_head_len-strlen(file_head_name)-1);
		}
		
		if ( strncmp(msg->msg_text,"login",5) != 0 )
		{
			usfAddMsgHeadValue(msg, "FHN", file_name,strlen(file_name));
			usfAddMsgHeadValue(msg, "FHL", file_len,strlen(file_len)); 
		}		
		free(recv_buf);
		recv_buf = NULL;

		if ( strncmp(msg->msg_text,"sover",5) == 0 )
		{
			usfTraceX("文件接收完毕,退出接收线程");
			break;		
		}
		if ( strncmp(msg->msg_text,"sfile",5) == 0 )
		{
			usfErrlog("请求编号=[%s] 数据写入文件[%s|%d]!", msg->request_id,file_name,msg->msg_size -17);

			if ( writebinfile(file_name, msg->msg_text+17, msg->msg_size-17) != 0 )
			{
				usfErrlog("请求编号=[%s] 数据写入文件失败!", msg->request_id);
			}
		}
		
		}

	free(p_buf);
	if ( file_head_info != NULL )
		free(file_head_info);
	return (0);
}
/********************************************************************
	Function:			 // serverSyncOut
	Description:		// 服务启动后发送应答数据给渠道的入口函数
	Calls:					// 
	Called By:			// 被服务框架调用
	Table Accessed: // 
	Table Updated:	// 
	Input:					// msg:应答消息包
									//
	Output:				 //
	Return:				 // 0：成功 !0:失败
	Others:				 // 
********************************************************************/
int serverSyncOut(Message *msg)
{
		int				 iLen;
		char				aTmp[20];
		char				aNetId[6+1];
		char				aIpAddr[IPADDR_LEN + 1];
		char				aKey[KEY_LEN	+ 1];
		char				aContFlag[2];
		char				* p_buf = NULL;
		char				* p_tmp = NULL;
		int				 buf_len;
		int				 tmp_len;
		int				 size;
		int				 iSockFd;
		int				 result;
		int				 iSendLen;
		int				 iSlot;
		char				* send_buf = NULL;
	 
	/*
	 *	取socked 登记的位置号，ip地址，key值和后续包标志
	 */
	memset(aTmp, 0x0, sizeof(aTmp)); 	
	if (usfGetMsgHeadValue(msg, "SFD", aTmp) < 0 )
	{
		usfErrlog( "请求编号=[%s] 取消息头(SFD)失败!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);	
	}
		
	iSlot = atoi(aTmp);

	memset(aIpAddr, 0x0, sizeof(aIpAddr));
	if (usfGetMsgHeadValue(msg, "SIP", aIpAddr) < 0 )
	{
		usfErrlog( "请求编号=[%s] 取消息头(SIP)失败!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
	}
		
	memset(aKey, 0x0, sizeof(aKey));
	if (usfGetMsgHeadValue(msg, "SKY", aKey) < 0 )
	{
		usfErrlog( "请求编号=[%s] 取消息头(SKY)失败!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
	}

	/*
	 *	匹配原连接,未匹配到，不能关闭socket描述符
	 */
	if ((iSockFd = check_conn_node(iSlot, aIpAddr, aKey)) < 0 )
	{
		usfErrlog( "请求编号=[%s] 交易返回超时，原通讯连接已关闭!", msg->request_id);
		usfDestroyMsg(msg);	

		return(-1);	
	}
		
	/* 加密处理 add by liangwj in 20040618 */
	if (_EncFlg == 1)
	{
		memset(aNetId, 0x0, sizeof(aNetId));
		if (usfGetMsgHeadValue(msg, "NID", aNetId) < 0 )
		{
			usfErrlog( "请求编号=[%s] 取消息头(NID)失败!", msg->request_id);
			usfDestroyMsg(msg);
			del_conn_node(iSlot);
			 
			return (-1);
		}
		p_buf = (char *)malloc(MAX_DAT_LEN+1);
		p_tmp = (char *)malloc(MAX_DAT_LEN+1);
		if (p_buf == NULL || p_tmp == NULL)
		{
			usfErrlog( "请求编号=[%s] 申请内存失败! 大小=[%d]", msg->request_id, MAX_DAT_LEN*2);
			usfDestroyMsg(msg);
			if (p_buf != NULL)
			{
				free(p_buf);
			}
			if (p_tmp != NULL)
			{
				free(p_tmp);
			}
				 
			del_conn_node(iSlot);
			return (-1);
		}
		hsnprintf(p_tmp, MAX_DAT_LEN+1, "%06d%8.8s", msg->msg_size, aNetId);
		memcpy(p_tmp+14, msg->msg_text, msg->msg_size);
		tmp_len = msg->msg_size + 14;
		*(p_tmp+tmp_len) = '\0';
		result = mac3des_api(ENCODE, p_tmp, &tmp_len, p_buf, &buf_len);
		if (result < 0)
		{
			free(p_buf);
	 		free(p_tmp);
			usfErrlog("请求编号=[%s] 加密处理失败! rc=[%d]", msg->request_id, result);
			usfDestroyMsg(msg);
			del_conn_node(iSlot);
			return (-1);
		}
		free(p_tmp);
		size = buf_len;
	}
	else
	{
		size	= msg->msg_size;
	}	

	send_buf = (char *)malloc(size + 2 + 1);
	if (send_buf != NULL)
	{
		memset( send_buf, 0x0, sizeof( send_buf ));
	}
	else
	 {
		usfErrlog("请求编号=[%s] 申请内存空间失败!", msg->request_id);
		hsocketclose(iSockFd);
		del_conn_node(iSlot);
								
		return(-1);
	}
	if (_EncFlg == 1)
	{
		sprintf(send_buf,"%c%c%s",0xef,0x14,p_buf);

		/*iLen = hsocketwrite(iSockFd, p_buf, size);*/
		iLen = write(iSockFd, send_buf, size + 2);
		free(p_buf);
	}
	else
	{

		/*iLen = hsocketwrite(iSockFd, send_buf, size + 2);*/
		sprintf(send_buf,"%c%c%s",0xef,0x14,msg->msg_text);
		iLen = write(iSockFd, send_buf, size + 2);
	}
	iSendLen = size + 2;

	if (iLen != iSendLen)
	{
		usfErrlog("请求编号=[%s] 发送响应数据失败!", msg->request_id);
		usfDestroyMsg(msg);
		del_conn_node(iSlot);
		if (send_buf != NULL)
		{
			free(send_buf);
			send_buf = NULL;
		}
		return (-1);						
	}
	if (send_buf != NULL)
	{
		free(send_buf);
		send_buf = NULL;
	}
	usfTraceX("请求编号=[%s] 发送数据成功! IP=[%s]\n数据=[%d][%s]", msg->request_id, aIpAddr, iSendLen, msg->msg_text);

	strcpy(aContFlag,"0");
	if (usfGetMsgHeadValue(msg, "SNC", aContFlag) == 0)
	{
		if (aContFlag[0] != '0') 
		{	/* 有后续子交易 */
			usfTraceX("有后续交易，继续接收数据");
			usfDestroyMsg(msg);
			return(0);
		}
	}
	usfTraceX("无后续交易，退出");

	del_conn_node(iSlot);
				
	usfDestroyMsg(msg);

	return(0);
}

/*
 * 增加通讯连接同步连接信息
 */
int add_conn_node(CONN_DESP * conn_desp)
{
		 short slot;
		 
		 slot = mplMalloc(_FDsList);
		 if (slot < 0) 
		 {
			 usfErrlog("[add_conn_node] 连接数已满，不能处理更多的连接");
			 return(-1);
		 }
		 
		 memcpy(_FDsList->addr[slot], conn_desp, sizeof(CONN_DESP));
	
		 return(slot);
}

/*
 * 删除通讯连接同步连接信息
 */

int del_conn_node(int iSlot)
{
		CONN_DESP * p;
		int			 i;

		if (( iSlot < 0)	|| (iSlot >= _FDsList->cursize))
		{
			 return(-1);
		}

		if (_FDsList->allocedpos[iSlot] == 1)
		{
			 p = (CONN_DESP *)_FDsList->addr[iSlot];	
	 	 	 hsocketclose(p->sockfd);
			 mplFree(_FDsList, iSlot);
		}
		
		return(0);
}

/*
 * 匹配原来的通讯连接
 */
int check_conn_node(int id, char *ipAddr,char * key)
{
		CONN_DESP * p;
		
	if (id > _FDsList->cursize || _FDsList->allocedpos[id] != 1)
	{
		return (-1);
	}
	p = (CONN_DESP *)_FDsList->addr[id];
	if ( ( strcmp( p->ipAddr, ipAddr) == 0 )	&&
		( strcmp( p->key, key) == 0) )
	{
		return (p->sockfd);
	}

	return(-1);
}

/*
 * 管理监控返回
 * Added by liangwj at 2006-06-05
 */
int putManageMsgResponse(Message * msg, XmlNode * out_root, char * err_code, char * err_msg)
{
	/* 设置处理结果代码 */
	xmlSetChildValue(out_root, "RspCod", err_code);
	usfSetMsgHeadValue(msg, "SSC", err_code, 6);

	/* 设置处理结果信息 */
	xmlSetChildValue(out_root, "RspMsg", err_msg);
	usfSetMsgHeadValue(msg, "SEM", err_msg, strlen(err_msg));

	usfReturn(msg, out_root, "text/xml", 0);

	/* 释放资源 */
	usfDestroyMsg(msg);
	xmlFreeNode(out_root, 1);
	
	return 0;
}

/*
 * 动态更新IPD文件
 * Added by liangwj at 2006-06-05
 */
int reloadIpList(Message * msg) 
{
	XmlNode	* root=NULL;
	char	result[6+1];
	char	err_msg[1024+1];
	int		rc=0;
	
	if (strlen(_ConnPara.ipConFile) > 0)
	{	
		root = xmlNewNode(ELEMENT_NODE, "ROOT", NULL, NULL);
	
		rc = ecnReloadIpList(_ConnPara.ipConFile, &_IPsList, &_IPsTable);
		if (rc == 0)
		{
			strcpy(result, "000000");
			strcpy(err_msg, "动态更新IPD文件成功!");
		}
		else
		{
			strcpy(result, "999999");
			strcpy(err_msg, "动态更新IPD文件失败, 请检查IPD文件是否合法!");
		}
	}
	else
	{
		strcpy(result, "999999");
		strcpy(err_msg, "动态更新IPD文件失败, ATR中原来没有配置IPD文件!");
	}
	putManageMsgResponse(msg, root, result, err_msg);
	return (0);
}

int writebinfile(char * fn, char * bin_buf, int len)
{
	FILE	*fp;
	char	pathname[256];
	int	retval;
	 
	memset(pathname,0x00,sizeof(pathname));
	sprintf(pathname,"%s%s",_FP,fn);
	fp = fopen(pathname,"a+");
	if ( fp == NULL )
	{
	 usfErrlog("[%s] 文件打开出错",pathname);

		return (-1);
	}

	retval = fwrite(bin_buf,len,1,fp);

	if ( retval != 1 )
	{
		fclose(fp);
		return(-1);
	}
	fclose(fp);
	return (0);
}
