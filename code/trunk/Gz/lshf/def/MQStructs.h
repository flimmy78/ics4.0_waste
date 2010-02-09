#include <stdio.h>

#include "mqcclient.h"


#ifdef _WIN32
	#pragma warning(disable:4786)
    #ifndef EINTR
#define EINTR 2
    #endif
#endif

/************************************************************/
#define MQ_ANSWER_TYPE_ARRIVEQUEUE   1 
#define MQ_ANSWER_TYPE_FETCHED   3 
#define MQ_ANSWER_TYPE_LOCALQUEUE   2 
#define MQ_ANSWER_TYPE_MAX_VALUE 5 
#define MQ_ANSWER_TYPE_NOANSWER   0 
#define MQ_ANSWER_TYPE_PROCESSED   4 
#define MQ_ANSWER_TYPE_SYNCHRONIZED  5 
#define MQ_FRAG_HAS_MORE   1 
#define MQ_FRAG_HAS_NO   0 
#define MQ_MESSAGE_COMPRESS_NO   0   
#define MQ_MESSAGE_COMPRESS_USERDEFINE   100  
#define MQ_MESSAGE_COMPRESS_Z   1   
#define MQ_MESSAGE_CRYPT_DES   1   
#define MQ_MESSAGE_CRYPT_NO   0   
#define MQ_MESSAGE_CRYPT_STD_DES   2   
#define MQ_MESSAGE_CRYPT_STD_DES3   3   
#define MQ_MESSAGE_CRYPT_USERDEFINE   100  
#define MQ_MESSAGE_TYPE_ANSWER_INFO 41   
#define MQ_MESSAGE_TYPE_ANSWER_WAIT 40   
#define MQ_MESSAGE_TYPE_BYTES  20     
#define MQ_MESSAGE_TYPE_GET_ANSWER_LOG   101 
#define MQ_MESSAGE_TYPE_GET_LOG   104 
#define MQ_MESSAGE_TYPE_MAP 22      
#define MQ_MESSAGE_TYPE_OBJECT 24   
#define MQ_MESSAGE_TYPE_PUT_ANSWER_LOG   102 
#define MQ_MESSAGE_TYPE_PUT_LOG   105 
#define MQ_MESSAGE_TYPE_STREAM 21   
#define MQ_MESSAGE_TYPE_TEXT 23     
#define MQ_MSG_TYPE_ACK   3 
#define MQ_MSG_TYPE_ACK_AND_CLOSEQUEUE   4 
#define MQ_MSG_TYPE_ANSWER   10 
#define MQ_MSG_TYPE_COMMAND   5 
#define MQ_MSG_TYPE_COMMAND_ACK   6 
#define MQ_MSG_TYPE_DATA   1 
#define MQ_MSG_TYPE_INFO   2 
#define MQ_MSG_TYPE_PEEK_DATA   7 
#define MQ_MSG_TYPE_REQDATA   0 
#define MQ_OS_BYTES_SEQ_HIGH   0 
#define MQ_OS_BYTES_SEQ_LOW   1 
/*********************** private *************************************/


#ifdef _MQTHREADSAFE

typedef struct _MQMutex {
	/*int m_mutex; */
	pthread_mutex_t m_mutex;
}_MQMutex;

#else

typedef struct _MQMutex {
	int m_mutex;
	/* pthread_mutex_t m_mutex; */
}_MQMutex;

#endif

typedef struct _MQTransferMsg
{
    uint8 m_iBOP;
    uint8 m_iType;

    uint8 m_iVersion;

    uint8 m_iHeadLength;

    uint32 m_iMsgLength;

    uint32 m_iPacketSeqNO;

    uint32 m_iTimeOut;
    uint32 m_iCode;
    uint8 m_iHasSuccessPacket;
    uint8 m_cReserved1;

    uint8 m_cReserved2;
    uint8 m_cReserved3;
    uint32 m_iReserved;

}_MQTransferMsg;

typedef struct _MQMsgHead
{
    uint8 m_iBOP;

    uint8 m_iType;

    uint8 m_iVersion;
    uint8 m_iHeadLength;

    uint32 m_iMsgLength;
    uint32 m_iID;
    uint32 m_iTimeOut;
    uint32 m_iCode;

    uint8 m_iData1;
    uint8 m_iData2;
    uint8 m_iData3;
    uint8 m_iData4;
    uint32 m_iReserved;

}_MQMsgHead;


typedef struct _MQMessage
{
	uint16 m_iVersion;

	uint16 m_iHeadLength;

	uint32 m_iMsgLength;

	uint32 m_iSourceServerIP;

	uint32 m_iClientIP;
	
	uint32 m_iMsgID;

	uint32 m_iTransferID;

	uint32 m_iCorrelID;

	uint32 m_iLifeTimeOut;

	uint32 m_tStartTime;

	char m_cSourceServerName[8];

	char m_cSourceQueueName[8];

	char m_cClientName[8];

	uint32 m_iTag;

	uint8 m_iType;

	uint8 m_iPriority;

	uint8 m_iFixedFlag;

	uint8 m_iErrHandleId;

	uint32 m_iGroupID;


	int32 m_iGroupSeq;

	uint8 m_iAnswerType;

	uint8 m_iRedelivedTimes;

	uint8 m_iEncryptType;

	uint8 m_iCompressType;

	uint32 m_iCRC;
	char  m_cReserved[11];

	char m_pMsg[1];
}_MQMessage;

typedef struct  _MQSelector  
{

	_MQMessage* m_pFilter;
	_MQMessage* m_pPattern;
}_MQSelector;


typedef struct _MQMsg  
{

	_MQMessage* m_pMsg;

	uint32 m_iPutMsgID;

	char *m_pUserMsg;

	int m_iCRCFlag;

	int m_iSaveMsgLength;
	
	char* m_strEncryptKey;
}_MQMsg;



typedef struct _MQServer
{

	char m_strPublisherIP[20];
	uint16 m_iPublisherPort;
	char m_strGroup[20];
	char* m_strVersion;

	int m_iSocket;

	int m_iRemoteIP;

	uint16 m_iRemotePort;

	char m_strVerifyData[20];

	bool m_iActive;

	_MQMsgHead *m_pSendMsgHead;

	_MQMsgHead *m_pRecvMsgHead;

	char* m_pRecv;

	char* m_pSend;

	char* m_strServerIP;

	uint16 m_iBackupDispatcherPort;
	char m_strBackupDispatcherIP[20];

	uint16 m_iServerPort;

	char* m_strCfgFileName;

	char* m_strUserName;

	char* m_strPassword;

	char* m_strServerName;
 
	uint32 m_iErrorNo;

	_MQMutex m_mutex;
}_MQServer;


typedef struct _MQQueue
{
	_MQSelector* m_pSelector;

	char* m_strEncryptKey;	

	int m_iCRCFlag;

	int m_iSocket;
	uint32 m_iServerIP;
	uint32 m_iClientIP;

	uint16 m_iClientPort;


	char* m_pUserMsg;

	_MQMessage *m_pGetMsgHead;

	_MQMessage *m_pPutMsgHead;

	_MQMsgHead *m_pSendMsgHead;

	_MQMsgHead *m_pRecvMsgHead;

	char* m_pRecv;

	char* m_pSend;

	char* m_strQueueName;

	char* m_strMode;
 
	uint32 m_iErrorNo;

	_MQServer *m_pMServer;
	
	uint32  m_iMaxPacketLength ;	
	uint32  m_iDepartPacketFlag ;
	_MQMutex m_mutex;
}_MQQueue;



typedef struct  _MQXMLBuilder
{
	char** m_xmlList;
	int m_iLayer;
}_MQXMLBuilder;


typedef struct _MQXMLParser
{
	char* m_xml;
	char m_cSeperator;
}_MQXMLParser;


typedef struct _MQSession
{
	uint32 m_iSessionID;
	uint16 m_iSessionStatus;

	int m_iRecvOverFlag;

	_MQQueue * m_pQFrom;
	_MQQueue * m_pQTo;

	uint32 m_iTimeout;
	uint32 m_iTryTimes;

	_MQMutex m_mutex;
}_MQSession;

