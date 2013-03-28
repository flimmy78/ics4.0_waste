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
* Function : spe_unca
* Call     : herrlog
* Called by: dataparser
* Paras    :
* Return   : 
* Describe : 广州联通直联报文解析特殊处理函数
* Others   : 广州联通报文格式：
*       1.报文前添加“@”,报文后添加“(char)26”，这两个字符不算入报文长度；
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
      herrlog(LOG_LOCATION, "分配内存失败");
      return(DP_FAIL);
   }
   sprintf(pre_len, "%d", in_len+int_pre_len);
   pointer = strlen(pre_len);
   herrlog(LOG_LOCATION,"报文长度[%s]",pre_len);
   memset(pre_len+pointer, 0x20, int_pre_len-pointer);
   memset(pre_len+int_pre_len, off_by_one, sizeof(off_by_one));
   herrlog(LOG_LOCATION,"报文长度[%s]",pre_len);

   herrlog(LOG_LOCATION, "---->>>>交易[%s]正在进行报文特殊处理>>>>----",curr_inf->req_id);
   herrlog(LOG_LOCATION,"收到待处理报文[%s]",in_data);
   herrlog(LOG_LOCATION,"添加头尾长度共[%d]",ext_char_len);
   
   *out_len = int_pre_len+in_len+ext_char_len;
   int totle_len = int_pre_len+*out_len+sizeof(off_by_one);
   *out_data = (char *)malloc(totle_len);
   if(*out_data == NULL){
      herrlog(LOG_LOCATION, "分配内存失败");
      return(DP_FAIL);
   }
   memset(*out_data, 0x00, totle_len);
   memset(*out_data, head_char, sizeof(head_char));   /* 添加头字符 */
   memcpy(*out_data+sizeof(head_char), pre_len, int_pre_len);   /* 先把输入数据转储到输出数据 */
   memcpy(*out_data+sizeof(head_char)+int_pre_len, in_data, in_len);   /* 先把输入数据转储到输出数据 */
   memset(*out_data+sizeof(head_char)+int_pre_len+in_len, end_char, sizeof(end_char));   /* 添加尾字符 */
   memset(*out_data+sizeof(head_char)+int_pre_len+in_len+sizeof(end_char), off_by_one, sizeof(off_by_one));   /* 添加尾字符 */
   
   herrlog(LOG_LOCATION,"发送处理完成报文[%s]",*out_data);
   herrlog(LOG_LOCATION, "---->>>>交易[%s]报文特殊处理结束>>>>----",curr_inf->req_id);
   return(DP_SUCC);
}
