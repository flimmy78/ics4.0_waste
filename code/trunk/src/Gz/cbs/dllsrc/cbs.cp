/******************************************************************************       
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.            

  File name    : cbs.cp
  Author       : Jamez
  Version      : 1.0  
  Date         : 2005.11.15  
  Description  : 省集中支付平台个性化原子函数
  History      :


  No.  Date    Author    Modification                 
  ===  ==========  ========  ============================

******************************************************************************/
#include <sql.h>
#include "hicbs.h"
#include "hibase.h"
#include "hionline.h"
#include "hidatabase.h"
#include "hibusmsg.h"
#include "hibppubdef.h"
#include "hipex.h"
#define ClearStr(str) memset(str,'\0',sizeof(str))
/******************************************************************************
  Function          : CbsGetFee
  Description       : 计算业务手续费
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
int CbsGetFee(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sTxnKnd[TxnKndLen+1];
    char   sUsgCod[UsgCodLen+1];
    char   sLclFlg[LclFlgLen+1];
    char   sBrNo[BrNoLen+1];
    char   sCcyCod[CcyCodLen+1];
    char   sTxnAmt[TxnAmtLen+1];
    char   sFeeMod[FeeModLen+1];
    char   sFeeAmt[FeeAmtLen+1];
    char   sPstMod[PstModLen+1];
    char   sPstAmt[PstAmtLen+1];
  EXEC SQL END DECLARE SECTION;
    long   iTxnAmt, iFeeTmp, iPstTmp;
    long   iFeeRat, iFeeAmt, iPstRat, iPstAmt;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin CbsGetFee.\n" );
/*
**  检查输入参数个数
*/
  if( Step_Args_Num != 6 ) {
    bpAddResult( TrNode, "CBS999", "参数个数错" );
    bpErrorLog( trdata, "CbsGetFee: 参数个数错!" );
    return( -1 );
  }
/*
**  依次获取资金用途代码、本异地标志、分行号、币种、交易金额
*/
  ClearStr( sTxnKnd );
  ClearStr( sUsgCod );
  ClearStr( sLclFlg );
  ClearStr( sBrNo   );
  ClearStr( sCcyCod );
  ClearStr( sTxnAmt );
  ClearStr( sFeeMod );
  iFeeRat=0;
  iFeeAmt=0;
  ClearStr( sPstMod );
  iPstRat=0;
  iPstAmt=0;

  iFeeTmp=0;
  iPstTmp=0;
  ClearStr( sFeeAmt );
  ClearStr( sPstAmt );
  
  strcpy( sTxnKnd, Step_Arg1 );
  strcpy( sUsgCod, Step_Arg2 );
  strcpy( sLclFlg, Step_Arg3 );
  strcpy( sBrNo,   Step_Arg4 );
  strcpy( sCcyCod, Step_Arg5 );
  strcpy( sTxnAmt, Step_Arg6 );
/*
**  根据输入要素计算费率
*/
  EXEC SQL select case when FeeMod='0' then right( ('000000000000000'||rtrim(char(BIGINT(:sTxnAmt)*BIGINT(FeeRat)/10000))),15) 
                  else FeeAmt
                  end,
                  case when PstMod='0' then right( ('000000000000000'||rtrim(char(BIGINT(:sTxnAmt)*BIGINT(PstRat)/10000))),15) 
                  else PstAmt
                  end
             into :sFeeAmt, :sPstAmt
             from CbsFeeRat
            where TxnKnd = :sTxnKnd
              and UsgCod = :sUsgCod
              and LclFlg = :sLclFlg
              and BrNo = :sBrNo
              and CcyCod = :sCcyCod
              and MinAmt < :sTxnAmt
              and MaxAmt >= :sTxnAmt
              and Sts='0';
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult( TrNode, "CBS999", "没有对应的费率表" );
    bpErrorLog( trdata, "CbsGetFee:没有对应的费率表【%s】【%s】【%s】【%s】【%s】【%s】,SQLCODE【%d】", sTxnKnd, sUsgCod, sLclFlg, sBrNo, sCcyCod, sTxnAmt, SQLCODE );
    return( -1 );
  }
  etfAddOrRepNode( TrNode, "FEEAMT", sFeeAmt, FeeAmtLen );
  etfAddOrRepNode( TrNode, "PSTAMT", sPstAmt, PstAmtLen );

  bpAddResult( TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End CbsGetFee.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsGetAccFlg
  Description       : 判断接收人帐号的性质(个人、企业)
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : 无
  Table Updated      : 无
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int CbsGetAccFlg(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sRcvAct[RcvActLen+1];
    char   sLAccFlg[AccFlgLen+1];
    char   sLActFg[ActFlgLen+1];
    char   sVchTyp[VchTypLen+1];
    char   sBokAct[ActNoLen+1];
    char   sBgnLoc[BgnLocLen+1];
    char   sCenLen[CenLenLen+1];
  EXEC SQL END DECLARE SECTION;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin CbsGetAccFlg.\n" );
/*
**  检查输入参数个数
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "CBS999", "参数个数错" );
    bpErrorLog( trdata, "CbsGetFee: 参数个数错!" );
    return( -1 );
  }
/*
**  获取接收人帐号
*/
  ClearStr( sRcvAct );
  ClearStr( sLAccFlg );
  ClearStr( sLActFg );
  ClearStr( sVchTyp );
  ClearStr( sBokAct );
  strcpy( sRcvAct, Step_Arg1 );
  hdelbothspace( sRcvAct );
  strcpy( sBokAct, sRcvAct );

  ClearStr( sBgnLoc );
  ClearStr( sCenLen );
  if( strlen( sRcvAct ) > ActNoLen ) {
    bpAddResult( TrNode, "CBS999", "非交行帐号" );
    bpErrorLog(trdata, "CbsGetAccFlg：帐号【%s】非交行帐号", sRcvAct);
    bpTraceLog( trdata, "End CbsGetAccFlg.\n" );
    return -1;
  }
/*
**  判断是否为老存折（暂未考虑辖属行）
*/
  if( memcmp(sRcvAct,"071",3)==0 ) {
    EXEC SQL select ActNo
               into :sBokAct
               from SavOldAct
              where OldAct =:sRcvAct;
    if( SQLCODE == SQL_SUCCESS ) {
      strcpy( sLAccFlg, "1" );
      strcpy( sLActFg, "2" );
      bpErrorLog(trdata, "CbsGetAccFlg：转换帐号【%s】＝＞【%s】", sRcvAct, sBokAct);
      etfAddOrRepNode( TrNode, "LAccFlg", sLAccFlg, AccFlgLen );
      etfAddOrRepNode( TrNode, "LActFg", sLActFg, ActFlgLen );
      etfAddOrRepNode( TrNode, "BokAct", sBokAct, RcvActLen );
      return 0;
    }
  }
/*
**  判断是否为卡业务
*/
  EXEC SQL select BgnLoc, CenLen
             into :sBgnLoc, :sCenLen
             from StpBinInf
            where CrdBin = substr( :sBokAct, 1, 6 );
  if( SQLCODE == SQL_SUCCESS ) {
    strcpy( sLAccFlg, "2" );
    strcpy( sLActFg, "4" );
  }  else {
    if( ( strlen(sBokAct)==ActNoLen ) && ( memcmp(sBokAct+AreaCdLen,"9",1)==0 ) ) {
      memcpy( sVchTyp, sBokAct+ActNoLen-VchTypLen, VchTypLen );
      switch( atoi(sVchTyp) ) {
        case 209:   /* 卡备用金帐号 */
        case 229:   /* 卡备用金帐号 */
          strcpy( sLAccFlg, "2" );
          strcpy( sLActFg, "4" );
          break;
        case 998:   /* 一本通 */
          strcpy( sLAccFlg, "1" );
          strcpy( sLActFg, "1" );
          break;
        case 202:   /* 存折 */
          strcpy( sLAccFlg, "1" );
          strcpy( sLActFg, "2" );
          break;
        default:
          strcpy( sLAccFlg, "0" );
          strcpy( sLActFg, "0" );
          break;        
      }
    }  else {
      strcpy( sLAccFlg, "0" );
      strcpy( sLActFg, "0" );
    }
  }
  
  etfAddOrRepNode( TrNode, "LAccFlg", sLAccFlg, AccFlgLen );
  etfAddOrRepNode( TrNode, "LActFg", sLActFg, ActFlgLen );
  etfAddOrRepNode( TrNode, "BokAct", sBokAct, RcvActLen );

  bpAddResult( TrNode, "000000", "交易成功" );
  bpErrorLog(trdata, "CbsGetAccFlg：帐号【%s】帐户性质【%s】【%s】对应新帐号【%s】", sRcvAct,sLAccFlg,sLActFg,sBokAct);
  bpTraceLog( trdata, "End CbsGetAccFlg.\n" );
  return(0);
}
/******************************************************************************
  Function          : CbsUpdBal
  Description       : 判断并修改分行头寸
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : 无
  Table Updated      : 无
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败  1--头寸不足
  Others            : 其它说明             
******************************************************************************/
int CbsUpdBal(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sBrNo[BrNoLen+1];
    char   sUpdDir[UpdDirLen+1];
    char   sTxnAmt[TxnAmtLen+1];
    char   sTxnMod[TxnModLen+1];
    char   sCurAmt[TxnAmtLen+1];
  EXEC SQL END DECLARE SECTION;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin CbsUpdBal.\n" );
/*
**  检查输入参数个数
*/
  if( Step_Args_Num != 4 ) {
    bpAddResult( TrNode, "CBS999", "参数个数错" );
    bpErrorLog( trdata, "CbsUpdBal: 参数个数错!" );
    return( -1 );
  }
/*
**  获取接收人帐号（暂未考虑辖属行）
*/
  ClearStr( sBrNo );
  ClearStr( sUpdDir );
  ClearStr( sTxnAmt );
  ClearStr( sTxnMod );
  strcpy( sBrNo, Step_Arg1 );
  strcpy( sUpdDir, Step_Arg2 );
  strcpy( sTxnAmt, Step_Arg3 );
  strcpy( sTxnMod, Step_Arg4 );
/*
**  通过加锁实现并发
*/
  EXEC SQL update CbsBnkInf
              set CurAmt=CurAmt
            where BrNo = :sBrNo;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult( TrNode, "CBS999", "表【CbsBnkInf】加锁错" );
    bpErrorLog( trdata, "CbsUpdBal: 表【CbsBnkInf】加锁错!" );
    return -1;
  }
  ClearStr( sCurAmt );
  EXEC SQL select CurAmt
             into :sCurAmt
             from CbsBnkInf
            where BrNo = :sBrNo;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult( TrNode, "CBS999", "查询表【CbsBnkInf】当前余额错" );
    bpErrorLog( trdata, "CbsUpdBal: 查询表【CbsBnkInf】当前余额错!" );
    return -1;
  }
  if( strcmp( sTxnMod, "0" )==0 ) {  /* 头寸查询 */
    if( atoi(sCurAmt)<atoi(sTxnAmt) ) {
      bpAddResult( TrNode, "000000", "头寸不足" );
      bpErrorLog( trdata, "CbsUpdBal: 头寸不足!" );
      return 1;
    } else {
      bpAddResult( TrNode, "000000", "头寸充足" );
      bpErrorLog( trdata, "CbsUpdBal: 头寸充足!" );
      return 0;
    }
  } else { /* 头寸变更 */
    if( strcmp( sUpdDir, "0" )==0 ) {  /* 头寸增加 */
      EXEC SQL update CbsBnkInf
                  set CurAmt = substr( right( ( '000000000000000'||rtrim(char( int( CurAmt ) + int( :sTxnAmt ) ) ) ),15 ), 1, 15 )
                where BrNo = :sBrNo;
    } else { /* 头寸减少 */
      if( atoi(sCurAmt)<atoi(sTxnAmt) ) {
        ClearStr( sTxnAmt );
        strcpy( sTxnAmt, sCurAmt );
      }
      EXEC SQL update CbsBnkInf
                  set CurAmt = substr( right( ( '000000000000000'||rtrim(char( int( CurAmt ) - int( :sTxnAmt ) ) ) ),15 ), 1, 15 )
                where BrNo = :sBrNo;
    }
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult( TrNode, "CBS999", "更新表【CbsBnkInf】当前余额错" );
      bpErrorLog( trdata, "CbsUpdBal: 更新表【CbsBnkInf】当前余额错!" );
      bpTraceLog( trdata, "End CbsUpdBal.\n" );
      return -1;
    }
  }
  bpAddResult( TrNode, "000000", "头寸查询（更新）成功" );
  bpErrorLog( trdata, "CbsUpdBal: 头寸查询（更新）成功!" );
  bpTraceLog( trdata, "End CbsUpdBal.\n" );
  return(0);
}
/******************************************************************************
  Function          : CbsGetNodInfo
  Description       : 根据支付行号得到分行号，帐务中心网点号， 营业部网点号
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int CbsGetNodInfo(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sBrNo[BrNoLen+1];
    char   sCtlNod[CtlNodLen+1];
    char   sBusNod[BusCodLen+1];
    char   sPBnkNo[PBnkNoLen+1];
    char   sCnlSub[CnlSubLen+1];
  EXEC SQL END DECLARE SECTION;
/*  设置跟踪信息 */
  bpTraceLog( trdata, "Begin CbsGetNodInfo.\n" );
/*检查输入参数个数*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "参数个数错" );
    bpErrorLog( trdata, "CbsGetNodInfo: 参数个数错!" );
    return( -1 );
  }
  ClearStr( sPBnkNo );
  ClearStr( sBrNo );
  ClearStr( sCtlNod );
  ClearStr( sBusNod );
  ClearStr( sCnlSub );
  strcpy( sPBnkNo, Step_Arg1 );
  EXEC SQL SELECT  distinct BrNo 
               INTO  :sBrNo
               FROM  pubnodinf
              WHERE  SBkNo=:sPBnkNo;
  if( SQLCODE )  {
    bpAddResult(TrNode, "CBS999", "查询表【PubNodInf】错" );
    bpErrorLog(trdata, "CbsGetNodInfo:查询表【PubNodInf】错【%d】", SQLCODE);
    return( -1 );
  }
  EXEC SQL SELECT  CtlNod,BusNod,CnlSub
               INTO  :sCtlNod,:sBusNod,:sCnlSub
               FROM  cbsbnkinf
              WHERE  BrNo=:sBrNo;
  if( SQLCODE )  {
    bpAddResult(TrNode, "CBS999", "查询表【CbsBnkInf】错" );
    bpErrorLog(trdata, "CbsGetNodInfo查询表【CbsBnkInf】错【%d】", SQLCODE);
    return( -1 );
  }
  bpErrorLog(trdata, "【%s】【%s】【%s】【%s】", sBrNo,sCtlNod,sBusNod,sCnlSub);
  sCnlSub[6]='\0';
  etfAddOrRepNode(TrNode,"BrNo", sBrNo, strlen(sBrNo));
  etfAddOrRepNode(TrNode,"CtlNod", sCtlNod, strlen(sCtlNod));
  etfAddOrRepNode(TrNode,"BusNod", sBusNod, strlen(sBusNod));
  etfAddOrRepNode(TrNode,"CnlSub", sCnlSub, strlen(sCnlSub));

  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End CbsGetNodInfo.\n" );
  return(0);
}
/******************************************************************************
  Function          : CbsFLstToDb
  Description       : 将人行8583数据文件列表插入数据库并产生回应文件
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int CbsFLstToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sMsgTyp[MsgTypLen+1];
    char   sRspCod[RspCodLen+1];
    char   sRspMsg[RspMsgLen+1];
    char   sOIFlag[OIFlagLen+1];

    char   sMsgId[MsgIdLen+1];
    char   sTxnKnd[TxnKndLen+1];
    char   sSysId[SysIdLen+1];
    char   sWorkDt[WorkDtLen+1];
    char   sBchNo[BchNoLen+1];
    char   sFSize[FSizeLen+1];
    char   sClrDat[ClrDatLen+1];
    char   sClrSce[ClrSceLen+1];
    char   sSSysId[SSysIdLen+1];
    char   sSndBNo[SndBNoLen+1];
    char   sRSysId[RSysIdLen+1];
    char   sRcvBNo[RcvBNoLen+1];
    char   sTraKnd[TraKndLen+1];
    char   sFilNam[FilNamLen+1];
    char   sRefFil[RefFilLen+1];
    char   sBchSqn[BchSqnLen+1];
    char   sRefSqn[RefSqnLen+1];
    char   sCusSqn[CusSqnLen+1];
    char   sTotNum[TotNumLen+1];
    char   sTotAmt[TotAmtLen+1];
    char   sRefNum[RefNumLen+1];
    char   sRefAmt[RefAmtLen+1];
    char   sRtnCod[RtnCodLen+1];
    char   sReServ[ReServLen+1];
    char   sBchSts[BchStsLen+1];
    char   sFlag[2];
    char   sLogNo[LogNoLen+1];
    char   sRcvFilLst[FNameLen+1];
    char   sSrc8583Fil[FNameLen+1];
    char   sSrcFil[FNameLen+1];
    char   sSndFilLst[FNameLen+1];
    char   sDelFilLst[FNameLen+1];
    char   sDesFil[FNameLen+1];
    char   sDFil[FNameLen+1];
    char   sUpdFil[FNameLen+1];
    char   sNodNo[NodNoLen+1];
    char   sBrNo[BrNoLen+1];

    char   sOClrDat[ClrDatLen+1];
    char   sOClrSce[ClrSceLen+1];
  EXEC SQL END DECLARE SECTION;
    FILE   *rlst_fp, *rfp, *slst_fp, *sfp, *dlst_fp;
    int    iFSize, ret;
    char   sTmpFil[FilNamLen+1];
/*
**设置跟踪信息
*/
  ClearStr( sMsgTyp );
  ClearStr( sRspCod );
  ClearStr( sRspMsg );
  ClearStr( sOIFlag );
  strcpy( sOIFlag, "1" );
  bpTraceLog( trdata, "Begin CbsFLstToDb.\n" );
/*检查输入参数个数*/
  if( Step_Args_Num != 5 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "参数个数错" );
    bpErrorLog( trdata, "CbsFLstToDb: 参数个数错!" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "参数个数错" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  根据列表文件获取具体文件，并生成收妥回应列表文件和具体回应文件
*/
  ClearStr( sRcvFilLst );
  ClearStr( sSndFilLst );
  sprintf( sRcvFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg1 );
  sprintf( sSndFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg3 );
  sprintf( sDelFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg5 );
/*
**  回应文件列表
*/
  slst_fp =fopen( sSndFilLst, "w" );
  if( slst_fp == NULL ) {
    fclose( slst_fp );
    bpAddResult( TrNode, "CBS999", "打开发送列表文件错" );
    bpErrorLog( trdata, "CbsFLstToDb:打开发送列表文件【%s】失败!\n", sSndFilLst );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "打开发送列表文件【%s】错", Step_Arg3 );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  删除文件列表
*/
  dlst_fp =fopen( sDelFilLst, "w" );
  if( dlst_fp == NULL ) {
    fclose( slst_fp );
    fclose( dlst_fp );
    bpAddResult( TrNode, "CBS999", "打开删除列表文件错" );
    bpErrorLog( trdata, "CbsFLstToDb:打开删除列表文件【%s】失败!\n", sDelFilLst );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "打开删除列表文件【%s】错", Step_Arg3 );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  接收文件列表
*/
  rlst_fp =fopen( sRcvFilLst, "r" );
  if( rlst_fp == NULL ) {
    fclose( slst_fp );
    fclose( dlst_fp );
    fclose( rlst_fp );
    bpAddResult( TrNode, "CBS999", "打开接收列表文件错" );
    bpErrorLog( trdata, "CbsFLstToDb:打开接收列表文件【%s】失败!\n", sRcvFilLst );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "打开接收列表文件【%s】错", Step_Arg1 );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  while( !feof( rlst_fp ) ) {
    ClearStr( sTmpFil );
    ClearStr( sFilNam );
    ClearStr( sBrNo );
    ClearStr( sNodNo );
/*
**  此处用于删除列表文件中的回车换行符
*/
    fgets( sTmpFil, FNmLstLen, rlst_fp );
    strncpy( sFilNam, sTmpFil, FNmLstLen-2 );
    if( strlen(sFilNam)==0 ) {
      bpErrorLog( trdata, "CbsFLstToDb:本次文件列表处理完毕!\n" );
      fclose( rfp );
      break;
    }
    bpErrorLog( trdata, "CbsFLstToDb:正在处理文件【%s】!\n", sFilNam );
    ClearStr( sFlag );
    strcpy( sFlag, "N" );
    EXEC SQL select 'Y'
               into :sFlag
               from TABLE(VALUES(1)) AS anony
              where EXISTS ( select 'Y' from CbsBchSum where FilNam = :sFilNam );
/*
**  此处不处理是为了可以重复生成回应文件
*/
    ClearStr( sMsgId  );
    ClearStr( sTxnKnd );
    ClearStr( sSysId  );
    ClearStr( sWorkDt );
    ClearStr( sBchNo  );
    ClearStr( sFSize  );
    ClearStr( sSrc8583Fil );
    ClearStr( sSrcFil );
    memcpy( sMsgId,  sFilNam+MsgIdOffset,  MsgIdLen  );
    memcpy( sTxnKnd, sFilNam+TxnKndOffset, TxnKndLen );
    memcpy( sSysId,  sFilNam+SysIdOffset,  SysIdLen  );
    memcpy( sWorkDt, sFilNam+WorkDtOffset, WorkDtLen );
    memcpy( sBchNo,  sFilNam+BchNoOffset,  BchNoLen  );
    memcpy( sFSize,  sFilNam+FSizeOffset,  FSizeLen  );
    sprintf( sSrc8583Fil, "%s/%s/%s", getenv("WORKDIR"), Step_Arg2, sFilNam );
    sprintf( sSrcFil, "%s/%s/%s%s", getenv("WORKDIR"), Step_Arg2, sFilNam, ".dat" );
/*
**  判断文件的完整性
*/
    rfp =fopen( sSrc8583Fil, "r" );
    if( rfp == NULL ) {
      bpAddResult( TrNode, "CBS999", "打开数据文件错" );
      bpErrorLog( trdata, "CbsFLstToDb:打开数据文件【%s】失败!\n", sSrc8583Fil );
      fclose( rfp );
      continue;
    }
    iFSize=0;
    iFSize=hfgetsize( rfp );
    if( iFSize != atol( sFSize ) ) {
      bpErrorLog( trdata, "CbsFLstToDb:数据文件【%s】不完整!\n", sSrc8583Fil );
      fclose( rfp );
      continue;
    }
    fclose( rfp );
/*
**  将数据文件8583转换为普通文件
*/
    ret=CbsFilChg( "2", sSrc8583Fil, sSrcFil );
    if( ret!=0 ) {
      bpErrorLog( trdata, "CbsFLstToDb:数据文件【%s】转换异常!\n", sSrc8583Fil );
      continue;
    }
/*
** 处理数据文件的第一行并登记或修改汇总表
*/
    rfp =fopen( sSrcFil, "r" );
    if( rfp == NULL ) {
      bpAddResult( TrNode, "CBS999", "打开数据文件错" );
      bpErrorLog( trdata, "CbsFLstToDb:打开数据文件【%s】失败!\n", sSrcFil );
      fclose( rfp );
      continue;
    }
    ClearStr( sClrDat );
    ClearStr( sClrSce );
    ClearStr( sSSysId );
    ClearStr( sSndBNo );
    ClearStr( sRSysId );
    ClearStr( sRcvBNo );
    ClearStr( sTraKnd );
    ClearStr( sFilNam );
    ClearStr( sRefFil );
    ClearStr( sBchSqn );
    ClearStr( sRefSqn );
    ClearStr( sCusSqn );
    ClearStr( sTotNum );
    ClearStr( sTotAmt );
    ClearStr( sRefNum );
    ClearStr( sRefAmt );
    ClearStr( sRtnCod );
    ClearStr( sReServ );
    ClearStr( sBchSts );
    fscanf( rfp, "%[^|]",  sClrDat ); /* 清算日期 */
    fscanf( rfp, "|%[^|]", sClrSce ); /* 清算场次 */
    fscanf( rfp, "|%[^|]", sSSysId ); /* 发起方系统号 */
    fscanf( rfp, "|%[^|]", sSndBNo ); /* 发起方代码 */
    fscanf( rfp, "|%[^|]", sRSysId ); /* 接收方系统号 */
    fscanf( rfp, "|%[^|]", sRcvBNo ); /* 接收方代码 */
    fscanf( rfp, "|%[^|]", sTraKnd ); /* 交易种类 */
    fscanf( rfp, "|%[^|]", sFilNam ); /* 文件名 */
    fscanf( rfp, "|%[^|]", sRefFil ); /* 参照文件名 */
    fscanf( rfp, "|%[^|]", sBchSqn ); /* 批量包序号 */
    fscanf( rfp, "|%[^|]", sRefSqn ); /* 参考批量包序号 */
    fscanf( rfp, "|%[^|]", sCusSqn ); /* 客户批量包序号 */
    fscanf( rfp, "|%[^|]", sTotNum ); /* 交易总笔数 */
    fscanf( rfp, "|%[^|]", sTotAmt ); /* 交易总金额 */
    fscanf( rfp, "|%[^|]", sRefNum ); /* 拒绝支付总笔数 */
    fscanf( rfp, "|%[^|]", sRefAmt ); /* 拒绝支付总金额 */
    fscanf( rfp, "|%[^|]", sRtnCod ); /* 返回码 */
    fscanf( rfp, "|%[^|\n]",sReServ );/* 预留位 */
    strcpy( sBchSts, "U" );
/*
**  判断文件类型是2202（转发缴费申请）还是2220（返回ACK回应）
*/
    switch( atoi(sMsgId) ) {
      case 2220:   /* 定期借记来帐的返回ACK回应 */
        if( ( strcmp( sRtnCod, "000I1000" )==0 ) || ( strcmp( sRtnCod, "000O7008" )==0 ) ) { /*中心成功接收业务回应文件*/
          EXEC SQL update CbsBchSum Set BchSts='D', ClrDat=:sClrDat, ClrSce=:sClrSce, AckFil2=:sFilNam where ClrFil=substr(:sRefFil,1,36) and OIFlag='1';
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:处理ACK2220回应文件【%s】【%s】更新汇总表【CbsBchSum】失败!\n", sSrc8583Fil, sRefFil );
          }
          EXEC SQL update CbsBchJnl Set ClrDat=:sClrDat  where filnam=( select FilNam from CbsBchSum where ClrFil=substr(:sRefFil,1,36) and OIFlag='1');
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:处理ACK2220回应文件【%s】【%s】更新明细表【CbsBchJnl】失败!\n", sSrc8583Fil, sRefFil );
          }
        } else {
          bpErrorLog( trdata, "CbsFLstToDb:处理ACK2220回应文件【%s】失败，原回应文件【%s】!\n", sSrc8583Fil, sRefFil );
        }
        /*ACK回应文件2220说明原业务回应2212有错，通过其他程序重新生城回应，此处不作任何处理*/
        fprintf( dlst_fp, "%s\n", sFilNam );
        break;
      case 2202:   /* 转发定期借记缴费申请2202、批量贷记 */
/*
**  源文件2202数据入库
*/
        if( strcmp( sFlag, "Y" ) != 0 ) {
          EXEC SQL select BrNo, substr(BrNo,1,3)||'800' 
                     into :sBrNo, :sNodNo
                     from pubnodinf
                    where SBkNo=:sRcvBNo fetch first 1 rows only;
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:获取接收行【%s】分行号出错，文件名:【%s】!\n", sRcvBNo, sSrc8583Fil );
            bpAddResult( TrNode, _DB_OPER_ERR, "获取接收行分行号错误" );
            strcpy( sMsgTyp, "E" );
            strcpy( sRspCod, "CBS999" );
            strcpy( sRspMsg, "获取接收行分行号错误" );
            etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
            etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
            etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
            fclose( rfp );
            continue;
          }
          EXEC SQL insert into CbsBchSum( BchSts,ClrDat,ClrSce,SSysId,SndBNo,RSysId,RcvBNo,TraKnd,OIFlag,FilNam,RefFil,BchSqn,RefSqn,CusSqn,TotNum,TotAmt,RefNum,RefAmt,RtnCod,ReServ,NodNo, BrNo )
                                    values( :sBchSts,:sClrDat,:sClrSce,:sSSysId,:sSndBNo,:sRSysId,:sRcvBNo,:sTraKnd,:sOIFlag,:sFilNam,:sRefFil,:sBchSqn,:sRefSqn,:sCusSqn,:sTotNum,:sTotAmt,:sRefNum,:sRefAmt,:sRtnCod,:sReServ,:sNodNo,:sBrNo );
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:insert【CbsBchSum】出错-文件名:【%s】!\n", sSrc8583Fil );
            bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsBchSum】出错" );
            strcpy( sMsgTyp, "E" );
            strcpy( sRspCod, "CBS999" );
            strcpy( sRspMsg, "登记文件名出错" );
            etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
            etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
            etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
            fclose( rfp );
            continue;
          }
        }  else {
          bpErrorLog( trdata, "CbsFLstToDb:数据文件【%s】重复处理!\n", sSrc8583Fil );
        }
        fclose( rfp );
/*
**  生成收妥回应文件
*/
        switch( atoi( sTxnKnd ) ) {
          case 105101:   /* 批量贷记 */
          case 105102:   /* 定期贷记 */
            strcpy( sMsgId, "2222" );
            break;
          case 105201:   /* 定期借记 */
            strcpy( sMsgId, "2242" );
            break;
          default:
            bpErrorLog( trdata, "CbsFileToDb:无法处理【%s】报文类型!\n", sTxnKnd );
            bpAddResult( TrNode, "CBS999", "无法处理该报文类型" );
            strcpy( sMsgTyp, "E" );
            strcpy( sRspCod, "CBS999" );
            strcpy( sRspMsg, "无法处理该报文类型" );
            etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
            etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
            etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
            fclose( slst_fp );
            fclose( dlst_fp );
            fclose( rlst_fp );
            return( -1 );
        } /* end of switch( atoi( sTxnKnd ) ) */
/*
**  利用前置流水号部分作为回应文件的批次号
*/
        ClearStr( sLogNo );
        if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
          bpErrorLog( trdata, "CbsFileToDb:取前置流水号错，文件名【%s】!\n", sSrcFil );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          sprintf( sRspMsg, "取前置流水号错，文件名【%s】!\n", sSrcFil );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          fclose( slst_fp );
          fclose( rlst_fp );
          fclose( rfp );
          return( -1 );
        }
        ClearStr( sDesFil );
        ClearStr( sDFil );
        ClearStr( sBchNo );
        strncpy( sBchNo, sLogNo+6, 8 );
        sprintf( sDesFil, "%s%s%s%s%s%s%s", FILMARK, sMsgId, sTxnKnd, SYSID, sWorkDt, sBchNo, RSPFILLEN );
        sprintf( sDFil, "%s/%s/%s", getenv("WORKDIR"), Step_Arg4, sDesFil );
        sfp=fopen( sDFil, "w" );
        if( sfp == NULL ) {
          bpAddResult( TrNode, "CBS999", "打开回应文件错" );
          bpErrorLog( trdata, "CbsFLstToDb:打开回应文件【%s】失败!\n", sDFil );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          sprintf( sRspMsg, "打开回应文件【%s】错", sDFil );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          fclose( slst_fp );
          fclose( dlst_fp );
          fclose( rlst_fp );
          fclose( rfp );
          fclose( sfp );
          return( -1 );
        }
/*
**  公共数据部分
*/
        ClearStr( sClrDat );
        ClearStr( sClrSce );
        ClearStr( sRefFil );
        ClearStr( sRefSqn );
        ClearStr( sCusSqn );
        ClearStr( sTotNum );
        ClearStr( sTotAmt );
        ClearStr( sRefNum );
        ClearStr( sRefAmt );
        ClearStr( sRtnCod );
        strcpy( sClrDat, "00000000" );
        strcpy( sClrSce, "0" );
        strcpy( sRefFil, sFilNam );
        strcpy( sFilNam, sDesFil );
        strcpy( sRefSqn, sBchSqn );
        strcpy( sBchSqn, sBchNo );
        strcpy( sCusSqn, "00000000" );
        strcpy( sTotNum, "0000000000" );
        strcpy( sTotAmt, "0000000000000000" );
        strcpy( sRefNum, "0000000000" );
        strcpy( sRefAmt, "0000000000000000" );
        strcpy( sRtnCod, "000I1000" );
        strcpy( sReServ, "                " );
        fprintf( sfp, "%3s%8s%s%4s%12s%4s%12s%4s%-60s%-60s%8s%8s%8s%010s%016s%010s%016s%8s%16s%s%s%-64s%s", "{3:",sClrDat,sClrSce,sSSysId,sSndBNo,sRSysId,sRcvBNo,sTraKnd,sDesFil,sRefFil,sBchSqn,sRefSqn,sCusSqn,sTotNum,sTotAmt,sRefNum,sRefAmt,sRtnCod,sReServ,"}", "{5:", " ", "}" );
        fclose( sfp );
/*
**  登记回应文件列表，并修改数据库中收妥回应文件名
*/
        fprintf( slst_fp, "%s\n", sDesFil );
        fprintf( dlst_fp, "%s\n", sRefFil );
        EXEC SQL update CbsBchSum set AckFil1=:sDesFil where FilNam=:sRefFil and OIFlag='1' and BchSts='U';
        if( SQLCODE != SQL_SUCCESS ) {
          bpErrorLog( trdata, "CbsFLstToDb:修改【CbsBchSum】出错-文件名:【%d】【%s】【%s】!\n", SQLCODE, sRefFil, sDesFil );
          continue;
        }
        break;
      case 2210:  /*定期贷记往帐的清算通知、定期借记往帐的ACK回应*/
/*
**  修改批量表的状态为：C－已回应，待明细处理结束后修改为D－已清算
**  将8583文件转换为普通格式，提供给明细表使用
**  返回收妥回应
*/
        ClearStr( sUpdFil );
        ClearStr( sOClrDat );
        ClearStr( sOClrSce );
        strcpy( sUpdFil, sRefFil );
        strcpy( sOClrDat, sClrDat );
        strcpy( sOClrSce, sClrSce );
        if( ( strcmp( sRtnCod, "000I1000" )==0 ) || ( strcmp( sRtnCod, "" )==0 ) ) { /*中心成功接收清算通知文件*/
          if( ( strcmp( sTxnKnd,"105101" )==0 ) || ( strcmp( sTxnKnd,"105102" )==0 ) ) {   /*定期贷记*/
            strcpy( sMsgId, "2212" );
/*
**  利用前置流水号部分作为回应文件的批次号
*/
            ClearStr( sLogNo );
            if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
              bpErrorLog( trdata, "CbsFileToDb:取前置流水号错，文件名【%s】!\n", sSrcFil );
              strcpy( sMsgTyp, "E" );
              strcpy( sRspCod, "CBS999" );
              sprintf( sRspMsg, "取前置流水号错，文件名【%s】!\n", sSrcFil );
              etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
              etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
              etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
              fclose( slst_fp );
              fclose( rlst_fp );
              fclose( rfp );
              return( -1 );
            }
            ClearStr( sDesFil );
            ClearStr( sDFil );
            ClearStr( sBchNo );
            strncpy( sBchNo, sLogNo+6, 8 );
            sprintf( sDesFil, "%s%s%s%s%s%s%s", FILMARK, sMsgId, sTxnKnd, SYSID, sWorkDt, sBchNo, RSPFILLEN );
            sprintf( sDFil, "%s/%s/%s", getenv("WORKDIR"), Step_Arg4, sDesFil );
            sfp=fopen( sDFil, "w" );
            if( sfp == NULL ) {
              bpAddResult( TrNode, "CBS999", "打开回应文件错" );
              bpErrorLog( trdata, "CbsFLstToDb:打开回应文件【%s】失败!\n", sDFil );
              strcpy( sMsgTyp, "E" );
              strcpy( sRspCod, "CBS999" );
              sprintf( sRspMsg, "打开回应文件【%s】错", sDFil );
              etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
              etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
              etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
              fclose( slst_fp );
              fclose( dlst_fp );
              fclose( rlst_fp );
              fclose( rfp );
              fclose( sfp );
              return( -1 );
            }
/*
**  公共数据部分
*/
            ClearStr( sClrDat );
            ClearStr( sClrSce );
            ClearStr( sRefFil );
            ClearStr( sRefSqn );
            ClearStr( sCusSqn );
            ClearStr( sTotNum );
            ClearStr( sTotAmt );
            ClearStr( sRefNum );
            ClearStr( sRefAmt );
            ClearStr( sRtnCod );
            strcpy( sClrDat, "00000000" );
            strcpy( sClrSce, "0" );
            strcpy( sRefFil, sFilNam );
            strcpy( sFilNam, sDesFil );
            strcpy( sRefSqn, sBchSqn );
            strcpy( sBchSqn, sBchNo );
            strcpy( sCusSqn, "00000000" );
            strcpy( sTotNum, "0000000000" );
            strcpy( sTotAmt, "0000000000000000" );
            strcpy( sRefNum, "0000000000" );
            strcpy( sRefAmt, "0000000000000000" );
            strcpy( sRtnCod, "000I1000" );
            strcpy( sReServ, "                " );
            fprintf( sfp, "%3s%8s%s%4s%12s%4s%12s%4s%-60s%-60s%8s%8s%8s%010s%016s%010s%016s%8s%16s%s%s%-64s%s", "{3:",sClrDat,sClrSce,sSSysId,sSndBNo,sRSysId,sRcvBNo,sTraKnd,sDesFil,sRefFil,sBchSqn,sRefSqn,sCusSqn,sTotNum,sTotAmt,sRefNum,sRefAmt,sRtnCod,sReServ,"}", "{5:", " ", "}" );
            fclose( sfp );
/*
**  登记回应文件列表，并修改数据库中收妥回应文件名
**  原接收文件名变为参照文件名( sFilNam->sRefFil )，所以删除列表变为sRefFil
*/
            fprintf( slst_fp, "%s\n", sDesFil );
            fprintf( dlst_fp, "%s\n", sRefFil );
          }  else {   /*定期借记*/
            ClearStr( sDesFil );
          }
          EXEC SQL update CbsBchSum Set BchSts='R', ClrDat=:sOClrDat, ClrSce=:sOClrSce, ClrFil=:sRefFil, AckFil1=:sDesFil where FilNam=:sUpdFil and OIFlag='0' and BchSts='C';
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:修改【CbsBchSum】出错-文件名:【%d】【%s】【%s】【%s】!\n", SQLCODE, sRefFil, sDesFil, sUpdFil );
            bpErrorLog( trdata, "CbsFLstToDb:处理定期贷记清算文件【%s】【%s】失败!\n", sSrc8583Fil, sRefFil );
          }
        } else {
          bpErrorLog( trdata, "CbsFLstToDb:处理ACK2220文件【%s】失败，原发送文件【%s】,返回码【%s】!\n", sSrc8583Fil, sRefFil, sRtnCod );
        }
        break;
    } /* End of Switch(sMsgId) */
  } /* End of while( !feof( rlst_fp ) ) */
  fclose( slst_fp );
  fclose( dlst_fp );
  fclose( rlst_fp );
  strcpy( sMsgTyp, "N" );
  strcpy( sRspCod, "000000" );
  strcpy( sRspMsg, "交易成功" );
  etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
  etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
  etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
  bpTraceLog( trdata, "End CbsFLstToDb.\n" );
  return(0);
}
/******************************************************************************
  Function          : CbsFDtlToDb
  Description       : 将人行8583数据文件转换为普通文件并数据插入数据库
  Input             : ETF *TrNode  输入树
                      ST_TranData* trdata  公共结构
                      char* args  参数
                      DBConHandle* DBHandle  数据库句柄
  Output            : 对输出参数的说明。
  Return            : 0--成功 小于0--失败
  Others            : 其它说明
******************************************************************************/
int CbsFDtlToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*入口参数*/
    char   sDskNo[DskNoLen+1];
    char   sFilPth[FilPthLen+1];
    char   sDtlFil[FNameLen+1];
/*大小通道及其他*/
    char   sActFlg[ActFlgLen+1];
    char   sBchSts[BchStsLen+1];
    char   sOIFlag[OIFlagLen+1];
    char   sBilSts[BilStsLen+1];
    char   sAccKnd[AccKndLen+1];
    char   sBrNo[BrNoLen+1];
    char   sNodNo[NodNoLen+1];
    char   sLogNo[LogNoLen+1];
    char   sActDat[ActDatLen+1];
    char   sTTxnCd[TTxnCdLen+1];
    char   sHTxnCd[HTxnCdLen+1];
    char   sIsTxn[IsTxnLen+1];
    char   sTxnCnl[TxnCnlLen+1];
    char   sCnlSub[CnlSubLen+1];
    char   sTxnObj[TxnObjLen+1];
    char   sTlrId[TlrIdLen+1];
    char   sHTxnSt[HTxnStLen+1];
/*批量应用报文头*/
    char   sClrDat[ClrDatLen+1]; /*清算日期*/
    char   sClrSce[ClrSceLen+1]; /*清算场次*/
    char   sSSysId[SSysIdLen+1]; /*发起方系统号*/
    char   sSndBNo[SndBNoLen+1]; /*发起方代码*/
    char   sRSysId[RSysIdLen+1]; /*接收方系统号*/
    char   sRcvBNo[RcvBNoLen+1]; /*接收方代码*/
    char   sTraKnd[TraKndLen+1]; /*交易种类*/
    char   sFilNam[FilNamLen+1]; /*文件名*/
    char   sRefFil[RefFilLen+1]; /*参照文件名*/
    char   sBchSqn[BchSqnLen+1]; /*批量包序号*/
    char   sRefSqn[RefSqnLen+1]; /*参考批量包序号*/
    char   sCusSqn[CusSqnLen+1]; /*客户批量包序号*/
    char   sTotNum[TotNumLen+1]; /*交易总笔数*/
    char   sTotAmt[TotAmtLen+1]; /*交易总金额*/
    char   sRefNum[RefNumLen+1]; /*拒绝支付总笔数*/
    char   sRefAmt[RefAmtLen+1]; /*拒绝支付总金额*/
    char   sRtnCod[RtnCodLen+1]; /*返回码*/
    char   sReServ[ReServLen+1]; /*预留位*/
/*批量记录应用报文头*/
    char   sMsgSqn[MsgSqnLen+1]; /*信息序号*/
    char   sRefMsg[MsgSqnLen+1]; /*参考信息序号*/
/*批量记录正文体*/
    char   sMsgId[MsgIdLen+1];     /*报文类型标识符*/
    char   sTxnKnd[TxnKndLen+1];   /*交易种类细分*/
    char   sTxnAmt[TxnAmtLen+1];   /*交易金额*/
    char   sTraTm[TraTmLen+1];     /*交易发起日期和时间*/
    char   sClrBNo[ClrBNoLen+1];   /*直接清算行*/
    char   sSndDat[SndDatLen+1];   /*委托日期*/
/*报文头已定义
    char   sClrDat[ClrDatLen+1];   *清算日期*
*/
    char   sCcyCod[CcyCodLen+1];   /*交易货币种类*/
    char   sQryTyp[QryTypLen+1];   /*查询通知种类*/
    char   sAreaNo[AreaNoLen+1];   /*地区号*/
    char   sSvrCod[SvrCodLen+1];   /*服务点输入方式码*/
    char   sCenId[CenIdLen+1];     /*中心客户号*/
    char   sCusId[CusIdLen+1];     /*企业客户号*/
    char   sCenTm[CenTmLen+1];     /*中心受理日期时间*/
    char   sCenLog[CenLogLen+1];   /*中心受理号*/
    char   sThdTm[ThdTmLen+1];     /*业务处理方处理日期时间*/
    char   sThdLog[ThdLogLen+1];   /*业务受理方流水号*/
/*报文头已定义
    char   sRtnCod[RtnCodLen+1];   *返回码*
*/
    char   sCshFlg[CshFlgLen+1];   /*现金转帐标志*/
    char   sSmrCod[SmrCodLen+1];   /*摘要代码*/
    char   sUsgCod[UsgCodLen+1];   /*资金用途代码*/
    char   sRSdFlg[RSdFlgLen+1];   /*重发标识*/
    char   sAccFlg[AccFlgLen+1];   /*对公对私标识*/
    char   sTBusTp[TBusTpLen+1];   /*业务种类*/
    char   sCardFg[CardFgLen+1];   /*卡折标识*/
    char   sBillFg[BillFgLen+1];   /*钞户汇户标识*/
    char   sFeeTyp[FeeTypLen+1];   /*收费方式*/
    char   sPayFuc[PayFucLen+1];   /*支付工具*/
    char   sAuthCd[AuthCdLen+1];   /*授权码*/
    char   sPayLvl[PayLvlLen+1];   /*支付优先级*/
    char   sOrgId[OrgIdLen+1];     /*原数据元*/
/*报文头已定义
    char   sSndBNo[SndBNoLen+1];   *发起行行号*
*/
    char   sSOpnBk[SOpnBkLen+1];   /*发起人开户行行号*/
    char   sSndNod[SndNodLen+1];   /*发起行网点号*/
    char   sSndAct[SndActLen+1];   /*发起人账号*/
    char   sSndNm[SndNmLen+1];     /*发起人名称*/
    char   sVchId[VchIdLen+1];     /*凭证提交号*/
/*报文头已经定义
    char   sRcvBNo[RcvBNoLen+1];   *接收行行号*
*/
    char   sROpnBk[ROpnBkLen+1];   /*接收人开户行行号*/
    char   sRcvNod[RcvNodLen+1];   /*接收行网点号*/
    char   sRcvAct[RcvActLen+1];   /*接收人账号*/
    char   sRcvNm[RcvNmLen+1];     /*接收人名称*/
    char   sAgrNo[AgrNoLen+1];     /*协议号*/
    char   sSysSts[SysStsLen+1];   /*系统运行状态*/
    char   sCreAmt[CreAmtLen+1];   /*贷方金额*/
    char   sCreCnt[CreCntLen+1];   /*贷方笔数*/
    char   sDebAmt[DebAmtLen+1];   /*借方金额*/
    char   sDebCnt[DebCntLen+1];   /*借方笔数*/
    char   sCTraKnd[CTraKndLen+1]; /*交易种类*/
    char   sOSgnId[OSgnIdLen+1];   /*旧登陆标识*/
    char   sNSgnId[NSgnIdLen+1];   /*新登陆标识*/
    char   sSmr[SmrLen+1];         /*交易摘要*/
    char   sSecKey[SecKeyLen+1];   /*密押*/
    char   sTCrpCd[TCrpCdLen+1];   /*企业机构代码*/
    char   sSvrKnd[SvrKndLen+1];   /*服务信息类型*/
    char   sTBilNo[TBilNoLen+1];   /*税票号码*/
    char   sTaxNo[TaxNoLen+1];     /*纳税人编码*/
    char   sTaxer[TaxerLen+1];     /*纳税人名称*/
    char   sTaxLvl[TaxLvlLen+1];   /*预算级次*/
    char   sTSubCd[TSubCdLen+1];   /*预算科目*/
    char   sTOrgCd[TOrgCdLen+1];   /*征收机关代码*/
    char   sTActDt[TActDtLen+1];   /*税票限缴日期*/
    char   sSvrMsg[SvrMsgLen+1];   /*服务信息内容*/
    char   sSndNm2[SndNm2Len+1];   /*附加发起人名称*/
    char   sSndAdr[SndAdrLen+1];   /*发起人地址*/
    char   sRcvNm2[RcvNm2Len+1];   /*附加接收人名称*/
    char   sRcvAdr[RcvAdrLen+1];   /*接收人地址*/
/*程序变量*/
    char   sAgrKnd[AgrKndLen+1];   /*协议类型*/
    char   sBokAct[ActNoLen+1];    /*协议客户帐号，用于将对公帐户由18位转21位*/
    char   sOrnCnt[OrnCntLen+1];
    char   sCtlNod[CtlNodLen+1];
/*
**帐户性质使用
*/
    char   sBgnLoc[BgnLocLen+1];
    char   sCenLen[CenLenLen+1];
  EXEC SQL END DECLARE SECTION;
    char   sSrcFil[FilNamLen];
    char   sDesFil[FilNamLen];
    char   sTmpDat[15];
    FILE   *fp;
    int    i=0,iOrnCnt=0;

/*  设置跟踪信息 */
  bpTraceLog( trdata, "Begin CbsFDtlToDb.\n" );
/*检查输入参数个数*/
  if( Step_Args_Num != 0 ) {
    bpAddResult( TrNode, "CBS999", "参数个数错" );
    bpErrorLog( trdata, "CbsFDtlToDb: 参数个数错!" );
    return( -1 );
  }
  ClearStr( sDtlFil );
  ClearStr( sFilNam );
  ClearStr( sTraKnd );
  ClearStr( sOIFlag );
  ClearStr( sDskNo  );
  ClearStr( sActDat );
  ClearStr( sTTxnCd );
  ClearStr( sHTxnCd );
  ClearStr( sHTxnSt );
  ClearStr( sIsTxn  );
  ClearStr( sTxnObj );
  ClearStr( sTxnCnl );
  if ( etfGetChildValue(TrNode, "FilNam", sFilNam, FilNamLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【FilNam】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【FilNam】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TraKnd", sTraKnd, TraKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TraKnd】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TraKnd】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "DtlFil", sDtlFil, FNameLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【DtlFil】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【DtlFil】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "OIFlag", sOIFlag, OIFlagLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【FilNam】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【FilNam】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【ActDat】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【ActDat】【%d】错误!\n", i );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【DskNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【DskNo】【%d】错误!\n", i );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TTxnCd】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TTxnCd】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【HTxnCd】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【HTxnCd】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnSt", sHTxnSt, HTxnStLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【HTxnSt】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【HTxnSt】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TxnObj】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TxnObj】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TxnCnl】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TxnCnl】错误!\n" );
    return( -1 );
  }
/*
**  将批量处理汇总表对应记录修改为"B"(Booking记帐中)
*/
  ClearStr( sBchSts );
  if( strcmp( sOIFlag, "1" )==0 ) { /* 来帐 */
    if( strcmp( sTraKnd, "1052" )==0 ) { /*借记：B-准备入账*/
      strcpy( sBchSts, "B" );
    } else { /*贷记：D-已清算*/
      strcpy( sBchSts, "D" );
    }
    EXEC SQL update CbsBchSum
                set  BchSts = :sBchSts, ActDat=:sActDat, DskNo=:sDskNo
              where FilNam = :sFilNam
                and OIFlag = '1'
                and BchSts = 'U';
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, _DB_QUERY_ERR, "修改表【CbsBchSum】异常" );
      bpErrorLog(trdata, "CbsFDtlToDb:修改表【CbsBchSum】异常【%d】【%s】", SQLCODE, sFilNam);
      return( -1 );
    }
  } else { /* 往帐 */
    EXEC SQL update CbsBchSum
                set  BchSts = 'D', ActDat=:sActDat, DskNo=:sDskNo
              where FilNam = :sFilNam
                and OIFlag = '0'
                and BchSts = 'R';
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, _DB_QUERY_ERR, "修改表【CbsBchSum】异常" );
      bpErrorLog(trdata, "CbsFDtlToDb:修改表【CbsBchSum】异常【%d】【%s】", SQLCODE, sFilNam);
      return( -1 );
    }
  }
/*
**  开始处理数据文件
*/
  fp =fopen( sDtlFil, "r" );
  if( fp == NULL ) {
    bpAddResult( TrNode, "CBS999", "打开数据文件错" );
    bpErrorLog( trdata, "CbsFDtlToDb:打开数据文件【%s】失败!\n", sDtlFil );
    return( -1 );
  }
/*
** 处理数据文件的第一行并登记汇总表
*/
  ClearStr( sClrDat );
  ClearStr( sClrSce );
  ClearStr( sSSysId );
  ClearStr( sSndBNo );
  ClearStr( sRSysId );
  ClearStr( sRcvBNo );
  ClearStr( sTraKnd );
  ClearStr( sFilNam );
  ClearStr( sRefFil );
  ClearStr( sBchSqn );
  ClearStr( sRefSqn );
  ClearStr( sCusSqn );
  ClearStr( sTotNum );
  ClearStr( sTotAmt );
  ClearStr( sRefNum );
  ClearStr( sRefAmt );
  ClearStr( sRtnCod );
  ClearStr( sReServ );
  fscanf( fp, "%[^|]",  sClrDat ); /* 清算日期 */
  fscanf( fp, "|%[^|]", sClrSce ); /* 清算场次 */
  fscanf( fp, "|%[^|]", sSSysId ); /* 发起方系统号 */
  fscanf( fp, "|%[^|]", sSndBNo ); /* 发起方代码 */
  fscanf( fp, "|%[^|]", sRSysId ); /* 接收方系统号 */
  fscanf( fp, "|%[^|]", sRcvBNo ); /* 接收方代码 */
  fscanf( fp, "|%[^|]", sTraKnd ); /* 交易种类 */
  fscanf( fp, "|%[^|]", sFilNam ); /* 文件名 */
  fscanf( fp, "|%[^|]", sRefFil ); /* 参照文件名 */
  fscanf( fp, "|%[^|]", sBchSqn ); /* 批量包序号 */
  fscanf( fp, "|%[^|]", sRefSqn ); /* 参考批量包序号 */
  fscanf( fp, "|%[^|]", sCusSqn ); /* 客户批量包序号 */
  fscanf( fp, "|%[^|]", sTotNum ); /* 交易总笔数 */
  fscanf( fp, "|%[^|]", sTotAmt ); /* 交易总金额 */
  fscanf( fp, "|%[^|]", sRefNum ); /* 拒绝支付总笔数 */
  fscanf( fp, "|%[^|]", sRefAmt ); /* 拒绝支付总金额 */
  fscanf( fp, "|%[^|]", sRtnCod ); /* 返回码 */
  fscanf( fp, "|%[^\n]",sReServ ); /* 预留位 */
/*
** 处理数据明细
*/
  iOrnCnt=atol(sTotNum);
  for( i=1; i<=atol(sTotNum); i++ ) {
    ClearStr( sMsgSqn  ); /*信息序号*/
    ClearStr( sRefMsg  ); /*参考信息序号*/
    ClearStr( sMsgId   ); /*报文类型标识符*/
    ClearStr( sTxnKnd  ); /*交易种类细分类型*/
    ClearStr( sTxnAmt  ); /*交易金额*/
    ClearStr( sTraTm   ); /*交易发起日期和时间*/
    ClearStr( sClrBNo  ); /*直接清算行*/
    ClearStr( sTmpDat  ); /*委托日期*/
    ClearStr( sSndDat  ); /*委托日期*/
    ClearStr( sClrDat  ); /*清算日期*/
    ClearStr( sQryTyp  ); /*查询通知种类标识*/
    ClearStr( sAreaNo  ); /*地区号*/
    ClearStr( sCcyCod  ); /*交易货币代码*/
    ClearStr( sSvrCod  ); /*服务点输入方式码*/
    ClearStr( sCenId   ); /*中心客户号*/
    ClearStr( sCusId   ); /*企业客户号*/
    ClearStr( sCenTm   ); /*中心交易受理日期时间*/
    ClearStr( sCenLog  ); /*中心交易受理号*/
    ClearStr( sThdTm   ); /*业务处理方处理日期时间*/
    ClearStr( sThdLog  ); /*业务处理方流水号*/
    ClearStr( sRtnCod  ); /*返回码*/
    ClearStr( sCshFlg  ); /*现金转账标识*/
    ClearStr( sSmrCod  ); /*摘要代码*/
    ClearStr( sUsgCod  ); /*资金用途代码*/
    ClearStr( sRSdFlg  ); /*重发标识*/
    ClearStr( sAccFlg  ); /*对公对私标识*/
    ClearStr( sTBusTp  ); /*业务种类*/
    ClearStr( sCardFg  ); /*卡折标识*/
    ClearStr( sAccKnd  ); /*钞户汇户标识*/
    ClearStr( sFeeTyp  ); /*手续费方式*/
    ClearStr( sPayFuc  ); /*支付工具*/
    ClearStr( sAuthCd  ); /*授权码*/
    ClearStr( sPayLvl  ); /*支付优先级*/
    ClearStr( sOrgId   ); /*原交易业务唯一标识*/
    ClearStr( sSndBNo  ); /*发起行行号*/
    ClearStr( sSOpnBk  ); /*发起人开户行行号*/
    ClearStr( sSndNod  ); /*发起行网点号*/
    ClearStr( sSndAct  ); /*发起人账号*/
    ClearStr( sSndNm   ); /*发起人名称*/
    ClearStr( sVchId   ); /*凭证提交号*/
    ClearStr( sRcvBNo  ); /*接收行行号*/
    ClearStr( sROpnBk  ); /*接收人开户行行号*/
    ClearStr( sRcvNod  ); /*接收行网点号*/
    ClearStr( sRcvAct  ); /*接收人账号*/
    ClearStr( sRcvNm   ); /*接收人名称*/
    ClearStr( sAgrNo   ); /*多方协议号*/
    ClearStr( sSysSts  ); /*系统运行状态*/
    ClearStr( sCreAmt  ); /*贷方金额*/
    ClearStr( sCreCnt  ); /*贷方笔数*/
    ClearStr( sDebAmt  ); /*借方金额*/
    ClearStr( sDebCnt  ); /*借方笔数*/
    ClearStr( sCTraKnd ); /*交易种类*/
    ClearStr( sOSgnId  ); /*旧登陆标识*/
    ClearStr( sNSgnId  ); /*新登陆标识*/
    ClearStr( sSmr     ); /*交易摘要(300)*/
    ClearStr( sSecKey  ); /*密押*/
    ClearStr( sTCrpCd  ); /*企业机构代码*/
    ClearStr( sSvrKnd  ); /*服务信息类型*/
    ClearStr( sTBilNo  ); /*税票号码*/
    ClearStr( sTaxNo   ); /*纳税人编码*/
    ClearStr( sTaxer   ); /*纳税人名称*/
    ClearStr( sTaxLvl  ); /*预算级次*/
    ClearStr( sTSubCd  ); /*预算科目*/
    ClearStr( sTOrgCd  ); /*征收机关代码*/
    ClearStr( sTActDt  ); /*税票限缴日期*/
    ClearStr( sSvrMsg  ); /*服务信息内容*/
    ClearStr( sSndNm2  ); /*附加发起人名称*/
    ClearStr( sSndAdr  ); /*发起人地址*/
    ClearStr( sRcvNm2  ); /*附加接收人名称*/
    ClearStr( sRcvAdr  ); /*接收人地址*/
/*
**  专门用于处理吴SIR程序中的非法字符
*/
    if ( i==1 ) {
        fscanf( fp, "\n%[^|]", sMsgSqn );   /*信息序号*/
    } else {
        fscanf( fp, "|\n%[^|]", sMsgSqn );   /*信息序号*/
    }  
    fscanf( fp, "|%[^|]", sRefMsg  );   /*参考信息序号*/
    fscanf( fp, "|%[^|]", sMsgId   );   /*报文类型标识符*/
    fscanf( fp, "|%[^|]", sTxnKnd  );   /*交易种类细分*/
    fscanf( fp, "|%[^|]", sTxnAmt  );   /*交易金额*/
    fscanf( fp, "|%[^|]", sTraTm   );   /*交易发起日期和时间*/
    fscanf( fp, "|%[^|]", sClrBNo  );   /*直接清算行*/
    fscanf( fp, "|%[^|]", sTmpDat  );   /*委托日期*/
    strncpy( sSndDat, sTmpDat, 8 );     /*删除低位的0*/
    fscanf( fp, "|%[^|]", sClrDat  );   /*清算日期*/
    fscanf( fp, "|%[^|]", sQryTyp  );   /*查询通知种类*/
    fscanf( fp, "|%[^|]", sAreaNo  );   /*地区号*/
    fscanf( fp, "|%[^|]", sCcyCod  );   /*交易货币代码*/
    fscanf( fp, "|%[^|]", sSvrCod  );   /*服务点输入方式码*/
    fscanf( fp, "|%[^|]", sCenId   );   /*中心客户号*/
    fscanf( fp, "|%[^|]", sCusId   );   /*企业客户号*/
    fscanf( fp, "|%[^|]", sCenTm   );   /*中心受理日期时间*/
    fscanf( fp, "|%[^|]", sCenLog  );   /*中心受理号*/
    fscanf( fp, "|%[^|]", sThdTm   );   /*业务处理方处理日期时间*/
    fscanf( fp, "|%[^|]", sThdLog  );   /*业务受理方流水号*/
    fscanf( fp, "|%[^|]", sRtnCod  );   /*返回码*/
    fscanf( fp, "|%[^|]", sCshFlg  );   /*现金转帐标志*/
    fscanf( fp, "|%[^|]", sSmrCod  );   /*摘要代码*/
    fscanf( fp, "|%[^|]", sUsgCod  );   /*资金用途代码*/
    fscanf( fp, "|%[^|]", sRSdFlg  );   /*重发标识*/
    fscanf( fp, "|%[^|]", sAccFlg  );   /*对公对私标识*/
    fscanf( fp, "|%[^|]", sTBusTp  );   /*业务种类*/
    fscanf( fp, "|%[^|]", sCardFg  );   /*卡折标识*/
    fscanf( fp, "|%[^|]", sAccKnd  );   /*钞户汇户标识*/
    fscanf( fp, "|%[^|]", sFeeTyp  );   /*收费方式*/
    fscanf( fp, "|%[^|]", sPayFuc  );   /*支付工具*/
    fscanf( fp, "|%[^|]", sAuthCd  );   /*授权码*/
    fscanf( fp, "|%[^|]", sPayLvl  );   /*支付优先级*/
    fscanf( fp, "|%[^|]", sOrgId   );   /*原数据元*/
    fscanf( fp, "|%[^|]", sSndBNo  );   /*发起行行号*/
    fscanf( fp, "|%[^|]", sSOpnBk  );   /*发起人开户行行号*/
    fscanf( fp, "|%[^|]", sSndNod  );   /*发起行网点号*/
    fscanf( fp, "|%[^|]", sSndAct  );   /*发起人账号*/
    fscanf( fp, "|%[^|]", sSndNm   );   /*发起人名称*/
    fscanf( fp, "|%[^|]", sVchId   );   /*凭证提交号*/
    fscanf( fp, "|%[^|]", sRcvBNo  );   /*接收行行号*/
    fscanf( fp, "|%[^|]", sROpnBk  );   /*接收人开户行行号*/
    fscanf( fp, "|%[^|]", sRcvNod  );   /*接收行网点号*/
    fscanf( fp, "|%[^|]", sRcvAct  );   /*接收人账号*/
    fscanf( fp, "|%[^|]", sRcvNm   );   /*接收人名称*/
    fscanf( fp, "|%[^|]", sAgrNo   );   /*协议号*/
    fscanf( fp, "|%[^|]", sSysSts  );   /*系统运行状态*/
    fscanf( fp, "|%[^|]", sCreAmt  );   /*贷方金额*/
    fscanf( fp, "|%[^|]", sCreCnt  );   /*贷方笔数*/
    fscanf( fp, "|%[^|]", sDebAmt  );   /*借方金额*/
    fscanf( fp, "|%[^|]", sDebCnt  );   /*借方笔数*/
    fscanf( fp, "|%[^|]", sCTraKnd );   /*交易种类*/
    fscanf( fp, "|%[^|]", sOSgnId  );   /*旧登陆标识*/
    fscanf( fp, "|%[^|]", sNSgnId  );   /*新登陆标识*/
    fscanf( fp, "|%[^|]", sSmr     );   /*交易摘要*/
    fscanf( fp, "|%[^|]", sSecKey  );   /*密押*/
    fscanf( fp, "|%[^|]", sTCrpCd  );   /*企业机构代码*/
    fscanf( fp, "|%[^|]", sSvrKnd  );   /*服务信息内容*/
    fscanf( fp, "|%[^|]", sTBilNo  );   /*税票号码*/
    fscanf( fp, "|%[^|]", sTaxNo   );   /*纳税人编码*/
    fscanf( fp, "|%[^|]", sTaxer   );   /*纳税人名称*/
    fscanf( fp, "|%[^|]", sTaxLvl  );   /*预算级次*/
    fscanf( fp, "|%[^|]", sTSubCd  );   /*预算科目*/
    fscanf( fp, "|%[^|]", sTOrgCd  );   /*征收机关代码*/
    fscanf( fp, "|%[^|]", sTActDt  );   /*税票限缴日期*/
/**
    fscanf( fp, "|%[^|]", sSvrMsg  );   *服务信息内容*
**/
    fscanf( fp, "|%[^|]", sSndNm2  );   /*附加发起人名称*/
    fscanf( fp, "|%[^|]", sSndAdr  );   /*发起人地址*/
    fscanf( fp, "|%[^|]", sRcvNm2  );   /*附加接收人名称*/
    fscanf( fp, "|%[^|]", sRcvAdr  );   /*接收人地址*/
/*
**  取前置流水号，提供大小通道的数据及储蓄入帐的唯一标志
*/
    ClearStr( sLogNo  );
    ClearStr( sActFlg );
    ClearStr( sBokAct );
    ClearStr( sBilSts );
    ClearStr( sCnlSub );
    strcpy( sBilSts, "P" );
    if( strcmp( sOIFlag, "0" )==0 ) {
      if( strcmp( sRtnCod, "000I1000" )==0 ) {
        strcpy( sBilSts, "G" );
      } else {
        strcpy( sBilSts, "E" );
      }
      EXEC SQL update CbsBchJnl set BilSts =:sBilSts, CenTm  =:sCenTm, CenLog =:sCenLog, RtnCod =:sRtnCod, DskNo=:sDskNo, ClrDat=:sClrDat
                              where TraKnd =:sTraKnd and SndBNo =:sSndBNo and SndDat =:sSndDat and VchId  =:sVchId and OIFlag =:sOIFlag and BilSts='D';
      if( SQLCODE != SQL_SUCCESS ) {
        bpAddResult( TrNode, "CBS999", "update【CbsBchJnl】出错" );
        bpErrorLog( trdata, "CbsFDtlToDb:update【CbsBchJnl】出错【%d】-文件【%s】-数据:【%s】【%s】【%s】【%s】【%s】!\n", SQLCODE, sDtlFil, sMsgSqn, sTraKnd, sSndBNo, sSndDat, sVchId );
        return( -1 );
      }
      iOrnCnt=iOrnCnt-1;
    } else {
/*
**  获取前置流水号，同时生成业务处理方流水号
*/
      if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
        bpAddResult( TrNode, "CBS999", "取前置流水号错" );
        bpErrorLog( trdata, "CbsFDtlToDb:取前置流水号错，业务唯一标志【%s】【%s】【%s】【%s】!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
        return( -1 );
      }
      sprintf( sThdLog,"%s%s","00",sLogNo );
      ClearStr( sIsTxn );
      strcpy( sIsTxn, "Y" );
      hdelbothspace( sRcvAct );
      if( strcmp( sTraKnd, "1052" )==0 ) {
/***
        EXEC SQL select PyrAct, ActFlg
                   into :sBokAct, :sActFlg
                   from LBepCusAgr
                  where AgrNo  =:sAgrNo
                    and ( PyrAct =:sRcvAct or substr(PyrAct,4,18) =:sRcvAct )
                    and Status='0' fetch first 1 rows only;
***/
        EXEC SQL select PayAct, ActCls
                   into :sBokAct, :sActFlg
                   from CbsCenAgr
                  where AgrNo  =:sAgrNo
                    and ( PayAct =:sRcvAct or substr(PayAct,4,18) =:sRcvAct )
                    and Status='1' fetch first 1 rows only;
        if( SQLCODE != SQL_SUCCESS ) {
          bpErrorLog( trdata, "CbsFDtlToDb:帐号【%s】未与收费单位【%s】签约，协议号【%s】!\n", sRcvAct, sSndAct, sAgrNo );
          iOrnCnt=iOrnCnt-1;
          strcpy( sBilSts, "E" );
          strcpy( sRtnCod, "001O6065" );
          strcpy( sIsTxn, "N" );
          goto DB_INSERT;
        }
      }
/*
**  根据接收人开户行行号获取归属分行号、帐务中心号
*/
      EXEC SQL select retnod, BrNo
                 into :sNodNo, :sBrNo
                 from pubnodinf
                where SBkNo=:sROpnBk fetch first 1 rows only;
      if( SQLCODE != SQL_SUCCESS ) {
        bpErrorLog( trdata, "CbsFDtlToDb:获取归属分行号出错，接收人开户行行号:【%s】!\n", sROpnBk );
        iOrnCnt=iOrnCnt-1;
        strcpy( sBilSts, "E" );
        strcpy( sRtnCod, "001O1040" );
        strcpy( sIsTxn, "N" );
        goto DB_INSERT;
      }
/*
**  根据分行号取交易渠道
*/
      EXEC SQL select CtlNod, CnlSub
                 into :sCtlNod, :sCnlSub
                 from CbsBnkInf
                where BrNo=:sBrNo;
      if( SQLCODE != SQL_SUCCESS ) {
        bpErrorLog( trdata, "CbsFDtlToDb:获取归属交易渠道、会计分录序号出错，接收人开户行行号:【%s】!\n", sROpnBk );
        iOrnCnt=iOrnCnt-1;
        strcpy( sBilSts, "E" );
        strcpy( sIsTxn, "N" );
        strcpy( sRtnCod, "001O1040" );
        goto DB_INSERT;
      }
/*
** 退回不自动入账
*/
      if( strcmp( sTBusTp, "99985" )==0 ) {
        bpErrorLog( trdata, "CbsFDtlToDb:退回业务不能自动入账:【%s】【%s】【%s】【%s】【%s】!\n", sTraKnd,sSndBNo,sSndDat,sVchId,sOIFlag );
        iOrnCnt=iOrnCnt-1;
        strcpy( sBilSts, "E" );
        strcpy( sIsTxn, "N" );
        strcpy( sRtnCod, "001O1040" );
        goto DB_INSERT;
      }
/*
**  根据分行号和交易渠道获取电子柜员号
*/
      if( sqnGetDumTlr( sBrNo, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
        bpErrorLog( trdata, "CbsFDtlToDb:取前置电子柜员号错【%s】【%s】【%s】【%s】!\n", sBrNo, sTxnCnl, sCnlSub, sTlrId );
        iOrnCnt=iOrnCnt-1;
        strcpy( sBilSts, "E" );
        strcpy( sIsTxn, "N" );
        strcpy( sRtnCod, "001S3008" );
        goto DB_INSERT;
      }
/*
**  数据入库
*/
DB_INSERT:
      EXEC SQL insert into CbsBchJnl( FilNam,MsgSqn,TraKnd,SndBNo,SndDat,VchId,OIFlag,BilSts,MsgId,TxnKnd,TxnAmt,TraTm,ClrDat,CcyCod,SvrCod,CenTm,CenLog,ThdTm,ThdLog,RtnCod,CshFlg,SmrCod,UsgCod,RSdFlg,AccFlg,TBusTp,CardFg,AccKnd,FeeTyp,PayFuc,AuthCd,PayLvl,SOpnBk,SndNod,SndAct,SndNm,SndAdr,RcvBNo,ROpnBk,RcvNod,RcvAct,RcvNm,RcvAdr,AgrNo,Smr,SvrKnd,TBilNo,TaxNo,Taxer,TaxLvl,TSubCd,TOrgCd,TActDt,SecKey,BrNo,NodNo,LogNo,ActFlg,BokAct,DskNo,ActDat,TTxnCd,HTxnCd,HTxnSt,IsTxn,TxnObj,TlrId )
                              values( :sFilNam,:sMsgSqn,:sTraKnd,:sSndBNo,:sSndDat,:sVchId,:sOIFlag,:sBilSts,:sMsgId,:sTxnKnd,:sTxnAmt,:sTraTm,:sClrDat,:sCcyCod,:sSvrCod,:sCenTm,:sCenLog,:sThdTm,:sThdLog,:sRtnCod,:sCshFlg,:sSmrCod,:sUsgCod,:sRSdFlg,:sAccFlg,:sTBusTp,:sCardFg,:sAccKnd,:sFeeTyp,:sPayFuc,:sAuthCd,:sPayLvl,:sSOpnBk,:sSndNod,:sSndAct,:sSndNm,:sSndAdr,:sRcvBNo,:sROpnBk,:sRcvNod,:sRcvAct,:sRcvNm,:sRcvAdr,:sAgrNo,:sSmr,:sSvrKnd,:sTBilNo,:sTaxNo,:sTaxer,:sTaxLvl,:sTSubCd,:sTOrgCd,:sTActDt,:sSecKey,:sBrNo,:sNodNo,:sLogNo,:sActFlg,:sBokAct,:sDskNo,:sActDat,:sTTxnCd,:sHTxnCd,:sHTxnSt,:sIsTxn,:sTxnObj,:sTlrId );
      if( SQLCODE != SQL_SUCCESS ) {
        bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsBchJnl】出错" );
        bpErrorLog( trdata, "CbsFDtlToDb:insert【CbsBchJnl】出错【%d】-文件【%s】-数据:【%s】!\n", SQLCODE, sDtlFil, sMsgSqn );
/**
bpErrorLog( trdata, "数据内容:FilNam【%s】MsgSqn【%s】TraKnd【%s】SndBNo【%s】SndDat【%s】VchId【%s】OIFlag【%s】BilSts【%s】MsgId【%s】TxnKnd【%s】TxnAmt【%s】TraTm【%s】ClrDat【%s】CcyCod【%s】SvrCod【%s】CenTm【%s】CenLog【%s】ThdTm【%s】ThdLog【%s】RtnCod【%s】CshFlg【%s】SmrCod【%s】UsgCod【%s】RSdFlg【%s】AccFlg【%s】TBusTp【%s】CardFg【%s】AccKnd【%s】FeeTyp【%s】PayFuc【%s】AuthCd【%s】PayLvl【%s】SOpnBk【%s】SndNod【%s】SndAct【%s】SndNm【%s】SndAdr【%s】RcvBNo【%s】ROpnBk【%s】RcvNod【%s】RcvAct【%s】RcvNm【%s】RcvAdr【%s】AgrNo【%s】Smr【%s】SvrKnd【%s】TBilNo【%s】TaxNo【%s】Taxer【%s】TaxLvl【%s】TSubCd【%s】TOrgCd【%s】TActDt【%s】SecKey【%s】BrNo【%s】NodNo【%s】LogNo【%s】ActFlg【%s】BokAct【%s】DskNo【%s】ActDat【%s】TTxnCd【%s】HTxnCd【%s】HTxnSt【%s】IsTxn【%s】TxnObj【%s】TlrId【%s】!\n", \
sFilNam,sMsgSqn,sTraKnd,sSndBNo,sSndDat,sVchId,sOIFlag,sBilSts,sMsgId,sTxnKnd,sTxnAmt,sTraTm,sClrDat,sCcyCod,sSvrCod,sCenTm,sCenLog,sThdTm,sThdLog,sRtnCod,sCshFlg,sSmrCod,sUsgCod,sRSdFlg,sAccFlg,sTBusTp,sCardFg,sAccKnd,sFeeTyp,sPayFuc,sAuthCd,sPayLvl,sSOpnBk,sSndNod,sSndAct,sSndNm,sSndAdr,sRcvBNo,sROpnBk,sRcvNod,sRcvAct,sRcvNm,sRcvAdr,sAgrNo,sSmr,sSvrKnd,sTBilNo,sTaxNo,sTaxer,sTaxLvl,sTSubCd,sTOrgCd,sTActDt,sSecKey,sBrNo,sNodNo,sLogNo,sActFlg,sBokAct,sDskNo,sActDat,sTTxnCd,sHTxnCd,sHTxnSt,sIsTxn,sTxnObj,sTlrId );
**/
        fclose( fp );
        return( -1 );
      }
    }
  }
  if( strcmp( sOIFlag, "0" )==0 ) {
/*
**  将磁盘编号作为往帐发出时行内业务的大小通道磁盘号（暂时不考虑行内业务）
*/
/**
    EXEC SQL update CbsBchJnl
                set DskNo  =:sDskNo
              where FilNam = :sRefFil
                and OIFlag = '0'
                and BilSts = 'B';
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, _DB_QUERY_ERR, "修改表【CbsBchJnl】异常" );
      bpErrorLog(trdata, "CbsFDtlToDb:修改表【CbsBchJnl】异常【%d】【%s】", SQLCODE, sRefFil);
      return( -1 );
    }
    EXEC SQL select count(*)
               into :iOrnCnt
               from CbsBchJnl
              where FilNam = :sRefFil
                and OIFlag = '0'
                and BilSts = 'B';
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, "CBS999", "计算【OrnCnt】异常" );
      bpErrorLog(trdata, "CbsFDtlToDb:计算【OrnCnt】异常【%d】", SQLCODE);
      return( -1 );
    }
**/
  }
  sprintf( sOrnCnt,"%08d", iOrnCnt );
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
/*
**  关闭处理文件
*/
  fclose( fp );
  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End CbsFDtlToDb.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsFilConv
  Description       : 将普通文件转换为8583文件
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int CbsFilConv(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
  EXEC SQL END DECLARE SECTION;
    char   sSrcFil[FNameLen+1];
    char   sSndFil[FilNamLen+1];
    char   sDes8583[FNameLen+1];
    int    iFSize=0, ret;
    char   sFSize[FSizeLen+1];
    FILE   *fp;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin CbsFilConv.\n" );
/*
**  检查输入参数个数
*/
  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, "CBS999", "参数个数错" );
    bpErrorLog( trdata, "CbsFilConv: 参数个数错!" );
    return( -1 );
  }
/*
**  获取转换前后文件名
*/
  ClearStr( sSrcFil );
  ClearStr( sSndFil );
  ClearStr( sDes8583 );
  sprintf( sSrcFil, "%s/%s/%s", getenv("WORKDIR"), Step_Arg2, Step_Arg1 );
  strncpy( sSndFil, Step_Arg1, 36 );
  sprintf( sDes8583, "%s/%s/%s", getenv("WORKDIR"), Step_Arg2, sSndFil );
/*
**  进行8583格式转换
*/
  ret=CbsFilChg( "1", sSrcFil, sDes8583 );
  if( ret!=0 ) {
    bpAddResult( TrNode, "CBS999", "数据文件转换异常" );
    bpErrorLog( trdata, "CbsFilConv:数据文件【%s】转换异常!\n", sDes8583 );
    return( -1 );
  }
/*
**  获取转换后文件的大小
*/
  fp =fopen( sDes8583, "r+" );
  if( fp == NULL ) {
    bpAddResult( TrNode, "CBS999", "打开数据文件错" );
    bpErrorLog( trdata, "CbsFilConv:打开数据文件【%s】失败!\n", sDes8583 );
    fclose( fp );
    return( -1 );
  }
  fseek( fp, 0, SEEK_SET );
  iFSize=hfgetsize( fp );
  sprintf( sFSize, "%08d", iFSize );
/*
**  替换文件中XXXXXXXX为真实文件大小
*/
  fseek( fp, F8583SizeOffset, SEEK_SET );
  fwrite( sFSize, sizeof(sFSize)-1, 1, fp );
  fclose( fp );
  etfAddOrRepNode( TrNode, "SndFil", sSndFil, FilNamLen );
  etfAddOrRepNode( TrNode, "FSize", sFSize,  FSizeLen );
  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End CbsFilConv.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsF1051OToDb
  Description       : 将批量贷记往帐文件入库
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int CbsF1051OToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sMsgTyp[MsgTypLen+1];
    char   sRspCod[RspCodLen+1];
    char   sRspMsg[RspMsgLen+1];

    char   sFilNam[FilNamLen+1];
    char   sMsgSqn[MsgSqnLen+1];
    char   sTraKnd[TraKndLen+1];
    char   sSndBNo[SndBNoLen+1];
    char   sSndDat[SndDatLen+1];
    char   sVchId[VchIdLen+1];
    char   sOIFlag[OIFlagLen+1];
    char   sBilSts[BilStsLen+1];
    char   sMsgId[MsgIdLen+1];
    char   sTxnKnd[TxnKndLen+1];
    char   sTxnAmt[TxnAmtLen+1];
    char   sTraTm[TraTmLen+1];
    char   sClrDat[ClrDatLen+1];
    char   sCcyCod[CcyCodLen+1];
    char   sSvrCod[SvrCodLen+1];
    char   sCenTm[CenTmLen+1];
    char   sCenLog[CenLogLen+1];
    char   sThdTm[ThdTmLen+1];
    char   sThdLog[ThdLogLen+1];
    char   sRtnCod[RtnCodLen+1];
    char   sCshFlg[CshFlgLen+1];
    char   sSmrCod[SmrCodLen+1];
    char   sUsgCod[UsgCodLen+1];
    char   sRSdFlg[RSdFlgLen+1];
    char   sAccFlg[AccFlgLen+1];
    char   sTBusTp[TBusTpLen+1];
    char   sCardFg[CardFgLen+1];
    char   sAccKnd[AccKndLen+1];
    char   sFeeTyp[FeeTypLen+1];
    char   sPayFuc[PayFucLen+1];
    char   sAuthCd[AuthCdLen+1];
    char   sPayLvl[PayLvlLen+1];
    char   sSOpnBk[SOpnBkLen+1];
    char   sSndNod[SndNodLen+1];
    char   sSndAct[SndActLen+1];
    char   sSndNm[SndNmLen+1];
    char   sSndAdr[SndAdrLen+1];
    char   sRcvBNo[RcvBNoLen+1];
    char   sROpnBk[ROpnBkLen+1];
    char   sRcvNod[RcvNodLen+1];
    char   sRcvAct[RcvActLen+1];
    char   sRcvNm[RcvNmLen+1];
    char   sRcvAdr[RcvAdrLen+1];
    char   sAgrNo[AgrNoLen+1];
    char   sSmr[SmrLen+1];
    char   sSecKey[SecKeyLen+1];
    char   sBrNo[BrNoLen+1];
    char   sNodNo[NodNoLen+1];
    char   sLogNo[LogNoLen+1];
    char   sActFlg[ActFlgLen+1];
    char   sBokAct[ActNoLen+1];
    char   sDskNo[DskNoLen+1];
    char   sActDat[ActDatLen+1];
    char   sTTxnCd[TTxnCdLen+1];
    char   sHTxnCd[HTxnCdLen+1];
    char   sHTxnSt[HTxnStLen+1];
    char   sIsTxn[IsTxnLen+1];
    char   sTxnObj[TxnObjLen+1];
    char   sTlrId[TlrIdLen+1];

    char   sTxnCnl[TxnCnlLen+1];
    char   sRec[RecLen+1];
    char   sRecNum[TotNumLen+1];
    char   sRecAmt[TotAmtLen+1];
/*
**  记帐要素
*/
    char   sFName[FNameLen+1];
    char   sCnlSub[CnlSubLen+1];
    char   sBgnLoc[BgnLocLen+1];
    char   sCenLen[CenLenLen+1];
  EXEC SQL END DECLARE SECTION;
    FILE   *fp;
    int    iRecNum=0;
    long   iRecAmt=0;
    char   sFlag[2];
    int    i=0,j=0,iTxnAmt=0;
    char   sTmpSmr[SmrLen+1];
    char   sTmpNm[RcvNmLen+1];
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin CbsF1051OToDb.\n" );
/*
**  检查输入参数个数
*/
  ClearStr( sMsgTyp );
  ClearStr( sRspCod );
  ClearStr( sRspMsg );

  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "参数个数错" );
    bpErrorLog( trdata, "CbsF1051OToDb: 参数个数错!" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "参数个数错" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  初始化变量
*/
  ClearStr( sFilNam );
  ClearStr( sMsgSqn );
  ClearStr( sTraKnd );
  ClearStr( sSndBNo );
  ClearStr( sSndDat );
  ClearStr( sVchId  );
  ClearStr( sOIFlag );
  ClearStr( sBilSts );
  ClearStr( sMsgId  );
  ClearStr( sTxnKnd );
  ClearStr( sTxnAmt );
  ClearStr( sTraTm  );
  ClearStr( sClrDat );
  ClearStr( sCcyCod );
  ClearStr( sSvrCod );
  ClearStr( sCenTm  );
  ClearStr( sCenLog );
  ClearStr( sThdTm  );
  ClearStr( sThdLog );
  ClearStr( sRtnCod );
  ClearStr( sCshFlg );
  ClearStr( sSmrCod );
  ClearStr( sUsgCod );
  ClearStr( sRSdFlg );
  ClearStr( sAccFlg );
  ClearStr( sTBusTp );
  ClearStr( sCardFg );
  ClearStr( sAccKnd );
  ClearStr( sFeeTyp );
  ClearStr( sPayFuc );
  ClearStr( sAuthCd );
  ClearStr( sPayLvl );
  ClearStr( sSOpnBk );
  ClearStr( sSndNod );
  ClearStr( sSndAct );
  ClearStr( sSndNm  );
  ClearStr( sSndAdr );
  ClearStr( sRcvBNo );
  ClearStr( sROpnBk );
  ClearStr( sRcvNod );
  ClearStr( sRcvAct );
  ClearStr( sRcvNm  );
  ClearStr( sRcvAdr );
  ClearStr( sAgrNo  );
  ClearStr( sSmr    );
  ClearStr( sSecKey );
  ClearStr( sBrNo   );
  ClearStr( sNodNo );
  ClearStr( sLogNo  );
  ClearStr( sActFlg );
  ClearStr( sBokAct );
  ClearStr( sDskNo  );
  ClearStr( sActDat );
  ClearStr( sTTxnCd );
  ClearStr( sHTxnCd );
  ClearStr( sHTxnSt );
  ClearStr( sIsTxn  );
  ClearStr( sTxnObj );
  ClearStr( sTlrId  );
/*
**  部分数据常量
*/
  if( etfGetChildValue(TrNode, "TraKnd", sTraKnd, TraKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TraKnd】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TraKnd】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【TraKnd】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "SndBNo", sSndBNo, SndBNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【SndBNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【SndBNo】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【SndBNo】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【ActDat】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【ActDat】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【ActDat】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  strcpy( sSndDat, sActDat );
  if( etfGetChildValue(TrNode, "OIFlag", sOIFlag, OIFlagLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【OIFlag】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【OIFlag】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【OIFlag】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "MsgId", sMsgId, MsgIdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【MsgId】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【MsgId】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【MsgId】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnKnd", sTxnKnd, TxnKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TxnKnd】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TxnKnd】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【TxnKnd】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TraTm", sTraTm, TraTmLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TraTm】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TraTm】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【TraTm】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CcyCod", sCcyCod, CcyCodLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【CcyCod】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【CcyCod】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【CcyCod】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "SvrCod", sSvrCod, SvrCodLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【SvrCod】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【SvrCod】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【SvrCod】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CshFlg", sCshFlg, CshFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【CshFlg】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【CshFlg】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【CshFlg】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "RsdFlg", sRSdFlg, RSdFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【RsdFlg】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【RsdFlg】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【RsdFlg】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "AccFlg", sAccFlg, AccFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【AccFlg】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【AccFlg】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【AccFlg】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CardFg", sCardFg, CardFgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【CardFg】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【CardFg】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【CardFg】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "AccKnd", sAccKnd, AccKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【AccKnd】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【AccKnd】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【AccKnd】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "FeeTyp", sFeeTyp, FeeTypLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【FeeTyp】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【FeeTyp】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【FeeTyp】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "PayFuc", sPayFuc, PayFucLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【PayFuc】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【PayFuc】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【PayFuc】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "PayLvl", sPayLvl, PayLvlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【PayLvl】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【PayLvl】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【PayLvl】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "SOpnBk", sSOpnBk, SOpnBkLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【SOpnBk】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【SOpnBk】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【SOpnBk】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【NodNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【NodNo】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【NodNo】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActNo", sSndAct, ActNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【ActNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【ActNo】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【ActNo】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActNm", sSndNm, SndNmLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【ActNm】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【ActNm】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【ActNm】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  strcpy( sSecKey, "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
  if ( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【BrNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【BrNo】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【BrNo】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  sprintf( sSndNod, "%09s", sNodNo );
  strcpy( sRcvNod, "000000000" );

  strcpy( sDskNo, "AAAAAAAAAAAA" );
/**
  if ( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【DskNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【DskNo】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【DskNo】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
**/
  if ( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TxnCnl】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TxnCnl】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【TxnCnl】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  根据分行号取交易渠道
*/
  ClearStr( sCnlSub  );
  EXEC SQL select CnlSub
             into :sCnlSub
             from CbsBnkInf
            where BrNo=:sBrNo;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog( trdata, "CbsF1051OToDb:获取归属交易渠道、会计分录序号出错，发起分行行号:【%s】!\n", sBrNo );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "获取归属交易渠道、会计分录序号出错" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  sprintf( sFName, "%s/%s/%s", getenv("WORKDIR"), Step_Arg1, Step_Arg2 );
  strcpy( sFilNam, Step_Arg2 );
  fp =fopen( sFName, "r" );
  if( fp == NULL ) {
    bpAddResult( TrNode, "CBS999", "打开数据文件错" );
    bpErrorLog( trdata, "CbsF1051OToDb:打开数据文件【%s】失败!\n", sFName );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "打开数据文件错" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    fclose( fp );
    return( -1 );
  }

  iRecNum=0;
  ClearStr( sFlag );
  ClearStr( sTBusTp );
  ClearStr( sUsgCod );
  ClearStr( sSmrCod );

  strcpy( sFlag, "0" );
  strcpy( sTBusTp, "04900" );
  strcpy( sUsgCod, "090" );
  strcpy( sSmrCod, "0002" );
  while( !feof( fp ) ) {
/*
**  利用前置流水号作为信息序号、凭证提交号
*/
    ClearStr( sLogNo  );
    ClearStr( sMsgSqn );
    ClearStr( sVchId  );
    ClearStr( sTTxnCd );
    ClearStr( sHTxnCd );
    ClearStr( sHTxnSt );
    ClearStr( sIsTxn  );
    ClearStr( sTxnObj );
    ClearStr( sActFlg );
    ClearStr( sBokAct );
    ClearStr( sBilSts );
    ClearStr( sRtnCod );
/*
**  变量初始值
*/
    strcpy( sBilSts, "P" );
    strcpy( sIsTxn, "N" );
    if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
      bpErrorLog( trdata, "CbsFileToDb:取前置流水号错，文件名【%s】!\n", sFName );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "取前置流水号错，文件名【%s】!\n", sFName );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
      fclose( fp );
      return( -1 );
    }

    sprintf( sMsgSqn, "%s%s", SYSID, sLogNo+2 );
    memcpy( sVchId, sLogNo+6, 8 );
/*
**  逐行获取数据
*/
    ClearStr( sROpnBk );
    ClearStr( sRcvBNo );
    ClearStr( sRcvAct );
    ClearStr( sRcvNm  );
    ClearStr( sTxnAmt );
    ClearStr( sSmr    );
    if ( strcmp(sFlag,"0")==0 ) {
      fscanf( fp, "%[^\t]", sROpnBk );
      strcpy( sFlag, "1" );
    } else {
      fscanf( fp, "\n%[^\t]", sROpnBk );
    }  
    hdelbothspace( sROpnBk );
    if( strlen( sROpnBk ) ==0 ) break;
    strcpy( sRcvBNo, sROpnBk );
    fscanf( fp, "\t%[^\t]", sRcvAct );
    fscanf( fp, "\t%[^\t]", sRcvNm  );
    fscanf( fp, "\t%[^\t]", sTxnAmt );
    fscanf( fp, "\t%[^\n]", sSmr );

    ClearStr( sTmpNm );
    Str2CStr( sRcvNm, sTmpNm );
    if( strlen(sTmpNm) > RcvNmLen ) {
      sTmpNm[RcvNmLen+1] = '\0';
    }
    ClearStr( sRcvNm );
    strcpy( sRcvNm, sTmpNm );

    ClearStr( sTmpSmr );
    Str2CStr( sSmr, sTmpSmr );
    if( strlen(sTmpSmr) > SmrLen ) {
      sTmpSmr[SmrLen+1] = '\0';
    }
    ClearStr( sSmr );
    strcpy( sSmr, sTmpSmr );
/*
**  去除金额中的小数点，并转换为指定格式
*/
    j=0;
    for( i=0;i<sizeof(sTxnAmt);i++) {
      if( sTxnAmt[i]=='.' ) continue;
      sTxnAmt[j++]=sTxnAmt[i];
    }
    sTxnAmt[j]='\0';
    iTxnAmt=0;
    iTxnAmt=atol(sTxnAmt);
    ClearStr( sTxnAmt );
    sprintf( sTxnAmt, "%015d", iTxnAmt );
/***
    ClearStr( sRec    );
    ClearStr( sRcvBNo );
    ClearStr( sROpnBk );
    ClearStr( sRcvAct );
    ClearStr( sRcvNm  );
    ClearStr( sTxnAmt );
    ClearStr( sTBusTp );
    ClearStr( sUsgCod );
    ClearStr( sSmrCod );
    ClearStr( sSmr    );
    fgets( sRec, RecLen, fp );
    memcpy( sRcvBNo, sRec+RcvBNoOffset, RcvBNoLen );
    if( strlen( sRcvBNo )==0 ) break;
    if( strlen( sRec ) !=RecDatLen ) {
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "文件【%s】第【%d】笔有误!", sFilNam, iRecNum+1 );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
      fclose( fp );
      return( -1 );
    }
    memcpy( sROpnBk, sRec+ROpnBkOffset, ROpnBkLen );
    memcpy( sRcvAct, sRec+RcvActOffset, RcvActLen );
    memcpy( sRcvNm,  sRec+RcvNmOffset,  RcvNmLen  );
    memcpy( sTxnAmt, sRec+TxnAmtOffset, TxnAmtLen );
    memcpy( sTBusTp, sRec+TBusTpOffset, TBusTpLen );
    memcpy( sUsgCod, sRec+UsgCodOffset, UsgCodLen );
    memcpy( sSmrCod, sRec+SmrCodOffset, SmrCodLen );
    memcpy( sSmr,    sRec+SmrOffset,    SmrLen    );

    hdelallspace( sRcvNm );
    hdelallspace( sSmr );
***/
/*
**  若接收行为交行客户
*/
    if( memcmp(sROpnBk,BOCSGN,3)==0 ) {
      strcpy( sBilSts, "B" );
      strcpy( sTTxnCd, "465851" );
      strcpy( sHTxnCd, "465895" );
      strcpy( sHTxnSt, "U" );
      strcpy( sIsTxn, "Y" );
      strcpy( sTxnObj, "OFRTCBS5" );
      if( memcmp(sRcvAct,"071",3)==0 ) {
        EXEC SQL select ActNo
                   into :sBokAct
                   from SavOldAct
                  where OldAct =:sRcvAct;
        if( SQLCODE == SQL_SUCCESS ) {
          strcpy( sActFlg, "1" );
        } else {
          bpErrorLog( trdata, "CbsFDtlToDb:帐号【%s】新旧帐号对照表不存在!\n", sRcvAct );
          strcpy( sBilSts, "E" );
          strcpy( sRtnCod, "001O6017" );
          strcpy( sIsTxn, "N" );
        }
      } else { 
        EXEC SQL select BgnLoc, CenLen
                   into :sBgnLoc, :sCenLen
                   from StpBinInf
                  where CrdBin = substr( :sRcvAct, 1, 6 );
        if( SQLCODE == SQL_SUCCESS ) {
          strcpy( sActFlg, "2" );
        }  else {
          if( ( strlen(sRcvAct)==ActNoLen ) && ( memcmp(sRcvAct+AreaCdLen,"9",1)==0 ) ) {
            if( ( memcmp(sRcvAct+ActNoLen-VchTypLen,"209",VchTypLen)==0 )||( memcmp(sRcvAct+ActNoLen-VchTypLen,"229",VchTypLen)==0 ) ) { /* 卡备用金帐号 */
              strcpy( sActFlg, "2" );
            } else {
              strcpy( sActFlg, "1" );
            }
          }  else {
            strcpy( sActFlg, "0" );
          }
        }
        memcpy( sBokAct, sRcvAct, ActNoLen );
      }
/*
**  根据分行号和交易渠道获取电子柜员号
*/
      if( strcmp( sBilSts, "E")!=0 ) {
        if( sqnGetDumTlr( sBrNo, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
          bpErrorLog( trdata, "CbsF1051OToDb:取前置电子柜员号错【%s】【%s】【%s】!\n", sBrNo, sTxnCnl, sCnlSub );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "取前置电子柜员号错" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          fclose( fp );
          return( -1 );
        }
      }
    } else {
/*
**  接收行不是交行
**  判断该行号是否加入金融服务系统
*/
      strcpy( sActFlg, "A" );
      EXEC SQL select A.BankNo
                 from CbsBankCd A, CbsBTxnCd B
                where A.BankNo = :sROpnBk
                  and A.BankNo = B.BankNo
                  and B.TxnKnd = :sTxnKnd
                  and B.CcyCod = :sCcyCod
                  and A.EffDat <= :sActDat
                  and A.IvdDat >= :sActDat
                  and B.EffDat <= :sActDat
                  and B.IvdDat >= :sActDat;
      if( SQLCODE != SQL_SUCCESS ) {
        bpErrorLog( trdata, "CbsF1051OToDb:行号【%s】【%s】未开通此类业务!\n", sROpnBk, sActDat );
        strcpy( sBilSts, "E" );
        strcpy( sRtnCod, "001O6010" );
      } else {
/**
        strcpy( sIsTxn, "Y" );
**/
      }
    }

    EXEC SQL insert into CbsBchJnl( FilNam,MsgSqn,TraKnd,SndBNo,SndDat,VchId,OIFlag,BilSts,MsgId,TxnKnd,TxnAmt,TraTm,ClrDat,CcyCod,SvrCod,CenTm,CenLog,ThdTm,ThdLog,RtnCod,CshFlg,SmrCod,UsgCod,RSdFlg,AccFlg,TBusTp,CardFg,AccKnd,FeeTyp,PayFuc,AuthCd,PayLvl,SOpnBk,SndNod,SndAct,SndNm,SndAdr,RcvBNo,ROpnBk,RcvNod,RcvAct,RcvNm,RcvAdr,AgrNo,Smr,SecKey,BrNo,NodNo,LogNo,ActFlg,BokAct,DskNo,ActDat,TTxnCd,HTxnCd,HTxnSt,IsTxn,TxnObj,TlrId )
                            values( :sFilNam,:sMsgSqn,:sTraKnd,:sSndBNo,:sSndDat,:sVchId,:sOIFlag,:sBilSts,:sMsgId,:sTxnKnd,:sTxnAmt,:sTraTm,:sClrDat,:sCcyCod,:sSvrCod,:sCenTm,:sCenLog,:sThdTm,:sThdLog,:sRtnCod,:sCshFlg,:sSmrCod,:sUsgCod,:sRSdFlg,:sAccFlg,:sTBusTp,:sCardFg,:sAccKnd,:sFeeTyp,:sPayFuc,:sAuthCd,:sPayLvl,:sSOpnBk,:sSndNod,:sSndAct,:sSndNm,:sSndAdr,:sRcvBNo,:sROpnBk,:sRcvNod,:sRcvAct,:sRcvNm,:sRcvAdr,:sAgrNo,:sSmr,:sSecKey,:sBrNo,:sNodNo,:sLogNo,:sActFlg,:sBokAct,:sDskNo,:sActDat,:sTTxnCd,:sHTxnCd,:sHTxnSt,:sIsTxn,:sTxnObj,:sTlrId );
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "CbsF1051OToDb:insert【CbsBchJnl】出错【%d】-文件【%s】!\n", SQLCODE, sFName );
      bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsBchJnl】出错" );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      strcpy( sRspMsg, "数据入库失败" );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
/**
bpErrorLog( trdata, "数据-1-内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", \
sFilNam, sMsgSqn, sTraKnd, sSndBNo, sSndDat, sVchId, sBilSts, sOIFlag, sMsgId, sTxnKnd );
bpErrorLog( trdata, "数据-2-内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", \
sTxnAmt, sTraTm,  sCcyCod, sSvrCod, sCshFlg, sSmrCod, sUsgCod, sRSdFlg, sAccFlg, sTBusTp );
bpErrorLog( trdata, "数据-3-内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", \
sCardFg, sAccKnd, sFeeTyp,sPayFuc, sSOpnBk, sSndNod, sSndAct, sSndNm, sRcvBNo, sROpnBk );
bpErrorLog( trdata, "数据-4-内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", \
sRcvAct, sRcvNm, sSmr, sSecKey, sBrNo, sNodNo, sLogNo, sDskNo, sTxnCnl, sActFlg );
**/
      fclose( fp );
      return( -1 );
    }
/*
**  计算总笔数和总金额，提供核对功能
*/
    iRecNum=iRecNum+1;
    iRecAmt=iRecAmt+atoi(sTxnAmt);
  }

  ClearStr( sRecNum );
  ClearStr( sRecAmt );
  sprintf( sRecNum, "%010d", iRecNum );
  sprintf( sRecAmt, "%016d", iRecAmt );
  etfAddOrRepNode( TrNode, "RecNum", sRecNum, TotNumLen );
  etfAddOrRepNode( TrNode, "RecAmt", sRecAmt, TotAmtLen );

  fclose( fp );
  strcpy( sMsgTyp, "N" );
  strcpy( sRspCod, "000000" );
  strcpy( sRspMsg, "交易成功" );
  etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
  etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
  etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
  bpTraceLog( trdata, "End CbsF1051OToDb.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsF1052OToDb
  Description       : 将定期借记往帐文件入库
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int CbsF1052OToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sMsgTyp[MsgTypLen+1];
    char   sRspCod[RspCodLen+1];
    char   sRspMsg[RspMsgLen+1];

    char   sFilNam[FilNamLen+1];
    char   sMsgSqn[MsgSqnLen+1];
    char   sTraKnd[TraKndLen+1];
    char   sSndBNo[SndBNoLen+1];
    char   sSndDat[SndDatLen+1];
    char   sVchId[VchIdLen+1];
    char   sOIFlag[OIFlagLen+1];
    char   sBilSts[BilStsLen+1];
    char   sMsgId[MsgIdLen+1];
    char   sTxnKnd[TxnKndLen+1];
    char   sTxnAmt[TxnAmtLen+1];
    char   sTraTm[TraTmLen+1];
    char   sClrDat[ClrDatLen+1];
    char   sCcyCod[CcyCodLen+1];
    char   sSvrCod[SvrCodLen+1];
    char   sCenTm[CenTmLen+1];
    char   sCenLog[CenLogLen+1];
    char   sThdTm[ThdTmLen+1];
    char   sThdLog[ThdLogLen+1];
    char   sRtnCod[RtnCodLen+1];
    char   sCshFlg[CshFlgLen+1];
    char   sSmrCod[SmrCodLen+1];
    char   sUsgCod[UsgCodLen+1];
    char   sRSdFlg[RSdFlgLen+1];
    char   sAccFlg[AccFlgLen+1];
    char   sTBusTp[TBusTpLen+1];
    char   sCardFg[CardFgLen+1];
    char   sAccKnd[AccKndLen+1];
    char   sFeeTyp[FeeTypLen+1];
    char   sPayFuc[PayFucLen+1];
    char   sAuthCd[AuthCdLen+1];
    char   sPayLvl[PayLvlLen+1];
    char   sSOpnBk[SOpnBkLen+1];
    char   sSndNod[SndNodLen+1];
    char   sSndAct[SndActLen+1];
    char   sSndNm[SndNmLen+1];
    char   sSndAdr[SndAdrLen+1];
    char   sRcvBNo[RcvBNoLen+1];
    char   sROpnBk[ROpnBkLen+1];
    char   sRcvNod[RcvNodLen+1];
    char   sRcvAct[RcvActLen+1];
    char   sRcvNm[RcvNmLen+1];
    char   sRcvAdr[RcvAdrLen+1];
    char   sAgrNo[AgrNoLen+1];
    char   sSmr[SmrLen+1];
    char   sSecKey[SecKeyLen+1];
    char   sBrNo[BrNoLen+1];
    char   sNodNo[NodNoLen+1];
    char   sLogNo[LogNoLen+1];
    char   sActFlg[ActFlgLen+1];
    char   sBokAct[ActNoLen+1];
    char   sDskNo[DskNoLen+1];
    char   sActDat[ActDatLen+1];
    char   sTTxnCd[TTxnCdLen+1];
    char   sHTxnCd[HTxnCdLen+1];
    char   sHTxnSt[HTxnStLen+1];
    char   sIsTxn[IsTxnLen+1];
    char   sTxnObj[TxnObjLen+1];
    char   sTlrId[TlrIdLen+1];

    char   sTxnCnl[TxnCnlLen+1];
    char   sRec[RecLen+1];
    char   sRecNum[TotNumLen+1];
    char   sRecAmt[TotAmtLen+1];
/*
**  记帐要素
*/
    char   sFName[FNameLen+1];
    char   sCnlSub[CnlSubLen+1];
    char   sBgnLoc[BgnLocLen+1];
    char   sCenLen[CenLenLen+1];
  EXEC SQL END DECLARE SECTION;
    FILE   *fp;
    int    iRecNum=0;
    long   iRecAmt=0;

/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin CbsF1052OToDb.\n" );
/*
**  检查输入参数个数
*/
  ClearStr( sMsgTyp );
  ClearStr( sRspCod );
  ClearStr( sRspMsg );

  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "参数个数错" );
    bpErrorLog( trdata, "CbsF1052OToDb: 参数个数错!" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "参数个数错" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  初始化变量
*/
  ClearStr( sFilNam );
  ClearStr( sMsgSqn );
  ClearStr( sTraKnd );
  ClearStr( sSndBNo );
  ClearStr( sSndDat );
  ClearStr( sVchId  );
  ClearStr( sOIFlag );
  ClearStr( sBilSts );
  ClearStr( sMsgId  );
  ClearStr( sTxnKnd );
  ClearStr( sTxnAmt );
  ClearStr( sTraTm  );
  ClearStr( sClrDat );
  ClearStr( sCcyCod );
  ClearStr( sSvrCod );
  ClearStr( sCenTm  );
  ClearStr( sCenLog );
  ClearStr( sThdTm  );
  ClearStr( sThdLog );
  ClearStr( sRtnCod );
  ClearStr( sCshFlg );
  ClearStr( sSmrCod );
  ClearStr( sUsgCod );
  ClearStr( sRSdFlg );
  ClearStr( sAccFlg );
  ClearStr( sTBusTp );
  ClearStr( sCardFg );
  ClearStr( sAccKnd );
  ClearStr( sFeeTyp );
  ClearStr( sPayFuc );
  ClearStr( sAuthCd );
  ClearStr( sPayLvl );
  ClearStr( sSOpnBk );
  ClearStr( sSndNod );
  ClearStr( sSndAct );
  ClearStr( sSndNm  );
  ClearStr( sSndAdr );
  ClearStr( sRcvBNo );
  ClearStr( sROpnBk );
  ClearStr( sRcvNod );
  ClearStr( sRcvAct );
  ClearStr( sRcvNm  );
  ClearStr( sRcvAdr );
  ClearStr( sAgrNo  );
  ClearStr( sSmr    );
  ClearStr( sSecKey );
  ClearStr( sBrNo   );
  ClearStr( sNodNo );
  ClearStr( sLogNo  );
  ClearStr( sActFlg );
  ClearStr( sBokAct );
  ClearStr( sDskNo  );
  ClearStr( sActDat );
  ClearStr( sTTxnCd );
  ClearStr( sHTxnCd );
  ClearStr( sHTxnSt );
  ClearStr( sIsTxn  );
  ClearStr( sTxnObj );
  ClearStr( sTlrId  );
/*
**  部分数据常量
*/
  if( etfGetChildValue(TrNode, "TraKnd", sTraKnd, TraKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TraKnd】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TraKnd】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【TraKnd】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "SndBNo", sSndBNo, SndBNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【SndBNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【SndBNo】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【SndBNo】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【ActDat】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【ActDat】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【ActDat】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  strcpy( sSndDat, sActDat );
  if( etfGetChildValue(TrNode, "OIFlag", sOIFlag, OIFlagLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【OIFlag】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【OIFlag】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【OIFlag】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "MsgId", sMsgId, MsgIdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【MsgId】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【MsgId】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【MsgId】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnKnd", sTxnKnd, TxnKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TxnKnd】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TxnKnd】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【TxnKnd】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TraTm", sTraTm, TraTmLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TraTm】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TraTm】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【TraTm】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CcyCod", sCcyCod, CcyCodLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【CcyCod】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【CcyCod】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【CcyCod】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "SvrCod", sSvrCod, SvrCodLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【SvrCod】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【SvrCod】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【SvrCod】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CshFlg", sCshFlg, CshFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【CshFlg】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【CshFlg】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【CshFlg】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "RsdFlg", sRSdFlg, RSdFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【RsdFlg】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【RsdFlg】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【RsdFlg】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "AccFlg", sAccFlg, AccFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【AccFlg】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【AccFlg】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【AccFlg】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CardFg", sCardFg, CardFgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【CardFg】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【CardFg】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【CardFg】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "AccKnd", sAccKnd, AccKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【AccKnd】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【AccKnd】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【AccKnd】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "FeeTyp", sFeeTyp, FeeTypLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【FeeTyp】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【FeeTyp】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【FeeTyp】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "PayFuc", sPayFuc, PayFucLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【PayFuc】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【PayFuc】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【PayFuc】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "PayLvl", sPayLvl, PayLvlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【PayLvl】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【PayLvl】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【PayLvl】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "SOpnBk", sSOpnBk, SOpnBkLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【SOpnBk】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【SOpnBk】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【SOpnBk】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【NodNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【NodNo】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【NodNo】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActNo", sSndAct, ActNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【ActNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【ActNo】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【ActNo】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActNm", sSndNm, SndNmLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【ActNm】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【ActNm】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【ActNm】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  strcpy( sSecKey, "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
  if ( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【BrNo】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【BrNo】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【BrNo】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  sprintf( sSndNod, "%09s", sNodNo );
  strcpy( sRcvNod, "000000000" );
  strcpy( sDskNo, "AAAAAAAAAAAA" );
  if ( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TxnCnl】错误" );
    bpErrorLog( trdata, "CbsFDtlToDb:获取节点【TxnCnl】错误!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "获取节点【TxnCnl】错误" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  根据分行号取交易渠道
*/
  ClearStr( sCnlSub  );
  EXEC SQL select CnlSub
             into :sCnlSub
             from CbsBnkInf
            where BrNo=:sBrNo;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog( trdata, "CbsF1052OToDb:获取归属交易渠道、会计分录序号出错，发起分行行号:【%s】!\n", sBrNo );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "获取归属交易渠道、会计分录序号出错" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  sprintf( sFName, "%s/%s/%s", getenv("WORKDIR"), Step_Arg1, Step_Arg2 );
  strcpy( sFilNam, Step_Arg2 );
  fp =fopen( sFName, "r" );
  if( fp == NULL ) {
    bpAddResult( TrNode, "CBS999", "打开数据文件错" );
    bpErrorLog( trdata, "CbsF1052OToDb:打开数据文件【%s】失败!\n", sFName );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "打开数据文件错" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    fclose( fp );
    return( -1 );
  }

  iRecNum=0;
  while( !feof( fp ) ) {
/*
**  利用前置流水号作为信息序号、凭证提交号
*/
    ClearStr( sLogNo  );
    ClearStr( sMsgSqn );
    ClearStr( sVchId  );
    ClearStr( sTTxnCd );
    ClearStr( sHTxnCd );
    ClearStr( sHTxnSt );
    ClearStr( sIsTxn  );
    ClearStr( sTxnObj );
    ClearStr( sActFlg );
    ClearStr( sBokAct );
    ClearStr( sBilSts );
    ClearStr( sRtnCod );
/*
**  变量初始值
*/
    strcpy( sBilSts, "P" );
    if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
      bpErrorLog( trdata, "CbsFileToDb:取前置流水号错，文件名【%s】!\n", sFName );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "取前置流水号错，文件名【%s】!\n", sFName );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
      fclose( fp );
      return( -1 );
    }

    sprintf( sMsgSqn, "%s%s", SYSID, sLogNo+2 );
    memcpy( sVchId, sLogNo+6, 8 );

    ClearStr( sRec    );
    ClearStr( sRcvBNo );
    ClearStr( sROpnBk );
    ClearStr( sRcvAct );
    ClearStr( sRcvNm  );
    ClearStr( sTxnAmt );
    ClearStr( sTBusTp );
    ClearStr( sUsgCod );
    ClearStr( sSmrCod );
    ClearStr( sSmr    );
    fgets( sRec, RecLen, fp );
    memcpy( sRcvBNo, sRec+RcvBNoOffset, RcvBNoLen );
    if( strlen( sRcvBNo )==0 ) break;
    if( strlen( sRec ) !=RecDatLen ) {
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "文件【%s】第【%d】笔有误!", sFilNam, iRecNum+1 );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
      fclose( fp );
      return( -1 );
    }
    memcpy( sROpnBk, sRec+ROpnBkOffset, ROpnBkLen );
    memcpy( sRcvAct, sRec+RcvActOffset, RcvActLen );
    memcpy( sRcvNm,  sRec+RcvNmOffset,  RcvNmLen  );
    memcpy( sTxnAmt, sRec+TxnAmtOffset, TxnAmtLen );
    memcpy( sTBusTp, sRec+TBusTpOffset, TBusTpLen );
    memcpy( sUsgCod, sRec+UsgCodOffset, UsgCodLen );
    memcpy( sSmrCod, sRec+SmrCodOffset, SmrCodLen );
    memcpy( sSmr,    sRec+SmrOffset,    SmrLen    );

    hdelallspace( sRcvNm );
    hdelallspace( sSmr );

    if( memcmp(sRcvBNo,BOCSGN,3)==0 ) {
      strcpy( sBilSts, "B" );
      strcpy( sTTxnCd, "465851" );
      strcpy( sHTxnCd, "465895" );
      strcpy( sHTxnSt, "U" );
      strcpy( sIsTxn, "Y" );
      strcpy( sTxnObj, "OFRTCBS5" );
      if( memcmp(sRcvAct,"071",3)==0 ) {
        EXEC SQL select ActNo
                   into :sBokAct
                   from SavOldAct
                  where OldAct =:sRcvAct;
        if( SQLCODE == SQL_SUCCESS ) {
          strcpy( sActFlg, "1" );
        } else {
          bpErrorLog( trdata, "CbsFDtlToDb:帐号【%s】新旧帐号对照表不存在!\n", sRcvAct );
          strcpy( sBilSts, "E" );
          strcpy( sRtnCod, "001O6017" );
          strcpy( sIsTxn, "N" );
        }
      } else { 
        EXEC SQL select BgnLoc, CenLen
                   into :sBgnLoc, :sCenLen
                   from StpBinInf
                  where CrdBin = substr( :sRcvAct, 1, 6 );
        if( SQLCODE == SQL_SUCCESS ) {
          strcpy( sActFlg, "2" );
        }  else {
          if( ( strlen(sRcvAct)==ActNoLen ) && ( memcmp(sRcvAct+AreaCdLen,"9",1)==0 ) ) {
            if( ( memcmp(sRcvAct+ActNoLen-VchTypLen,"209",VchTypLen)==0 )||( memcmp(sRcvAct+ActNoLen-VchTypLen,"229",VchTypLen)==0 ) ) { /* 卡备用金帐号 */
              strcpy( sActFlg, "2" );
            } else {
              strcpy( sActFlg, "1" );
            }
          }  else {
            strcpy( sActFlg, "0" );
          }
        }
        memcpy( sBokAct, sRcvAct, ActNoLen );
      }
/*
**  根据分行号和交易渠道获取电子柜员号
*/
      if( strcmp( sBilSts, "E") !=0 ) {
        if( sqnGetDumTlr( sBrNo, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
          bpErrorLog( trdata, "CbsF1052OToDb:取前置电子柜员号错【%s】【%s】【%s】!\n", sBrNo, sTxnCnl, sCnlSub );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "取前置电子柜员号错" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          fclose( fp );
          return( -1 );
        }
      }
    }
    EXEC SQL insert into CbsBchJnl( FilNam,MsgSqn,TraKnd,SndBNo,SndDat,VchId,OIFlag,BilSts,MsgId,TxnKnd,TxnAmt,TraTm,ClrDat,CcyCod,SvrCod,CenTm,CenLog,ThdTm,ThdLog,RtnCod,CshFlg,SmrCod,UsgCod,RSdFlg,AccFlg,TBusTp,CardFg,AccKnd,FeeTyp,PayFuc,AuthCd,PayLvl,SOpnBk,SndNod,SndAct,SndNm,SndAdr,RcvBNo,ROpnBk,RcvNod,RcvAct,RcvNm,RcvAdr,AgrNo,Smr,SecKey,BrNo,NodNo,LogNo,ActFlg,BokAct,DskNo,ActDat,TTxnCd,HTxnCd,HTxnSt,IsTxn,TxnObj,TlrId )
                            values( :sFilNam,:sMsgSqn,:sTraKnd,:sSndBNo,:sSndDat,:sVchId,:sOIFlag,:sBilSts,:sMsgId,:sTxnKnd,:sTxnAmt,:sTraTm,:sClrDat,:sCcyCod,:sSvrCod,:sCenTm,:sCenLog,:sThdTm,:sThdLog,:sRtnCod,:sCshFlg,:sSmrCod,:sUsgCod,:sRSdFlg,:sAccFlg,:sTBusTp,:sCardFg,:sAccKnd,:sFeeTyp,:sPayFuc,:sAuthCd,:sPayLvl,:sSOpnBk,:sSndNod,:sSndAct,:sSndNm,:sSndAdr,:sRcvBNo,:sROpnBk,:sRcvNod,:sRcvAct,:sRcvNm,:sRcvAdr,:sAgrNo,:sSmr,:sSecKey,:sBrNo,:sNodNo,:sLogNo,:sActFlg,:sBokAct,:sDskNo,:sActDat,:sTTxnCd,:sHTxnCd,:sHTxnSt,:sIsTxn,:sTxnObj,:sTlrId );
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "CbsF1052OToDb:insert【CbsBchJnl】出错【%d】-文件【%s】!\n", SQLCODE, sFName );
      bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsBchJnl】出错" );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      strcpy( sRspMsg, "数据入库失败" );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
/**
bpErrorLog( trdata, "数据-1-内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", \
sFilNam, sMsgSqn, sTraKnd, sSndBNo, sSndDat, sVchId, sBilSts, sOIFlag, sMsgId, sTxnKnd );
bpErrorLog( trdata, "数据-2-内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", \
sTxnAmt, sTraTm,  sCcyCod, sSvrCod, sCshFlg, sSmrCod, sUsgCod, sRSdFlg, sAccFlg, sTBusTp );
bpErrorLog( trdata, "数据-3-内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", \
sCardFg, sAccKnd, sFeeTyp,sPayFuc, sSOpnBk, sSndNod, sSndAct, sSndNm, sRcvBNo, sROpnBk );
bpErrorLog( trdata, "数据-4-内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", \
sRcvAct, sRcvNm, sSmr, sSecKey, sBrNo, sNodNo, sLogNo, sDskNo, sTxnCnl, sActFlg );
**/
      fclose( fp );
      return( -1 );
    }
/*
**  计算总笔数和总金额，提供核对功能
*/
    iRecNum=iRecNum+1;
    iRecAmt=iRecAmt+atoi(sTxnAmt);
  }

  ClearStr( sRecNum );
  ClearStr( sRecAmt );
  sprintf( sRecNum, "%010d", iRecNum );
  sprintf( sRecAmt, "%016d", iRecAmt );
  etfAddOrRepNode( TrNode, "RecNum", sRecNum, TotNumLen );
  etfAddOrRepNode( TrNode, "RecAmt", sRecAmt, TotAmtLen );

  fclose( fp );
  strcpy( sMsgTyp, "N" );
  strcpy( sRspCod, "000000" );
  strcpy( sRspMsg, "交易成功" );
  etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
  etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
  etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
  bpTraceLog( trdata, "End CbsF1052OToDb.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsMsgFilToDb
  Description       : 将信息文件入库
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int CbsMsgFilToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sMsgTyp[MsgTypLen+1];
    char   sRspCod[RspCodLen+1];
    char   sRspMsg[RspMsgLen+1];

    char   sMsgId[MsgIdLen+1];
    char   sTxnKnd[TxnKndLen+1];
    char   sSysId[SysIdLen+1];
    char   sWorkDt[WorkDtLen+1];
    char   sBchNo[BchNoLen+1];
    char   sFSize[FSizeLen+1];
/*
**  行号数据文件
*/
    char   sBankNo[BankNoLen+1];
    char   sSwftNo[SwftNoLen+1];
    char   sCityCd[CityCdLen+1];
    char   sBlArea[BlAreaLen+1];
    char   sDirBNo[DirBNoLen+1];
    char   sBnkTyp[BnkTypLen+1];
    char   sBankNm[BankNmLen+1];
    char   sSimBNm[SimBNmLen+1];
    char   sSecBNo[SecBNoLen+1];
    char   sAdr[AdrLen+1];
    char   sPosCod[PosCodLen+1];
    char   sTelNo[TelNoLen+1];
    char   sFaxNo[FaxNoLen+1];
    char   sEMail[EMailLen+1];
    char   sComman[CommanLen+1];
    char   sDirFlg[DirFlgLen+1];
    char   sCnpsFg[CnpsFgLen+1];
    char   sEffDat[EffDatLen+1];
    char   sIvdDat[IvdDatLen+1];
    char   sReMark[ReMarkLen+1];
/*
**  银行业务开通信息
*/
    char   sCcyCod[CcyCodLen+1];
/*
**  系统代码信息
*/
    char   sCodTyp[CodTypLen+1];
    char   sCode[CodeLen+1];
    char   sCodSmr[CodSmrLen+1];
/*
**  系统号信息
*/
    char   sSysNam[SysNamLen+1];
    char   sIdType[IdTypeLen+1];
/*
**  地区代码信息
*/
    char   sCityNm[CityNmLen+1];
    char   sUpgCod[UpgCodLen+1];
    char   sCityFg[CityFgLen+1];
/*
**  机构信息
*/
    char   sOrgCod[OrgCodLen+1];
    char   sOrgNam[OrgNamLen+1];
    char   sOrgAct[OrgActLen+1];
    char   sOrgANm[OrgANmLen+1];
    char   sTBusTp[TBusTpLen+1];
  EXEC SQL END DECLARE SECTION;
    char   sMsgFilLst[FNameLen+1];
    char   sTmpFil[FilNamLen+1];
    char   sFilNam[FilNamLen+1];
    char   sMsgFil[FNameLen+1];
    FILE   *msg_fp, *mlst_fp;
    int    iFSize=0;
    char   sFlag[2];

/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin CbsMsgFilToDb.\n" );
/*
**  检查输入参数个数
*/
  ClearStr( sMsgTyp );
  ClearStr( sRspCod );
  ClearStr( sRspMsg );

  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "参数个数错" );
    bpErrorLog( trdata, "CbsMsgFilToDb: 参数个数错!" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "参数个数错" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  初始化变量
*/
  ClearStr( sMsgFilLst );
  sprintf( sMsgFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg1 );
  mlst_fp =fopen( sMsgFilLst, "r" );
  if( mlst_fp == NULL ) {
    fclose( mlst_fp );
    bpAddResult( TrNode, "CBS999", "打开信息列表文件错" );
    bpErrorLog( trdata, "CbsMsgFilToDb:打开信息列表文件【%s】失败!\n", sMsgFilLst );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "打开信息列表文件【%s】错", Step_Arg1 );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  while( !feof( mlst_fp ) ) {
    ClearStr( sTmpFil );
    ClearStr( sFilNam );
    ClearStr( sMsgFil );
    fgets( sTmpFil, FNmLstLen, mlst_fp );
    memcpy( sFilNam, sTmpFil, FNmLstLen-2 );
    if( strlen(sFilNam)==0 ) {
      bpErrorLog( trdata, "CbsMsgFilToDb:本次文件列表处理完毕!\n" );
      break;
    }
    bpErrorLog( trdata, "CbsMsgFilToDb:正在处理文件【%s】!\n", sFilNam );
    ClearStr( sMsgId  );
    ClearStr( sTxnKnd );
    ClearStr( sSysId  );
    ClearStr( sWorkDt );
    ClearStr( sBchNo  );
    ClearStr( sFSize  );
    memcpy( sMsgId,  sFilNam+MsgIdOffset,  MsgIdLen  );
    memcpy( sTxnKnd, sFilNam+TxnKndOffset, TxnKndLen );
    memcpy( sSysId,  sFilNam+SysIdOffset,  SysIdLen  );
    memcpy( sWorkDt, sFilNam+WorkDtOffset, WorkDtLen );
    memcpy( sBchNo,  sFilNam+BchNoOffset,  BchNoLen  );
    memcpy( sFSize,  sFilNam+FSizeOffset,  FSizeLen  );

    sprintf( sMsgFil, "%s/%s/%s", getenv("WORKDIR"), Step_Arg2, sFilNam );
    iFSize=0;
    msg_fp =fopen( sMsgFil, "r" );
    if( msg_fp == NULL ) {
      bpAddResult( TrNode, "CBS999", "打开信息文件错" );
      bpErrorLog( trdata, "CbsMsgFilToDb:打开信息文件【%s】失败!\n", sMsgFil );
      fclose( mlst_fp );
      fclose( msg_fp );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "打开信息文件【%s】错", sMsgFil );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
      return( -1 );
    }
    iFSize=hfgetsize( msg_fp );
    if( iFSize != atol( sFSize ) ) {
      bpErrorLog( trdata, "CbsMsgFilToDb:信息文件【%s】不完整!\n", sMsgFil );
      fclose( mlst_fp );
      fclose( msg_fp );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "信息文件【%s】不完整", sMsgFil );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
      return( -1 );
    }
    ClearStr( sFlag );
    strcpy( sFlag, "0" );
/*
**  根据不同的业务类型分别处理
*/
    if( strcmp( sTxnKnd, "BANKCD" ) == 0 ) {   /*行号文件*/
      EXEC SQL delete from CbsBankCd;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:清理数据表【CbsBankCd】错误【%d】!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "清理数据表【CbsBankCd】错误【%d】", SQLCODE );
        etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
        etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
        etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
        return( -1 );
      }
      while( !feof( msg_fp ) ) {
        ClearStr( sBankNo );
        ClearStr( sSwftNo );
        ClearStr( sSysId  );
        ClearStr( sCityCd );
        ClearStr( sBlArea );
        ClearStr( sDirBNo );
        ClearStr( sBnkTyp );
        ClearStr( sBankNm );
        ClearStr( sSimBNm );
        ClearStr( sSecBNo );
        ClearStr( sAdr    );
        ClearStr( sPosCod );
        ClearStr( sTelNo  );
        ClearStr( sFaxNo  );
        ClearStr( sEMail  );
        ClearStr( sComman );
        ClearStr( sDirFlg );
        ClearStr( sCnpsFg );
        ClearStr( sEffDat );
        ClearStr( sIvdDat );
        ClearStr( sReMark );
        if ( strcmp(sFlag,"0")==0 ) {
          fscanf( msg_fp, "%[^|]", sBankNo );
          strcpy( sFlag, "1" );
        } else {
          fscanf( msg_fp, "|\n%[^|]", sBankNo );
        }  
        hdelbothspace( sBankNo );
        if( strlen( sBankNo ) ==0 ) break;
/*
        fscanf( msg_fp, "%[^|]",  sBankNo );
*/
        fscanf( msg_fp, "|%[^|]", sSwftNo );
        fscanf( msg_fp, "|%[^|]", sSysId  );
        fscanf( msg_fp, "|%[^|]", sCityCd );
        fscanf( msg_fp, "|%[^|]", sBlArea );
        fscanf( msg_fp, "|%[^|]", sDirBNo );
        fscanf( msg_fp, "|%[^|]", sBnkTyp );
        fscanf( msg_fp, "|%[^|]", sBankNm );
        fscanf( msg_fp, "|%[^|]", sSimBNm );
        fscanf( msg_fp, "|%[^|]", sSecBNo );
        fscanf( msg_fp, "|%[^|]", sAdr    );
        fscanf( msg_fp, "|%[^|]", sPosCod );
        fscanf( msg_fp, "|%[^|]", sTelNo  );
        fscanf( msg_fp, "|%[^|]", sFaxNo  );
        fscanf( msg_fp, "|%[^|]", sEMail  );
        fscanf( msg_fp, "|%[^|]", sComman );
        fscanf( msg_fp, "|%[^|]", sDirFlg );
        fscanf( msg_fp, "|%[^|]", sCnpsFg );
        fscanf( msg_fp, "|%[^|]", sEffDat );
        fscanf( msg_fp, "|%[^|]", sIvdDat );
        fscanf( msg_fp, "|%[^|]", sReMark );
        hdelbothspace( sIvdDat );
        if( strcmp( sIvdDat, "" )==0 ) {
          strcpy( sIvdDat, "99999999" );
        }
        EXEC SQL insert into CbsBankCd( BankNo,SwftNo,SysId,CityCd,BlArea,DirBNo,BnkTyp,BankNm,SimBNm,SecBNo,Adr,PosCod,TelNo,FaxNo,EMail,Comman,DirFlg,CnpsFg,EffDat,IvdDat,ReMark )
                                values( :sBankNo,:sSwftNo,:sSysId,:sCityCd,:sBlArea,:sDirBNo,:sBnkTyp,:sBankNm,:sSimBNm,:sSecBNo,:sAdr,:sPosCod,:sTelNo,:sFaxNo,:sEMail,:sComman,:sDirFlg,:sCnpsFg,:sEffDat,:sIvdDat,:sReMark );
        if( SQLCODE != SQL_SUCCESS ) {
bpErrorLog( trdata, "读入内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", \
            sBankNo,sSwftNo,sSysId,sCityCd,sBlArea,sDirBNo,sBnkTyp,sBankNm,sSimBNm,sSecBNo,sAdr,sPosCod,sTelNo,sFaxNo,sEMail,sComman,sDirFlg,sCnpsFg,sEffDat,sIvdDat,sReMark );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert【CbsBankCd】出错【%d】-文件【%s】!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsBankCd】出错" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert【CbsBankCd】出错" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "BTXNCD" ) == 0 ) {   /* 银行业务开通信息 */
      EXEC SQL delete from CbsBTxnCd;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:清理数据表【CbsBTxnCd】错误【%d】!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "清理数据表【CbsBTxnCd】错误【%d】", SQLCODE );
        etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
        etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
        etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
        return( -1 );
      }
      while( !feof( msg_fp ) ) {
        ClearStr( sBankNo );
        ClearStr( sTxnKnd );
        ClearStr( sCcyCod  );
        ClearStr( sEffDat );
        ClearStr( sIvdDat );
        if ( strcmp(sFlag,"0")==0 ) {
          fscanf( msg_fp, "%[^|]", sBankNo );
          strcpy( sFlag, "1" );
        } else {
          fscanf( msg_fp, "|\n%[^|]", sBankNo );
        }  
        hdelbothspace( sBankNo );
        if( strlen( sBankNo ) ==0 ) break;
        fscanf( msg_fp, "|%[^|]", sTxnKnd );
        fscanf( msg_fp, "|%[^|]", sCcyCod );
        fscanf( msg_fp, "|%[^|]", sEffDat );
        fscanf( msg_fp, "|%[^|]", sIvdDat );
        hdelbothspace( sIvdDat );
        if( strcmp( sIvdDat, "" )==0 ) {
          strcpy( sIvdDat, "99999999" );
        }
        EXEC SQL insert into CbsBTxnCd( BankNo, TxnKnd, CcyCod, EffDat, IvdDat ) values( :sBankNo, :sTxnKnd, :sCcyCod, :sEffDat, :sIvdDat );
        if( SQLCODE != SQL_SUCCESS ) {
bpErrorLog( trdata, "读入内容:【%s】【%s】【%s】【%s】【%s】!\n", sBankNo,sTxnKnd, sCcyCod, sEffDat,sIvdDat );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert【CbsBTxnCd】出错【%d】-文件【%s】!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsBTxnCd】出错" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert【CbsBTxnCd】出错" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "CODECD" ) == 0 ) {   /* 系统代码信息 */
      EXEC SQL delete from CbsCodeCd where CodTyp!='TXNKND';
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:清理数据表【CbsCodeCd】错误【%d】!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "清理数据表【CbsCodeCd】错误【%d】", SQLCODE );
        etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
        etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
        etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
        return( -1 );
      }
      while( !feof( msg_fp ) ) {
        ClearStr( sCodTyp );
        ClearStr( sCode );
        ClearStr( sCodSmr  );
        ClearStr( sEffDat );
        ClearStr( sIvdDat );
        if ( strcmp(sFlag,"0")==0 ) {
          fscanf( msg_fp, "%[^|]", sCodTyp );
          strcpy( sFlag, "1" );
        } else {
          fscanf( msg_fp, "|\n%[^|]", sCodTyp );
        }  
        hdelbothspace( sCodTyp );
        if( strlen( sCodTyp ) ==0 ) break;
        fscanf( msg_fp, "|%[^|]", sCode );
        fscanf( msg_fp, "|%[^|]", sCodSmr );
        fscanf( msg_fp, "|%[^|]", sEffDat );
        fscanf( msg_fp, "|%[^|]", sIvdDat );
        hdelbothspace( sIvdDat );
        if( strcmp( sIvdDat, "" )==0 ) {
          strcpy( sIvdDat, "99999999" );
        }
        EXEC SQL insert into CbsCodeCd( CodTyp, Code, CodSmr, EffDat, IvdDat ) values( :sCodTyp, :sCode, :sCodSmr, :sEffDat, :sIvdDat );
        if( SQLCODE != SQL_SUCCESS ) {
bpErrorLog( trdata, "读入内容:【%s】【%s】【%s】【%s】【%s】!\n", sCodTyp,sCode, sCodSmr, sEffDat,sIvdDat );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert【CbsCodeCd】出错【%d】-文件【%s】!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsCodeCd】出错" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert【CbsCodeCd】出错" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "SYIDCD" ) == 0 ) {   /* 系统号信息 */
      EXEC SQL delete from CbsSyIdCd;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:清理数据表【CbsSyIdCd】错误【%d】!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "清理数据表【CbsSyIdCd】错误【%d】", SQLCODE );
        etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
        etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
        etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
        return( -1 );
      }
      while( !feof( msg_fp ) ) {
        ClearStr( sSysId  );
        ClearStr( sSysNam );
        ClearStr( sBlArea );
        ClearStr( sIdType );
        ClearStr( sEffDat );
        ClearStr( sIvdDat );
        if ( strcmp(sFlag,"0")==0 ) {
          fscanf( msg_fp, "%[^|]", sSysId );
          strcpy( sFlag, "1" );
        } else {
          fscanf( msg_fp, "|\n%[^|]", sSysId );
        }  
        hdelbothspace( sSysId );
        if( strlen( sSysId ) ==0 ) break;
        fscanf( msg_fp, "|%[^|]", sSysNam );
        fscanf( msg_fp, "|%[^|]", sBlArea );
        fscanf( msg_fp, "|%[^|]", sIdType );
        fscanf( msg_fp, "|%[^|]", sEffDat );
        fscanf( msg_fp, "|%[^|]", sIvdDat );
        hdelbothspace( sIvdDat );
        if( strcmp( sIvdDat, "" )==0 ) {
          strcpy( sIvdDat, "99999999" );
        }
        EXEC SQL insert into CbsSyIdCd( SysId, SysNam, BlArea, IdType, EffDat, IvdDat ) values( :sSysId, :sSysNam, :sBlArea, :sIdType, :sEffDat, :sIvdDat );
        if( SQLCODE != SQL_SUCCESS ) {
          bpErrorLog( trdata, "读入内容:【%s】【%s】【%s】【%s】【%s】【%s】!\n", sSysId, sSysNam, sBlArea, sIdType, sEffDat,sIvdDat );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert【CbsSyIdCd】出错【%d】-文件【%s】!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsSyIdCd】出错" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert【CbsSyIdCd】出错" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "AREACD" ) == 0 ) {   /* 地区代码信息 */
      EXEC SQL delete from CbsAreaCd;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:清理数据表【CbsAreaCd】错误【%d】!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "清理数据表【CbsAreaCd】错误【%d】", SQLCODE );
        etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
        etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
        etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
        return( -1 );
      }
      while( !feof( msg_fp ) ) {
        ClearStr( sCityCd );
        ClearStr( sCityNm );
        ClearStr( sUpgCod );
        ClearStr( sCityFg );
        if ( strcmp(sFlag,"0")==0 ) {
          fscanf( msg_fp, "%[^|]", sCityCd );
          strcpy( sFlag, "1" );
        } else {
          fscanf( msg_fp, "|\n%[^|]", sCityCd );
        }  
        hdelbothspace( sCityCd );
        if( strlen( sCityCd ) ==0 ) break;
        fscanf( msg_fp, "|%[^|]", sCityNm );
        fscanf( msg_fp, "|%[^|]", sUpgCod );
        fscanf( msg_fp, "|%[^|]", sCityFg );
        EXEC SQL insert into CbsAreaCd( CityCd, CityNm, UpgCod, CityFg ) values( :sCityCd, :sCityNm, :sUpgCod, :sCityFg );
        if( SQLCODE != SQL_SUCCESS ) {
bpErrorLog( trdata, "读入内容:【%s】【%s】【%s】【%s】!\n", sCityCd, sCityNm, sUpgCod, sCityFg );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert【CbsAreaCd】出错【%d】-文件【%s】!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsAreaCd】出错" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert【CbsAreaCd】出错" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "ORGACD" ) == 0 ) {   /* 机构信息 */
      EXEC SQL delete from CbsCenOrg;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:清理数据表【CbsCenOrg】错误【%d】!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "清理数据表【CbsCenOrg】错误【%d】", SQLCODE );
        etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
        etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
        etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
        return( -1 );
      }
      while( !feof( msg_fp ) ) {
        ClearStr( sOrgCod );
        ClearStr( sOrgNam );
        ClearStr( sCityCd );
        ClearStr( sTBusTp );
        ClearStr( sTxnKnd );
        ClearStr( sCcyCod );
        ClearStr( sBankNo );
        ClearStr( sOrgAct );
        ClearStr( sOrgANm );
        ClearStr( sTelNo  );
        ClearStr( sComman );
        ClearStr( sEffDat );
        ClearStr( sIvdDat );
        if ( strcmp(sFlag,"0")==0 ) {
          fscanf( msg_fp, "%[^|]", sOrgCod );
          strcpy( sFlag, "1" );
        } else {
          fscanf( msg_fp, "|\n%[^|]", sOrgCod );
        }  
        hdelbothspace( sOrgCod );
        if( strlen( sOrgCod ) ==0 ) break;
        fscanf( msg_fp, "|%[^|]", sOrgNam );
        fscanf( msg_fp, "|%[^|]", sCityCd );
        fscanf( msg_fp, "|%[^|]", sTBusTp );
        fscanf( msg_fp, "|%[^|]", sTxnKnd );
        fscanf( msg_fp, "|%[^|]", sCcyCod );
        fscanf( msg_fp, "|%[^|]", sBankNo );
        fscanf( msg_fp, "|%[^|]", sOrgAct );
        fscanf( msg_fp, "|%[^|]", sOrgANm );
        fscanf( msg_fp, "|%[^|]", sTelNo  );
        fscanf( msg_fp, "|%[^|]", sComman );
        fscanf( msg_fp, "|%[^|]", sEffDat );
        fscanf( msg_fp, "|%[^|]", sIvdDat );
        EXEC SQL insert into CbsCenOrg( OrgCod, OrgNam, CtyCod, SBusTy, TxnKnd, CcyCod, OrgOBnk, OrgActNo, OrgActNm, ComTel, ComMan, EffDat, EprDat )
                                values( :sOrgCod, :sOrgNam, :sCityCd, :sTBusTp, :sTxnKnd, :sCcyCod, :sBankNo, :sOrgAct, :sOrgANm, :sTelNo, :sComman, :sEffDat, :sIvdDat );
        if( SQLCODE != SQL_SUCCESS ) {
bpErrorLog( trdata, "读入内容:【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】【%s】!\n", sOrgCod, sOrgNam, sCityCd, sTBusTp, sTxnKnd, sCcyCod, sBankNo, sOrgAct, sOrgANm, sTelNo, sComman, sEffDat, sIvdDat );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert【CbsCenOrg】出错【%d】-文件【%s】!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert【CbsCenOrg】出错" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert【CbsCenOrg】出错" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    fclose( msg_fp );
  }
  fclose( mlst_fp );
  strcpy( sMsgTyp, "N" );
  strcpy( sRspCod, "000000" );
  strcpy( sRspMsg, "交易成功" );
  etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
  etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
  etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
  bpTraceLog( trdata, "End CbsMsgFilToDb.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsDtlFilChk
  Description       : 明细文件核对
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明( 为保证对帐全面，故任何一个文件不合法，则退出 )
******************************************************************************/
int CbsDtlFilChk(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sMsgId[MsgIdLen+1];
    char   sTxnKnd[TxnKndLen+1];
    char   sSysId[SysIdLen+1];
    char   sWorkDt[WorkDtLen+1];
    char   sBchNo[BchNoLen+1];
    char   sFSize[FSizeLen+1];
    char   sMsgSqn[MsgSqnLen+1];
    char   sRefMsg[MsgSqnLen+1];
    char   sTxnKndDtl[TxnKndLen+1];
    char   sTxnAmt[TxnAmtLen+1];
    char   sTraTm[TraTmLen+1];
    char   sClrBNo[ClrBNoLen+1];
    char   sSndDat[SndDatLen+1];
    char   sClrDat[ClrDatLen+1];
    char   sClrSce[ClrSceLen+1];
    char   sSSysId[SSysIdLen+1];
    char   sSndBNo[SndBNoLen+1];
    char   sRSysId[RSysIdLen+1];
    char   sRcvBNo[RcvBNoLen+1];
    char   sTraKnd[TraKndLen+1];
    char   sRefFil[RefFilLen+1];
    char   sBchSqn[BchSqnLen+1];
    char   sRefSqn[RefSqnLen+1];
    char   sCusSqn[CusSqnLen+1];
    char   sTotNum[TotNumLen+1];
    char   sTotAmt[TotAmtLen+1];
    char   sRefNum[RefNumLen+1];
    char   sRefAmt[RefAmtLen+1];
    char   sRtnCod[RtnCodLen+1];
    char   sReServ[ReServLen+1];
    char   sQryTyp[QryTypLen+1];
    char   sAreaNo[AreaNoLen+1];
    char   sCcyCod[CcyCodLen+1];
    char   sSvrCod[SvrCodLen+1];
    char   sCenId[CenIdLen+1];
    char   sCusId[CusIdLen+1];
    char   sCenTm[CenTmLen+1];
    char   sCenLog[CenLogLen+1];
    char   sThdTm[ThdTmLen+1];
    char   sThdLog[ThdLogLen+1];
    char   sCshFlg[CshFlgLen+1];
    char   sSmrCod[SmrCodLen+1];
    char   sUsgCod[UsgCodLen+1];
    char   sRSdFlg[RSdFlgLen+1];
    char   sAccFlg[AccFlgLen+1];
    char   sTBusTp[TBusTpLen+1];
    char   sCardFg[CardFgLen+1];
    char   sAccKnd[AccKndLen+1];
    char   sFeeTyp[FeeTypLen+1];
    char   sPayFuc[PayFucLen+1];
    char   sAuthCd[AuthCdLen+1];
    char   sPayLvl[PayLvlLen+1];
    char   sOrgId[OrgIdLen+1];
    char   sSOpnBk[SOpnBkLen+1];
    char   sSndNod[SndNodLen+1];
    char   sSndAct[SndActLen+1];
    char   sSndNm[SndNmLen+1];
    char   sVchId[VchIdLen+1];
    char   sROpnBk[ROpnBkLen+1];
    char   sRcvNod[RcvNodLen+1];
    char   sRcvAct[RcvActLen+1];
    char   sRcvNm[RcvNmLen+1];
    char   sAgrNo[AgrNoLen+1];
    char   sSysSts[SysStsLen+1];
    char   sCreAmt[CreAmtLen+1];
    char   sCreCnt[CreCntLen+1];
    char   sDebAmt[DebAmtLen+1];
    char   sDebCnt[DebCntLen+1];
    char   sCTraKnd[CTraKndLen+1];
    char   sOSgnId[OSgnIdLen+1];
    char   sNSgnId[NSgnIdLen+1];
    char   sSmr[SmrLen+1];
    char   sSecKey[SecKeyLen+1];
    char   sTCrpCd[TCrpCdLen+1];
    char   sSvrKnd[SvrKndLen+1];
    char   sTBilNo[TBilNoLen+1];   /*税票号码*/
    char   sTaxNo[TaxNoLen+1];     /*纳税人编码*/
    char   sTaxer[TaxerLen+1];     /*纳税人名称*/
    char   sTaxLvl[TaxLvlLen+1];   /*预算级次*/
    char   sTSubCd[TSubCdLen+1];   /*预算科目*/
    char   sTOrgCd[TOrgCdLen+1];   /*征收机关代码*/
    char   sTActDt[TActDtLen+1];   /*税票限缴日期*/
    char   sSvrMsg[SvrMsgLen+1];
    char   sSndNm2[SndNm2Len+1];
    char   sSndAdr[SndAdrLen+1];
    char   sRcvNm2[RcvNm2Len+1];
    char   sRcvAdr[RcvAdrLen+1];
    char   sBrNo[BrNoLen+1];
    char   sNodNo[NodNoLen+1];
    char   sActDat[ActDatLen+1];
    char   sBilSts[BilStsLen+1];
    char   sLogNo[LogNoLen+1];
    char   sOIFlag[OIFlagLen+1];
    char   sTRspCd[RspCodLen+1];
  EXEC SQL END DECLARE SECTION;
    char   sDtlFilLst[FNameLen+1];
    char   sTmpFil[FilNamLen+1];
    char   sFilNam[FilNamLen+1];
    char   sDtl8583Fil[FNameLen+1];
    char   sDtlFil[FNameLen+1];
    char   sRptDir[FNameLen+1];
    char   sDtlDir[FNameLen+1];
    char   sChkFil[FNameLen+1];
    char   sSucFlg[SucFlgLen+1];
    char   sResult[ResultLen+1];
    FILE   *dtl_fp, *dlst_fp, *chk_fp;
    int    iFSize=0,ret=0,iOrnCnt,i=1;
    char   sTmpDat[15];
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin CbsDtlFilChk.\n" );
/*
**  检查输入参数个数
*/
  if( Step_Args_Num != 5 ) {
    bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 参数个数错" );
    bpErrorLog( trdata, "CbsDtlFilChk: 参数个数错!" );
    return( -1 );
  }
/*
**  部分常量赋值
*/
  ClearStr( sSucFlg );
  ClearStr( sBrNo   );
  ClearStr( sActDat );
  ClearStr( sNodNo  );
  ClearStr( sRptDir );
  ClearStr( sChkFil );
  strcpy( sSucFlg, "Y" );
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【BrNo】错误" );
    bpErrorLog( trdata, "CbsDtlFilChk:获取节点【BrNo】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【ActDat】错误" );
    bpErrorLog( trdata, "CbsDtlFilChk:获取节点【ActDat】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【NodNo】错误" );
    bpErrorLog( trdata, "CbsDtlFilChk:获取节点【NodNo】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "RptDir", sRptDir, FNameLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【RptDir】错误" );
    bpErrorLog( trdata, "CbsDtlFilChk:获取节点【RptDir】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "IcsDtlDir", sDtlDir, FNameLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【DtlDir】错误" );
    bpErrorLog( trdata, "CbsDtlFilChk:获取节点【DtlDir】错误!\n" );
    return( -1 );
  }
/*
**  生成对帐结果文件表头
*/
  sprintf( sChkFil, "%s/%s", getenv("WORKDIR"), Step_Arg5 );
  chk_fp =fopen( sChkFil, "w" );
  if( chk_fp == NULL ) {
    fclose( chk_fp );
    bpAddResult( TrNode, "CBS999", "打开对帐结果文件错" );
    bpErrorLog( trdata, "CbsDtlFilChk:打开对帐文件结果【%s】失败!\n", sChkFil );
    return( -1 );
  }
  fprintf( chk_fp, "[1]:RptHead=对帐差错报表\n" );
  fprintf( chk_fp, "[2]:TxnKnd=%s|ClrDat=%s|\n", Step_Arg3, Step_Arg4 );
/*
**  初始化变量
*/
  ClearStr( sDtlFilLst );
  sprintf( sDtlFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg1 );
  dlst_fp =fopen( sDtlFilLst, "r" );
  if( dlst_fp == NULL ) {
    fclose( chk_fp );
    fclose( dlst_fp );
    bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 打开对帐列表文件错" );
    bpErrorLog( trdata, "CbsDtlFilChk:打开对帐列表文件【%s】失败!\n", sDtlFilLst );
    return( -1 );
  }
  while( !feof( dlst_fp ) ) {
    ClearStr( sTmpFil );
    ClearStr( sFilNam );
    ClearStr( sDtl8583Fil );
    ClearStr( sDtlFil );
    fgets( sTmpFil, FNmLstLen, dlst_fp );
    memcpy( sFilNam, sTmpFil, FNmLstLen-2 );
    if( strlen(sFilNam)==0 ) {
      bpErrorLog( trdata, "CbsDtlFilChk:本次文件列表处理完毕!\n" );
      break;
    }
    bpErrorLog( trdata, "CbsDtlFilChk:正在处理文件【%s】!\n", sFilNam );
    ClearStr( sMsgId  );
    ClearStr( sTxnKnd );
    ClearStr( sTraKnd );
    ClearStr( sSysId  );
    ClearStr( sWorkDt );
    ClearStr( sBchNo  );
    ClearStr( sFSize  );
    ClearStr( sTraTm  );
    memcpy( sMsgId,  sFilNam+MsgIdOffset,  MsgIdLen  );
    memcpy( sTxnKnd, sFilNam+TxnKndOffset, TxnKndLen );
    memcpy( sSysId,  sFilNam+SysIdOffset,  SysIdLen  );
    memcpy( sWorkDt, sFilNam+WorkDtOffset, WorkDtLen );
    memcpy( sBchNo,  sFilNam+BchNoOffset,  BchNoLen  );
    memcpy( sFSize,  sFilNam+FSizeOffset,  FSizeLen  );
    memcpy( sTraKnd, sTxnKnd, TraKndLen );
    sprintf( sTraTm, "%s%s", sWorkDt+4, "999999" );
/*
**  检查文件完整性
*/
    sprintf( sDtl8583Fil, "%s/%s/%s", getenv("WORKDIR"), sDtlDir, sFilNam );
    sprintf( sDtlFil, "%s%s", sDtl8583Fil, ".dat" );
    iFSize=0;
    dtl_fp =fopen( sDtl8583Fil, "r" );
    if( dtl_fp == NULL ) {
      fclose( chk_fp );
      fclose( dlst_fp );
      fclose( dtl_fp );
      bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 打开对帐文件错" );
      bpErrorLog( trdata, "CbsDtlFilChk:打开数据文件【%s】失败!\n", sDtlFil );
      return( -1 );
    }
    iFSize=hfgetsize( dtl_fp );
    if( iFSize != atol( sFSize ) ) {
      fclose( chk_fp );
      fclose( dlst_fp );
      fclose( dtl_fp );
      bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 对帐文件不完整" );
      bpErrorLog( trdata, "CbsDtlFilChk:对帐文件【%s】不完整!\n", sDtlFil );
      return( -1 );
    }
/*
**  将数据文件8583转换为普通文件
*/
    ret=CbsFilChg( "2", sDtl8583Fil, sDtlFil );
    if( ret!=0 ) {
      fclose( chk_fp );
      fclose( dtl_fp );
      fclose( dlst_fp );
      bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 数据文件转换异常" );
      bpErrorLog( trdata, "CbsDtlFilChk:数据文件【%s】转换异常!\n", sDtl8583Fil );
      return( -1 );
    }
/*
**  读取数据文件
*/
    dtl_fp =fopen( sDtlFil, "r" );
    if( dtl_fp == NULL ) {
      fclose( chk_fp );
      fclose( dtl_fp );
      fclose( dlst_fp );
      bpAddResult( TrNode, "CBS999", "打开数据文件错" );
      bpErrorLog( trdata, "CbsDtlFilChk:打开数据文件【%s】失败!\n", sDtlFil );
      return( -1 );
    }
/*
** 处理数据明细
*/
    while( !feof( dtl_fp ) ) {
      ClearStr( sMsgSqn  ); /*信息序号*/
      ClearStr( sRefMsg  ); /*参考信息序号*/
      ClearStr( sMsgId   ); /*报文类型标识符*/
      ClearStr( sTxnKndDtl  ); /*交易种类细分类型*/
      ClearStr( sTxnAmt  ); /*交易金额*/
      ClearStr( sTraTm   ); /*交易发起日期和时间*/
      ClearStr( sClrBNo  ); /*直接清算行*/
      ClearStr( sTmpDat  ); /*委托日期*/
      ClearStr( sSndDat  ); /*委托日期*/
      ClearStr( sClrDat  ); /*清算日期*/
      ClearStr( sQryTyp  ); /*查询通知种类标识*/
      ClearStr( sAreaNo  ); /*地区号*/
      ClearStr( sCcyCod  ); /*交易货币代码*/
      ClearStr( sSvrCod  ); /*服务点输入方式码*/
      ClearStr( sCenId   ); /*中心客户号*/
      ClearStr( sCusId   ); /*企业客户号*/
      ClearStr( sCenTm   ); /*中心交易受理日期时间*/
      ClearStr( sCenLog  ); /*中心交易受理号*/
      ClearStr( sThdTm   ); /*业务处理方处理日期时间*/
      ClearStr( sThdLog  ); /*业务处理方流水号*/
      ClearStr( sRtnCod  ); /*返回码*/
      ClearStr( sCshFlg  ); /*现金转账标识*/
      ClearStr( sSmrCod  ); /*摘要代码*/
      ClearStr( sUsgCod  ); /*资金用途代码*/
      ClearStr( sRSdFlg  ); /*重发标识*/
      ClearStr( sAccFlg  ); /*对公对私标识*/
      ClearStr( sTBusTp  ); /*业务种类*/
      ClearStr( sCardFg  ); /*卡折标识*/
      ClearStr( sAccKnd  ); /*钞户汇户标识*/
      ClearStr( sFeeTyp  ); /*手续费方式*/
      ClearStr( sPayFuc  ); /*支付工具*/
      ClearStr( sAuthCd  ); /*授权码*/
      ClearStr( sPayLvl  ); /*支付优先级*/
      ClearStr( sOrgId   ); /*原交易业务唯一标识*/
      ClearStr( sSndBNo  ); /*发起行行号*/
      ClearStr( sSOpnBk  ); /*发起人开户行行号*/
      ClearStr( sSndNod  ); /*发起行网点号*/
      ClearStr( sSndAct  ); /*发起人账号*/
      ClearStr( sSndNm   ); /*发起人名称*/
      ClearStr( sVchId   ); /*凭证提交号*/
      ClearStr( sRcvBNo  ); /*接收行行号*/
      ClearStr( sROpnBk  ); /*接收人开户行行号*/
      ClearStr( sRcvNod  ); /*接收行网点号*/
      ClearStr( sRcvAct  ); /*接收人账号*/
      ClearStr( sRcvNm   ); /*接收人名称*/
      ClearStr( sAgrNo   ); /*多方协议号*/
      ClearStr( sSysSts  ); /*系统运行状态*/
      ClearStr( sCreAmt  ); /*贷方金额*/
      ClearStr( sCreCnt  ); /*贷方笔数*/
      ClearStr( sDebAmt  ); /*借方金额*/
      ClearStr( sDebCnt  ); /*借方笔数*/
      ClearStr( sCTraKnd ); /*交易种类*/
      ClearStr( sOSgnId  ); /*旧登陆标识*/
      ClearStr( sNSgnId  ); /*新登陆标识*/
      ClearStr( sSmr     ); /*交易摘要(300)*/
      ClearStr( sSecKey  ); /*密押*/
      ClearStr( sTCrpCd  ); /*企业机构代码*/
      ClearStr( sSvrKnd  ); /*服务信息类型*/
      ClearStr( sTBilNo  ); /*税票号码*/
      ClearStr( sTaxNo   ); /*纳税人编码*/
      ClearStr( sTaxer   ); /*纳税人名称*/
      ClearStr( sTaxLvl  ); /*预算级次*/
      ClearStr( sTSubCd  ); /*预算科目*/
      ClearStr( sTOrgCd  ); /*征收机关代码*/
      ClearStr( sTActDt  ); /*税票限缴日期*/
      ClearStr( sSvrMsg  ); /*服务信息内容*/
      ClearStr( sSndNm2  ); /*附加发起人名称*/
      ClearStr( sSndAdr  ); /*发起人地址*/
      ClearStr( sRcvNm2  ); /*附加接收人名称*/
      ClearStr( sRcvAdr  ); /*接收人地址*/

      ClearStr( sBilSts  ); /*状态*/
      ClearStr( sResult );
/*
**  专门用于处理吴SIR程序中的非法字符
*/
      if ( i==1 ) {
        fscanf( dtl_fp, "%[^|]", sMsgSqn );   /*信息序号*/
        i++;
      } else {
        fscanf( dtl_fp, "|\n%[^|]", sMsgSqn );   /*信息序号*/
      }  
      hdelallspace(sMsgSqn);
      if( strlen(sMsgSqn)==0 ) {
        break;
      }
      fscanf( dtl_fp, "|%[^|]", sRefMsg  );   /*参考信息序号*/
      fscanf( dtl_fp, "|%[^|]", sMsgId   );   /*报文类型标识符*/
      fscanf( dtl_fp, "|%[^|]", sTxnKndDtl );   /*交易种类细分*/
      fscanf( dtl_fp, "|%[^|]", sTxnAmt  );   /*交易金额*/
      fscanf( dtl_fp, "|%[^|]", sTraTm   );   /*交易发起日期和时间*/
      fscanf( dtl_fp, "|%[^|]", sClrBNo  );   /*直接清算行*/
      fscanf( dtl_fp, "|%[^|]", sTmpDat  );   /*委托日期*/
      strncpy( sSndDat, sTmpDat, 8 );         /*删除低位的0*/
      fscanf( dtl_fp, "|%[^|]", sClrDat  );   /*清算日期*/
      fscanf( dtl_fp, "|%[^|]", sQryTyp  );   /*查询通知种类*/
      fscanf( dtl_fp, "|%[^|]", sAreaNo  );   /*地区号*/
      fscanf( dtl_fp, "|%[^|]", sCcyCod  );   /*交易货币代码*/
      fscanf( dtl_fp, "|%[^|]", sSvrCod  );   /*服务点输入方式码*/
      fscanf( dtl_fp, "|%[^|]", sCenId   );   /*中心客户号*/
      fscanf( dtl_fp, "|%[^|]", sCusId   );   /*企业客户号*/
      fscanf( dtl_fp, "|%[^|]", sCenTm   );   /*中心受理日期时间*/
      fscanf( dtl_fp, "|%[^|]", sCenLog  );   /*中心受理号*/
      fscanf( dtl_fp, "|%[^|]", sThdTm   );   /*业务处理方处理日期时间*/
      fscanf( dtl_fp, "|%[^|]", sThdLog  );   /*业务受理方流水号*/
      fscanf( dtl_fp, "|%[^|]", sRtnCod  );   /*返回码*/
      fscanf( dtl_fp, "|%[^|]", sCshFlg  );   /*现金转帐标志*/
      fscanf( dtl_fp, "|%[^|]", sSmrCod  );   /*摘要代码*/
      fscanf( dtl_fp, "|%[^|]", sUsgCod  );   /*资金用途代码*/
      fscanf( dtl_fp, "|%[^|]", sRSdFlg  );   /*重发标识*/
      fscanf( dtl_fp, "|%[^|]", sAccFlg  );   /*对公对私标识*/
      fscanf( dtl_fp, "|%[^|]", sTBusTp  );   /*业务种类*/
      fscanf( dtl_fp, "|%[^|]", sCardFg  );   /*卡折标识*/
      fscanf( dtl_fp, "|%[^|]", sAccKnd  );   /*钞户汇户标识*/
      fscanf( dtl_fp, "|%[^|]", sFeeTyp  );   /*收费方式*/
      fscanf( dtl_fp, "|%[^|]", sPayFuc  );   /*支付工具*/
      fscanf( dtl_fp, "|%[^|]", sAuthCd  );   /*授权码*/
      fscanf( dtl_fp, "|%[^|]", sPayLvl  );   /*支付优先级*/
      fscanf( dtl_fp, "|%[^|]", sOrgId   );   /*原数据元*/
      fscanf( dtl_fp, "|%[^|]", sSndBNo  );   /*发起行行号*/
      fscanf( dtl_fp, "|%[^|]", sSOpnBk  );   /*发起人开户行行号*/
      fscanf( dtl_fp, "|%[^|]", sSndNod  );   /*发起行网点号*/
      fscanf( dtl_fp, "|%[^|]", sSndAct  );   /*发起人账号*/
      fscanf( dtl_fp, "|%[^|]", sSndNm   );   /*发起人名称*/
      fscanf( dtl_fp, "|%[^|]", sVchId   );   /*凭证提交号*/
      fscanf( dtl_fp, "|%[^|]", sRcvBNo  );   /*接收行行号*/
      fscanf( dtl_fp, "|%[^|]", sROpnBk  );   /*接收人开户行行号*/
      fscanf( dtl_fp, "|%[^|]", sRcvNod  );   /*接收行网点号*/
      fscanf( dtl_fp, "|%[^|]", sRcvAct  );   /*接收人账号*/
      fscanf( dtl_fp, "|%[^|]", sRcvNm   );   /*接收人名称*/
      fscanf( dtl_fp, "|%[^|]", sAgrNo   );   /*协议号*/
      fscanf( dtl_fp, "|%[^|]", sSysSts  );   /*系统运行状态*/
      fscanf( dtl_fp, "|%[^|]", sCreAmt  );   /*贷方金额*/
      fscanf( dtl_fp, "|%[^|]", sCreCnt  );   /*贷方笔数*/
      fscanf( dtl_fp, "|%[^|]", sDebAmt  );   /*借方金额*/
      fscanf( dtl_fp, "|%[^|]", sDebCnt  );   /*借方笔数*/
      fscanf( dtl_fp, "|%[^|]", sCTraKnd );   /*交易种类*/
      fscanf( dtl_fp, "|%[^|]", sOSgnId  );   /*旧登陆标识*/
      fscanf( dtl_fp, "|%[^|]", sNSgnId  );   /*新登陆标识*/
      fscanf( dtl_fp, "|%[^|]", sSmr     );   /*交易摘要*/
      fscanf( dtl_fp, "|%[^|]", sSecKey  );   /*密押*/
      fscanf( dtl_fp, "|%[^|]", sTCrpCd  );   /*企业机构代码*/
      fscanf( dtl_fp, "|%[^|]", sSvrKnd  );   /*服务信息内容*/
      fscanf( dtl_fp, "|%[^|]", sTBilNo  );   /*税票号码*/
      fscanf( dtl_fp, "|%[^|]", sTaxNo   );   /*纳税人编码*/
      fscanf( dtl_fp, "|%[^|]", sTaxer   );   /*纳税人名称*/
      fscanf( dtl_fp, "|%[^|]", sTaxLvl  );   /*预算级次*/
      fscanf( dtl_fp, "|%[^|]", sTSubCd  );   /*预算科目*/
      fscanf( dtl_fp, "|%[^|]", sTOrgCd  );   /*征收机关代码*/
      fscanf( dtl_fp, "|%[^|]", sTActDt  );   /*税票限缴日期*/
/***
      fscanf( dtl_fp, "|%[^|]", sSvrMsg  );   *服务信息内容*
***/
      fscanf( dtl_fp, "|%[^|]", sSndNm2  );   /*附加发起人名称*/
      fscanf( dtl_fp, "|%[^|]", sSndAdr  );   /*发起人地址*/
      fscanf( dtl_fp, "|%[^|]", sRcvNm2  );   /*附加接收人名称*/
      fscanf( dtl_fp, "|%[^|]", sRcvAdr  );   /*接收人地址*/
/*
**  根据不同的业务类型分别处理
*/
      switch( atoi( sTxnKnd ) ) {
        case 100101:   /* 同城人民币 */
        case 100102:   /* 同城MT103 */
        case 100103:   /* 同城MT202 */
        case 100104:   /* 粤港MT103 */
        case 100105:   /* 粤港MT202 */
        case 100106:   /* 内部转账 */
        case 100201:   /* 在线支付 */
        case 300101:   /* 同城人民币退回 */
        case 300102:   /* 粤港MT103退回 */
          if( memcmp(sRcvBNo,BOCSGN,3)==0 ) {   /*检查来帐*/
            ClearStr( sOIFlag );
            strcpy( sOIFlag, "1" );
            EXEC SQL select BilSts
                       into :sBilSts
                       from CbsTxnJnl
                      where TraKnd=:sTraKnd
                        and SndBNo=:sSndBNo
                        and SndDat=:sSndDat
                        and VchId=:sVchId
                        and OIFlag=:sOIFlag;
            if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {  /*数据库操作异常*/
              fclose( chk_fp );
              fclose( dtl_fp );
              fclose( dlst_fp );
              bpErrorLog( trdata, "CbsDtlFilChk:查询来帐明细表错【%d】【%s】【%s】【%s】【%s】【%s】!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
              bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 查询来帐明细表【CbsTxnJnl】错" );
              return( -1 );
            }
            if( SQLCODE == SQL_NOTFOUND ) {  /*数据库中无来帐记录、补登*/
              bpErrorLog( trdata, "CbsDtlFilChk:明细表中不存在【%s】【%s】【%s】【%s】【%s】!\n", sTraKnd, sSndBNo, sSndDat, sVchId, sOIFlag );
              ClearStr( sBilSts );
              ClearStr( sTRspCd );
              ClearStr( sLogNo  );
              strcpy( sBilSts, "U" );
              strcpy( sTRspCd, "000000" );
              if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
                fclose( chk_fp );
                fclose( dtl_fp );
                fclose( dlst_fp );
                bpErrorLog( trdata, "CbsDtlFilChk:取前置流水号错!\n" );
                bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 取前置流水号错" );
                return( -1 );
              }
              Exec SQL insert into CbsTxnJnl( TraKnd,SndBNo,SndDat,VchId,OIFlag,BilSts,MsgId,TxnKnd,AccFlg,ClrDat,LogNo,BrNo,ActDat,CcyCod,TxnAmt,TraTm,CenTm,CenLog,SvrCod,TRspCd,CshFlg,SmrCod,UsgCod,RSdFlg,TBusTp,CardFg,AccKnd,FeeTyp,PayFuc,AuthCd,PayLvl,SOpnBk,SndNod,SndAct,SndNm,SndAdr,RcvBNo,ROpnBk,RcvNod,RcvAct,RcvNm,RcvAdr,OrgId,Smr )
                                      values( :sTraKnd,:sSndBNo,:sSndDat,:sVchId,:sOIFlag,:sBilSts,:sMsgId,:sTxnKnd,:sAccFlg,:sClrDat,:sLogNo,:sBrNo,:sActDat,:sCcyCod,:sTxnAmt,:sTraTm,:sCenTm,:sCenLog,:sSvrCod,:sTRspCd,:sCshFlg,:sSmrCod,:sUsgCod,:sRSdFlg,:sTBusTp,:sCardFg,:sAccKnd,:sFeeTyp,:sPayFuc,:sAuthCd,:sPayLvl,:sSOpnBk,:sSndNod,:sSndAct,:sSndNm,:sSndAdr,:sRcvBNo,:sROpnBk,:sRcvNod,:sRcvAct,:sRcvNm,:sRcvAdr,:sOrgId,:sSmr );
              if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
                fclose( chk_fp );
                fclose( dtl_fp );
                fclose( dlst_fp );
                bpErrorLog( trdata, "CbsDtlFilChk:补登明细表错SQLCODE【%d】,内容I：TraKnd【%s】SndBNo【%s】SndDat【%s】VchId【%s】OIFlag【%s】!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId, sOIFlag );
                bpErrorLog( trdata, "CbsDtlFilChk:内容II：BilSts【%s】MsgId【%s】TxnKnd【%s】AccFlg【%s】ClrDat【%s】\n",sBilSts,sMsgId,sTxnKnd,sAccFlg,sClrDat );
                bpErrorLog( trdata, "CbsDtlFilChk:内容III：LogNo【%s】BrNo【%s】ActDat【%s】CcyCod【%s】TxnAmt【%s】\n",sLogNo,sBrNo,sActDat,sCcyCod,sTxnAmt );
                bpErrorLog( trdata, "CbsDtlFilChk:内容IV：TraTm【%s】CenTm【%s】CenLog【%s】SvrCod【%s】TRspCd【%s】\n",sTraTm,sCenTm,sCenLog,sSvrCod,sTRspCd );
                bpErrorLog( trdata, "CbsDtlFilChk:内容V：CshFlg【%s】SmrCod【%s】UsgCod【%s】RSdFlg【%s】TBusTp【%s】\n",sCshFlg,sSmrCod,sUsgCod,sRSdFlg,sTBusTp );
                bpErrorLog( trdata, "CbsDtlFilChk:内容VI：CardFg【%s】AccKnd【%s】FeeTyp【%s】PayFuc【%s】AuthCd【%s】\n",sCardFg,sAccKnd,sFeeTyp,sPayFuc,sAuthCd );
                bpErrorLog( trdata, "CbsDtlFilChk:内容VII：PayLvl【%s】SOpnBk【%s】SndNod【%s】SndAct【%s】SndNm【%s】\n",sPayLvl,sSOpnBk,sSndNod,sSndAct,sSndNm );
                bpErrorLog( trdata, "CbsDtlFilChk:内容VIII：SndAdr【%s】RcvBNo【%s】ROpnBk【%s】RcvNod【%s】RcvAct【%s】\n",sSndAdr,sRcvBNo,sROpnBk,sRcvNod,sRcvAct );
                bpErrorLog( trdata, "CbsDtlFilChk:内容IX：RcvNm【%s】RcvAdr【%s】OrgId【%s】Smr【%s】!\n",sRcvNm,sRcvAdr,sOrgId,sSmr );
                bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 补登明细表【CbsTxnJnl】错" );
                return( -1 );
              }
              strcpy( sResult, "中心有，行内无，已补登" );
              fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
              strcpy( sSucFlg, "N" );
            }
          }
          if( memcmp(sSndBNo,BOCSGN,3)==0 ) {   /*检查往帐*/
            ClearStr( sOIFlag );
            ClearStr( sResult );
            strcpy( sOIFlag, "0" );
            EXEC SQL select BilSts
                       into :sBilSts
                       from CbsTxnJnl
                      where TraKnd=:sTraKnd
                        and SndBNo=:sSndBNo
                        and SndDat=:sSndDat
                        and VchId=:sVchId
                        and OIFlag=:sOIFlag;
            if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {  /*数据库操作异常*/
              fclose( chk_fp );
              fclose( dtl_fp );
              fclose( dlst_fp );
              bpErrorLog( trdata, "CbsDtlFilChk:查询往帐明细表错【%d】【%s】【%s】【%s】【%s】【%s】!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
              bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 查询往帐明细表【CbsTxnJnl】错" );
              return( -1 );
            }
            if( SQLCODE == SQL_NOTFOUND ) {  /*数据库中无来帐记录、该情况正常情况下不应出现*/
              bpErrorLog( trdata, "CbsDtlFilChk:缺少往帐明细【%s】【%s】【%s】【%s】【%s】!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
              strcpy( sResult, "中心有，行内无" );
              fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
              strcpy( sSucFlg, "N" );
            }
            if( SQLCODE == SQL_SUCCESS ) {
              EXEC SQL update CbsTxnJnl
                          set BiLSts='G', ClrDat=:sClrDat
                        where TraKnd=:sTraKnd
                          and SndBNo=:sSndBNo
                          and SndDat=:sSndDat
                          and VchId=:sVchId
                          and OIFlag=:sOIFlag
                          and BilSts in ( 'C', 'D' );
              if( SQLCODE != SQL_SUCCESS ) {
                bpErrorLog( trdata, "CbsDtlFilChk:修改往帐明细状态错【%s】【%s】【%s】【%s】【%s】!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
                strcpy( sResult, "中心成功，行内异常" );
                fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                  sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
                strcpy( sSucFlg, "N" );
              }
            }
          }
          break;
        case 100301:   /* 实时扣款 */
          if( memcmp(sRcvBNo,BOCSGN,3)==0 ) {   /*检查来帐*/
            ClearStr( sOIFlag );
            strcpy( sOIFlag, "1" );
            EXEC SQL select BilSts
                       into :sBilSts
                       from CbsTxnJnl
                      where TraKnd=:sTraKnd
                        and SndBNo=:sSndBNo
                        and SndDat=:sSndDat
                        and VchId =:sVchId
                        and OIFlag=:sOIFlag;
            if( SQLCODE == SQL_NOTFOUND ) {  /*数据库中无来帐记录、补登*/
              strcpy( sResult, "中心有，行内无" );
              fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
              strcpy( sSucFlg, "N" );
            } else {
              if( SQLCODE == SQL_SUCCESS ) {  /*数据库有记录*/
                if( ( strcmp( sBilSts, "Z" )!=0 ) && ( strcmp( sBilSts, "S" )!=0 ) ) {
                  bpErrorLog( trdata, "CbsDtlFilChk:中心成功，行内异常【%d】【%s】【%s】【%s】【%s】【%s】!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId, sBilSts );
                  strcpy( sResult, "中心成功，行内异常" );
                  fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                    sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
                  strcpy( sSucFlg, "N" );
                }
              } else {
                fclose( chk_fp );
                fclose( dtl_fp );
                fclose( dlst_fp );
                bpErrorLog( trdata, "CbsDtlFilChk:查询实时明细表错【%d】【%s】【%s】【%s】【%s】【%s】!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
                bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 查询实时明细表【CbsBchJnl】错" );
                return( -1 );
              }
            }
          }
          if( memcmp(sSndBNo,BOCSGN,3)==0 ) {   /*检查往帐*/
            ClearStr( sOIFlag );
            strcpy( sOIFlag, "0" );
            EXEC SQL select BilSts
                       into :sBilSts
                       from CbsTxnJnl
                      where TraKnd=:sTraKnd
                        and SndBNo=:sSndBNo
                        and SndDat=:sSndDat
                        and VchId=:sVchId
                        and OIFlag=:sOIFlag;
            if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {  /*数据库操作异常*/
              fclose( chk_fp );
              fclose( dtl_fp );
              fclose( dlst_fp );
              bpErrorLog( trdata, "CbsDtlFilChk:查询往帐明细表错【%d】【%s】【%s】【%s】【%s】【%s】!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
              bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 查询往帐明细表【CbsTxnJnl】错" );
              return( -1 );
            }
            if( SQLCODE == SQL_NOTFOUND ) {  /*数据库中无往帐记录、该情况正常情况下不应出现*/
              bpErrorLog( trdata, "CbsDtlFilChk:缺少往帐明细【%s】【%s】【%s】【%s】【%s】!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
              strcpy( sResult, "中心有，行内无" );
              fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
              strcpy( sSucFlg, "N" );
            }
            if( SQLCODE == SQL_SUCCESS ) {
              EXEC SQL update CbsBchJnl
                          set BiLSts='G', ClrDat=:sClrDat
                        where TraKnd=:sTraKnd
                          and SndBNo=:sSndBNo
                          and SndDat=:sSndDat
                          and VchId=:sVchId
                          and OIFlag=:sOIFlag
                          and BilSts in ( 'C', 'D' );
              if( SQLCODE != SQL_SUCCESS ) {
                bpErrorLog( trdata, "CbsDtlFilChk:修改往帐明细状态错【%s】【%s】【%s】【%s】【%s】!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
                strcpy( sResult, "中心成功，行内异常" );
                fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                  sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
                strcpy( sSucFlg, "N" );
              }
            }
          }
          break;
        case 105101:   /* 批量贷记 */
        case 105102:   /* 定期贷记 */
        case 105201:   /* 定期借记 */
          if( memcmp(sRcvBNo,BOCSGN,3)==0 ) {   /*检查来帐*/
            ClearStr( sOIFlag );
            strcpy( sOIFlag, "1" );
            EXEC SQL select BilSts
                       into :sBilSts
                       from CbsBchJnl
                      where TraKnd=:sTraKnd
                        and SndBNo=:sSndBNo
                        and SndDat=:sSndDat
                        and VchId=:sVchId
                        and OIFlag=:sOIFlag;
            if( SQLCODE == SQL_NOTFOUND ) {  /*数据库中无来帐记录、补登*/
              strcpy( sResult, "中心有，行内无" );
              fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
              strcpy( sSucFlg, "N" );
            } else {
              if( SQLCODE == SQL_SUCCESS ) {  /*数据库有记录*/
                if( ( strcmp( sBilSts, "Z" )!=0 ) && ( strcmp( sBilSts, "S" )!=0 ) ) {
                  strcpy( sResult, "中心成功，行内异常" );
                  fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                    sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
                  strcpy( sSucFlg, "N" );
                }
              } else {
                fclose( chk_fp );
                fclose( dtl_fp );
                fclose( dlst_fp );
                bpErrorLog( trdata, "CbsDtlFilChk:查询批量明细表错【%d】【%s】【%s】【%s】【%s】【%s】!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
                bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 查询批量明细表【CbsBchJnl】错" );
                return( -1 );
              }
            }
          }
          if( memcmp(sSndBNo,BOCSGN,3)==0 ) {   /*检查往帐*/
            ClearStr( sOIFlag );
            strcpy( sOIFlag, "0" );
            EXEC SQL select BilSts
                       into :sBilSts
                       from CbsBchJnl
                      where TraKnd=:sTraKnd
                        and SndBNo=:sSndBNo
                        and SndDat=:sSndDat
                        and VchId=:sVchId
                        and OIFlag=:sOIFlag;
            if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {  /*数据库操作异常*/
              fclose( chk_fp );
              fclose( dtl_fp );
              fclose( dlst_fp );
              bpErrorLog( trdata, "CbsDtlFilChk:查询往帐明细表错【%d】【%s】【%s】【%s】【%s】【%s】!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
              bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 查询往帐明细表【CbsTxnJnl】错" );
              return( -1 );
            }
            if( SQLCODE == SQL_NOTFOUND ) {  /*数据库中无往帐记录、该情况正常情况下不应出现*/
              bpErrorLog( trdata, "CbsDtlFilChk:缺少往帐明细【%s】【%s】【%s】【%s】【%s】!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
              strcpy( sResult, "中心有，行内无" );
              fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
              strcpy( sSucFlg, "N" );
            }
            if( SQLCODE == SQL_SUCCESS ) {
              EXEC SQL update CbsBchJnl
                          set BiLSts='G', ClrDat=:sClrDat
                        where TraKnd=:sTraKnd
                          and SndBNo=:sSndBNo
                          and SndDat=:sSndDat
                          and VchId=:sVchId
                          and OIFlag=:sOIFlag
                          and BilSts in ( 'C', 'D' );
              if( SQLCODE != SQL_SUCCESS ) {
                bpErrorLog( trdata, "CbsDtlFilChk:修改往帐明细状态错【%s】【%s】【%s】【%s】【%s】!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
                strcpy( sResult, "中心成功，行内异常" );
                fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                  sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
                strcpy( sSucFlg, "N" );
              }
            }
          }
          break;
        default:
          fclose( chk_fp );
          fclose( dtl_fp );
          fclose( dlst_fp );
          bpErrorLog( trdata, "CbsDtlFilChk:业务类型不存在【%s】!", sTxnKnd );
          bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: 业务类型不存在!" );
          return( -1 );
      } /* End of Switch(sTxnKnd) */
    }
    fclose( dtl_fp );
  }
  fclose( chk_fp );
  fclose( dlst_fp );
  etfAddOrRepNode(TrNode,"SucFlg", sSucFlg, strlen(sSucFlg));
  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End CbsDtlFilChk.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsNetToFee
  Description       : 处理网银手续费
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明( 为保证对帐全面，故任何一个文件不合法，则退出 )
******************************************************************************/
int CbsNetToFee(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  传入参数
*/
    char   sTxnMon[TxnMonLen+1];
/*
**  大小通道数据
*/
    char   sDskNo[DskNoLen+1];
    char   sActDat[ActDatLen+1];
    char   sTTxnCd[TTxnCdLen+1];
    char   sHTxnCd[HTxnCdLen+1];
    char   sIsTxn[IsTxnLen+1];
    char   sUpdFlg[UpdFlgLen+1];
    char   sUpdFld[UpdFldLen+1];
    char   sTxnObj[TxnObjLen+1];
    char   sTxnCnl[TxnCnlLen+1];
    char   sCnlSub[CnlSubLen+1];
    char   sBrNo[BrNoLen+1];
    char   sNodNo[NodNoLen+1];
    char   sLogNo[LogNoLen+1];
    char   sTlrId[TlrIdLen+1];
/*
**  游标参数
*/
    char   sDrAct[DrActLen+1];
    char   sDrNam[DrNamLen+1];
    char   sTmpNum[TxnNumLen+1];
    char   sTmpFee[TxnAmtLen+1];
    char   sTmpPst[TxnAmtLen+1];
    char   sTxnNum[TxnNumLen+1];
    char   sFeeAmt[TxnAmtLen+1];
    char   sPstAmt[TxnAmtLen+1];
  EXEC SQL END DECLARE SECTION;
    char   sOrnCnt[OrnCntLen+1];
    long   iCount=0;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin CbsNetToFee.\n" );
/*
**  检查参数个数
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "CBS999", "参数个数错" );
    bpErrorLog( trdata, "CbsNetToFee:参数个数错!\n" );
    return( -1 );
  }
/*
**  获取网银清算月份
*/
  ClearStr( sTxnMon );
  strcpy( sTxnMon, Step_Arg1 );
/*
**  大小通道参数初始化
*/
  ClearStr( sDskNo  );
  ClearStr( sActDat );
  ClearStr( sTTxnCd );
  ClearStr( sHTxnCd );
  ClearStr( sIsTxn  );
  ClearStr( sUpdFlg );
  ClearStr( sUpdFld );
  ClearStr( sTxnObj );
  ClearStr( sTxnCnl );
  ClearStr( sCnlSub );
  ClearStr( sBrNo   );
  ClearStr( sNodNo  );
/*
**  传入参数处理（磁盘号、会计日期、大小通道目标服务、前置交易码）
*/
  if( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【DskNo】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【DskNo】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【ActDat】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【ActDat】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TTxnCd】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【TTxnCd】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【HTxnCd】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【HTxnCd】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "IsTxn", sIsTxn, IsTxnLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【IsTxn】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【IsTxn】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFlg", sUpdFlg, UpdFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【UpdFlg】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【UpdFlg】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFld", sUpdFld, UpdFldLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【UpdFld】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【UpdFld】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TxnObj】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【TxnObj】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【TxnCnl】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【TxnCnl】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CnlSub", sCnlSub, CnlSubLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【CnlSub】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【CnlSub】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【BrNo】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【BrNo】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "获取节点【NodNo】错误" );
    bpErrorLog( trdata, "CbsNetToFee:获取节点【NodNo】错误!\n" );
    return( -1 );
  }

/*
**  遍历网银下载流水表
*/
  EXEC SQL DECLARE c_netdtl CURSOR FOR
    select DrAct, DrNam, rtrim(char(count(*))), rtrim(char(sum(bigint(FeeAmt)))), rtrim(char(sum(bigint(PstAmt))))
      from CbsNetDtl
     where BrNo=:sBrNo and substr(DonDat,1,6)=:sTxnMon and FeeFlg='0'
  group by DrAct, DrNam;
  EXEC SQL OPEN c_netdtl;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult(TrNode, "CBS999", "查询表【CbsNetDtl】异常－打开游标错");
    bpErrorLog(trdata, "CbsNetToFee:查询表【CbsNetDtl】异常－打开游标错[%d]", SQLCODE);
    return( -1 );
  }
  for( ; ; ) {
/*
**  游标参数初始化
*/
    ClearStr( sDrAct  );
    ClearStr( sDrNam  );
    ClearStr( sTmpNum );
    ClearStr( sTmpFee );
    ClearStr( sTmpPst );
    ClearStr( sTxnNum );
    ClearStr( sFeeAmt );
    ClearStr( sPstAmt );
    EXEC SQL FETCH c_netdtl INTO :sDrAct,:sDrNam,:sTmpNum,:sTmpFee,:sTmpPst;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, "CBS999", "查询表【CbsNetDtl】异常－FETCH出错" );
      bpErrorLog(trdata, "CbsNetToFee:查询表【CbsNetDtl】异常－FETCH出错[%d]", SQLCODE);
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
    sprintf( sTxnNum, "%06s",  sTmpNum );
    sprintf( sFeeAmt, "%015s", sTmpFee );
    sprintf( sPstAmt, "%015s", sTmpPst );
/*
**  根据分行号和交易渠道获取电子柜员号
*/
    if( sqnGetDumTlr( sBrNo, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
      bpAddResult(TrNode, "CBS999", "取电子柜员号出错" );
      bpErrorLog( trdata, "CbsNetToFee:取电子柜员号出错，参数BrNo【%s】TxnCnl【%s】CnlSub【%s】", sBrNo, sTxnCnl, sCnlSub );
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
    if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
      bpAddResult(TrNode, "CBS999", "取前置流水号出错" );
      bpErrorLog(trdata, "CbsNetToFee:取前置流水号出错" );
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
    EXEC SQL insert into CbsNetFee( LogNo,DskNo,ActDat,TlrId,TTxnCd,HTxnCd,IsTxn,TxnCnl,CnlSub,TxnObj,UpdFlg,UpdFld,BrNo,NodNo,TxnMon,DrAct,DrNam,TxnNum,FeeAmt,PstAmt )
                            values( :sLogNo,:sDskNo,:sActDat,:sTlrId,:sTTxnCd,:sHTxnCd,:sIsTxn,:sTxnCnl,:sCnlSub,:sTxnObj,:sUpdFlg,:sUpdFld,:sBrNo,:sNodNo,:sTxnMon,:sDrAct,:sDrNam,:sTxnNum,:sFeeAmt,:sPstAmt );
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, "CBS999", "INSERT表【CbsNetFee】异常" );
      bpErrorLog( trdata, "CbsNetToFee:INSERT表【CbsNetFee】异常【%d】-数据内容-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sLogNo,sDskNo,sActDat,sTlrId,sIsTxn,sTxnCnl,sCnlSub,sTxnObj,sUpdFlg,sUpdFld,sBrNo,sTxnMon,sDrAct,sDrNam,sTxnNum,sFeeAmt,sPstAmt );
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
    iCount++;
/*
**  修改网银流水表状态为已处理
    EXEC SQL update CbsNetDtl set FeeFlg='1' where BrNo=:sBrNo and substr(DonDat,1,6)=:sTxnMon;
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, "CBS999", "Update表【CbsNetDtl】异常" );
      bpErrorLog( trdata, "CbsNetToFee:Update表【CbsNetDtl】异常【%d】【%s】",SQLCODE,sTxnMon );
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
*/
  }
  sprintf( sOrnCnt,"%8d", iCount );
  EXEC SQL CLOSE c_netdtl;
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
  bpAddResult(TrNode, "000000", "处理网银流水完成" );
  bpTraceLog( trdata, "End CbsNetToFee.\n" );
  return (0);
}
