/********************************************************************
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.

  File name    : pre_icca.c
  Author       : xuan
  Version      : 1.0  
  Date         : 2010.05.18  
  Description  : 广州大学城IC联名卡系统预处理函数
  History      :


  No.  Date    Author    Modification
  ===  ==========  ========  ============================
 **********************************************************************/ 
#include   <stdlib.h>
#include   "hiafp.h"
#include   "hiicca.h"
#define    ClearStr(str) memset(str,'\0',sizeof(str))

/******************************************************************************
  Function          : spe_icca
  Description       : 混合型报文发送预处理函数
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : 无
  Table Updated     : 无
  Input             : 字符型报文
  Output            : 混合型报文( 无符号整形、流状数据、XML数据 )
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int spe_icca( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{
	char sBodyLen[BodyLenLen+1];
	char sBodyLen_DES[BodyLenLen+1];
	char sBodyLen_DES_16[BodyLenLen+1];
	char sBodyMac[BodyMacLen+1];
	char sBodyRec[1024];
	char sBodyRec_DES[1024];
	char sBodyRec_DES_16[1024];
	int  iBodyLen,iBodyLen_Des,iBodyLen_Des_16;
	int  i;
	
	ClearStr( sBodyLen );
	ClearStr( sBodyLen_DES );
	ClearStr( sBodyLen_DES_16 );
	ClearStr( sBodyMac );
	ClearStr( sBodyRec );
	ClearStr( sBodyRec_DES );
	ClearStr( sBodyRec_DES_16 );

herrlog("pre_icca.log", "函数【spe_icca】：包体内容【%s】",in_data);

	/*包体长度*/
	iBodyLen = 0;
	iBodyLen_Des = 0;
	iBodyLen_Des_16 = 0;
	iBodyLen = len1 - HeadLen;
	sprintf( sBodyLen, "%04d", iBodyLen );
herrlog("pre_icca.log", "函数【spe_icca】：包体长度sBodyLen【%s】",sBodyLen);
	
	/*计算包体MAC码*/
	memcpy( sBodyRec, in_data+HeadLen, iBodyLen );
herrlog("pre_icca.log", "函数【spe_icca】：sBodyRec【%s】",sBodyRec);
	/*MD5X( sBodyRec , sBodyMac );*/
	md5( sBodyRec , sBodyMac );
herrlog("pre_icca.log", "函数【spe_icca】：MAC码【%s】",sBodyMac);
	
	
	/*输出报文*/
	*out_len = HeadLen + strlen(sBodyRec);
	
	if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("pre_icca.log", "函数【spe_icca】：分配【out_data】内存失败");
    return( -1 );
	}
	
	memset( *out_data, 0x00, *out_len+1 );
	memcpy( *out_data, in_data, out_len );
	sprintf( *out_data, "%06d", out_len );
	memcpy( *out_data + MesgLenLen + TTxnCdLen + MchIDLen + TTxnTmLen + RetCodLen + TLogNoLen, sBodyMac , BodyMacLen );
herrlog("pre_icca.log", "函数【spe_icca】：out_data【%s】",*out_data);
 return( 0 );
	
}


/***************************************************************************
  Function          : pre_icca
  Description       : 返回报文预处理函数
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : 无
  Table Updated      : 无
  Input             : 第三方返回报文( 无符号整形、流状数据、XML数据 )
  Output            : XML格式数据。
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int pre_icca( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{
	char sBodyLen[BodyLenLen+1];
	char sBodyMac[BodyMacLen+1];
	char sBodyMac_ORG[BodyMacLen+1];
	char sBodyRec[1024];
	char sBodyRec_DES[1024];
	int  iBodyLen;
	int  iBodyLen_DES;
	
	ClearStr( sBodyRec );
	ClearStr( sBodyRec_DES );
	ClearStr( sBodyMac );
	ClearStr( sBodyMac_ORG );
	
	
	
	iBodyLen = len1 - HeadLen;
herrlog("pre_icca.log", "函数【pre_icca】：iBodyLen【%d】",iBodyLen);
  if ( iBodyLen!=0 ){
    memcpy( sBodyRec, in_data+HeadLen,	iBodyLen );
    herrlog("pre_icca.log", "函数【pre_icca】：sBodyRec【%s】",sBodyRec);
	
	  /*校验包体MAC*/
	  /*MD5X( sBodyRec, sBodyMac );*/
	  md5( sBodyRec, sBodyMac );
    herrlog("pre_icca.log", "函数【pre_icca】：sBodyMac【%s】",sBodyMac);
	  memcpy( sBodyMac_ORG, in_data+MesgLenLen+TTxnCdLen+MchIDLen+TTxnTmLen+RetCodLen+TLogNoLen, BodyMacLen );
	  if ( strcmp(sBodyMac_ORG,sBodyMac)!=0 ){
      herrlog("pre_icca.log", "函数【pre_icca】MAC校验失败");
      return( -1 );	  
	  }
  }
	
	
	/*输出数据包*/
	*out_len = HeadLen + iBodyLen;
  if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("pre_icca.log", "函数【pre_icca】分配内存失败");
    return( -1 );
  }	
	memset( *out_data, 0x00, *out_len+1 );
	memcpy( *out_data, in_data, HeadLen );
	if ( iBodyLen!=0 ){
	  memcpy( *out_data+HeadLen, sBodyRec, iBodyLen);
	}
herrlog("pre_icca.log", "函数【pre_icca】：out_data【%s】",*out_data);
   return( 0 );
	
}
