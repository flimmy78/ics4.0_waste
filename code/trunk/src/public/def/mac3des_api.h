/* mac3des_api.h */

#ifndef _MAC3DES_API_H_
#define _MAC3DES_API_H_

#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <signal.h>

#define ENCODE '0'
#define DECODE '1'

#define CFGFILENAME "api.cfg"

#define MAXPKGLEN 16*1024 /* 16 kilo Bytes */

/*
	Function Name:
		mac3des_api
	
	Description:
		3des + mac ENCODE/DECODE
	
	Parameters:
		type 			- ENCODE/DECODE(0/1)
		DataInBuf		- 输入数据(in)
		DataInLength	- 输入数据长度(in)
		DataOutBuf		- 输出数据(out)
		DataOutLength	- 输出数据长度(out)
		
	Return Values:
		 0	- 成功
		-1	- 加解密数据长度 包含非法字符
		-2	- 网点号 包含非法字符
		-3	- 密钥标识 包含非法字符
		-4	- 密钥未找到
		-5	- MAC校验错
		-6	- 非法的处理类型
		-7	- 网络超时
		-8	- 消息队列标识获取失败
		-9	- 发送消息失败
*/

int mac3des_api(char type, char *DataInBuf, int *DataInLength, char *DataOutBuf, int *DataOutLength);



#endif /* _MAC3DES_API_H_ */
