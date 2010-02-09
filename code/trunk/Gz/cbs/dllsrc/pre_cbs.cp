#define _DATAPARSER_EXTERN

#include "hiafp.h"

int CbsRspPre(CurrInf *curr_inf, char *in_data, int len1, char **out_data, int *len2)
{
    int n;
    char sTxnKnd[5];
    char sMsgId[5];
    char sTxnCod[7];
    char sTrsTyp[2]; /*传输类型*/

    if (strlen(curr_inf->txn_code) == 0)
	  {
   	    memset(sTxnKnd,0,sizeof(sTxnKnd));
        memset(sMsgId,0,sizeof(sMsgId));
        memset(sTxnCod,0,sizeof(sTxnCod));
        memset(sTrsTyp,0,sizeof(sTrsTyp));
        /*取交易码*/
        memcpy(sTxnCod, in_data + 27+12, 6); 
        /*取传输类型*/
        memcpy(sTrsTyp, in_data + 25+12, 1); 
        memcpy(curr_inf->txn_code, sTxnCod, 6);       
        curr_inf->txn_code[6] = '\0';
        memcpy(sTxnKnd, in_data + 53+12, 4);
        memcpy(sMsgId, in_data + 58+12, 4);

        /*银行接收在线支付即时回应*/
        
        if ( (strcmp(sTxnKnd, "1002") == 0)  && (strcmp(sMsgId, "2212") == 0) && (strcmp(sTrsTyp, "0") == 0))
        {
          strcpy(curr_inf->txn_code,"T01245"); 	        
	        curr_inf->rq_or_rp = 2;
        }
        /*银行接收登录退出业务系统即时回应*/
        else if ( (strcmp(sTxnKnd, "9001") == 0)  && (strcmp(sMsgId, "XXXX") == 0) )
        {
 	        strcpy(curr_inf->txn_code,"T00145"); 	        
	        curr_inf->rq_or_rp = 2;
        }
        /*银行接收发送机构信息即时回应*/
        else if ( (strcmp(sTxnKnd, "2002") == 0)  && (strcmp(sMsgId, "2233") == 0) && (strcmp(sTrsTyp, "0") == 0))
        {
 	        strcpy(curr_inf->txn_code,"T00145"); 	        
	        curr_inf->rq_or_rp = 2;
        }        
        *out_data = (char *)malloc(len1 + 1);
        *len2 = len1-12;
        memcpy(*out_data, in_data+12, *len2);
        *(*out_data + *len2) = '\0';
    }
    else
    {
        *out_data = (char *)malloc(len1 + 1);
        *len2 = len1;
        memcpy(*out_data, in_data, *len2);
        *(*out_data + *len2) = '\0';
    }
    return(0);
}


int spe_cbs(CurrInf *curr_inf, char *in_data, int len1, char **out_data, int *len2)
{
	char lenstr[5];
  char len1str[7];
  char sbuf[3];

/*4 bit is mac 12 is prehen*/
  *len2 = len1+12;	
  *out_data = (char *)malloc(len1+17);
  memset(sbuf,0,sizeof(sbuf));
  sbuf[0]=0xef;
  sbuf[1]=0x14;
	memcpy(*out_data,sbuf, 2);
	sprintf( lenstr, "%04d", len1+10);
	memcpy(*out_data+2,lenstr, 4);
 	memcpy(*out_data+6,"000000", 6);
  memcpy(*out_data+12,in_data, len1);
  sprintf( len1str, "%06d", len1);
  memcpy(*out_data+12+18,len1str, 6); 
/*  memcpy(*out_data+len1+12,"0000", 4); */
	*(*out_data+*len2) = '\0';
    return(0);
}
