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
*       1.����ǰ��ӡ�@��,���ĺ���ӡ�(char)26�����������ַ������뱨�ĳ��ȣ�
*******************************************************************/
int spe_unca(CurrInf *curr_inf, char *in_data, int in_len, char **out_data, int *out_len)
{

   int   ret;
   char head_char = '@';
   char end_char = 26;
   char off_by_one = '\0';
   int ext_char_len = sizeof(head_char)+sizeof(end_char);

   int int_pre_len = 5;
   int pointer = 0;
/*char tmp[5]="     ";*/
   char *pre_len = (char *)malloc(int_pre_len+sizeof(off_by_one));
   if(pre_len == NULL){
      herrlog(LOG_LOCATION, "�����ڴ�ʧ��");
      return(DP_FAIL);
   }
   sprintf(pre_len, "%d", in_len+int_pre_len);
   pointer = strlen(pre_len);
   herrlog(LOG_LOCATION,"���ĳ���[%s]",pre_len);
   memset(pre_len+pointer, 0x20, int_pre_len-pointer);
   memset(pre_len+int_pre_len, off_by_one, sizeof(off_by_one));
   herrlog(LOG_LOCATION,"���ĳ���[%s]",pre_len);

   herrlog(LOG_LOCATION, "---->>>>����[%s]���ڽ��б������⴦��>>>>----",curr_inf->req_id);
   herrlog(LOG_LOCATION,"�յ���������[%s]",in_data);
   herrlog(LOG_LOCATION,"���ͷβ���ȹ�[%d]",ext_char_len);
   
   *out_len = int_pre_len+in_len+ext_char_len;
   int totle_len = int_pre_len+*out_len+sizeof(off_by_one);
   *out_data = (char *)malloc(totle_len);
   if(*out_data == NULL){
      herrlog(LOG_LOCATION, "�����ڴ�ʧ��");
      return(DP_FAIL);
   }
   memset(*out_data, 0x00, totle_len);
   memset(*out_data, head_char, sizeof(head_char));   /* ���ͷ�ַ� */
   memcpy(*out_data+sizeof(head_char), pre_len, int_pre_len);   /* �Ȱ���������ת����������� */
   memcpy(*out_data+sizeof(head_char)+int_pre_len, in_data, in_len);   /* �Ȱ���������ת����������� */
   memset(*out_data+sizeof(head_char)+int_pre_len+in_len, end_char, sizeof(end_char));   /* ���β�ַ� */
   memset(*out_data+sizeof(head_char)+int_pre_len+in_len+sizeof(end_char), off_by_one, sizeof(off_by_one));   /* ���β�ַ� */
   
   herrlog(LOG_LOCATION,"���ʹ�����ɱ���[%s]",*out_data);
   herrlog(LOG_LOCATION, "---->>>>����[%s]�������⴦�����>>>>----",curr_inf->req_id);
   return(DP_SUCC);
}
