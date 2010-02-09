/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : pftsvrfil_gz.c
 Author         : WangXiaoDong
 Version        : 1.0
 Date           : 2003-03-27
 Description    : �����ⲿͨѶģ���пͻ���ͬ������Դ�ļ�
 Others         : Ŀǰֻ����һ��������   
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-03-27  WangXD      ���
  002   2006-03-22  LiangWJ     �޸�
  003		2007-06-15  WangXF      �޸�
        ע����Բ�˰ϵͳ����ͨѶ���ö����ӣ�һ�����Ӷ�ν�����Ϣ��
        ��ͨѶ�ӿ�ͨ����ϢͷSNC�ж��Ƿ������ӡ�
******************************************************************************/      
#include "ecnmain.h"       

#define LONG_CONN  1
#define SHORT_CONN 0

char               _ServerIp[IPADDR_LEN + 1];/*  �Է�������ip��ַ */
int                _ServerPort;              /*  �Է��������˿ں� */
int                _ConnType;                /*  0�������� 1��������  */
int                _HavePreLen;              /*  0:��ǰ�ó��� 1:����ǰ�ó��� */
int                _PreLen;                  /*  ǰ���򳤶�  */
int				   _IncludeFlag=0;			 /*  �Ƿ����ǰ�ó��ȱ�־ */
											 /*   0�������� 1������ */
int				   _TimeOut;				 /*  ȱʡ��ʱʱ�� */

pthread_mutex_t    _SocketMutex = PTHREAD_MUTEX_INITIALIZER;
SERVER_CONF        * _SvrConfHead;
SERVER_CONF        * _SvrConfTail;
MemoryPool         * _SvrList;

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
	int iMaxConn;

	if (argc < 3)
	{
		/* modified by yu_qj, 2004-6-2
		usfErrlog("[%d]���������Ĳ���:ServerIp,ServerPort,ConnType,[MaxConn],[PreLen]", ERRCODE+1);
		*/
		usfErrlog("���������Ĳ���:ServerIp,ServerPort,ConnType,[MaxConn],[PreLen],[TimeOut]");
		return (-1);
    }

	/*
	 * ���ñ���IP��ַ
	 * Added by liangwj in 20050918
	 */
	hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
    memset(_ServerIp, 0x0, sizeof(_ServerIp));
    strncpy(_ServerIp, argv[0], IPADDR_LEN);
    if (inet_addr(_ServerIp) < 0)
    {
		usfErrlog("�Ƿ���IP��ַ[%s]", _ServerIp);
		return (-1);
    }

	_ServerPort = atoi(argv[1]);
	if (_ServerPort <= 0)
    {
		usfErrlog("�Ƿ��Ķ˿ں�");
		return (-1);
	}

	_ConnType = atoi(argv[2]);
	if ((_ConnType != SHORT_CONN) && (_ConnType != LONG_CONN))
	{
		usfErrlog("�������ͱ�־��[%d]", _ConnType);
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

	usfTraceX( "[1]IP[%s]Port[%d]��������[%d]���������Ŀ[%d]ǰ�ó���[%d]ȱʡ��ʱ[%d]", _ServerIp, _ServerPort, _ConnType,iMaxConn,_PreLen,_TimeOut);


	_SvrList = mplCreate(1, iMaxConn, sizeof(SERVER_CONF), 1, 1, initSvrConf);
	if (_SvrList == NULL)
    {
		usfErrlog("���������ڴ��ռ�ʧ��");
		return (-1);
	}

	return (0);
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
   
	
		for (i = 0; i < _SvrList->cursize; i++)
		{
			if (_SvrList->allocedpos[i] == 1)
			{
				p = ( SERVER_CONF *)_SvrList->addr[i];
				hsocketclose( p->sockFd);
			}
		}
	
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
     * �ж���ʹ����Ϣͷ�е�ip��ַ�Ͷ˿ںţ�����ʹ��ȱʡ��ip��ַ�Ͷ˿ں�
     */
	memset(aCommIp, 0x0, sizeof(aCommIp));      
	judgeSvrIpPort(msg, _ServerIp, _ServerPort, aCommIp, &iCommPort);

    /* 
     * �ж��Ƿ񳬹�����ʱ��
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
    
    iFlag = 0; /* iFlag = 0��ʾ���뽨������  ==1 ����Ҫ����*/
    iAdd  = 0; /* iAdd = 0 ��ʾ�������������� ==1 ԭ����*/
	thdLockMutex(&_SocketMutex);
    if ( strncmp(msg->msg_text,"login",5) != 0 )/*���״λỰ������Ҫ����*/
    {
retry:
		usfErrlog("������=[%s] ƥ��ԭ��������! IP=[%s] Port=[%d]\n����=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, msg->msg_text);
	
       /*
        *  ���Ѿ������ķ�����������Ѱ��ǰҪ���ķ������Ƿ��Ѵ��ڣ�
        *  ���������Ƿ񻹿���
        */
     	currSlot = checkConnectedSvrInfo(_SvrList, aCommIp, iCommPort, &iFlag, &iAdd, &iSockFd);
/*usfErrlog("������=[%d] ��ǰ��λ[%d]", msg->request_id,currSlot);
*/
     	if (iFlag == 0)  /* ������ʧЧ  */
    	{
			usfErrlog("������=[%s] ������ʧЧ! IP=[%s] Port=[%d]\n����=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, msg->msg_text);
			mplFree(_SvrList, currSlot);

			thdUnlockMutex(&_SocketMutex);
			goto rp;
		}

		if ((currSlot < 0) || (currSlot >= _SvrList->cursize))
		{
			usfErrlog("������=[%s] ��ǰ��λ�Ƿ�", msg->request_id);
			usfDestroyMsg(msg);
			hsocketclose(iSockFd);
			mplFree(_SvrList, currSlot);
			thdUnlockMutex(&_SocketMutex);
			return (-1);
		}
	}
	else   /*��������*/
	{
		usfErrlog("������=[%s] �½�����! IP=[%s] Port=[%d]\n����=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, msg->msg_text);
			
		iSockFd = hsocketconnect(aCommIp, iCommPort);
		if (iSockFd <= 0)
		{
			usfErrlog("������=[%s] ���ӵ���������ʧ��! IP=[%s] Port=[%d]", msg->request_id, aCommIp, iCommPort);
			thdUnlockMutex(&_SocketMutex);
			
			goto rp;
		}
		currSlot = addConnectToSvrInfo(_SvrList, aCommIp, iCommPort, iSockFd);
		if (currSlot < 0)
		{
			if (currSlot == -2)
			{
				usfErrlog("������=[%s] �����ڴ�SERVER_CONFʧ��!", msg->request_id);
			}
			if (currSlot == -3)
			{
				usfErrlog("������=[%s] ����������!", msg->request_id);
 			}
			thdUnlockMutex(&_SocketMutex);
			hsocketclose(iSockFd);
			usfDestroyMsg(msg);
			return (-1);
		}
		/*usfErrlog("������=[%d] ��ǰ��λ[%d]", msg->request_id,currSlot);
		*/
  	}
	thdUnlockMutex(&_SocketMutex);

	 /* ����ǰ�ó��ȣ�����ǰ������λǰ���� */
    iSendLen = msg->msg_size + 2;	
	send_buf = (char *)malloc(iSendLen + 1);
	if (send_buf != NULL)
	{
		memset( send_buf, 0x0, sizeof( send_buf ));
		
		sprintf(send_buf,"%c%c%s",0xef,0x14,msg->msg_text);
    	usfErrlog("������=[%s] ��������! IP=[%s] Port=[%d]\n����=[%d][%s]", msg->request_id, aCommIp, iCommPort, msg->msg_size, send_buf);

	}
	else
    {
		usfErrlog("������=[%s] �����ڴ�ռ�ʧ��!", msg->request_id);
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
    	usfErrlog("������=[%s] ��������ʧ��! IP=[%s] Port=[%d]\n����=[%d][%s][%d]", msg->request_id, aCommIp, iCommPort, msg->msg_size+2, send_buf,iLen);
		hsocketclose(iSockFd);
		if (send_buf != NULL)
		{
			free(send_buf);
			send_buf = NULL;
		}
		goto rp;
    }
	usfTraceX("������=[%s] �������ݳɹ�! IP=[%s] Port=[%d]\n����=[%d][%s] ", msg->request_id, aCommIp, iCommPort, msg->msg_size+2, send_buf);
    
	if (send_buf != NULL)
	{
		free(send_buf);
		send_buf = NULL;
	}
	strcpy(aContFlag,"0");
	if (usfGetMsgHeadValue(msg, "SNC", aContFlag) == 0)
	{
		if (aContFlag[0] == '0') 
   		{  /* �޺����ӽ��� */
    		usfTraceX("�޺������ף��˳���������");
    		hsocketshutdown(iSockFd, 1);
		}
	}
    /*
     * ��ʱ����
     */
    memset(aTimeOut, 0x0, sizeof(aTimeOut));
    usfGetMsgHeadValue(msg, "TMO", aTimeOut);
    /* 
     * hisnumber����0Ϊȫ����
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
		usfErrlog("������=[%s] �ȴ���Ӧ��ʱ��ͨѶ�����ѹر�!", msg->request_id);
		hsocketclose(iSockFd);

		curr = (SERVER_CONF *)_SvrList->addr[currSlot];

		thdLockMutex(&curr->conn_lock);
		curr->sockFd = 0;
		mplFree(_SvrList, currSlot);
		thdUnlockMutex(&curr->conn_lock);
      
      	goto errpc;
    }

    iLen = -1;
    /*  ����ǰ�ó���  */
	recv_buf = (char *)malloc(MAX_DATA_LEN + 1);
	if ( recv_buf == NULL )
	{
		hsocketclose(iSockFd);
		usfDestroyMsg(msg);
		usfErrlog("������=[%s] �����ڴ�ʧ��", msg->request_id);

		return (-1);
	}
	temp_buf = (char *)malloc(MAX_DATA_LEN + 1);
	if ( temp_buf == NULL )
	{
		hsocketclose(iSockFd);
		usfDestroyMsg(msg);
		free(recv_buf);
		usfErrlog("������=[%s] �����ڴ�ʧ��", msg->request_id);
		
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
usfErrlog("������=[%s] ��������[%s][%d]", msg->request_id,temp_buf,iLen);
		}
		*/
		iLen = recv(iSockFd, recv_buf, MAX_DATA_LEN, 0);
usfErrlog("������=[%s] ��������[%s][%d]", msg->request_id,recv_buf,iLen);

	}
	free(temp_buf);
	temp_buf = NULL;
	iRecvLen = iLen;
	if (iRecvLen <= 0)
    {
		usfErrlog("������=[%s] ������Ӧ����ʧ��!", msg->request_id);
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

	usfTraceX("������=[%s] �������ݳɹ�! IP=[%s]\n����=[%d][%s]", msg->request_id, aCommIp, iLen, recv_buf);
		
    /*д����Ϣǰ���˵���λǰ����*/
    usfSetMsgData(msg, recv_buf+2, iLen - 2);
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
	strcpy(aContFlag,"0");
	if (usfGetMsgHeadValue(msg, "SNC", aContFlag) == 0)
	{
		if (aContFlag[0] == '0') 
		{  /* �޺����ӽ��� */
    		usfTraceX("�޺������ף�����������Ϣ");
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
