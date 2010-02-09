/******************************************************************************       
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.            
                                                                                      
  File name   : pcl.cp
  Author      : Jamez
  Version     : 2.0  
  Date        : 2007.04.03  
  Description : POS 自动清算系统个性原子函数库
  History     :


  No.  Date    Author    Modification                 
  ===  ==========  ========  ============================

******************************************************************************/
#include <sql.h>
#include "hipcl.h"
#include "hionline.h"
#include "hidatabase.h"
#include "hibusmsg.h"
#include "hibppubdef.h"
#include "hipex.h"
#define ClearStr(str) memset(str,'\0',sizeof(str))
/******************************************************************************
  Function        : PCLFileToDb
  Description     : POS 交易明细文件入库
  Calls           : 被本函数调用的函数清单
  Called By       : 调用本函数的函数清单 
  Table Accessed  : PclTxnDtl PclCifReg
  Table Updated   : PclTxnDtl
  Input           : ETF *TrNode  输入树
                    ST_TranData* trdata  公共结构
                    char* args  参数
                    DBConHandle* DBHandle  数据库句柄
  Output          : 对输出参数的说明
  Return          : 0--成功 小于0--失败
  Others          : 其它说明
******************************************************************************/
int PCLFileToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sSeqNo[SeqNoLen+1];
    char   sIssCode[IssCodeLen+1];
    char   sRecvIns[RecvInsLen+1];
    char   sTranAcc[TranAccLen+1];
    char   sAcqCode[AcqCodeLen+1];
    char   sForwIns[ForwInsLen+1];
    char   sAcqIns[AcqInsLen+1];
    char   sRefNo[RefNoLen+1];
    char   sCtrDt[CtrDtLen+1];
    char   sCtrTime[CtrTimeLen+1];
    char   sCtrTrn[CtrTrnLen+1];
    char   sTranAmt[TranAmtLen+1];
    char   sMerStandComm[MerStandCommLen+1];
    char   sMti[MtiLen+1];
    char   sProcCode[ProcCodeLen+1];
    char   sMerType[MerTypeLen+1];
    char   sCtrPostDate[ActDatLen+1];
    char   sTermId[TermIdLen+1];
    char   sMerId[MerIdLen+1];
    char   sMerAccFromTbl[MerAccFromTblLen+1];
    char   sTranCurr[TranCurrLen+1];
    char   sClearAmt[ClearAmtLen+1];
    char   sManuAuthFlag[ManuAuthFlagLen+1];
    char   sGnetAuthFlag[GnetAuthFlagLen+1];
    char   sAuthCode[AuthCodeLen+1];
    char   sTxCode[TxCodeLen+1];
    char   sRepCode[RepCodeLen+1];
    char   sMerName[MerNameLen+1];
    char   sOrigCtrTrn[OrigCtrTrnLen+1];
    char   sOrigRefNo[OrigRefNoLen+1];
    char   sEndFlag[EndFlagLen+1];
    char   sBankFee[BankFeeLen+1];
    char   sMerFee[MerFeeLen+1];
    char   sOCtrDt[OCtrDtLen+1];
    char   sPrvFlg[PrvFlgLen+1];

    char   sClrDt[ActDatLen+1];
    char   sActDat[ActDatLen+1];
    char   sBrNo[DeptNoLen+1];
    char   sCdFlag[CdFlagLen+1];
    
    char   sPosTyp[PosTypLen+1];
    char   sDeptNo[DeptNoLen+1];
    char   sOpnBr[DeptNoLen+1];
    char   sAgrBr[DeptNoLen+1];
    char   sAccFlg[AccFlgLen+1];
    char   sBankNo[BankNoLen+1];
    char   sInAcNo[InAcNoLen+1];
    char   sInMode[InModeLen+1];
    char   sTlrId[TlrIdLen+1];
    char   sTckNo[TckNoLen+1];
    char   sPrtNum[PrtNumLen+1];
    char   sErrMsg[ErrMsgLen+1];
    char   sFeeRat1[FeeRatLen+1];
    char   sFeeRat2[FeeRatLen+1];
    char   sTopAmt[TopAmtLen+1];
    char   sSts[StsLen+1];
  EXEC SQL END DECLARE SECTION;
    int    iRet;
    FILE   *fp;
    char   fname[128];
    char   sMsg[MsgLen+1];
    char   sTmpFee[BankFeeLen+1];

/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin PCLFileToDb.\n" );
/*
**  检查参数个数
*/
  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, "PCL999", "参数个数错" );
    bpErrorLog( trdata, "PCLFileToDb: 参数个数错!" );
    return( -1 );
  }
/*
**  处理数据文件
*/
  ClearStr( sClrDt );
  ClearStr( sActDat );
  ClearStr( sBrNo );
  ClearStr( fname );
  strcpy( sClrDt, Step_Arg1 );
  if ( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【ActDat】错误" );
    bpErrorLog( trdata, "PCLFileToDb:获取节点【ActDat】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "BrNo", sBrNo, DeptNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【BrNo】错误" );
    bpErrorLog( trdata, "PCLFileToDb:获取节点【BrNo】错误!\n" );
    return( -1 );
  }
  sprintf( fname, "%s/%s", getenv("WORKDIR"), Step_Arg2 );
  fp =fopen( fname,"r" );
  if( fp == NULL ) {
    fclose( fp );
    bpAddResult( TrNode, "PCL999", "打开POS明细文件错" );
    bpErrorLog( trdata, "PCLFileToDb:打开POS明细文件【%s】失败!\n", fname );
    return( -1 );
  }
/*
**  逐条处理明细文件
*/
  iRet = 0;
  while( !feof( fp ) ) {
/*
**  文件数据变量初始化
*/
    ClearStr( sSeqNo );
    ClearStr( sIssCode );
    ClearStr( sRecvIns );
    ClearStr( sTranAcc );
    ClearStr( sAcqCode );
    ClearStr( sForwIns );
    ClearStr( sAcqIns );
    ClearStr( sRefNo );
    ClearStr( sCtrDt );
    ClearStr( sCtrTime );
    ClearStr( sCtrTrn );
    ClearStr( sTranAmt );
    ClearStr( sMerStandComm );
    ClearStr( sMti );
    ClearStr( sProcCode );
    ClearStr( sMerType );
    ClearStr( sCtrPostDate );
    ClearStr( sTermId );
    ClearStr( sMerId );
    ClearStr( sMerAccFromTbl );
    ClearStr( sTranCurr );
    ClearStr( sClearAmt );
    ClearStr( sManuAuthFlag );
    ClearStr( sGnetAuthFlag );
    ClearStr( sAuthCode );
    ClearStr( sTxCode );
    ClearStr( sRepCode );
    ClearStr( sMerName );
    ClearStr( sOrigCtrTrn );
    ClearStr( sOrigRefNo );
    ClearStr( sEndFlag );
    ClearStr( sBankFee );
    ClearStr( sMerFee );
    ClearStr( sOCtrDt );
    ClearStr( sPrvFlg );
/*
**  数据库其他变量初始化
*/
    ClearStr( sMsg );
    ClearStr( sSts );
    ClearStr( sCdFlag );
    ClearStr( sInAcNo );
    ClearStr( sPosTyp );
    ClearStr( sDeptNo );
    ClearStr( sOpnBr );
    ClearStr( sAgrBr );
    ClearStr( sBankNo );
    ClearStr( sAccFlg );
    ClearStr( sInMode );
    ClearStr( sTlrId );
    ClearStr( sTckNo );
    ClearStr( sPrtNum );
    ClearStr( sFeeRat1 );
    ClearStr( sFeeRat2 );
    ClearStr( sTopAmt );
    ClearStr( sErrMsg );

    fgets( sMsg, MsgLen, fp );
    memcpy( sSeqNo, sMsg+SeqNoOffset, SeqNoLen );
    if( strcmp( sSeqNo, "000000" ) == 0 ) continue;
    if( strcmp( sSeqNo, "999999" ) == 0 ) break;
    memcpy( sIssCode, sMsg+IssCodeOffset, IssCodeLen );
    memcpy( sRecvIns, sMsg+RecvInsOffset, RecvInsLen );
    memcpy( sTranAcc, sMsg+TranAccOffset, TranAccLen );
    memcpy( sAcqCode, sMsg+AcqCodeOffset, AcqCodeLen );
    memcpy( sForwIns, sMsg+ForwInsOffset, ForwInsLen );
    memcpy( sAcqIns, sMsg+AcqInsOffset, AcqInsLen );
    memcpy( sRefNo, sMsg+RefNoOffset, RefNoLen );
    memcpy( sCtrDt, sMsg+CtrDtOffset, CtrDtLen );
    memcpy( sCtrTime, sMsg+CtrTimeOffset, CtrTimeLen );
    memcpy( sCtrTrn, sMsg+CtrTrnOffset, CtrTrnLen );
    memcpy( sTranAmt, sMsg+TranAmtOffset, TranAmtLen );
    memcpy( sMerStandComm, sMsg+MerStandCommOffset, MerStandCommLen );
    memcpy( sMti, sMsg+MtiOffset, MtiLen );
    memcpy( sProcCode, sMsg+ProcCodeOffset, ProcCodeLen );
    memcpy( sMerType, sMsg+MerTypeOffset, MerTypeLen );
    memcpy( sCtrPostDate, sMsg+CtrPostDateOffset, CtrPostDateLen );
    memcpy( sTermId, sMsg+TermIdOffset, TermIdLen );
    memcpy( sMerId, sMsg+MerIdOffset, MerIdLen );
    memcpy( sMerAccFromTbl, sMsg+MerAccFromTblOffset, MerAccFromTblLen );
    memcpy( sTranCurr, sMsg+TranCurrOffset, TranCurrLen );
    memcpy( sClearAmt, sMsg+ClearAmtOffset, ClearAmtLen );
    memcpy( sManuAuthFlag, sMsg+ManuAuthFlagOffset, ManuAuthFlagLen );
    memcpy( sGnetAuthFlag, sMsg+GnetAuthFlagOffset, GnetAuthFlagLen );
    memcpy( sAuthCode, sMsg+AuthCodeOffset, AuthCodeLen );
    memcpy( sTxCode, sMsg+TxCodeOffset, TxCodeLen );
    memcpy( sRepCode, sMsg+RepCodeOffset, RepCodeLen );
    memcpy( sMerName, sMsg+MerNameOffset, MerNameLen );
    memcpy( sOrigCtrTrn, sMsg+OrigCtrTrnOffset, OrigCtrTrnLen );
    memcpy( sOrigRefNo, sMsg+OrigRefNoOffset, OrigRefNoLen );
    memcpy( sEndFlag, sMsg+EndFlagOffset, EndFlagLen );
/*
**  处理退货明细中手续费含有"-"号的问题
*/
    ClearStr( sTmpFee );
    memcpy( sTmpFee, sMsg+BankFeeOffset, BankFeeLen );
    sprintf( sBankFee, "%012d", abs( atoi( sTmpFee ) ) );
    ClearStr( sTmpFee );
    memcpy( sTmpFee, sMsg+MerFeeOffset, MerFeeLen );
    sprintf( sMerFee, "%012d", abs( atoi( sTmpFee ) ) );
    memcpy( sPrvFlg, sMsg+PrvFlgOffset, PrvFlgLen );
/*
**  部分数据按要求格式转换
*/
    sprintf( sFeeRat1, "%s%s", "00", sMerStandComm );
    ClearStr( sClearAmt );
    sprintf( sClearAmt, "%012d", atoi( sTranAmt ) - abs( atoi( sMerFee ) ) );
/*
**  状态位、借贷标志赋初值
*/
    strcpy( sSts, "0" );
    strcpy( sCdFlag, "C" );
/*
**  判断输入日期是否未POS清算日
*/
    if( memcmp( sClrDt+CtrPostDateLen, sCtrPostDate, CtrPostDateLen ) != 0 ) {
      bpErrorLog( trdata, "PCLFileToDb:数据日期非POS清算日【%s】【%s】", sClrDt, sCtrPostDate );
      iRet = -1;
      strcpy( sSts, "E" );
      strcpy( sAgrBr, sBrNo );
      strcpy( sErrMsg, "清算文件数据非POS清算日数据" );
      goto DB_INSERT;
    }
/*
**  完成标志不为"00"的，不清算
*/
    if( strcmp( sRepCode, "00" ) != 0 ) strcpy( sSts, "A" );
/*
**  检查商户号是否存在，若不存在则将代理分行号置为操作分行行号，保证报表的正确取值
*/
    EXEC SQL select PosTyp, DeptNo, OpnBr, AgrBr, BankNo, AccFlg, InAcNo, InMode, FeeRat, TopAmt
               into :sPosTyp, :sDeptNo, :sOpnBr, :sAgrBr, :sBankNo, :sAccFlg, :sInAcNo, :sInMode, :sFeeRat2, :sTopAmt
               from PclCusAgt
              where PosTyp='0'
                and BusiNo = :sMerId
                and Sts = '0';    
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLFileToDb:该商户号未登记或异常【%s】", sMerId );
      iRet = -1;
      strcpy( sSts, "E" );
      strcpy( sAgrBr, sBrNo );
      strcpy( sErrMsg, "该商户号未登记或异常" );
      goto DB_INSERT;
    }
/*
**  检查手续费率是否一致 7299 5511
*/
/*
    if( ( strncmp( sMerId+7, "5271", 4 )==0 ) || ( strncmp( sMerId+7, "5998", 4 )==0 ) || ( strncmp( sMerId+7, "1520", 4 )==0 ) ||
        ( strncmp( sMerId+7, "7299", 4 )==0 ) || ( strncmp( sMerId+7, "5511", 4 )==0 ) ) {
      bpErrorLog( trdata, "PCLFileToDb:该商户号手续费率为零【%s】", sMerId );
      EXEC SQL select substr(right( '000000000000000' || rtrim(char(bigint(round(bigint(:sTranAmt) * int(:sFeeRat2) / 100000.00,0)))), 15 ),1,15)
                 into :sMerFee
                 from PclCusAgt
                fetch first 1 rows only;
      if( atoi(sMerFee) > atoi(sTopAmt) ) strcpy( sMerFee, sTopAmt );
      sprintf( sClearAmt, "%015d", atoi( sTranAmt ) - atoi( sMerFee ) );
      bpErrorLog( trdata, "PCLFileToDb:该商户号手续费率应为【%s】", sMerFee );
    } else {
      if( strcmp( sFeeRat1, sFeeRat2 ) != 0 ) {
        bpErrorLog( trdata, "PCLFileToDb:该商户号手续费率不一致【%s】【%s】", sMerId, sFeeRat1 );
        iRet = -1;
        strcpy( sSts, "E" );
        strcpy( sErrMsg, "该商户号手续费率不一致" );
        goto DB_INSERT;
      }
    }
*/
    if( strcmp( sFeeRat1, sFeeRat2 ) != 0 ) {
      bpErrorLog( trdata, "PCLFileToDb:该商户号手续费率不一致【%s】【%s】", sMerId, sFeeRat1 );
      iRet = -1;
      strcpy( sSts, "E" );
      strcpy( sErrMsg, "该商户号手续费率不一致" );
      goto DB_INSERT;
    }
/*
**  对于按交易总额入帐的客户，将清算金额置为交易金额
    if( strcmp( sInMode, "0" ) == 0 ) {
      strcpy( aClearAmt, aTranAmt );
    }
*/
/*
**  排除被冲正的交易
*/
    if( ( ( ( strcmp( sTxCode, "PER" ) == 0 )||( strcmp( sTxCode, "I22" ) == 0 ) ) && ( strcmp( sEndFlag, "02" ) == 0 ) ) ||
      ( ( strcmp( sTxCode, "PEC" ) == 0 ) && ( strcmp( sEndFlag, "03" ) == 0 ) ) ||
      ( ( strcmp( sTxCode, "ACR" ) == 0 ) && ( strcmp( sEndFlag, "02" ) == 0 ) ) ||
      ( ( strcmp( sTxCode, "ACC" ) == 0 ) && ( strcmp( sEndFlag, "03" ) == 0 ) ) ||
      ( ( strcmp( sTxCode, "ECC" ) == 0 ) && ( strcmp( sEndFlag, "03" ) == 0 ) ) ) {
      strcpy( sSts, "A" );
    }
/*
**  处理退货交易（将借贷标志位置为"D"借方、并将入账方式改为单笔入账）
*/ 
    if( strcmp( sTxCode, "RSA" ) == 0 ) {
      strcpy( sCdFlag, "D" );
      strcpy( sInMode, "2" );
    }
/*
**  数据入库
*/
DB_INSERT:
    EXEC SQL insert into PclTxnDtl( Sts, SeqNo, IssCode, RecvIns, TranAcc, AcqCode, ForWins, AcqIns, RefNo, CtrDt, CtrTime, CtrTrn, TranAmt, MerStandComm, Mti, ProcCode, MerType, CtrPostDate, TermId, MerId, MerAccFromTbl, TranCurr, ClearAmt, ManuAuthFlag, GnetAuthFlag, AuthCode, TxCode, RepCode, MerName, OrigCtrTrn, OrigRefNo, EndFlag, BankFee, MerFee, PrvFlg, InAcNo, CdFlag, DeptNo, OpnBr, AgrBr, BankNo, AccFlg, InMode, DskNo, LogNo, ActDat, HLogNo, TlrId, TckNo, SPrtNum, RPrtNum, ErrMsg )
                values( :sSts, :sSeqNo, :sIssCode, :sRecvIns, :sTranAcc, :sAcqCode, :sForwIns, :sAcqIns, :sRefNo, :sCtrDt, :sCtrTime, :sCtrTrn, :sTranAmt, :sFeeRat1, :sMti, :sProcCode, :sMerType, :sClrDt, :sTermId, :sMerId, :sMerAccFromTbl, :sTranCurr, :sClearAmt, :sManuAuthFlag, :sGnetAuthFlag, :sAuthCode, :sTxCode, :sRepCode, :sMerName, :sOrigCtrTrn, :sOrigRefNo, :sEndFlag, :sBankFee, :sMerFee, :sPrvFlg, :sInAcNo, :sCdFlag, :sDeptNo, :sOpnBr, :sAgrBr, :sBankNo, :sAccFlg, :sInMode, ' ', ' ', :sActDat, ' ', ' ', ' ', '00', '00', :sErrMsg );
    if( SQLCODE != SQL_SUCCESS ) {
      fclose( fp );
      bpAddResult( TrNode, "PCL999", "INSERT表【PclTxnDtl】出错" );
      bpErrorLog(trdata, "PCLFileToDb:INSERT出错[%d][%s]-数据内容-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE, sMsg, sSts, sSeqNo, sIssCode, sRecvIns, sTranAcc, sAcqCode, sForwIns, sAcqIns, sRefNo, sCtrDt, sCtrTime, sCtrTrn, sTranAmt, sFeeRat1, sMti, sProcCode, sMerType, sCtrPostDate, sTermId, sMerId, sMerAccFromTbl, sTranCurr, sClearAmt, sManuAuthFlag, sGnetAuthFlag, sAuthCode, sTxCode, sRepCode, sMerName, sOrigCtrTrn, sOrigRefNo, sEndFlag, sBankFee, sMerFee, sCdFlag, sInAcNo, sDeptNo, sBankNo, sAccFlg, sInMode, sErrMsg );
      return( -1 );
    }
  }
/*
**  关闭处理文件
*/
  fclose( fp );
/*
**  处理撤销交易（将数据库记录置为"A"）
**  以下步骤是在保证撤销交易的ORIGCTRTRN和原交易的CTRTRN相同的基础上实现的，可能会有误
*/
  EXEC SQL DECLARE c_txndtl1 CURSOR FOR
      select SeqNo, TranAmt, OrigCtrTrn, MerId
        from PclTxnDtl
       where CtrPostDate = :sClrDt
         and AgrBr= :sBrNo
         and Sts in ( '0', 'A' )
         and TxCode in ( 'ECR', 'CCR', 'I52' );
  EXEC SQL OPEN c_txndtl1;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult(TrNode, "PCL999", "查询表【PclTxnDtl】异常" );
    bpErrorLog(trdata, "PCLFileToDb:查询表【PclTxnDtl】OPEN游标错[%d]", SQLCODE);
    return( -1 );
  }
  for( ; ; ) {
    ClearStr( sSeqNo );
    ClearStr( sTranAmt );
    ClearStr( sOrigCtrTrn );
    ClearStr( sMerId );
    EXEC SQL FETCH c_txndtl1 INTO :sSeqNo, :sTranAmt, :sOrigCtrTrn, :sMerId;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLFileToDb:FETCH出错[%d]", SQLCODE );
      iRet = -1;
      break;
    }
    EXEC SQL update PclTxnDtl
                set Sts = 'A'
              where CtrPostDate = :sClrDt
                and AgrBr= :sBrNo
                and Sts in ( '0', 'A' )
/*
                and PosTyp='0'
*/
                and MerId = :sMerId
                and TxCode in ( 'ECR', 'CCR', 'PER', 'ACR','I52','I22' )
                and ( OrigCtrTrn = :sOrigCtrTrn or CtrTrn = :sOrigCtrTrn or OrigCtrTrn = '' )
                and TranAmt = :sTranAmt
                and AgrBr= :sBrNo;
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog(trdata, "PCLFileToDb:修改表【PclTxnDtl】异常[%d]", SQLCODE);
      iRet = -1;
      break;
    }
  }
  EXEC SQL CLOSE c_txndtl1;
  if( iRet != 0 ) {
    bpAddResult(TrNode, "PCL999", "数据入库失败" );
    bpErrorLog(trdata, "PCLFileToDb:数据文件【%s】入库失败", fname);
    iRet = -1;
  } else {
    bpAddResult(TrNode, "000000", "交易成功" );
    bpErrorLog(trdata, "PCLFileToDb:数据文件【%s】入库成功", fname);
  }
  bpTraceLog( trdata, "End PCLFileToDb.\n" );
  return iRet;
}
/******************************************************************************
  Function        : PCLDtlToAcc
  Description     : 根据POS入帐明细生成入帐数据
  Calls           : 被本函数调用的函数清单
  Called By       : 调用本函数的函数清单
  Table Accessed  : PclTxnDtl PclCusAgt PclAccJnl
  Table Updated   : PclTxnDtl
  Input           : ETF *TrNode  输入树
                    ST_TranData* trdata  公共结构
                    char* args  参数
                    DBConHandle* DBHandle  数据库句柄
  Output          : 对输出参数的说明
  Return          : 0--成功 小于0--失败
  Others          : 其它说明
******************************************************************************/
int PCLDtlToAcc(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  传入参数
*/
    char   sCtrPostDate[ActDatLen+1];
    char   sClrAct[InAcNoLen+1];
    char   sCdFlag[CdFlagLen+1];
/*
**  大小通道数据
*/
    char   sDskNo[DskNoLen+1];
    char   sActDat[ActDatLen+1];
    char   sTTxnCd[TTxnCdLen+1];
    char   sHTxnCd[HTxnCdLen+1];
    char   sHTxnSt[HTxnStLen+1];
    char   sIsTxn[IsTxnLen+1];
    char   sTxnObj[TxnObjLen+1];
    char   sTxnCnl[TxnCnlLen+1];
    char   sBrNo[BrNoLen+1];

    char   sLogNo[LogNoLen+1];
    char   sHLogNo[HLogNoLen+1];
    char   sHRspCd[HRspCdLen+1];
    char   sCnlSub[CnlSubLen+1];
    char   sTlrId[TlrIdLen+1];
    char   sTckNo[TckNoLen+1];
    char   sUpdFlg[UpdFlgLen+1];
    char   sUpdFld[UpdFldLen+1];
/*
**  游标参数
*/
    char   sOMerId[MerIdLen+1];
    char   sRepFlg[RepFlgLen+1];
    char   sSeqNo[SeqNoLen+1];
    char   sMerId[MerIdLen+1];
    char   sTranAmt[TranAmtLen+1];
    char   sClearAmt[ClearAmtLen+1];
    char   sMerFee[MerFeeLen+1];
    char   sInAcNo[InAcNoLen+1];
    char   sDeptNo[DeptNoLen+1];
    char   sOpnBr[DeptNoLen+1];
    char   sSndFlg[SndFlgLen+1];
    char   sInMode[InModeLen+1];
/*
**  程序变量
*/
    char   sTmpTranAmt[TopAmtLen+1];
    char   sTmpClearAmt[TopAmtLen+1];
    char   sTmpMerFee[TopAmtLen+1];
    char   sOrnCnt[OrnCntLen+1];
  EXEC SQL END DECLARE SECTION;
    long   iCount=0;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin PCLDtlToAcc.\n" );
/*
**  检查参数个数
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "参数个数错" );
    bpErrorLog( trdata, "PCLDtlToAcc:参数个数错!\n" );
    return( -1 );
  }
/*
**  大小通道参数初始化
*/
  ClearStr( sDskNo  );
  ClearStr( sActDat );
  ClearStr( sTTxnCd );
  ClearStr( sHTxnCd );
  ClearStr( sHTxnSt );
  ClearStr( sIsTxn  );
  ClearStr( sUpdFlg );
  ClearStr( sUpdFld );
  ClearStr( sTxnObj );
  ClearStr( sTxnCnl );
  ClearStr( sDeptNo );
  ClearStr( sBrNo   );
  ClearStr( sHLogNo );
  ClearStr( sHRspCd );
  ClearStr( sTckNo  );
/*
**  传入参数处理（磁盘号、会计日期、大小通道目标服务、银联清算日期、前置交易码）
*/
  if( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【DskNo】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【DskNo】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【ActDat】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【ActDat】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【TTxnCd】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【TTxnCd】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【HTxnCd】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【HTxnCd】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnSt", sHTxnSt, HTxnStLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【HTxnSt】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【HTxnSt】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "IsTxn", sIsTxn, IsTxnLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【IsTxn】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【IsTxn】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFlg", sUpdFlg, UpdFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【UpdFlg】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【UpdFlg】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFld", sUpdFld, UpdFldLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【UpdFld】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【UpdFld】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【TxnObj】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【TxnObj】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【TxnCnl】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【TxnCnl】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【BrNo】错误" );
    bpErrorLog( trdata, "PCLDtlToAcc:获取节点【BrNo】错误!\n" );
    return( -1 );
  }
/*
**  获取银联清算日期
*/
  ClearStr( sCtrPostDate );
  ClearStr( sClrAct );
  ClearStr( sCdFlag );
  strcpy( sCtrPostDate, Step_Arg1 );
  strcpy( sClrAct, Step_Arg2 );
  strcpy( sCdFlag, Step_Arg3 );
/*
**  将明细表状态该为入帐中Booking
*/
  EXEC SQL update PclTxnDtl
              set  Sts='B', DskNo = :sDskNo
            where CtrPostDate =:sCtrPostDate
              and OpnBr =:sBrNo
              and Sts ='0'
              and CdFlag =:sCdFlag;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult(TrNode, "PCL999", "修改表【PclTxnDtl】异常" );
    bpErrorLog(trdata, "PCLDtlToAcc:修改表【PclTxnDtl】异常，参数ActDat【%s】CtrPostDate【%s】SQLCODE【%d】", sActDat, sCtrPostDate, SQLCODE);
    return( -1 );
  }
/*
**  遍历交易明细表所有可以等待处理记录
*/
  ClearStr( sOMerId );
  EXEC SQL DECLARE c_txndtl3 CURSOR FOR
      select SeqNo, MerId, TranAmt, ClearAmt, MerFee, InAcNo, DeptNo, OpnBr, AccFlg, InMode
        from PclTxnDtl
       where CtrPostDate =:sCtrPostDate
         and OpnBr =:sBrNo
         and Sts ='B'
         and CdFlag=:sCdFlag;
  EXEC SQL OPEN c_txndtl3;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult(TrNode, "PCL999", "查询表【PclTxnDtl】异常－打开游标错" );
    bpErrorLog(trdata, "PCLDtlToAcc:查询表【PclTxnDtl】异常－打开游标错[%d]", SQLCODE);
    return( -1 );
  }
  for( ; ; ) {
/*
**  游标参数初始化
*/
    ClearStr( sSeqNo );
    ClearStr( sMerId );
    ClearStr( sTranAmt );
    ClearStr( sClearAmt );
    ClearStr( sMerFee );
    ClearStr( sInAcNo );
    ClearStr( sDeptNo );
    ClearStr( sOpnBr );
    ClearStr( sSndFlg );
    ClearStr( sInMode );

    ClearStr( sLogNo );
    ClearStr( sTlrId );
    ClearStr( sRepFlg );
    ClearStr( sCnlSub );

    EXEC SQL FETCH c_txndtl3 INTO :sSeqNo, :sMerId, :sTranAmt, :sClearAmt, :sMerFee, :sInAcNo, :sDeptNo, :sOpnBr, :sSndFlg, :sInMode;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      EXEC SQL CLOSE c_txndtl3;
      bpAddResult(TrNode, "PCL999", "查询表【PclTxnDtl】异常－FETCH出错" );
      bpErrorLog(trdata, "PCLDtlToAcc:查询表【PclTxnDtl】异常－FETCH出错[%d]", SQLCODE);
      return( -1 );
    }
/*
**  对于系统外、或结算帐户异常（即通过内部帐户中转清算资金的特约商户，入帐方式修改为“8－按清算总额入内部帐”，入帐金额为“清算金额”
*/
    if( strncmp( sInAcNo+19, "99", 2 )==0 ) {
      strcpy( sInMode, "8" );
    }      
/*
**  根据帐户性质决定主机交易服务
    sprintf( sSmr, "清算【%s】银联特约商户【%s】资金", sCtrPostDate, sMerId ); 
*/
/*
**  将SeqNo设置为"ZZZZZZ"目的是当清算方式不为单笔清算时，用于标志原交易明细与入帐汇总记录的对应关系
*/
    if( strcmp( sInMode, "2" )!=0 ) strcpy( sSeqNo, "ZZZZZZ" );
/*
**  计算入帐金额、判断入帐方式
*/
    EXEC SQL select 'Y'
               into :sRepFlg
               from PclAccJnl
              where CtrPostDate =:sCtrPostDate
                and OpnBr =:sBrNo
                and MerId =:sMerId
                and CdFlag =:sCdFlag fetch first 1 rows only;
    if( ( SQLCODE != SQL_SUCCESS )&&( SQLCODE != SQL_NOTFOUND ) ) {
      EXEC SQL CLOSE c_txndtl3;
      bpAddResult(TrNode, "PCL999", "判断入帐方式出错" );
      bpErrorLog(trdata, "PCLDtlToAcc:判断入帐方式出错【%d】", SQLCODE);
      return( -1 );
    }
    if( ( strcmp( sInMode, "2" )==0 ) || ( strcmp( sRepFlg, "Y" )==0 ) ) { /*  按交易单笔入帐或第一笔业务  */
      if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
        EXEC SQL CLOSE c_txndtl3;
        bpAddResult(TrNode, "PCL999", "取前置流水号出错" );
        bpErrorLog(trdata, "PCLDtlToAcc:取前置流水号出错" );
        return( -1 );
      }
/*
**  根据分行号和交易渠道获取电子柜员号
*/
      if( sqnGetDumTlr( sOpnBr, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
        EXEC SQL CLOSE c_txndtl3;
        bpAddResult(TrNode, "PCL999", "取电子柜员号出错" );
        bpErrorLog( trdata, "PCLDtlToAcc:取电子柜员号出错，参数OpnBr【%s】TxnCnl【%s】CnlSub【%s】", sOpnBr, sTxnCnl, sCnlSub );
        return( -1 );
      }
/*
**  金额格式转换
*/
      ClearStr( sTmpTranAmt );
      ClearStr( sTmpClearAmt );
      ClearStr( sTmpMerFee );
      sprintf( sTmpTranAmt,  "%s%s", "000", sTranAmt  );
      sprintf( sTmpClearAmt, "%s%s", "000", sClearAmt );
      sprintf( sTmpMerFee,   "%s%s", "000", sMerFee   );
      EXEC SQL insert into PclAccJnl( LogNo, DskNo, ActDat, TTxnCd, HTxnCd, HLogNo, HTxnSt, HRspCd, IsTxn, UpdFlg, UpdFld, TxnObj, TlrId, TckNo, CtrPostDate, PosTyp, MerId, SeqNo, ClrAct, BokAct, SndFlg, InMode, TranAmt, ClearAmt, MerFee, DeptNo, OpnBr, CdFlag )
                              values( :sLogNo,:sDskNo,:sActDat,:sTTxnCd,:sHTxnCd,:sHLogNo,:sHTxnSt,:sHRspCd,:sIsTxn,:sUpdFlg,:sUpdFld,:sTxnObj,:sTlrId,:sTckNo,:sCtrPostDate,'0',:sMerId,:sSeqNo,:sClrAct,:sInAcNo,:sSndFlg,:sInMode,:sTmpTranAmt,:sTmpClearAmt,:sTmpMerFee,:sDeptNo,:sOpnBr, :sCdFlag );
      if( SQLCODE != SQL_SUCCESS ) {
        EXEC SQL CLOSE c_txndtl3;
        bpAddResult(TrNode, "PCL999", "INSERT表【PclAccJnl】异常" );
        bpErrorLog( trdata, "PCLDtlToAcc:INSERT表【PclAccJnl】异常【%d】-数据内容-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sLogNo,sDskNo,sActDat,sTTxnCd,sHTxnCd,sHLogNo,sHTxnSt,sHRspCd,sIsTxn,sUpdFlg,sUpdFld,sTxnObj,sTlrId,sTckNo,sCtrPostDate,sMerId,sSeqNo,sClrAct,sInAcNo,sSndFlg,sInMode,sTmpTranAmt,sTmpClearAmt,sTmpMerFee,sDeptNo,sOpnBr,sCdFlag );
        return( -1 );
      }
      iCount++;
    } else {                        /*  按交易总额或累计入帐  */
      EXEC SQL update PclAccJnl
                  set TranAmt  = substr( right( ( '000000000000000'||rtrim(char( bigint( TranAmt  ) + bigint( :sTranAmt  ) ) ) ),15 ), 1, 15 ),
                      ClearAmt = substr( right( ( '000000000000000'||rtrim(char( bigint( ClearAmt ) + bigint( :sClearAmt ) ) ) ),15 ), 1, 15 ),
                      MerFee   = substr( right( ( '000000000000000'||rtrim(char( bigint( MerFee   ) + bigint( :sMerFee   ) ) ) ),15 ), 1, 15 )
                where CtrPostDate = :sCtrPostDate
                  and OpnBr = :sOpnBr
                  and MerId = :sMerId
                  and CdFlag= :sCdFlag;
      if( SQLCODE != SQL_SUCCESS ) {
        EXEC SQL CLOSE c_txndtl3;
        bpAddResult(TrNode, "PCL999", "UPDATE表【PclAccJnl】异常" );
        bpErrorLog( trdata, "PCLDtlToAcc:UPDATE出错[%d][%s][%s][%s][%s][%s][%s][%s]", SQLCODE, sInMode, sCtrPostDate, sMerId, sOpnBr, sTranAmt, sClearAmt, sMerFee );
        return( -1 );
      }
    }
  }
  sprintf( sOrnCnt,"%8d", iCount );
  EXEC SQL CLOSE c_txndtl3;
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
  bpAddResult(TrNode, "000000", "数据表【PCLDtlToAcc】整理完成" );
  bpTraceLog( trdata, "End PCLDtlToAcc.\n" );
  return (0);
}
/******************************************************************************
  Function        : PCLDtlToRpt
  Description     : 根据POS入帐明细生成报表数据
  Calls           : 被本函数调用的函数清单
  Called By       : 调用本函数的函数清单
  Table Accessed  : PclTxnDtl PclCusAgt
  Table Updated   : PclTxnDtl
  Input           : ETF *TrNode  输入树
                    ST_TranData* trdata  公共结构
                    char* args  参数
                    DBConHandle* DBHandle  数据库句柄
  Output          : 对输出参数的说明
  Return          : 0--成功 小于0--失败
  Others          : 其它说明
******************************************************************************/
int PCLDtlToRpt(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sActDat[ActDatLen+1];
    char   sTmpDt[5];
    char   sTranAmt[TranAmtLen+1];
    char   sCtrPostDate[ActDatLen+1];
    char   sMerId[MerIdLen+1];
    char   sTmpMerId[MerIdLen+1];
    char   sMerAccFromTbl[MerAccFromTblLen+1];
    char   sMerName[MerNameLen+1];
    char   sBankFee[BankFeeLen+1];
    char   sMerFee[MerFeeLen+1];
    char   sInAcNo[InAcNoLen+1];
    char   sOpnBr[DeptNoLen+1];
    char   sInMode[InModeLen+1];
    char   sTlrId[TlrIdLen+1];
    char   sTckNo[TckNoLen+1];
    char   sClearAmt[ClearAmtLen+1];
    char   sOMerId[MerIdLen+1];
    char   sRepFlg[RepFlgLen+1];
  EXEC SQL END DECLARE SECTION;
    int    iRet=0;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin PCLDtlToRpt.\n" );
/*
**  检查参数个数
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "PCL999", "参数个数错" );
    bpErrorLog( trdata, "PCLDtlToRpt: 参数个数错!" );
    return( -1 );
  }
/*
**  清除历史记录
*/
  EXEC SQL delete from PclTmpRpt;
  if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND ) ) {
    bpAddResult( TrNode, "PCL999", "清理表【PCLTMPRPT】异常" );
    bpErrorLog(trdata, "PCLDtlToRpt:清理表【PCLTMPRPT】异常[%d]", SQLCODE);
    return( -1 );
  }
/*
**  入口参数处理
*/
  ClearStr( sActDat );
  ClearStr( sTmpDt );
  ClearStr( sOMerId );
  ClearStr( sRepFlg );
  if ( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【ActDat】错误" );
    bpErrorLog( trdata, "PCLDtlToRpt:获取节点【ActDat】错误!\n" );
    return( -1 );
  }
  strcpy( sTmpDt, Step_Arg1 );

  EXEC SQL DECLARE c_txndtl2 CURSOR FOR
      select TranAmt, CtrPostDate, MerId, MerAccFromTbl, ClearAmt, MerName, BankFee, MerFee, InAcNo, OpnBr, InMode, TlrId, TckNo
        From PclTxnDtl
       where CtrPostDate = :sTmpDt
         and Sts in ( '1', '2' )
    order by MerId;
  EXEC SQL OPEN c_txndtl2;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult(TrNode, "PCL999", "查询表【PclTxnDtl】异常－打开游标错" );
    bpErrorLog(trdata, "PCLDtlToRpt:查询表【PclTxnDtl】异常－打开游标错[%d]", SQLCODE);
    return( -1 );
  }

  for( ; ; ) {
    ClearStr( sTranAmt );
    ClearStr( sCtrPostDate );
    ClearStr( sMerId );
    ClearStr( sMerAccFromTbl );
    ClearStr( sClearAmt );
    ClearStr( sMerName );
    ClearStr( sBankFee );
    ClearStr( sMerFee );
    ClearStr( sInAcNo );
    ClearStr( sOpnBr );
    ClearStr( sInMode );
    ClearStr( sTlrId );
    ClearStr( sTckNo );

    EXEC SQL FETCH c_txndtl2 into :sTranAmt, :sCtrPostDate, :sMerId, :sMerAccFromTbl, :sClearAmt, :sMerName, :sBankFee, :sMerFee, :sInAcNo, :sOpnBr, :sInMode, :sTlrId, :sTckNo;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      EXEC SQL CLOSE c_txndtl2;
      bpAddResult(TrNode, "PCL999", "查询表【PclTxnDtl】异常－FETCH出错" );
      bpErrorLog(trdata, "PCLDtlToRpt:查询表【PclTxnDtl】异常－FETCH出错【%d】", SQLCODE);
      return( -1 );
    }
    if( strcmp( sMerId, sOMerId )==0 ) {
      strcpy( sRepFlg, "0" );
    } else {
      strcpy( sRepFlg, "1" );
      strcpy( sOMerId, sMerId );
    }
/*
**  选择不同清算情况进行数据库处理
*/
    if( ( strcmp( sInMode, "2" )==0 ) || ( strcmp( sRepFlg, "1" )==0 ) ) { /*  按交易单笔入帐或第一笔业务  */
      EXEC SQL INSERT INTO PCLTMPRPT( MerId, CtrPostDate, TlrId, TckNo, InAcNo, TranAmt, ClearAmt, BankFee, MerFee, InMode, OpnBr, MerAccFromTbl, MerName )
                  VALUES( :sMerId, :sCtrPostDate, :sTlrId, :sTckNo, :sInAcNo, cast( bigint(:sTranAmt) as char(15) ), cast( bigint(:sClearAmt) as char(15) ), cast( bigint(:sBankFee) as char(15) ), cast( bigint(:sMerFee) as char(15) ), :sInMode, :sOpnBr, :sMerAccFromTbl, :sMerName );
      if( SQLCODE != SQL_SUCCESS ) {
        EXEC SQL CLOSE c_txndtl2;
        bpAddResult(TrNode, "PCL999", "插入表【PCLTMPRPT】异常" );
        bpErrorLog( trdata, "PCLDtlToRpt:插入表【PCLTMPRPT】异常－【%d】-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sMerId,sCtrPostDate,sTlrId,sTckNo,sInAcNo,sTranAmt,sClearAmt,sBankFee,sMerFee,sInMode,sOpnBr,sMerAccFromTbl,sMerName);
        return( -1 );
      }
    } else {                                        /*  按交易总额入帐  */
      EXEC SQL Update PclTmpRpt
                  set TranAmt = cast( ( bigint( TranAmt ) + bigint( :sTranAmt ) ) as char(15) ),
                      ClearAmt = cast( ( bigint( ClearAmt ) + bigint( :sClearAmt ) ) as char(15) ),
                      BankFee = cast( ( bigint( BankFee ) + bigint( :sBankFee ) ) as char(15) ),
                      MerFee = cast( ( bigint( MerFee ) + bigint( :sMerFee ) ) as char(15) )
                where Merid = :sMerId
                  and CtrPostDate = :sCtrPostDate;
      if( SQLCODE != SQL_SUCCESS ) {
        EXEC SQL CLOSE c_txndtl2;
        bpAddResult(TrNode, "PCL999", "更新表【PCLTMPRPT】异常" );
        bpErrorLog( trdata, "PCLDtlToRpt:Update出错[%d][%s][%s]", SQLCODE, sCtrPostDate, sMerId );
        return( -1 );
      }
    }
  }
  EXEC SQL CLOSE c_txndtl2;
  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End PCLDtlToRpt.\n" );
  return (0);
}
/******************************************************************************
  Function        : PCLGetTrmInf
  Description     : 根据POS商户号获取对应分行号
  Calls           : 被本函数调用的函数清单
  Called By       : 调用本函数的函数清单
  Table Accessed  : PclTrmAgt
  Table Updated   : 
  Input           : ETF *TrNode  输入树
                    ST_TranData* trdata  公共结构
                    char* args  参数
                    DBConHandle* DBHandle  数据库句柄
  Output          : 对输出参数的说明
  Return          : 0--成功 小于0--失败
  Others          : 其它说明
******************************************************************************/
int PCLGetTrmInf(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sPosTyp[PosTypLen+1];
    char   sMerId[MerIdLen+1];
    char   sTermId[TermIdLen+1];
    char   sOpnBr[BrNoLen+1];
    char   sInAcNo[ActNoLen+1];
    char   sUniNo[UniNoLen+1];
    char   sMobTel[MobTelLen+1];
  EXEC SQL END DECLARE SECTION;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin PCLGetTrmInf.\n" );
/*
**  初始化返回数据
*/
  ClearStr( sPosTyp );
  ClearStr( sMerId  );
  ClearStr( sTermId );
  ClearStr( sOpnBr  );
  ClearStr( sInAcNo );
  ClearStr( sUniNo  );
  ClearStr( sMobTel );
/*
**  获取商户号和终端号
*/
  if ( etfGetChildValue(TrNode, "PosTyp", sPosTyp, PosTypLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【PosTyp】错误" );
    bpErrorLog( trdata, "PCLGetTrmInf:获取节点【PosTyp】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "MerId", sMerId, MerIdLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【MerId】错误" );
    bpErrorLog( trdata, "PCLGetTrmInf:获取节点【MerId】错误!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TermId", sTermId, TermIdLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【TermId】错误" );
    bpErrorLog( trdata, "PCLGetTrmInf:获取节点【TermId】错误!\n" );
    return( -1 );
  }
  EXEC SQL select InAcNo, OpnBr, UniNo, MobTel
             into :sInAcNo, :sOpnBr, :sUniNo, :sMobTel
             from PclTrmAgt
            where PosTyp =:sPosTyp
              and MerId  =:sMerId
              and TermId =:sTermId
              and Sts='0';
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult( TrNode, "PB0249", "PCLGetTrmInf: 没有对应商户的资料" );
    bpErrorLog( trdata, "PCLGetTrmInf: 没有对应商户号【%s】【%s】【%s】的资料!",sPosTyp,sMerId, sTermId );
    return( -1 );
  }
  etfAddOrRepNode( TrNode, "BrNo",   sOpnBr,  BrNoLen   );
  etfAddOrRepNode( TrNode, "ActNo",  sInAcNo, ActNoLen  );
  etfAddOrRepNode( TrNode, "UniNo",  sUniNo,  UniNoLen  );
  etfAddOrRepNode( TrNode, "MobTel", sMobTel, MobTelLen );
  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End PCLGetTrmInf.\n" );
  return (0);
}
/******************************************************************************
  Function          : PCLDGetFee
  Description       : 直联POS转帐相关费用
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : PclTrmAgt
  Table Updated     : 无
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int PCLDGetFee(ETF *TrNode, TranData *trdata, PbItemData args, DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sMerId[MerIdLen+1];
    char   sTermId[TermIdLen+1];
    char   sTxnAmt[TxnAmtLen+1];
    char   sFeeAmt[TxnAmtLen+1];
  EXEC SQL END DECLARE SECTION;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin PCLDGetFee.\n" );
/*
**  检查输入参数个数
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "PCLDGetFee: 参数个数错" );
    bpErrorLog( trdata, "PCLDGetFee: 参数个数错!" );
    return( -1 );
  }
/*
**  依次获取账号，交易金额
*/
  ClearStr( sMerId  );
  ClearStr( sTermId );
  ClearStr( sTxnAmt );
  ClearStr( sFeeAmt );
  strcpy( sMerId,  Step_Arg1 );
  strcpy( sTermId, Step_Arg2 );
  strcpy( sTxnAmt, Step_Arg3 );
/*
**  根据输入要素计算费率
*/
  EXEC SQL select case when FeeMod='0' then right( ('000000000000000'||rtrim(char(BIGINT(:sTxnAmt)*BIGINT(FeeRat)/10000))),15) 
                  else FeeAmt
                  end FeeAmt
             into :sFeeAmt
             from PclTrmAgt
            where MerId  =:sMerId
              and TermId =:sTermId
              and Sts='0';
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult( TrNode, "PB2049", "PCLDGetFee: 没有对应商户的资料表" );
    bpErrorLog( trdata, "PCLDGetFee: 没有对应商户【%s】【%s】的资料表!", sMerId, sTermId );
    return( -1 );
  }
  etfAddOrRepNode( TrNode, "FEEAMT", sFeeAmt, TxnAmtLen );
  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End PCLDGetFee.\n" );
  return (0);
}
/******************************************************************************
  Function          : PCLGetFee
  Description       : 直联POS转帐相关费用
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单 
  Table Accessed    : PclFeeRat
  Table Updated     : 无
  Input             : ETF *TrNode  输入树 
                      ST_TranData* trdata  公共结构
                      char* args  参数  
                      DBConHandle* DBHandle  数据库句柄   
  Output            : 对输出参数的说明。     
  Return            : 0--成功 小于0--失败   
  Others            : 其它说明             
******************************************************************************/
int PCLGetFee(ETF *TrNode, TranData *trdata, PbItemData args, DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sBrNo[BrNoLen+1];
    char   sSysFlg[SysFlgLen+1];
    char   sTxnAmt[TxnAmtLen+1];
    char   sFeeAmt[TxnAmtLen+1];
  EXEC SQL END DECLARE SECTION;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin PCLGetFee.\n" );
/*
**  检查输入参数个数
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "PCLGetFee: 参数个数错" );
    bpErrorLog( trdata, "PCLGetFee: 参数个数错!" );
    return( -1 );
  }
/*
**  依次获取账号，交易金额
*/
  ClearStr( sBrNo   );
  ClearStr( sSysFlg );
  ClearStr( sTxnAmt );
  ClearStr( sFeeAmt );
  strcpy( sBrNo  , Step_Arg1 );
  strcpy( sSysFlg, Step_Arg2 );
  strcpy( sTxnAmt, Step_Arg3 );
/*
**  根据输入要素计算费率
*/
  EXEC SQL select case when FeeMod='0' then right( ('000000000000000'||rtrim(char(BIGINT(:sTxnAmt)*BIGINT(FeeRat)/10000))),15) 
                  else FeeAmt
                  end FeeAmt
             into :sFeeAmt
             from PclFeeRat
            where SysFlg =:sSysFlg
              and BrNo   =:sBrNo
              and MinAmt <= :sTxnAmt
              and MaxAmt >:sTxnAmt
              and Sts='0';
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult( TrNode, "PB2049", "PCLGetFee: 没有对应商户的资料表" );
    bpErrorLog( trdata, "PCLGetFee: 没有对应【%s】【%s】的资料表!", sBrNo, sSysFlg );
    return( -1 );
  }
  etfAddOrRepNode( TrNode, "FEEAMT", sFeeAmt, TxnAmtLen );
  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End PCLGetFee.\n" );
  return (0);
}
/******************************************************************************
  Function        : PCLDFilToDb
  Description     : POS 交易明细文件入库
  Calls           : 被本函数调用的函数清单
  Called By       : 调用本函数的函数清单 
  Table Accessed  : PclDTxnDtl PclTrmAgt
  Table Updated   : PclDTxnDtl 
  Input           : ETF *TrNode  输入树
                    ST_TranData* trdata  公共结构
                    char* args  参数
                    DBConHandle* DBHandle  数据库句柄
  Output          : 对输出参数的说明
  Return          : 0--成功 小于0--失败
  Others          : 其它说明
******************************************************************************/
int PCLDFilToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sClrDt[ActDatLen+1];
    char   sBrNo[BrNoLen+1];
    char   sPosTyp[PosTypLen+1];

    char   sRefNo[RefNoLen+1];
    char   sCtrPostDate[ActDatLen+1];
    char   sCtrDt[CtrDtLen+1];
    char   sCtrTime[CtrTimeLen+1];
    char   sTranAcc[TranAccLen+1];
    char   sDMti[DMtiLen+1];
    char   sProcCode[ProcCodeLen+1];
    char   sCdFlag[CdFlagLen+1];
    char   sTranAmt[TranAmtLen+1];
    char   sFeeAmt[TxnAmtLen+1];
    char   sOrigRefNo[OrigRefNoLen+1];
    char   sMerId[MerIdLen+1];
    char   sTermId[TermIdLen+1];
    char   sCtrTrn[CtrTrnLen+1];
    char   sRepCode[RepCodeLen+1];
    char   sBankId[BankIdLen+1];
    char   sTBusTp[TBusTpLen+1];

    char   sTxnSts[StsLen+1];
    char   sTmpAmt[TxnAmtLen+1];
    char   sTxnAmt[TxnAmtLen+1];
    char   sActNo[ActNoLen+1];
    char   sActNm[ActNmLen+1];
    char   sDeptNo[DeptNoLen+1];
    char   sOpnBr[BrNoLen+1];
    char   sCusFee[TxnAmtLen+1];
    char   sThdFee[TxnAmtLen+1];
    char   sBnkFee[TxnAmtLen+1];
    char   sClrAct[ActNoLen+1];
    char   sErrMsg[ErrMsgLen+1];
  EXEC SQL END DECLARE SECTION;
    int    iRet=0, i=0;
    FILE  *fp;
    char  fname[128];
    char  sMsg[MsgLen+1];
    char  sBgnFlg[FlagLen+1];
    char  sEndFlg[FlagLen+1];
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin PCLDFilToDb.\n" );
/*
**  检查参数个数
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "参数个数错" );
    bpErrorLog( trdata, "PCLDFilToDb: 参数个数错!" );
    return( -1 );
  }
/*
**  处理数据文件
*/
  ClearStr( sClrDt  );
  ClearStr( sBrNo   );
  ClearStr( sPosTyp );
  ClearStr( fname );
  strcpy( sClrDt, Step_Arg1 );
    if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【BrNo】错误" );
    bpErrorLog( trdata, "PCLDFilToDb:获取节点【BrNo】错误!\n" );
    return( -1 );
  }
  strcpy( sPosTyp, Step_Arg3 );
  sprintf( fname, "%s/%s", getenv("WORKDIR"), Step_Arg2 );
  fp =fopen( fname,"r" );
  if( fp == NULL ) {
    fclose( fp );
    bpAddResult( TrNode, "PCL999", "打开POS明细文件错" );
    bpErrorLog( trdata, "PCLDFilToDb:打开POS明细文件【%s】失败!\n", fname );
    return( -1 );
  }
/*
**  逐条处理明细文件
*/
  ClearStr( sBgnFlg );
  ClearStr( sEndFlg );
  strcpy( sBgnFlg, "0" );
  strcpy( sEndFlg, "0" );
  while( !feof( fp ) ) {
  i++;
/*
**  文件数据变量初始化
*/
    ClearStr( sRefNo );
    ClearStr( sCtrPostDate );
    ClearStr( sCtrDt );
    ClearStr( sCtrTime );
    ClearStr( sTranAcc );
    ClearStr( sDMti );
    ClearStr( sProcCode );
    ClearStr( sCdFlag );
    ClearStr( sTranAmt );
    ClearStr( sFeeAmt );
    ClearStr( sOrigRefNo );
    ClearStr( sMerId );
    ClearStr( sTermId );
    ClearStr( sCtrTrn );
    ClearStr( sRepCode );
    ClearStr( sBankId );
    ClearStr( sTBusTp );
    ClearStr( sTxnAmt );
    ClearStr( sErrMsg );
    ClearStr( sActNo  );
    ClearStr( sActNm  );
    ClearStr( sDeptNo );
    ClearStr( sOpnBr  );
    ClearStr( sCusFee );
    ClearStr( sThdFee );
    ClearStr( sBnkFee );
    ClearStr( sClrAct );
    ClearStr( sErrMsg );
    if ( i==1 ) {
      fscanf( fp, "%[^,]", sRefNo );   /*系统参考号*/
    } else {
      fscanf( fp, "\n%[^,]", sRefNo ); /*系统参考号*/
    }
    fscanf( fp, ",%[^,]", sCtrPostDate );   /*清算日*/
    fscanf( fp, ",%[^,]", sCtrDt       );   /*交易发生日*/
    fscanf( fp, ",%[^,]", sCtrTime     );   /*交易时间*/
    fscanf( fp, ",%[^,]", sTranAcc     );   /*转出卡帐号*/
    fscanf( fp, ",%[^,]", sDMti        );   /*信息码*/
    fscanf( fp, ",%[^,]", sProcCode    );   /*处理码*/
    fscanf( fp, ",%[^,]", sCdFlag      );   /*借贷标志*/
    fscanf( fp, ",%[^,]", sTranAmt     );   /*交易金额*/
    ClearStr( sTmpAmt );
    fscanf( fp, ",%[^,]", sTmpAmt      );   /*手续费金额*/
    sprintf( sFeeAmt, "%015d", atoi(sTmpAmt) );
    fscanf( fp, ",%[^,]", sOrigRefNo   );   /*原系统参考号*/
    fscanf( fp, ",%[^,]", sMerId       );   /*商户号*/
    fscanf( fp, ",%[^,]", sTermId      );   /*终端机号*/
    fscanf( fp, ",%[^,]", sCtrTrn      );   /*POS交易流水号*/
    fscanf( fp, ",%[^,]", sRepCode     );   /*交易响应码*/
    fscanf( fp, ",%[^,]", sBankId      );   /*银行代码*/
    fscanf( fp, ",%[^\n]", sTBusTp     );   /*业务代码*/
    if( strcmp( sRefNo, "000000000000" ) == 0 ) {
      strcpy( sBgnFlg,"1" );
      continue;
    }
    if( strcmp( sRefNo, "999999999999" ) == 0 ) {
      strcpy( sEndFlg,"1" );
      break;
    }
/*
**  部分数据按要求格式转换
*/
    sprintf( sTxnAmt, "%015d", atoi(sTranAmt)-abs(atoi(sFeeAmt)) );
/*
**  状态位赋初值
*/
    strcpy( sTxnSts, "0" );
/*
**  判断输入日期是否未POS清算日
*/
    if( memcmp( sClrDt, sCtrPostDate, ActDatLen ) != 0 ) {
      bpErrorLog( trdata, "PCLDFilToDb:数据日期非POS清算日【%s】【%s】【%s】", sClrDt, sCtrPostDate, sRefNo );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "清算数据非直联POS清算日数据" );
      goto DB_INSERT;
    }
/*
**  冲正交易，不清算
*/
    if( strcmp( sCdFlag, "D" )==0 ) strcpy( sTxnSts, "A" );
/*
**  根据商户号、终端号获取记帐帐号、计算手续费，并检查合法性
*/
    EXEC SQL select InAcNo, InAcNm, DeptNo, OpnBr, 
                    case when FeeMod='0' then right( ('000000000000000'||rtrim(char(BIGINT(:sTxnAmt)*BIGINT(FeeRat)/10000))),15)
                         else FeeAmt
                         end CusFee,
                    case when TFeeMod='0' then right( ('000000000000000'||rtrim(char(BIGINT(:sFeeAmt)*BIGINT(TFeeRat)/10000))),15)
                         else TFeeAmt
                         end ThdFee
               into :sActNo, :sActNm, :sDeptNo, :sOpnBr, :sCusFee, :sThdFee
               from PclTrmAgt
              where PosTyp=:sPosTyp
                and MerId  =:sMerId
                and TermId =:sTermId
                and Sts ='0';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLDFilToDb:该商户终端号未登记或异常：PosTyp【%s】MerId【%s】TermId【%s】", sPosTyp,sMerId,sTermId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "该商户终端号未登记或异常" );
      goto DB_INSERT;
    }
    sprintf( sBnkFee, "%015d", atoi(sFeeAmt)-atoi(sThdFee) );
    if ( atoi(sFeeAmt)<atoi(sThdFee) ) {
      bpErrorLog( trdata, "PCLDFilToDb:该商户号手续费低于天信手续费PosTyp【%s】MerId【%s】TermId【%s】", sPosTyp,sMerId,sTermId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "该商户号手续费低于天信手续费" );
      goto DB_INSERT;
    }
/*
**  根据商户号获取清算内部帐
*/
    EXEC SQL select InAcNo
               into :sClrAct
               from PclCusAgt
              where PosTyp =:sPosTyp
                and BusiNo =:sMerId
                and Sts ='0';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLDFilToDb:该商户号未登记或异常【%s】", sMerId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "该商户号未登记或异常" );
      goto DB_INSERT;
    }
/*
**  根据商户
*/
/*
**  数据入库
*/
DB_INSERT:
    EXEC SQL insert into PclDTxnDtl( TxnSts,RefNo,CtrPostDate,CtrDt,CtrTime,TranAcc,DMti,ProcCode,CdFlag,TranAmt,TxnAmt,FeeAmt,BnkFee,ThdFee,OrigRefNo,MerId,TermId,CtrTrn,RepCode,BankId,TBusTp,ClrAct,ActNo,ActNm,DeptNo,OpnBr,ErrMsg )
                values( :sTxnSts,:sRefNo,:sCtrPostDate,:sCtrDt,:sCtrTime,:sTranAcc,:sDMti,:sProcCode,:sCdFlag,:sTranAmt,:sTxnAmt,:sFeeAmt,:sBnkFee,:sThdFee,:sOrigRefNo,:sMerId,:sTermId,:sCtrTrn,:sRepCode,:sBankId,:sTBusTp,:sClrAct,:sActNo,:sActNm,:sDeptNo,:sOpnBr,:sErrMsg );
    if( SQLCODE != SQL_SUCCESS ) {
      fclose( fp );
      bpAddResult( TrNode, "PCL999", "PCLDFilToDb:INSERT表【PclDTxnDtl】出错" );
      bpErrorLog(trdata, "PCLDFilToDb:INSERT出错[%d]-数据内容-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sTxnSts,sRefNo,sCtrPostDate,sCtrDt,sCtrTime,sTranAcc,sDMti,sProcCode,sCdFlag,sTranAmt,sTxnAmt,sFeeAmt,sOrigRefNo,sMerId,sTermId,sCtrTrn,sRepCode,sBankId,sTBusTp,sActNo,sActNm,sDeptNo,sOpnBr,sErrMsg );
      return( -1 );
    }
  }
/*
**  关闭处理文件
*/
  fclose( fp );
/*
**  处理撤销交易（将数据库记录置为"A"）
**  以下步骤是在保证撤销交易的ORIGCTRTRN和原交易的CTRTRN相同的基础上实现的，可能会有误
*/
  EXEC SQL DECLARE c_dtxndtl1 CURSOR FOR
      select TranAmt, OrigRefNo, MerId, TermId
        from PclDTxnDtl
       where CtrPostDate =:sClrDt
          and TxnSts in ( '0','A' )
         and CdFlag ='D';
  EXEC SQL OPEN c_dtxndtl1;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult(TrNode, _DB_QUERY_ERR, "查询表【PclTxnDtl】异常" );
    bpErrorLog(trdata, "PCLDFilToDb:查询表【PclTxnDtl】OPEN游标错[%d]", SQLCODE);
    return( -1 );
  }
  for( ; ; ) {
    ClearStr( sTranAmt );
    ClearStr( sOrigRefNo );
    ClearStr( sMerId );
    EXEC SQL FETCH c_dtxndtl1 INTO :sTranAmt, :sOrigRefNo, :sMerId, :sTermId;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLDFilToDb:FETCH出错[%d]", SQLCODE );
      iRet = -1;
      break;
    }
    EXEC SQL update PclDTxnDtl
                set TxnSts = 'A'
              where CtrPostDate = :sClrDt
                and MerId = :sMerId
                and TermId = :sTermId
                and ( OrigRefNo = :sOrigRefNo or RefNo = :sOrigRefNo )
                and TranAmt = :sTranAmt;
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog(trdata, "PCLDFilToDb:修改表【PclDTxnDtl】异常[%d]【%s】【%s】【%s】", SQLCODE, sClrDt, sMerId, sRefNo);
      iRet = -1;
      break;
    }
  }
  EXEC SQL CLOSE c_dtxndtl1;
  if( ( iRet != 0 ) || ( strcmp(sBgnFlg,"1")!=0 ) || ( strcmp( sEndFlg,"1" )!=0 ) ) {
    bpAddResult(TrNode, "PCL999", "数据入库失败或数据文件不完整" );
    bpErrorLog(trdata, "PCLDFilToDb:文件【%s】入库失败或不完整",fname );
    return( -1 );
  }
  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End PCLDFilToDb.\n" );
  return iRet;
}
/******************************************************************************
  Function        : PCLIFilToDb
  Description     : 间联POS入账明细文件入库
  Calls           : 被本函数调用的函数清单
  Called By       : 调用本函数的函数清单 
  Table Accessed  : PclITxnDtl PclTrmAgt
  Table Updated   : PclITxnDtl 
  Input           : ETF *TrNode  输入树
                    ST_TranData* trdata  公共结构
                    char* args  参数
                    DBConHandle* DBHandle  数据库句柄
  Output          : 对输出参数的说明
  Return          : 0--成功 小于0--失败
  Others          : 其它说明
******************************************************************************/
int PCLIFilToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sCtrPostDate[ActDatLen+1];
    char   sBrNo[BrNoLen+1];
    char   sPosTyp[PosTypLen+1];
    char   sActDat[ActDatLen+1];

    char   sTotNum[TotNumLen+1];
    char   sTotAmt[TotAmtLen+1];
    char   sTotFee[TotFeeLen+1];

    char   sTrmTyp[TrmTypLen+1];
    char   sMerId[MerIdLen+1];
    char   sTermId[TermIdLen+1];
    char   sTranAmt[TranAmtLen+1];
    char   sFeeAmt[TxnAmtLen+1];
    char   sTxnAmt[TxnAmtLen+1];
    char   sClrAct[ActNoLen+1];

    char   sTxnSts[StsLen+1];
    char   sLogNo[LogNoLen+1];
    char   sDate[DateLen+1];
    char   sSerial[SerialLen+1];
    char   sActNo[ActNoLen+1];
    char   sActNm[ActNmLen+1];
    char   sDeptNo[DeptNoLen+1];
    char   sOpnBr[DeptNoLen+1];
    char   sErrMsg[ErrMsgLen+1];
  EXEC SQL END DECLARE SECTION;
    int    iRet=0, iCount=0;
    FILE  *fp;
    char  sBuf[MaxBufLen+1];
    char  sFlag[FlagLen+1];
    char  fname[128];
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin PCLIFilToDb.\n" );
/*
**  检查参数个数
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "参数个数错" );
    bpErrorLog( trdata, "PCLIFilToDb: 参数个数错!" );
    return( -1 );
  }
/*
**  处理数据文件
*/
  ClearStr( sCtrPostDate );
  ClearStr( sBrNo   );
  ClearStr( sPosTyp );
  ClearStr( sActDat );
  ClearStr( fname   );
  ClearStr( sTotNum );
  ClearStr( sTotAmt );
  ClearStr( sTotFee );
  strcpy( sCtrPostDate, Step_Arg1 );
  strcpy( sPosTyp, Step_Arg3 );
  sprintf( fname, "%s/%s", getenv("WORKDIR"), Step_Arg2 );
  fp =fopen( fname,"r" );
  if( fp == NULL ) {
    fclose( fp );
    bpAddResult( TrNode, "PCL999", "打开POS明细文件错" );
    bpErrorLog( trdata, "PCLIFilToDb:打开POS明细文件【%s】失败!\n", fname );
    return( -1 );
  }

  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【BrNo】错误" );
    bpErrorLog( trdata, "PCLIFilToDb:获取节点【BrNo】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【BrNo】错误" );
    bpErrorLog( trdata, "PCLIFilToDb:获取节点【BrNo】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TotNum", sTotNum, TotNumLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【TotNum】错误" );
    bpErrorLog( trdata, "PCLIFilToDb:获取节点【TotNum】错误!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TotAmt", sTotAmt, TotAmtLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "获取节点【TotAmt】错误" );
    bpErrorLog( trdata, "PCLIFilToDb:获取节点【TotAmt】错误!\n" );
    return( -1 );
  }
/*
**  逐条处理明细文件
*/
  iCount=0;
  strcpy( sFlag, "0" );
/*
** 一次性获取流水号，避免并发问题
*/
  ClearStr( sLogNo );
  ClearStr( sDate  );
  ClearStr( sSerial );
  if( sqnGetLogNo( sLogNo, atol(sTotNum) ) < 0 ) {
     bpAddResult(TrNode, "PCL999", "取前置流水号出错" );
     bpErrorLog(trdata, "PCLIFilToDb:取前置流水号出错" );
     return( -1 );
  }
  memcpy( sDate, sLogNo, DateLen );
  memcpy( sSerial, sLogNo+DateLen, SerialLen );
/*
** 文件解析入库
*/
  while( !feof( fp ) ) {
    if( atol(sTotNum)==iCount ) {
      strcpy( sFlag,"1" );
      break;
    } else {
      iCount++;
    }
/*
**  文件数据变量初始化
*/
    ClearStr( sTrmTyp );
    ClearStr( sMerId   );
    ClearStr( sTermId  );
    ClearStr( sTranAmt );
    ClearStr( sFeeAmt  );
    ClearStr( sTxnAmt  );
    ClearStr( sClrAct  );
    ClearStr( sActNo   );
    ClearStr( sActNm   );
    ClearStr( sDeptNo  );
    ClearStr( sOpnBr   );
    ClearStr( sErrMsg  );
    if ( iCount==1 ) {
      fscanf( fp, "%[^,]", sMerId );   /*商户号*/
    } else {
      fscanf( fp, "\n%[^,]", sMerId ); /*商户号*/
    }
    fscanf( fp, ",%[^,]", sTermId  );   /*终端机号*/
    ClearStr( sBuf );
    fscanf( fp, ",%[^,]", sBuf     );   /*交易金额*/
    sprintf( sTranAmt, "%012d", atoi(sBuf) );
    fscanf( fp, ",%[^\n]", sBuf    );   /*手续费金额*/
    sprintf( sFeeAmt, "%012d", atoi(sBuf) );
/*
**  部分数据按要求格式转换
*/
    sprintf( sTxnAmt, "%015d", atoi(sTranAmt)-atoi(sFeeAmt) );
/*
**  状态位赋初值
*/
    strcpy( sTxnSts, "0" );
/*
**  根据商户号、终端号获取记帐帐号、计算手续费，并检查合法性
*/
    EXEC SQL select TrmTyp, InAcNo, InAcNm, DeptNo, OpnBr
               into :sTrmTyp, :sActNo, :sActNm, :sDeptNo, :sOpnBr
               from PclTrmAgt
              where PosTyp =:sPosTyp
                and MerId  =:sMerId
                and TermId =:sTermId
                and Sts ='0';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLIFilToDb:该商户终端号未登记或异常：PosTyp【%s】MerId【%s】TermId【%s】", sPosTyp,sMerId,sTermId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "该商户终端号未登记或异常" );
      goto DB_INSERT;
    }
/*
**  根据商户号获取清算内部帐
*/
    EXEC SQL select InAcNo
               into :sClrAct
               from PclCusAgt
              where PosTyp =:sPosTyp
                and BusiNo =:sMerId
                and Sts ='0';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLIFilToDb:该商户号未登记或异常PosTyp【%s】MerId【%s】", sPosTyp,sMerId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "该商户号未登记或异常" );
      goto DB_INSERT;
    }
/*
**  数据入库
*/
DB_INSERT:
    EXEC SQL insert into PclITxnDtl( TxnSts,CtrPostDate,TranAmt,TxnAmt,FeeAmt,PosTyp,MerId,TrmTyp,TermId,LogNo,ActDat,ClrAct,ActNo,ActNm,DeptNo,OpnBr,ErrMsg )
                             values( :sTxnSts,:sCtrPostDate,:sTranAmt,:sTxnAmt,:sFeeAmt,:sPosTyp,:sMerId,:sTrmTyp,:sTermId,:sLogNo,:sActDat,:sClrAct,:sActNo,:sActNm,:sDeptNo,:sOpnBr,:sErrMsg );
    if( SQLCODE != SQL_SUCCESS ) {
      fclose( fp );
      bpAddResult( TrNode, "PCL999", "PCLIFilToDb:INSERT表【PclITxnDtl】出错" );
      bpErrorLog(trdata, "PCLIFilToDb:INSERT出错[%d]-数据TxnSts【%s】CtrPostDate【%s】TranAmt【%s】TxnAmt【%s】FeeAmt【%s】PosTyp【%s】MerId【%s】TrmTyp【%s】TermId【%s】LogNo【%s】ActDat【%s】ClrAct【%s】ActNo【%s】ActNm【%s】DeptNo【%s】OpnBr【%s】ErrMsg【%s】",sTxnSts,sCtrPostDate,sTranAmt,sTxnAmt,sFeeAmt,sPosTyp,sMerId,sTrmTyp,sTermId,sLogNo,sActDat,sClrAct,sActNo,sActNm,sDeptNo,sOpnBr,sErrMsg );
      return( -1 );
    }
    ClearStr( sLogNo );
    sprintf( sSerial,"%08ld", atol(sSerial)+1 );
    sprintf( sLogNo,"%s%s", sDate, sSerial );
  }
/*
**  关闭处理文件
*/
  fclose( fp );
  if( ( iRet != 0 ) || ( strcmp(sFlag,"1")!=0 ) || ( iCount!=atol(sTotNum) ) ) {
    bpAddResult(TrNode, "PCL999", "数据入库失败或数据文件不完整" );
    bpErrorLog(trdata, "PCLIFilToDb:文件【%s】入库失败或不完整",fname );
    return( -1 );
  }
  bpAddResult(TrNode, "000000", "交易成功" );
  bpTraceLog( trdata, "End PCLIFilToDb.\n" );
  return iRet;
}
