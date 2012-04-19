/********************************************************************
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.

  File name    : pre_icca.c
  Author       : xuan
  Version      : 1.0  
  Date         : 2010.05.18  
  Description  : ���ݴ�ѧ��IC������ϵͳԤ������
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

herrlog("pre_icca.log", "������spe_icca�����������ݡ�%s��",in_data);

	/*���峤��*/
	iBodyLen = 0;
	iBodyLen_Des = 0;
	iBodyLen_Des_16 = 0;
	iBodyLen = len1 - HeadLen;
	sprintf( sBodyLen, "%04d", iBodyLen );
herrlog("pre_icca.log", "������spe_icca�������峤��sBodyLen��%s��",sBodyLen);
	
	/*�������MAC��*/
	memcpy( sBodyRec, in_data+HeadLen, iBodyLen );
herrlog("pre_icca.log", "������spe_icca����sBodyRec��%s��",sBodyRec);
	/*MD5X( sBodyRec , sBodyMac );*/
	md5( sBodyRec , sBodyMac );
herrlog("pre_icca.log", "������spe_icca����MAC�롾%s��",sBodyMac);
	
	
	/*�������*/
	*out_len = HeadLen + strlen(sBodyRec);
	
	if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("pre_icca.log", "������spe_icca�������䡾out_data���ڴ�ʧ��");
    return( -1 );
	}
	
	memset( *out_data, 0x00, *out_len+1 );
	memcpy( *out_data, in_data, out_len );
	sprintf( *out_data, "%06d", out_len );
	memcpy( *out_data + MesgLenLen + TTxnCdLen + MchIDLen + TTxnTmLen + RetCodLen + TLogNoLen, sBodyMac , BodyMacLen );
herrlog("pre_icca.log", "������spe_icca����out_data��%s��",*out_data);
 return( 0 );
	
}


/***************************************************************************
  Function          : pre_icca
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
herrlog("pre_icca.log", "������pre_icca����iBodyLen��%d��",iBodyLen);
  if ( iBodyLen!=0 ){
    memcpy( sBodyRec, in_data+HeadLen,	iBodyLen );
    herrlog("pre_icca.log", "������pre_icca����sBodyRec��%s��",sBodyRec);
	
	  /*У�����MAC*/
	  /*MD5X( sBodyRec, sBodyMac );*/
	  md5( sBodyRec, sBodyMac );
    herrlog("pre_icca.log", "������pre_icca����sBodyMac��%s��",sBodyMac);
	  memcpy( sBodyMac_ORG, in_data+MesgLenLen+TTxnCdLen+MchIDLen+TTxnTmLen+RetCodLen+TLogNoLen, BodyMacLen );
	  if ( strcmp(sBodyMac_ORG,sBodyMac)!=0 ){
      herrlog("pre_icca.log", "������pre_icca��MACУ��ʧ��");
      return( -1 );	  
	  }
  }
	
	
	/*������ݰ�*/
	*out_len = HeadLen + iBodyLen;
  if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("pre_icca.log", "������pre_icca�������ڴ�ʧ��");
    return( -1 );
  }	
	memset( *out_data, 0x00, *out_len+1 );
	memcpy( *out_data, in_data, HeadLen );
	if ( iBodyLen!=0 ){
	  memcpy( *out_data+HeadLen, sBodyRec, iBodyLen);
	}
herrlog("pre_icca.log", "������pre_icca����out_data��%s��",*out_data);
   return( 0 );
	
}
