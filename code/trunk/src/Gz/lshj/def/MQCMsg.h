#ifndef MQCMSG_H_INCLUDED_C255D3000
#define MQCMSG_H_INCLUDED_C255D3000

#include "mqcclient.h"

/*## 创建消息句柄 */
	DLL_API HMQMsg createMQMsgHandle();

/*## 删除消息句柄 */
	DLL_API void deleteMQMsgHandle( HMQMsg hMsg );

    /*## 清空消息 */
	DLL_API void clearMsg(HMQMsg hMsg);

    /*## 清除消息的属性设置，置为初始值。 */
	DLL_API void clearProperties(HMQMsg hMsg);

    /*## 获取消息的长度 */
	DLL_API uint32 get_m_iMsgLength(HMQMsg hMsg);

    /*## 设置消息消息 */
	DLL_API void setMsg( HMQMsg hMsg, char* pUserMsg, uint32* pLength);

    /*## 获取消息 */
	DLL_API char* getMsg(HMQMsg hMsg);
 
    /*## 获取消息的压缩方法 */
	DLL_API uint8 get_m_iCompressType(HMQMsg hMsg);

    /*## 获取消息的加密方法 */
	DLL_API uint8 get_m_iEncryptType(HMQMsg hMsg);

    /*## 设置消息的压缩方法 */
	DLL_API void  set_m_iCompressType(HMQMsg hMsg, uint8 left);

    /*## 设置消息的加密方法 */
	DLL_API void  set_m_iEncryptType(HMQMsg hMsg,uint8 left);
 
    /*## 获取消息的传输时的校验方式 */
	DLL_API uint32 get_m_iCRCFlag(HMQMsg hMsg);

    /*## 设置消息的传输时的校验方式 */
	DLL_API void set_m_iCRCFlag(HMQMsg hMsg,int left);    
    /*## 设置消息加密的用户口令。 */
	DLL_API void set_m_strEncryptKey(HMQMsg hMsg, char* name);
    /*## 获取消息加密的用户口令 */
	DLL_API char* get_m_strEncryptKey(HMQMsg hMsg);


    /*## 获取队列服务器名字 */
	DLL_API char* get_m_strSourceServerName(HMQMsg hMsg);

    /*## 获取队列名字 */
 	DLL_API char* get_m_strSourceQueueName(HMQMsg hMsg);

    /*## 获取发送端的应用名字 */
	DLL_API char* get_m_strClientName(HMQMsg hMsg);

    /*## 获取消息应答的标志 */
	DLL_API uint8 get_m_iAnswerType(HMQMsg hMsg);

    /*## 获取消息的异常错误标志 */
	DLL_API uint8 get_m_iErrHandleId(HMQMsg hMsg);

    /*## 获取消息的固化标志 */
 	DLL_API uint8 get_m_iFixedFlag(HMQMsg hMsg);

    /*## 获取消息的优先级 */
	DLL_API uint8 get_m_iPriority(HMQMsg hMsg);

    /*## 设置PUT操作的超时时间 */
	DLL_API uint32 get_m_iPutTimeOut(HMQMsg hMsg);


    /*## 获取消息的组别ID */
	DLL_API uint32 get_m_iGroupID(HMQMsg hMsg);

    /*## 获取消息的所在的组的序列号 */
	DLL_API uint32 get_m_iGroupSeq(HMQMsg hMsg);

    /*## 获取消息的相关ID号。 */
	DLL_API uint32 get_m_iCorrelID(HMQMsg hMsg);

    /*## 获取PUT操作后的消息的ID号。注意与get_m_iMsgID的区别 */
	DLL_API uint32 getPutMsgID(HMQMsg hMsg);

    /*## 获取消息的ID号。 */
	DLL_API uint32 get_m_iMsgID(HMQMsg hMsg);

    /*## 设置发送端的应用名字 */
	DLL_API void set_m_strClientName( HMQMsg hMsg, char* name );

    /*## 设置消息应答的标志 */
	DLL_API void set_m_iAnswerType(HMQMsg hMsg,uint8 left);

    /*## 设置消息的异常错误标志 */
	DLL_API void set_m_iErrHandleId(HMQMsg hMsg,uint8 left);

    /*## 设置消息的固化标志 */
 	DLL_API void set_m_iFixedFlag(HMQMsg hMsg,uint8 left);

    /*## 设置消息的优先级 */
	DLL_API void set_m_iPriority(HMQMsg hMsg,uint8 left);

    /*## 设置PUT操作的超时时间 */
	DLL_API void set_m_iPutTimeOut(HMQMsg hMsg,uint32 left);

    /*## 设置消息的组别ID */
	DLL_API void set_m_iGroupID(HMQMsg hMsg,uint32 left);

    /*## 设置消息的相关ID号 */
	DLL_API void set_m_iCorrelID(HMQMsg hMsg,uint32 left);

    /*## 设置消息的所在的组的序列号 */
	DLL_API void set_m_iGroupSeq(HMQMsg hMsg,uint32 left);

	DLL_API void set_m_iMsgLength(HMQMsg hMsg,uint32 left);


#endif /* !defined(MQCMSG_H_INCLUDED_C255D3000) */
