#ifndef MQCSELECTOR_H_INCLUDED_C255D4454
#define MQCSELECTOR_H_INCLUDED_C255D4454

#include "mqcclient.h"

DLL_API HMQSelector createMQSelectorHandle();
DLL_API void deleteMQSelectorHandle( HMQSelector hSelector );

DLL_API void selectSourceServerIP( HMQSelector hSelector, uint32 iIP, int iOperator);
DLL_API void selectGroupSeq( HMQSelector hSelector, uint32 iGroupSeq, int iOperator);
DLL_API void selectGroupID( HMQSelector hSelector, uint32 iGroupID, int iOperator);
DLL_API void selectCorrelID( HMQSelector hSelector, uint32 iCorrelID, int iOperator );
DLL_API void selectClientIP( HMQSelector hSelector, uint32 iIP, int iOperator );
DLL_API void selectSourceServerName( HMQSelector hSelector, char* pName, int iOperator );
DLL_API void selectSourceQueueName( HMQSelector hSelector, char *pName, int iOperator );
DLL_API void selectClientName( HMQSelector hSelector, char* pName, int iOperator);
DLL_API void clearSelector( HMQSelector hSelector);

#endif /* !defined(MQCSELECTOR_H_INCLUDED_C255D4454) */
