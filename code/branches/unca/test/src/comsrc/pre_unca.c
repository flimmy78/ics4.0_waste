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
* Function : pre_unca
* Call     : herrlog
* Called by: dataparser
* Paras    :
* Return   : 
* Describe : ������ֱͨ�����Ľ������⴦����
* Others   : ������ͨ���ĸ�ʽ��
*       1.��ӱ��ĳ��ȣ�
*       2.����ǰ��ӡ�@��,���ĺ���ӡ�(char)26�����������ַ������뱨�ĳ��ȣ�
*******************************************************************/
int pre_unca(CurrInf *curr_inf, char *in_data, int in_len, char **out_data, int *out_len)
{
   herrlog(LOG_LOCATION, "---->>>>����[%s]���ڽ��б���pre����>>>>----",curr_inf->req_id);
   herrlog(LOG_LOCATION,"�յ���������[%s]",in_data);

   char head_char = '@';
   char end_char = 26;
   char off_by_one = '\0';
   int ext_char_len = sizeof(head_char)+sizeof(end_char);
   herrlog(LOG_LOCATION,"���ͷβ���ȹ�[%d]",ext_char_len);

   int int_pre_len = 5;

   char *pre_len = (char *)malloc(int_pre_len+sizeof(off_by_one));
   if(pre_len == NULL){
      herrlog(LOG_LOCATION, "����pre_len�ڴ�ʧ��");
      return(DP_FAIL);
   }

   memset(pre_len, off_by_one, int_pre_len+sizeof(off_by_one));
   memcpy(pre_len, in_data+sizeof(head_char), int_pre_len);
   herrlog(LOG_LOCATION,"��ͷ+���峤�ȹ�[%s]", pre_len);
   *out_len = atoi(pre_len) - int_pre_len;
   herrlog(LOG_LOCATION,"���峤�ȹ�[%d]", *out_len);

   *out_data = (char *)malloc(*out_len+sizeof(off_by_one));
   if(*out_data == NULL){
      herrlog(LOG_LOCATION, "����out_data�ڴ�ʧ��");
      return(DP_FAIL);
   }
   memcpy(*out_data, in_data+sizeof(head_char)+int_pre_len, *out_len);

   herrlog(LOG_LOCATION,"���ʹ�����ɱ���[%s]",*out_data);
   herrlog(LOG_LOCATION, "---->>>>����[%s]�������⴦�����>>>>----",curr_inf->req_id);
   return(DP_SUCC);
}
