#ifndef MQCMSG_H_INCLUDED_C255D3000
#define MQCMSG_H_INCLUDED_C255D3000

#include "mqcclient.h"

/*## ������Ϣ��� */
	DLL_API HMQMsg createMQMsgHandle();

/*## ɾ����Ϣ��� */
	DLL_API void deleteMQMsgHandle( HMQMsg hMsg );

    /*## �����Ϣ */
	DLL_API void clearMsg(HMQMsg hMsg);

    /*## �����Ϣ���������ã���Ϊ��ʼֵ�� */
	DLL_API void clearProperties(HMQMsg hMsg);

    /*## ��ȡ��Ϣ�ĳ��� */
	DLL_API uint32 get_m_iMsgLength(HMQMsg hMsg);

    /*## ������Ϣ��Ϣ */
	DLL_API void setMsg( HMQMsg hMsg, char* pUserMsg, uint32* pLength);

    /*## ��ȡ��Ϣ */
	DLL_API char* getMsg(HMQMsg hMsg);
 
    /*## ��ȡ��Ϣ��ѹ������ */
	DLL_API uint8 get_m_iCompressType(HMQMsg hMsg);

    /*## ��ȡ��Ϣ�ļ��ܷ��� */
	DLL_API uint8 get_m_iEncryptType(HMQMsg hMsg);

    /*## ������Ϣ��ѹ������ */
	DLL_API void  set_m_iCompressType(HMQMsg hMsg, uint8 left);

    /*## ������Ϣ�ļ��ܷ��� */
	DLL_API void  set_m_iEncryptType(HMQMsg hMsg,uint8 left);
 
    /*## ��ȡ��Ϣ�Ĵ���ʱ��У�鷽ʽ */
	DLL_API uint32 get_m_iCRCFlag(HMQMsg hMsg);

    /*## ������Ϣ�Ĵ���ʱ��У�鷽ʽ */
	DLL_API void set_m_iCRCFlag(HMQMsg hMsg,int left);    
    /*## ������Ϣ���ܵ��û���� */
	DLL_API void set_m_strEncryptKey(HMQMsg hMsg, char* name);
    /*## ��ȡ��Ϣ���ܵ��û����� */
	DLL_API char* get_m_strEncryptKey(HMQMsg hMsg);


    /*## ��ȡ���з��������� */
	DLL_API char* get_m_strSourceServerName(HMQMsg hMsg);

    /*## ��ȡ�������� */
 	DLL_API char* get_m_strSourceQueueName(HMQMsg hMsg);

    /*## ��ȡ���Ͷ˵�Ӧ������ */
	DLL_API char* get_m_strClientName(HMQMsg hMsg);

    /*## ��ȡ��ϢӦ��ı�־ */
	DLL_API uint8 get_m_iAnswerType(HMQMsg hMsg);

    /*## ��ȡ��Ϣ���쳣�����־ */
	DLL_API uint8 get_m_iErrHandleId(HMQMsg hMsg);

    /*## ��ȡ��Ϣ�Ĺ̻���־ */
 	DLL_API uint8 get_m_iFixedFlag(HMQMsg hMsg);

    /*## ��ȡ��Ϣ�����ȼ� */
	DLL_API uint8 get_m_iPriority(HMQMsg hMsg);

    /*## ����PUT�����ĳ�ʱʱ�� */
	DLL_API uint32 get_m_iPutTimeOut(HMQMsg hMsg);


    /*## ��ȡ��Ϣ�����ID */
	DLL_API uint32 get_m_iGroupID(HMQMsg hMsg);

    /*## ��ȡ��Ϣ�����ڵ�������к� */
	DLL_API uint32 get_m_iGroupSeq(HMQMsg hMsg);

    /*## ��ȡ��Ϣ�����ID�š� */
	DLL_API uint32 get_m_iCorrelID(HMQMsg hMsg);

    /*## ��ȡPUT���������Ϣ��ID�š�ע����get_m_iMsgID������ */
	DLL_API uint32 getPutMsgID(HMQMsg hMsg);

    /*## ��ȡ��Ϣ��ID�š� */
	DLL_API uint32 get_m_iMsgID(HMQMsg hMsg);

    /*## ���÷��Ͷ˵�Ӧ������ */
	DLL_API void set_m_strClientName( HMQMsg hMsg, char* name );

    /*## ������ϢӦ��ı�־ */
	DLL_API void set_m_iAnswerType(HMQMsg hMsg,uint8 left);

    /*## ������Ϣ���쳣�����־ */
	DLL_API void set_m_iErrHandleId(HMQMsg hMsg,uint8 left);

    /*## ������Ϣ�Ĺ̻���־ */
 	DLL_API void set_m_iFixedFlag(HMQMsg hMsg,uint8 left);

    /*## ������Ϣ�����ȼ� */
	DLL_API void set_m_iPriority(HMQMsg hMsg,uint8 left);

    /*## ����PUT�����ĳ�ʱʱ�� */
	DLL_API void set_m_iPutTimeOut(HMQMsg hMsg,uint32 left);

    /*## ������Ϣ�����ID */
	DLL_API void set_m_iGroupID(HMQMsg hMsg,uint32 left);

    /*## ������Ϣ�����ID�� */
	DLL_API void set_m_iCorrelID(HMQMsg hMsg,uint32 left);

    /*## ������Ϣ�����ڵ�������к� */
	DLL_API void set_m_iGroupSeq(HMQMsg hMsg,uint32 left);

	DLL_API void set_m_iMsgLength(HMQMsg hMsg,uint32 left);


#endif /* !defined(MQCMSG_H_INCLUDED_C255D3000) */
