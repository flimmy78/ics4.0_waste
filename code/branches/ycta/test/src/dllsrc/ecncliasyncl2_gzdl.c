/********************************************************************      
Copyright (C),1998-2003,Hisuntech Co.,Ltd.                                
  File name:      // ecncliasyncl2.c                                   
  Author:         // WangXiaoDong                                       
  Version:        // 1.0                                               
  Date:           // 20030401                                         
  Description:    // �����ⲿͨѶģ���з�����첽������˫��Դ�ļ���      
  Others:         // Ŀǰֻ����һ��������                             
  Function List:  // ��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��
                     serverLongAsync2In                             
                     serverLongAsync2Out                           
                     initChannel                                  
                     closeChannel                                
                     thread_main                                
                     create_connect
                     longAsync2Request                     
  History:        // �޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ
                  // �޸��߼��޸����ݼ���                        
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
  Description:    // ��������ʱ���еĳ�ʼ��������ִ��װ��IP��һЩ����
  Calls:          // loadIpTableAsync(char * filename) װ��ip��ĺ���
  Called By:      // �������ܵ���
  Table Accessed: // 
  Table Updated:  // 
  Input:          // argc:��������
                  // argv:��������,����������ipConFile,preLenLen
  Output:         //
  Return:         // 0:�ɹ� !0:ʧ��
  Others:         // 
********************************************************************/
int initChannel(int argc, char ** argv)
{
    memset(&_ConnPara, 0x0, sizeof(CONN_PARAM));
    if (argc < 1)
    {
		usfErrlog("����������Ϸ�IP�б�[ǰ�ó���]");	
		return (-1);
    }  
   
	/*
	 * ���ñ���IP��ַ
	 * Added by liangwj in 20050127
	 */
	hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
    if (strlen(argv[0]) <= FILENAME_LEN)
    {
		strcpy(_ConnPara.ipConFile,argv[0]);	
    }
    else
    {
		usfErrlog("�����ļ�����������(%d)", FILENAME_LEN);
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
    

    usfTraceX("�����ļ���[%s] ǰ�ó��ȱ�־[%d] ǰ�ó���[%d]",
		argv[0], _ConnPara.havePreLen, _ConnPara.preLenLen);

    if ((_AsyncIpSockfdHead = loadIpTableAsync(argv[0])) == NULL)
    {
        usfErrlog("װ��IP��ʧ��, ������IP�Ϸ��Լ��.");
    }
    
    return (0);
}

/********************************************************************
  Function:       // longAsyncSend2Request
  Description:    // ����������������
  Calls:          // hsocketselect
                  // hsocketread
                  // ReadLen
  Called By:      // thread_main
  Table Accessed: // 
  Table Updated:  // 
  Input:          // arg:����(CONN_DESP)
  Output:         //
  Return:         // ��
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
            usfErrlog("����������ź�ʧ��, ����ͨ��ͨѶ�����ѶϿ�! IP=[%s]", aIpAddr);
            
            /*�رյ���Ӧͨ��*/
            thdLockMutex(&_ResponseLock);
            if ( _RequestFD > 0 )
            {
            	hsocketclose(_ResponseFD);
            	_ResponseFD = -1;
        	}
            thdUnlockMutex(&_ResponseLock);
            
            thdExit(NULL);
        }
        if (iResult == 0) /* �ڳ�ʱʱ����û�����ݵ���������� */
        {
            continue;
        }
        
        
        iRecvLen = -1;
        switch (_ConnPara.havePreLen)
        {
        case HAVE_PRELEN: /*��ǰ�ó��� */	
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
        	usfErrlog("��������ʧ��, ����ͨ��ͨѶ�����ѹر�! IP=[%s]", aIpAddr);
            hsocketclose(iConnFd);
			thdLockMutex(&_RequestLock);
            _RequestFD = -1;
            thdUnlockMutex(&_RequestLock);
            if (aRecvBuf != NULL)
            {
                free(aRecvBuf);
                aRecvBuf = NULL;
            }
            
            /*�رյ���Ӧͨ��*/
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
            
            usfTraceX("������=[%s] �������ݳɹ�! IP=[%s]\n����=[%d][%s]", msg->request_id, aIpAddr, iRecvLen, aRecvBuf);

            if (usfSendRequest(msg))
            {
                usfErrlog("������=[%s] ����������Ϣʧ��!", msg->request_id);
                usfDestroyMsg(msg);
            }
        }
        else 
        {
            usfErrlog("����������Ϣʧ��! IP=[%s]\n����=[%d][%s]", aIpAddr, iRecvLen, aRecvBuf);
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
            usfErrlog("����������ź�ʧ��, ͨѶ�����ѶϿ�! IP=[%s]", aIpAddr);
            
            /*�رյ�����ͨ��*/
            thdLockMutex(&_RequestLock);
            if ( _RequestFD > 0 )
            {
            	hsocketclose(_RequestFD);
            	_RequestFD = -1;
        	}
            thdUnlockMutex(&_RequestLock);
            
            thdExit(NULL);
        }
        if (iResult == 0) /* �ڳ�ʱʱ����û�����ݵ���������� */
        {
            continue;
        }
        
		iRecvLen = recv(iConnFd, aRecvBuf, sizeof(aRecvBuf), 0);		
        if (iRecvLen <= 0 )
        {
        	usfErrlog("��������ʧ��, ��Ӧͨ��ͨѶ�����ѹر�! IP=[%s]", aIpAddr);
            hsocketclose(iConnFd);
			thdLockMutex(&_ResponseLock);
            _ResponseFD = -1;
            thdUnlockMutex(&_ResponseLock);
            
            /*�رյ�����ͨ��*/
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
  Description:    // ��ȡ�������ӡ������������������������ӡ�����������������
  Calls:          // create_connect
                  // longAsync2Request
  Called By:      // serverLongAsync2In
  Table Accessed: // 
  Table Updated:  // 
  Input:          // arg:����
  Output:         //
  Return:         // ��
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
    	 *  ��ȡ��������
    	 */
        iCliLen = sizeof(cli_addr);
        conn_desp = (CONN_DESP *)malloc(sizeof(CONN_DESP));
        if ( conn_desp == NULL ) 
        {
            usfErrlog("[request_thread_main] �����ڴ�[CONN_DESP]ʧ��!");
            continue;
        }
        memset( conn_desp, 0, sizeof(CONN_DESP) );

        iSockID = accept(_RequestListenFD, (struct sockaddr *)&cli_addr, &iCliLen);

        if (iSockID < 0) 
        {
            usfErrlog("[request_thread_main] ����(accept)��������ʧ��!");
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
         * �ж�ip��ַ�Ϸ���
         */
        if (checkIpAsync(_AsyncIpSockfdHead,conn_desp->ipAddr))
        {
            usfErrlog("ע��: �зǷ�IP��ַ[%s]��ͼ����!", conn_desp->ipAddr);
            hsocketclose(_RequestFD);
            if (conn_desp != NULL)
            {
                free(conn_desp);
                conn_desp = NULL;
            }
            continue;	
        }

		/* 
		 * ����������Ҫ���������ڴ�ռ�
		 * Modified by liangwj at 2006-03-30
		 */
		pIpAdr = strdup(conn_desp->ipAddr);
		if (pIpAdr == NULL)
		{
            usfErrlog("�����ڴ�ʧ��!");
            hsocketclose(_RequestFD);
            free(conn_desp);
            conn_desp = NULL;
            continue;	
        }
			
        /*
         *  ��������������������
         */
        iErrno = thdCreate(&pThreadId, &pAttr, longAsyncSend2Request, 
			(void *)conn_desp);
        if (iErrno)
        {
            usfErrlog("�������ݽ�������ʧ��! [%d]", iErrno);
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
  Description:    // ��ȡ�������ӡ������������������������ӡ�����������������
  Calls:          // create_connect
                  // longAsync2Request
  Called By:      // serverLongAsync2In
  Table Accessed: // 
  Table Updated:  // 
  Input:          // arg:����
  Output:         //
  Return:         // ��
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
    	 *  ��ȡ��������
    	 */
        iCliLen = sizeof(cli_addr);
        conn_desp = (CONN_DESP *)malloc(sizeof(CONN_DESP));
        if ( conn_desp == NULL ) 
        {
            usfErrlog("[request_thread_main] �����ڴ�[CONN_DESP]ʧ��!");
            continue;
        }
        memset( conn_desp, 0, sizeof(CONN_DESP) );

        iSockID = accept(_ResponseListenFD, (struct sockaddr *)&cli_addr, &iCliLen);

        if (iSockID < 0) 
        {
            usfErrlog("[response_thread_main] ����(accept)��Ӧ����ͨ������ʧ��!");
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
         * �ж�ip��ַ�Ϸ���
         */
        if (checkIpAsync(_AsyncIpSockfdHead,conn_desp->ipAddr))
        {
            usfErrlog("ע��: �зǷ�IP��ַ[%s]��ͼ����!", conn_desp->ipAddr);
            hsocketclose(_ResponseFD);
            if (conn_desp != NULL)
            {
                free(conn_desp);
                conn_desp = NULL;
            }
            continue;	
        }

		/* 
		 * ����������Ҫ���������ڴ�ռ�
		 * Modified by liangwj at 2006-03-30
		 */
		pIpAdr = strdup(conn_desp->ipAddr);
		if (pIpAdr == NULL)
		{
            usfErrlog("�����ڴ�ʧ��!");
            hsocketclose(_ResponseFD);
            free(conn_desp);
            conn_desp = NULL;
            continue;	
        }
			
        /*
         *  ��������������������
         */
        iErrno = thdCreate(&pThreadId, &pAttr, checkResponseSockConnection, 
			(void *)conn_desp);
        if (iErrno)
        {
            usfErrlog("������Ӧͨ���������ʧ��! [%d]", iErrno);
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
  Description:    // FCA�첽������˫����FCA������������������ں�����
                  // ������¹��ܣ�
                  // ���մ������
                  // �󶨶˿ڲ�����
                  // �����������ɸ�������ɺ�������
  Calls:          // hsocketbindlisten
  Called By:      // ��������
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  argc:��������
                  //  argv:����[��Ϣ���͡��˿ں�]
                  //  tid :����id
  Output:         //
  Return:         // 0:�ɹ� -1��ʧ��
  Others:         // 
********************************************************************/
int serverLongAsync2In(int argc, char ** argv, pthread_t * tid)
{
    pthread_attr_t pAttr;
    int            iErrno;

    void *thread_main(void *);
    
    if (argc < 3)
    {
        usfErrlog("�������: MsgType RequestPort ResponsePort", ERRCODE + 40);
        return (-1);
    }

    if (strlen(argv[0]) == MSGLEN)
    {
        strcpy(_ConnPara.msgType, argv[0]);
    }
    else
    {
        usfErrlog("��Ϣ���ͳ�������(%d)", MSGLEN);
        return (-1);
    }

    _RequestPort = atoi(argv[1]);
    if (_RequestPort <= 0)
    {
        usfErrlog("����˿ںű���������! [%s]",argv[1]);
        return (-1);	
    }
    _ResponsePort = atoi(argv[2]);
    if (_ResponsePort <= 0)
    {
        usfErrlog("��Ӧ�˿ںű���������! [%s]",argv[2]);
        return (-1);	
    }

    _RequestListenFD = hsocketbindlisten(_RequestPort);
    if ( _RequestListenFD < 0 )
    {
        usfErrlog("�󶨲���������˿�(%d)ʧ��!", _RequestPort);
        return (-1);
    }
    _ResponseListenFD = hsocketbindlisten(_ResponsePort);
    if ( _ResponseListenFD < 0 )
    {
        usfErrlog("�󶨲���Ӧ�����˿�(%d)ʧ��!", _ResponseListenFD);
        return (-1);
    }

	thdInitAttr(&pAttr);
    
    thdSetDetachState(&pAttr, PTHREAD_CREATE_UNDETACHED);
    thdSetScope(&pAttr, PTHREAD_SCOPE_SYSTEM);

    iErrno = thdCreate(&_ResponseThreadID, &pAttr, response_thread_main, NULL);
    if (iErrno)
    {
    	usfErrlog("��Ӧ����������ʧ��! errno=[%d]", iErrno);
        thdDestroyAttr(&pAttr);
        hsocketclose(_ResponseListenFD);
        return (-1);
    }	
    iErrno = thdCreate(&_RequestThreadID, &pAttr, request_thread_main, NULL);
    if (iErrno)
    {
    	usfErrlog("��������������ʧ��! errno=[%d]", iErrno);
        thdDestroyAttr(&pAttr);
        hsocketclose(_RequestListenFD);
        return (-1);
    }	
    
    thdDestroyAttr(&pAttr);
    return (0);
}


/********************************************************************
  Function:       // serverLongAsync2Out
  Description:    // FCA�첽������˫����������������Ӧ���ݵ���ں���
  Calls:          // hsocketwrite
                  // hsocketwritebylen
  Called By:      // ��������
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  msg:��Ϣ
  Output:         //
  Return:         // 0:�ɹ� -1��ʧ��
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
		usfErrlog("������=[%s] ��Ӧ��Ϣʧ��, �Է�δ������Ӧ����ͨ��.msg=[%d][%s]", msg->request_id, msg->msg_size, msg->msg_text);
		thdUnlockMutex(&_ResponseLock);
		usfDestroyMsg(msg);
		return (-1);
	}
	
	iSockFd = _ResponseFD;
	iSendLen = msg->msg_size;
	switch (_ConnPara.havePreLen)
	{
	case HAVE_PRELEN:/*��ǰ�ó���  */	
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
	    usfErrlog("������=[%s] ��������ʧ��! ����=[%d][%s]", msg->request_id, iSendLen, msg->msg_text);
	    usfDestroyMsg(msg); 
	    hsocketclose(iSockFd);
	    return (-1);
	}
	usfTraceX("������=[%s] �������ݳɹ�! ����=[%d][%s]", msg->request_id, iSendLen, msg->msg_text);
	usfDestroyMsg(msg);

    return (0);
}

/********************************************************************
  Function:       // closeChannel
  Description:    // �����˳�ʱ���ر�������������socket�������������
                  //���ͷ��첽ͨѶ����״̬��Ϣ��
  Calls:          // freeIpTableAsync
                  // 
  Called By:      // �������ܵ���
  Table Accessed: // 
  Table Updated:  // 
  Input:          //  
  Output:         //
  Return:         // ��
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

