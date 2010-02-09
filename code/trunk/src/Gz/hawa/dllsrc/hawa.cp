/******************************************************************************       
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.            

  File name    : haw441.cp
  Author       : Jamez
  Version      : 1.0  
  Date         : 2008.11.15  
  Description  : ס������ϵͳ���Ի�ԭ�Ӻ���
  History      :


  No.  Date    Author    Modification                 
  ===  ==========  ========  ============================

******************************************************************************/
#include <sql.h>
#include "hihaw.h"
#include "hibase.h"
#include "hionline.h"
#include "hidatabase.h"
#include "hibusmsg.h"
#include "hibppubdef.h"
#include "hipex.h"
#define ClearStr(str) memset(str,'\0',sizeof(str))
/******************************************************************************
  Function          : HawGetFmpVal
  Description       : ����
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : CbsFeeRat
  Table Updated      : ��
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
******************************************************************************/
int HawGetFmpVal(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
  EXEC SQL END DECLARE SECTION;
    char   sFmpSrc[FmpSrcLen+1];
    char   sFmpVal[FmpValLen+1];
/*
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin HawGetFmpVal.\n" );
/*
**  ��������������
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "HAW999", "����������" );
    bpErrorLog( trdata, "HawGetFmpVal: ����������!" );
    return( -1 );
  }
  ClearStr( sFmpSrc );
  ClearStr( sFmpVal );
	strcpy( sFmpSrc, Step_Arg1 );
  MD5X(sFmpSrc,sFmpVal);
  etfAddOrRepNode( TrNode, "FmpVal", sFmpVal, FmpValLen );
  bpAddResult( TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End HawGetFmpVal.\n" );
  return (0);
}
/******************************************************************************
  Function          : RtyToHex
  Description       : ���ַ�����ת��Ϊ�ַ�ʮ������
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : 
  Table Updated      : ��
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
******************************************************************************/
int HawToHex(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
  EXEC SQL END DECLARE SECTION;
    char  sSrcDat[MaxLen+1];
    char  sHexDat[MaxLen+1];
    long  i,len;
/*
**  ��������������
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "HAW999", "����������" );
    bpErrorLog( trdata, "HawToHex: ����������!" );
    return( -1 );
  }
  ClearStr( sSrcDat );
  ClearStr( sHexDat );

/*
  len = strlen(Step_Arg1);

  if (!(sAscDat = (char *) malloc(len)))
      return(-1);

  if (!(sHexDat = (char *) malloc(len)))
      return(-1);
*/
  strcpy( sSrcDat, Step_Arg1 );
  i=atol( sSrcDat );
  sprintf( sHexDat,"%X",i );
  etfAddOrRepNode( TrNode, "HexDat", sHexDat, MaxLen );
  return(0);
}
/******************************************************************************
  Function          : HawRevOrd
  Description       : �ַ����Ӻ�ÿ�����ַ�����
  Example           :  00000156ת��Ϊ56010000
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : 
  Table Updated      : ��
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
******************************************************************************/
int HawRevOrd(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
  EXEC SQL END DECLARE SECTION;
  char  sSrcDat[MaxLen+1];
  char  sRevDat[MaxLen+1];
  char  sTmpDat[3];
  long  i,len;

/*
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin HawRevOrd.\n" );
/*
**  ��������������
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "HAW999", "����������" );
    bpErrorLog( trdata, "HawRevOrd: ����������!" );
    return( -1 );
  }
/*
  len = strlen(Step_Arg1);
  if (!(sAscDat = (char *) malloc(len)))
      return(-1);
  if (!(sRevDat = (char *) malloc(len)))
      return(-1);
*/
  ClearStr( sSrcDat );
  ClearStr( sRevDat );
  ClearStr( sTmpDat );

  strcpy( sSrcDat, Step_Arg1 );

  for ( i=MaxLen-2;i>=0;i=i-2 )  {
    memcpy( sTmpDat, sSrcDat+i, 2 );
    strcat( sRevDat, sTmpDat );
  }
  etfAddOrRepNode( TrNode, "RevDat", sRevDat, MaxLen );
/*
  free(sAscDat);
  free(sRevDat);
*/
  return(0);
}
