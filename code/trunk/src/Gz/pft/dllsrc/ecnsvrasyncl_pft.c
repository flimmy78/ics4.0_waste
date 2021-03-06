/******************************************************************************
 File name	: 
 Author			: wishman
 Version		: 1.0
 Date			: 2008-01-20
 Description	: 异步通讯，双通道
 Others			: 无
 History		:
  No.	Date		    Author		Modification
  ===	==========	========	==============================================
  
******************************************************************************/
#include "ecnmain.h"       

#define MY_DATA_LEN 1024
char              _ServerIp[IPADDR_LEN + 1]; /*  对方服务器ip地址 */
char              _MsgType[MSGLEN + 1];      /*  消息类型   */
int               _HavePreLen;               /*  0:带前置长度  1:不带前置长度*/
int               _PreLen;                   /*  前置域长度  */
int               _SendPort;               	 /*  对方发送端口 */
int               _RecvPort;                 /*  对方接收端口 */
int               _LocalSendPort;            /*  我方发送端口 */
int               _LocalRecvPort;            /*  我方接收端口 */
int               _CrypSvrPort;              /*  密押服务端口 */
int	       			  _SendSockFd=-1;			 /*  我方发送描述符 */
int				        _RecvSockFd=-1;			 /*  我方接收描述符 */
int               _IsEnc=1;
pthread_mutex_t   _SocketMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t         _MainThreadId;
char	sMasterKey[8+1] = "ying5876";

void initSvrConf( void * args)
{
    SERVER_CONF * svrConf = (SERVER_CONF *)args;
    memset(svrConf, 0x0, sizeof(SERVER_CONF));
}
int initChannel(int argc,char **argv)
{
    int  iMaxConn;
    int iSign=0;

    if (argc < 7)
    {
        usfErrlog("输入参数: <HostIp> <SendPort> <RecvPort> <LocalSendPort> <LocalRecvPort> <CrypSvrPort> [PreLen]");
        return (-1);
    }

	hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
    memset(_ServerIp, 0x0, sizeof(_ServerIp));
    if (inet_addr(_ServerIp) < 0)
    {
        usfErrlog("非法的IP地址(%s)", _ServerIp);
        return (-1);
    }
    strcpy(_ServerIp, argv[0]);

	_SendPort = atoi(argv[1]);
	_RecvPort = atoi(argv[2]);
	_LocalSendPort = atoi(argv[3]);
	_LocalRecvPort = atoi(argv[4]);
	_CrypSvrPort = atoi(argv[5]);	
	_HavePreLen = NO_PRELEN;

    if (argc > 100)
    {
        _PreLen = atoi(argv[100]);
        _HavePreLen = HAVE_PRELEN;
        if (_PreLen <= 0)
        {
            _HavePreLen = NO_PRELEN;
        }    
    }
        
	_SendSockFd = my_socketconnect(_ServerIp, _SendPort, _LocalSendPort);
	if (_SendSockFd < 0)
	{
        usfErrlog("Init_Creat_Send_Chanel_Fail! SockFd=[%d] Ip=[%s] OPort=[%d] LPort=[%d]", _SendSockFd,_ServerIp, _SendPort, _LocalSendPort);
        return (-1);        
	}
  else
  {
        usfErrlog("Init_Creat_Send_Chanel_SUCC! SockFd=[%d] Ip=[%s] OPort=[%d] LPort=[%d]", _SendSockFd,_ServerIp, _SendPort, _LocalSendPort);
  }
	_RecvSockFd = my_socketconnect(_ServerIp, _RecvPort, _LocalRecvPort);
	if (_RecvSockFd < 0)
	{
		usfErrlog("Init_Creat_Recv_Chanel_Fail[%d]! IP=[%s] OPort=[%d] LPort=[%d]", _RecvSockFd, _ServerIp, _RecvPort, _LocalRecvPort);
    return (-1);        
  }
  else 
  {
		usfErrlog("Init_Creat_Recv_Chanel_Succ[%d]! IP=[%s] OPort=[%d] LPort=[%d]", _RecvSockFd, _ServerIp, _RecvPort, _LocalRecvPort);
  }    
  iSign = DoSignOn(_SendSockFd);
	if (iSign !=1)
	{
		usfErrlog("Init_SignOn_Send_Fail!" );
  	hsocketclose(_SendSockFd);
  	hsocketclose(_RecvSockFd);
    return (-1);        
  }
  usfErrlog("SignOn_Send_Suc!");
  iSign = DoSignOn(_RecvSockFd);
	if (iSign !=1)
	{
		usfErrlog("Init_SignOn_RecvP_Fail!" );
  	hsocketclose(_SendSockFd);
  	hsocketclose(_RecvSockFd);
    return (-1);        
  }
  return (0);
}

void closeChannel()
{
    int         i;

    /*
     *  释放主线索
     */
  usfErrlog("服务主线索进行释放");
	thdCancel(_MainThreadId);
	if (_SendSockFd > 0)
	{    
		hsocketclose(_SendSockFd);
		usfErrlog("关闭发送通讯");
	}
	if (_RecvSockFd > 0)
	{    
		hsocketclose(_RecvSockFd);
		usfErrlog("关闭接收通讯");
	}	
}
/********************************************************************
  Function:       // clientLongAsync2In
  Description:    // 客户端异步长连接双工中接收数据的入口函数。主要功能：
                  //      绑定本地IP地址，建立监听
                  //      创建接收数据的线索
  Calls:          // 
                  // recvThread
  Called By:      // 被服务框架调用�
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  argc  参数个数
                  //  argv  参数数组(消息类型、端口号)
  Output:         //
  Return:         // 0:成功 !0:失败
  Others:         // 
********************************************************************/
int clientLongAsync2In(int argc ,char ** argv)
{
    pthread_attr_t pAttr;
    
    void * recvThread( void * );

    if (argc < 1)
    {
		usfErrlog("输入参数: 消息类型");
		return (-1);
    }

    memset(_MsgType, 0x0, sizeof(_MsgType));
    if (strlen(argv[0]) != MSGLEN)
    {
		usfErrlog("消息类型参数超过长度(%d)", MSGLEN);
		return (-1);
    }
	strcpy(_MsgType, argv[0]);
  SignOk();

	thdInitAttr(&pAttr);

    thdSetDetachState(&pAttr, PTHREAD_CREATE_UNDETACHED);
    thdSetScope(&pAttr, PTHREAD_SCOPE_SYSTEM);

    if (thdCreate(&_MainThreadId, &pAttr, recvThread, NULL) != 0)
    {
        usfErrlog("创建主线索失败!");
        thdDestroyAttr(&pAttr);
        return (-1);
    }

    thdDestroyAttr(&pAttr);
    return (0);
}


/********************************************************************
  Function:       // recvThread
  Description:    // 该函数由clientLongAsync2In函数启动的线索调用,
                  // 主要完成如下功能：
                  // 维护长连接
                  // 接收响应数据
  Calls:          // 
  Called By:      // clientLongAsync2In
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  void * args 参数
  Output:         // 
  Return:         //  无
  Others:         // 
********************************************************************/
void * recvThread(void * args)
{
    Message   * pMsg = NULL;
    char      sRecvBuf[MY_DATA_LEN + 1];
    char      sPartBuf[MY_DATA_LEN + 1];
    int       iRecvLen=-1;
    int       iRet=-1;
    int       iPartLen=-1;
    int       iDatLen=-1;
    int       iBool=-1;
    int  iDestLen=0;
    char sDestDat[MY_DATA_LEN + 1];    

    char sMsgLen[5+1];
    char sMsgTm[6+1];
            
    for ( ;; )
    {
    	if (_RecvSockFd < 0)
    	{
    		_RecvSockFd = my_socketconnect(_ServerIp, _RecvPort, _LocalRecvPort);
    		if (_RecvSockFd < 0)
    		{
				usfErrlog("Creat_Recv_Chanel_Fail[%d]! IP=[%s] OPort=[%d] LPort=[%d]", _RecvSockFd, _ServerIp, _RecvPort, _LocalRecvPort);
				sleep(60);
				continue;
    		}
        else 
        {
				 usfErrlog("Creat_Recv_Chanel_Succ[%d]! IP=[%s] OPort=[%d] LPort=[%d]", _RecvSockFd, _ServerIp, _RecvPort, _LocalRecvPort);
        }
    	}
		  iRet = hsocketselect(TIME_OUT ,_RecvSockFd);
		  if (iRet == 0)
			{
				continue;
			}
			else if (iRet < 0)
			{
				usfErrlog("当前接收通道连接已关闭!");
				continue;
			}
			iRecvLen = 0;
/*			
			pRecvBuf = (char *)malloc(MY_DATA_LEN + 1);
			pPartBuf = (char *)malloc(MY_DATA_LEN + 1);
			if ( ( pRecvBuf == NULL ) || ( pRecvBuf == NULL ) )
			{
				usfErrlog("内存分配错误[pRecvBuf]！");
				hsocketclose(_RecvSockFd);
        hsocketclose(_SendSockFd);
				thdExit(NULL);
			}
*/			
				memset( sRecvBuf, 0x0, MY_DATA_LEN+1);
	      for ( ;; )			
	      { 
	      	memset( sPartBuf, 0x0, MY_DATA_LEN+1);
 	        iPartLen = hsocketread( _RecvSockFd, sPartBuf,1);
	      	usfErrlog("Rcv_Leader1[%d][%x]!", iPartLen,sPartBuf[0]);
	      	if ( (sPartBuf[0] !=0xef) && (sPartBuf[0] !=0x20) )
	      	{
	      		usfErrlog("Err_Leader1[%d][%x]!", iPartLen,sPartBuf[0]);
				    hsocketclose(_RecvSockFd);
          /*  hsocketclose(_SendSockFd); */
				    thdExit(NULL);	      		
	      	}
	      	if  (sPartBuf[0] == 0xef) 
	      	{
	      	  memset( sPartBuf, 0x0, MY_DATA_LEN+1);
	 	        iPartLen = hsocketread( _RecvSockFd, sPartBuf,1);
	      		usfErrlog("Rcv_Leader2[%d][%x]!", iPartLen,sPartBuf[0]);
        		if  (sPartBuf[0] !=0x14)
        		{
        			usfErrlog("ERR_Leader2[%x]",sPartBuf[0]);
        			hsocketclose(_RecvSockFd);
        		/*	hsocketclose(_SendSockFd); */
        			thdExit(NULL);
        		}	      		
	      		break;
	      	}
   				continue;	      	
	       }
	       
	      /*no use for space check		      	
        iPartLen = recv(_RecvSockFd, pPartBuf,2,0);
        usfErrlog("Rcv_Leader[%d][%x][%x]!", iPartLen,*pPartBuf,*(pPartBuf+1));
        if ( (*pPartBuf !=0xef) || (*(pPartBuf+1) !=0x14))
        {
        	usfErrlog("ERR_Leader[%x][%x]", *pPartBuf,*(pPartBuf+1));
        	free(pPartBuf);
        	free(pRecvBuf);
        	hsocketclose(_RecvSockFd);
        	hsocketclose(_SendSockFd);
        	thdExit(NULL);
        }
        */ 
        memset( sPartBuf, 0x0, MY_DATA_LEN+1);
        iPartLen = hsocketread( _RecvSockFd, sPartBuf,11);
        usfErrlog("Rcv_head[%d][%s]",iPartLen,sPartBuf);
        memset( sDestDat, 0x0, sizeof(sDestDat));       
        iDestLen=0;
        iBool=DoCypConvert(sDestDat,&iDestLen ,"01",sPartBuf,11 );
        if (iBool !=0)
        {
        	usfErrlog("DoCypConvert_UNCHEAD_ERR[%s]", sPartBuf);
        	hsocketclose(_RecvSockFd);
        	/*hsocketclose(_SendSockFd);*/
        	thdExit(NULL);
        }
        usfErrlog("DoCypConvert_UNCHEAD_RSP[%d][%s]",iDestLen,sDestDat);

        memcpy(sRecvBuf,sDestDat,11);
        iRecvLen = 11;            
        memset(sMsgLen  ,0x0,sizeof(sMsgLen));
        memset(sMsgTm,0x0,sizeof(sMsgTm));        
        memcpy(sMsgLen,sDestDat,5);
        memcpy(sMsgTm,sDestDat+5,6);        
        iDatLen  = atoi(sMsgLen)-11;
        usfErrlog("iDatLen[%d]",iDatLen);        
        memset( sPartBuf, 0x0, MY_DATA_LEN+1);
        iPartLen = hsocketread( _RecvSockFd, sPartBuf,iDatLen);
        usfErrlog("Rcv_Body[%d][%d][%s]",iPartLen,iDatLen,sPartBuf);
        if (iPartLen !=iDatLen)
        {
          usfErrlog("Rcv_Body_ERR");          
          hsocketclose(_RecvSockFd);
        	/*hsocketclose(_SendSockFd); */
        	thdExit(NULL);                    
        }
        memcpy(sRecvBuf+11,sPartBuf,iDatLen);
        iRecvLen = 11+iDatLen;        
        memset(sDestDat,0x0,sizeof(sDestDat));
        iDestLen=0;
        iBool=DoCypConvert(sDestDat,&iDestLen ,"02",sRecvBuf,iRecvLen);
        if (iBool !=0)
        {
        	usfErrlog("DoCypConvert_UncBody_ERR[%s]", sRecvBuf);
        	hsocketclose(_RecvSockFd);
        	/*hsocketclose(_SendSockFd);*/
        	thdExit(NULL);
        }
        usfErrlog("--Unc_Body[%d][%s]!", iDestLen,sDestDat);
	    
		  pMsg = (Message *)usfCreateMsg(_MsgType);
			if (pMsg == NULL)
			{
				usfErrlog("创建消息失败! IP=[%s] 已接收数据=[%d][%s]", _ServerIp, iDestLen, sDestDat);
				continue;
			}
		  usfTraceX("接收编号=[%s] IP=[%s]\n数据=[%d][%s]", pMsg->request_id, _ServerIp, iDestLen, sDestDat);
		  usfSetMsgData(pMsg, sDestDat, iDestLen);
		  usfAddMsgHeadValue(pMsg, "SCH", "rq", 2);
      if (usfSendRequest(pMsg))
			{
				usfErrlog("请求编号=[%s] 发送请求消息失败!", pMsg->request_id);
				usfDestroyMsg(pMsg);
			}
	} /* for */
    thdExit( NULL );
}

/********************************************************************
  Function:       // clientLongAsync2Out
  Description:    // 异步长连接双工中发送请求数据的入口函数。主要功能：
                  //      建立与服务端的连接
                  //      发送数据
  Calls:          //  my_socketconnect
  Called By:      // 被服务框架调用�
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  pMsg 消息
  Output:         //
  Return:         // 0:成功 !0:失败
  Others:         // 
********************************************************************/
int clientLongAsync2Out(Message * pMsg)
{
	char		aResult[6+1];
	char		aTmp[2+1];
	char		aFlag[1+1];
  int     iSendLen;
	int			iLen;
  int			iRetry=0;
	int			iFlag=0;

  int  iBool=-1;
  int  iBodyLen;
  char sDestBody[MY_DATA_LEN + 1];    
  int  iHeadLen;
  char sDestHead[MY_DATA_LEN + 1];
  char sOrgHead[11+1];
  char sLeader[2+1];
  int  iComSts=0;
  char sOutMsg[MY_DATA_LEN + 1];
  int  iOutLen;
  

	    
  /*  usfErrlog("clientLongAsync2Out发送数据:[%d][%s]",pMsg->msg_size, pMsg->msg_text);*/

	/* 需要判断是否报文解析失败, 如果是不发送 */
  usfErrlog("**********Enter_Send_Deal**********"); 
	memset(aResult, 0x00, sizeof(aResult));
	if (usfGetMsgHeadValue(pMsg, "SSC", aResult) == 0 && 
		(strcmp(aResult, NET_ERROR_RQ) == 0 ||
		 strcmp(aResult, NET_ERROR_RP) == 0))
	{
		usfDestroyMsg(pMsg);
		return (0);
	}
	strcpy(aResult, NET_ERROR_RQ);
	if (usfIsNotify(pMsg) == 0)
	{
		/* 如果是请求交易且消息头FLG为"1",需要返回通讯结果 */
		memset(aTmp, 0x00, sizeof(aTmp));
		memset(aFlag, 0x00, sizeof(aFlag));
		usfGetMsgHeadValue(pMsg, "SCH", aTmp);
		usfGetMsgHeadValue(pMsg, "FLG", aFlag);
    /*    usfErrlog("aTmp=[%s],aFlag=[%s]",aTmp,aFlag); */
		if (strcmp(aTmp, "rq") == 0 && atoi(aFlag) == 1)
		{
			iFlag = 1;
		}
	}
retry:
	thdLockMutex(&_SocketMutex);
  if (_SendSockFd < 0)  /* 需要重新连接  */
  {
  	iComSts =2;
  	usfErrlog("Err_Connect[%d][%s]!",pMsg->msg_size,pMsg->msg_text); 
  	goto rp;
  	/*不重新连接，屏蔽
		_SendSockFd = my_socketconnect(_ServerIp, _SendPort, _LocalSendPort);
		if (_SendSockFd < 0)
		{
			usfErrlog("Creat_Send_Chanel_Fail![%d] ReqId=[%s]  IP=[%s] OPort=[%d] LPort=[%d]", _SendSockFd, pMsg->request_id, _ServerIp, _SendPort, _LocalSendPort);

			thdUnlockMutex(&_SocketMutex);
			goto rp;
		}
    else
    {
       usfErrlog("Creat_Send_Chanel_SUCC![%d] Ip=[%s] OPort=[%d] LPort=[%d]", _SendSockFd,_ServerIp, _SendPort, _LocalSendPort);
    }
    */
	}
	memset(sDestBody,0x00, sizeof(sDestBody));
	iBodyLen=0;
	usfErrlog("Snd_Body[%d][%s]!",pMsg->msg_size,pMsg->msg_text); 
  iBool=DoCypConvert(sDestBody,&iBodyLen ,"03",pMsg->msg_text,pMsg->msg_size);	
	if (iBool !=0)
	{
		usfErrlog("DoCypConvert_03_ERR,exit[%d][%s]", pMsg->msg_size,pMsg->msg_text);
		/*hsocketclose(_RecvSockFd);*/
    hsocketclose(_SendSockFd);
    thdUnlockMutex(&_SocketMutex);
    iComSts=1;
		goto rp;
	}
  usfErrlog("DoCypConvert_03_Rsp[%d][%s]",iBodyLen,sDestBody);
  
	memset( sOrgHead, 0x00, sizeof(sOrgHead));
	memcpy(sOrgHead,sDestBody,11);
	memset( sDestHead, 0x00, sizeof(sDestHead));
	iHeadLen=0;
  iBool=DoCypConvert(sDestHead,&iHeadLen ,"01",sOrgHead,11);		
	if (iBool !=0)
	{
	  usfErrlog("DoCypConvert_ENCHEAD_ERR,exit[%s]", sOrgHead);
	  /*hsocketclose(_RecvSockFd);*/
    hsocketclose(_SendSockFd);
    thdUnlockMutex(&_SocketMutex);
    iComSts=1;
	  goto rp;
	}
  usfErrlog("DoCypConvert_ENCHEAD_RSP[%d][%s]",iHeadLen,sDestHead);	
	memset( sLeader, 0x00, sizeof(sLeader));
	sLeader[0]=0xef;
	sLeader[1]=0x14;
	memset( sOutMsg, 0x00, sizeof(sOutMsg));
	iOutLen=iBodyLen+2;
	memcpy(sOutMsg,sLeader,2);
	memcpy(sOutMsg+2,sDestHead,11);
	memcpy(sOutMsg+13,sDestBody+11,iBodyLen-11);	
	iLen = hsocketwrite(_SendSockFd, sOutMsg, iOutLen);
  if (iLen != iOutLen)
  {
	  usfErrlog("请求编号=[%s] 发送数据失败! IP=[%s] Port=[%d]\n数据=[%d][%s]", pMsg->request_id, _ServerIp, _SendPort, iOutLen, sOutMsg);
	  hsocketclose(_SendSockFd);
	  _SendSockFd = -1;
	  thdUnlockMutex(&_SocketMutex);
	 /* 再尝试连接1次 */
	  if (iRetry == 0)
	  {
	    usfTraceX("原有连接发送失败,尝试建立新连接!");
	    iRetry ++;
	    goto retry;
	  }
	  goto rp;
   }
	thdUnlockMutex(&_SocketMutex);
	strcpy(aResult, NET_OK);
	usfTraceX("发送编号=[%s] IP=[%s] Port=[%d]\n发送数据=[%d][%s]", pMsg->request_id, _ServerIp, _SendPort, iOutLen, sOutMsg);
rp:
  /*  usfErrlog("iFlag=[%d]",iFlag); */
	if (iFlag == 0)
	{
		usfDestroyMsg(pMsg);
		return (0);
	}
 	usfSetMsgHeadValue(pMsg, "SCH", "rp", 2);
 	usfSetMsgHeadValue(pMsg, "SSC", aResult, 6);
	if (iComSts ==1)
	{ 	
		usfSetMsgData(pMsg, "ERRECN", 6);
	}
	else if(iComSts ==2)
	{
		usfSetMsgData(pMsg, "ERRCOM", 6);		
  }
  else
	{
		usfSetMsgData(pMsg, "000000", 6);		
	}
	
	if (usfSendResponse(pMsg) < 0)
	{
		usfErrlog("发送响应消息失败!");
   		usfDestroyMsg(pMsg);
	}
  return (0);
}

/*
 * 对一个socket描述符绑定本地端口
 */
int	my_socketbind(int sockfd, char *ip, int port)
{
    struct sockaddr_in local_addr;

    /* 绑定本地网络地址及端口号 */
    memset((char *)&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    
	if (inet_pton(AF_INET, ip, &(local_addr.sin_addr)) < 0)
	{
		local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
    
    local_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr_in)) < 0) 
    {
        return (-1);
    }
    
    return (0);
}

int	my_socketconnect(char *ip, int third_port, int local_port)
{
    int                sockfd;
    struct sockaddr_in svr_addr;
    char               buff[100];

    /* 创建一个网络socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        return (-1);
    }

	/* _local_ip为全局变量 */
	if (my_socketbind(sockfd, _local_ip, local_port) < 0)
	{
		close(sockfd);
        return (-2);
	}
	
    /* 连接到其他机器  */
    memset((char *)&svr_addr, 0, sizeof(svr_addr));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = inet_addr(ip);
    svr_addr.sin_port = htons(third_port);

    if ((connect(sockfd, (struct sockaddr *)&svr_addr, sizeof(struct sockaddr))) < 0) 
    {
        close(sockfd);
        return (-3);
    }

    return (sockfd);
}

int	SocketShortConnect(char *ip, int third_port)
{
    int                sockfd;
    struct sockaddr_in svr_addr;
    char               buff[100];

    /* 创建一个网络socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        return (-1);
    }
	
    /* 连接到其他机器  */
    memset((char *)&svr_addr, 0, sizeof(svr_addr));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = inet_addr(ip);
    svr_addr.sin_port = htons(third_port);

    if ((connect(sockfd, (struct sockaddr *)&svr_addr, sizeof(struct sockaddr))) < 0) 
    {
        close(sockfd);
        return (-3);
    }
    return (sockfd);
}


int	DoSignOn(int iSockFd)
{	
	int iRet;
  int iLen;
  int iBool;
  char MsgFmt[7]="SES201";
  char DBankNo[13]="001658100000";
  char UsrId[19]="001658100000      ";
  char Passwd[9]="12345678";
  char sOrgMsg[52+1];
  int  iOrgLen=52;
  int  iDestLen;
  int  iHeadLen;
  char sDestHead[MY_DATA_LEN + 1];
  char sDestBody[MY_DATA_LEN + 1];
  char sLeader[2+1];
  char sOutMsg[MY_DATA_LEN + 1];
  int  iOutLen;
  char sPartBuf[MY_DATA_LEN + 1];
  char sRecvBuf[MY_DATA_LEN + 1];
  int iRcvLen;
  char sMsgLen[5+1];
  int iMsgLen;
  char sRspCod[4+1];	
  time_t    timer;
  struct  tm  *tblock;
  char SndDat[9];
  char sOrgHead[11+1];
 
  
	usfErrlog("DoSignOn_begin[%d]",iSockFd);
  timer = time(NULL);
  tblock = localtime(&timer);
  memset(SndDat,0x0,sizeof(SndDat));
  sprintf(SndDat, "%04d%02d%02d",    tblock->tm_year+1900,tblock->tm_mon+1, tblock->tm_mday);
  memset(sOrgMsg,0x0,sizeof(sOrgMsg));
  strcat(sOrgMsg,MsgFmt);
  strcat(sOrgMsg,DBankNo);
  strcat(sOrgMsg,SndDat);
  strcat(sOrgMsg,UsrId);
  strcat(sOrgMsg,Passwd);  
  memset(sDestBody,0x0,sizeof(sDestBody));
  iBool=rtss_code_proc_snd(sDestBody,&iDestLen,sOrgMsg,iOrgLen,_IsEnc,sMasterKey);
  if (iBool ==0)
  {
		usfErrlog("Err_DoSignOn_1[%s]",sOrgMsg);
		return (0);
  }	
  memset( sOrgHead, 0x00, sizeof(sOrgHead));
  memcpy(sOrgHead,sDestBody,11);
  memset( sDestHead, 0x00, sizeof(sDestHead));
  iBool=rtss_header_code(sDestHead,&iHeadLen,sOrgHead,11,sMasterKey);
  if (iBool ==0)
  {
		usfErrlog("Err_DoSignOn_2[%s]",sOrgHead);
		return (0);
  }
  memset( sLeader, 0x00, sizeof(sLeader));
  sLeader[0]=0xef;
  sLeader[1]=0x14;
	memset( sOutMsg, 0x00, sizeof(sOutMsg));	
	iOutLen=iDestLen+2;
	memcpy(sOutMsg,sLeader,2);
	memcpy(sOutMsg+2,sDestHead,11);
	memcpy(sOutMsg+13,sDestBody+11,iDestLen-11);	
		
	iLen = hsocketwrite(iSockFd, sOutMsg, iOutLen);
  if (iLen != iOutLen)
  {
		usfErrlog("Socketwrite_SignOn_Fail!data=[%d][%s]", iOutLen, sOutMsg);
		return(0);
  }  
	iRet = hsocketselect(TIME_OUT ,iSockFd);
	if (iRet == 0)
	{
		usfErrlog("Socketwrite_SignOn_NoResponse!data=[%d][%s]", iOutLen, sOutMsg);
		return(0);
	}
	else if (iRet < 0)
	{
		usfErrlog("Socketwrite_SignOn_NoConnect!data=[%d][%s]", iOutLen, sOutMsg);
		return(0);
	}
	memset( sRecvBuf, 0x0, MY_DATA_LEN+1);
	memset( sPartBuf, 0x0, MY_DATA_LEN+1);
  iLen= hsocketread(iSockFd, sPartBuf,2);
  
  usfErrlog("Rcv_SignOn_Leader[%d][%x][%x]!", iLen,sPartBuf[0],sPartBuf[1]);
  if ( (sPartBuf[0] !=0xef) || (sPartBuf[1] !=0x14))
  {
    usfErrlog("ERR_SignOn_Leader[%x][%x]", sPartBuf[0],sPartBuf[1]);
 		return(0);
  }
  memset( sPartBuf, 0x0, MY_DATA_LEN+1);
  iLen= hsocketread(iSockFd, sPartBuf,11);

/*  memcpy(sRecvBuf,sPartBuf,11); */
  memset( sDestHead, 0x0, sizeof(sDestHead));
  iBool=rtss_header_code(sDestHead,&iDestLen,sPartBuf,11,sMasterKey);
  if (iBool ==0)
  {
    usfErrlog("ERR_SignOn_Rcv_rtss_header_code[%s]", sPartBuf);
    return(0);
  }
  memcpy(sRecvBuf,sDestHead,11); 
  memset(sMsgLen,0,sizeof(sMsgLen));
  memcpy(sMsgLen,sDestHead,5);
  iMsgLen  = atoi(sMsgLen)-11;
  usfErrlog("Rcv_SignOnheader[%d][%s][%d]", iDestLen,sDestHead,iMsgLen);
  memset( sPartBuf, 0x0, MY_DATA_LEN+1);
  iLen= hsocketread(iSockFd, sPartBuf,iMsgLen);

  memcpy(sRecvBuf+11,sPartBuf,iMsgLen);
  iRcvLen = 11+iMsgLen;    
  memset( sDestBody, 0x00, sizeof(sDestBody));
  iBool=rtss_code_proc_rcv(sDestBody,&iDestLen,sRecvBuf,iRcvLen,_IsEnc,sMasterKey);
  if (iBool ==0)
  {
    usfErrlog("ERR_SignOn_rtss_code_proc_rcv[%s]", sPartBuf);
    return(0);
  }
  usfErrlog("Rcv_SignOn_Body[%d][%s]!", iDestLen,sDestBody);
  memset(sRspCod,0,sizeof(sRspCod));
  strcpy(sRspCod,"0000");
  if (memcmp(sDestBody+26,sRspCod,4) != 0 )
  {
    usfErrlog("ERR_SignOn_RspCOd" );
    return(0);  	
  }  
  usfErrlog("SignOn_Suc");
	return(1);
}



int	DoCypConvert(char *sDestDat,int *iDestLen ,char *sTxnTyp,  char *sOrgDat, int iOrgLen )
{
  int iSockFd=-1;	
  int iLen=-1;
  int iOutLen=-1;
  char sOutMsg[MY_DATA_LEN + 1];
  char sRspMsg[MY_DATA_LEN + 1];
  char sOrgLen[5+1];
  char sDestLen[5+1];
  int iRet;
  
	iSockFd = SocketShortConnect(_local_ip, _CrypSvrPort);
	if (iSockFd < 0)
	{
        usfErrlog("DoCypConvert_Fail! SockFd=[%d] Ip=[%s]  Port=[%d]", iSockFd,_local_ip,_CrypSvrPort);
        return (-1);        
	}
  else
  {
        usfErrlog("DoCypConvert_SockFd_SUCC! SockFd=[%d] Ip=[%s]  Port=[%d]", iSockFd,_local_ip,_CrypSvrPort);
  }
  memset(sOutMsg,0,sizeof(sOutMsg));
  memset(sOrgLen,0,sizeof(sOrgLen));
  memcpy(sOutMsg,sTxnTyp,2);
  sprintf(sOrgLen,"%05d",iOrgLen);
  memcpy(sOutMsg+2,sOrgLen,5);
  memcpy(sOutMsg+7,sOrgDat,iOrgLen);
  iOutLen=7+iOrgLen;
	iLen = hsocketwrite(iSockFd, sOutMsg, iOutLen);
  if (iLen != iOutLen)
  {
	  usfErrlog("DoCypConvert_Send_Fail!Data=[%d][%s]", iOutLen, sOutMsg);
	  hsocketclose(iSockFd);
    return (-1);	  
  }
  
	iRet = hsocketselect(TIME_OUT ,iSockFd);
	if (iRet == 0)
	{
		usfErrlog("DoCypConvert_Socketwrite_NoResponse!");
	  hsocketclose(iSockFd);
		return(-1);
	}
	else if (iRet < 0)
	{
		usfErrlog("DoCypConvert_Socketwrite_NoConnect!");
		hsocketclose(iSockFd);
		return(-1);
	}
	memset( sRspMsg, 0x0, MY_DATA_LEN+1);
  iLen = recv(iSockFd, sRspMsg,MY_DATA_LEN,0);
  
  if (iLen < 6)
  {
		usfErrlog("DoCypConvert_Socketrecv_Err!");
		hsocketclose(iSockFd);
		return(-1);   
  }
  if (strncmp(sRspMsg,"000000",6) !=0)
  {
		usfErrlog("DoCypConvert_RspCod_Err![%s]",sRspMsg);
		hsocketclose(iSockFd);
		return(-1);     	
  }
  memset(sDestLen,0,sizeof(sDestLen));  
  memcpy(sDestLen,sRspMsg+6,5);
  *iDestLen=atoi(sDestLen);
  memcpy(sDestDat,sRspMsg+11,*iDestLen);
	hsocketclose(iSockFd);
}

int mytestfun()
{
	char		aResult[6+1];
	char		aTmp[2+1];
	char		aFlag[1+1];
  int     iSendLen;
	int			iLen;
  int			iRetry=0;
	int			iFlag=0;

  int  iBool=-1;
  int  iBodyLen;
  char sDestBody[MY_DATA_LEN + 1];    
  int  iHeadLen;
  char sDestHead[MY_DATA_LEN + 1];
  char sOrgHead[11+1];
  char sLeader[2+1];
  int  iComSts=0;
  char sOutMsg[MY_DATA_LEN + 1];
  int  iOutLen;
  char msg_text[MY_DATA_LEN + 1];
  int  msg_size;
  
  memset(msg_text,0x00, sizeof(msg_text));
  strcpy(msg_text,"SET203301586000010200704239907042300000627244512200  2007061300000000000089381                         200706143007000000000000004");
  msg_size=130;
  
	memset(sDestBody,0x00, sizeof(sDestBody));
	iBodyLen=0;
	usfErrlog("Snd_Body[%d][%s]!",msg_size,msg_text); 
  iBool=DoCypConvert(sDestBody,&iBodyLen ,"03",msg_text,msg_size);	
	if (iBool !=0)
	{
		usfErrlog("DoCypConvert_03_ERR,exit[%d][%s]", msg_size,msg_text);
		return(-1);
	}
  usfErrlog("DoCypConvert_03_Rsp[%d][%s]",iBodyLen,sDestBody);
  
	memset( sOrgHead, 0x00, sizeof(sOrgHead));
	memcpy(sOrgHead,sDestBody,11);
	memset( sDestHead, 0x00, sizeof(sDestHead));
	iHeadLen=0;
  iBool=DoCypConvert(sDestHead,&iHeadLen ,"01",sOrgHead,11);		
	if (iBool !=0)
	{
	  usfErrlog("DoCypConvert_ADD01_ERR,exit[%s]", sOrgHead);
    return(-1);
	}
  usfErrlog("DoCypConvert_ADD01_RSP[%d][%s]",iHeadLen,sDestHead);	
}

int SignOk()
{
	    Message   * pMsg = NULL;
      int  iDestLen=0;
      char sDestDat[MY_DATA_LEN + 1];    
      char sMsgType[MSGLEN + 1];      /*  消息类型   */


      strcpy(sMsgType,"PLTIN0");
		  pMsg = (Message *)usfCreateMsg(sMsgType);
			if (pMsg == NULL)
			{
				usfErrlog("SignOk创建消息失败!");
				return(-1);
			}
      memset( sDestDat, 0x0, sizeof(sDestDat));
      strcpy(sDestDat,"SES202");
      iDestLen=6;      
		  usfSetMsgData(pMsg, sDestDat, iDestLen);
		  usfAddMsgHeadValue(pMsg, "SCH", "rq", 2);
      if (usfSendRequest(pMsg))
			{
				usfErrlog("SignOk请求编号=[%s] 发送请求消息失败!", pMsg->request_id);
				usfDestroyMsg(pMsg);
				return(-1);				
			}
		  return(0);
}
