#ifndef MQCSERVER_H_INCLUDED_C255F4000
#define MQCSERVER_H_INCLUDED_C255F4000

#include "mqcclient.h"

/*## 创建MQ服务器句柄 */
DLL_API HMQServer createMQServerHandle();

/*## 删除MQ服务器句柄 */
DLL_API void deleteMQServerHandle( HMQServer hServer );

DLL_API uint32 get_m_iErrorNo(HMQServer hServer);

/*## 登陆 */
DLL_API int login(HMQServer hServer, char* strServerIP, uint16 iServerPort, char* strUserName, char* strPassword );

/*## 退出 */
DLL_API int logout(HMQServer hServer );


#endif /* MQCSERVER_H_INCLUDED_C255F4000 */
