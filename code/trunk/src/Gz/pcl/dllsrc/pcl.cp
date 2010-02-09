/******************************************************************************       
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.            
                                                                                      
  File name   : pcl.cp
  Author      : Jamez
  Version     : 2.0  
  Date        : 2007.04.03  
  Description : POS �Զ�����ϵͳ����ԭ�Ӻ�����
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
  Description     : POS ������ϸ�ļ����
  Calls           : �����������õĺ����嵥
  Called By       : ���ñ������ĺ����嵥 
  Table Accessed  : PclTxnDtl PclCifReg
  Table Updated   : PclTxnDtl
  Input           : ETF *TrNode  ������
                    ST_TranData* trdata  �����ṹ
                    char* args  ����
                    DBConHandle* DBHandle  ���ݿ���
  Output          : �����������˵��
  Return          : 0--�ɹ� С��0--ʧ��
  Others          : ����˵��
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin PCLFileToDb.\n" );
/*
**  ����������
*/
  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, "PCL999", "����������" );
    bpErrorLog( trdata, "PCLFileToDb: ����������!" );
    return( -1 );
  }
/*
**  ���������ļ�
*/
  ClearStr( sClrDt );
  ClearStr( sActDat );
  ClearStr( sBrNo );
  ClearStr( fname );
  strcpy( sClrDt, Step_Arg1 );
  if ( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾ActDat������" );
    bpErrorLog( trdata, "PCLFileToDb:��ȡ�ڵ㡾ActDat������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "BrNo", sBrNo, DeptNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾BrNo������" );
    bpErrorLog( trdata, "PCLFileToDb:��ȡ�ڵ㡾BrNo������!\n" );
    return( -1 );
  }
  sprintf( fname, "%s/%s", getenv("WORKDIR"), Step_Arg2 );
  fp =fopen( fname,"r" );
  if( fp == NULL ) {
    fclose( fp );
    bpAddResult( TrNode, "PCL999", "��POS��ϸ�ļ���" );
    bpErrorLog( trdata, "PCLFileToDb:��POS��ϸ�ļ���%s��ʧ��!\n", fname );
    return( -1 );
  }
/*
**  ����������ϸ�ļ�
*/
  iRet = 0;
  while( !feof( fp ) ) {
/*
**  �ļ����ݱ�����ʼ��
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
**  ���ݿ�����������ʼ��
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
**  �����˻���ϸ�������Ѻ���"-"�ŵ�����
*/
    ClearStr( sTmpFee );
    memcpy( sTmpFee, sMsg+BankFeeOffset, BankFeeLen );
    sprintf( sBankFee, "%012d", abs( atoi( sTmpFee ) ) );
    ClearStr( sTmpFee );
    memcpy( sTmpFee, sMsg+MerFeeOffset, MerFeeLen );
    sprintf( sMerFee, "%012d", abs( atoi( sTmpFee ) ) );
    memcpy( sPrvFlg, sMsg+PrvFlgOffset, PrvFlgLen );
/*
**  �������ݰ�Ҫ���ʽת��
*/
    sprintf( sFeeRat1, "%s%s", "00", sMerStandComm );
    ClearStr( sClearAmt );
    sprintf( sClearAmt, "%012d", atoi( sTranAmt ) - abs( atoi( sMerFee ) ) );
/*
**  ״̬λ�������־����ֵ
*/
    strcpy( sSts, "0" );
    strcpy( sCdFlag, "C" );
/*
**  �ж����������Ƿ�δPOS������
*/
    if( memcmp( sClrDt+CtrPostDateLen, sCtrPostDate, CtrPostDateLen ) != 0 ) {
      bpErrorLog( trdata, "PCLFileToDb:�������ڷ�POS�����ա�%s����%s��", sClrDt, sCtrPostDate );
      iRet = -1;
      strcpy( sSts, "E" );
      strcpy( sAgrBr, sBrNo );
      strcpy( sErrMsg, "�����ļ����ݷ�POS����������" );
      goto DB_INSERT;
    }
/*
**  ��ɱ�־��Ϊ"00"�ģ�������
*/
    if( strcmp( sRepCode, "00" ) != 0 ) strcpy( sSts, "A" );
/*
**  ����̻����Ƿ���ڣ����������򽫴�����к���Ϊ���������кţ���֤�������ȷȡֵ
*/
    EXEC SQL select PosTyp, DeptNo, OpnBr, AgrBr, BankNo, AccFlg, InAcNo, InMode, FeeRat, TopAmt
               into :sPosTyp, :sDeptNo, :sOpnBr, :sAgrBr, :sBankNo, :sAccFlg, :sInAcNo, :sInMode, :sFeeRat2, :sTopAmt
               from PclCusAgt
              where PosTyp='0'
                and BusiNo = :sMerId
                and Sts = '0';    
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLFileToDb:���̻���δ�Ǽǻ��쳣��%s��", sMerId );
      iRet = -1;
      strcpy( sSts, "E" );
      strcpy( sAgrBr, sBrNo );
      strcpy( sErrMsg, "���̻���δ�Ǽǻ��쳣" );
      goto DB_INSERT;
    }
/*
**  ������������Ƿ�һ�� 7299 5511
*/
/*
    if( ( strncmp( sMerId+7, "5271", 4 )==0 ) || ( strncmp( sMerId+7, "5998", 4 )==0 ) || ( strncmp( sMerId+7, "1520", 4 )==0 ) ||
        ( strncmp( sMerId+7, "7299", 4 )==0 ) || ( strncmp( sMerId+7, "5511", 4 )==0 ) ) {
      bpErrorLog( trdata, "PCLFileToDb:���̻�����������Ϊ�㡾%s��", sMerId );
      EXEC SQL select substr(right( '000000000000000' || rtrim(char(bigint(round(bigint(:sTranAmt) * int(:sFeeRat2) / 100000.00,0)))), 15 ),1,15)
                 into :sMerFee
                 from PclCusAgt
                fetch first 1 rows only;
      if( atoi(sMerFee) > atoi(sTopAmt) ) strcpy( sMerFee, sTopAmt );
      sprintf( sClearAmt, "%015d", atoi( sTranAmt ) - atoi( sMerFee ) );
      bpErrorLog( trdata, "PCLFileToDb:���̻�����������ӦΪ��%s��", sMerFee );
    } else {
      if( strcmp( sFeeRat1, sFeeRat2 ) != 0 ) {
        bpErrorLog( trdata, "PCLFileToDb:���̻����������ʲ�һ�¡�%s����%s��", sMerId, sFeeRat1 );
        iRet = -1;
        strcpy( sSts, "E" );
        strcpy( sErrMsg, "���̻����������ʲ�һ��" );
        goto DB_INSERT;
      }
    }
*/
    if( strcmp( sFeeRat1, sFeeRat2 ) != 0 ) {
      bpErrorLog( trdata, "PCLFileToDb:���̻����������ʲ�һ�¡�%s����%s��", sMerId, sFeeRat1 );
      iRet = -1;
      strcpy( sSts, "E" );
      strcpy( sErrMsg, "���̻����������ʲ�һ��" );
      goto DB_INSERT;
    }
/*
**  ���ڰ������ܶ����ʵĿͻ�������������Ϊ���׽��
    if( strcmp( sInMode, "0" ) == 0 ) {
      strcpy( aClearAmt, aTranAmt );
    }
*/
/*
**  �ų��������Ľ���
*/
    if( ( ( ( strcmp( sTxCode, "PER" ) == 0 )||( strcmp( sTxCode, "I22" ) == 0 ) ) && ( strcmp( sEndFlag, "02" ) == 0 ) ) ||
      ( ( strcmp( sTxCode, "PEC" ) == 0 ) && ( strcmp( sEndFlag, "03" ) == 0 ) ) ||
      ( ( strcmp( sTxCode, "ACR" ) == 0 ) && ( strcmp( sEndFlag, "02" ) == 0 ) ) ||
      ( ( strcmp( sTxCode, "ACC" ) == 0 ) && ( strcmp( sEndFlag, "03" ) == 0 ) ) ||
      ( ( strcmp( sTxCode, "ECC" ) == 0 ) && ( strcmp( sEndFlag, "03" ) == 0 ) ) ) {
      strcpy( sSts, "A" );
    }
/*
**  �����˻����ף��������־λ��Ϊ"D"�跽���������˷�ʽ��Ϊ�������ˣ�
*/ 
    if( strcmp( sTxCode, "RSA" ) == 0 ) {
      strcpy( sCdFlag, "D" );
      strcpy( sInMode, "2" );
    }
/*
**  �������
*/
DB_INSERT:
    EXEC SQL insert into PclTxnDtl( Sts, SeqNo, IssCode, RecvIns, TranAcc, AcqCode, ForWins, AcqIns, RefNo, CtrDt, CtrTime, CtrTrn, TranAmt, MerStandComm, Mti, ProcCode, MerType, CtrPostDate, TermId, MerId, MerAccFromTbl, TranCurr, ClearAmt, ManuAuthFlag, GnetAuthFlag, AuthCode, TxCode, RepCode, MerName, OrigCtrTrn, OrigRefNo, EndFlag, BankFee, MerFee, PrvFlg, InAcNo, CdFlag, DeptNo, OpnBr, AgrBr, BankNo, AccFlg, InMode, DskNo, LogNo, ActDat, HLogNo, TlrId, TckNo, SPrtNum, RPrtNum, ErrMsg )
                values( :sSts, :sSeqNo, :sIssCode, :sRecvIns, :sTranAcc, :sAcqCode, :sForwIns, :sAcqIns, :sRefNo, :sCtrDt, :sCtrTime, :sCtrTrn, :sTranAmt, :sFeeRat1, :sMti, :sProcCode, :sMerType, :sClrDt, :sTermId, :sMerId, :sMerAccFromTbl, :sTranCurr, :sClearAmt, :sManuAuthFlag, :sGnetAuthFlag, :sAuthCode, :sTxCode, :sRepCode, :sMerName, :sOrigCtrTrn, :sOrigRefNo, :sEndFlag, :sBankFee, :sMerFee, :sPrvFlg, :sInAcNo, :sCdFlag, :sDeptNo, :sOpnBr, :sAgrBr, :sBankNo, :sAccFlg, :sInMode, ' ', ' ', :sActDat, ' ', ' ', ' ', '00', '00', :sErrMsg );
    if( SQLCODE != SQL_SUCCESS ) {
      fclose( fp );
      bpAddResult( TrNode, "PCL999", "INSERT��PclTxnDtl������" );
      bpErrorLog(trdata, "PCLFileToDb:INSERT����[%d][%s]-��������-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE, sMsg, sSts, sSeqNo, sIssCode, sRecvIns, sTranAcc, sAcqCode, sForwIns, sAcqIns, sRefNo, sCtrDt, sCtrTime, sCtrTrn, sTranAmt, sFeeRat1, sMti, sProcCode, sMerType, sCtrPostDate, sTermId, sMerId, sMerAccFromTbl, sTranCurr, sClearAmt, sManuAuthFlag, sGnetAuthFlag, sAuthCode, sTxCode, sRepCode, sMerName, sOrigCtrTrn, sOrigRefNo, sEndFlag, sBankFee, sMerFee, sCdFlag, sInAcNo, sDeptNo, sBankNo, sAccFlg, sInMode, sErrMsg );
      return( -1 );
    }
  }
/*
**  �رմ����ļ�
*/
  fclose( fp );
/*
**  ���������ף������ݿ��¼��Ϊ"A"��
**  ���²������ڱ�֤�������׵�ORIGCTRTRN��ԭ���׵�CTRTRN��ͬ�Ļ�����ʵ�ֵģ����ܻ�����
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
    bpAddResult(TrNode, "PCL999", "��ѯ��PclTxnDtl���쳣" );
    bpErrorLog(trdata, "PCLFileToDb:��ѯ��PclTxnDtl��OPEN�α��[%d]", SQLCODE);
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
      bpErrorLog( trdata, "PCLFileToDb:FETCH����[%d]", SQLCODE );
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
      bpErrorLog(trdata, "PCLFileToDb:�޸ı�PclTxnDtl���쳣[%d]", SQLCODE);
      iRet = -1;
      break;
    }
  }
  EXEC SQL CLOSE c_txndtl1;
  if( iRet != 0 ) {
    bpAddResult(TrNode, "PCL999", "�������ʧ��" );
    bpErrorLog(trdata, "PCLFileToDb:�����ļ���%s�����ʧ��", fname);
    iRet = -1;
  } else {
    bpAddResult(TrNode, "000000", "���׳ɹ�" );
    bpErrorLog(trdata, "PCLFileToDb:�����ļ���%s�����ɹ�", fname);
  }
  bpTraceLog( trdata, "End PCLFileToDb.\n" );
  return iRet;
}
/******************************************************************************
  Function        : PCLDtlToAcc
  Description     : ����POS������ϸ������������
  Calls           : �����������õĺ����嵥
  Called By       : ���ñ������ĺ����嵥
  Table Accessed  : PclTxnDtl PclCusAgt PclAccJnl
  Table Updated   : PclTxnDtl
  Input           : ETF *TrNode  ������
                    ST_TranData* trdata  �����ṹ
                    char* args  ����
                    DBConHandle* DBHandle  ���ݿ���
  Output          : �����������˵��
  Return          : 0--�ɹ� С��0--ʧ��
  Others          : ����˵��
******************************************************************************/
int PCLDtlToAcc(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  �������
*/
    char   sCtrPostDate[ActDatLen+1];
    char   sClrAct[InAcNoLen+1];
    char   sCdFlag[CdFlagLen+1];
/*
**  ��Сͨ������
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
**  �α����
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
**  �������
*/
    char   sTmpTranAmt[TopAmtLen+1];
    char   sTmpClearAmt[TopAmtLen+1];
    char   sTmpMerFee[TopAmtLen+1];
    char   sOrnCnt[OrnCntLen+1];
  EXEC SQL END DECLARE SECTION;
    long   iCount=0;
/*
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin PCLDtlToAcc.\n" );
/*
**  ����������
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "����������" );
    bpErrorLog( trdata, "PCLDtlToAcc:����������!\n" );
    return( -1 );
  }
/*
**  ��Сͨ��������ʼ��
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
**  ��������������̺š�������ڡ���Сͨ��Ŀ����������������ڡ�ǰ�ý����룩
*/
  if( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾DskNo������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾DskNo������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾ActDat������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾ActDat������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾TTxnCd������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾TTxnCd������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾HTxnCd������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾HTxnCd������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnSt", sHTxnSt, HTxnStLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾HTxnSt������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾HTxnSt������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "IsTxn", sIsTxn, IsTxnLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾IsTxn������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾IsTxn������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFlg", sUpdFlg, UpdFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾UpdFlg������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾UpdFlg������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFld", sUpdFld, UpdFldLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾UpdFld������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾UpdFld������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾TxnObj������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾TxnObj������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾TxnCnl������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾TxnCnl������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾BrNo������" );
    bpErrorLog( trdata, "PCLDtlToAcc:��ȡ�ڵ㡾BrNo������!\n" );
    return( -1 );
  }
/*
**  ��ȡ������������
*/
  ClearStr( sCtrPostDate );
  ClearStr( sClrAct );
  ClearStr( sCdFlag );
  strcpy( sCtrPostDate, Step_Arg1 );
  strcpy( sClrAct, Step_Arg2 );
  strcpy( sCdFlag, Step_Arg3 );
/*
**  ����ϸ��״̬��Ϊ������Booking
*/
  EXEC SQL update PclTxnDtl
              set  Sts='B', DskNo = :sDskNo
            where CtrPostDate =:sCtrPostDate
              and OpnBr =:sBrNo
              and Sts ='0'
              and CdFlag =:sCdFlag;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult(TrNode, "PCL999", "�޸ı�PclTxnDtl���쳣" );
    bpErrorLog(trdata, "PCLDtlToAcc:�޸ı�PclTxnDtl���쳣������ActDat��%s��CtrPostDate��%s��SQLCODE��%d��", sActDat, sCtrPostDate, SQLCODE);
    return( -1 );
  }
/*
**  ����������ϸ�����п��Եȴ������¼
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
    bpAddResult(TrNode, "PCL999", "��ѯ��PclTxnDtl���쳣�����α��" );
    bpErrorLog(trdata, "PCLDtlToAcc:��ѯ��PclTxnDtl���쳣�����α��[%d]", SQLCODE);
    return( -1 );
  }
  for( ; ; ) {
/*
**  �α������ʼ��
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
      bpAddResult(TrNode, "PCL999", "��ѯ��PclTxnDtl���쳣��FETCH����" );
      bpErrorLog(trdata, "PCLDtlToAcc:��ѯ��PclTxnDtl���쳣��FETCH����[%d]", SQLCODE);
      return( -1 );
    }
/*
**  ����ϵͳ�⡢������ʻ��쳣����ͨ���ڲ��ʻ���ת�����ʽ����Լ�̻������ʷ�ʽ�޸�Ϊ��8���������ܶ����ڲ��ʡ������ʽ��Ϊ�������
*/
    if( strncmp( sInAcNo+19, "99", 2 )==0 ) {
      strcpy( sInMode, "8" );
    }      
/*
**  �����ʻ����ʾ����������׷���
    sprintf( sSmr, "���㡾%s��������Լ�̻���%s���ʽ�", sCtrPostDate, sMerId ); 
*/
/*
**  ��SeqNo����Ϊ"ZZZZZZ"Ŀ���ǵ����㷽ʽ��Ϊ��������ʱ�����ڱ�־ԭ������ϸ�����ʻ��ܼ�¼�Ķ�Ӧ��ϵ
*/
    if( strcmp( sInMode, "2" )!=0 ) strcpy( sSeqNo, "ZZZZZZ" );
/*
**  �������ʽ��ж����ʷ�ʽ
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
      bpAddResult(TrNode, "PCL999", "�ж����ʷ�ʽ����" );
      bpErrorLog(trdata, "PCLDtlToAcc:�ж����ʷ�ʽ����%d��", SQLCODE);
      return( -1 );
    }
    if( ( strcmp( sInMode, "2" )==0 ) || ( strcmp( sRepFlg, "Y" )==0 ) ) { /*  �����׵������ʻ��һ��ҵ��  */
      if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
        EXEC SQL CLOSE c_txndtl3;
        bpAddResult(TrNode, "PCL999", "ȡǰ����ˮ�ų���" );
        bpErrorLog(trdata, "PCLDtlToAcc:ȡǰ����ˮ�ų���" );
        return( -1 );
      }
/*
**  ���ݷ��кźͽ���������ȡ���ӹ�Ա��
*/
      if( sqnGetDumTlr( sOpnBr, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
        EXEC SQL CLOSE c_txndtl3;
        bpAddResult(TrNode, "PCL999", "ȡ���ӹ�Ա�ų���" );
        bpErrorLog( trdata, "PCLDtlToAcc:ȡ���ӹ�Ա�ų�������OpnBr��%s��TxnCnl��%s��CnlSub��%s��", sOpnBr, sTxnCnl, sCnlSub );
        return( -1 );
      }
/*
**  ����ʽת��
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
        bpAddResult(TrNode, "PCL999", "INSERT��PclAccJnl���쳣" );
        bpErrorLog( trdata, "PCLDtlToAcc:INSERT��PclAccJnl���쳣��%d��-��������-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sLogNo,sDskNo,sActDat,sTTxnCd,sHTxnCd,sHLogNo,sHTxnSt,sHRspCd,sIsTxn,sUpdFlg,sUpdFld,sTxnObj,sTlrId,sTckNo,sCtrPostDate,sMerId,sSeqNo,sClrAct,sInAcNo,sSndFlg,sInMode,sTmpTranAmt,sTmpClearAmt,sTmpMerFee,sDeptNo,sOpnBr,sCdFlag );
        return( -1 );
      }
      iCount++;
    } else {                        /*  �������ܶ���ۼ�����  */
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
        bpAddResult(TrNode, "PCL999", "UPDATE��PclAccJnl���쳣" );
        bpErrorLog( trdata, "PCLDtlToAcc:UPDATE����[%d][%s][%s][%s][%s][%s][%s][%s]", SQLCODE, sInMode, sCtrPostDate, sMerId, sOpnBr, sTranAmt, sClearAmt, sMerFee );
        return( -1 );
      }
    }
  }
  sprintf( sOrnCnt,"%8d", iCount );
  EXEC SQL CLOSE c_txndtl3;
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
  bpAddResult(TrNode, "000000", "���ݱ�PCLDtlToAcc���������" );
  bpTraceLog( trdata, "End PCLDtlToAcc.\n" );
  return (0);
}
/******************************************************************************
  Function        : PCLDtlToRpt
  Description     : ����POS������ϸ���ɱ�������
  Calls           : �����������õĺ����嵥
  Called By       : ���ñ������ĺ����嵥
  Table Accessed  : PclTxnDtl PclCusAgt
  Table Updated   : PclTxnDtl
  Input           : ETF *TrNode  ������
                    ST_TranData* trdata  �����ṹ
                    char* args  ����
                    DBConHandle* DBHandle  ���ݿ���
  Output          : �����������˵��
  Return          : 0--�ɹ� С��0--ʧ��
  Others          : ����˵��
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin PCLDtlToRpt.\n" );
/*
**  ����������
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "PCL999", "����������" );
    bpErrorLog( trdata, "PCLDtlToRpt: ����������!" );
    return( -1 );
  }
/*
**  �����ʷ��¼
*/
  EXEC SQL delete from PclTmpRpt;
  if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND ) ) {
    bpAddResult( TrNode, "PCL999", "�����PCLTMPRPT���쳣" );
    bpErrorLog(trdata, "PCLDtlToRpt:�����PCLTMPRPT���쳣[%d]", SQLCODE);
    return( -1 );
  }
/*
**  ��ڲ�������
*/
  ClearStr( sActDat );
  ClearStr( sTmpDt );
  ClearStr( sOMerId );
  ClearStr( sRepFlg );
  if ( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾ActDat������" );
    bpErrorLog( trdata, "PCLDtlToRpt:��ȡ�ڵ㡾ActDat������!\n" );
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
    bpAddResult(TrNode, "PCL999", "��ѯ��PclTxnDtl���쳣�����α��" );
    bpErrorLog(trdata, "PCLDtlToRpt:��ѯ��PclTxnDtl���쳣�����α��[%d]", SQLCODE);
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
      bpAddResult(TrNode, "PCL999", "��ѯ��PclTxnDtl���쳣��FETCH����" );
      bpErrorLog(trdata, "PCLDtlToRpt:��ѯ��PclTxnDtl���쳣��FETCH����%d��", SQLCODE);
      return( -1 );
    }
    if( strcmp( sMerId, sOMerId )==0 ) {
      strcpy( sRepFlg, "0" );
    } else {
      strcpy( sRepFlg, "1" );
      strcpy( sOMerId, sMerId );
    }
/*
**  ѡ��ͬ��������������ݿ⴦��
*/
    if( ( strcmp( sInMode, "2" )==0 ) || ( strcmp( sRepFlg, "1" )==0 ) ) { /*  �����׵������ʻ��һ��ҵ��  */
      EXEC SQL INSERT INTO PCLTMPRPT( MerId, CtrPostDate, TlrId, TckNo, InAcNo, TranAmt, ClearAmt, BankFee, MerFee, InMode, OpnBr, MerAccFromTbl, MerName )
                  VALUES( :sMerId, :sCtrPostDate, :sTlrId, :sTckNo, :sInAcNo, cast( bigint(:sTranAmt) as char(15) ), cast( bigint(:sClearAmt) as char(15) ), cast( bigint(:sBankFee) as char(15) ), cast( bigint(:sMerFee) as char(15) ), :sInMode, :sOpnBr, :sMerAccFromTbl, :sMerName );
      if( SQLCODE != SQL_SUCCESS ) {
        EXEC SQL CLOSE c_txndtl2;
        bpAddResult(TrNode, "PCL999", "�����PCLTMPRPT���쳣" );
        bpErrorLog( trdata, "PCLDtlToRpt:�����PCLTMPRPT���쳣����%d��-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sMerId,sCtrPostDate,sTlrId,sTckNo,sInAcNo,sTranAmt,sClearAmt,sBankFee,sMerFee,sInMode,sOpnBr,sMerAccFromTbl,sMerName);
        return( -1 );
      }
    } else {                                        /*  �������ܶ�����  */
      EXEC SQL Update PclTmpRpt
                  set TranAmt = cast( ( bigint( TranAmt ) + bigint( :sTranAmt ) ) as char(15) ),
                      ClearAmt = cast( ( bigint( ClearAmt ) + bigint( :sClearAmt ) ) as char(15) ),
                      BankFee = cast( ( bigint( BankFee ) + bigint( :sBankFee ) ) as char(15) ),
                      MerFee = cast( ( bigint( MerFee ) + bigint( :sMerFee ) ) as char(15) )
                where Merid = :sMerId
                  and CtrPostDate = :sCtrPostDate;
      if( SQLCODE != SQL_SUCCESS ) {
        EXEC SQL CLOSE c_txndtl2;
        bpAddResult(TrNode, "PCL999", "���±�PCLTMPRPT���쳣" );
        bpErrorLog( trdata, "PCLDtlToRpt:Update����[%d][%s][%s]", SQLCODE, sCtrPostDate, sMerId );
        return( -1 );
      }
    }
  }
  EXEC SQL CLOSE c_txndtl2;
  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End PCLDtlToRpt.\n" );
  return (0);
}
/******************************************************************************
  Function        : PCLGetTrmInf
  Description     : ����POS�̻��Ż�ȡ��Ӧ���к�
  Calls           : �����������õĺ����嵥
  Called By       : ���ñ������ĺ����嵥
  Table Accessed  : PclTrmAgt
  Table Updated   : 
  Input           : ETF *TrNode  ������
                    ST_TranData* trdata  �����ṹ
                    char* args  ����
                    DBConHandle* DBHandle  ���ݿ���
  Output          : �����������˵��
  Return          : 0--�ɹ� С��0--ʧ��
  Others          : ����˵��
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin PCLGetTrmInf.\n" );
/*
**  ��ʼ����������
*/
  ClearStr( sPosTyp );
  ClearStr( sMerId  );
  ClearStr( sTermId );
  ClearStr( sOpnBr  );
  ClearStr( sInAcNo );
  ClearStr( sUniNo  );
  ClearStr( sMobTel );
/*
**  ��ȡ�̻��ź��ն˺�
*/
  if ( etfGetChildValue(TrNode, "PosTyp", sPosTyp, PosTypLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾PosTyp������" );
    bpErrorLog( trdata, "PCLGetTrmInf:��ȡ�ڵ㡾PosTyp������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "MerId", sMerId, MerIdLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾MerId������" );
    bpErrorLog( trdata, "PCLGetTrmInf:��ȡ�ڵ㡾MerId������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TermId", sTermId, TermIdLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾TermId������" );
    bpErrorLog( trdata, "PCLGetTrmInf:��ȡ�ڵ㡾TermId������!\n" );
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
    bpAddResult( TrNode, "PB0249", "PCLGetTrmInf: û�ж�Ӧ�̻�������" );
    bpErrorLog( trdata, "PCLGetTrmInf: û�ж�Ӧ�̻��š�%s����%s����%s��������!",sPosTyp,sMerId, sTermId );
    return( -1 );
  }
  etfAddOrRepNode( TrNode, "BrNo",   sOpnBr,  BrNoLen   );
  etfAddOrRepNode( TrNode, "ActNo",  sInAcNo, ActNoLen  );
  etfAddOrRepNode( TrNode, "UniNo",  sUniNo,  UniNoLen  );
  etfAddOrRepNode( TrNode, "MobTel", sMobTel, MobTelLen );
  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End PCLGetTrmInf.\n" );
  return (0);
}
/******************************************************************************
  Function          : PCLDGetFee
  Description       : ֱ��POSת����ط���
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : PclTrmAgt
  Table Updated     : ��
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin PCLDGetFee.\n" );
/*
**  ��������������
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "PCLDGetFee: ����������" );
    bpErrorLog( trdata, "PCLDGetFee: ����������!" );
    return( -1 );
  }
/*
**  ���λ�ȡ�˺ţ����׽��
*/
  ClearStr( sMerId  );
  ClearStr( sTermId );
  ClearStr( sTxnAmt );
  ClearStr( sFeeAmt );
  strcpy( sMerId,  Step_Arg1 );
  strcpy( sTermId, Step_Arg2 );
  strcpy( sTxnAmt, Step_Arg3 );
/*
**  ��������Ҫ�ؼ������
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
    bpAddResult( TrNode, "PB2049", "PCLDGetFee: û�ж�Ӧ�̻������ϱ�" );
    bpErrorLog( trdata, "PCLDGetFee: û�ж�Ӧ�̻���%s����%s�������ϱ�!", sMerId, sTermId );
    return( -1 );
  }
  etfAddOrRepNode( TrNode, "FEEAMT", sFeeAmt, TxnAmtLen );
  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End PCLDGetFee.\n" );
  return (0);
}
/******************************************************************************
  Function          : PCLGetFee
  Description       : ֱ��POSת����ط���
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : PclFeeRat
  Table Updated     : ��
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin PCLGetFee.\n" );
/*
**  ��������������
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "PCLGetFee: ����������" );
    bpErrorLog( trdata, "PCLGetFee: ����������!" );
    return( -1 );
  }
/*
**  ���λ�ȡ�˺ţ����׽��
*/
  ClearStr( sBrNo   );
  ClearStr( sSysFlg );
  ClearStr( sTxnAmt );
  ClearStr( sFeeAmt );
  strcpy( sBrNo  , Step_Arg1 );
  strcpy( sSysFlg, Step_Arg2 );
  strcpy( sTxnAmt, Step_Arg3 );
/*
**  ��������Ҫ�ؼ������
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
    bpAddResult( TrNode, "PB2049", "PCLGetFee: û�ж�Ӧ�̻������ϱ�" );
    bpErrorLog( trdata, "PCLGetFee: û�ж�Ӧ��%s����%s�������ϱ�!", sBrNo, sSysFlg );
    return( -1 );
  }
  etfAddOrRepNode( TrNode, "FEEAMT", sFeeAmt, TxnAmtLen );
  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End PCLGetFee.\n" );
  return (0);
}
/******************************************************************************
  Function        : PCLDFilToDb
  Description     : POS ������ϸ�ļ����
  Calls           : �����������õĺ����嵥
  Called By       : ���ñ������ĺ����嵥 
  Table Accessed  : PclDTxnDtl PclTrmAgt
  Table Updated   : PclDTxnDtl 
  Input           : ETF *TrNode  ������
                    ST_TranData* trdata  �����ṹ
                    char* args  ����
                    DBConHandle* DBHandle  ���ݿ���
  Output          : �����������˵��
  Return          : 0--�ɹ� С��0--ʧ��
  Others          : ����˵��
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin PCLDFilToDb.\n" );
/*
**  ����������
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "����������" );
    bpErrorLog( trdata, "PCLDFilToDb: ����������!" );
    return( -1 );
  }
/*
**  ���������ļ�
*/
  ClearStr( sClrDt  );
  ClearStr( sBrNo   );
  ClearStr( sPosTyp );
  ClearStr( fname );
  strcpy( sClrDt, Step_Arg1 );
    if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾BrNo������" );
    bpErrorLog( trdata, "PCLDFilToDb:��ȡ�ڵ㡾BrNo������!\n" );
    return( -1 );
  }
  strcpy( sPosTyp, Step_Arg3 );
  sprintf( fname, "%s/%s", getenv("WORKDIR"), Step_Arg2 );
  fp =fopen( fname,"r" );
  if( fp == NULL ) {
    fclose( fp );
    bpAddResult( TrNode, "PCL999", "��POS��ϸ�ļ���" );
    bpErrorLog( trdata, "PCLDFilToDb:��POS��ϸ�ļ���%s��ʧ��!\n", fname );
    return( -1 );
  }
/*
**  ����������ϸ�ļ�
*/
  ClearStr( sBgnFlg );
  ClearStr( sEndFlg );
  strcpy( sBgnFlg, "0" );
  strcpy( sEndFlg, "0" );
  while( !feof( fp ) ) {
  i++;
/*
**  �ļ����ݱ�����ʼ��
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
      fscanf( fp, "%[^,]", sRefNo );   /*ϵͳ�ο���*/
    } else {
      fscanf( fp, "\n%[^,]", sRefNo ); /*ϵͳ�ο���*/
    }
    fscanf( fp, ",%[^,]", sCtrPostDate );   /*������*/
    fscanf( fp, ",%[^,]", sCtrDt       );   /*���׷�����*/
    fscanf( fp, ",%[^,]", sCtrTime     );   /*����ʱ��*/
    fscanf( fp, ",%[^,]", sTranAcc     );   /*ת�����ʺ�*/
    fscanf( fp, ",%[^,]", sDMti        );   /*��Ϣ��*/
    fscanf( fp, ",%[^,]", sProcCode    );   /*������*/
    fscanf( fp, ",%[^,]", sCdFlag      );   /*�����־*/
    fscanf( fp, ",%[^,]", sTranAmt     );   /*���׽��*/
    ClearStr( sTmpAmt );
    fscanf( fp, ",%[^,]", sTmpAmt      );   /*�����ѽ��*/
    sprintf( sFeeAmt, "%015d", atoi(sTmpAmt) );
    fscanf( fp, ",%[^,]", sOrigRefNo   );   /*ԭϵͳ�ο���*/
    fscanf( fp, ",%[^,]", sMerId       );   /*�̻���*/
    fscanf( fp, ",%[^,]", sTermId      );   /*�ն˻���*/
    fscanf( fp, ",%[^,]", sCtrTrn      );   /*POS������ˮ��*/
    fscanf( fp, ",%[^,]", sRepCode     );   /*������Ӧ��*/
    fscanf( fp, ",%[^,]", sBankId      );   /*���д���*/
    fscanf( fp, ",%[^\n]", sTBusTp     );   /*ҵ�����*/
    if( strcmp( sRefNo, "000000000000" ) == 0 ) {
      strcpy( sBgnFlg,"1" );
      continue;
    }
    if( strcmp( sRefNo, "999999999999" ) == 0 ) {
      strcpy( sEndFlg,"1" );
      break;
    }
/*
**  �������ݰ�Ҫ���ʽת��
*/
    sprintf( sTxnAmt, "%015d", atoi(sTranAmt)-abs(atoi(sFeeAmt)) );
/*
**  ״̬λ����ֵ
*/
    strcpy( sTxnSts, "0" );
/*
**  �ж����������Ƿ�δPOS������
*/
    if( memcmp( sClrDt, sCtrPostDate, ActDatLen ) != 0 ) {
      bpErrorLog( trdata, "PCLDFilToDb:�������ڷ�POS�����ա�%s����%s����%s��", sClrDt, sCtrPostDate, sRefNo );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "�������ݷ�ֱ��POS����������" );
      goto DB_INSERT;
    }
/*
**  �������ף�������
*/
    if( strcmp( sCdFlag, "D" )==0 ) strcpy( sTxnSts, "A" );
/*
**  �����̻��š��ն˺Ż�ȡ�����ʺš����������ѣ������Ϸ���
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
      bpErrorLog( trdata, "PCLDFilToDb:���̻��ն˺�δ�Ǽǻ��쳣��PosTyp��%s��MerId��%s��TermId��%s��", sPosTyp,sMerId,sTermId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "���̻��ն˺�δ�Ǽǻ��쳣" );
      goto DB_INSERT;
    }
    sprintf( sBnkFee, "%015d", atoi(sFeeAmt)-atoi(sThdFee) );
    if ( atoi(sFeeAmt)<atoi(sThdFee) ) {
      bpErrorLog( trdata, "PCLDFilToDb:���̻��������ѵ�������������PosTyp��%s��MerId��%s��TermId��%s��", sPosTyp,sMerId,sTermId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "���̻��������ѵ�������������" );
      goto DB_INSERT;
    }
/*
**  �����̻��Ż�ȡ�����ڲ���
*/
    EXEC SQL select InAcNo
               into :sClrAct
               from PclCusAgt
              where PosTyp =:sPosTyp
                and BusiNo =:sMerId
                and Sts ='0';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLDFilToDb:���̻���δ�Ǽǻ��쳣��%s��", sMerId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "���̻���δ�Ǽǻ��쳣" );
      goto DB_INSERT;
    }
/*
**  �����̻�
*/
/*
**  �������
*/
DB_INSERT:
    EXEC SQL insert into PclDTxnDtl( TxnSts,RefNo,CtrPostDate,CtrDt,CtrTime,TranAcc,DMti,ProcCode,CdFlag,TranAmt,TxnAmt,FeeAmt,BnkFee,ThdFee,OrigRefNo,MerId,TermId,CtrTrn,RepCode,BankId,TBusTp,ClrAct,ActNo,ActNm,DeptNo,OpnBr,ErrMsg )
                values( :sTxnSts,:sRefNo,:sCtrPostDate,:sCtrDt,:sCtrTime,:sTranAcc,:sDMti,:sProcCode,:sCdFlag,:sTranAmt,:sTxnAmt,:sFeeAmt,:sBnkFee,:sThdFee,:sOrigRefNo,:sMerId,:sTermId,:sCtrTrn,:sRepCode,:sBankId,:sTBusTp,:sClrAct,:sActNo,:sActNm,:sDeptNo,:sOpnBr,:sErrMsg );
    if( SQLCODE != SQL_SUCCESS ) {
      fclose( fp );
      bpAddResult( TrNode, "PCL999", "PCLDFilToDb:INSERT��PclDTxnDtl������" );
      bpErrorLog(trdata, "PCLDFilToDb:INSERT����[%d]-��������-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sTxnSts,sRefNo,sCtrPostDate,sCtrDt,sCtrTime,sTranAcc,sDMti,sProcCode,sCdFlag,sTranAmt,sTxnAmt,sFeeAmt,sOrigRefNo,sMerId,sTermId,sCtrTrn,sRepCode,sBankId,sTBusTp,sActNo,sActNm,sDeptNo,sOpnBr,sErrMsg );
      return( -1 );
    }
  }
/*
**  �رմ����ļ�
*/
  fclose( fp );
/*
**  ���������ף������ݿ��¼��Ϊ"A"��
**  ���²������ڱ�֤�������׵�ORIGCTRTRN��ԭ���׵�CTRTRN��ͬ�Ļ�����ʵ�ֵģ����ܻ�����
*/
  EXEC SQL DECLARE c_dtxndtl1 CURSOR FOR
      select TranAmt, OrigRefNo, MerId, TermId
        from PclDTxnDtl
       where CtrPostDate =:sClrDt
          and TxnSts in ( '0','A' )
         and CdFlag ='D';
  EXEC SQL OPEN c_dtxndtl1;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult(TrNode, _DB_QUERY_ERR, "��ѯ��PclTxnDtl���쳣" );
    bpErrorLog(trdata, "PCLDFilToDb:��ѯ��PclTxnDtl��OPEN�α��[%d]", SQLCODE);
    return( -1 );
  }
  for( ; ; ) {
    ClearStr( sTranAmt );
    ClearStr( sOrigRefNo );
    ClearStr( sMerId );
    EXEC SQL FETCH c_dtxndtl1 INTO :sTranAmt, :sOrigRefNo, :sMerId, :sTermId;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLDFilToDb:FETCH����[%d]", SQLCODE );
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
      bpErrorLog(trdata, "PCLDFilToDb:�޸ı�PclDTxnDtl���쳣[%d]��%s����%s����%s��", SQLCODE, sClrDt, sMerId, sRefNo);
      iRet = -1;
      break;
    }
  }
  EXEC SQL CLOSE c_dtxndtl1;
  if( ( iRet != 0 ) || ( strcmp(sBgnFlg,"1")!=0 ) || ( strcmp( sEndFlg,"1" )!=0 ) ) {
    bpAddResult(TrNode, "PCL999", "�������ʧ�ܻ������ļ�������" );
    bpErrorLog(trdata, "PCLDFilToDb:�ļ���%s�����ʧ�ܻ�����",fname );
    return( -1 );
  }
  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End PCLDFilToDb.\n" );
  return iRet;
}
/******************************************************************************
  Function        : PCLIFilToDb
  Description     : ����POS������ϸ�ļ����
  Calls           : �����������õĺ����嵥
  Called By       : ���ñ������ĺ����嵥 
  Table Accessed  : PclITxnDtl PclTrmAgt
  Table Updated   : PclITxnDtl 
  Input           : ETF *TrNode  ������
                    ST_TranData* trdata  �����ṹ
                    char* args  ����
                    DBConHandle* DBHandle  ���ݿ���
  Output          : �����������˵��
  Return          : 0--�ɹ� С��0--ʧ��
  Others          : ����˵��
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin PCLIFilToDb.\n" );
/*
**  ����������
*/
  if( Step_Args_Num != 3 ) {
    bpAddResult( TrNode, "PCL999", "����������" );
    bpErrorLog( trdata, "PCLIFilToDb: ����������!" );
    return( -1 );
  }
/*
**  ���������ļ�
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
    bpAddResult( TrNode, "PCL999", "��POS��ϸ�ļ���" );
    bpErrorLog( trdata, "PCLIFilToDb:��POS��ϸ�ļ���%s��ʧ��!\n", fname );
    return( -1 );
  }

  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾BrNo������" );
    bpErrorLog( trdata, "PCLIFilToDb:��ȡ�ڵ㡾BrNo������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾BrNo������" );
    bpErrorLog( trdata, "PCLIFilToDb:��ȡ�ڵ㡾BrNo������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TotNum", sTotNum, TotNumLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾TotNum������" );
    bpErrorLog( trdata, "PCLIFilToDb:��ȡ�ڵ㡾TotNum������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TotAmt", sTotAmt, TotAmtLen+1) <= 0 ) {
    bpAddResult( TrNode, "PCL999", "��ȡ�ڵ㡾TotAmt������" );
    bpErrorLog( trdata, "PCLIFilToDb:��ȡ�ڵ㡾TotAmt������!\n" );
    return( -1 );
  }
/*
**  ����������ϸ�ļ�
*/
  iCount=0;
  strcpy( sFlag, "0" );
/*
** һ���Ի�ȡ��ˮ�ţ����Ⲣ������
*/
  ClearStr( sLogNo );
  ClearStr( sDate  );
  ClearStr( sSerial );
  if( sqnGetLogNo( sLogNo, atol(sTotNum) ) < 0 ) {
     bpAddResult(TrNode, "PCL999", "ȡǰ����ˮ�ų���" );
     bpErrorLog(trdata, "PCLIFilToDb:ȡǰ����ˮ�ų���" );
     return( -1 );
  }
  memcpy( sDate, sLogNo, DateLen );
  memcpy( sSerial, sLogNo+DateLen, SerialLen );
/*
** �ļ��������
*/
  while( !feof( fp ) ) {
    if( atol(sTotNum)==iCount ) {
      strcpy( sFlag,"1" );
      break;
    } else {
      iCount++;
    }
/*
**  �ļ����ݱ�����ʼ��
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
      fscanf( fp, "%[^,]", sMerId );   /*�̻���*/
    } else {
      fscanf( fp, "\n%[^,]", sMerId ); /*�̻���*/
    }
    fscanf( fp, ",%[^,]", sTermId  );   /*�ն˻���*/
    ClearStr( sBuf );
    fscanf( fp, ",%[^,]", sBuf     );   /*���׽��*/
    sprintf( sTranAmt, "%012d", atoi(sBuf) );
    fscanf( fp, ",%[^\n]", sBuf    );   /*�����ѽ��*/
    sprintf( sFeeAmt, "%012d", atoi(sBuf) );
/*
**  �������ݰ�Ҫ���ʽת��
*/
    sprintf( sTxnAmt, "%015d", atoi(sTranAmt)-atoi(sFeeAmt) );
/*
**  ״̬λ����ֵ
*/
    strcpy( sTxnSts, "0" );
/*
**  �����̻��š��ն˺Ż�ȡ�����ʺš����������ѣ������Ϸ���
*/
    EXEC SQL select TrmTyp, InAcNo, InAcNm, DeptNo, OpnBr
               into :sTrmTyp, :sActNo, :sActNm, :sDeptNo, :sOpnBr
               from PclTrmAgt
              where PosTyp =:sPosTyp
                and MerId  =:sMerId
                and TermId =:sTermId
                and Sts ='0';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLIFilToDb:���̻��ն˺�δ�Ǽǻ��쳣��PosTyp��%s��MerId��%s��TermId��%s��", sPosTyp,sMerId,sTermId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "���̻��ն˺�δ�Ǽǻ��쳣" );
      goto DB_INSERT;
    }
/*
**  �����̻��Ż�ȡ�����ڲ���
*/
    EXEC SQL select InAcNo
               into :sClrAct
               from PclCusAgt
              where PosTyp =:sPosTyp
                and BusiNo =:sMerId
                and Sts ='0';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "PCLIFilToDb:���̻���δ�Ǽǻ��쳣PosTyp��%s��MerId��%s��", sPosTyp,sMerId );
      iRet = -1;
      strcpy( sTxnSts, "E" );
      strcpy( sOpnBr, sBrNo );
      strcpy( sErrMsg, "���̻���δ�Ǽǻ��쳣" );
      goto DB_INSERT;
    }
/*
**  �������
*/
DB_INSERT:
    EXEC SQL insert into PclITxnDtl( TxnSts,CtrPostDate,TranAmt,TxnAmt,FeeAmt,PosTyp,MerId,TrmTyp,TermId,LogNo,ActDat,ClrAct,ActNo,ActNm,DeptNo,OpnBr,ErrMsg )
                             values( :sTxnSts,:sCtrPostDate,:sTranAmt,:sTxnAmt,:sFeeAmt,:sPosTyp,:sMerId,:sTrmTyp,:sTermId,:sLogNo,:sActDat,:sClrAct,:sActNo,:sActNm,:sDeptNo,:sOpnBr,:sErrMsg );
    if( SQLCODE != SQL_SUCCESS ) {
      fclose( fp );
      bpAddResult( TrNode, "PCL999", "PCLIFilToDb:INSERT��PclITxnDtl������" );
      bpErrorLog(trdata, "PCLIFilToDb:INSERT����[%d]-����TxnSts��%s��CtrPostDate��%s��TranAmt��%s��TxnAmt��%s��FeeAmt��%s��PosTyp��%s��MerId��%s��TrmTyp��%s��TermId��%s��LogNo��%s��ActDat��%s��ClrAct��%s��ActNo��%s��ActNm��%s��DeptNo��%s��OpnBr��%s��ErrMsg��%s��",sTxnSts,sCtrPostDate,sTranAmt,sTxnAmt,sFeeAmt,sPosTyp,sMerId,sTrmTyp,sTermId,sLogNo,sActDat,sClrAct,sActNo,sActNm,sDeptNo,sOpnBr,sErrMsg );
      return( -1 );
    }
    ClearStr( sLogNo );
    sprintf( sSerial,"%08ld", atol(sSerial)+1 );
    sprintf( sLogNo,"%s%s", sDate, sSerial );
  }
/*
**  �رմ����ļ�
*/
  fclose( fp );
  if( ( iRet != 0 ) || ( strcmp(sFlag,"1")!=0 ) || ( iCount!=atol(sTotNum) ) ) {
    bpAddResult(TrNode, "PCL999", "�������ʧ�ܻ������ļ�������" );
    bpErrorLog(trdata, "PCLIFilToDb:�ļ���%s�����ʧ�ܻ�����",fname );
    return( -1 );
  }
  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End PCLIFilToDb.\n" );
  return iRet;
}
