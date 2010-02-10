/*==============================================================================

 Copyright (C)    2003   rePRO Labs    GuangZhou   China
   All Rights  Reserved.

==============================================================================*/

#ifndef __MQCSESSION_H
#define __MQCSESSION_H

#include  "mqcclient.h"

#undef MQ_SESSION_STATUS_RECVONLY
#define MQ_SESSION_STATUS_RECVONLY	0x0002

#undef MQ_SESSION_STATUS_SENDONLY
#define MQ_SESSION_STATUS_SENDONLY	0x0004

DLL_API HMQSession createMQSessionHandle();
DLL_API void deleteMQSessionHandle( HMQSession hSession );

DLL_API HMQQueue get_m_pQFrom( HMQSession hSession );
DLL_API void set_m_pQFrom( HMQSession hSession, HMQQueue hQFrom );

DLL_API HMQQueue get_m_pQTo( HMQSession hSession );
DLL_API void set_m_pQTo( HMQSession hSession, HMQQueue hQTo );

DLL_API uint32 get_m_iTimeout( HMQSession hSession );
DLL_API void set_m_iTimeout( HMQSession hSession, uint32 iTimeout );

DLL_API uint32 get_m_iTryTimes( HMQSession hSession );
DLL_API void set_m_iTryTimes( HMQSession hSession, uint32 iTryTimes );

DLL_API int isRecvOver( HMQSession hSession );
DLL_API int isSessionOver( HMQSession hSession );

DLL_API void MQClear( HMQSession hSession );

DLL_API void sessionForward( HMQSession hSession, HMQSession hNewSession );

DLL_API int MQCall( HMQSession hSession, HMQMsg hReqMsg, HMQMsg hResMsg );
DLL_API int MQAsynCall( HMQSession hSession, HMQMsg hMsg );
DLL_API int MQGetReply( HMQSession hSession,  HMQMsg hMsg );

DLL_API int MQReturn( HMQSession hSession, HMQMsg hMsg );

DLL_API int MQInform( HMQSession hSession, HMQMsg hMsg );

DLL_API int MQConnect( HMQSession hSession, HMQMsg hMsg, uint16 iSessionStatus );
DLL_API int MQSend( HMQSession hSession, HMQMsg hMsg, uint16 iSessionStatus );
DLL_API int MQRecv( HMQSession hSession, HMQMsg hMsg );
DLL_API int MQDisconnect( HMQSession hSession, HMQMsg hMsg );


#endif /* __MQCSESSION_H */


