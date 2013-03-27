#define _DATAPARSER_EXTERN
#include    "hiafp.h"
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
* Function : spe_unca
* Call     : herrlog
* Called by: dataparser
* Paras    :
* Return   : 
* Describe : ������ֱͨ�����Ľ������⴦����
* Others   : ������ͨ���ĸ�ʽ��
*       1.����ǰ��ӡ�@��,���ĺ���ӡ�(char)26����
*******************************************************************/
int spe_unca(CurrInf *curr_inf, char *in_data, int in_len, char **out_data, int *out_len)
{

   int   ret;
   char head_char = '@';
   char end_char = 26;
   char off_by_one = '\0';
   int ext_char_len = sizeof(head_char)+sizeof(end_char)+sizeof(off_by_one);

   herrlog(LOG_LOCATION, "---->>>>����[%s]���ڽ��б������⴦��>>>>----",curr_inf->req_id);
   herrlog(LOG_LOCATION,"�յ���������[%s]",in_data);
   
   *out_len = in_len+ext_char_len;
   *out_data = (char *)malloc(*out_len);
   if(*out_data == NULL){
      herrlog(LOG_LOCATION, "�����ڴ�ʧ��");
      return(DP_FAIL);
   }
   memset(*out_data, 0x00, *out_len);
   memcpy(*out_data, head_char, sizeof(head_char));   /* ���ͷ�ַ� */
   memcpy(*out_data+sizeof(head_char), in_data, in_len);   /* �Ȱ���������ת����������� */
   memcpy(*out_data+sizeof(head_char)+in_len, end_char, sizeof(end_char));   /* ���β�ַ� */
   memcpy(*out_data+sizeof(head_char)+in_len+sizeof(end_char), off_by_one, sizeof(off_by_one));   /* ���β�ַ� */
   
   herrlog(LOG_LOCATION,"���ʹ�����ɱ���[%s]",*out_data);
   herrlog(LOG_LOCATION, "---->>>>����[%s]�������⴦�����>>>>----",curr_inf->req_id);
   return(DP_SUCC);
}


