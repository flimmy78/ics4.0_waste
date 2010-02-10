/********************************************************************
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.

  File name    : pre_haw.c
  Author       : Jamez
  Version      : 1.0  
  Date         : 2008.12.15  
  Description  : 广州市住房补贴系统预处理函数
  History      :


  No.  Date    Author    Modification
  ===  ==========  ========  ============================

*********************************************************************/
#include <stdlib.h>
#include "hiafp.h"
#include "hihaw.h"
#define  ClearStr(str) memset(str,'\0',sizeof(str))
/******************************************************************************
  Function          : pre_haw
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
int pre_haw( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{
  char  sTmpDat1[HexDatLen+1];
  char  sTmpDat2[StatusLen+1];
  char  *sTotLen, *sComId, *sSeqId, *sStatus;

  ClearStr( sTmpDat1 );
  memcpy( sTmpDat1, in_data, HexDatLen );
  if ( HawHexToStr( sTmpDat1, &sTotLen, HexDatLen ) != 0 ) herrlog("pre_haw.log", "函数【pre_haw】报文长度【TotLen】转换失败");

  ClearStr( sTmpDat1 );
  memcpy( sTmpDat1, in_data+ComIdOffSet, HexDatLen );
  if ( HawHexToStr( sTmpDat1, &sComId, HexDatLen ) != 0 ) herrlog("pre_haw.log", "函数【pre_haw】响应类型【ComId】转换失败");

  ClearStr( sTmpDat1 );
  memcpy( sTmpDat1, in_data+SeqIdOffSet, HexDatLen );
  if ( HawHexToStr( sTmpDat1, &sSeqId, HexDatLen ) != 0 ) herrlog("pre_haw.log", "函数【pre_haw】消息流水号【SeqId】转换失败");

  ClearStr( sTmpDat2 );
  memcpy( sTmpDat2, in_data+StatusOffSet, StatusLen );
  if ( HawHexToStr( sTmpDat2, &sStatus, StatusLen ) != 0 ) herrlog("pre_haw.log", "函数【pre_haw】状态【Status】转换失败");

herrlog("pre_haw.log", "函数pre_haw：TotLen【%s】－ComId【%s】－SeqId【%s】－Status【%s】",sTotLen,sComId,sSeqId,sStatus);
/*
  if ( ( *out_data=(char *)malloc(MaxLen+atoi(sTotLen)) )==NULL ) {
*/
  *out_len=len1-HexDatLen*3-StatusLen+DecDatLen*4;
  if ( ( *out_data=(char *)malloc(*out_len) )==NULL ) {
    herrlog("pre_haw.log", "函数【pre_haw】分配内存失败");
    return( -1 );
  }
  memset( *out_data, 0x00, MaxLen+atol(sTotLen) );
  sprintf( *out_data, "%s%s%s%s", sTotLen, sComId, sSeqId, sStatus );
  memcpy( *out_data+DecDatLen*4, in_data+HexDatLen*3+StatusLen-1, atol(sTotLen)-HexDatLen*3-StatusLen+1 );
  return( 0 );
}
/******************************************************************************
  Function          : HawHexToStr
  Description       : 无符号整型（十六进制）转十进制字符
  Example           : 
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : 
  Table Updated     : 无
  Input             : char *  sSrcDat 输入字符串
                      char ** sDesDat 输出字符串
                      int     iLen    无符号整型长度
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int HawHexToStr( char * sSrcDat, char **sDesDat, int iLen ) 
{
  int   i, j=0;
  char  sHexSrc[HexDatLen+1];
  char  sHexDes[HexDatLen+1];
  char  sDecDat[DecDatLen+1];
/*
**第一步、将无符号4位整型转换为16进制字符【sSrcDat－＞sHexSrc】
*/
  ClearStr( sHexSrc );
  hhextoasc( sSrcDat, sHexSrc, iLen );
/*
**第二步、将转换后16进制字符高、低位恢复【sHexSrc－＞sHexDes】
*/
  ClearStr( sHexDes );
  for ( i=iLen-2;i>=0;i=i-2 ) memcpy( sHexDes+(iLen-2)-i, sHexSrc+i, 2 );
/*
**第三步、计算16进制字符对应十进制值
*/
  j=0;
  for(i=0; i<iLen; i++) { 
    if ( ( sHexDes[i] >= '0' ) && ( sHexDes[i] <= '9' ) ) j = j*16 + sHexDes[i] - '0';
    if ( ( sHexDes[i] >= 'a' ) && ( sHexDes[i] <= 'f' ) ) j = j*16 + sHexDes[i] - 'a' + 10;
    if ( ( sHexDes[i] >= 'A' ) && ( sHexDes[i] <= 'F' ) ) j = j*16 + sHexDes[i] - 'A' + 10;
  } 
  ClearStr( sDecDat );
  sprintf( sDecDat, "%08d", j );
  if ( ( *sDesDat=(char *)malloc(sizeof(sDecDat)+1) )==NULL ) {
    herrlog("pre_haw.log", "函数【HawHexToStr】分配【DesDat】内存失败");
    return( -1 );
  }
  memset( *sDesDat, 0x00, iLen+1 );
  memcpy( *sDesDat, sDecDat, sizeof( sDecDat ) );
/*
herrlog("pre_haw.log", "函数HawHexToStr：SrcDat【%s】－＞HexSrc【%s】－＞HexDes【%s】－＞DesDat【%s】",sSrcDat,sHexSrc,sHexDes,sDecDat);
*/
  return(0);
}
/******************************************************************************
  Function          : spe_haw2
  Description       : XML解析发送报文预处理函数
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : 无
  Table Updated     : 无
  Input             : 第三方返回报文( 无符号整形、流状数据、XML数据 )
  Output            : XML格式数据。
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int spe_haw2( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{
  char  sTComCd[TComCdLen+1];
  char  sPrvFrm[PrvFrmLen+1];
  char  sTCrpCd[TCrpCdLen+1];
  char  sRecNum[RecNumLen+1];
  
  char  sTxn52[]="<HAWDATA><TComCd></TComCd><PrvFrm></PrvFrm><TCrpCd></TCrpCd><RecNum></RecNum></HAWDATA>";
  char  sTxn62[]="<HAWDATA><TComCd></TComCd><RecNum></RecNum></HAWDATA>";
  char  sTxn58[]="<HAWDATA><TComCd></TComCd></HAWDATA>";
 
  ClearStr( sTComCd );
  ClearStr( sPrvFrm );
  ClearStr( sTCrpCd );
  ClearStr( sRecNum );
  memcpy( sTComCd, in_data, TComCdLen );
/*
**根据交易码构建新报文
*/
herrlog("spe_haw2.log", "通讯包【%s】",in_data);
  switch( atoi(sTComCd) ) {
    case 462452:   /* 获取住房货币补贴开户个人信息【批量】 */
      memcpy( sPrvFrm, in_data+TComCdLen, PrvFrmLen );
      memcpy( sTCrpCd, in_data+TComCdLen+PrvFrmLen, TCrpCdLen );
      memcpy( sRecNum, in_data+TComCdLen+PrvFrmLen+TCrpCdLen, RecNumLen );
      *out_len=sizeof(sTxn52)+len1;
      if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
        herrlog("spe_haw2.log", "函数【spe_haw2】分配内存失败");
        return( -1 );
      }
      memset( *out_data, 0x00, sizeof(sTxn52)+len1+1 );
      sprintf( *out_data, "<HAWDATA><TComCd>%s</TComCd><PrvFrm>%s</PrvFrm><TCrpCd>%s</TCrpCd><RecNum>%s</RecNum>%s</HAWDATA>", sTComCd, sPrvFrm,sTCrpCd,sRecNum,in_data+TComCdLen+PrvFrmLen+TCrpCdLen+RecNumLen );
      break;
    case 462462:   /* 获取住房货币补贴修改及特殊销户信息【批量】 */
      memcpy( sRecNum, in_data+TComCdLen, RecNumLen );
      *out_len=sizeof(sTxn62)+len1;
      if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
        herrlog("spe_haw2.log", "函数【spe_haw2】分配内存失败");
        return( -1 );
      }
      memset( *out_data, 0x00, sizeof(sTxn62)+len1+1 );
      sprintf( *out_data, "<HAWDATA><TComCd>%s</TComCd><RecNum>%s</RecNum>%s</HAWDATA>", sTComCd, sRecNum,in_data+TComCdLen+RecNumLen );
      break;
    case 462458:
    case 462459:
      *out_len=sizeof(sTxn58)+len1;
      if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
        herrlog("spe_haw2.log", "函数【spe_haw2】分配内存失败");
        return( -1 );
      }
      memset( *out_data, 0x00, *out_len+1 );
      sprintf( *out_data, "<HAWDATA><TComCd>%s</TComCd></HAWDATA>", in_data );
      break;
    default:
      return( -1 );
  }
herrlog("spe_haw2.log", "通讯包【%s】转换【%s】－＞【%s】",sTComCd,in_data,*out_data);
  return( 0 );
}
/******************************************************************************
  Function          : spe_haw
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
int spe_haw( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{
  char  sStrTotLen[DecDatLen+1];
  char  sStrComId[DecDatLen+1];
  char  sStrSeqId[DecDatLen+1];
  char  sTmpDat[DecDatLen+1];
  char  *sHexTotLen, *sHexComId, *sHexSeqId;

  ClearStr( sStrTotLen );
  *out_len=TotLenLen+ComIdLen+SeqIdLen+len1-DecDatLen-DecDatLen;
	sprintf( sStrTotLen, "%08X", *out_len );
  if ( HawStrToHex( sStrTotLen, &sHexTotLen, DecDatLen ) != 0 ) herrlog("sre_haw.log", "函数【sre_haw】报文总长度【TotLen】转换失败");

	ClearStr( sTmpDat );
  ClearStr( sStrComId );
  memcpy( sTmpDat, in_data, DecDatLen );
	sprintf( sStrComId, "%08X", atoi(sTmpDat) );
  if ( HawStrToHex( sStrComId, &sHexComId, DecDatLen ) != 0 ) herrlog("sre_haw.log", "函数【sre_haw】响应类型【ComId】转换失败");

	ClearStr( sTmpDat );
  ClearStr( sStrSeqId );
  memcpy( sTmpDat, in_data+DecDatLen, DecDatLen );
	sprintf( sStrSeqId, "%08X", atoi(sTmpDat) );
  if ( HawStrToHex( sStrSeqId, &sHexSeqId, DecDatLen ) != 0 ) herrlog("sre_haw.log", "函数【sre_haw】消息流水号【SeqId】转换失败");
herrlog("spe_haw.log", "函数spe_haw：TotLen【%s】－＞【%s】ComId【%s】－＞【%s】SeqId【%s】－＞【%s】",sStrTotLen,sHexTotLen,sStrComId,sHexComId,sStrSeqId,sHexSeqId);

  if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("spe_haw.log", "函数【HawHexToStr】分配【out_data】内存失败");
    return( -1 );
  }
  memset( *out_data, 0x00, *out_len+1 );
	memcpy( *out_data, sHexTotLen, HexDatLen );
	memcpy( *out_data+HexDatLen, sHexComId, HexDatLen );
	memcpy( *out_data+HexDatLen+HexDatLen, sHexSeqId, HexDatLen );
	memcpy( *out_data+HexDatLen+HexDatLen+HexDatLen, in_data+DecDatLen+DecDatLen, len1-DecDatLen-DecDatLen );
/*
  sprintf( *out_data, "%s%s%s%s", sHexTotLen,sHexComId,sHexSeqId,in_data+DecDatLen+DecDatLen );
*/
  return( 0 );
}
/******************************************************************************
  Function          : HawStrToHex
  Description       : 十进制字符转无符号整型（十六进制）
  Example           : 
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : 
  Table Updated     : 无
  Input             : char *  sSrcDat 输入字符串
                      char ** sDesDat 输出字符串
                      int     iLen    无符号整型长度
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int HawStrToHex( char * sSrcDat, char **sDesDat, int iLen ) 
{
  int   i, j=0;
  char  sDecSrc[DecDatLen+1];
  char  sHexDes[HexDatLen+1];
/* 
  char  sDecDat[DecDatLen+1];
*/
/*
**第一步、将16进制字符高、低位易位【sSrcDat－＞sDecSrc】
*/
  ClearStr( sDecSrc );
  for ( i=iLen-2;i>=0;i=i-2 ) memcpy( sDecSrc+(iLen-2)-i, sSrcDat+i, 2 );
/*
**第二步、将无符号4位整型转换为16进制字符【sDecSrc－＞sHexDes】
*/
  ClearStr( sHexDes );
  hasctohex( sDecSrc, sHexDes, HexDatLen );
  if ( ( *sDesDat=(char *)malloc(HexDatLen+1) )==NULL ) {
    herrlog("pre_haw.log", "函数【HawStrToHex】分配【DesDat】内存失败");
    return( -1 );
  }
  memset( *sDesDat, 0x00, HexDatLen+1 );
  memcpy( *sDesDat, sHexDes, DecDatLen );
/*
herrlog("pre_haw.log", "函数HawStrToHex：SrcDat【%s】－＞DecSrc【%s】－＞HexDes【%s】",sSrcDat,sDecSrc,sHexDes);
*/
  return(0);
}
