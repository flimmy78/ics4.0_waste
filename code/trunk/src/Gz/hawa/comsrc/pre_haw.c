/********************************************************************
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.

  File name    : pre_haw.c
  Author       : Jamez
  Version      : 1.0  
  Date         : 2008.12.15  
  Description  : ������ס������ϵͳԤ������
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
  Description       : ���ر���Ԥ������
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : ��
  Table Updated      : ��
  Input             : ���������ر���( �޷������Ρ���״���ݡ�XML���� )
  Output            : XML��ʽ���ݡ�
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
******************************************************************************/
int pre_haw( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{
  char  sTmpDat1[HexDatLen+1];
  char  sTmpDat2[StatusLen+1];
  char  *sTotLen, *sComId, *sSeqId, *sStatus;

  ClearStr( sTmpDat1 );
  memcpy( sTmpDat1, in_data, HexDatLen );
  if ( HawHexToStr( sTmpDat1, &sTotLen, HexDatLen ) != 0 ) herrlog("pre_haw.log", "������pre_haw�����ĳ��ȡ�TotLen��ת��ʧ��");

  ClearStr( sTmpDat1 );
  memcpy( sTmpDat1, in_data+ComIdOffSet, HexDatLen );
  if ( HawHexToStr( sTmpDat1, &sComId, HexDatLen ) != 0 ) herrlog("pre_haw.log", "������pre_haw����Ӧ���͡�ComId��ת��ʧ��");

  ClearStr( sTmpDat1 );
  memcpy( sTmpDat1, in_data+SeqIdOffSet, HexDatLen );
  if ( HawHexToStr( sTmpDat1, &sSeqId, HexDatLen ) != 0 ) herrlog("pre_haw.log", "������pre_haw����Ϣ��ˮ�š�SeqId��ת��ʧ��");

  ClearStr( sTmpDat2 );
  memcpy( sTmpDat2, in_data+StatusOffSet, StatusLen );
  if ( HawHexToStr( sTmpDat2, &sStatus, StatusLen ) != 0 ) herrlog("pre_haw.log", "������pre_haw��״̬��Status��ת��ʧ��");

herrlog("pre_haw.log", "����pre_haw��TotLen��%s����ComId��%s����SeqId��%s����Status��%s��",sTotLen,sComId,sSeqId,sStatus);
/*
  if ( ( *out_data=(char *)malloc(MaxLen+atoi(sTotLen)) )==NULL ) {
*/
  *out_len=len1-HexDatLen*3-StatusLen+DecDatLen*4;
  if ( ( *out_data=(char *)malloc(*out_len) )==NULL ) {
    herrlog("pre_haw.log", "������pre_haw�������ڴ�ʧ��");
    return( -1 );
  }
  memset( *out_data, 0x00, MaxLen+atol(sTotLen) );
  sprintf( *out_data, "%s%s%s%s", sTotLen, sComId, sSeqId, sStatus );
  memcpy( *out_data+DecDatLen*4, in_data+HexDatLen*3+StatusLen-1, atol(sTotLen)-HexDatLen*3-StatusLen+1 );
  return( 0 );
}
/******************************************************************************
  Function          : HawHexToStr
  Description       : �޷������ͣ�ʮ�����ƣ�תʮ�����ַ�
  Example           : 
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : 
  Table Updated     : ��
  Input             : char *  sSrcDat �����ַ���
                      char ** sDesDat ����ַ���
                      int     iLen    �޷������ͳ���
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
******************************************************************************/
int HawHexToStr( char * sSrcDat, char **sDesDat, int iLen ) 
{
  int   i, j=0;
  char  sHexSrc[HexDatLen+1];
  char  sHexDes[HexDatLen+1];
  char  sDecDat[DecDatLen+1];
/*
**��һ�������޷���4λ����ת��Ϊ16�����ַ���sSrcDat����sHexSrc��
*/
  ClearStr( sHexSrc );
  hhextoasc( sSrcDat, sHexSrc, iLen );
/*
**�ڶ�������ת����16�����ַ��ߡ���λ�ָ���sHexSrc����sHexDes��
*/
  ClearStr( sHexDes );
  for ( i=iLen-2;i>=0;i=i-2 ) memcpy( sHexDes+(iLen-2)-i, sHexSrc+i, 2 );
/*
**������������16�����ַ���Ӧʮ����ֵ
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
    herrlog("pre_haw.log", "������HawHexToStr�����䡾DesDat���ڴ�ʧ��");
    return( -1 );
  }
  memset( *sDesDat, 0x00, iLen+1 );
  memcpy( *sDesDat, sDecDat, sizeof( sDecDat ) );
/*
herrlog("pre_haw.log", "����HawHexToStr��SrcDat��%s������HexSrc��%s������HexDes��%s������DesDat��%s��",sSrcDat,sHexSrc,sHexDes,sDecDat);
*/
  return(0);
}
/******************************************************************************
  Function          : spe_haw2
  Description       : XML�������ͱ���Ԥ������
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : ��
  Table Updated     : ��
  Input             : ���������ر���( �޷������Ρ���״���ݡ�XML���� )
  Output            : XML��ʽ���ݡ�
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**���ݽ����빹���±���
*/
herrlog("spe_haw2.log", "ͨѶ����%s��",in_data);
  switch( atoi(sTComCd) ) {
    case 462452:   /* ��ȡס�����Ҳ�������������Ϣ�������� */
      memcpy( sPrvFrm, in_data+TComCdLen, PrvFrmLen );
      memcpy( sTCrpCd, in_data+TComCdLen+PrvFrmLen, TCrpCdLen );
      memcpy( sRecNum, in_data+TComCdLen+PrvFrmLen+TCrpCdLen, RecNumLen );
      *out_len=sizeof(sTxn52)+len1;
      if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
        herrlog("spe_haw2.log", "������spe_haw2�������ڴ�ʧ��");
        return( -1 );
      }
      memset( *out_data, 0x00, sizeof(sTxn52)+len1+1 );
      sprintf( *out_data, "<HAWDATA><TComCd>%s</TComCd><PrvFrm>%s</PrvFrm><TCrpCd>%s</TCrpCd><RecNum>%s</RecNum>%s</HAWDATA>", sTComCd, sPrvFrm,sTCrpCd,sRecNum,in_data+TComCdLen+PrvFrmLen+TCrpCdLen+RecNumLen );
      break;
    case 462462:   /* ��ȡס�����Ҳ����޸ļ�����������Ϣ�������� */
      memcpy( sRecNum, in_data+TComCdLen, RecNumLen );
      *out_len=sizeof(sTxn62)+len1;
      if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
        herrlog("spe_haw2.log", "������spe_haw2�������ڴ�ʧ��");
        return( -1 );
      }
      memset( *out_data, 0x00, sizeof(sTxn62)+len1+1 );
      sprintf( *out_data, "<HAWDATA><TComCd>%s</TComCd><RecNum>%s</RecNum>%s</HAWDATA>", sTComCd, sRecNum,in_data+TComCdLen+RecNumLen );
      break;
    case 462458:
    case 462459:
      *out_len=sizeof(sTxn58)+len1;
      if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
        herrlog("spe_haw2.log", "������spe_haw2�������ڴ�ʧ��");
        return( -1 );
      }
      memset( *out_data, 0x00, *out_len+1 );
      sprintf( *out_data, "<HAWDATA><TComCd>%s</TComCd></HAWDATA>", in_data );
      break;
    default:
      return( -1 );
  }
herrlog("spe_haw2.log", "ͨѶ����%s��ת����%s��������%s��",sTComCd,in_data,*out_data);
  return( 0 );
}
/******************************************************************************
  Function          : spe_haw
  Description       : ����ͱ��ķ���Ԥ������
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : ��
  Table Updated     : ��
  Input             : �ַ��ͱ���
  Output            : ����ͱ���( �޷������Ρ���״���ݡ�XML���� )
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
  if ( HawStrToHex( sStrTotLen, &sHexTotLen, DecDatLen ) != 0 ) herrlog("sre_haw.log", "������sre_haw�������ܳ��ȡ�TotLen��ת��ʧ��");

	ClearStr( sTmpDat );
  ClearStr( sStrComId );
  memcpy( sTmpDat, in_data, DecDatLen );
	sprintf( sStrComId, "%08X", atoi(sTmpDat) );
  if ( HawStrToHex( sStrComId, &sHexComId, DecDatLen ) != 0 ) herrlog("sre_haw.log", "������sre_haw����Ӧ���͡�ComId��ת��ʧ��");

	ClearStr( sTmpDat );
  ClearStr( sStrSeqId );
  memcpy( sTmpDat, in_data+DecDatLen, DecDatLen );
	sprintf( sStrSeqId, "%08X", atoi(sTmpDat) );
  if ( HawStrToHex( sStrSeqId, &sHexSeqId, DecDatLen ) != 0 ) herrlog("sre_haw.log", "������sre_haw����Ϣ��ˮ�š�SeqId��ת��ʧ��");
herrlog("spe_haw.log", "����spe_haw��TotLen��%s��������%s��ComId��%s��������%s��SeqId��%s��������%s��",sStrTotLen,sHexTotLen,sStrComId,sHexComId,sStrSeqId,sHexSeqId);

  if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("spe_haw.log", "������HawHexToStr�����䡾out_data���ڴ�ʧ��");
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
  Description       : ʮ�����ַ�ת�޷������ͣ�ʮ�����ƣ�
  Example           : 
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : 
  Table Updated     : ��
  Input             : char *  sSrcDat �����ַ���
                      char ** sDesDat ����ַ���
                      int     iLen    �޷������ͳ���
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**��һ������16�����ַ��ߡ���λ��λ��sSrcDat����sDecSrc��
*/
  ClearStr( sDecSrc );
  for ( i=iLen-2;i>=0;i=i-2 ) memcpy( sDecSrc+(iLen-2)-i, sSrcDat+i, 2 );
/*
**�ڶ��������޷���4λ����ת��Ϊ16�����ַ���sDecSrc����sHexDes��
*/
  ClearStr( sHexDes );
  hasctohex( sDecSrc, sHexDes, HexDatLen );
  if ( ( *sDesDat=(char *)malloc(HexDatLen+1) )==NULL ) {
    herrlog("pre_haw.log", "������HawStrToHex�����䡾DesDat���ڴ�ʧ��");
    return( -1 );
  }
  memset( *sDesDat, 0x00, HexDatLen+1 );
  memcpy( *sDesDat, sHexDes, DecDatLen );
/*
herrlog("pre_haw.log", "����HawStrToHex��SrcDat��%s������DecSrc��%s������HexDes��%s��",sSrcDat,sDecSrc,sHexDes);
*/
  return(0);
}
