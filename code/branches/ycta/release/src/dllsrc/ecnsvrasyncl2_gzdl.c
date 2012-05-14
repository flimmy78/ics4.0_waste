
#include "ecnmain.h"     
#include "himmg.h"  

#define LONG_CONN  1
#define SHORT_CONN 0

char               _ServerIp[IPADDR_LEN + 1];/*  �Է�������ip��ַ */
int                _RequestPort = 0;         /*  �Է��������˿ں� */
int                _ResponsePort = 0;        /*  �Է��������˿ں� */
int                _HavePreLen;              /*  0:��ǰ�ó��� 1:����ǰ�ó��� */
int                _PreLen;                  /*  ǰ���򳤶�  */
int				   _IncludeFlag=0;			 /*  �Ƿ����ǰ�ó��ȱ�־ */
											 /*   0�������� 1������ */
int				   _TimeOut;				 /*  ȱʡ��ʱʱ�� */

pthread_mutex_t    _SocketMutex = PTHREAD_MUTEX_INITIALIZER;
SERVER_CONF        * _SvrConfHead;
SERVER_CONF        * _SvrConfTail;
MemoryPool         * _SvrList;
Logger			   * logger = NULL;

int					_RequestSockFD = -1;
int					_ResponseSockFD = -1;


/********************************************************************
  Function:       // initSvrConf
  Description:    // ��ʼ���ṹSERVER_CONF
  Calls:          // 
  Called By:      // initChannel
  Table Accessed: // 
  Table Updated:  // 
  Input:          // args:����
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
  Description:    // ��������ʱ���еĳ�ʼ����������ʼ��һЩ����
  Calls:          // 
  Called By:      // �������ܵ���
  Table Accessed: // 
  Table Updated:  // 
  Input:          // argc:��������
                  // argv:��������,��������: _ServerIp,_ServerPort
                  //      _ConnType:�������� 0:������ 1:������ 
                  //      _PreLen :ǰ�ó�����ĳ���
  Output:         //
  Return:         // 0:�ɹ� !0:ʧ��
  Others:         // 
********************************************************************/
int initChannel(int argc,char **argv)
{
	int iMaxConn = 100;
	char * pTmp = NULL;

	if (argc < 3)
	{
		usfErrlog("���������Ĳ���:ServerIp,RequestPort,ResponsePort,[PreLen],[TimeOut]");
		return (-1);
    }

	/*
	 * ���ñ���IP��ַ
	 * Added by liangwj in 20050918
	 */
	hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
    memset(_ServerIp, 0x0, sizeof(_ServerIp));
    strncpy(_ServerIp, argv[0], IPADDR_LEN);
    if ( inet_addr(_ServerIp) == INADDR_NONE )
    {
		usfErrlog("�Ƿ���IP��ַ[%s]", _ServerIp);
		return (-1);
    }

	_RequestPort = atoi(argv[1]);
	if (_RequestPort <= 0)
    {
		usfErrlog("�Ƿ��Ķ˿ں�[%d]", argv[1]);
		return (-1);
	}
	_ResponsePort = atoi(argv[2]);
	if (_ResponsePort <= 0)
    {
		usfErrlog("�Ƿ��Ķ˿ں�[%d]", argv[2]);
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

	usfTraceX( "[1]IP[%s]RequestPort[%d]ResponsePort[%d]ǰ�ó���[%d]ȱʡ��ʱ[%d]", _ServerIp, _RequestPort, _ResponsePort, _PreLen,_TimeOut);
	
	logger = ecnCreateLogger();
	if ( !logger )
	{
		usfErrlog("����ͨѶ��־��ʧ��");
        return(-1);
	}

	_SvrList = mplCreate(1, iMaxConn, sizeof(SERVER_CONF), 1, 1, initSvrConf);
	if (_SvrList == NULL)
    {
		usfErrlog("���������ڴ��ռ�ʧ��");
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
  Description:    // ����ֹͣʱ���еĺ�����(����ͬ��������)�ر�socket������
  Calls:          // 
  Called By:      // �������ܵ���
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
     * �ͷſͻ�������������Ϣ��
     */
	mplDestroy(_SvrList);
}

/********************************************************************
  Function:       // clientSyncOut
  Description:    // ����������������ͽ���Ӧ�����ݵ���ں���
                  // ��Ҫ���������ȡOIP,OPT,��֧������������ͨѶ
  Calls:          // 
                  //
  Called By:      // �������ܵ��õ
  Table Accessed: // 
  Table Updated:  // 
  Input:          // argc:��������
                  // argv:��������
                  // tid :����id
  Output:         //
  Return:         // 0:�ɹ� !0:ʧ��
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
     * �ж��Ƿ񳬹�����ʱ��
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
                usfErrlog("������=[%s] ��ǰʱ��(%ld)�Ѿ��������׽���ʱ��(%ld)��������!", msg->request_id, lCurrTime, atol(aDeadTime));
                goto rp;
            }
        }
        else
        {
            usfErrlog("������=[%s] ETM����ֵ[%s]���Ϸ�!", msg->request_id, aDeadTime);
            usfDestroyMsg(msg);
            return (-1);
        }
    }
    
retry:    

	thdLockMutex(&_SocketMutex);
	
    if (_RequestSockFD < 0 || _ResponseSockFD < 0 )  /* ��Ҫ��������  */
    {
usfErrlog("1111111111111");
    	closeAllChannel();	
		iSockFd = hsocketconnect(_ServerIp, _RequestPort);
		if (iSockFd <= 0)
		{
			usfErrlog("������=[%s] ���ӵ���������ʧ��! IP=[%s] Port=[%d]", msg->request_id, _ServerIp, _RequestPort);
			thdUnlockMutex(&_SocketMutex);
			goto rp;
		}
		_RequestSockFD = iSockFd;
usfErrlog("222222222222222");
		iSockFd = hsocketconnect(_ServerIp, _ResponsePort);
		if (iSockFd <= 0)
		{
			usfErrlog("������=[%s] ���ӵ���������ʧ��! IP=[%s] Port=[%d]", msg->request_id, _ServerIp, _ResponsePort);
			thdUnlockMutex(&_SocketMutex);
			goto rp;
		}
		_ResponseSockFD = iSockFd;
usfErrlog("333333333333333");
	}
	iSockFd = _RequestSockFD;
	switch (_HavePreLen)
	{
	case HAVE_PRELEN: /* ��ǰ�ó��� */
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
    default:  /* ����ǰ�ó��� */
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
    	usfErrlog("������=[%s] ��������ʧ��! IP=[%s] Port=[%d]\n����=[%d][%s]", msg->request_id, _ServerIp, _RequestPort, msg->msg_size, msg->msg_text);
		closeAllChannel();	
		thdUnlockMutex(&_SocketMutex);
		/* ԭ�е�����ʧЧ,�ٳ�������1�� */
		if (iRetry == 0)
		{
			usfTraceX("������=[%s] ԭ�����ӷ���ʧ��,���Խ���������!", msg->request_id);
			iRetry ++;
			goto retry;
		}
		goto rp;
    }

	snprintf(aTmp, sizeof(aTmp), "%s(%d)", _ServerIp, _RequestPort);
	logComm(logger, msg->request_id, LOG_COMM_SEND, aTmp, msg->msg_size, msg->msg_text);

    /*
     * ��ʱ����
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
		usfErrlog("������=[%s] �ȴ���Ӧ��ʱ��ͨѶ�����ѹر�!", msg->request_id);
        closeAllChannel();
		thdUnlockMutex(&_SocketMutex);
        goto errpc;
    }

    iLen = -1;
    switch (_HavePreLen)
    {
    case HAVE_PRELEN: /* ��ǰ�ó��� */
		iResult = hsocketreadbylen2(iSockFd, &recv_buf, &iLen, _PreLen, iTimeOut);
		if ( iResult > 0 && iResult != iLen )
		{
			//����û�н�������
			usfErrlog("���ݽ��ղ�����,�ѳ�ʱ!�ѽ���[%d],��Ҫ[%d]", iLen, iResult);
			iLen = -1;
		}
		iRecvLen = iLen + _PreLen;
		break;

    default: /*  ����ǰ�ó���  */
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
		usfErrlog("������=[%s] ������Ӧ����ʧ��!", msg->request_id);
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
		usfErrlog("������=[%s] ������Ӧ��Ϣʧ��!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
    }
    
    return (0);

rp:
    usfSetMsgHeadValue(msg, "SSC", NET_ERROR_RQ, 6);
   
    if (usfSendResponse(msg))
    {
		usfErrlog("������=[%s] ������Ӧ��Ϣʧ��!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
    }
   
	return (0);

errpc:
    usfSetMsgHeadValue(msg, "SSC", NET_ERROR_RP, 6);
   
    if (usfSendResponse(msg))
    {
		usfErrlog("������=[%s] ������Ӧ��Ϣʧ��!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
    }

    return (0);
}
