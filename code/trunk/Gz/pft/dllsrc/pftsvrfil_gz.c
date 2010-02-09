/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : pftsvrfil_gz.c
 Author         : WangXiaoDong
 Version        : 1.0
 Date           : 2003-03-27
 Description    : ÕâÊÇÍâ²¿Í¨Ñ¶Ä£¿éÖÐ¿Í»§¶ËÍ¬²½Á¬½ÓÔ´ÎÄ¼þ
 Others         : Ä¿Ç°Ö»¿¼ÂÇÒ»Ìõ³¤Á¬½Ó   
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-03-27  WangXD      Íê³É
  002   2006-03-22  LiangWJ     ÐÞ¸Ä
  003		2007-06-15  WangXF      ÐÞ¸Ä
        ×¢£ºÕë¶Ô²ÆË°ÏµÍ³ÐèÇó£¬Í¨Ñ¶²ÉÓÃ¶ÌÁ¬½Ó£¬Ò»´ÎÁ¬½Ó¶à´Î½»»¥ÐÅÏ¢£¬
        ±¾Í¨Ñ¶½Ó¿ÚÍ¨¹ýÏûÏ¢Í·SNCÅÐ¶ÏÊÇ·ñ±£ÁôÁ¬½Ó¡£
******************************************************************************/      
#include "ecnmain.h"       

#define LONG_CONN  1
#define SHORT_CONN 0

char               _ServerIp[IPADDR_LEN + 1];/*  ¶Ô·½·þÎñÆ÷ipµØÖ· */
int                _ServerPort;              /*  ¶Ô·½·þÎñÆ÷¶Ë¿ÚºÅ */
int                _ConnType;                /*  0£º¶ÌÁ¬½Ó 1£º³¤Á¬½Ó  */
int                _HavePreLen;              /*  0:´øÇ°ÖÃ³¤¶È 1:²»´øÇ°ÖÃ³¤¶È */
int                _PreLen;                  /*  Ç°ÖÃÓò³¤¶È  */
int				   _IncludeFlag=0;			 /*  ÊÇ·ñ°üº¬Ç°ÖÃ³¤¶È±êÖ¾ */
											 /*   0£º²»°üº¬ 1£º°üº¬ */
int				   _TimeOut;				 /*  È±Ê¡³¬Ê±Ê±¼ä */

pthread_mutex_t    _SocketMutex = PTHREAD_MUTEX_INITIALIZER;
SERVER_CONF        * _SvrConfHead;
SERVER_CONF        * _SvrConfTail;
MemoryPool         * _SvrList;

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
	int iMaxConn;

	if (argc < 3)
	{
		/* modified by yu_qj, 2004-6-2
		usfErrlog("[%d]ÇëÊäÈë±ØÐëµÄ²ÎÊý:ServerIp,ServerPort,ConnType,[MaxConn],[PreLen]", ERRCODE+1);
		*/
		usfErrlog("ÇëÊäÈë±ØÐëµÄ²ÎÊý:ServerIp,ServerPort,ConnType,[MaxConn],[PreLen],[TimeOut]");
		return (-1);
    }

	/*
	 * ÉèÖÃ±¾µØIPµØÖ·
	 * Added by liangwj in 20050918
	 */
	hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
    memset(_ServerIp, 0x0, sizeof(_ServerIp));
    strncpy(_ServerIp, argv[0], IPADDR_LEN);
    if (inet_addr(_ServerIp) < 0)
    {
		usfErrlog("·Ç·¨µÄIPµØÖ·[%s]", _ServerIp);
		return (-1);
    }

	_ServerPort = atoi(argv[1]);
	if (_ServerPort <= 0)
    {
		usfErrlog("·Ç·¨µÄ¶Ë¿ÚºÅ");
		return (-1);
	}

	_ConnType = atoi(argv[2]);
	if ((_ConnType != SHORT_CONN) && (_ConnType != LONG_CONN))
	{
		usfErrlog("Á¬½ÓÀàÐÍ±êÖ¾´í[%d]", _ConnType);
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

	usfTraceX( "[1]IP[%s]Port[%d]Á¬½ÓÀàÐÍ[%d]×î´óÁ¬½ÓÊýÄ¿[%d]Ç°ÖÃ³¤¶È[%d]È±Ê¡³¬Ê±[%d]", _ServerIp, _ServerPort, _ConnType,iMaxConn,_PreLen,_TimeOut);


	_SvrList = mplCreate(1, iMaxConn, sizeof(SERVER_CONF), 1, 1, initSvrConf);
	if (_SvrList == NULL)
    {
		usfErrlog("ÉêÇëÁ¬½ÓÄÚ´æ±í¿Õ¼äÊ§°Ü");
		return (-1);
	}

	return (0);
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
   
	
		for (i = 0; i < _SvrList->cursize; i++)
		{
			if (_SvrList->allocedpos[i] == 1)
			{
				p = ( SERVER_CONF *)_SvrList->addr[i];
				hsocketclose( p->sockFd);
			}
		}
	
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
	char           * recv_buf = NULL, * send_buf = NULL, *temp_buf = NULL;
	char           aCommIp[IPADDR_LEN + 1];
	int            iCommPort;    
	char           aTimeOut[4];
	char           aDeadTime[11];
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
	char				aContFlag[2];

	usfSetMsgHeadValue(msg, "SCH", "rp", 2);

    /*
     *
     * ÅÐ¶ÏÊÇÊ¹ÓÃÏûÏ¢Í·ÖÐµÄipµØÖ·ºÍ¶Ë¿ÚºÅ£¬»¹ÊÇÊ¹ÓÃÈ±Ê¡µÄipµØÖ·ºÍ¶Ë¿ÚºÅ
     */
	memset(aCommIp, 0x0, sizeof(aCommIp));      
	judgeSvrIpPort(msg, _ServerIp, _ServerPort, aCommIp, &iCommPort);

    /* 
     * ÅÐ¶ÏÊÇ·ñ³¬¹ý·¢ËÍÊ±¼ä
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
    
    iFlag = 0; /* iFlag = 0±íÊ¾±ØÐë½¨Á¢Á¬½Ó  ==1 ²»ÐèÒªÁ¬½Ó*/
    iAdd  = 0; /* iAdd = 0 ±íÊ¾½¨Á¢µÄÊÇÐÂÁ¬½Ó ==1 Ô­À´µÄ*/
	thdLockMutex(&_SocketMutex);
    if ( strncmp(msg->msg_text,"login",5) != 0 )/*·ÇÊ×´Î»á»°£¬²»ÐèÒªÁ¬½Ó*/
    {
retry:
		usfErrlog("ÇëÇó±àºÅ=[%s] Æ¥ÅäÔ­À´µÄÁ¬½Ó! IP=[%s] Port=[%d]\nÊý¾Ý=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, msg->msg_text);
	
       /*
        *  ´ÓÒÑ¾­ÍâÁªµÄ·þÎñÆ÷±íÖÐËÑÑ°µ±Ç°ÒªÁªµÄ·þÎñÆ÷ÊÇ·ñÒÑ´æÔÚ£¬
        *  ÓëÆäÁ¬½ÓÊÇ·ñ»¹¿ÉÓÃ
        */
     	currSlot = checkConnectedSvrInfo(_SvrList, aCommIp, iCommPort, &iFlag, &iAdd, &iSockFd);
/*usfErrlog("ÇëÇó±àºÅ=[%d] µ±Ç°²ÛÎ»[%d]", msg->request_id,currSlot);
*/
     	if (iFlag == 0)  /* Á¬½ÓÒÑÊ§Ð§  */
    	{
			usfErrlog("ÇëÇó±àºÅ=[%s] Á¬½ÓÒÑÊ§Ð§! IP=[%s] Port=[%d]\nÊý¾Ý=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, msg->msg_text);
			mplFree(_SvrList, currSlot);

			thdUnlockMutex(&_SocketMutex);
			goto rp;
		}

		if ((currSlot < 0) || (currSlot >= _SvrList->cursize))
		{
			usfErrlog("ÇëÇó±àºÅ=[%s] µ±Ç°²ÛÎ»·Ç·¨", msg->request_id);
			usfDestroyMsg(msg);
			hsocketclose(iSockFd);
			mplFree(_SvrList, currSlot);
			thdUnlockMutex(&_SocketMutex);
			return (-1);
		}
	}
	else   /*½¨Á¢Á¬½Ó*/
	{
		usfErrlog("ÇëÇó±àºÅ=[%s] ÐÂ½¨Á¬½Ó! IP=[%s] Port=[%d]\nÊý¾Ý=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, msg->msg_text);
			
		iSockFd = hsocketconnect(aCommIp, iCommPort);
		if (iSockFd <= 0)
		{
			usfErrlog("ÇëÇó±àºÅ=[%s] Á¬½ÓµÚÈý·½Ö÷»úÊ§°Ü! IP=[%s] Port=[%d]", msg->request_id, aCommIp, iCommPort);
			thdUnlockMutex(&_SocketMutex);
			
			goto rp;
		}
		currSlot = addConnectToSvrInfo(_SvrList, aCommIp, iCommPort, iSockFd);
		if (currSlot < 0)
		{
			if (currSlot == -2)
			{
				usfErrlog("ÇëÇó±àºÅ=[%s] ÉêÇëÄÚ´æSERVER_CONFÊ§°Ü!", msg->request_id);
			}
			if (currSlot == -3)
			{
				usfErrlog("ÇëÇó±àºÅ=[%s] Á¬½ÓÊýÒÑÂú!", msg->request_id);
 			}
			thdUnlockMutex(&_SocketMutex);
			hsocketclose(iSockFd);
			usfDestroyMsg(msg);
			return (-1);
		}
		/*usfErrlog("ÇëÇó±àºÅ=[%d] µ±Ç°²ÛÎ»[%d]", msg->request_id,currSlot);
		*/
  	}
	thdUnlockMutex(&_SocketMutex);

	 /* ²»´øÇ°ÖÃ³¤¶È£¬·¢ËÍÇ°Ôö¼ÓÁ½Î»Ç°µ¼·û */
    iSendLen = msg->msg_size + 2;	
	send_buf = (char *)malloc(iSendLen + 1);
	if (send_buf != NULL)
	{
		memset( send_buf, 0x0, sizeof( send_buf ));
		
		sprintf(send_buf,"%c%c%s",0xef,0x14,msg->msg_text);
    	usfErrlog("ÇëÇó±àºÅ=[%s] ·¢ËÍÊý¾Ý! IP=[%s] Port=[%d]\nÊý¾Ý=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, send_buf);

	}
	else
    {
		usfErrlog("ÇëÇó±àºÅ=[%s] ÉêÇëÄÚ´æ¿Õ¼äÊ§°Ü!", msg->request_id);
		hsocketclose(iSockFd);
	
		thdLockMutex(&curr->conn_lock);
		curr->sockFd = 0;
		thdUnlockMutex(&curr->conn_lock);
		            
		return(-1);
	}
    /*iLen = hsocketwrite(iSockFd, send_buf, msg->msg_size + 2);*/
    iLen = write(iSockFd, send_buf, msg->msg_size + 2);
   	if (iLen != iSendLen)
    {
    	usfErrlog("ÇëÇó±àºÅ=[%s] ·¢ËÍÊý¾ÝÊ§°Ü! IP=[%s] Port=[%d]\nÊý¾Ý=[%d][%s][%d]", msg->request_id, aCommIp, iCommPort, msg->msg_size+2, send_buf,iLen);
		hsocketclose(iSockFd);
		if (send_buf != NULL)
		{
			free(send_buf);
			send_buf = NULL;
		}
		goto rp;
    }
	usfTraceX("ÇëÇó±àºÅ=[%s] ·¢ËÍÊý¾Ý³É¹¦! IP=[%s] Port=[%d]\nÊý¾Ý=[%d][%s] ", msg->request_id, aCommIp, iCommPort, msg->msg_size+2, send_buf);
    
	if (send_buf != NULL)
	{
		free(send_buf);
		send_buf = NULL;
	}
	strcpy(aContFlag,"0");
	if (usfGetMsgHeadValue(msg, "SNC", aContFlag) == 0)
	{
		if (aContFlag[0] == '0') 
   		{  /* ÎÞºóÐø×Ó½»Ò× */
    		usfTraceX("ÎÞºóÐø½»Ò×£¬ÍË³ö½ÓÊÕÊý¾Ý");
    		hsocketshutdown(iSockFd, 1);
		}
	}
    /*
     * ³¬Ê±¿ØÖÆ
     */
    memset(aTimeOut, 0x0, sizeof(aTimeOut));
    usfGetMsgHeadValue(msg, "TMO", aTimeOut);
    /* 
     * hisnumber·µ»Ø0ÎªÈ«Êý×Ö
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
		usfErrlog("ÇëÇó±àºÅ=[%s] µÈ´ýÏìÓ¦³¬Ê±»òÍ¨Ñ¶Á¬½ÓÒÑ¹Ø±Õ!", msg->request_id);
		hsocketclose(iSockFd);

		curr = (SERVER_CONF *)_SvrList->addr[currSlot];

		thdLockMutex(&curr->conn_lock);
		curr->sockFd = 0;
		mplFree(_SvrList, currSlot);
		thdUnlockMutex(&curr->conn_lock);
      
      	goto errpc;
    }

    iLen = -1;
    /*  ²»´øÇ°ÖÃ³¤¶È  */
	recv_buf = (char *)malloc(MAX_DATA_LEN + 1);
	if ( recv_buf == NULL )
	{
		hsocketclose(iSockFd);
		usfDestroyMsg(msg);
		usfErrlog("ÇëÇó±àºÅ=[%s] ÉêÇëÄÚ´æÊ§°Ü", msg->request_id);

		return (-1);
	}
	temp_buf = (char *)malloc(MAX_DATA_LEN + 1);
	if ( temp_buf == NULL )
	{
		hsocketclose(iSockFd);
		usfDestroyMsg(msg);
		free(recv_buf);
		usfErrlog("ÇëÇó±àºÅ=[%s] ÉêÇëÄÚ´æÊ§°Ü", msg->request_id);
		
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
usfErrlog("ÇëÇó±àºÅ=[%s] ½ÓÊÕÊý¾Ý[%s][%d]", msg->request_id,temp_buf,iLen);
		}
		*/
		iLen = recv(iSockFd, recv_buf, MAX_DATA_LEN, 0);
usfErrlog("ÇëÇó±àºÅ=[%s] ½ÓÊÕÊý¾Ý[%s][%d]", msg->request_id,recv_buf,iLen);

	}
	free(temp_buf);
	temp_buf = NULL;
	iRecvLen = iLen;
	if (iRecvLen <= 0)
    {
		usfErrlog("ÇëÇó±àºÅ=[%s] ½ÓÊÕÏìÓ¦Êý¾ÝÊ§°Ü!", msg->request_id);
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

	usfTraceX("ÇëÇó±àºÅ=[%s] ½ÓÊÕÊý¾Ý³É¹¦! IP=[%s]\nÊý¾Ý=[%d][%s]", msg->request_id, aCommIp, iLen, recv_buf);
		
    /*Ð´ÈëÏûÏ¢Ç°¹ýÂËµôÁ½Î»Ç°µ¼·û*/
    usfSetMsgData(msg, recv_buf+2, iLen - 2);
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
	strcpy(aContFlag,"0");
	if (usfGetMsgHeadValue(msg, "SNC", aContFlag) == 0)
	{
		if (aContFlag[0] == '0') 
		{  /* ÎÞºóÐø×Ó½»Ò× */
    		usfTraceX("ÎÞºóÐø½»Ò×£¬ÇåÀíÁ¬½ÓÐÅÏ¢");
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
