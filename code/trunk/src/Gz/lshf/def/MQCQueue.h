
#ifndef MQCQUEUE_H_INCLUDED_C255D4000
#define MQCQUEUE_H_INCLUDED_C255D4000

#include "mqcclient.h"

#include "MQCSelector.h"
#include "MQCMsg.h"


DLL_API HMQQueue createMQQueueHandle();
DLL_API void deleteMQQueueHandle( HMQQueue hQueue );

/*## 设置队列的MQ服务器属性 */
DLL_API void set_m_pMQServer( HMQQueue hQueue, HMQServer hServer );

/*## 获取分包的最大长度 */
DLL_API int get_m_iMaxPacketLength( HMQQueue hQueue);	

/*## 获取分包标志 */
DLL_API int get_m_iDepartPacketFlag( HMQQueue hQueue);

/*## 设置分包的最大长度 */
DLL_API void set_m_iMaxPacketLength( HMQQueue hQueue, int left);	

/*## 设置分包标志 */
DLL_API void set_m_iDepartPacketFlag( HMQQueue hQueue,int left);

/*## 消息批处理回滚 */
DLL_API int transactionRollback( HMQQueue hQueue);

/*## 消息批处理提交 */
DLL_API int transactionCommit( HMQQueue hQueue);

/*## 消息批处理开始。开始后，发往服务器的消息都在服务器一端缓存起来，
在COMMIT后才真正提交到队列里去。 */
DLL_API int transactionBegin( HMQQueue hQueue);

/*## 打开队列 */
DLL_API int openQueue( HMQQueue hQueue,char* strQueueName, char* strMode );

/*## 往服务器端发送一个消息 */
DLL_API int put( HMQQueue hQueue, HMQMsg pMQMsg );

/*## 给队列设置消息选择器， */
DLL_API HMQSelector setMQSelector( HMQQueue hQueue, HMQSelector pSelector );

/*## 删除队列的消息选择器， */
DLL_API HMQSelector clearMQSelector( HMQQueue hQueue);

/*## 从服务器端GET一个消息,如果不需要，用户要自行删除该指针， */
DLL_API int get( HMQQueue hQueue, HMQMsg pMQMsg,uint32* pWaitSecond , uint32* pCorrelId );

/*## 从服务器端窥探一个消息,如果不需要，用户要自行删除该指针， */
DLL_API int peek( HMQQueue hQueue, HMQMsg pMQMsg, uint32* pWaitSecond, uint32* pCorrelID);

/*## 关闭队列 */
DLL_API int closeQueue( HMQQueue hQueue);

/*## 发送应答消息。如果该消息需要处理后应答，则处理后调用该函数 */
DLL_API int sendAnswerMsg( HMQQueue hQueue, int iCode );

/*## 获取错误返回号 */
DLL_API uint32 get_m_iQueueErrorNo( HMQQueue hQueue);

/*## 设置异常错误标志 */
DLL_API void set_m_iQueueErrorNo( HMQQueue hQueue, uint32 left);

/*## 检测是否已打开队列 */
DLL_API int isOpen( HMQQueue hQueue);

#endif /* MQCQUEUE_H_INCLUDED_C255D4000 */
