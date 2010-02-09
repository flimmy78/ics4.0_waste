/********************************************************************

		Copyright (C),1998-2003,Hisuntech Co.,Ltd.

	File name:			// pftclifil_gz.c
	Author:				 // WangXiaoDong
	Version:				// 1.0
	Date:					 // 20030327
	Description:		// �����ⲿͨѶģ���з����ͬ����/������Դ�ļ���
	Others:				 // Ŀǰֻ����һ������
	Function List:	// ��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��
										 serverSyncIn
										 serverSyncOut
										 initChannel
										 closeChannel
										 thread_main
										 syncSendRequest
	History:				// �޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ�
									// �޸��߼��޸����ݼ���
		1. Date:			
			 Author:	 
			 Modification:
		2. ...
 No.	 Date				Author			Modification
===	 ==========	========		==============================================
001		2007-06-15	WangXF			�޸�
			ע����Բ�˰ϵͳ�ļ��ӿ�����ͨѶ���ö����ӣ�һ�����Ӷ�ν�����Ϣ��
			��ͨѶ�ӿ�ͨ����ϢͷSNC�ж��Ƿ������ӡ�
			�޸�ͨѶ����󳤶ȡ�

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
char			_FP[256] = "/app/ics/dat/pft/recv/"; /*�ļ����·��*/
/********************************************************************
	Function:			 // initConnDesp
	Description:		// ��ʼ��CONN_DESP�ṹ
	Calls:					// 
	Called By:			// initChannel
	Table Accessed: // 
	Table Updated:	// 
	Input:					// arg:����	
	Output:				 //
	Return:				 // ��
	Others:				 // 
********************************************************************/
void initConnDesp(void * arg)
{
	
		CONN_DESP * fdnode = (CONN_DESP *)arg;
		memset(fdnode, 0, sizeof(CONN_DESP));	
	
}
/********************************************************************
	Function:			 // peerCloseMonitor
	Description:		// ����ʱ��ͬ������ƥ��ڵ�
	Calls:					// 
	Called By:			// initChannel
	Table Accessed: // 
	Table Updated:	// 
	Input:					// arg:����	
	Output:				 //
	Return:				 // ��
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
				 * ���������˳���
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
					usfErrlog("�����ʱsocket(%s.%d).[%d][%s][%ld][%ld]", fdnode->ipAddr, iTimeOut, i, fdnode->key, iKey, ct.tv_sec);
					del_conn_node(i);
								}
						}
				}
		}
}


/********************************************************************
	Function:			 // initChannel
	Description:		// ��������ʱ���еĳ�ʼ��������ִ��װ��IP��һЩ����
	Calls:					// loadIPTable(char * filename) װ��ip��ĺ���
	Called By:			// �������ܵ���?
	Table Accessed: // 
	Table Updated:	// 
	Input:					// argc:��������
									// argv:��������,������������������
									//												 �����ļ�����
									//												 ���������
									//												 ǰ�ñ�־����
									//												 ���ʱʱ��
	Output:				 //
	Return:				 // 0:�ɹ� !0:ʧ��
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
			usfErrlog("[%d]���������:��������,IP�����ļ���,[���������],[ǰ�ñ�־����],[���ʱʱ��],[���ܱ�־]",ERRCODE+1);
			 	return(-1);

		}
		memset(&_ConnPara, 0x0, sizeof(CONN_PARAM));
 
	/*
	 * ���ñ���IP��ַ
	 * Added by liangwj in 20050127
	 */
		hsocketsetlocalip(_PubRuntimeEnv->svr_addr); 
	 
		/*
		 * argv[0]:�������� 0:������ 1:������
		 * argv[1]:ip�����ļ�����
		 * argv[2]:���������
		 * argv[3]:ǰ�ó��ȵĳ���			
		 * argv[4]:���ʱʱ��
		 */


		_ConnPara.syncConType = SHORT_CONN;


		if (strlen(argv[1]) <= FILENAME_LEN )
		{
				 strcpy(_ConnPara.ipConFile,argv[1]);
		}
		else
		{
				 usfErrlog("[%d]�����ļ���������", ERRCODE+2);
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
				_ConnPara.havePreLen = NO_PRELEN; /* û��ǰ�ó���	*/
		}
		else 
		{
				_ConnPara.havePreLen = HAVE_PRELEN;/* ��ǰ�ó���	*/
				_ConnPara.preLenLen = atoi(argv[3]);
				if (_ConnPara.preLenLen <= 0)
				{
						 _ConnPara.havePreLen = NO_PRELEN; /* û��ǰ�ó���	*/
				}
			 
		}

		hdelbothspace(argv[1]);
		if (strlen(argv[1]) > 0 && ecnInitIpList(argv[1], &_IPsList, &_IPsTable) < 0)
		{
				usfErrlog("[%d]װ��IP�����ļ�[%s]ʧ��", ERRCODE + 3, argv[1]);
				return( -1 );
		}

		_FDsList = mplCreate(10, iMaxConn, sizeof(CONN_DESP), 1, 1, initConnDesp);
		if ( _FDsList == NULL )
		{
				usfErrlog("[%d]����ͬ������ƥ���ڴ��ʧ��", ERRCODE+4);
				return(-1);
		}

		/*
		 * ͬ�������Ӳſ����ó�ʱ�ж�
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
		usfErrlog("[%d]����ͬ��������ѯ����ʧ��", ERRCODE + 5);
		return(-1);
	}


	if (argc > 5)
	{
		_EncFlg = atoi(argv[5]);
	}

		usfTraceX("[10]��������[%s] �����ļ�[%s] ���������[%d] ǰ�ñ�־[%d] ǰ�ó���[%s] ���ʱʱ��[%d] ���ܱ�־[%d]", argv[0],argv[1],iMaxConn,_ConnPara.havePreLen,argv[3],iTimeOut, _EncFlg);

		return(0);
}

/********************************************************************
	Function:			 // closeChannel
	Description:		// ����ֹͣʱ���еĺ�����ִ���ͷ�IP��һЩ��Դ
	Calls:					// freeIPTable(char * filename) �ͷ�ip��ĺ���
	Called By:			// �������ܵ���
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
		 * �ͷ������������е���������
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
		 * �ͷ�ͬ�����ӵǼǽṹ��
		 */
		mplDestroy(_FDsList);
		/*
		 * �ͷ�IP���ýṹ��͹رռ������
		 */
		ecnFreeIpList(_IPsList, _IPsTable);
		hsocketclose(_ListenFD);

}
/********************************************************************
	Function:			 // serverSyncIn
	Description:		// ������������������������ݵ���ں�������Ҫ�������
	Calls:					// thread_main
									// syncSendRequest
	Called By:			// �������ܵ���?
	Table Accessed: // 
	Table Updated:	// 
	Input:					// argc:��������
									// argv:��������
									// tid :����id
	Output:				 //
	Return:				 // 0:�ɹ� !0:ʧ��
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
			 usfErrlog("[%d]���������:��Ϣ���͡��˿ںš�[��������Ŀ]", ERRCODE + 20);
			 return(-1);
		}
		
		if (strlen(argv[0]) <= MSGLEN)
		{
				strcpy(_ConnPara.msgType,argv[0]);
		}
		else
		{
				usfErrlog( "[%d]��Ϣ���Ͳ�������", ERRCODE+21);
				return(-1);
		}
		
		if ( atoi(argv[1]) > 0)
		{
				_ConnPara.port = atoi(argv[1]);
		}
		else
		{
				usfErrlog( "[%d]�˿ںű���Ϊ����", ERRCODE + 22);
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

		usfTraceX("[10]��Ϣ����[%s]�˿ں�[%d]������[%d]",_ConnPara.msgType, _ConnPara.port, _ConnPara.thread_num);

		_ListenFD = hsocketbindlisten(_ConnPara.port);
		if (_ListenFD < 0)
		{
				usfErrlog( "[%d]������������ʧ��", ERRCODE + 23);
				return(-1);
		}


		if (thdInitAttr(&pAttr) != 0)
		{
				usfErrlog( "[%d]��ʼ����������ʧ��", ERRCODE + 24);
				return(-1);
		}

		thdSetDetachState(&pAttr, PTHREAD_CREATE_UNDETACHED);
		thdSetScope(&pAttr, PTHREAD_SCOPE_SYSTEM);

		_MainThreadRec = (pthread_t *)malloc(_ConnPara.thread_num * sizeof(pthread_t));
		if (_MainThreadRec == NULL)
		{
				usfErrlog("[%d]����������ID�ڴ�ʧ��", ERRCODE+25);
				thdDestroyAttr(&pAttr);
				return(-1);
		}

		for(iCount = 0; iCount < _ConnPara.thread_num; iCount++)
		{
				if (thdCreate(&thread_id, &pAttr, thread_main, NULL) != 0)
				{
						 usfErrlog("[%d]����������ʧ��", ERRCODE + 26);
						 thdDestroyAttr(&pAttr);
						 if (_MainThreadRec != NULL)
						 {
								 free(_MainThreadRec);
								 _MainThreadRec = NULL;
						 }
						 return(-1);
				}

				/*
				 * ������������id���Ա��ڷ���ر�ʱ�ͷ�������Դ
				 */

				_MainThreadRec[iCount] = thread_id;
		}
				 
		thdDestroyAttr(&pAttr);
	 
		return(0);
}
/********************************************************************
	Function:			 // thread_main
	Description:		// ���������������󣬷�������������������
	Calls:					// syncSendRequest
	Called By:			// serverSyncIn
	Table Accessed: // 
	Table Updated:	// 
	Input:					// args :��
									//
	Output:				 //
	Return:				 // ��
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
				 * �����˳���
				 */
				thdTestCancel();
	 		 	memset((char *)&cli_addr, 0, sizeof(struct sockaddr_in));
 
				/*
				 * ������������
				 */
				iCliLen = sizeof(cli_addr);
				sockFd = accept(_ListenFD, (struct sockaddr *)&cli_addr, &iCliLen);

				if (sockFd < 0)
				{
						continue;	
				}
				/*
				 * ȡ��ʱ��ʱ�䣬��ȷ������
				 */
				memset(key, 0x0, sizeof(key));
				gettimeofday(&tv, NULL);
				sprintf(key, "%10d%6d", tv.tv_sec, tv.tv_usec);
					
				/*
				 * ��������������Ϣ
				 */				
				connDesp.sockfd = sockFd;
				sprintf(ipAddr,"%s", inet_ntoa(cli_addr.sin_addr));
				strcpy(connDesp.key , key);
				strcpy(connDesp.ipAddr, ipAddr);

				/*
				 * ����IP�Ϸ��Լ��
				 */
				if (ecnCheckIp(_IPsList, connDesp.ipAddr))
				{
						usfErrlog( "[%d]ע��:�зǷ�Ip[%s]��ͼ����", ERRCODE + 32, connDesp.ipAddr);
						hsocketclose(sockFd);
						continue;
				}

				/*
				 * ��������ƥ��ֵ
				 * ���ڽӿ�mplMalloc�Ѿ��Լ����ˣ��������������ټ���
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
	Description:		// ������������
	Calls:					// 
	Called By:			// thread_main
	Table Accessed: // 
	Table Updated:	// 
	Input:					// args:����������Ϣ�ṹCONN_DESP
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
		usfErrlog("�����ڴ�ռ�ʧ��![%d]", MAX_DAT_LEN+1);	
		return (-1);
	}
 
		/*
		 *	���ֳ������Ӽ���ǰ�ó���/����ǰ�ó���
		 */
		for (;;)
		{
		result = hsocketselect(TIME_OUT, desp->sockfd);
		if (result < 0) 
		{
			usfErrlog("���������ź�ʧ��, ͨѶ�����ѹر�! IP=[%s]", desp->ipAddr);	
			del_conn_node(desp->slot);
			break;
		}
		 
		if (result == 0)	/* �ڳ�ʱʱ����û�����ݵ��� */
		{
						if (_ConnPara.syncConType == LONG_CONN)
						{
								continue;
						}
						else
						{
							usfErrlog("�������ݵȴ���ʱ! IP=[%s]", desp->ipAddr);	
								del_conn_node(desp->slot);
								break;
						}
		}

		recv_len = -1;
		
		/* û��ǰ�ó���*/
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
				usfErrlog("��������[���ճ���=%d][��Ϣ�峤��+19=[%d]\n", recv_len,atoi(tmp_str));
				while( 1 )
				{
					i = 0;
					usfErrlog("��ʼ�������գ�����\n");	
					i = read(desp->sockfd, recv_buf+recv_len, MAX_DAT_LEN);
					usfErrlog("��������[%s][%d]\n", recv_buf+recv_len,i);
					if ( i<= 0 )
						break;
					recv_len += i;
					if( recv_len == (19 + atoi(tmp_str)) )
						break;
				}
			}
			
			usfErrlog("�������[%s][%d]\n", recv_buf,recv_len);	
		}

		if ( (recv_len <= 0) || (i < 0) )
		{
			usfErrlog("������������ʧ��, ͨѶ�����ѹر�! IP=[%s]", desp->ipAddr);	
			
			free(recv_buf);
			recv_buf = NULL;
			del_conn_node(desp->slot);
			
			break;
		}
		
		/* ���ܴ��� add by liangwj in 20040618 */
		if (_EncFlg == 1)
		{
			rc = mac3des_api(DECODE, recv_buf, &recv_len, p_buf, &buf_len);
			if (rc < 0)
			{
				usfErrlog("���ܴ���ʧ��!IP=[%s] ����=[%d][%s]", desp->ipAddr, recv_len, recv_buf);
			
				free(recv_buf);
				recv_buf = NULL;
				del_conn_node(desp->slot);
			
				break;
			 }
		 }

			 /*
				*	������Ϣ��������ߵ��������
				*/

		msg = (Message *)usfCreateMsg(_ConnPara.msgType);
		if (msg) 
		{
			if (_EncFlg == 1)
			{
				usfSetMsgData(msg, p_buf+14, buf_len-14);
				/* NIDΪ�ӽ��ܱ�ʶ����Ҫ���棬����Ӧʱ������ */
				/* add by liangwj in 20040618								*/
				usfAddMsgHeadValue(msg, "NID", p_buf+6, 8);
			}
			else
			{
				/*д����Ϣǰ���˵���λǰ����*/
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
				
			usfTraceX("������=[%s] �������ݳɹ�! IP=[%s]\n����=[%d][%s]", msg->request_id, desp->ipAddr, recv_len, recv_buf);

			if (usfSendRequest(msg))
			{
				usfErrlog("����������Ϣʧ��!");
				usfDestroyMsg(msg);
				del_conn_node(desp->slot);
				
			}
		}
		else 
		{
			usfErrlog("����������Ϣʧ��! IP=[%s]\n����=[%d][%s]", desp->ipAddr, recv_len, recv_buf);
			del_conn_node(desp->slot);
		}
		/*�����ļ������ļ�����*/
		if ( strncmp(msg->msg_text,"shead",5) == 0 )
		{ 
			memset(tmp_str,0x00,sizeof(tmp_str));
			memcpy(tmp_str,msg->msg_text+9,8);
			
			file_head_len = atoi(tmp_str);
			file_head_info = (char *)malloc(file_head_len + 1);			 	
			if ( file_head_info == NULL )
			{
				usfErrlog("�����ڴ�ʧ��[%d]", file_head_len+1);
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
			usfTraceX("�ļ��������,�˳������߳�");
			break;		
		}
		if ( strncmp(msg->msg_text,"sfile",5) == 0 )
		{
			usfErrlog("������=[%s] ����д���ļ�[%s|%d]!", msg->request_id,file_name,msg->msg_size -17);

			if ( writebinfile(file_name, msg->msg_text+17, msg->msg_size-17) != 0 )
			{
				usfErrlog("������=[%s] ����д���ļ�ʧ��!", msg->request_id);
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
	Description:		// ������������Ӧ�����ݸ���������ں���
	Calls:					// 
	Called By:			// �������ܵ���
	Table Accessed: // 
	Table Updated:	// 
	Input:					// msg:Ӧ����Ϣ��
									//
	Output:				 //
	Return:				 // 0���ɹ� !0:ʧ��
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
	 *	ȡsocked �Ǽǵ�λ�úţ�ip��ַ��keyֵ�ͺ�������־
	 */
	memset(aTmp, 0x0, sizeof(aTmp)); 	
	if (usfGetMsgHeadValue(msg, "SFD", aTmp) < 0 )
	{
		usfErrlog( "������=[%s] ȡ��Ϣͷ(SFD)ʧ��!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);	
	}
		
	iSlot = atoi(aTmp);

	memset(aIpAddr, 0x0, sizeof(aIpAddr));
	if (usfGetMsgHeadValue(msg, "SIP", aIpAddr) < 0 )
	{
		usfErrlog( "������=[%s] ȡ��Ϣͷ(SIP)ʧ��!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
	}
		
	memset(aKey, 0x0, sizeof(aKey));
	if (usfGetMsgHeadValue(msg, "SKY", aKey) < 0 )
	{
		usfErrlog( "������=[%s] ȡ��Ϣͷ(SKY)ʧ��!", msg->request_id);
		usfDestroyMsg(msg);
		return (-1);
	}

	/*
	 *	ƥ��ԭ����,δƥ�䵽�����ܹر�socket������
	 */
	if ((iSockFd = check_conn_node(iSlot, aIpAddr, aKey)) < 0 )
	{
		usfErrlog( "������=[%s] ���׷��س�ʱ��ԭͨѶ�����ѹر�!", msg->request_id);
		usfDestroyMsg(msg);	

		return(-1);	
	}
		
	/* ���ܴ��� add by liangwj in 20040618 */
	if (_EncFlg == 1)
	{
		memset(aNetId, 0x0, sizeof(aNetId));
		if (usfGetMsgHeadValue(msg, "NID", aNetId) < 0 )
		{
			usfErrlog( "������=[%s] ȡ��Ϣͷ(NID)ʧ��!", msg->request_id);
			usfDestroyMsg(msg);
			del_conn_node(iSlot);
			 
			return (-1);
		}
		p_buf = (char *)malloc(MAX_DAT_LEN+1);
		p_tmp = (char *)malloc(MAX_DAT_LEN+1);
		if (p_buf == NULL || p_tmp == NULL)
		{
			usfErrlog( "������=[%s] �����ڴ�ʧ��! ��С=[%d]", msg->request_id, MAX_DAT_LEN*2);
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
			usfErrlog("������=[%s] ���ܴ���ʧ��! rc=[%d]", msg->request_id, result);
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
		usfErrlog("������=[%s] �����ڴ�ռ�ʧ��!", msg->request_id);
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
		usfErrlog("������=[%s] ������Ӧ����ʧ��!", msg->request_id);
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
	usfTraceX("������=[%s] �������ݳɹ�! IP=[%s]\n����=[%d][%s]", msg->request_id, aIpAddr, iSendLen, msg->msg_text);

	strcpy(aContFlag,"0");
	if (usfGetMsgHeadValue(msg, "SNC", aContFlag) == 0)
	{
		if (aContFlag[0] != '0') 
		{	/* �к����ӽ��� */
			usfTraceX("�к������ף�������������");
			usfDestroyMsg(msg);
			return(0);
		}
	}
	usfTraceX("�޺������ף��˳�");

	del_conn_node(iSlot);
				
	usfDestroyMsg(msg);

	return(0);
}

/*
 * ����ͨѶ����ͬ��������Ϣ
 */
int add_conn_node(CONN_DESP * conn_desp)
{
		 short slot;
		 
		 slot = mplMalloc(_FDsList);
		 if (slot < 0) 
		 {
			 usfErrlog("[add_conn_node] ���������������ܴ�����������");
			 return(-1);
		 }
		 
		 memcpy(_FDsList->addr[slot], conn_desp, sizeof(CONN_DESP));
	
		 return(slot);
}

/*
 * ɾ��ͨѶ����ͬ��������Ϣ
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
 * ƥ��ԭ����ͨѶ����
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
 * �����ط���
 * Added by liangwj at 2006-06-05
 */
int putManageMsgResponse(Message * msg, XmlNode * out_root, char * err_code, char * err_msg)
{
	/* ���ô��������� */
	xmlSetChildValue(out_root, "RspCod", err_code);
	usfSetMsgHeadValue(msg, "SSC", err_code, 6);

	/* ���ô�������Ϣ */
	xmlSetChildValue(out_root, "RspMsg", err_msg);
	usfSetMsgHeadValue(msg, "SEM", err_msg, strlen(err_msg));

	usfReturn(msg, out_root, "text/xml", 0);

	/* �ͷ���Դ */
	usfDestroyMsg(msg);
	xmlFreeNode(out_root, 1);
	
	return 0;
}

/*
 * ��̬����IPD�ļ�
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
			strcpy(err_msg, "��̬����IPD�ļ��ɹ�!");
		}
		else
		{
			strcpy(result, "999999");
			strcpy(err_msg, "��̬����IPD�ļ�ʧ��, ����IPD�ļ��Ƿ�Ϸ�!");
		}
	}
	else
	{
		strcpy(result, "999999");
		strcpy(err_msg, "��̬����IPD�ļ�ʧ��, ATR��ԭ��û������IPD�ļ�!");
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
	 usfErrlog("[%s] �ļ��򿪳���",pathname);

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
