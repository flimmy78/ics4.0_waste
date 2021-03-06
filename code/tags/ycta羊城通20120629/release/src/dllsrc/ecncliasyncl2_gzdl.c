/********************************************************************      
Copyright (C),1998-2003,Hisuntech Co.,Ltd.                                
  File name:      // ecncliasyncl2.c                                   
  Author:         // WangXiaoDong                                       
  Version:        // 1.0                                               
  Date:           // 20030401                                         
  Description:    // 这是外部通讯模块中服务端异步长连接双工源文件。      
  Others:         // 目前只考虑一条长连接                             
  Function List:  // 主要函数列表，每条记录应包括函数名及功能简要说明
                     serverLongAsync2In                             
                     serverLongAsync2Out                           
                     initChannel                                  
                     closeChannel                                
                     thread_main                                
                     create_connect
                     longAsync2Request                     
  History:        // 修改历史记录列表，每条修改记录应包括修改日期�
                  // 修改者及修改内容简述                        
    1. Date:                                                    
       Author:                                                 
       Modification:                                          
    2. ...                                                   
********************************************************************/   
#include "ecnmain.h"

ASYNC_IP_SOCKFD  * _AsyncIpSockfdHead = NULL;

CONN_PARAM       _ConnPara;
pthread_t        _MainThreadId;
int              _RequestListenFD;
int				 _RequestPort = 0;
int				 _ResponsePort = 0;
int				 _RequestListenFD = -1;
int				 _ResponseListenFD = -1;
int				 _RequestFD = -1;
int				 _ResponseFD = -1;
pthread_t			 _RequestThreadID;
pthread_t			 _ResponseThreadID;
pthread_mutex_t	 _RequestLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	 _ResponseLock = PTHREAD_MUTEX_INITIALIZER;

/********************************************************************
  Function:       // initChannel
  Description:    // 服务启动时运行的初始化函数，执行装载IP表及一些参数
  Calls:          // loadIpTableAsync(char * filename) 装载ip表的函数
  Called By:      // 被服务框架调用
  Table Accessed: // 
  Table Updated:  // 
  Input:          // argc:参数个数
                  // argv:参数数组,包括参数：ipConFile,preLenLen
  Output:         //
  Return:         // 0:成功 !0:失败
  Others:         // 
********************************************************************/
int initChannel(int argc, char ** argv)
{
    memset(&_ConnPara, 0x0, sizeof(CONN_PARAM));
    if (argc < 1)
    {
		usfErrlog("输入参数：合法IP列表，[前置长度]");	
		return (-1);
    }  
   
	/*
	 * 设置本地IP地址
	 * Added by liangwj in 20050127
	 */
	hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
    if (strlen(argv[0]) <= FILENAME_LEN)
    {
		strcpy(_ConnPara.ipConFile,argv[0]);	
    }
    else
    {
		usfErrlog("配置文件名超过长度(%d)", FILENAME_LEN);
		return (-1);
    }

    if (argc == 1)
    {
        _ConnPara.havePreLen = NO_PRELEN;
    } 
    else
    {
        _ConnPara.havePreLen = HAVE_PRELEN;
        _ConnPara.preLenLen = atoi(argv[1]);	
        if (_ConnPara.preLenLen <= 0)
        {
           _ConnPara.havePreLen = NO_PRELEN;
        }
    }
    

    usfTraceX("配置文件名[%s] 前置长度标志[%d] 前置长度[%d]",
		argv[0], _ConnPara.havePreLen, _ConnPara.preLenLen);

    if ((_AsyncIpSockfdHead = loadIpTableAsync(argv[0])) == NULL)
    {
        usfErrlog("装载IP表失败, 不进行IP合法性检查.");
    }
    
    return (0);
}

/********************************************************************
  Function:       // longAsyncSend2Request
  Description:    // 接收渠道请求数据
  Calls:          // hsocketselect
                  // hsocketread
                  // ReadLen
  Called By:      // thread_main
  Table Accessed: // 
  Table Updated:  // 
  Input:          // arg:参数(CONN_DESP)
  Output:         //
  Return:         // 无
  Others:         // 
********************************************************************/
void * longAsyncSend2Request(void *arg)
{
    CONN_DESP      * conn_desp = (CONN_DESP *)arg;
    char           *aRecvBuf;
    char           aIpAddr[IPADDR_LEN + 1];
    int            iConnFd,iRecvLen,iResult,iReadLen;
    Message        * msg = NULL;
	char           tmp_str[20];
	long           stime;
    struct timeval tv;

    if (conn_desp == NULL )
    {
    	//deleted by kixiong at 2009-1-24 9:38:47
        //hsocketclose(iConnFd);
        thdExit( NULL );
    }

    iConnFd = _RequestFD;
    strcpy(aIpAddr,conn_desp->ipAddr);
    free( conn_desp );
    conn_desp = NULL;

    /*
    thdSetCancelType(PTHREAD_CANCEL_DEFERRED, NULL);
    thdSetCancelState(PTHREAD_CANCEL_ENABLE, NULL);
    */

    for (;;)
    {
        thdTestCancel();

        iResult = hsocketselect(TIME_OUT, iConnFd);
        if (iResult < 0) 
        {
            hsocketclose(iConnFd);
            thdLockMutex(&_RequestLock);
            _RequestFD = -1;
            thdUnlockMutex(&_RequestLock);
            usfErrlog("侦听网络读信号失败, 请求通道通讯连接已断开! IP=[%s]", aIpAddr);
            
            /*关闭掉响应通道*/
            thdLockMutex(&_ResponseLock);
            if ( _RequestFD > 0 )
            {
            	hsocketclose(_ResponseFD);
            	_ResponseFD = -1;
        	}
            thdUnlockMutex(&_ResponseLock);
            
            thdExit(NULL);
        }
        if (iResult == 0) /* 在超时时间内没有数据到达，继续侦听 */
        {
            continue;
        }
        
        
        iRecvLen = -1;
        switch (_ConnPara.havePreLen)
        {
        case HAVE_PRELEN: /*有前置长度 */	
			iRecvLen = hsocketreadbylen(iConnFd, &aRecvBuf, _ConnPara.preLenLen);
			iReadLen = iRecvLen + _ConnPara.preLenLen;
			break;  	
        default:
			aRecvBuf = (char *)malloc(MAX_DATA_LEN+1);
			if ( aRecvBuf != NULL )
			{
				memset( aRecvBuf, 0x0, sizeof( aRecvBuf ));
				iRecvLen = recv(iConnFd, aRecvBuf, MAX_DATA_LEN, 0);
				iReadLen = iRecvLen;
			}
			break;
        }
        if (iRecvLen <= 0 )
        {
        	usfErrlog("接收数据失败, 请求通道通讯连接已关闭! IP=[%s]", aIpAddr);
            hsocketclose(iConnFd);
			thdLockMutex(&_RequestLock);
            _RequestFD = -1;
            thdUnlockMutex(&_RequestLock);
            if (aRecvBuf != NULL)
            {
                free(aRecvBuf);
                aRecvBuf = NULL;
            }
            
            /*关闭掉响应通道*/
            thdLockMutex(&_ResponseLock);
            if ( _RequestFD > 0 )
            {
            	hsocketclose(_ResponseFD);
            	_ResponseFD = -1;
        	}
            thdUnlockMutex(&_ResponseLock);
            
            thdExit(NULL);
        }

        msg = (Message *)usfCreateMsg(_ConnPara.msgType);
        if (msg) 
        {
            usfSetMsgData(msg, aRecvBuf, iRecvLen);
            usfAddMsgHeadValue(msg, "SIP", aIpAddr, strlen(aIpAddr) );
            usfAddMsgHeadValue(msg, "SCH", "rq", 2);
            /*
            stime = time(NULL);
            sprintf(tmp_str, "%ld", stime);
            usfAddMsgHeadValue(msg, "STM", tmp_str, strlen(tmp_str));
            */
            gettimeofday(&tv, NULL);
            snprintf(tmp_str, sizeof(tmp_str), "%ld.%ld", tv.tv_sec, tv.tv_usec);
            usfAddMsgHeadValue(msg, "STM", tmp_str, strlen(tmp_str));
            
            usfTraceX("请求编号=[%s] 接收数据成功! IP=[%s]\n数据=[%d][%s]", msg->request_id, aIpAddr, iRecvLen, aRecvBuf);

            if (usfSendRequest(msg))
            {
                usfErrlog("请求编号=[%s] 发送请求消息失败!", msg->request_id);
                usfDestroyMsg(msg);
            }
        }
        else 
        {
            usfErrlog("创建请求消息失败! IP=[%s]\n数据=[%d][%s]", aIpAddr, iRecvLen, aRecvBuf);
        }

        if (aRecvBuf != NULL )
        {
            free(aRecvBuf);
            aRecvBuf = NULL;
        }
    } 
}

void * checkResponseSockConnection(void *arg)
{
    CONN_DESP      * conn_desp = (CONN_DESP *)arg;
    char           aRecvBuf[64];
    char           aIpAddr[IPADDR_LEN + 1];
    int            iConnFd,iRecvLen,iResult,iReadLen;
    Message        * msg = NULL;
	char           tmp_str[20];
	long           stime;
	
    if (conn_desp == NULL )
    {
        thdExit( NULL );
    }

    iConnFd = _ResponseFD;
    strcpy(aIpAddr,conn_desp->ipAddr);
    free( conn_desp );
    conn_desp = NULL;

    for (;;)
    {
        thdTestCancel();

        iResult = hsocketselect(TIME_OUT, iConnFd);
        if (iResult < 0) 
        {
            hsocketclose(iConnFd);
            thdLockMutex(&_ResponseLock);
            _ResponseFD = -1;
            thdUnlockMutex(&_ResponseLock);
            usfErrlog("侦听网络读信号失败, 通讯连接已断开! IP=[%s]", aIpAddr);
            
            /*关闭掉请求通道*/
            thdLockMutex(&_RequestLock);
            if ( _RequestFD > 0 )
            {
            	hsocketclose(_RequestFD);
            	_RequestFD = -1;
        	}
            thdUnlockMutex(&_RequestLock);
            
            thdExit(NULL);
        }
        if (iResult == 0) /* 在超时时间内没有数据到达，继续侦听 */
        {
            continue;
        }
        
		iRecvLen = recv(iConnFd, aRecvBuf, sizeof(aRecvBuf), 0);		
        if (iRecvLen <= 0 )
        {
        	usfErrlog("接收数据失败, 响应通道通讯连接已关闭! IP=[%s]", aIpAddr);
            hsocketclose(iConnFd);
			thdLockMutex(&_ResponseLock);
            _ResponseFD = -1;
            thdUnlockMutex(&_ResponseLock);
            
            /*关闭掉请求通道*/
            thdLockMutex(&_RequestLock);
            if ( _RequestFD > 0 )
            {
            	hsocketclose(_RequestFD);
            	_RequestFD = -1;
        	}
            thdUnlockMutex(&_RequestLock);
            
            thdExit(NULL);
        }
    } 
}

/********************************************************************
  Function:       // thread_main
  Description:    // 获取渠道连接、创建线索建立与渠道的连接、创建线索接收数据
  Calls:          // create_connect
                  // longAsync2Request
  Called By:      // serverLongAsync2In
  Table Accessed: // 
  Table Updated:  // 
  Input:          // arg:参数
  Output:         //
  Return:         // 无
  Others:         // 
********************************************************************/
void * request_thread_main(void *arg)
{
	#ifdef _HP_SYSTEM_
	int					iCliLen = 0;
	#else
    socklen_t          iCliLen;
    #endif
    int                iErrno;
    int                iSockID;
    struct sockaddr_in cli_addr;
    pthread_t          pThreadId;
    pthread_attr_t     pAttr;
    CONN_DESP          * conn_desp = NULL;
    char			   * pIpAdr;


    void               *longAsyncSend2Request(void *);

    memset((char *)&cli_addr, 0, sizeof(struct sockaddr_in));

    thdSetCancelType(PTHREAD_CANCEL_DEFERRED, NULL);
    thdSetCancelState(PTHREAD_CANCEL_ENABLE, NULL);

	thdInitAttr(&pAttr);

    thdSetDetachState(&pAttr, PTHREAD_CREATE_DETACHED);
    //thdSetScope(&pAttr, PTHREAD_SCOPE_SYSTEM);

    for (;;) 
    {
    	
        thdTestCancel();
    	/*
    	 *  获取渠道连接
    	 */
        iCliLen = sizeof(cli_addr);
        conn_desp = (CONN_DESP *)malloc(sizeof(CONN_DESP));
        if ( conn_desp == NULL ) 
        {
            usfErrlog("[request_thread_main] 分配内存[CONN_DESP]失败!");
            continue;
        }
        memset( conn_desp, 0, sizeof(CONN_DESP) );

        iSockID = accept(_RequestListenFD, (struct sockaddr *)&cli_addr, &iCliLen);

        if (iSockID < 0) 
        {
            usfErrlog("[request_thread_main] 接受(accept)连接请求失败!");
            if (conn_desp != NULL)
            {
                free(conn_desp);
                conn_desp = NULL;
            }
            continue;
        }
        
        thdLockMutex(&_RequestLock);
        _RequestFD = iSockID;
        thdUnlockMutex(&_RequestLock);

        memset(conn_desp->ipAddr, 0x0, sizeof(conn_desp->ipAddr));
        sprintf(conn_desp->ipAddr, "%s", inet_ntoa(cli_addr.sin_addr));
        
        /*
         * 判断ip地址合法性
         */
        if (checkIpAsync(_AsyncIpSockfdHead,conn_desp->ipAddr))
        {
            usfErrlog("注意: 有非法IP地址[%s]试图连接!", conn_desp->ipAddr);
            hsocketclose(_RequestFD);
            if (conn_desp != NULL)
            {
                free(conn_desp);
                conn_desp = NULL;
            }
            continue;	
        }

		/* 
		 * 函数参数需要重新申请内存空间
		 * Modified by liangwj at 2006-03-30
		 */
		pIpAdr = strdup(conn_desp->ipAddr);
		if (pIpAdr == NULL)
		{
            usfErrlog("申请内存失败!");
            hsocketclose(_RequestFD);
            free(conn_desp);
            conn_desp = NULL;
            continue;	
        }
			
        /*
         *  创建线索接收渠道数据
         */
        iErrno = thdCreate(&pThreadId, &pAttr, longAsyncSend2Request, 
			(void *)conn_desp);
        if (iErrno)
        {
            usfErrlog("创建数据接收线索失败! [%d]", iErrno);
            if (conn_desp != NULL)
            {
				free(conn_desp);
				conn_desp = NULL;
            }
            hsocketclose(_RequestFD);
            continue;
        }
    }
}

/********************************************************************
  Function:       // thread_main
  Description:    // 获取渠道连接、创建线索建立与渠道的连接、创建线索接收数据
  Calls:          // create_connect
                  // longAsync2Request
  Called By:      // serverLongAsync2In
  Table Accessed: // 
  Table Updated:  // 
  Input:          // arg:参数
  Output:         //
  Return:         // 无
  Others:         // 
********************************************************************/
void * response_thread_main(void *arg)
{
	#ifdef _HP_SYSTEM_
	int					iCliLen = 0;
	#else
    socklen_t          iCliLen;
    #endif
    int                iErrno;
    struct sockaddr_in cli_addr;
    pthread_t          pThreadId;
    pthread_attr_t     pAttr;
    CONN_DESP          * conn_desp = NULL;
    char			   * pIpAdr;
    int				   iSockID = -1;
    
    void               *checkResponseSockConnection(void *);

    memset((char *)&cli_addr, 0, sizeof(struct sockaddr_in));

    thdSetCancelType(PTHREAD_CANCEL_DEFERRED, NULL);
    thdSetCancelState(PTHREAD_CANCEL_ENABLE, NULL);

	thdInitAttr(&pAttr);

    thdSetDetachState(&pAttr, PTHREAD_CREATE_DETACHED);

    for (;;) 
    {
    	
        thdTestCancel();
    	/*
    	 *  获取渠道连接
    	 */
        iCliLen = sizeof(cli_addr);
        conn_desp = (CONN_DESP *)malloc(sizeof(CONN_DESP));
        if ( conn_desp == NULL ) 
        {
            usfErrlog("[request_thread_main] 分配内存[CONN_DESP]失败!");
            continue;
        }
        memset( conn_desp, 0, sizeof(CONN_DESP) );

        iSockID = accept(_ResponseListenFD, (struct sockaddr *)&cli_addr, &iCliLen);

        if (iSockID < 0) 
        {
            usfErrlog("[response_thread_main] 接受(accept)响应连接通道请求失败!");
            if (conn_desp != NULL)
            {
                free(conn_desp);
                conn_desp = NULL;
            }
            continue;
        }
        
        thdLockMutex(&_ResponseLock);
        _ResponseFD = iSockID;
        thdUnlockMutex(&_ResponseLock);

        memset(conn_desp->ipAddr, 0x0, sizeof(conn_desp->ipAddr));
        sprintf(conn_desp->ipAddr, "%s", inet_ntoa(cli_addr.sin_addr));
        
        /*
         * 判断ip地址合法性
         */
        if (checkIpAsync(_AsyncIpSockfdHead,conn_desp->ipAddr))
        {
            usfErrlog("注意: 有非法IP地址[%s]试图连接!", conn_desp->ipAddr);
            hsocketclose(_ResponseFD);
            if (conn_desp != NULL)
            {
                free(conn_desp);
                conn_desp = NULL;
            }
            continue;	
        }

		/* 
		 * 函数参数需要重新申请内存空间
		 * Modified by liangwj at 2006-03-30
		 */
		pIpAdr = strdup(conn_desp->ipAddr);
		if (pIpAdr == NULL)
		{
            usfErrlog("申请内存失败!");
            hsocketclose(_ResponseFD);
            free(conn_desp);
            conn_desp = NULL;
            continue;	
        }
			
        /*
         *  创建线索接收渠道数据
         */
        iErrno = thdCreate(&pThreadId, &pAttr, checkResponseSockConnection, 
			(void *)conn_desp);
        if (iErrno)
        {
            usfErrlog("创建响应通道检测线索失败! [%d]", iErrno);
            if (conn_desp != NULL)
            {
				free(conn_desp);
				conn_desp = NULL;
            }
            hsocketclose(_ResponseFD);
            _ResponseFD = -1;
            continue;
        }
    }
}

/********************************************************************
  Function:       // serverLongAsync2In
  Description:    // FCA异步长连接双工中FCA服务接收渠道请求的入口函数。
                  // 完成如下功能：
                  // 接收传入参数
                  // 绑定端口并侦听
                  // 创建线索，由该线索完成后续功能
  Calls:          // hsocketbindlisten
  Called By:      // 被服务框架
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  argc:参数个数
                  //  argv:参数[消息类型、端口号]
                  //  tid :线索id
  Output:         //
  Return:         // 0:成功 -1：失败
  Others:         // 
********************************************************************/
int serverLongAsync2In(int argc, char ** argv, pthread_t * tid)
{
    pthread_attr_t pAttr;
    int            iErrno;

    void *thread_main(void *);
    
    if (argc < 3)
    {
        usfErrlog("输入参数: MsgType RequestPort ResponsePort", ERRCODE + 40);
        return (-1);
    }

    if (strlen(argv[0]) == MSGLEN)
    {
        strcpy(_ConnPara.msgType, argv[0]);
    }
    else
    {
        usfErrlog("消息类型超过长度(%d)", MSGLEN);
        return (-1);
    }

    _RequestPort = atoi(argv[1]);
    if (_RequestPort <= 0)
    {
        usfErrlog("请求端口号必须是数字! [%s]",argv[1]);
        return (-1);	
    }
    _ResponsePort = atoi(argv[2]);
    if (_ResponsePort <= 0)
    {
        usfErrlog("响应端口号必须是数字! [%s]",argv[2]);
        return (-1);	
    }

    _RequestListenFD = hsocketbindlisten(_RequestPort);
    if ( _RequestListenFD < 0 )
    {
        usfErrlog("绑定并请求监听端口(%d)失败!", _RequestPort);
        return (-1);
    }
    _ResponseListenFD = hsocketbindlisten(_ResponsePort);
    if ( _ResponseListenFD < 0 )
    {
        usfErrlog("绑定并响应监听端口(%d)失败!", _ResponseListenFD);
        return (-1);
    }

	thdInitAttr(&pAttr);
    
    thdSetDetachState(&pAttr, PTHREAD_CREATE_UNDETACHED);
    thdSetScope(&pAttr, PTHREAD_SCOPE_SYSTEM);

    iErrno = thdCreate(&_ResponseThreadID, &pAttr, response_thread_main, NULL);
    if (iErrno)
    {
    	usfErrlog("响应主线索创建失败! errno=[%d]", iErrno);
        thdDestroyAttr(&pAttr);
        hsocketclose(_ResponseListenFD);
        return (-1);
    }	
    iErrno = thdCreate(&_RequestThreadID, &pAttr, request_thread_main, NULL);
    if (iErrno)
    {
    	usfErrlog("请求主线索创建失败! errno=[%d]", iErrno);
        thdDestroyAttr(&pAttr);
        hsocketclose(_RequestListenFD);
        return (-1);
    }	
    
    thdDestroyAttr(&pAttr);
    return (0);
}


/********************************************************************
  Function:       // serverLongAsync2Out
  Description:    // FCA异步长连接双工中向渠道返回响应数据的入口函数
  Calls:          // hsocketwrite
                  // hsocketwritebylen
  Called By:      // 被服务框架
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  msg:消息
  Output:         //
  Return:         // 0:成功 -1：失败
  Others:         // 
********************************************************************/
int serverLongAsync2Out(Message * msg)
{
    int              iResult,iSockFd;
    ASYNC_IP_SOCKFD  * p = NULL;
    char             aIpAddr[IPADDR_LEN + 1];
    int              iSendLen;

	thdLockMutex(&_ResponseLock);
	if ( _ResponseFD < 0 )
	{
		usfErrlog("请求编号=[%s] 响应消息失败, 对方未建立响应连接通道.msg=[%d][%s]", msg->request_id, msg->msg_size, msg->msg_text);
		thdUnlockMutex(&_ResponseLock);
		usfDestroyMsg(msg);
		return (-1);
	}
	
	iSockFd = _ResponseFD;
	iSendLen = msg->msg_size;
	switch (_ConnPara.havePreLen)
	{
	case HAVE_PRELEN:/*有前置长度  */	
		iResult = hsocketwritebylen(iSockFd, msg->msg_text, msg->msg_size,
			_ConnPara.preLenLen);
		iSendLen = msg->msg_size + _ConnPara.preLenLen;
		break;
	default:
		iResult = hsocketwrite(iSockFd, msg->msg_text, msg->msg_size);
		iSendLen = msg->msg_size;
		break;
	}
	thdUnlockMutex(&_ResponseLock);
	if ( iResult != iSendLen ) 
	{
	    usfErrlog("请求编号=[%s] 发送数据失败! 数据=[%d][%s]", msg->request_id, iSendLen, msg->msg_text);
	    usfDestroyMsg(msg); 
	    hsocketclose(iSockFd);
	    return (-1);
	}
	usfTraceX("请求编号=[%s] 发送数据成功! 数据=[%d][%s]", msg->request_id, iSendLen, msg->msg_text);
	usfDestroyMsg(msg);

    return (0);
}

/********************************************************************
  Function:       // closeChannel
  Description:    // 服务退出时，关闭启动的线索、socket句柄和侦听句柄�
                  //释放异步通讯连接状态信息表
  Calls:          // freeIpTableAsync
                  // 
  Called By:      // 被服务框架调用
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  
  Output:         //
  Return:         // 无
  Others:         // 
********************************************************************/
void closeChannel()
{
    int iErrno;
    
    thdCancel(_RequestThreadID);
    thdCancel(_ResponseThreadID);
    thdJoin( _RequestThreadID, NULL); 
    thdJoin( _ResponseThreadID, NULL);    
    freeIpTableAsync(_AsyncIpSockfdHead);
    hsocketclose(_RequestListenFD);
    hsocketclose(_ResponseListenFD);
    _ResponseListenFD = -1;
    _RequestListenFD = -1;
}

