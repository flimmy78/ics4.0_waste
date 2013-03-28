#define _DATAPARSER_EXTERN
#include    "hiafp.h"
#include    "hibase.h"
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
*       1.报文前添加“@”,报文后添加“(char)26”，这两个字符不算入报文长度；
*******************************************************************/
int pre_unca(CurrInf *curr_inf, char *in_data, int in_len, char **out_data, int *out_len)
{

   herrlog(LOG_LOCATION, "---->>>>交易[%s]正在进行报文特殊处理>>>>----",curr_inf->req_id);
   herrlog(LOG_LOCATION,"收到待处理报文[%s]",in_data);
   return(DP_SUCC);
}
