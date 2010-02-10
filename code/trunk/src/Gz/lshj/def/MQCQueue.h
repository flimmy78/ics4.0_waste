
#ifndef MQCQUEUE_H_INCLUDED_C255D4000
#define MQCQUEUE_H_INCLUDED_C255D4000

#include "mqcclient.h"

#include "MQCSelector.h"
#include "MQCMsg.h"


DLL_API HMQQueue createMQQueueHandle();
DLL_API void deleteMQQueueHandle( HMQQueue hQueue );

/*## ���ö��е�MQ���������� */
DLL_API void set_m_pMQServer( HMQQueue hQueue, HMQServer hServer );

/*## ��ȡ�ְ�����󳤶� */
DLL_API int get_m_iMaxPacketLength( HMQQueue hQueue);	

/*## ��ȡ�ְ���־ */
DLL_API int get_m_iDepartPacketFlag( HMQQueue hQueue);

/*## ���÷ְ�����󳤶� */
DLL_API void set_m_iMaxPacketLength( HMQQueue hQueue, int left);	

/*## ���÷ְ���־ */
DLL_API void set_m_iDepartPacketFlag( HMQQueue hQueue,int left);

/*## ��Ϣ������ع� */
DLL_API int transactionRollback( HMQQueue hQueue);

/*## ��Ϣ�������ύ */
DLL_API int transactionCommit( HMQQueue hQueue);

/*## ��Ϣ������ʼ����ʼ�󣬷�������������Ϣ���ڷ�����һ�˻���������
��COMMIT��������ύ��������ȥ�� */
DLL_API int transactionBegin( HMQQueue hQueue);

/*## �򿪶��� */
DLL_API int openQueue( HMQQueue hQueue,char* strQueueName, char* strMode );

/*## ���������˷���һ����Ϣ */
DLL_API int put( HMQQueue hQueue, HMQMsg pMQMsg );

/*## ������������Ϣѡ������ */
DLL_API HMQSelector setMQSelector( HMQQueue hQueue, HMQSelector pSelector );

/*## ɾ�����е���Ϣѡ������ */
DLL_API HMQSelector clearMQSelector( HMQQueue hQueue);

/*## �ӷ�������GETһ����Ϣ,�������Ҫ���û�Ҫ����ɾ����ָ�룬 */
DLL_API int get( HMQQueue hQueue, HMQMsg pMQMsg,uint32* pWaitSecond , uint32* pCorrelId );

/*## �ӷ������˿�̽һ����Ϣ,�������Ҫ���û�Ҫ����ɾ����ָ�룬 */
DLL_API int peek( HMQQueue hQueue, HMQMsg pMQMsg, uint32* pWaitSecond, uint32* pCorrelID);

/*## �رն��� */
DLL_API int closeQueue( HMQQueue hQueue);

/*## ����Ӧ����Ϣ���������Ϣ��Ҫ�����Ӧ���������øú��� */
DLL_API int sendAnswerMsg( HMQQueue hQueue, int iCode );

/*## ��ȡ���󷵻غ� */
DLL_API uint32 get_m_iQueueErrorNo( HMQQueue hQueue);

/*## �����쳣�����־ */
DLL_API void set_m_iQueueErrorNo( HMQQueue hQueue, uint32 left);

/*## ����Ƿ��Ѵ򿪶��� */
DLL_API int isOpen( HMQQueue hQueue);

#endif /* MQCQUEUE_H_INCLUDED_C255D4000 */
