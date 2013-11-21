/********************************************************************
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.

  File name    : pre_tbc.c
  Author       : xuan
  Version      : 1.0  
  Date         : 2010.05.18  
  Description  : 广东烟草营销系统预处理函数
  History      :


  No.  Date    Author    Modification
  ===  ==========  ========  ============================
 **********************************************************************/ 
#include   <stdlib.h>
#include   "hiafp.h"
#include   "hitbc.h"
#define    ClearStr(str) memset(str,'\0',sizeof(str))

/******************************************************************************
  Function          : spe_tbc
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
int spe_tbc( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{

	  char sTranCode[4+1];   /*交易代码*/
	  char sDeptCode[4+1];   /*公司代码*/
	  char sComKey[16+1];    /*通讯密钥*/
	  char sFileName[255];   /*密钥文件*/
	  FILE  *fp;
	  
  char sMsgLen[MsgLenLen+1]; /*消息长度*/
	char sBodyLen[MsgLenLen+1];
	char sBodyLen_DES[MsgLenLen+1];
	char sBodyLen_DES_16[MsgLenLen+1];
	char sBodyRec[4096];
	char sBodyRec_DES[4096];
	char sBodyRec_DES_16[4096];
	int  iBodyLen,iBodyLen_DES,iBodyLen_DES_16;
	int  i,ret;
	DBConHandle * DBHandle;
	
	ClearStr( sMsgLen );
	ClearStr( sBodyLen );
	ClearStr( sBodyLen_DES );
	ClearStr( sBodyLen_DES_16 );
	ClearStr( sBodyRec );
	ClearStr( sBodyRec_DES );
	ClearStr( sBodyRec_DES_16 );
	ClearStr( sTranCode );
	ClearStr( sDeptCode );

herrlog("pre_tbc.log", "函数【spe_tbc】：包体内容【%s】",in_data);

	/*包体长度*/
	iBodyLen = 0;
	iBodyLen_DES = 0;
	iBodyLen_DES_16 = 0;
	iBodyLen = len1 ;
	sprintf( sBodyLen, "%04d", iBodyLen );
herrlog("pre_tbc.log", "函数【spe_tbc】：包体长度sBodyLen【%s】",sBodyLen);
	memcpy( sBodyRec, in_data, iBodyLen );
	
	i = hgetcharspos( sBodyRec, "<DPT_ID>" );
  /*截取公司代码*/
  memcpy( sDeptCode, sBodyRec+i+8, DepCodLen );

	i = hgetcharspos( sBodyRec, "<TRADE_ID>" );
  /*截取交易代码*/
  memcpy( sTranCode, sBodyRec+i+10, TranCodLen );
	
	/*包体DES加密*/
	memcpy( sBodyRec_DES, sBodyRec, iBodyLen );
	iBodyLen_DES = strlen(sBodyRec_DES)%8;	
  switch(iBodyLen_DES)
  {
    case 0: iBodyLen_DES = strlen(sBodyRec_DES); break;
    case 1: iBodyLen_DES = strlen(sBodyRec_DES) + 7;break;
    case 2: iBodyLen_DES = strlen(sBodyRec_DES) + 6;break;
    case 3: iBodyLen_DES = strlen(sBodyRec_DES) + 5;break;
    case 4: iBodyLen_DES = strlen(sBodyRec_DES) + 4;break;
    case 5: iBodyLen_DES = strlen(sBodyRec_DES) + 3;break;
    case 6: iBodyLen_DES = strlen(sBodyRec_DES) + 2;break;
    case 7: iBodyLen_DES = strlen(sBodyRec_DES) + 1;break;
  }

  switch( atoi(sTranCode) ){
    case 8910:
    case 8888:
    case 8918:
    	/*test*/
    	ret = TriDes( DesKey, sBodyRec_DES, iBodyLen_DES);
    	if ( ret != 0 ){
    		herrlog("pre_tbc.log", "函数【spe_tbc】：TriUNDes解密失败2");
    		return -1;    	  
    	}

    	break;
    default:
    	memcpy( sFileName, HomeDir, strlen(HomeDir) );
      memcpy( sFileName+strlen(HomeDir), sDeptCode, DepCodLen );
      memcpy( sFileName+strlen(HomeDir)+DepCodLen, ".key", 4 );
      fp = fopen( sFileName, "r" );
      if( fp == NULL ) {
        herrlog( "pre_tbc.log", "函数【spe_tbc】：打开数据文件【%s】失败", sFileName );
        fclose( fp );
        return( -1 );
      }
      fgets( sComKey, KeyLen+1, fp );
      herrlog( "pre_tbc.log", "函数【spe_tbc】：sComKey=【%s】", sComKey );
      fclose( fp );
      /*test*/
    	ret = TriDes( sComKey, sBodyRec_DES, iBodyLen_DES);
    	if ( ret != 0 ){
    		herrlog("pre_tbc.log", "函数【spe_tbc】：TriUNDes解密失败2");
    		return -1;    	  
    	}

  }  
herrlog("pre_tbc.log", "函数【spe_tbc】：sBodyRec_DES【%s】",sBodyRec_DES);

	
	/*包体加密后转成十六进制
	 hhextoasc( sBodyRec_DES, sBodyRec_DES_16, iBodyLen_DES*2);
herrlog("pre_tbc.log", "函数【spe_tbc】：sBodyRec_DES_16【%s】",sBodyRec_DES_16);  
  */
  

  sprintf( sMsgLen, "%04d", MsgHedLen+TranCodLen+DepCodLen+iBodyLen_DES+EndLen );
herrlog("pre_tbc.log", "函数【spe_tbc】：sMsgLen【%s】",sMsgLen);
	
	/*输出报文*/
	*out_len = HeadLen + iBodyLen_DES;
	*out_len = *out_len + EndLen;
	
	if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("pre_tbc.log", "函数【spe_tbc】：分配【out_data】内存失败");
    return( -1 );
	}
	
	memset( *out_data, 0x00, *out_len+1 );
	memcpy( *out_data, sMsgLen, MsgLenLen );
	memcpy( *out_data + MsgLenLen, "TEB", MsgHedLen );
	memcpy( *out_data + MsgLenLen + MsgHedLen, sTranCode, TranCodLen );
	memcpy( *out_data + MsgLenLen + MsgHedLen + TranCodLen, sDeptCode, DepCodLen );
	memcpy( *out_data + MsgLenLen + MsgHedLen + TranCodLen + DepCodLen, sBodyRec_DES, iBodyLen_DES );
	memcpy( *out_data + MsgLenLen + MsgHedLen + TranCodLen + DepCodLen + iBodyLen_DES, "***" , EndLen );
herrlog("pre_tbc.log", "函数【spe_tbc】：out_data【%s】",*out_data);
herrlog("pre_tbc.log", "函数【pre_tbc】：=====END===================广东烟草系统开始返回数据=========================");
 return( 0 );
	
}


/***************************************************************************
  Function          : pre_tbc
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
int pre_tbc( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{

	  char sTranCode[TranCodLen+1];   /*交易代码*/
	  char sDeptCode[DepCodLen+1];    /*公司代码*/
	  char sComKey[KeyLen+1];         /*通讯密钥*/
	  char sFileName[255];            /*密钥文件*/
	  FILE  *fp;

	char sBodyLen[MsgLenLen+1];
	char sBodyRec[4096];
	char sBodyRec_DES[4096];
	int  iBodyLen;
	int  iBodyLen_DES;
	int  ret;

herrlog("pre_tbc.log", "函数【pre_tbc】：=====BEGIN=============广东烟草系统开始接收数据=========================");
	
	ClearStr( sBodyRec );
	ClearStr( sBodyRec_DES );
	ClearStr( sTranCode );
	ClearStr( sDeptCode );
	ClearStr( sTranCode );
	ClearStr( sComKey );
	ClearStr( sFileName );

	
	
	/*包体DES解密*/
	iBodyLen_DES = len1 - HeadLen;
	iBodyLen_DES = iBodyLen_DES - EndLen;
herrlog("pre_tbc.log", "函数【pre_tbc】：iBodyLen_DES【%d】",iBodyLen_DES);
	
	memcpy( sBodyRec_DES, in_data+HeadLen,	iBodyLen_DES );
herrlog("pre_tbc.log", "函数【pre_tbc】：sBodyRec_DES【%s】",sBodyRec_DES);

  memcpy( sDeptCode, in_data+MsgLenLen+MsgHedLen+TranCodLen, DepCodLen );
  memcpy( sTranCode, in_data+MsgLenLen+MsgHedLen,	TranCodLen );
herrlog("pre_tbc.log", "函数【pre_tbc】：烟草公司交易码【%s】",sTranCode);
  switch( atoi(sTranCode) ){
    case 8910:
    case 8888:
    case 8918:
    	/*test*/
    	ret = TriUNDes( DesKey, sBodyRec_DES, iBodyLen_DES);
    	if ( ret != 0 ){
    		herrlog("pre_tbc.log", "函数【pre_tbc】：TriUNDes解密失败2");
    		return -1;    	  
    	}
    	
    	break;
    default:
    	memcpy( sFileName, HomeDir, strlen(HomeDir) );
      memcpy( sFileName+strlen(HomeDir), sDeptCode, DepCodLen );
      memcpy( sFileName+strlen(HomeDir)+DepCodLen, ".key", 4 );
      fp = fopen( sFileName, "r" );
      if( fp == NULL ) {
        herrlog( "pre_tbc.log", "函数【pre_tbc】：打开数据文件【%s】失败", sFileName );
        fclose( fp );
        return( -1 );
      }
      fgets( sComKey, KeyLen+1, fp );
      herrlog( "pre_tbc.log", "函数【pre_tbc】：sComKey=【%s】", sComKey );
      fclose( fp );
      /*test*/
    	ret = TriUNDes( sComKey, sBodyRec_DES, iBodyLen_DES);
    	if ( ret != 0 ){
    		herrlog("pre_tbc.log", "函数【pre_tbc】：TriUNDes解密失败2");
    		return -1;    	  
    	}
    	
  }
	iBodyLen = strlen(sBodyRec_DES);  
  memcpy( sBodyRec, sBodyRec_DES,	iBodyLen );
	
	/*输出数据包*/
	*out_len = iBodyLen;
  if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("pre_tbc.log", "函数【pre_tbc】分配内存失败");
    return( -1 );
  }	
	memset( *out_data, 0x00, *out_len+1 );
	memcpy( *out_data, sBodyRec, iBodyLen );
herrlog("pre_tbc.log", "函数【pre_tbc】：out_data【%s】",*out_data);
   return( 0 );
	
}
