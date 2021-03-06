/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : pftsvrfil_gz.c
 Author         : WangXiaoDong
 Version        : 1.0
 Date           : 2003-03-27
 Description    : 这是外部通讯模块中客户端同步连接源文件
 Others         : 目前只考虑一条长连接   
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-03-27  WangXD      完成
  002   2006-03-22  LiangWJ     修改
  003		2007-06-15  WangXF      修改
        注：针对财税系统需求，通讯采用短连接，一次连接多次交互信息，
        本通讯接口通过消息头SNC判断是否保留连接。
******************************************************************************/      
#include "ecnmain.h"       

#define LONG_CONN  1
#define SHORT_CONN 0

char               _ServerIp[IPADDR_LEN + 1];/*  对方服务器ip地址 */
int                _ServerPort;              /*  对方服务器端口号 */
int                _ConnType;                /*  0：短连接 1：长连接  */
int                _HavePreLen;              /*  0:带前置长度 1:不带前置长度 */
int                _PreLen;                  /*  前置域长度  */
int				   _IncludeFlag=0;			 /*  是否包含前置长度标志 */
											 /*   0：不包含 1：包含 */
int				   _TimeOut;				 /*  缺省超时时间 */
pthread_mutex_t    _SocketMutex = PTHREAD_MUTEX_INITIALIZER;
SERVER_CONF        * _SvrConfHead;
SERVER_CONF        * _SvrConfTail;
MemoryPool         * _SvrList;
/********************************************************************
  Function:       // initSvrConf
  Description:    // 初始化结构SERVER_CONF
  Calls:          // 
  Called By:      // initChannel
  Table Accessed: // 
  Table Updated:  // 
  Input:          // args:参数
  Output:         //
  Return:         // 
  Others:         // 
********************************************************************/
void initSvrConf( void * args)
{
	SERVER_CONF * svrConf = (SERVER_CONF *)args;
	memset(svrConf, 0x0, sizeof(SERVER_CONF));
}
/********************************************************************
  Function:       // initChannel
  Description:    // 服务启动时运行的初始化函数，初始化一些参数
  Calls:          // 
  Called By:      // 被服务框架调用
  Table Accessed: // 
  Table Updated:  // 
  Input:          // argc:参数个数
                  // argv:参数数组,包括参数: _ServerIp,_ServerPort
                  //      _ConnType:连接类型 0:短连接 1:长连接 
                  //      _PreLen :前置长度域的长度
  Output:         //
  Return:         // 0:成功 !0:失败
  Others:         // 
********************************************************************/
int initChannel(int argc,char **argv)
{
	int iMaxConn;

	if (argc < 3)
	{
		/* modified by yu_qj, 2004-6-2
		usfErrlog("[%d]请输入必须的参数:ServerIp,ServerPort,ConnType,[MaxConn],[PreLen]", ERRCODE+1);
		*/
		usfErrlog("请输入必须的参数:ServerIp,ServerPort,ConnType,[MaxConn],[PreLen],[TimeOut]");
		return (-1);
    }

	/*
	 * 设置本地IP地址
	 * Added by liangwj in 20050918
	 */
	hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
    memset(_ServerIp, 0x0, sizeof(_ServerIp));
    strncpy(_ServerIp, argv[0], IPADDR_LEN);
    if (inet_addr(_ServerIp) < 0)
    {
		usfErrlog("非法的IP地址[%s]", _ServerIp);
		return (-1);
    }

	_ServerPort = atoi(argv[1]);
	if (_ServerPort <= 0)
    {
		usfErrlog("非法的端口号");
		return (-1);
	}

	_ConnType = atoi(argv[2]);
	if ((_ConnType != SHORT_CONN) && (_ConnType != LONG_CONN))
	{
		usfErrlog("连接类型标志错[%d]", _ConnType);
		return (-1);
	}


	if (argc < 4)
	{
		iMaxConn = DEFAULT_CONN_SERVER_NUM;
	}
	else
	{
		iMaxConn = atoi(argv[3]);
		if (iMaxConn <= 0)
		{
			iMaxConn = DEFAULT_CONN_SERVER_NUM;
		}
	}

	if (argc < 5)
	{
		_HavePreLen = NO_PRELEN;
	}
	else
	{
		_PreLen = atoi(argv[4]);
		_HavePreLen = HAVE_PRELEN;
		if (_PreLen <= 0)
		{
			_HavePreLen = NO_PRELEN;
		}  
	}

	if (argc < 6)
	{
		_TimeOut = TIME_OUT;
	}
	else
	{
		_TimeOut = atoi(argv[5]);
		if (_TimeOut <= 0)
		{
			_TimeOut = TIME_OUT;
		}  
	}

	usfTraceX( "[1]IP[%s]Port[%d]连接类型[%d]最大连接数目[%d]前置长度[%d]缺省超时[%d]", _ServerIp, _ServerPort, _ConnType,iMaxConn,_PreLen,_TimeOut);


	_SvrList = mplCreate(1, iMaxConn, sizeof(SERVER_CONF), 1, 1, initSvrConf);
	if (_SvrList == NULL)
    {
		usfErrlog("申请连接内存表空间失败");
		return (-1);
	}

	return (0);
}


/********************************************************************
  Function:       // closeChannel
  Description:    // 服务停止时运行的函数，(用于同步长连接)关闭socket描述符
  Calls:          // 
  Called By:      // 被服务框架调用
  Table Accessed: // 
  Table Updated:  // 
  Input:          // 
                  //
  Output:         //
  Return:         //
  Others:         // 
********************************************************************/
void closeChannel()
{
	SERVER_CONF *p;
	int         i ;
   
	
		for (i = 0; i < _SvrList->cursize; i++)
		{
			if (_SvrList->allocedpos[i] == 1)
			{
				p = ( SERVER_CONF *)_SvrList->addr[i];
				hsocketclose( p->sockFd);
			}
		}
	
    /*
     * 释放客户端外联服务信息表
     */
	mplDestroy(_SvrList);
}

/********************************************************************
  Function:       // clientSyncOut
  Description:    // 服务启动后发送请求和接收应答数据的入口函数
                  // 需要从请求包中取OIP,OPT,以支持与多个服务器通讯
  Calls:          // 
                  //
  Called By:      // 被服务框架调用�
  Table Accessed: // 
  Table Updated:  // 
  Input:          // argc:参数个数
                  // argv:参数数组
                  // tid :线索id
  Output:         //
  Return:         // 0:成功 !0:失败
  Others:         // 
********************************************************************/
int clientSyncOut(Message * msg)
{
	char           * recv_buf = NULL, * send_buf = NULL, *temp_buf = NULL ,*read_buf = NULL;
	char           aCommIp[IPADDR_LEN + 1];
	int            iCommPort;    
	char           aTimeOut[4];
	char           aDeadTime[11];
	SERVER_CONF    *curr;
	struct timeval tv;
	int            iFlag,iAdd;
	int            iSockFd;
	int            iSendLen,iRecvLen,iLen, iOffSet, iFilSiz;
	int            iResult;
	int            iRetry=0;
	long           lCurrTime;
	short          currSlot = -1;
	char		   		 aTmp[255+1];
	char					 aContFlag[2];
	char					 sFilNam[255+1],sFilSiz[16],sSekPnt[16], sSendHead[17+1];  /*读取的文件名,文件长度,偏移位置,信息头*/

	usfSetMsgHeadValue(msg, "SCH", "rp", 2);

    /*
     *
     * 判断是使用消息头中的ip地址和端口号，还是使用缺省的ip地址和端口号
     */
	memset(aCommIp, 0x0, sizeof(aCommIp));      
	judgeSvrIpPort(msg, _ServerIp, _ServerPort, aCommIp, &iCommPort);

    /* 
     * 判断是否超过发送时间
     */
   memset(aDeadTime, 0x0, sizeof(aDeadTime));
   if (usfGetMsgHeadValue( msg, "ETM", aDeadTime) == 0)
   {
       if ((strlen(aDeadTime) > 0) && (hisnumber(aDeadTime) == 0))
       {
           gettimeofday(&tv, NULL);
           lCurrTime = tv.tv_sec;
           if (lCurrTime >= atol(aDeadTime)-1)
           {
               usfErrlog("请求编号=[%s] 当前时间(%ld)已经超过交易结束时间(%ld)，不发送!", msg->request_id, lCurrTime, atol(aDeadTime));
               goto rp;
           }
       }
       else
       {
           usfErrlog("请求编号=[%s] ETM的数值[%s]不合法!", msg->request_id, aDeadTime);
           usfDestroyMsg(msg);
           return (-1);
       }
   }
    
   iFlag = 0; /* iFlag = 0表示必须建立连接  ==1 不需要连接*/
   iAdd  = 0; /* iAdd = 0 表示建立的是新连接 ==1 原来的*/
	 thdLockMutex(&_SocketMutex);
   if ( strncmp(msg->msg_text,"login",5) != 0 )/*非首次会话，不需要连接*/
   {
retry:
	 	usfErrlog("请求编号=[%s] 匹配原来的连接! IP=[%s] Port=[%d]\n数据=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, msg->msg_text);
	
       /*
        *  从已经外联的服务器表中搜寻当前要联的服务器是否已存在，
        *  与其连接是否还可用
        */
    currSlot = checkConnectedSvrInfo(_SvrList, aCommIp, iCommPort, &iFlag, &iAdd, &iSockFd);
		/*usfErrlog("请求编号=[%d] 当前槽位[%d]", msg->request_id,currSlot);*/
    if (iFlag == 0)  /* 连接已失效  */
    {
			usfErrlog("请求编号=[%s] 连接已失效! IP=[%s] Port=[%d]\n数据=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, msg->msg_text);
			mplFree(_SvrList, currSlot);

			thdUnlockMutex(&_SocketMutex);
			goto rp;
		}

		if ((currSlot < 0) || (currSlot >= _SvrList->cursize))
		{
			usfErrlog("请求编号=[%s] 当前槽位非法", msg->request_id);
			usfDestroyMsg(msg);
			hsocketclose(iSockFd);
			mplFree(_SvrList, currSlot);
			thdUnlockMutex(&_SocketMutex);
			return (-1);
		}
	}
	else   /*建立连接*/
	{
		usfErrlog("请求编号=[%s] 新建连接! IP=[%s] Port=[%d]\n数据=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, msg->msg_text);
			
		iSockFd = hsocketconnect(aCommIp, iCommPort);
		if (iSockFd <= 0)
		{
			usfErrlog("请求编号=[%s] 连接第三方主机失败! IP=[%s] Port=[%d]", msg->request_id, aCommIp, iCommPort);
			thdUnlockMutex(&_SocketMutex);
			
			goto rp;
		}
		currSlot = addConnectToSvrInfo(_SvrList, aCommIp, iCommPort, iSockFd);
		if (currSlot < 0)
		{
			if (currSlot == -2)
			{
				usfErrlog("请求编号=[%s] 申请内存SERVER_CONF失败!", msg->request_id);
			}
			if (currSlot == -3)
			{
				usfErrlog("请求编号=[%s] 连接数已满!", msg->request_id);
 			}
			thdUnlockMutex(&_SocketMutex);
			hsocketclose(iSockFd);
			usfDestroyMsg(msg);
			return (-1);
		}
		/*usfErrlog("请求编号=[%d] 当前槽位[%d]", msg->request_id,currSlot);
		*/
  }
	thdUnlockMutex(&_SocketMutex);

	 /* 不带前置长度，发送前增加两位前导符 */
	if ( strncmp(msg->msg_text,"sfile",5) == 0 )  /*如果发送文件体信息则单独处理要发送的信息*/
  {
  	memset(sFilNam,0x0, sizeof(sFilNam));
  	memset(sFilSiz,0x0, sizeof(sFilSiz));
  	memset(sSekPnt,0x0, sizeof(sSekPnt));
  	memset(sSendHead,0x0,sizeof(sSendHead));
  	memset(aTmp,0x0, sizeof(aTmp));
  	memcpy(sSendHead,msg->msg_text,17);
  	memcpy(sFilSiz, msg->msg_text+9, 8);
  	memcpy(aTmp, msg->msg_text+17, msg->msg_size - 17);
  	sprintf(sFilNam,"%s",strtok(aTmp,"|"));	
  	sprintf(sSekPnt,"%s",strtok(NULL,"|"));
  	iFilSiz= atoi(sFilSiz);
  	iOffSet= atoi(sSekPnt);
  	iSendLen= iFilSiz + 2 + 5 + 4 + 8;
  	usfErrlog("sFilSiz=[%d],sFilNam=[%s],sSekPnt=[%d],iSendLen=[%d]",iFilSiz,sFilNam,iOffSet,iSendLen);
	}
	else 
	{
  	iSendLen = msg->msg_size + 2;		
	}
	
	send_buf = (char *)malloc(iSendLen + 1);
	if (send_buf != NULL)
	{
		memset( send_buf, 0x0, sizeof( send_buf ));
		if( strncmp(msg->msg_text,"sfile",5) == 0 )  /*如果发送文件体信息则单独处理要发送的信息*/
		{
			read_buf = (char *)malloc(iFilSiz + 1);
			if ( read_buf == NULL )
			{
				usfErrlog("请求编号=[%s] 申请read_buf内存空间失败!", msg->request_id);
				hsocketclose(iSockFd);
				return(-1);
	  	}
	  	memset( read_buf, 0x0, sizeof( read_buf ));
			if ( readbinfile( sFilNam, read_buf, iFilSiz, iOffSet ) != 0 )
			{
				free(read_buf);
				usfErrlog("请求编号=[%s] 读取文件失败!", msg->request_id);
				return(-1);
			}
			memset( aTmp, 0x0, sizeof(aTmp));
			sprintf(aTmp,"%c%c%s",0xef,0x14, sSendHead);
			memcpy(send_buf, aTmp,19);
			memcpy(send_buf+19, read_buf, iFilSiz);
			
			if ( read_buf != NULL )
			{
				free(read_buf);
				read_buf = NULL;
			}
			usfErrlog("请求编号=[%s] 发送数据! IP=[%s] Port=[%d]\n数据长度=[%d][%s----%c%c%c%c%c%c----%c%c%c]", msg->request_id, aCommIp, iCommPort, iSendLen,send_buf,send_buf[19],send_buf[20],send_buf[21],send_buf[22],send_buf[23],send_buf[24],send_buf[iSendLen-3],send_buf[iSendLen-2],send_buf[iSendLen-1]);
	  }
	  else 
	  {
			sprintf(send_buf,"%c%c%s",0xef,0x14,msg->msg_text);
			usfErrlog("请求编号=[%s] 发送数据! IP=[%s] Port=[%d]\n数据=[%d][%s]", msg->request_id, aCommIp, iCommPort, iSendLen, send_buf);
	  }
	}
	else
  {
		usfErrlog("请求编号=[%s] 申请内存空间失败!", msg->request_id);
		hsocketclose(iSockFd);
	
		thdLockMutex(&curr->conn_lock);
		curr->sockFd = 0;
		thdUnlockMutex(&curr->conn_lock);
		            
		return(-1);
	}
  /*iLen = hsocketwrite(iSockFd, send_buf, msg->msg_size + 2);*/
  iLen = send(iSockFd, send_buf, iSendLen, 0);
  if (iLen != iSendLen)
  {
  	usfErrlog("请求编号=[%s] 发送数据失败! IP=[%s] Port=[%d]\n数据=[%d][%s][%d]", msg->request_id, aCommIp, iCommPort, iSendLen, send_buf,iLen);
		hsocketclose(iSockFd);
		if (send_buf != NULL)
		{
			free(send_buf);
			send_buf = NULL;
		}
		goto rp;
  }
	usfTraceX("请求编号=[%s] 发送数据成功! IP=[%s] Port=[%d]\n数据=[%d][%s] ", msg->request_id, aCommIp, iCommPort, iSendLen, send_buf);
    
	if (send_buf != NULL)
	{
		free(send_buf);
		send_buf = NULL;
	}
	
	strcpy(aContFlag,"0");
	if (usfGetMsgHeadValue(msg, "SNC", aContFlag) == 0)
	{
		if (aContFlag[0] == '0') 
   		{  /* 无后续子交易 */
    		usfTraceX("无后续交易，退出接收数据");
    		hsocketshutdown(iSockFd, 1);
		}
	}
    /*
     * 超时控制
     */
  memset(aTimeOut, 0x0, sizeof(aTimeOut));
  usfGetMsgHeadValue(msg, "TMO", aTimeOut);
    /* 
     * hisnumber返回0为全数字
     * Modified by liangwj at 2006-03-23
     */
    /*
    if ((strlen(aTimeOut) > 0) && (hisnumber(aTimeOut)))
    */
  if ((strlen(aTimeOut) > 0) && (hisnumber(aTimeOut) == 0))
  {
		iResult = hsocketselect(atoi(aTimeOut), iSockFd);
    }  
    else
    {
		/* modified by yu_qj, 2004-6-2
        iResult = hsocketselect( TIME_OUT, iSockFd );
		*/
		iResult = hsocketselect(_TimeOut, iSockFd);
    }
      
    if (iResult <= 0)
    {
		usfErrlog("请求编号=[%s] 等待响应超时或通讯连接已关闭!", msg->request_id);
		hsocketclose(iSockFd);

		curr = (SERVER_CONF *)_SvrList->addr[currSlot];

		thdLockMutex(&curr->conn_lock);
		curr->sockFd = 0;
		mplFree(_SvrList, currSlot);
		thdUnlockMutex(&curr->conn_lock);
      
   	goto errpc;
  }

  iLen = -1;
    /*  不带前置长度  */
	recv_buf = (char *)malloc(MAX_DATA_LEN + 1);
	if ( recv_buf == NULL )
	{
		hsocketclose(iSockFd);
		usfDestroyMsg(msg);
		usfErrlog("请求编号=[%s] 申请内存失败", msg->request_id);

		return (-1);
	}
	temp_buf = (char *)malloc(MAX_DATA_LEN + 1);
	if ( temp_buf == NULL )
	{
		hsocketclose(iSockFd);
		usfDestroyMsg(msg);
		free(recv_buf);
		usfErrlog("请求编号=[%s] 申请内存失败", msg->request_id);
		
		return (-1);
	}
	if (recv_buf != NULL)
	{
		memset( recv_buf, 0x0, sizeof( recv_buf ));
		
		/*
		iLen = hsocketrecv(iSockFd, recv_buf, MAX_DATA_LEN);
		*/
		iLen = 0;
		iRecvLen = 0;
		/*
		while (1)
		{
			memset( temp_buf, 0x0, sizeof( temp_buf ));
			iLen = recv(iSockFd, temp_buf, MAX_DATA_LEN, 0);
			if ( iLen <= 0)	
				break;
			memcpy(recv_buf+iRecvLen,temp_buf,iLen);
			iRecvLen += iLen;
			usfErrlog("请求编号=[%s] 接收数据[%s][%d]", msg->request_id,temp_buf,iLen);
		}
		*/
		iLen = recv(iSockFd, recv_buf, MAX_DATA_LEN, 0);
		usfErrlog("请求编号=[%s] 接收数据[%s][%d]", msg->request_id,recv_buf,iLen);

	}
	free(temp_buf);
	temp_buf = NULL;
	iRecvLen = iLen;
	if (iRecvLen <= 0)
  {
		usfErrlog("请求编号=[%s] 接收响应数据失败!", msg->request_id);
		hsocketclose(iSockFd);
		if (aContFlag[0] == '0') 
		{
			curr = (SERVER_CONF *)_SvrList->addr[currSlot];
			thdLockMutex(&curr->conn_lock);
			curr->sockFd = 0;
			mplFree(_SvrList, currSlot);
			thdUnlockMutex(&curr->conn_lock);
		}
         
		if (recv_buf != NULL)
		{
			free(recv_buf);
			recv_buf = NULL;
		}
            
		goto errpc;
	}

	usfTraceX("请求编号=[%s] 接收数据成功! IP=[%s]\n数据=[%d][%s]", msg->request_id, aCommIp, iLen, recv_buf);
		
    /*写入消息前过滤掉两位前导符*/
  usfSetMsgData(msg, recv_buf+2, iLen - 2);
  if (recv_buf != NULL)
  {
		free(recv_buf);
		recv_buf = NULL;
  }   

  usfSetMsgHeadValue(msg, "SSC", NET_OK, 6);

  if (usfSendResponse(msg))
  {
		usfErrlog("请求编号=[%s] 发送响应消息失败!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
  }
	strcpy(aContFlag,"0");
	if (usfGetMsgHeadValue(msg, "SNC", aContFlag) == 0)
	{
		if (aContFlag[0] == '0') 
		{  /* 无后续子交易 */
    	usfTraceX("无后续交易，清理连接信息");
			hsocketclose(iSockFd);

			curr = (SERVER_CONF *)_SvrList->addr[currSlot];
			thdLockMutex(&curr->conn_lock);
			curr->sockFd = 0;
			mplFree(_SvrList, currSlot);
			thdUnlockMutex(&curr->conn_lock);
				
    	return(0);
    }
  }
    
  return (0);

rp:
  usfSetMsgHeadValue(msg, "SSC", NET_ERROR_RQ, 6);
   
  if (usfSendResponse(msg))
  {
		usfErrlog("请求编号=[%s] 发送响应消息失败!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
  } 
	return (0);

errpc:
  usfSetMsgHeadValue(msg, "SSC", NET_ERROR_RP, 6);
   
  if (usfSendResponse(msg))
  {
		usfErrlog("请求编号=[%s] 发送响应消息失败!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
  }
  return (0);
}

int readbinfile(char * fn, char *bin_buf, int len, int offset)
{
  FILE  *fp;
  int retval;

  fp = fopen(fn,"rb");
  if ( fp == NULL )
  {
   usfErrlog("[%s] 文件打开出错",fn);
    return (-1);
  }
  usfErrlog("fn=[%s],len=[%d],offset=[%d]",fn,len,offset);
  if( offset != 0 )
  {
  	fseek(fp,offset,0);
  }
  retval = fread(bin_buf,len,1,fp);
  usfErrlog("bin_buf=[%c][%c][%c][%c][%c][%c]",bin_buf[0],bin_buf[1],bin_buf[2],bin_buf[3],bin_buf[4],bin_buf[5]);
  if ( retval != 1 )
  {
    fclose(fp);
    return(-1);
  }
  fclose(fp);
  return (0);
}
