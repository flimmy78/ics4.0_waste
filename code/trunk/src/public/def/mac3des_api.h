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
		DataInBuf		- ��������(in)
		DataInLength	- �������ݳ���(in)
		DataOutBuf		- �������(out)
		DataOutLength	- ������ݳ���(out)
		
	Return Values:
		 0	- �ɹ�
		-1	- �ӽ������ݳ��� �����Ƿ��ַ�
		-2	- ����� �����Ƿ��ַ�
		-3	- ��Կ��ʶ �����Ƿ��ַ�
		-4	- ��Կδ�ҵ�
		-5	- MACУ���
		-6	- �Ƿ��Ĵ�������
		-7	- ���糬ʱ
		-8	- ��Ϣ���б�ʶ��ȡʧ��
		-9	- ������Ϣʧ��
*/

int mac3des_api(char type, char *DataInBuf, int *DataInLength, char *DataOutBuf, int *DataOutLength);



#endif /* _MAC3DES_API_H_ */
