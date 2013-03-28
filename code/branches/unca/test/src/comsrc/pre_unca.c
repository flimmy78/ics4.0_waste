#define _DATAPARSER_EXTERN
#include    "hiafp.h"
#include    "hibase.h"
#include    <stdlib.h>
#define		DP_FAIL  		-1
#define		DP_SUCC  		0
#define		PATH_LEN 		1024
#define		FILENAME_LEN 	512
#define		PASSWDLEN  		512

/* ����Ϊ�����籣���� */
#define     LOG_LOCATION        "GZ_UNCA.log"



pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;



/******************************************************************
* Function : pre_unca
* Call     : herrlog
* Called by: dataparser
* Paras    :
* Return   : 
* Describe : ������ֱͨ�����Ľ������⴦����
* Others   : ������ͨ���ĸ�ʽ��
*       1.����ǰ��ӡ�@��,���ĺ���ӡ�(char)26�����������ַ������뱨�ĳ��ȣ�
*******************************************************************/
int pre_unca(CurrInf *curr_inf, char *in_data, int in_len, char **out_data, int *out_len)
{

   herrlog(LOG_LOCATION, "---->>>>����[%s]���ڽ��б������⴦��>>>>----",curr_inf->req_id);
   herrlog(LOG_LOCATION,"�յ���������[%s]",in_data);
   return(DP_SUCC);
}
