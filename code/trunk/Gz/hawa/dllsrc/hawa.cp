/******************************************************************************       
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.            

  File name    : haw441.cp
  Author       : Jamez
  Version      : 1.0  
  Date         : 2008.11.15  
  Description  : 住房补贴系统个性化原子函数
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
  Description       : 加密
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : CbsFeeRat
  Table Updated      : 无
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int HawGetFmpVal(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
  EXEC SQL END DECLARE SECTION;
    char   sFmpSrc[FmpSrcLen+1];
    char   sFmpVal[FmpValLen+1];
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin HawGetFmpVal.\n" );
/*
**  检查输入参数个数
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "HAW999", "参数个数错" );
    bpErrorLog( trdata, "HawGetFmpVal: 参数个数错!" );
    return( -1 );
  }
  ClearStr( sFmpSrc );
  ClearStr( sFmpVal );
	strcpy( sFmpSrc, Step_Arg1 );
  MD5X(sFmpSrc,sFmpVal);
  etfAddOrRepNode( TrNode, "FmpVal", sFmpVal, FmpValLen );
  bpAddResult( TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End HawGetFmpVal.\n" );
  return (0);
}
/******************************************************************************
  Function          : RtyToHex
  Description       : 将字符数字转换为字符十六进制
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : 
  Table Updated      : 无
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
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
**  检查输入参数个数
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "HAW999", "参数个数错" );
    bpErrorLog( trdata, "HawToHex: 参数个数错!" );
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
  Description       : 字符串从后每两个字符倒排
  Example           :  00000156转换为56010000
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : 
  Table Updated      : 无
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
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
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin HawRevOrd.\n" );
/*
**  检查输入参数个数
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "HAW999", "参数个数错" );
    bpErrorLog( trdata, "HawRevOrd: 参数个数错!" );
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
