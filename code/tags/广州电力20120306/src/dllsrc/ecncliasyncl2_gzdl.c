/********************************************************************      
Copyright (C),1998-2003,Hisuntech Co.,Ltd.                                
  File name:      // ecncliasyncl2.c                                   
  Author:         // WangXiaoDong                                       
  Version:        // 1.0                                               
  Date:           // 20030401                                         
  Description:    // ÕâÊÇÍâ²¿Í¨Ñ¶Ä£¿éÖÐ·þÎñ¶ËÒì²½³¤Á¬½ÓË«¹¤Ô´ÎÄ¼þ¡£      
  Others:         // Ä¿Ç°Ö»¿¼ÂÇÒ»Ìõ³¤Á¬½Ó                             
  Function List:  // Ö÷Òªº¯ÊýÁÐ±í£¬Ã¿Ìõ¼ÇÂ¼Ó¦°üÀ¨º¯ÊýÃû¼°¹¦ÄÜ¼òÒªËµÃ÷
                     serverLongAsync2In                             
                     serverLongAsync2Out                           
                     initChannel                                  
                     closeChannel                                
                     thread_main                                
                     create_connect
                     longAsync2Request                     
  History:        // ÐÞ¸ÄÀúÊ·¼ÇÂ¼ÁÐ±í£¬Ã¿ÌõÐÞ¸Ä¼ÇÂ¼Ó¦°üÀ¨ÐÞ¸ÄÈÕÆÚ¡
                  // ÐÞ¸ÄÕß¼°ÐÞ¸ÄÄÚÈÝ¼òÊö                        
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
  Description:    // ·þÎñÆô¶¯Ê±ÔËÐÐµÄ³õÊ¼»¯º¯Êý£¬Ö´ÐÐ×°ÔØIP±í¼°Ò»Ð©²ÎÊý
  Calls:          // loadIpTableAsync(char * filename) ×°ÔØip±íµÄº¯Êý
  Called By:      // ±»·þÎñ¿ò¼Üµ÷ÓÃ
  Table Accessed: // 
  Table Updated:  // 
  Input:          // argc:²ÎÊý¸öÊý
                  // argv:²ÎÊýÊý×é,°üÀ¨²ÎÊý£ºipConFile,preLenLen
  Output:         //
  Return:         // 0:³É¹¦ !0:Ê§°Ü
  Others:         // 
********************************************************************/
int initChannel(int argc, char ** argv)
{
    memset(&_ConnPara, 0x0, sizeof(CONN_PARAM));
    if (argc < 1)
    {
		usfErrlog("ÊäÈë²ÎÊý£ººÏ·¨IPÁÐ±í£¬[Ç°ÖÃ³¤¶È]");	
		return (-1);
    }  
   
	/*
	 * ÉèÖÃ±¾µØIPµØÖ·
	 * Added by liangwj in 20050127
	 */
	hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
    if (strlen(argv[0]) <= FILENAME_LEN)
    {
		strcpy(_ConnPara.ipConFile,argv[0]);	
    }
    else
    {
		usfErrlog("ÅäÖÃÎÄ¼þÃû³¬¹ý³¤¶È(%d)", FILENAME_LEN);
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
    

    usfTraceX("ÅäÖÃÎÄ¼þÃû[%s] Ç°ÖÃ³¤¶È±êÖ¾[%d] Ç°ÖÃ³¤¶È[%d]",
		argv[0], _ConnPara.havePreLen, _ConnPara.preLenLen);

    if ((_AsyncIpSockfdHead = loadIpTableAsync(argv[0])) == NULL)
    {
        usfErrlog("×°ÔØIP±íÊ§°Ü, ²»½øÐÐIPºÏ·¨ÐÔ¼ì²é.");
    }
    
    return (0);
}

/********************************************************************
  Function:       // longAsyncSend2Request
  Description:    // ½ÓÊÕÇþµÀÇëÇóÊý¾Ý
  Calls:          // hsocketselect
                  // hsocketread
                  // ReadLen
  Called By:      // thread_main
  Table Accessed: // 
  Table Updated:  // 
  Input:          // arg:²ÎÊý(CONN_DESP)
  Output:         //
  Return:         // ÎÞ
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
            usfErrlog("ÕìÌýÍøÂç¶ÁÐÅºÅÊ§°Ü, ÇëÇóÍ¨µÀÍ¨Ñ¶Á¬½ÓÒÑ¶Ï¿ª! IP=[%s]", aIpAddr);
            
            /*¹Ø±ÕµôÏìÓ¦Í¨µÀ*/
            thdLockMutex(&_ResponseLock);
            if ( _RequestFD > 0 )
            {
            	hsocketclose(_ResponseFD);
            	_ResponseFD = -1;
        	}
            thdUnlockMutex(&_ResponseLock);
            
            thdExit(NULL);
        }
        if (iResult == 0) /* ÔÚ³¬Ê±Ê±¼äÄÚÃ»ÓÐÊý¾Ýµ½´ï£¬¼ÌÐøÕìÌý */
        {
            continue;
        }
        
        
        iRecvLen = -1;
        switch (_ConnPara.havePreLen)
        {
        case HAVE_PRELEN: /*ÓÐÇ°ÖÃ³¤¶È */	
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
        	usfErrlog("½ÓÊÕÊý¾ÝÊ§°Ü, ÇëÇóÍ¨µÀÍ¨Ñ¶Á¬½ÓÒÑ¹Ø±Õ! IP=[%s]", aIpAddr);
            hsocketclose(iConnFd);
			thdLockMutex(&_RequestLock);
            _RequestFD = -1;
            thdUnlockMutex(&_RequestLock);
            if (aRecvBuf != NULL)
            {
                free(aRecvBuf);
                aRecvBuf = NULL;
            }
            
            /*¹Ø±ÕµôÏìÓ¦Í¨µÀ*/
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
            
            usfTraceX("ÇëÇó±àºÅ=[%s] ½ÓÊÕÊý¾Ý³É¹¦! IP=[%s]\nÊý¾Ý=[%d][%s]", msg->request_id, aIpAddr, iRecvLen, aRecvBuf);

            if (usfSendRequest(msg))
            {
                usfErrlog("ÇëÇó±àºÅ=[%s] ·¢ËÍÇëÇóÏûÏ¢Ê§°Ü!", msg->request_id);
                usfDestroyMsg(msg);
            }
        }
        else 
        {
            usfErrlog("´´½¨ÇëÇóÏûÏ¢Ê§°Ü! IP=[%s]\nÊý¾Ý=[%d][%s]", aIpAddr, iRecvLen, aRecvBuf);
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
            usfErrlog("ÕìÌýÍøÂç¶ÁÐÅºÅÊ§°Ü, Í¨Ñ¶Á¬½ÓÒÑ¶Ï¿ª! IP=[%s]", aIpAddr);
            
            /*¹Ø±ÕµôÇëÇóÍ¨µÀ*/
            thdLockMutex(&_RequestLock);
            if ( _RequestFD > 0 )
            {
            	hsocketclose(_RequestFD);
            	_RequestFD = -1;
        	}
            thdUnlockMutex(&_RequestLock);
            
            thdExit(NULL);
        }
        if (iResult == 0) /* ÔÚ³¬Ê±Ê±¼äÄÚÃ»ÓÐÊý¾Ýµ½´ï£¬¼ÌÐøÕìÌý */
        {
            continue;
        }
        
		iRecvLen = recv(iConnFd, aRecvBuf, sizeof(aRecvBuf), 0);		
        if (iRecvLen <= 0 )
        {
        	usfErrlog("½ÓÊÕÊý¾ÝÊ§°Ü, ÏìÓ¦Í¨µÀÍ¨Ñ¶Á¬½ÓÒÑ¹Ø±Õ! IP=[%s]", aIpAddr);
            hsocketclose(iConnFd);
			thdLockMutex(&_ResponseLock);
            _ResponseFD = -1;
            thdUnlockMutex(&_ResponseLock);
            
            /*¹Ø±ÕµôÇëÇóÍ¨µÀ*/
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
  Description:    // »ñÈ¡ÇþµÀÁ¬½Ó¡¢´´½¨ÏßË÷½¨Á¢ÓëÇþµÀµÄÁ¬½Ó¡¢´´½¨ÏßË÷½ÓÊÕÊý¾Ý
  Calls:          // create_connect
                  // longAsync2Request
  Called By:      // serverLongAsync2In
  Table Accessed: // 
  Table Updated:  // 
  Input:          // arg:²ÎÊý
  Output:         //
  Return:         // ÎÞ
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
    	 *  »ñÈ¡ÇþµÀÁ¬½Ó
    	 */
        iCliLen = sizeof(cli_addr);
        conn_desp = (CONN_DESP *)malloc(sizeof(CONN_DESP));
        if ( conn_desp == NULL ) 
        {
            usfErrlog("[request_thread_main] ·ÖÅäÄÚ´æ[CONN_DESP]Ê§°Ü!");
            continue;
        }
        memset( conn_desp, 0, sizeof(CONN_DESP) );

        iSockID = accept(_RequestListenFD, (struct sockaddr *)&cli_addr, &iCliLen);

        if (iSockID < 0) 
        {
            usfErrlog("[request_thread_main] ½ÓÊÜ(accept)Á¬½ÓÇëÇóÊ§°Ü!");
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
         * ÅÐ¶ÏipµØÖ·ºÏ·¨ÐÔ
         */
        if (checkIpAsync(_AsyncIpSockfdHead,conn_desp->ipAddr))
        {
            usfErrlog("×¢Òâ: ÓÐ·Ç·¨IPµØÖ·[%s]ÊÔÍ¼Á¬½Ó!", conn_desp->ipAddr);
            hsocketclose(_RequestFD);
            if (conn_desp != NULL)
            {
                free(conn_desp);
                conn_desp = NULL;
            }
            continue;	
        }

		/* 
		 * º¯Êý²ÎÊýÐèÒªÖØÐÂÉêÇëÄÚ´æ¿Õ¼ä
		 * Modified by liangwj at 2006-03-30
		 */
		pIpAdr = strdup(conn_desp->ipAddr);
		if (pIpAdr == NULL)
		{
            usfErrlog("ÉêÇëÄÚ´æÊ§°Ü!");
            hsocketclose(_RequestFD);
            free(conn_desp);
            conn_desp = NULL;
            continue;	
        }
			
        /*
         *  ´´½¨ÏßË÷½ÓÊÕÇþµÀÊý¾Ý
         */
        iErrno = thdCreate(&pThreadId, &pAttr, longAsyncSend2Request, 
			(void *)conn_desp);
        if (iErrno)
        {
            usfErrlog("´´½¨Êý¾Ý½ÓÊÕÏßË÷Ê§°Ü! [%d]", iErrno);
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
  Description:    // »ñÈ¡ÇþµÀÁ¬½Ó¡¢´´½¨ÏßË÷½¨Á¢ÓëÇþµÀµÄÁ¬½Ó¡¢´´½¨ÏßË÷½ÓÊÕÊý¾Ý
  Calls:          // create_connect
                  // longAsync2Request
  Called By:      // serverLongAsync2In
  Table Accessed: // 
  Table Updated:  // 
  Input:          // arg:²ÎÊý
  Output:         //
  Return:         // ÎÞ
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
    	 *  »ñÈ¡ÇþµÀÁ¬½Ó
    	 */
        iCliLen = sizeof(cli_addr);
        conn_desp = (CONN_DESP *)malloc(sizeof(CONN_DESP));
        if ( conn_desp == NULL ) 
        {
            usfErrlog("[request_thread_main] ·ÖÅäÄÚ´æ[CONN_DESP]Ê§°Ü!");
            continue;
        }
        memset( conn_desp, 0, sizeof(CONN_DESP) );

        iSockID = accept(_ResponseListenFD, (struct sockaddr *)&cli_addr, &iCliLen);

        if (iSockID < 0) 
        {
            usfErrlog("[response_thread_main] ½ÓÊÜ(accept)ÏìÓ¦Á¬½ÓÍ¨µÀÇëÇóÊ§°Ü!");
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
         * ÅÐ¶ÏipµØÖ·ºÏ·¨ÐÔ
         */
        if (checkIpAsync(_AsyncIpSockfdHead,conn_desp->ipAddr))
        {
            usfErrlog("×¢Òâ: ÓÐ·Ç·¨IPµØÖ·[%s]ÊÔÍ¼Á¬½Ó!", conn_desp->ipAddr);
            hsocketclose(_ResponseFD);
            if (conn_desp != NULL)
            {
                free(conn_desp);
                conn_desp = NULL;
            }
            continue;	
        }

		/* 
		 * º¯Êý²ÎÊýÐèÒªÖØÐÂÉêÇëÄÚ´æ¿Õ¼ä
		 * Modified by liangwj at 2006-03-30
		 */
		pIpAdr = strdup(conn_desp->ipAddr);
		if (pIpAdr == NULL)
		{
            usfErrlog("ÉêÇëÄÚ´æÊ§°Ü!");
            hsocketclose(_ResponseFD);
            free(conn_desp);
            conn_desp = NULL;
            continue;	
        }
			
        /*
         *  ´´½¨ÏßË÷½ÓÊÕÇþµÀÊý¾Ý
         */
        iErrno = thdCreate(&pThreadId, &pAttr, checkResponseSockConnection, 
			(void *)conn_desp);
        if (iErrno)
        {
            usfErrlog("´´½¨ÏìÓ¦Í¨µÀ¼ì²âÏßË÷Ê§°Ü! [%d]", iErrno);
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
  Description:    // FCAÒì²½³¤Á¬½ÓË«¹¤ÖÐFCA·þÎñ½ÓÊÕÇþµÀÇëÇóµÄÈë¿Úº¯Êý¡£
                  // Íê³ÉÈçÏÂ¹¦ÄÜ£º
                  // ½ÓÊÕ´«Èë²ÎÊý
                  // °ó¶¨¶Ë¿Ú²¢ÕìÌý
                  // ´´½¨ÏßË÷£¬ÓÉ¸ÃÏßË÷Íê³ÉºóÐø¹¦ÄÜ
  Calls:          // hsocketbindlisten
  Called By:      // ±»·þÎñ¿ò¼Ü
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  argc:²ÎÊý¸öÊý
                  //  argv:²ÎÊý[ÏûÏ¢ÀàÐÍ¡¢¶Ë¿ÚºÅ]
                  //  tid :ÏßË÷id
  Output:         //
  Return:         // 0:³É¹¦ -1£ºÊ§°Ü
  Others:         // 
********************************************************************/
int serverLongAsync2In(int argc, char ** argv, pthread_t * tid)
{
    pthread_attr_t pAttr;
    int            iErrno;

    void *thread_main(void *);
    
    if (argc < 3)
    {
        usfErrlog("ÊäÈë²ÎÊý: MsgType RequestPort ResponsePort", ERRCODE + 40);
        return (-1);
    }

    if (strlen(argv[0]) == MSGLEN)
    {
        strcpy(_ConnPara.msgType, argv[0]);
    }
    else
    {
        usfErrlog("ÏûÏ¢ÀàÐÍ³¬¹ý³¤¶È(%d)", MSGLEN);
        return (-1);
    }

    _RequestPort = atoi(argv[1]);
    if (_RequestPort <= 0)
    {
        usfErrlog("ÇëÇó¶Ë¿ÚºÅ±ØÐëÊÇÊý×Ö! [%s]",argv[1]);
        return (-1);	
    }
    _ResponsePort = atoi(argv[2]);
    if (_ResponsePort <= 0)
    {
        usfErrlog("ÏìÓ¦¶Ë¿ÚºÅ±ØÐëÊÇÊý×Ö! [%s]",argv[2]);
        return (-1);	
    }

    _RequestListenFD = hsocketbindlisten(_RequestPort);
    if ( _RequestListenFD < 0 )
    {
        usfErrlog("°ó¶¨²¢ÇëÇó¼àÌý¶Ë¿Ú(%d)Ê§°Ü!", _RequestPort);
        return (-1);
    }
    _ResponseListenFD = hsocketbindlisten(_ResponsePort);
    if ( _ResponseListenFD < 0 )
    {
        usfErrlog("°ó¶¨²¢ÏìÓ¦¼àÌý¶Ë¿Ú(%d)Ê§°Ü!", _ResponseListenFD);
        return (-1);
    }

	thdInitAttr(&pAttr);
    
    thdSetDetachState(&pAttr, PTHREAD_CREATE_UNDETACHED);
    thdSetScope(&pAttr, PTHREAD_SCOPE_SYSTEM);

    iErrno = thdCreate(&_ResponseThreadID, &pAttr, response_thread_main, NULL);
    if (iErrno)
    {
    	usfErrlog("ÏìÓ¦Ö÷ÏßË÷´´½¨Ê§°Ü! errno=[%d]", iErrno);
        thdDestroyAttr(&pAttr);
        hsocketclose(_ResponseListenFD);
        return (-1);
    }	
    iErrno = thdCreate(&_RequestThreadID, &pAttr, request_thread_main, NULL);
    if (iErrno)
    {
    	usfErrlog("ÇëÇóÖ÷ÏßË÷´´½¨Ê§°Ü! errno=[%d]", iErrno);
        thdDestroyAttr(&pAttr);
        hsocketclose(_RequestListenFD);
        return (-1);
    }	
    
    thdDestroyAttr(&pAttr);
    return (0);
}


/********************************************************************
  Function:       // serverLongAsync2Out
  Description:    // FCAÒì²½³¤Á¬½ÓË«¹¤ÖÐÏòÇþµÀ·µ»ØÏìÓ¦Êý¾ÝµÄÈë¿Úº¯Êý
  Calls:          // hsocketwrite
                  // hsocketwritebylen
  Called By:      // ±»·þÎñ¿ò¼Ü
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  msg:ÏûÏ¢
  Output:         //
  Return:         // 0:³É¹¦ -1£ºÊ§°Ü
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
		usfErrlog("ÇëÇó±àºÅ=[%s] ÏìÓ¦ÏûÏ¢Ê§°Ü, ¶Ô·½Î´½¨Á¢ÏìÓ¦Á¬½ÓÍ¨µÀ.msg=[%d][%s]", msg->request_id, msg->msg_size, msg->msg_text);
		thdUnlockMutex(&_ResponseLock);
		usfDestroyMsg(msg);
		return (-1);
	}
	
	iSockFd = _ResponseFD;
	iSendLen = msg->msg_size;
	switch (_ConnPara.havePreLen)
	{
	case HAVE_PRELEN:/*ÓÐÇ°ÖÃ³¤¶È  */	
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
	    usfErrlog("ÇëÇó±àºÅ=[%s] ·¢ËÍÊý¾ÝÊ§°Ü! Êý¾Ý=[%d][%s]", msg->request_id, iSendLen, msg->msg_text);
	    usfDestroyMsg(msg); 
	    hsocketclose(iSockFd);
	    return (-1);
	}
	usfTraceX("ÇëÇó±àºÅ=[%s] ·¢ËÍÊý¾Ý³É¹¦! Êý¾Ý=[%d][%s]", msg->request_id, iSendLen, msg->msg_text);
	usfDestroyMsg(msg);

    return (0);
}

/********************************************************************
  Function:       // closeChannel
  Description:    // ·þÎñÍË³öÊ±£¬¹Ø±ÕÆô¶¯µÄÏßË÷¡¢socket¾ä±úºÍÕìÌý¾ä±ú£
                  //¬ÊÊÍ·ÅÒì²½Í¨Ñ¶Á¬½Ó×´Ì¬ÐÅÏ¢±í
  Calls:          // freeIpTableAsync
                  // 
  Called By:      // ±»·þÎñ¿ò¼Üµ÷ÓÃ
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  
  Output:         //
  Return:         // ÎÞ
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

