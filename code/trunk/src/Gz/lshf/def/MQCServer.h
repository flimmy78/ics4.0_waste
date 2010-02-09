#ifndef MQCSERVER_H_INCLUDED_C255F4000
#define MQCSERVER_H_INCLUDED_C255F4000

#include "mqcclient.h"

/*## ����MQ��������� */
DLL_API HMQServer createMQServerHandle();

/*## ɾ��MQ��������� */
DLL_API void deleteMQServerHandle( HMQServer hServer );

DLL_API uint32 get_m_iErrorNo(HMQServer hServer);

/*## ��½ */
DLL_API int login(HMQServer hServer, char* strServerIP, uint16 iServerPort, char* strUserName, char* strPassword );

/*## �˳� */
DLL_API int logout(HMQServer hServer );


#endif /* MQCSERVER_H_INCLUDED_C255F4000 */
