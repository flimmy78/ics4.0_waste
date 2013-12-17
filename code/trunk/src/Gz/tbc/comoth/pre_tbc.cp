/********************************************************************
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.

  File name    : pre_tbc.c
  Author       : xuan
  Version      : 1.0  
  Date         : 2010.05.18  
  Description  : �㶫�̲�Ӫ��ϵͳԤ��������
  History      :


  No.  Date    Author    Modification
  ===  ==========  ========  ============================
 **********************************************************************/ 
#include   <stdlib.h>
#include   <sql.h>
#include   "hibase.h"
#include   "hionline.h"
#include   "hidatabase.h"
#include   "hibusmsg.h"
#include   "hibppubdef.h"
#include   "hipex.h"
#include   "hiafp.h"
#include   "hitbc.h"
#define    ClearStr(str) memset(str,'\0',sizeof(str))

/******************************************************************************
  Function          : spe_tbc
  Description       : ����ͱ��ķ���Ԥ��������
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : ��
  Table Updated     : ��
  Input             : �ַ��ͱ���
  Output            : ����ͱ���( �޷������Ρ���״���ݡ�XML���� )
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
******************************************************************************/
int spe_tbc( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
	  char sTranCode[4+1];   /*���״���*/
	  char sDeptCode[4+1];   /*��˾����*/
	  char sComKey[16+1];    /*ͨѶ��Կ*/
  EXEC SQL END DECLARE SECTION;
  char sMsgLen[MsgLenLen+1]; /*��Ϣ����*/
	char sBodyLen[MsgLenLen+1];
	char sBodyLen_DES[MsgLenLen+1];
	char sBodyLen_DES_16[MsgLenLen+1];
	char sBodyRec[4096];
	char sBodyRec_DES[4096];
	char sBodyRec_DES_16[4096];
	int  iBodyLen,iBodyLen_DES,iBodyLen_DES_16;
	int  i,ret;
	DBConHandle *DBHandle;
	
	ClearStr( sMsgLen );
	ClearStr( sBodyLen );
	ClearStr( sBodyLen_DES );
	ClearStr( sBodyLen_DES_16 );
	ClearStr( sBodyRec );
	ClearStr( sBodyRec_DES );
	ClearStr( sBodyRec_DES_16 );
	ClearStr( sTranCode );
	ClearStr( sDeptCode );

herrlog("pre_tbc.log", "������spe_tbc�����������ݡ�%s��",in_data);

  

	/*���峤��*/
	iBodyLen = 0;
	iBodyLen_DES = 0;
	iBodyLen_DES_16 = 0;
	iBodyLen = len1 ;
	sprintf( sBodyLen, "%04d", iBodyLen );
herrlog("pre_tbc.log", "������spe_tbc�������峤��sBodyLen��%s��",sBodyLen);
	memcpy( sBodyRec, in_data, iBodyLen );
	
	i = hgetcharspos( sBodyRec, "<DPT_ID>" );
  /*��ȡ��˾����*/
  memcpy( sDeptCode, sBodyRec+i+8, DepCodLen );

	i = hgetcharspos( sBodyRec, "<TRADE_ID>" );
  /*��ȡ���״���*/
  memcpy( sTranCode, sBodyRec+i+10, TranCodLen );
	
	/*����DES����*/
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
    	ret = TriDes( DesKey, sBodyRec_DES, iBodyLen_DES);
    	if ( ret != 0 ){
    		herrlog("pre_tbc.log", "������spe_tbc����TriDes����ʧ��1");
    		return -1;    	  
    	}
    	break;
    default:
      usfOpenDBConnection( "DB1", DBHandle, 1000);
    	EXEC SQL select ComKey into :sComKey from tbcbasinf where DptId = :sDeptCode;
    	if( SQLCODE != SQL_SUCCESS ) {
    		herrlog("pre_tbc.log", "������spe_tbc����TBCBASINF��SELECT����");
    		return -1;
    	}
    	/**
    	ret = TriDes( sComKey, sBodyRec_DES, iBodyLen_DES);
    	if ( ret != 0 ){
    		herrlog("pre_tbc.log", "������spe_tbc����TriDes����ʧ��2");
    		return -1;    	  
    	}
    	**/
    	usfCloseDBConnection(DBHandle);
  }  
herrlog("pre_tbc.log", "������spe_tbc����sBodyRec_DES��%s��",sBodyRec_DES);

	
	/*������ܺ�ת��ʮ������
	 hhextoasc( sBodyRec_DES, sBodyRec_DES_16, iBodyLen_DES*2);
herrlog("pre_tbc.log", "������spe_tbc����sBodyRec_DES_16��%s��",sBodyRec_DES_16);  
  */
  

  sprintf( sMsgLen, "%04d", MsgHedLen+TranCodLen+DepCodLen+iBodyLen_DES+EndLen );
herrlog("pre_tbc.log", "������spe_tbc����sMsgLen��%s��",sMsgLen);
	
	/*�������*/
	*out_len = HeadLen + iBodyLen_DES;
	*out_len = *out_len + EndLen;
	
	if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("pre_tbc.log", "������spe_tbc�������䡾out_data���ڴ�ʧ��");
    return( -1 );
	}
	
	memset( *out_data, 0x00, *out_len+1 );
	memcpy( *out_data, sMsgLen, MsgLenLen );
	memcpy( *out_data + MsgLenLen, "TEB", MsgHedLen );
	memcpy( *out_data + MsgLenLen + MsgHedLen, sTranCode, TranCodLen );
	memcpy( *out_data + MsgLenLen + MsgHedLen + TranCodLen, sDeptCode, DepCodLen );
	memcpy( *out_data + MsgLenLen + MsgHedLen + TranCodLen + DepCodLen, sBodyLen_DES, iBodyLen_DES );
	memcpy( *out_data + MsgLenLen + MsgHedLen + TranCodLen + DepCodLen + iBodyLen_DES, "***" , EndLen );
herrlog("pre_tbc.log", "������spe_tbc����out_data��%s��",*out_data);
 return( 0 );
	
}


/***************************************************************************
  Function          : pre_tbc
  Description       : ���ر���Ԥ��������
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : ��
  Table Updated      : ��
  Input             : ���������ر���( �޷������Ρ���״���ݡ�XML���� )
  Output            : XML��ʽ���ݡ�
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
******************************************************************************/
int pre_tbc( CurrInf * curr_inf,  char * in_data, int len1, char ** out_data, int * out_len )
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
	  char sTranCode[4+1];   /*���״���*/
	  char sDeptCode[4+1];   /*��˾����*/
	  char sComKey[16+1];    /*ͨѶ��Կ*/
  EXEC SQL END DECLARE SECTION;
	char sBodyLen[MsgLenLen+1];
	char sBodyRec[4096];
	char sBodyRec_DES[4096];
	int  iBodyLen;
	int  iBodyLen_DES;
	int  ret;
	DBConHandle *DBHandle;

	
	ClearStr( sBodyRec );
	ClearStr( sBodyRec_DES );
	ClearStr( sTranCode );
	ClearStr( sDeptCode );

	
	
	/*����DES����*/
	iBodyLen_DES = len1 - HeadLen;
	iBodyLen_DES = iBodyLen_DES - EndLen;
herrlog("pre_tbc.log", "������pre_tbc����iBodyLen_DES��%d��",iBodyLen_DES);
	
	memcpy( sBodyRec_DES, in_data+HeadLen,	iBodyLen_DES );
herrlog("pre_tbc.log", "������pre_tbc����sBodyRec_DES��%s��",sBodyRec_DES);

  memcpy( sDeptCode, in_data+MsgLenLen+MsgHedLen+TranCodLen, DepCodLen );
  memcpy( sTranCode, in_data+MsgLenLen+MsgHedLen,	TranCodLen );
  switch( atoi(sTranCode) ){
    case 8910:
    case 8888:
    case 8918:
    	ret = TriUNDes( DesKey, sBodyRec_DES, iBodyLen_DES);
    	if ( ret != 0 ){
    		herrlog("pre_tbc.log", "������pre_tbc����TriUNDes����ʧ��1");
    		return -1;    	  
    	}
    	break;
    default:
    herrlog("pre_tbc.log", "������pre_tbc����1111111111");
      usfOpenDBConnection( "DB1", DBHandle, 100);
    herrlog("pre_tbc.log", "������pre_tbc����2222222222");
    	EXEC SQL select ComKey into :sComKey from tbcbasinf where DptId = :sDeptCode;
    herrlog("pre_tbc.log", "������pre_tbc����3333333333");
    herrlog("pre_tbc.log", "������pre_tbc����sComKey=��%s��",sComKey);
    /**	
    	if( SQLCODE != SQL_SUCCESS ) {
    	herrlog("pre_tbc.log", "������pre_tbc����kkkkkkkkkk");
    		herrlog("pre_tbc.log", "������pre_tbc����TBCBASINF��SELECT����");
    	herrlog("pre_tbc.log", "������pre_tbc����cccccccccc");
    		return -1;
    	}
    	herrlog("pre_tbc.log", "������pre_tbc����4444444444");
    	
    	ret = TriUNDes( sComKey, sBodyRec_DES, iBodyLen_DES);
    	if ( ret != 0 ){
    		herrlog("pre_tbc.log", "������pre_tbc����TriUNDes����ʧ��2");
    		return -1;    	  
    	}
    	**/
    	herrlog("pre_tbc.log", "������pre_tbc����555555555");
    	usfCloseDBConnection(DBHandle);
    	herrlog("pre_tbc.log", "������pre_tbc����6666666666");
  }
	iBodyLen = strlen(sBodyRec_DES);  
  memcpy( sBodyRec, sBodyRec_DES,	iBodyLen );
	
	/*������ݰ�*/
	*out_len = iBodyLen;
  if ( ( *out_data=(char *)malloc(*out_len+1) )==NULL ) {
    herrlog("pre_tbc.log", "������pre_tbc�������ڴ�ʧ��");
    return( -1 );
  }	
	memset( *out_data, 0x00, *out_len+1 );
	memcpy( *out_data, sBodyRec, iBodyLen );
herrlog("pre_tbc.log", "������pre_tbc����out_data��%s��",*out_data);
   return( 0 );
	
}