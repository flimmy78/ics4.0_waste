#define _DATAPARSER_EXTERN
#include    "hiafp.h"
#include    <stdlib.h>
#define		DP_FAIL  		-1
#define		DP_SUCC  		0
#define		PATH_LEN 		1024
#define		FILENAME_LEN 	512
#define		PASSWDLEN  		512

/* 以下为广州社保参数 */
#define     LOG_LOCATION        "GZ_UNCA.log"



pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;



/******************************************************************
* Function : pre_unca
* Call     : herrlog
* Called by: dataparser
* Paras    :
* Return   : 
* Describe : 广州联通直联报文解析特殊处理函数
* Others   : 广州联通报文格式：
*       1.添加报文长度；
*       2.报文前添加“@”,报文后添加“(char)26”，这两个字符不算入报文长度；
*******************************************************************/
int pre_unca(CurrInf *curr_inf, char *in_data, int in_len, char **out_data, int *out_len)
{
   herrlog(LOG_LOCATION, "---->>>>交易[%s]正在进行报文pre处理>>>>----",curr_inf->req_id);
   herrlog(LOG_LOCATION,"收到待处理报文[%s]",in_data);

   char head_char = '@';
   char end_char = 26;
   char off_by_one = '\0';
   int ext_char_len = sizeof(head_char)+sizeof(end_char);
   herrlog(LOG_LOCATION,"添加头尾长度共[%d]",ext_char_len);

   int int_pre_len = 5;

   char *pre_len = (char *)malloc(int_pre_len+sizeof(off_by_one));
   if(pre_len == NULL){
      herrlog(LOG_LOCATION, "分配pre_len内存失败");
      return(DP_FAIL);
   }

   memset(pre_len, off_by_one, int_pre_len+sizeof(off_by_one));
   memcpy(pre_len, in_data+sizeof(head_char), int_pre_len);
   herrlog(LOG_LOCATION,"包头+包体长度共[%s]", pre_len);
   *out_len = atoi(pre_len) - int_pre_len;
   herrlog(LOG_LOCATION,"包体长度共[%d]", *out_len);

   *out_data = (char *)malloc(*out_len+sizeof(off_by_one));
   if(*out_data == NULL){
      herrlog(LOG_LOCATION, "分配out_data内存失败");
      return(DP_FAIL);
   }
   memcpy(*out_data, in_data+sizeof(head_char)+int_pre_len, *out_len);

   herrlog(LOG_LOCATION,"发送处理完成报文[%s]",*out_data);
   herrlog(LOG_LOCATION, "---->>>>交易[%s]报文特殊处理结束>>>>----",curr_inf->req_id);
   return(DP_SUCC);
}
