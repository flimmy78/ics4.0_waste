
#include "ecnmain.h"     
#include "himmg.h"  

#define LONG_CONN  1
#define SHORT_CONN 0

char               _ServerIp[IPADDR_LEN + 1];/*  ¶Ô·½·þÎñÆ÷ipµØÖ· */
int                _RequestPort = 0;         /*  ¶Ô·½·þÎñÆ÷¶Ë¿ÚºÅ */
int                _ResponsePort = 0;        /*  ¶Ô·½·þÎñÆ÷¶Ë¿ÚºÅ */
int                _HavePreLen;              /*  0:´øÇ°ÖÃ³¤¶È 1:²»´øÇ°ÖÃ³¤¶È */
int                _PreLen;                  /*  Ç°ÖÃÓò³¤¶È  */
int				   _IncludeFlag=0;			 /*  ÊÇ·ñ°üº¬Ç°ÖÃ³¤¶È±êÖ¾ */
											 /*   0£º²»°üº¬ 1£º°üº¬ */
int				   _TimeOut;				 /*  È±Ê¡³¬Ê±Ê±¼ä */

pthread_mutex_t    _SocketMutex = PTHREAD_MUTEX_INITIALIZER;
SERVER_CONF        * _SvrConfHead;
SERVER_CONF        * _SvrConfTail;
MemoryPool         * _SvrList;
Logger			   * logger = NULL;

int					_RequestSockFD = -1;
int					_ResponseSockFD = -1;


/********************************************************************
  Function:       // initSvrConf
  Description:    // ³õÊ¼»¯½á¹¹SERVER_CONF
  Calls:          // 
  Called By:      // initChannel
  Table Accessed: // 
  Table Updated:  // 
  Input:          // args:²ÎÊý
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
  Description:    // ·þÎñÆô¶¯Ê±ÔËÐÐµÄ³õÊ¼»¯º¯Êý£¬³õÊ¼»¯Ò»Ð©²ÎÊý
  Calls:          // 
  Called By:      // ±»·þÎñ¿ò¼Üµ÷ÓÃ
  Table Accessed: // 
  Table Updated:  // 
  Input:          // argc:²ÎÊý¸öÊý
                  // argv:²ÎÊýÊý×é,°üÀ¨²ÎÊý: _ServerIp,_ServerPort
                  //      _ConnType:Á¬½ÓÀàÐÍ 0:¶ÌÁ¬½Ó 1:³¤Á¬½Ó 
                  //      _PreLen :Ç°ÖÃ³¤¶ÈÓòµÄ³¤¶È
  Output:         //
  Return:         // 0:³É¹¦ !0:Ê§°Ü
  Others:         // 
********************************************************************/
int initChannel(int argc,char **argv)
{
	int iMaxConn = 100;
	char * pTmp = NULL;

	if (argc < 3)
	{
		usfErrlog("ÇëÊäÈë±ØÐëµÄ²ÎÊý:ServerIp,RequestPort,ResponsePort,[PreLen],[TimeOut]");
		return (-1);
    }

	/*
	 * ÉèÖÃ±¾µØIPµØÖ·
	 * Added by liangwj in 20050918
	 */
	hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
    memset(_ServerIp, 0x0, sizeof(_ServerIp));
    strncpy(_ServerIp, argv[0], IPADDR_LEN);
    if ( inet_addr(_ServerIp) == INADDR_NONE )
    {
		usfErrlog("·Ç·¨µÄIPµØÖ·[%s]", _ServerIp);
		return (-1);
    }

	_RequestPort = atoi(argv[1]);
	if (_RequestPort <= 0)
    {
		usfErrlog("·Ç·¨µÄ¶Ë¿ÚºÅ[%d]", argv[1]);
		return (-1);
	}
	_ResponsePort = atoi(argv[2]);
	if (_ResponsePort <= 0)
    {
		usfErrlog("·Ç·¨µÄ¶Ë¿ÚºÅ[%d]", argv[2]);
		return (-1);
	}

	if (argc < 4)
	{
		_HavePreLen = NO_PRELEN;
	}
	else
	{
		_PreLen = atoi(argv[3]);
		_HavePreLen = HAVE_PRELEN;
		if (_PreLen <= 0)
		{
			_HavePreLen = NO_PRELEN;
		}  
	}

	if (argc < 5)
	{
		_TimeOut = TIME_OUT;
	}
	else
	{
		_TimeOut = atoi(argv[4]);
		if (_TimeOut <= 0)
		{
			_TimeOut = TIME_OUT;
		}  
	}

	usfTraceX( "[1]IP[%s]RequestPort[%d]ResponsePort[%d]Ç°ÖÃ³¤¶È[%d]È±Ê¡³¬Ê±[%d]", _ServerIp, _RequestPort, _ResponsePort, _PreLen,_TimeOut);
	
	logger = ecnCreateLogger();
	if ( !logger )
	{
		usfErrlog("´´½¨Í¨Ñ¶ÈÕÖ¾Æ÷Ê§°Ü");
        return(-1);
	}

	_SvrList = mplCreate(1, iMaxConn, sizeof(SERVER_CONF), 1, 1, initSvrConf);
	if (_SvrList == NULL)
    {
		usfErrlog("ÉêÇëÁ¬½ÓÄÚ´æ±í¿Õ¼äÊ§°Ü");
		return (-1);
	}
	
	return (0);
}

void closeAllChannel(void)
{
	if ( _RequestSockFD > 0 )
	{
		hsocketclose(_RequestSockFD);
		_RequestSockFD = -1;
	}
	if ( _ResponseSockFD > 0 )
	{
		hsocketclose(_ResponseSockFD);
		_ResponseSockFD = -1;
	}
}

/********************************************************************
  Function:       // closeChannel
  Description:    // ·þÎñÍ£Ö¹Ê±ÔËÐÐµÄº¯Êý£¬(ÓÃÓÚÍ¬²½³¤Á¬½Ó)¹Ø±ÕsocketÃèÊö·û
  Calls:          // 
  Called By:      // ±»·þÎñ¿ò¼Üµ÷ÓÃ
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
   
	closeAllChannel();
	
    /*
     * ÊÍ·Å¿Í»§¶ËÍâÁª·þÎñÐÅÏ¢±í
     */
	mplDestroy(_SvrList);
}

/********************************************************************
  Function:       // clientSyncOut
  Description:    // ·þÎñÆô¶¯ºó·¢ËÍÇëÇóºÍ½ÓÊÕÓ¦´ðÊý¾ÝµÄÈë¿Úº¯Êý
                  // ÐèÒª´ÓÇëÇó°üÖÐÈ¡OIP,OPT,ÒÔÖ§³ÖÓë¶à¸ö·þÎñÆ÷Í¨Ñ¶
  Calls:          // 
                  //
  Called By:      // ±»·þÎñ¿ò¼Üµ÷ÓÃµ
  Table Accessed: // 
  Table Updated:  // 
  Input:          // argc:²ÎÊý¸öÊý
                  // argv:²ÎÊýÊý×é
                  // tid :ÏßË÷id
  Output:         //
  Return:         // 0:³É¹¦ !0:Ê§°Ü
  Others:         // 
********************************************************************/
int clientSyncOut(Message * msg)
{
	char           * recv_buf = NULL;
	char           aCommIp[IPADDR_LEN + 1];
	int            iCommPort;    
	char           aTimeOut[4];
	char           aDeadTime[21];
	SERVER_CONF    *curr;
	struct timeval tv;
	int            iFlag,iAdd;
	int            iSockFd;
	int            iSendLen,iRecvLen,iLen;
	int            iResult;
	int            iRetry=0;
	long           lCurrTime;
	short          currSlot = -1;
	char		   aTmp[255+1];
	char		   aFileName[255+1];
	char		   * pFileData = NULL;
	int			   iFileSize=0;
	int			   iTimeOut = 0;

	usfSetMsgHeadValue(msg, "SCH", "rp", 2);
	
    /* 
     * ÅÐ¶ÏÊÇ·ñ³¬¹ý·¢ËÍÊ±¼ä
     */
    memset(aDeadTime, 0x0, sizeof(aDeadTime));
    if (usfGetMsgHeadValue( msg, "ETM", aDeadTime) == 0)
    {
        if (strlen(aDeadTime) > 0)
        {
            gettimeofday(&tv, NULL);
            lCurrTime = tv.tv_sec;
            if (lCurrTime >= atol(aDeadTime)-1)
            {
                usfErrlog("ÇëÇó±àºÅ=[%s] µ±Ç°Ê±¼ä(%ld)ÒÑ¾­³¬¹ý½»Ò×½áÊøÊ±¼ä(%ld)£¬²»·¢ËÍ!", msg->request_id, lCurrTime, atol(aDeadTime));
                goto rp;
            }
        }
        else
        {
            usfErrlog("ÇëÇó±àºÅ=[%s] ETMµÄÊýÖµ[%s]²»ºÏ·¨!", msg->request_id, aDeadTime);
            usfDestroyMsg(msg);
            return (-1);
        }
    }
    
retry:    

	thdLockMutex(&_SocketMutex);
	
    if (_RequestSockFD < 0 || _ResponseSockFD < 0 )  /* ÐèÒªÖØÐÂÁ¬½Ó  */
    {
usfErrlog("1111111111111");
    	closeAllChannel();	
		iSockFd = hsocketconnect(_ServerIp, _RequestPort);
		if (iSockFd <= 0)
		{
			usfErrlog("ÇëÇó±àºÅ=[%s] Á¬½ÓµÚÈý·½Ö÷»úÊ§°Ü! IP=[%s] Port=[%d]", msg->request_id, _ServerIp, _RequestPort);
			thdUnlockMutex(&_SocketMutex);
			goto rp;
		}
		_RequestSockFD = iSockFd;
usfErrlog("222222222222222");
		iSockFd = hsocketconnect(_ServerIp, _ResponsePort);
		if (iSockFd <= 0)
		{
			usfErrlog("ÇëÇó±àºÅ=[%s] Á¬½ÓµÚÈý·½Ö÷»úÊ§°Ü! IP=[%s] Port=[%d]", msg->request_id, _ServerIp, _ResponsePort);
			thdUnlockMutex(&_SocketMutex);
			goto rp;
		}
		_ResponseSockFD = iSockFd;
usfErrlog("333333333333333");
	}
	iSockFd = _RequestSockFD;
	switch (_HavePreLen)
	{
	case HAVE_PRELEN: /* ´øÇ°ÖÃ³¤¶È */
    	iSendLen = msg->msg_size + iFileSize;
    	sprintf(aTmp, "%.*d", _PreLen, iSendLen);
    	iSendLen += _PreLen;
    	iLen = hsocketwrite(iSockFd, aTmp, _PreLen);
    	iLen += hsocketwrite(iSockFd, msg->msg_text, msg->msg_size);
    	if (iFileSize > 0)
    	{
    		iLen += hsocketwrite(iSockFd, pFileData, iFileSize);
    	}	
		break;
    default:  /* ²»´øÇ°ÖÃ³¤¶È */
    	iSendLen = msg->msg_size + iFileSize;
    	iLen = hsocketwrite(iSockFd, msg->msg_text, msg->msg_size);
usfErrlog("4444444444444444");
    	if (iFileSize > 0)
    	{
    		iLen += hsocketwrite(iSockFd, pFileData, iFileSize);
usfErrlog("5555555555555555");
    	}
		break;
    }

    if (iLen != iSendLen)
    {
    	usfErrlog("ÇëÇó±àºÅ=[%s] ·¢ËÍÊý¾ÝÊ§°Ü! IP=[%s] Port=[%d]\nÊý¾Ý=[%d][%s]", msg->request_id, _ServerIp, _RequestPort, msg->msg_size, msg->msg_text);
		closeAllChannel();	
		thdUnlockMutex(&_SocketMutex);
		/* Ô­ÓÐµÄÁ¬½ÓÊ§Ð§,ÔÙ³¢ÊÔÁ¬½Ó1´Î */
		if (iRetry == 0)
		{
			usfTraceX("ÇëÇó±àºÅ=[%s] Ô­ÓÐÁ¬½Ó·¢ËÍÊ§°Ü,³¢ÊÔ½¨Á¢ÐÂÁ¬½Ó!", msg->request_id);
			iRetry ++;
			goto retry;
		}
		goto rp;
    }

	snprintf(aTmp, sizeof(aTmp), "%s(%d)", _ServerIp, _RequestPort);
	logComm(logger, msg->request_id, LOG_COMM_SEND, aTmp, msg->msg_size, msg->msg_text);

    /*
     * ³¬Ê±¿ØÖÆ
     */
    memset(aTimeOut, 0x0, sizeof(aTimeOut));
    usfGetMsgHeadValue(msg, "TMO", aTimeOut);

	iSockFd = _ResponseSockFD;
    if ((strlen(aTimeOut) > 0) && (hisnumber(aTimeOut) == 0))
    {
		iResult = hsocketselect(atoi(aTimeOut), iSockFd);
		iTimeOut = atoi(aTimeOut);
    }  
    else
    {
		iResult = hsocketselect(_TimeOut, iSockFd);
		iTimeOut = _TimeOut;
    }
      
    if (iResult <= 0)
    {
		usfErrlog("ÇëÇó±àºÅ=[%s] µÈ´ýÏìÓ¦³¬Ê±»òÍ¨Ñ¶Á¬½ÓÒÑ¹Ø±Õ!", msg->request_id);
        closeAllChannel();
		thdUnlockMutex(&_SocketMutex);
        goto errpc;
    }

    iLen = -1;
    switch (_HavePreLen)
    {
    case HAVE_PRELEN: /* ´øÇ°ÖÃ³¤¶È */
		iResult = hsocketreadbylen2(iSockFd, &recv_buf, &iLen, _PreLen, iTimeOut);
		if ( iResult > 0 && iResult != iLen )
		{
			//Êý¾ÝÃ»ÓÐ½ÓÊÕÍêÕû
			usfErrlog("Êý¾Ý½ÓÊÕ²»ÍêÕû,ÒÑ³¬Ê±!ÒÑ½ÓÊÕ[%d],ÐèÒª[%d]", iLen, iResult);
			iLen = -1;
		}
		iRecvLen = iLen + _PreLen;
		break;

    default: /*  ²»´øÇ°ÖÃ³¤¶È  */
		recv_buf = (char *)malloc(MAX_DATA_LEN + 1);
		if (recv_buf != NULL)
		{
			memset( recv_buf, 0x0, sizeof( recv_buf ));
			iLen = recv(iSockFd, recv_buf, MAX_DATA_LEN, 0);
			iRecvLen = iLen;
		}
		break;
    }
    thdUnlockMutex(&_SocketMutex); 

    if (iLen <= 0)
    {
		usfErrlog("ÇëÇó±àºÅ=[%s] ½ÓÊÕÏìÓ¦Êý¾ÝÊ§°Ü!", msg->request_id);
		closeAllChannel();
		if (recv_buf != NULL)
		{
			free(recv_buf);
			recv_buf = NULL;
		}
		goto errpc;
	}
	logComm(logger, msg->request_id, LOG_COMM_RECV, _ServerIp, iLen, recv_buf);
    usfSetMsgData(msg, recv_buf, iLen);
    if (recv_buf != NULL)
    {
		free(recv_buf);
		recv_buf = NULL;
    }   

    usfSetMsgHeadValue(msg, "SSC", NET_OK, 6);

    if (usfSendResponse(msg))
    {
		usfErrlog("ÇëÇó±àºÅ=[%s] ·¢ËÍÏìÓ¦ÏûÏ¢Ê§°Ü!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
    }
    
    return (0);

rp:
    usfSetMsgHeadValue(msg, "SSC", NET_ERROR_RQ, 6);
   
    if (usfSendResponse(msg))
    {
		usfErrlog("ÇëÇó±àºÅ=[%s] ·¢ËÍÏìÓ¦ÏûÏ¢Ê§°Ü!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
    }
   
	return (0);

errpc:
    usfSetMsgHeadValue(msg, "SSC", NET_ERROR_RP, 6);
   
    if (usfSendResponse(msg))
    {
		usfErrlog("ÇëÇó±àºÅ=[%s] ·¢ËÍÏìÓ¦ÏûÏ¢Ê§°Ü!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
    }

    return (0);
}
