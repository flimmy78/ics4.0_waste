/*
	2004-05-19. Modified by chenbaiping.
	在HP机上，#必须出现在第一个，前面不能有任何的空格或其他字母。
	
*/
#ifndef MQCCLIENT_HPP_INCLUDED_ALL2000
#define MQCCLIENT_HPP_INCLUDED_ALL2000

#ifdef _REENTRANT
#else
#define _REENTRANT
#endif

#define BUFFER_SIZE_255 255
#define BUFFER_SIZE_1024 1024
#define MQMAXINT 0x7FFFFFFF



/*保证32位和64位平台可用。 */
typedef void* HMQServer;
typedef void* HMQQueue;
typedef void* HMQMsg;
typedef void* HMQSelector;
typedef void* HMQSession;
typedef void* HMQMutex;


#define MQ_MSGITEM_OP_NULL 0
#define MQ_MSGITEM_OP_EQ 1
#define MQ_MSGITEM_OP_NOT_EQ 2
#define MQ_MSGITEM_OP_BIG 3
#define MQ_MSGITEM_OP_BIG_EQ 4
#define MQ_MSGITEM_OP_LIT 5
#define MQ_MSGITEM_OP_LIT_EQ 6


#ifndef _AIX
typedef int int32;
typedef short int16;
typedef char int8;
#endif

typedef int bool ;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;


/* following just for me  */
#ifdef _WIN32
#pragma warning(disable:4786)
/*winsock2.h应放第一行。 */
#include <winsock2.h>
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*the lock head file */

#else
/* 系统头文件 */
/* 不支持线程 #include <pthread.h> */
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <string.h>
/*the lock head file */


#ifdef _AIX
#include <sys/time.h>
#include <sys/select.h>
#endif

#ifdef _HPUX
#include <pthread.h>
#endif

#endif


/*消息应答类型 */
#define MQC_ANSWER_TYPE_NOANSWER 0
#define MQC_ANSWER_TYPE_ARRIVEQUEUE 1
#define MQC_ANSWER_TYPE_LOCALQUEUE 2
#define MQC_ANSWER_TYPE_FETCHED 3
#define MQC_ANSWER_TYPE_PROCESSED 4

/*消息压缩类型 */
#define MQC_MESSAGE_COMPRESS_NO 0 
#define MQC_MESSAGE_COMPRESS_Z 1
#define MQC_MESSAGE_COMPRESS_USERDEFINE 100 

/*消息加密类型 */
#define MQC_MESSAGE_CRYPT_NO 0
#define MQC_MESSAGE_CRYPT_DES 1  
#define MQC_MESSAGE_CRYPT_USERDEFINE 100

/*消息错误处理类型 */
#define MQC_ERROR_HANDLE_WAIT_AND_TRY 5
#define MQC_ERROR_HANDLE_PUT_TO_DEADQUEUE_AND_INFO 4
#define MQC_ERROR_HANDLE_PUT_TO_DEADQUEUE_SILENTLY 3
#define MQC_ERROR_HANDLE_DROP_SILENTLY 2
#define MQC_ERROR_HANDLE_DROP_AND_INFO 1
#define MQC_ERROR_HANDLE_DEFAULT 0


/*error code*/
#define MQOK  0
#define MQERR  1
#define MQM1000GetMsg  1000
#define MQM1001PutMsg  1001
#define MQW2000OpenTooMuchFiles  2000
#define MQE3000CannotOpenQueue  3000
#define MQE3001QueueNotExist  3001
#define MQE3002CannotAccessQueue  3002
#define MQE3003QueueExisted  3003
#define MQE3004CannotCreateQueue  3004
#define MQE3005HasNoWriteAuthorized  3005
#define MQE3006HasNoReadAuthorized  3006
#define MQE3007HasNoExecuteAuthorized  3007
#define MQE3008CannotInitQueue  3008
#define MQE3009ServerStop  3009
#define MQE3010QueueGetSysError  3010
#define MQE3011QueueGetTimeOut  3011
#define MQE3014QueuePutMsgFull  3014
#define MQE3015QueueIsClosed  3015
#define MQE3016NotMsgQueue  3016
#define MQE3017QueueReachMaxReaders  3017
#define MQE3018QueueReachMaxWriters  3018
#define MQE3019QueuePutTimeOut  3019
#define MQE3012QueuePeekSysError  3012
#define MQE3013QueuePeekTimeOut  3013
#define MQE3020VerifyData  3020
#define MQE3021UserNotExisted  3021
#define MQE3023GroupNotExisted  3023
/*#define MQE3022PasswordIncorrect  3022*/
#define MQE3030UserNotFind  3030
#define MQE3031PasswordError  3031
#define MQE3090MsgSequence  3090
#define MQE3091MsgSizeTooLarge  3091
#define MQE3092MsgCRC  3092
#define MQE3093MsgCompress  3093
#define MQE3094MsgCrypt  3094
#define MQE3095MsgDecompress  3095
#define MQE3096MsgDecrypt  3096
#define MQE3100TransferPacket  3100
#define MQE3101TransferPacketLength  3101
#define MQE3102MsgPacket  3102
#define MQE3103MsgPacketLength  3103
#define MQE3104CannotConnectToServer  3104
#define MQE3105CannotGetSocket  3105
#define MQE3106CannotStartServer  3106
#define MQE3107CannotStopServer  3107
#define MQE3108InterruptWhenConnect 3108
#define MQE3109InterruptWhenGet  3109
#define MQE3110InterruptWhenPeek  3110
#define MQE3111InterruptWhenPut  3111
#define MQE3112InterruptWhenRecv  3112
#define MQE3113InterruptWhenSend  3113
#define MQE3114CannotRouteToServer  3114
#define MQE3115NoRouteToServer  3115
#define MQE3116MaxRouteStep  3116
#define MQE3117InterruptWhenSleep 3117
#define MQE3150ChannelRead  3150
#define MQE3151ChannelSend  3151
#define MQE3152ChannelSendLessData  3152
#define MQE3153ChannelSendMoreData  3153
#define MQE3154ChannelRemoteClosed  3154
#define MQE3156ChannelRemoteClosedAndRecvLessData  3156
#define MQE3157ChannelRemoteClosedAndSendLessData  3157
#define MQE3158NewMemoryWhenReceiveData  3158
#define MQE3155ChannelLocalClosed  3155
#define MQE3200CmdSyntaxError  3200
#define MQE3201CmdLessData  3201
#define MQE3202CmdCannotPerform  3202
#define MQE3300XMLFormatMoreElement  3300		
#define MQE3301XMLFormatNoElement  3301
#define MQE3302XMLFileFormat  3302
#define MQE3303XMLCommandFormat 3303
#define MQE3401CannotOpenFile  3401
#define MQE3402FileWrite  3402
#define MQE3403FileSeek  3403
#define MQE3404FileRead  3404
#define MQE3410OSOpenFile  3410
#define MQE3411OSFlushFile  3411
#define MQE3412OSReadFile  3412
#define MQE3413OSWriteFile  3413
#define MQE3414OSSeekFile  3414
#define MQE3415OSTellFile  3415
#define MQE3416OSInitFile  3416
#define MQE3417OSRenameFile  3417
#define MQE3420OSNoMemory  3420
#define MQE3430OSNoDisk  3430
#define MQE3500MQSBadArgument  3500
#define MQE3518MSGNotFound  3518
#define MQE3520FMMNoNode  3520
#define MQE3521FMMBadFormat  3521
#define MQE3522FMMNotReady  3522
#define MQE3524FMMAddressNotExist  3524
#define MQE3525FMMAddressDuplication  3525
#define MQE3526FMMNoSpace  3526
#define MQE3527FMMAddSpace  3527
#define MQE3528FMMSpaceFull  3528
#define MQE3530SMMBadFormat  3530
#define MQE3531SMMNotReady  3531
#define MQE3533SMMTruncateFile  3533
#define MQE3534SMMTruncateFile  3534
#define MQE3535SMMPutMsg  3535
#define MQE3536SMMGetMsg  3536
#define MQE3537SMMPackFile  3537
#define MQE3538SMMRecoveryFile  3538
#define MQE3523FMMNotGetLogFileName 3523 
#define MQE3527FMMReadTruncate 3527 
#define MQE3528FMMWriteTooBig 3528 
#define MQE3540FMLEndFixMsgLog  3540 
#define MQE3541FMLMapFixMsgLog 3541 
#define MQE3542FMLNotReady 3542 
#define MQE3543FMLBadLogLine  3543
#define MQE3544FMLBadPhisicalLog  3544
#define MQE3532SMMMsgTooBig  3532
#define MQE3529FMMMsgNotFound  3529
#define MQE4000NullPointer  4000
#define MQE4001Point2FreeObject 4001
#define MQE4002InitXMLSystem 4002
#define MQE4003InitMQSystem 4003
#define MQE4004MissXMLCfgFile 4004
#define MQE4006OpenMode 4006

#include "mqdll.h"
#endif /* MQCCLIENT_HPP_INCLUDED_ALL2000 */
