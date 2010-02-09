/******************************************************************************       
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.            

  File name    : cbs.cp
  Author       : Jamez
  Version      : 1.0  
  Date         : 2005.11.15  
  Description  : ʡ����֧��ƽ̨���Ի�ԭ�Ӻ���
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
  Description       : ����ҵ��������
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin CbsGetFee.\n" );
/*
**  ��������������
*/
  if( Step_Args_Num != 6 ) {
    bpAddResult( TrNode, "CBS999", "����������" );
    bpErrorLog( trdata, "CbsGetFee: ����������!" );
    return( -1 );
  }
/*
**  ���λ�ȡ�ʽ���;���롢����ر�־�����кš����֡����׽��
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
**  ��������Ҫ�ؼ������
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
    bpAddResult( TrNode, "CBS999", "û�ж�Ӧ�ķ��ʱ�" );
    bpErrorLog( trdata, "CbsGetFee:û�ж�Ӧ�ķ��ʱ�%s����%s����%s����%s����%s����%s��,SQLCODE��%d��", sTxnKnd, sUsgCod, sLclFlg, sBrNo, sCcyCod, sTxnAmt, SQLCODE );
    return( -1 );
  }
  etfAddOrRepNode( TrNode, "FEEAMT", sFeeAmt, FeeAmtLen );
  etfAddOrRepNode( TrNode, "PSTAMT", sPstAmt, PstAmtLen );

  bpAddResult( TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End CbsGetFee.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsGetAccFlg
  Description       : �жϽ������ʺŵ�����(���ˡ���ҵ)
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : ��
  Table Updated      : ��
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin CbsGetAccFlg.\n" );
/*
**  ��������������
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "CBS999", "����������" );
    bpErrorLog( trdata, "CbsGetFee: ����������!" );
    return( -1 );
  }
/*
**  ��ȡ�������ʺ�
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
    bpAddResult( TrNode, "CBS999", "�ǽ����ʺ�" );
    bpErrorLog(trdata, "CbsGetAccFlg���ʺš�%s���ǽ����ʺ�", sRcvAct);
    bpTraceLog( trdata, "End CbsGetAccFlg.\n" );
    return -1;
  }
/*
**  �ж��Ƿ�Ϊ�ϴ��ۣ���δ����Ͻ���У�
*/
  if( memcmp(sRcvAct,"071",3)==0 ) {
    EXEC SQL select ActNo
               into :sBokAct
               from SavOldAct
              where OldAct =:sRcvAct;
    if( SQLCODE == SQL_SUCCESS ) {
      strcpy( sLAccFlg, "1" );
      strcpy( sLActFg, "2" );
      bpErrorLog(trdata, "CbsGetAccFlg��ת���ʺš�%s��������%s��", sRcvAct, sBokAct);
      etfAddOrRepNode( TrNode, "LAccFlg", sLAccFlg, AccFlgLen );
      etfAddOrRepNode( TrNode, "LActFg", sLActFg, ActFlgLen );
      etfAddOrRepNode( TrNode, "BokAct", sBokAct, RcvActLen );
      return 0;
    }
  }
/*
**  �ж��Ƿ�Ϊ��ҵ��
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
        case 209:   /* �����ý��ʺ� */
        case 229:   /* �����ý��ʺ� */
          strcpy( sLAccFlg, "2" );
          strcpy( sLActFg, "4" );
          break;
        case 998:   /* һ��ͨ */
          strcpy( sLAccFlg, "1" );
          strcpy( sLActFg, "1" );
          break;
        case 202:   /* ���� */
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

  bpAddResult( TrNode, "000000", "���׳ɹ�" );
  bpErrorLog(trdata, "CbsGetAccFlg���ʺš�%s���ʻ����ʡ�%s����%s����Ӧ���ʺš�%s��", sRcvAct,sLAccFlg,sLActFg,sBokAct);
  bpTraceLog( trdata, "End CbsGetAccFlg.\n" );
  return(0);
}
/******************************************************************************
  Function          : CbsUpdBal
  Description       : �жϲ��޸ķ���ͷ��
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥 
  Table Accessed    : ��
  Table Updated      : ��
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��  1--ͷ�粻��
  Others            : ����˵��             
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin CbsUpdBal.\n" );
/*
**  ��������������
*/
  if( Step_Args_Num != 4 ) {
    bpAddResult( TrNode, "CBS999", "����������" );
    bpErrorLog( trdata, "CbsUpdBal: ����������!" );
    return( -1 );
  }
/*
**  ��ȡ�������ʺţ���δ����Ͻ���У�
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
**  ͨ������ʵ�ֲ���
*/
  EXEC SQL update CbsBnkInf
              set CurAmt=CurAmt
            where BrNo = :sBrNo;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult( TrNode, "CBS999", "��CbsBnkInf��������" );
    bpErrorLog( trdata, "CbsUpdBal: ��CbsBnkInf��������!" );
    return -1;
  }
  ClearStr( sCurAmt );
  EXEC SQL select CurAmt
             into :sCurAmt
             from CbsBnkInf
            where BrNo = :sBrNo;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult( TrNode, "CBS999", "��ѯ��CbsBnkInf����ǰ����" );
    bpErrorLog( trdata, "CbsUpdBal: ��ѯ��CbsBnkInf����ǰ����!" );
    return -1;
  }
  if( strcmp( sTxnMod, "0" )==0 ) {  /* ͷ���ѯ */
    if( atoi(sCurAmt)<atoi(sTxnAmt) ) {
      bpAddResult( TrNode, "000000", "ͷ�粻��" );
      bpErrorLog( trdata, "CbsUpdBal: ͷ�粻��!" );
      return 1;
    } else {
      bpAddResult( TrNode, "000000", "ͷ�����" );
      bpErrorLog( trdata, "CbsUpdBal: ͷ�����!" );
      return 0;
    }
  } else { /* ͷ���� */
    if( strcmp( sUpdDir, "0" )==0 ) {  /* ͷ������ */
      EXEC SQL update CbsBnkInf
                  set CurAmt = substr( right( ( '000000000000000'||rtrim(char( int( CurAmt ) + int( :sTxnAmt ) ) ) ),15 ), 1, 15 )
                where BrNo = :sBrNo;
    } else { /* ͷ����� */
      if( atoi(sCurAmt)<atoi(sTxnAmt) ) {
        ClearStr( sTxnAmt );
        strcpy( sTxnAmt, sCurAmt );
      }
      EXEC SQL update CbsBnkInf
                  set CurAmt = substr( right( ( '000000000000000'||rtrim(char( int( CurAmt ) - int( :sTxnAmt ) ) ) ),15 ), 1, 15 )
                where BrNo = :sBrNo;
    }
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult( TrNode, "CBS999", "���±�CbsBnkInf����ǰ����" );
      bpErrorLog( trdata, "CbsUpdBal: ���±�CbsBnkInf����ǰ����!" );
      bpTraceLog( trdata, "End CbsUpdBal.\n" );
      return -1;
    }
  }
  bpAddResult( TrNode, "000000", "ͷ���ѯ�����£��ɹ�" );
  bpErrorLog( trdata, "CbsUpdBal: ͷ���ѯ�����£��ɹ�!" );
  bpTraceLog( trdata, "End CbsUpdBal.\n" );
  return(0);
}
/******************************************************************************
  Function          : CbsGetNodInfo
  Description       : ����֧���кŵõ����кţ�������������ţ� Ӫҵ�������
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
/*  ���ø�����Ϣ */
  bpTraceLog( trdata, "Begin CbsGetNodInfo.\n" );
/*��������������*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "����������" );
    bpErrorLog( trdata, "CbsGetNodInfo: ����������!" );
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
    bpAddResult(TrNode, "CBS999", "��ѯ��PubNodInf����" );
    bpErrorLog(trdata, "CbsGetNodInfo:��ѯ��PubNodInf����%d��", SQLCODE);
    return( -1 );
  }
  EXEC SQL SELECT  CtlNod,BusNod,CnlSub
               INTO  :sCtlNod,:sBusNod,:sCnlSub
               FROM  cbsbnkinf
              WHERE  BrNo=:sBrNo;
  if( SQLCODE )  {
    bpAddResult(TrNode, "CBS999", "��ѯ��CbsBnkInf����" );
    bpErrorLog(trdata, "CbsGetNodInfo��ѯ��CbsBnkInf����%d��", SQLCODE);
    return( -1 );
  }
  bpErrorLog(trdata, "��%s����%s����%s����%s��", sBrNo,sCtlNod,sBusNod,sCnlSub);
  sCnlSub[6]='\0';
  etfAddOrRepNode(TrNode,"BrNo", sBrNo, strlen(sBrNo));
  etfAddOrRepNode(TrNode,"CtlNod", sCtlNod, strlen(sCtlNod));
  etfAddOrRepNode(TrNode,"BusNod", sBusNod, strlen(sBusNod));
  etfAddOrRepNode(TrNode,"CnlSub", sCnlSub, strlen(sCnlSub));

  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End CbsGetNodInfo.\n" );
  return(0);
}
/******************************************************************************
  Function          : CbsFLstToDb
  Description       : ������8583�����ļ��б�������ݿⲢ������Ӧ�ļ�
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**���ø�����Ϣ
*/
  ClearStr( sMsgTyp );
  ClearStr( sRspCod );
  ClearStr( sRspMsg );
  ClearStr( sOIFlag );
  strcpy( sOIFlag, "1" );
  bpTraceLog( trdata, "Begin CbsFLstToDb.\n" );
/*��������������*/
  if( Step_Args_Num != 5 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "����������" );
    bpErrorLog( trdata, "CbsFLstToDb: ����������!" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "����������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  �����б��ļ���ȡ�����ļ������������׻�Ӧ�б��ļ��;����Ӧ�ļ�
*/
  ClearStr( sRcvFilLst );
  ClearStr( sSndFilLst );
  sprintf( sRcvFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg1 );
  sprintf( sSndFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg3 );
  sprintf( sDelFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg5 );
/*
**  ��Ӧ�ļ��б�
*/
  slst_fp =fopen( sSndFilLst, "w" );
  if( slst_fp == NULL ) {
    fclose( slst_fp );
    bpAddResult( TrNode, "CBS999", "�򿪷����б��ļ���" );
    bpErrorLog( trdata, "CbsFLstToDb:�򿪷����б��ļ���%s��ʧ��!\n", sSndFilLst );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "�򿪷����б��ļ���%s����", Step_Arg3 );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  ɾ���ļ��б�
*/
  dlst_fp =fopen( sDelFilLst, "w" );
  if( dlst_fp == NULL ) {
    fclose( slst_fp );
    fclose( dlst_fp );
    bpAddResult( TrNode, "CBS999", "��ɾ���б��ļ���" );
    bpErrorLog( trdata, "CbsFLstToDb:��ɾ���б��ļ���%s��ʧ��!\n", sDelFilLst );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ɾ���б��ļ���%s����", Step_Arg3 );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  �����ļ��б�
*/
  rlst_fp =fopen( sRcvFilLst, "r" );
  if( rlst_fp == NULL ) {
    fclose( slst_fp );
    fclose( dlst_fp );
    fclose( rlst_fp );
    bpAddResult( TrNode, "CBS999", "�򿪽����б��ļ���" );
    bpErrorLog( trdata, "CbsFLstToDb:�򿪽����б��ļ���%s��ʧ��!\n", sRcvFilLst );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "�򿪽����б��ļ���%s����", Step_Arg1 );
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
**  �˴�����ɾ���б��ļ��еĻس����з�
*/
    fgets( sTmpFil, FNmLstLen, rlst_fp );
    strncpy( sFilNam, sTmpFil, FNmLstLen-2 );
    if( strlen(sFilNam)==0 ) {
      bpErrorLog( trdata, "CbsFLstToDb:�����ļ��б������!\n" );
      fclose( rfp );
      break;
    }
    bpErrorLog( trdata, "CbsFLstToDb:���ڴ����ļ���%s��!\n", sFilNam );
    ClearStr( sFlag );
    strcpy( sFlag, "N" );
    EXEC SQL select 'Y'
               into :sFlag
               from TABLE(VALUES(1)) AS anony
              where EXISTS ( select 'Y' from CbsBchSum where FilNam = :sFilNam );
/*
**  �˴���������Ϊ�˿����ظ����ɻ�Ӧ�ļ�
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
**  �ж��ļ���������
*/
    rfp =fopen( sSrc8583Fil, "r" );
    if( rfp == NULL ) {
      bpAddResult( TrNode, "CBS999", "�������ļ���" );
      bpErrorLog( trdata, "CbsFLstToDb:�������ļ���%s��ʧ��!\n", sSrc8583Fil );
      fclose( rfp );
      continue;
    }
    iFSize=0;
    iFSize=hfgetsize( rfp );
    if( iFSize != atol( sFSize ) ) {
      bpErrorLog( trdata, "CbsFLstToDb:�����ļ���%s��������!\n", sSrc8583Fil );
      fclose( rfp );
      continue;
    }
    fclose( rfp );
/*
**  �������ļ�8583ת��Ϊ��ͨ�ļ�
*/
    ret=CbsFilChg( "2", sSrc8583Fil, sSrcFil );
    if( ret!=0 ) {
      bpErrorLog( trdata, "CbsFLstToDb:�����ļ���%s��ת���쳣!\n", sSrc8583Fil );
      continue;
    }
/*
** ���������ļ��ĵ�һ�в��Ǽǻ��޸Ļ��ܱ�
*/
    rfp =fopen( sSrcFil, "r" );
    if( rfp == NULL ) {
      bpAddResult( TrNode, "CBS999", "�������ļ���" );
      bpErrorLog( trdata, "CbsFLstToDb:�������ļ���%s��ʧ��!\n", sSrcFil );
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
    fscanf( rfp, "%[^|]",  sClrDat ); /* �������� */
    fscanf( rfp, "|%[^|]", sClrSce ); /* ���㳡�� */
    fscanf( rfp, "|%[^|]", sSSysId ); /* ����ϵͳ�� */
    fscanf( rfp, "|%[^|]", sSndBNo ); /* ���𷽴��� */
    fscanf( rfp, "|%[^|]", sRSysId ); /* ���շ�ϵͳ�� */
    fscanf( rfp, "|%[^|]", sRcvBNo ); /* ���շ����� */
    fscanf( rfp, "|%[^|]", sTraKnd ); /* �������� */
    fscanf( rfp, "|%[^|]", sFilNam ); /* �ļ��� */
    fscanf( rfp, "|%[^|]", sRefFil ); /* �����ļ��� */
    fscanf( rfp, "|%[^|]", sBchSqn ); /* ��������� */
    fscanf( rfp, "|%[^|]", sRefSqn ); /* �ο���������� */
    fscanf( rfp, "|%[^|]", sCusSqn ); /* �ͻ���������� */
    fscanf( rfp, "|%[^|]", sTotNum ); /* �����ܱ��� */
    fscanf( rfp, "|%[^|]", sTotAmt ); /* �����ܽ�� */
    fscanf( rfp, "|%[^|]", sRefNum ); /* �ܾ�֧���ܱ��� */
    fscanf( rfp, "|%[^|]", sRefAmt ); /* �ܾ�֧���ܽ�� */
    fscanf( rfp, "|%[^|]", sRtnCod ); /* ������ */
    fscanf( rfp, "|%[^|\n]",sReServ );/* Ԥ��λ */
    strcpy( sBchSts, "U" );
/*
**  �ж��ļ�������2202��ת���ɷ����룩����2220������ACK��Ӧ��
*/
    switch( atoi(sMsgId) ) {
      case 2220:   /* ���ڽ�����ʵķ���ACK��Ӧ */
        if( ( strcmp( sRtnCod, "000I1000" )==0 ) || ( strcmp( sRtnCod, "000O7008" )==0 ) ) { /*���ĳɹ�����ҵ���Ӧ�ļ�*/
          EXEC SQL update CbsBchSum Set BchSts='D', ClrDat=:sClrDat, ClrSce=:sClrSce, AckFil2=:sFilNam where ClrFil=substr(:sRefFil,1,36) and OIFlag='1';
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:����ACK2220��Ӧ�ļ���%s����%s�����»��ܱ�CbsBchSum��ʧ��!\n", sSrc8583Fil, sRefFil );
          }
          EXEC SQL update CbsBchJnl Set ClrDat=:sClrDat  where filnam=( select FilNam from CbsBchSum where ClrFil=substr(:sRefFil,1,36) and OIFlag='1');
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:����ACK2220��Ӧ�ļ���%s����%s��������ϸ��CbsBchJnl��ʧ��!\n", sSrc8583Fil, sRefFil );
          }
        } else {
          bpErrorLog( trdata, "CbsFLstToDb:����ACK2220��Ӧ�ļ���%s��ʧ�ܣ�ԭ��Ӧ�ļ���%s��!\n", sSrc8583Fil, sRefFil );
        }
        /*ACK��Ӧ�ļ�2220˵��ԭҵ���Ӧ2212�д�ͨ�����������������ǻ�Ӧ���˴������κδ���*/
        fprintf( dlst_fp, "%s\n", sFilNam );
        break;
      case 2202:   /* ת�����ڽ�ǽɷ�����2202���������� */
/*
**  Դ�ļ�2202�������
*/
        if( strcmp( sFlag, "Y" ) != 0 ) {
          EXEC SQL select BrNo, substr(BrNo,1,3)||'800' 
                     into :sBrNo, :sNodNo
                     from pubnodinf
                    where SBkNo=:sRcvBNo fetch first 1 rows only;
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:��ȡ�����С�%s�����кų����ļ���:��%s��!\n", sRcvBNo, sSrc8583Fil );
            bpAddResult( TrNode, _DB_OPER_ERR, "��ȡ�����з��кŴ���" );
            strcpy( sMsgTyp, "E" );
            strcpy( sRspCod, "CBS999" );
            strcpy( sRspMsg, "��ȡ�����з��кŴ���" );
            etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
            etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
            etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
            fclose( rfp );
            continue;
          }
          EXEC SQL insert into CbsBchSum( BchSts,ClrDat,ClrSce,SSysId,SndBNo,RSysId,RcvBNo,TraKnd,OIFlag,FilNam,RefFil,BchSqn,RefSqn,CusSqn,TotNum,TotAmt,RefNum,RefAmt,RtnCod,ReServ,NodNo, BrNo )
                                    values( :sBchSts,:sClrDat,:sClrSce,:sSSysId,:sSndBNo,:sRSysId,:sRcvBNo,:sTraKnd,:sOIFlag,:sFilNam,:sRefFil,:sBchSqn,:sRefSqn,:sCusSqn,:sTotNum,:sTotAmt,:sRefNum,:sRefAmt,:sRtnCod,:sReServ,:sNodNo,:sBrNo );
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:insert��CbsBchSum������-�ļ���:��%s��!\n", sSrc8583Fil );
            bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsBchSum������" );
            strcpy( sMsgTyp, "E" );
            strcpy( sRspCod, "CBS999" );
            strcpy( sRspMsg, "�Ǽ��ļ�������" );
            etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
            etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
            etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
            fclose( rfp );
            continue;
          }
        }  else {
          bpErrorLog( trdata, "CbsFLstToDb:�����ļ���%s���ظ�����!\n", sSrc8583Fil );
        }
        fclose( rfp );
/*
**  �������׻�Ӧ�ļ�
*/
        switch( atoi( sTxnKnd ) ) {
          case 105101:   /* �������� */
          case 105102:   /* ���ڴ��� */
            strcpy( sMsgId, "2222" );
            break;
          case 105201:   /* ���ڽ�� */
            strcpy( sMsgId, "2242" );
            break;
          default:
            bpErrorLog( trdata, "CbsFileToDb:�޷�����%s����������!\n", sTxnKnd );
            bpAddResult( TrNode, "CBS999", "�޷�����ñ�������" );
            strcpy( sMsgTyp, "E" );
            strcpy( sRspCod, "CBS999" );
            strcpy( sRspMsg, "�޷�����ñ�������" );
            etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
            etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
            etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
            fclose( slst_fp );
            fclose( dlst_fp );
            fclose( rlst_fp );
            return( -1 );
        } /* end of switch( atoi( sTxnKnd ) ) */
/*
**  ����ǰ����ˮ�Ų�����Ϊ��Ӧ�ļ������κ�
*/
        ClearStr( sLogNo );
        if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
          bpErrorLog( trdata, "CbsFileToDb:ȡǰ����ˮ�Ŵ��ļ�����%s��!\n", sSrcFil );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          sprintf( sRspMsg, "ȡǰ����ˮ�Ŵ��ļ�����%s��!\n", sSrcFil );
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
          bpAddResult( TrNode, "CBS999", "�򿪻�Ӧ�ļ���" );
          bpErrorLog( trdata, "CbsFLstToDb:�򿪻�Ӧ�ļ���%s��ʧ��!\n", sDFil );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          sprintf( sRspMsg, "�򿪻�Ӧ�ļ���%s����", sDFil );
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
**  �������ݲ���
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
**  �Ǽǻ�Ӧ�ļ��б����޸����ݿ������׻�Ӧ�ļ���
*/
        fprintf( slst_fp, "%s\n", sDesFil );
        fprintf( dlst_fp, "%s\n", sRefFil );
        EXEC SQL update CbsBchSum set AckFil1=:sDesFil where FilNam=:sRefFil and OIFlag='1' and BchSts='U';
        if( SQLCODE != SQL_SUCCESS ) {
          bpErrorLog( trdata, "CbsFLstToDb:�޸ġ�CbsBchSum������-�ļ���:��%d����%s����%s��!\n", SQLCODE, sRefFil, sDesFil );
          continue;
        }
        break;
      case 2210:  /*���ڴ������ʵ�����֪ͨ�����ڽ�����ʵ�ACK��Ӧ*/
/*
**  �޸��������״̬Ϊ��C���ѻ�Ӧ������ϸ����������޸�ΪD��������
**  ��8583�ļ�ת��Ϊ��ͨ��ʽ���ṩ����ϸ��ʹ��
**  �������׻�Ӧ
*/
        ClearStr( sUpdFil );
        ClearStr( sOClrDat );
        ClearStr( sOClrSce );
        strcpy( sUpdFil, sRefFil );
        strcpy( sOClrDat, sClrDat );
        strcpy( sOClrSce, sClrSce );
        if( ( strcmp( sRtnCod, "000I1000" )==0 ) || ( strcmp( sRtnCod, "" )==0 ) ) { /*���ĳɹ���������֪ͨ�ļ�*/
          if( ( strcmp( sTxnKnd,"105101" )==0 ) || ( strcmp( sTxnKnd,"105102" )==0 ) ) {   /*���ڴ���*/
            strcpy( sMsgId, "2212" );
/*
**  ����ǰ����ˮ�Ų�����Ϊ��Ӧ�ļ������κ�
*/
            ClearStr( sLogNo );
            if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
              bpErrorLog( trdata, "CbsFileToDb:ȡǰ����ˮ�Ŵ��ļ�����%s��!\n", sSrcFil );
              strcpy( sMsgTyp, "E" );
              strcpy( sRspCod, "CBS999" );
              sprintf( sRspMsg, "ȡǰ����ˮ�Ŵ��ļ�����%s��!\n", sSrcFil );
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
              bpAddResult( TrNode, "CBS999", "�򿪻�Ӧ�ļ���" );
              bpErrorLog( trdata, "CbsFLstToDb:�򿪻�Ӧ�ļ���%s��ʧ��!\n", sDFil );
              strcpy( sMsgTyp, "E" );
              strcpy( sRspCod, "CBS999" );
              sprintf( sRspMsg, "�򿪻�Ӧ�ļ���%s����", sDFil );
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
**  �������ݲ���
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
**  �Ǽǻ�Ӧ�ļ��б����޸����ݿ������׻�Ӧ�ļ���
**  ԭ�����ļ�����Ϊ�����ļ���( sFilNam->sRefFil )������ɾ���б��ΪsRefFil
*/
            fprintf( slst_fp, "%s\n", sDesFil );
            fprintf( dlst_fp, "%s\n", sRefFil );
          }  else {   /*���ڽ��*/
            ClearStr( sDesFil );
          }
          EXEC SQL update CbsBchSum Set BchSts='R', ClrDat=:sOClrDat, ClrSce=:sOClrSce, ClrFil=:sRefFil, AckFil1=:sDesFil where FilNam=:sUpdFil and OIFlag='0' and BchSts='C';
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "CbsFLstToDb:�޸ġ�CbsBchSum������-�ļ���:��%d����%s����%s����%s��!\n", SQLCODE, sRefFil, sDesFil, sUpdFil );
            bpErrorLog( trdata, "CbsFLstToDb:�����ڴ��������ļ���%s����%s��ʧ��!\n", sSrc8583Fil, sRefFil );
          }
        } else {
          bpErrorLog( trdata, "CbsFLstToDb:����ACK2220�ļ���%s��ʧ�ܣ�ԭ�����ļ���%s��,�����롾%s��!\n", sSrc8583Fil, sRefFil, sRtnCod );
        }
        break;
    } /* End of Switch(sMsgId) */
  } /* End of while( !feof( rlst_fp ) ) */
  fclose( slst_fp );
  fclose( dlst_fp );
  fclose( rlst_fp );
  strcpy( sMsgTyp, "N" );
  strcpy( sRspCod, "000000" );
  strcpy( sRspMsg, "���׳ɹ�" );
  etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
  etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
  etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
  bpTraceLog( trdata, "End CbsFLstToDb.\n" );
  return(0);
}
/******************************************************************************
  Function          : CbsFDtlToDb
  Description       : ������8583�����ļ�ת��Ϊ��ͨ�ļ������ݲ������ݿ�
  Input             : ETF *TrNode  ������
                      ST_TranData* trdata  �����ṹ
                      char* args  ����
                      DBConHandle* DBHandle  ���ݿ���
  Output            : �����������˵����
  Return            : 0--�ɹ� С��0--ʧ��
  Others            : ����˵��
******************************************************************************/
int CbsFDtlToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*��ڲ���*/
    char   sDskNo[DskNoLen+1];
    char   sFilPth[FilPthLen+1];
    char   sDtlFil[FNameLen+1];
/*��Сͨ��������*/
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
/*����Ӧ�ñ���ͷ*/
    char   sClrDat[ClrDatLen+1]; /*��������*/
    char   sClrSce[ClrSceLen+1]; /*���㳡��*/
    char   sSSysId[SSysIdLen+1]; /*����ϵͳ��*/
    char   sSndBNo[SndBNoLen+1]; /*���𷽴���*/
    char   sRSysId[RSysIdLen+1]; /*���շ�ϵͳ��*/
    char   sRcvBNo[RcvBNoLen+1]; /*���շ�����*/
    char   sTraKnd[TraKndLen+1]; /*��������*/
    char   sFilNam[FilNamLen+1]; /*�ļ���*/
    char   sRefFil[RefFilLen+1]; /*�����ļ���*/
    char   sBchSqn[BchSqnLen+1]; /*���������*/
    char   sRefSqn[RefSqnLen+1]; /*�ο����������*/
    char   sCusSqn[CusSqnLen+1]; /*�ͻ����������*/
    char   sTotNum[TotNumLen+1]; /*�����ܱ���*/
    char   sTotAmt[TotAmtLen+1]; /*�����ܽ��*/
    char   sRefNum[RefNumLen+1]; /*�ܾ�֧���ܱ���*/
    char   sRefAmt[RefAmtLen+1]; /*�ܾ�֧���ܽ��*/
    char   sRtnCod[RtnCodLen+1]; /*������*/
    char   sReServ[ReServLen+1]; /*Ԥ��λ*/
/*������¼Ӧ�ñ���ͷ*/
    char   sMsgSqn[MsgSqnLen+1]; /*��Ϣ���*/
    char   sRefMsg[MsgSqnLen+1]; /*�ο���Ϣ���*/
/*������¼������*/
    char   sMsgId[MsgIdLen+1];     /*�������ͱ�ʶ��*/
    char   sTxnKnd[TxnKndLen+1];   /*��������ϸ��*/
    char   sTxnAmt[TxnAmtLen+1];   /*���׽��*/
    char   sTraTm[TraTmLen+1];     /*���׷������ں�ʱ��*/
    char   sClrBNo[ClrBNoLen+1];   /*ֱ��������*/
    char   sSndDat[SndDatLen+1];   /*ί������*/
/*����ͷ�Ѷ���
    char   sClrDat[ClrDatLen+1];   *��������*
*/
    char   sCcyCod[CcyCodLen+1];   /*���׻�������*/
    char   sQryTyp[QryTypLen+1];   /*��ѯ֪ͨ����*/
    char   sAreaNo[AreaNoLen+1];   /*������*/
    char   sSvrCod[SvrCodLen+1];   /*��������뷽ʽ��*/
    char   sCenId[CenIdLen+1];     /*���Ŀͻ���*/
    char   sCusId[CusIdLen+1];     /*��ҵ�ͻ���*/
    char   sCenTm[CenTmLen+1];     /*������������ʱ��*/
    char   sCenLog[CenLogLen+1];   /*���������*/
    char   sThdTm[ThdTmLen+1];     /*ҵ������������ʱ��*/
    char   sThdLog[ThdLogLen+1];   /*ҵ��������ˮ��*/
/*����ͷ�Ѷ���
    char   sRtnCod[RtnCodLen+1];   *������*
*/
    char   sCshFlg[CshFlgLen+1];   /*�ֽ�ת�ʱ�־*/
    char   sSmrCod[SmrCodLen+1];   /*ժҪ����*/
    char   sUsgCod[UsgCodLen+1];   /*�ʽ���;����*/
    char   sRSdFlg[RSdFlgLen+1];   /*�ط���ʶ*/
    char   sAccFlg[AccFlgLen+1];   /*�Թ���˽��ʶ*/
    char   sTBusTp[TBusTpLen+1];   /*ҵ������*/
    char   sCardFg[CardFgLen+1];   /*���۱�ʶ*/
    char   sBillFg[BillFgLen+1];   /*�����㻧��ʶ*/
    char   sFeeTyp[FeeTypLen+1];   /*�շѷ�ʽ*/
    char   sPayFuc[PayFucLen+1];   /*֧������*/
    char   sAuthCd[AuthCdLen+1];   /*��Ȩ��*/
    char   sPayLvl[PayLvlLen+1];   /*֧�����ȼ�*/
    char   sOrgId[OrgIdLen+1];     /*ԭ����Ԫ*/
/*����ͷ�Ѷ���
    char   sSndBNo[SndBNoLen+1];   *�������к�*
*/
    char   sSOpnBk[SOpnBkLen+1];   /*�����˿������к�*/
    char   sSndNod[SndNodLen+1];   /*�����������*/
    char   sSndAct[SndActLen+1];   /*�������˺�*/
    char   sSndNm[SndNmLen+1];     /*����������*/
    char   sVchId[VchIdLen+1];     /*ƾ֤�ύ��*/
/*����ͷ�Ѿ�����
    char   sRcvBNo[RcvBNoLen+1];   *�������к�*
*/
    char   sROpnBk[ROpnBkLen+1];   /*�����˿������к�*/
    char   sRcvNod[RcvNodLen+1];   /*�����������*/
    char   sRcvAct[RcvActLen+1];   /*�������˺�*/
    char   sRcvNm[RcvNmLen+1];     /*����������*/
    char   sAgrNo[AgrNoLen+1];     /*Э���*/
    char   sSysSts[SysStsLen+1];   /*ϵͳ����״̬*/
    char   sCreAmt[CreAmtLen+1];   /*�������*/
    char   sCreCnt[CreCntLen+1];   /*��������*/
    char   sDebAmt[DebAmtLen+1];   /*�跽���*/
    char   sDebCnt[DebCntLen+1];   /*�跽����*/
    char   sCTraKnd[CTraKndLen+1]; /*��������*/
    char   sOSgnId[OSgnIdLen+1];   /*�ɵ�½��ʶ*/
    char   sNSgnId[NSgnIdLen+1];   /*�µ�½��ʶ*/
    char   sSmr[SmrLen+1];         /*����ժҪ*/
    char   sSecKey[SecKeyLen+1];   /*��Ѻ*/
    char   sTCrpCd[TCrpCdLen+1];   /*��ҵ��������*/
    char   sSvrKnd[SvrKndLen+1];   /*������Ϣ����*/
    char   sTBilNo[TBilNoLen+1];   /*˰Ʊ����*/
    char   sTaxNo[TaxNoLen+1];     /*��˰�˱���*/
    char   sTaxer[TaxerLen+1];     /*��˰������*/
    char   sTaxLvl[TaxLvlLen+1];   /*Ԥ�㼶��*/
    char   sTSubCd[TSubCdLen+1];   /*Ԥ���Ŀ*/
    char   sTOrgCd[TOrgCdLen+1];   /*���ջ��ش���*/
    char   sTActDt[TActDtLen+1];   /*˰Ʊ�޽�����*/
    char   sSvrMsg[SvrMsgLen+1];   /*������Ϣ����*/
    char   sSndNm2[SndNm2Len+1];   /*���ӷ���������*/
    char   sSndAdr[SndAdrLen+1];   /*�����˵�ַ*/
    char   sRcvNm2[RcvNm2Len+1];   /*���ӽ���������*/
    char   sRcvAdr[RcvAdrLen+1];   /*�����˵�ַ*/
/*�������*/
    char   sAgrKnd[AgrKndLen+1];   /*Э������*/
    char   sBokAct[ActNoLen+1];    /*Э��ͻ��ʺţ����ڽ��Թ��ʻ���18λת21λ*/
    char   sOrnCnt[OrnCntLen+1];
    char   sCtlNod[CtlNodLen+1];
/*
**�ʻ�����ʹ��
*/
    char   sBgnLoc[BgnLocLen+1];
    char   sCenLen[CenLenLen+1];
  EXEC SQL END DECLARE SECTION;
    char   sSrcFil[FilNamLen];
    char   sDesFil[FilNamLen];
    char   sTmpDat[15];
    FILE   *fp;
    int    i=0,iOrnCnt=0;

/*  ���ø�����Ϣ */
  bpTraceLog( trdata, "Begin CbsFDtlToDb.\n" );
/*��������������*/
  if( Step_Args_Num != 0 ) {
    bpAddResult( TrNode, "CBS999", "����������" );
    bpErrorLog( trdata, "CbsFDtlToDb: ����������!" );
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
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾FilNam������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾FilNam������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TraKnd", sTraKnd, TraKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TraKnd������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TraKnd������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "DtlFil", sDtlFil, FNameLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾DtlFil������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾DtlFil������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "OIFlag", sOIFlag, OIFlagLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾FilNam������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾FilNam������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾ActDat������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾ActDat����%d������!\n", i );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾DskNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾DskNo����%d������!\n", i );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TTxnCd������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TTxnCd������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾HTxnCd������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾HTxnCd������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnSt", sHTxnSt, HTxnStLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾HTxnSt������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾HTxnSt������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TxnObj������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TxnObj������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TxnCnl������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TxnCnl������!\n" );
    return( -1 );
  }
/*
**  ������������ܱ��Ӧ��¼�޸�Ϊ"B"(Booking������)
*/
  ClearStr( sBchSts );
  if( strcmp( sOIFlag, "1" )==0 ) { /* ���� */
    if( strcmp( sTraKnd, "1052" )==0 ) { /*��ǣ�B-׼������*/
      strcpy( sBchSts, "B" );
    } else { /*���ǣ�D-������*/
      strcpy( sBchSts, "D" );
    }
    EXEC SQL update CbsBchSum
                set  BchSts = :sBchSts, ActDat=:sActDat, DskNo=:sDskNo
              where FilNam = :sFilNam
                and OIFlag = '1'
                and BchSts = 'U';
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, _DB_QUERY_ERR, "�޸ı�CbsBchSum���쳣" );
      bpErrorLog(trdata, "CbsFDtlToDb:�޸ı�CbsBchSum���쳣��%d����%s��", SQLCODE, sFilNam);
      return( -1 );
    }
  } else { /* ���� */
    EXEC SQL update CbsBchSum
                set  BchSts = 'D', ActDat=:sActDat, DskNo=:sDskNo
              where FilNam = :sFilNam
                and OIFlag = '0'
                and BchSts = 'R';
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, _DB_QUERY_ERR, "�޸ı�CbsBchSum���쳣" );
      bpErrorLog(trdata, "CbsFDtlToDb:�޸ı�CbsBchSum���쳣��%d����%s��", SQLCODE, sFilNam);
      return( -1 );
    }
  }
/*
**  ��ʼ���������ļ�
*/
  fp =fopen( sDtlFil, "r" );
  if( fp == NULL ) {
    bpAddResult( TrNode, "CBS999", "�������ļ���" );
    bpErrorLog( trdata, "CbsFDtlToDb:�������ļ���%s��ʧ��!\n", sDtlFil );
    return( -1 );
  }
/*
** ���������ļ��ĵ�һ�в��Ǽǻ��ܱ�
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
  fscanf( fp, "%[^|]",  sClrDat ); /* �������� */
  fscanf( fp, "|%[^|]", sClrSce ); /* ���㳡�� */
  fscanf( fp, "|%[^|]", sSSysId ); /* ����ϵͳ�� */
  fscanf( fp, "|%[^|]", sSndBNo ); /* ���𷽴��� */
  fscanf( fp, "|%[^|]", sRSysId ); /* ���շ�ϵͳ�� */
  fscanf( fp, "|%[^|]", sRcvBNo ); /* ���շ����� */
  fscanf( fp, "|%[^|]", sTraKnd ); /* �������� */
  fscanf( fp, "|%[^|]", sFilNam ); /* �ļ��� */
  fscanf( fp, "|%[^|]", sRefFil ); /* �����ļ��� */
  fscanf( fp, "|%[^|]", sBchSqn ); /* ��������� */
  fscanf( fp, "|%[^|]", sRefSqn ); /* �ο���������� */
  fscanf( fp, "|%[^|]", sCusSqn ); /* �ͻ���������� */
  fscanf( fp, "|%[^|]", sTotNum ); /* �����ܱ��� */
  fscanf( fp, "|%[^|]", sTotAmt ); /* �����ܽ�� */
  fscanf( fp, "|%[^|]", sRefNum ); /* �ܾ�֧���ܱ��� */
  fscanf( fp, "|%[^|]", sRefAmt ); /* �ܾ�֧���ܽ�� */
  fscanf( fp, "|%[^|]", sRtnCod ); /* ������ */
  fscanf( fp, "|%[^\n]",sReServ ); /* Ԥ��λ */
/*
** ����������ϸ
*/
  iOrnCnt=atol(sTotNum);
  for( i=1; i<=atol(sTotNum); i++ ) {
    ClearStr( sMsgSqn  ); /*��Ϣ���*/
    ClearStr( sRefMsg  ); /*�ο���Ϣ���*/
    ClearStr( sMsgId   ); /*�������ͱ�ʶ��*/
    ClearStr( sTxnKnd  ); /*��������ϸ������*/
    ClearStr( sTxnAmt  ); /*���׽��*/
    ClearStr( sTraTm   ); /*���׷������ں�ʱ��*/
    ClearStr( sClrBNo  ); /*ֱ��������*/
    ClearStr( sTmpDat  ); /*ί������*/
    ClearStr( sSndDat  ); /*ί������*/
    ClearStr( sClrDat  ); /*��������*/
    ClearStr( sQryTyp  ); /*��ѯ֪ͨ�����ʶ*/
    ClearStr( sAreaNo  ); /*������*/
    ClearStr( sCcyCod  ); /*���׻��Ҵ���*/
    ClearStr( sSvrCod  ); /*��������뷽ʽ��*/
    ClearStr( sCenId   ); /*���Ŀͻ���*/
    ClearStr( sCusId   ); /*��ҵ�ͻ���*/
    ClearStr( sCenTm   ); /*���Ľ�����������ʱ��*/
    ClearStr( sCenLog  ); /*���Ľ��������*/
    ClearStr( sThdTm   ); /*ҵ������������ʱ��*/
    ClearStr( sThdLog  ); /*ҵ������ˮ��*/
    ClearStr( sRtnCod  ); /*������*/
    ClearStr( sCshFlg  ); /*�ֽ�ת�˱�ʶ*/
    ClearStr( sSmrCod  ); /*ժҪ����*/
    ClearStr( sUsgCod  ); /*�ʽ���;����*/
    ClearStr( sRSdFlg  ); /*�ط���ʶ*/
    ClearStr( sAccFlg  ); /*�Թ���˽��ʶ*/
    ClearStr( sTBusTp  ); /*ҵ������*/
    ClearStr( sCardFg  ); /*���۱�ʶ*/
    ClearStr( sAccKnd  ); /*�����㻧��ʶ*/
    ClearStr( sFeeTyp  ); /*�����ѷ�ʽ*/
    ClearStr( sPayFuc  ); /*֧������*/
    ClearStr( sAuthCd  ); /*��Ȩ��*/
    ClearStr( sPayLvl  ); /*֧�����ȼ�*/
    ClearStr( sOrgId   ); /*ԭ����ҵ��Ψһ��ʶ*/
    ClearStr( sSndBNo  ); /*�������к�*/
    ClearStr( sSOpnBk  ); /*�����˿������к�*/
    ClearStr( sSndNod  ); /*�����������*/
    ClearStr( sSndAct  ); /*�������˺�*/
    ClearStr( sSndNm   ); /*����������*/
    ClearStr( sVchId   ); /*ƾ֤�ύ��*/
    ClearStr( sRcvBNo  ); /*�������к�*/
    ClearStr( sROpnBk  ); /*�����˿������к�*/
    ClearStr( sRcvNod  ); /*�����������*/
    ClearStr( sRcvAct  ); /*�������˺�*/
    ClearStr( sRcvNm   ); /*����������*/
    ClearStr( sAgrNo   ); /*�෽Э���*/
    ClearStr( sSysSts  ); /*ϵͳ����״̬*/
    ClearStr( sCreAmt  ); /*�������*/
    ClearStr( sCreCnt  ); /*��������*/
    ClearStr( sDebAmt  ); /*�跽���*/
    ClearStr( sDebCnt  ); /*�跽����*/
    ClearStr( sCTraKnd ); /*��������*/
    ClearStr( sOSgnId  ); /*�ɵ�½��ʶ*/
    ClearStr( sNSgnId  ); /*�µ�½��ʶ*/
    ClearStr( sSmr     ); /*����ժҪ(300)*/
    ClearStr( sSecKey  ); /*��Ѻ*/
    ClearStr( sTCrpCd  ); /*��ҵ��������*/
    ClearStr( sSvrKnd  ); /*������Ϣ����*/
    ClearStr( sTBilNo  ); /*˰Ʊ����*/
    ClearStr( sTaxNo   ); /*��˰�˱���*/
    ClearStr( sTaxer   ); /*��˰������*/
    ClearStr( sTaxLvl  ); /*Ԥ�㼶��*/
    ClearStr( sTSubCd  ); /*Ԥ���Ŀ*/
    ClearStr( sTOrgCd  ); /*���ջ��ش���*/
    ClearStr( sTActDt  ); /*˰Ʊ�޽�����*/
    ClearStr( sSvrMsg  ); /*������Ϣ����*/
    ClearStr( sSndNm2  ); /*���ӷ���������*/
    ClearStr( sSndAdr  ); /*�����˵�ַ*/
    ClearStr( sRcvNm2  ); /*���ӽ���������*/
    ClearStr( sRcvAdr  ); /*�����˵�ַ*/
/*
**  ר�����ڴ�����SIR�����еķǷ��ַ�
*/
    if ( i==1 ) {
        fscanf( fp, "\n%[^|]", sMsgSqn );   /*��Ϣ���*/
    } else {
        fscanf( fp, "|\n%[^|]", sMsgSqn );   /*��Ϣ���*/
    }  
    fscanf( fp, "|%[^|]", sRefMsg  );   /*�ο���Ϣ���*/
    fscanf( fp, "|%[^|]", sMsgId   );   /*�������ͱ�ʶ��*/
    fscanf( fp, "|%[^|]", sTxnKnd  );   /*��������ϸ��*/
    fscanf( fp, "|%[^|]", sTxnAmt  );   /*���׽��*/
    fscanf( fp, "|%[^|]", sTraTm   );   /*���׷������ں�ʱ��*/
    fscanf( fp, "|%[^|]", sClrBNo  );   /*ֱ��������*/
    fscanf( fp, "|%[^|]", sTmpDat  );   /*ί������*/
    strncpy( sSndDat, sTmpDat, 8 );     /*ɾ����λ��0*/
    fscanf( fp, "|%[^|]", sClrDat  );   /*��������*/
    fscanf( fp, "|%[^|]", sQryTyp  );   /*��ѯ֪ͨ����*/
    fscanf( fp, "|%[^|]", sAreaNo  );   /*������*/
    fscanf( fp, "|%[^|]", sCcyCod  );   /*���׻��Ҵ���*/
    fscanf( fp, "|%[^|]", sSvrCod  );   /*��������뷽ʽ��*/
    fscanf( fp, "|%[^|]", sCenId   );   /*���Ŀͻ���*/
    fscanf( fp, "|%[^|]", sCusId   );   /*��ҵ�ͻ���*/
    fscanf( fp, "|%[^|]", sCenTm   );   /*������������ʱ��*/
    fscanf( fp, "|%[^|]", sCenLog  );   /*���������*/
    fscanf( fp, "|%[^|]", sThdTm   );   /*ҵ������������ʱ��*/
    fscanf( fp, "|%[^|]", sThdLog  );   /*ҵ��������ˮ��*/
    fscanf( fp, "|%[^|]", sRtnCod  );   /*������*/
    fscanf( fp, "|%[^|]", sCshFlg  );   /*�ֽ�ת�ʱ�־*/
    fscanf( fp, "|%[^|]", sSmrCod  );   /*ժҪ����*/
    fscanf( fp, "|%[^|]", sUsgCod  );   /*�ʽ���;����*/
    fscanf( fp, "|%[^|]", sRSdFlg  );   /*�ط���ʶ*/
    fscanf( fp, "|%[^|]", sAccFlg  );   /*�Թ���˽��ʶ*/
    fscanf( fp, "|%[^|]", sTBusTp  );   /*ҵ������*/
    fscanf( fp, "|%[^|]", sCardFg  );   /*���۱�ʶ*/
    fscanf( fp, "|%[^|]", sAccKnd  );   /*�����㻧��ʶ*/
    fscanf( fp, "|%[^|]", sFeeTyp  );   /*�շѷ�ʽ*/
    fscanf( fp, "|%[^|]", sPayFuc  );   /*֧������*/
    fscanf( fp, "|%[^|]", sAuthCd  );   /*��Ȩ��*/
    fscanf( fp, "|%[^|]", sPayLvl  );   /*֧�����ȼ�*/
    fscanf( fp, "|%[^|]", sOrgId   );   /*ԭ����Ԫ*/
    fscanf( fp, "|%[^|]", sSndBNo  );   /*�������к�*/
    fscanf( fp, "|%[^|]", sSOpnBk  );   /*�����˿������к�*/
    fscanf( fp, "|%[^|]", sSndNod  );   /*�����������*/
    fscanf( fp, "|%[^|]", sSndAct  );   /*�������˺�*/
    fscanf( fp, "|%[^|]", sSndNm   );   /*����������*/
    fscanf( fp, "|%[^|]", sVchId   );   /*ƾ֤�ύ��*/
    fscanf( fp, "|%[^|]", sRcvBNo  );   /*�������к�*/
    fscanf( fp, "|%[^|]", sROpnBk  );   /*�����˿������к�*/
    fscanf( fp, "|%[^|]", sRcvNod  );   /*�����������*/
    fscanf( fp, "|%[^|]", sRcvAct  );   /*�������˺�*/
    fscanf( fp, "|%[^|]", sRcvNm   );   /*����������*/
    fscanf( fp, "|%[^|]", sAgrNo   );   /*Э���*/
    fscanf( fp, "|%[^|]", sSysSts  );   /*ϵͳ����״̬*/
    fscanf( fp, "|%[^|]", sCreAmt  );   /*�������*/
    fscanf( fp, "|%[^|]", sCreCnt  );   /*��������*/
    fscanf( fp, "|%[^|]", sDebAmt  );   /*�跽���*/
    fscanf( fp, "|%[^|]", sDebCnt  );   /*�跽����*/
    fscanf( fp, "|%[^|]", sCTraKnd );   /*��������*/
    fscanf( fp, "|%[^|]", sOSgnId  );   /*�ɵ�½��ʶ*/
    fscanf( fp, "|%[^|]", sNSgnId  );   /*�µ�½��ʶ*/
    fscanf( fp, "|%[^|]", sSmr     );   /*����ժҪ*/
    fscanf( fp, "|%[^|]", sSecKey  );   /*��Ѻ*/
    fscanf( fp, "|%[^|]", sTCrpCd  );   /*��ҵ��������*/
    fscanf( fp, "|%[^|]", sSvrKnd  );   /*������Ϣ����*/
    fscanf( fp, "|%[^|]", sTBilNo  );   /*˰Ʊ����*/
    fscanf( fp, "|%[^|]", sTaxNo   );   /*��˰�˱���*/
    fscanf( fp, "|%[^|]", sTaxer   );   /*��˰������*/
    fscanf( fp, "|%[^|]", sTaxLvl  );   /*Ԥ�㼶��*/
    fscanf( fp, "|%[^|]", sTSubCd  );   /*Ԥ���Ŀ*/
    fscanf( fp, "|%[^|]", sTOrgCd  );   /*���ջ��ش���*/
    fscanf( fp, "|%[^|]", sTActDt  );   /*˰Ʊ�޽�����*/
/**
    fscanf( fp, "|%[^|]", sSvrMsg  );   *������Ϣ����*
**/
    fscanf( fp, "|%[^|]", sSndNm2  );   /*���ӷ���������*/
    fscanf( fp, "|%[^|]", sSndAdr  );   /*�����˵�ַ*/
    fscanf( fp, "|%[^|]", sRcvNm2  );   /*���ӽ���������*/
    fscanf( fp, "|%[^|]", sRcvAdr  );   /*�����˵�ַ*/
/*
**  ȡǰ����ˮ�ţ��ṩ��Сͨ�������ݼ��������ʵ�Ψһ��־
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
        bpAddResult( TrNode, "CBS999", "update��CbsBchJnl������" );
        bpErrorLog( trdata, "CbsFDtlToDb:update��CbsBchJnl������%d��-�ļ���%s��-����:��%s����%s����%s����%s����%s��!\n", SQLCODE, sDtlFil, sMsgSqn, sTraKnd, sSndBNo, sSndDat, sVchId );
        return( -1 );
      }
      iOrnCnt=iOrnCnt-1;
    } else {
/*
**  ��ȡǰ����ˮ�ţ�ͬʱ����ҵ������ˮ��
*/
      if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
        bpAddResult( TrNode, "CBS999", "ȡǰ����ˮ�Ŵ�" );
        bpErrorLog( trdata, "CbsFDtlToDb:ȡǰ����ˮ�Ŵ�ҵ��Ψһ��־��%s����%s����%s����%s��!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
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
          bpErrorLog( trdata, "CbsFDtlToDb:�ʺš�%s��δ���շѵ�λ��%s��ǩԼ��Э��š�%s��!\n", sRcvAct, sSndAct, sAgrNo );
          iOrnCnt=iOrnCnt-1;
          strcpy( sBilSts, "E" );
          strcpy( sRtnCod, "001O6065" );
          strcpy( sIsTxn, "N" );
          goto DB_INSERT;
        }
      }
/*
**  ���ݽ����˿������кŻ�ȡ�������кš��������ĺ�
*/
      EXEC SQL select retnod, BrNo
                 into :sNodNo, :sBrNo
                 from pubnodinf
                where SBkNo=:sROpnBk fetch first 1 rows only;
      if( SQLCODE != SQL_SUCCESS ) {
        bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�������кų��������˿������к�:��%s��!\n", sROpnBk );
        iOrnCnt=iOrnCnt-1;
        strcpy( sBilSts, "E" );
        strcpy( sRtnCod, "001O1040" );
        strcpy( sIsTxn, "N" );
        goto DB_INSERT;
      }
/*
**  ���ݷ��к�ȡ��������
*/
      EXEC SQL select CtlNod, CnlSub
                 into :sCtlNod, :sCnlSub
                 from CbsBnkInf
                where BrNo=:sBrNo;
      if( SQLCODE != SQL_SUCCESS ) {
        bpErrorLog( trdata, "CbsFDtlToDb:��ȡ����������������Ʒ�¼��ų��������˿������к�:��%s��!\n", sROpnBk );
        iOrnCnt=iOrnCnt-1;
        strcpy( sBilSts, "E" );
        strcpy( sIsTxn, "N" );
        strcpy( sRtnCod, "001O1040" );
        goto DB_INSERT;
      }
/*
** �˻ز��Զ�����
*/
      if( strcmp( sTBusTp, "99985" )==0 ) {
        bpErrorLog( trdata, "CbsFDtlToDb:�˻�ҵ�����Զ�����:��%s����%s����%s����%s����%s��!\n", sTraKnd,sSndBNo,sSndDat,sVchId,sOIFlag );
        iOrnCnt=iOrnCnt-1;
        strcpy( sBilSts, "E" );
        strcpy( sIsTxn, "N" );
        strcpy( sRtnCod, "001O1040" );
        goto DB_INSERT;
      }
/*
**  ���ݷ��кźͽ���������ȡ���ӹ�Ա��
*/
      if( sqnGetDumTlr( sBrNo, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
        bpErrorLog( trdata, "CbsFDtlToDb:ȡǰ�õ��ӹ�Ա�Ŵ�%s����%s����%s����%s��!\n", sBrNo, sTxnCnl, sCnlSub, sTlrId );
        iOrnCnt=iOrnCnt-1;
        strcpy( sBilSts, "E" );
        strcpy( sIsTxn, "N" );
        strcpy( sRtnCod, "001S3008" );
        goto DB_INSERT;
      }
/*
**  �������
*/
DB_INSERT:
      EXEC SQL insert into CbsBchJnl( FilNam,MsgSqn,TraKnd,SndBNo,SndDat,VchId,OIFlag,BilSts,MsgId,TxnKnd,TxnAmt,TraTm,ClrDat,CcyCod,SvrCod,CenTm,CenLog,ThdTm,ThdLog,RtnCod,CshFlg,SmrCod,UsgCod,RSdFlg,AccFlg,TBusTp,CardFg,AccKnd,FeeTyp,PayFuc,AuthCd,PayLvl,SOpnBk,SndNod,SndAct,SndNm,SndAdr,RcvBNo,ROpnBk,RcvNod,RcvAct,RcvNm,RcvAdr,AgrNo,Smr,SvrKnd,TBilNo,TaxNo,Taxer,TaxLvl,TSubCd,TOrgCd,TActDt,SecKey,BrNo,NodNo,LogNo,ActFlg,BokAct,DskNo,ActDat,TTxnCd,HTxnCd,HTxnSt,IsTxn,TxnObj,TlrId )
                              values( :sFilNam,:sMsgSqn,:sTraKnd,:sSndBNo,:sSndDat,:sVchId,:sOIFlag,:sBilSts,:sMsgId,:sTxnKnd,:sTxnAmt,:sTraTm,:sClrDat,:sCcyCod,:sSvrCod,:sCenTm,:sCenLog,:sThdTm,:sThdLog,:sRtnCod,:sCshFlg,:sSmrCod,:sUsgCod,:sRSdFlg,:sAccFlg,:sTBusTp,:sCardFg,:sAccKnd,:sFeeTyp,:sPayFuc,:sAuthCd,:sPayLvl,:sSOpnBk,:sSndNod,:sSndAct,:sSndNm,:sSndAdr,:sRcvBNo,:sROpnBk,:sRcvNod,:sRcvAct,:sRcvNm,:sRcvAdr,:sAgrNo,:sSmr,:sSvrKnd,:sTBilNo,:sTaxNo,:sTaxer,:sTaxLvl,:sTSubCd,:sTOrgCd,:sTActDt,:sSecKey,:sBrNo,:sNodNo,:sLogNo,:sActFlg,:sBokAct,:sDskNo,:sActDat,:sTTxnCd,:sHTxnCd,:sHTxnSt,:sIsTxn,:sTxnObj,:sTlrId );
      if( SQLCODE != SQL_SUCCESS ) {
        bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsBchJnl������" );
        bpErrorLog( trdata, "CbsFDtlToDb:insert��CbsBchJnl������%d��-�ļ���%s��-����:��%s��!\n", SQLCODE, sDtlFil, sMsgSqn );
/**
bpErrorLog( trdata, "��������:FilNam��%s��MsgSqn��%s��TraKnd��%s��SndBNo��%s��SndDat��%s��VchId��%s��OIFlag��%s��BilSts��%s��MsgId��%s��TxnKnd��%s��TxnAmt��%s��TraTm��%s��ClrDat��%s��CcyCod��%s��SvrCod��%s��CenTm��%s��CenLog��%s��ThdTm��%s��ThdLog��%s��RtnCod��%s��CshFlg��%s��SmrCod��%s��UsgCod��%s��RSdFlg��%s��AccFlg��%s��TBusTp��%s��CardFg��%s��AccKnd��%s��FeeTyp��%s��PayFuc��%s��AuthCd��%s��PayLvl��%s��SOpnBk��%s��SndNod��%s��SndAct��%s��SndNm��%s��SndAdr��%s��RcvBNo��%s��ROpnBk��%s��RcvNod��%s��RcvAct��%s��RcvNm��%s��RcvAdr��%s��AgrNo��%s��Smr��%s��SvrKnd��%s��TBilNo��%s��TaxNo��%s��Taxer��%s��TaxLvl��%s��TSubCd��%s��TOrgCd��%s��TActDt��%s��SecKey��%s��BrNo��%s��NodNo��%s��LogNo��%s��ActFlg��%s��BokAct��%s��DskNo��%s��ActDat��%s��TTxnCd��%s��HTxnCd��%s��HTxnSt��%s��IsTxn��%s��TxnObj��%s��TlrId��%s��!\n", \
sFilNam,sMsgSqn,sTraKnd,sSndBNo,sSndDat,sVchId,sOIFlag,sBilSts,sMsgId,sTxnKnd,sTxnAmt,sTraTm,sClrDat,sCcyCod,sSvrCod,sCenTm,sCenLog,sThdTm,sThdLog,sRtnCod,sCshFlg,sSmrCod,sUsgCod,sRSdFlg,sAccFlg,sTBusTp,sCardFg,sAccKnd,sFeeTyp,sPayFuc,sAuthCd,sPayLvl,sSOpnBk,sSndNod,sSndAct,sSndNm,sSndAdr,sRcvBNo,sROpnBk,sRcvNod,sRcvAct,sRcvNm,sRcvAdr,sAgrNo,sSmr,sSvrKnd,sTBilNo,sTaxNo,sTaxer,sTaxLvl,sTSubCd,sTOrgCd,sTActDt,sSecKey,sBrNo,sNodNo,sLogNo,sActFlg,sBokAct,sDskNo,sActDat,sTTxnCd,sHTxnCd,sHTxnSt,sIsTxn,sTxnObj,sTlrId );
**/
        fclose( fp );
        return( -1 );
      }
    }
  }
  if( strcmp( sOIFlag, "0" )==0 ) {
/*
**  �����̱����Ϊ���ʷ���ʱ����ҵ��Ĵ�Сͨ�����̺ţ���ʱ����������ҵ��
*/
/**
    EXEC SQL update CbsBchJnl
                set DskNo  =:sDskNo
              where FilNam = :sRefFil
                and OIFlag = '0'
                and BilSts = 'B';
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, _DB_QUERY_ERR, "�޸ı�CbsBchJnl���쳣" );
      bpErrorLog(trdata, "CbsFDtlToDb:�޸ı�CbsBchJnl���쳣��%d����%s��", SQLCODE, sRefFil);
      return( -1 );
    }
    EXEC SQL select count(*)
               into :iOrnCnt
               from CbsBchJnl
              where FilNam = :sRefFil
                and OIFlag = '0'
                and BilSts = 'B';
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, "CBS999", "���㡾OrnCnt���쳣" );
      bpErrorLog(trdata, "CbsFDtlToDb:���㡾OrnCnt���쳣��%d��", SQLCODE);
      return( -1 );
    }
**/
  }
  sprintf( sOrnCnt,"%08d", iOrnCnt );
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
/*
**  �رմ����ļ�
*/
  fclose( fp );
  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End CbsFDtlToDb.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsFilConv
  Description       : ����ͨ�ļ�ת��Ϊ8583�ļ�
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin CbsFilConv.\n" );
/*
**  ��������������
*/
  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, "CBS999", "����������" );
    bpErrorLog( trdata, "CbsFilConv: ����������!" );
    return( -1 );
  }
/*
**  ��ȡת��ǰ���ļ���
*/
  ClearStr( sSrcFil );
  ClearStr( sSndFil );
  ClearStr( sDes8583 );
  sprintf( sSrcFil, "%s/%s/%s", getenv("WORKDIR"), Step_Arg2, Step_Arg1 );
  strncpy( sSndFil, Step_Arg1, 36 );
  sprintf( sDes8583, "%s/%s/%s", getenv("WORKDIR"), Step_Arg2, sSndFil );
/*
**  ����8583��ʽת��
*/
  ret=CbsFilChg( "1", sSrcFil, sDes8583 );
  if( ret!=0 ) {
    bpAddResult( TrNode, "CBS999", "�����ļ�ת���쳣" );
    bpErrorLog( trdata, "CbsFilConv:�����ļ���%s��ת���쳣!\n", sDes8583 );
    return( -1 );
  }
/*
**  ��ȡת�����ļ��Ĵ�С
*/
  fp =fopen( sDes8583, "r+" );
  if( fp == NULL ) {
    bpAddResult( TrNode, "CBS999", "�������ļ���" );
    bpErrorLog( trdata, "CbsFilConv:�������ļ���%s��ʧ��!\n", sDes8583 );
    fclose( fp );
    return( -1 );
  }
  fseek( fp, 0, SEEK_SET );
  iFSize=hfgetsize( fp );
  sprintf( sFSize, "%08d", iFSize );
/*
**  �滻�ļ���XXXXXXXXΪ��ʵ�ļ���С
*/
  fseek( fp, F8583SizeOffset, SEEK_SET );
  fwrite( sFSize, sizeof(sFSize)-1, 1, fp );
  fclose( fp );
  etfAddOrRepNode( TrNode, "SndFil", sSndFil, FilNamLen );
  etfAddOrRepNode( TrNode, "FSize", sFSize,  FSizeLen );
  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End CbsFilConv.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsF1051OToDb
  Description       : ���������������ļ����
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**  ����Ҫ��
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin CbsF1051OToDb.\n" );
/*
**  ��������������
*/
  ClearStr( sMsgTyp );
  ClearStr( sRspCod );
  ClearStr( sRspMsg );

  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "����������" );
    bpErrorLog( trdata, "CbsF1051OToDb: ����������!" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "����������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  ��ʼ������
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
**  �������ݳ���
*/
  if( etfGetChildValue(TrNode, "TraKnd", sTraKnd, TraKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TraKnd������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TraKnd������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾TraKnd������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "SndBNo", sSndBNo, SndBNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾SndBNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾SndBNo������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾SndBNo������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾ActDat������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾ActDat������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾ActDat������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  strcpy( sSndDat, sActDat );
  if( etfGetChildValue(TrNode, "OIFlag", sOIFlag, OIFlagLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾OIFlag������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾OIFlag������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾OIFlag������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "MsgId", sMsgId, MsgIdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾MsgId������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾MsgId������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾MsgId������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnKnd", sTxnKnd, TxnKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TxnKnd������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TxnKnd������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾TxnKnd������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TraTm", sTraTm, TraTmLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TraTm������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TraTm������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾TraTm������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CcyCod", sCcyCod, CcyCodLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾CcyCod������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾CcyCod������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾CcyCod������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "SvrCod", sSvrCod, SvrCodLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾SvrCod������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾SvrCod������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾SvrCod������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CshFlg", sCshFlg, CshFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾CshFlg������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾CshFlg������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾CshFlg������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "RsdFlg", sRSdFlg, RSdFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾RsdFlg������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾RsdFlg������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾RsdFlg������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "AccFlg", sAccFlg, AccFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾AccFlg������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾AccFlg������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾AccFlg������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CardFg", sCardFg, CardFgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾CardFg������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾CardFg������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾CardFg������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "AccKnd", sAccKnd, AccKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾AccKnd������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾AccKnd������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾AccKnd������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "FeeTyp", sFeeTyp, FeeTypLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾FeeTyp������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾FeeTyp������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾FeeTyp������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "PayFuc", sPayFuc, PayFucLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾PayFuc������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾PayFuc������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾PayFuc������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "PayLvl", sPayLvl, PayLvlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾PayLvl������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾PayLvl������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾PayLvl������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "SOpnBk", sSOpnBk, SOpnBkLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾SOpnBk������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾SOpnBk������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾SOpnBk������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾NodNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾NodNo������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾NodNo������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActNo", sSndAct, ActNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾ActNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾ActNo������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾ActNo������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActNm", sSndNm, SndNmLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾ActNm������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾ActNm������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾ActNm������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  strcpy( sSecKey, "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
  if ( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾BrNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾BrNo������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾BrNo������" );
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
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾DskNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾DskNo������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾DskNo������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
**/
  if ( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TxnCnl������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TxnCnl������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾TxnCnl������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  ���ݷ��к�ȡ��������
*/
  ClearStr( sCnlSub  );
  EXEC SQL select CnlSub
             into :sCnlSub
             from CbsBnkInf
            where BrNo=:sBrNo;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog( trdata, "CbsF1051OToDb:��ȡ����������������Ʒ�¼��ų�����������к�:��%s��!\n", sBrNo );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "��ȡ����������������Ʒ�¼��ų���" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  sprintf( sFName, "%s/%s/%s", getenv("WORKDIR"), Step_Arg1, Step_Arg2 );
  strcpy( sFilNam, Step_Arg2 );
  fp =fopen( sFName, "r" );
  if( fp == NULL ) {
    bpAddResult( TrNode, "CBS999", "�������ļ���" );
    bpErrorLog( trdata, "CbsF1051OToDb:�������ļ���%s��ʧ��!\n", sFName );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "�������ļ���" );
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
**  ����ǰ����ˮ����Ϊ��Ϣ��š�ƾ֤�ύ��
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
**  ������ʼֵ
*/
    strcpy( sBilSts, "P" );
    strcpy( sIsTxn, "N" );
    if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
      bpErrorLog( trdata, "CbsFileToDb:ȡǰ����ˮ�Ŵ��ļ�����%s��!\n", sFName );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "ȡǰ����ˮ�Ŵ��ļ�����%s��!\n", sFName );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
      fclose( fp );
      return( -1 );
    }

    sprintf( sMsgSqn, "%s%s", SYSID, sLogNo+2 );
    memcpy( sVchId, sLogNo+6, 8 );
/*
**  ���л�ȡ����
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
**  ȥ������е�С���㣬��ת��Ϊָ����ʽ
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
      sprintf( sRspMsg, "�ļ���%s���ڡ�%d��������!", sFilNam, iRecNum+1 );
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
**  ��������Ϊ���пͻ�
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
          bpErrorLog( trdata, "CbsFDtlToDb:�ʺš�%s���¾��ʺŶ��ձ�����!\n", sRcvAct );
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
            if( ( memcmp(sRcvAct+ActNoLen-VchTypLen,"209",VchTypLen)==0 )||( memcmp(sRcvAct+ActNoLen-VchTypLen,"229",VchTypLen)==0 ) ) { /* �����ý��ʺ� */
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
**  ���ݷ��кźͽ���������ȡ���ӹ�Ա��
*/
      if( strcmp( sBilSts, "E")!=0 ) {
        if( sqnGetDumTlr( sBrNo, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
          bpErrorLog( trdata, "CbsF1051OToDb:ȡǰ�õ��ӹ�Ա�Ŵ�%s����%s����%s��!\n", sBrNo, sTxnCnl, sCnlSub );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "ȡǰ�õ��ӹ�Ա�Ŵ�" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          fclose( fp );
          return( -1 );
        }
      }
    } else {
/*
**  �����в��ǽ���
**  �жϸ��к��Ƿ������ڷ���ϵͳ
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
        bpErrorLog( trdata, "CbsF1051OToDb:�кš�%s����%s��δ��ͨ����ҵ��!\n", sROpnBk, sActDat );
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
      bpErrorLog( trdata, "CbsF1051OToDb:insert��CbsBchJnl������%d��-�ļ���%s��!\n", SQLCODE, sFName );
      bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsBchJnl������" );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      strcpy( sRspMsg, "�������ʧ��" );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
/**
bpErrorLog( trdata, "����-1-����:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", \
sFilNam, sMsgSqn, sTraKnd, sSndBNo, sSndDat, sVchId, sBilSts, sOIFlag, sMsgId, sTxnKnd );
bpErrorLog( trdata, "����-2-����:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", \
sTxnAmt, sTraTm,  sCcyCod, sSvrCod, sCshFlg, sSmrCod, sUsgCod, sRSdFlg, sAccFlg, sTBusTp );
bpErrorLog( trdata, "����-3-����:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", \
sCardFg, sAccKnd, sFeeTyp,sPayFuc, sSOpnBk, sSndNod, sSndAct, sSndNm, sRcvBNo, sROpnBk );
bpErrorLog( trdata, "����-4-����:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", \
sRcvAct, sRcvNm, sSmr, sSecKey, sBrNo, sNodNo, sLogNo, sDskNo, sTxnCnl, sActFlg );
**/
      fclose( fp );
      return( -1 );
    }
/*
**  �����ܱ������ܽ��ṩ�˶Թ���
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
  strcpy( sRspMsg, "���׳ɹ�" );
  etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
  etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
  etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
  bpTraceLog( trdata, "End CbsF1051OToDb.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsF1052OToDb
  Description       : �����ڽ�������ļ����
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**  ����Ҫ��
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin CbsF1052OToDb.\n" );
/*
**  ��������������
*/
  ClearStr( sMsgTyp );
  ClearStr( sRspCod );
  ClearStr( sRspMsg );

  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "����������" );
    bpErrorLog( trdata, "CbsF1052OToDb: ����������!" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "����������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  ��ʼ������
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
**  �������ݳ���
*/
  if( etfGetChildValue(TrNode, "TraKnd", sTraKnd, TraKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TraKnd������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TraKnd������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾TraKnd������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "SndBNo", sSndBNo, SndBNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾SndBNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾SndBNo������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾SndBNo������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾ActDat������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾ActDat������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾ActDat������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  strcpy( sSndDat, sActDat );
  if( etfGetChildValue(TrNode, "OIFlag", sOIFlag, OIFlagLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾OIFlag������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾OIFlag������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾OIFlag������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "MsgId", sMsgId, MsgIdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾MsgId������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾MsgId������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾MsgId������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnKnd", sTxnKnd, TxnKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TxnKnd������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TxnKnd������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾TxnKnd������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TraTm", sTraTm, TraTmLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TraTm������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TraTm������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾TraTm������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CcyCod", sCcyCod, CcyCodLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾CcyCod������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾CcyCod������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾CcyCod������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "SvrCod", sSvrCod, SvrCodLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾SvrCod������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾SvrCod������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾SvrCod������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CshFlg", sCshFlg, CshFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾CshFlg������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾CshFlg������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾CshFlg������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "RsdFlg", sRSdFlg, RSdFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾RsdFlg������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾RsdFlg������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾RsdFlg������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "AccFlg", sAccFlg, AccFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾AccFlg������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾AccFlg������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾AccFlg������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CardFg", sCardFg, CardFgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾CardFg������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾CardFg������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾CardFg������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "AccKnd", sAccKnd, AccKndLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾AccKnd������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾AccKnd������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾AccKnd������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "FeeTyp", sFeeTyp, FeeTypLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾FeeTyp������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾FeeTyp������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾FeeTyp������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "PayFuc", sPayFuc, PayFucLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾PayFuc������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾PayFuc������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾PayFuc������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "PayLvl", sPayLvl, PayLvlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾PayLvl������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾PayLvl������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾PayLvl������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "SOpnBk", sSOpnBk, SOpnBkLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾SOpnBk������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾SOpnBk������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾SOpnBk������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾NodNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾NodNo������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾NodNo������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActNo", sSndAct, ActNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾ActNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾ActNo������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾ActNo������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "ActNm", sSndNm, SndNmLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾ActNm������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾ActNm������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾ActNm������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  strcpy( sSecKey, "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
  if ( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾BrNo������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾BrNo������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾BrNo������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  sprintf( sSndNod, "%09s", sNodNo );
  strcpy( sRcvNod, "000000000" );
  strcpy( sDskNo, "AAAAAAAAAAAA" );
  if ( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TxnCnl������" );
    bpErrorLog( trdata, "CbsFDtlToDb:��ȡ�ڵ㡾TxnCnl������!\n" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "��ȡ�ڵ㡾TxnCnl������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  ���ݷ��к�ȡ��������
*/
  ClearStr( sCnlSub  );
  EXEC SQL select CnlSub
             into :sCnlSub
             from CbsBnkInf
            where BrNo=:sBrNo;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog( trdata, "CbsF1052OToDb:��ȡ����������������Ʒ�¼��ų�����������к�:��%s��!\n", sBrNo );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "��ȡ����������������Ʒ�¼��ų���" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
  sprintf( sFName, "%s/%s/%s", getenv("WORKDIR"), Step_Arg1, Step_Arg2 );
  strcpy( sFilNam, Step_Arg2 );
  fp =fopen( sFName, "r" );
  if( fp == NULL ) {
    bpAddResult( TrNode, "CBS999", "�������ļ���" );
    bpErrorLog( trdata, "CbsF1052OToDb:�������ļ���%s��ʧ��!\n", sFName );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "�������ļ���" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    fclose( fp );
    return( -1 );
  }

  iRecNum=0;
  while( !feof( fp ) ) {
/*
**  ����ǰ����ˮ����Ϊ��Ϣ��š�ƾ֤�ύ��
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
**  ������ʼֵ
*/
    strcpy( sBilSts, "P" );
    if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
      bpErrorLog( trdata, "CbsFileToDb:ȡǰ����ˮ�Ŵ��ļ�����%s��!\n", sFName );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "ȡǰ����ˮ�Ŵ��ļ�����%s��!\n", sFName );
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
      sprintf( sRspMsg, "�ļ���%s���ڡ�%d��������!", sFilNam, iRecNum+1 );
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
          bpErrorLog( trdata, "CbsFDtlToDb:�ʺš�%s���¾��ʺŶ��ձ�����!\n", sRcvAct );
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
            if( ( memcmp(sRcvAct+ActNoLen-VchTypLen,"209",VchTypLen)==0 )||( memcmp(sRcvAct+ActNoLen-VchTypLen,"229",VchTypLen)==0 ) ) { /* �����ý��ʺ� */
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
**  ���ݷ��кźͽ���������ȡ���ӹ�Ա��
*/
      if( strcmp( sBilSts, "E") !=0 ) {
        if( sqnGetDumTlr( sBrNo, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
          bpErrorLog( trdata, "CbsF1052OToDb:ȡǰ�õ��ӹ�Ա�Ŵ�%s����%s����%s��!\n", sBrNo, sTxnCnl, sCnlSub );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "ȡǰ�õ��ӹ�Ա�Ŵ�" );
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
      bpErrorLog( trdata, "CbsF1052OToDb:insert��CbsBchJnl������%d��-�ļ���%s��!\n", SQLCODE, sFName );
      bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsBchJnl������" );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      strcpy( sRspMsg, "�������ʧ��" );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
/**
bpErrorLog( trdata, "����-1-����:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", \
sFilNam, sMsgSqn, sTraKnd, sSndBNo, sSndDat, sVchId, sBilSts, sOIFlag, sMsgId, sTxnKnd );
bpErrorLog( trdata, "����-2-����:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", \
sTxnAmt, sTraTm,  sCcyCod, sSvrCod, sCshFlg, sSmrCod, sUsgCod, sRSdFlg, sAccFlg, sTBusTp );
bpErrorLog( trdata, "����-3-����:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", \
sCardFg, sAccKnd, sFeeTyp,sPayFuc, sSOpnBk, sSndNod, sSndAct, sSndNm, sRcvBNo, sROpnBk );
bpErrorLog( trdata, "����-4-����:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", \
sRcvAct, sRcvNm, sSmr, sSecKey, sBrNo, sNodNo, sLogNo, sDskNo, sTxnCnl, sActFlg );
**/
      fclose( fp );
      return( -1 );
    }
/*
**  �����ܱ������ܽ��ṩ�˶Թ���
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
  strcpy( sRspMsg, "���׳ɹ�" );
  etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
  etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
  etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
  bpTraceLog( trdata, "End CbsF1052OToDb.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsMsgFilToDb
  Description       : ����Ϣ�ļ����
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��             
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
**  �к������ļ�
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
**  ����ҵ��ͨ��Ϣ
*/
    char   sCcyCod[CcyCodLen+1];
/*
**  ϵͳ������Ϣ
*/
    char   sCodTyp[CodTypLen+1];
    char   sCode[CodeLen+1];
    char   sCodSmr[CodSmrLen+1];
/*
**  ϵͳ����Ϣ
*/
    char   sSysNam[SysNamLen+1];
    char   sIdType[IdTypeLen+1];
/*
**  ����������Ϣ
*/
    char   sCityNm[CityNmLen+1];
    char   sUpgCod[UpgCodLen+1];
    char   sCityFg[CityFgLen+1];
/*
**  ������Ϣ
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin CbsMsgFilToDb.\n" );
/*
**  ��������������
*/
  ClearStr( sMsgTyp );
  ClearStr( sRspCod );
  ClearStr( sRspMsg );

  if( Step_Args_Num != 2 ) {
    bpAddResult( TrNode, _SYSTEM_ERR, "����������" );
    bpErrorLog( trdata, "CbsMsgFilToDb: ����������!" );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    strcpy( sRspMsg, "����������" );
    etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
    etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
    etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
    return( -1 );
  }
/*
**  ��ʼ������
*/
  ClearStr( sMsgFilLst );
  sprintf( sMsgFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg1 );
  mlst_fp =fopen( sMsgFilLst, "r" );
  if( mlst_fp == NULL ) {
    fclose( mlst_fp );
    bpAddResult( TrNode, "CBS999", "����Ϣ�б��ļ���" );
    bpErrorLog( trdata, "CbsMsgFilToDb:����Ϣ�б��ļ���%s��ʧ��!\n", sMsgFilLst );
    strcpy( sMsgTyp, "E" );
    strcpy( sRspCod, "CBS999" );
    sprintf( sRspMsg, "����Ϣ�б��ļ���%s����", Step_Arg1 );
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
      bpErrorLog( trdata, "CbsMsgFilToDb:�����ļ��б������!\n" );
      break;
    }
    bpErrorLog( trdata, "CbsMsgFilToDb:���ڴ����ļ���%s��!\n", sFilNam );
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
      bpAddResult( TrNode, "CBS999", "����Ϣ�ļ���" );
      bpErrorLog( trdata, "CbsMsgFilToDb:����Ϣ�ļ���%s��ʧ��!\n", sMsgFil );
      fclose( mlst_fp );
      fclose( msg_fp );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "����Ϣ�ļ���%s����", sMsgFil );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
      return( -1 );
    }
    iFSize=hfgetsize( msg_fp );
    if( iFSize != atol( sFSize ) ) {
      bpErrorLog( trdata, "CbsMsgFilToDb:��Ϣ�ļ���%s��������!\n", sMsgFil );
      fclose( mlst_fp );
      fclose( msg_fp );
      strcpy( sMsgTyp, "E" );
      strcpy( sRspCod, "CBS999" );
      sprintf( sRspMsg, "��Ϣ�ļ���%s��������", sMsgFil );
      etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
      etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
      etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
      return( -1 );
    }
    ClearStr( sFlag );
    strcpy( sFlag, "0" );
/*
**  ���ݲ�ͬ��ҵ�����ͷֱ���
*/
    if( strcmp( sTxnKnd, "BANKCD" ) == 0 ) {   /*�к��ļ�*/
      EXEC SQL delete from CbsBankCd;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:�������ݱ�CbsBankCd������%d��!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "�������ݱ�CbsBankCd������%d��", SQLCODE );
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
bpErrorLog( trdata, "��������:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", \
            sBankNo,sSwftNo,sSysId,sCityCd,sBlArea,sDirBNo,sBnkTyp,sBankNm,sSimBNm,sSecBNo,sAdr,sPosCod,sTelNo,sFaxNo,sEMail,sComman,sDirFlg,sCnpsFg,sEffDat,sIvdDat,sReMark );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert��CbsBankCd������%d��-�ļ���%s��!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsBankCd������" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert��CbsBankCd������" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "BTXNCD" ) == 0 ) {   /* ����ҵ��ͨ��Ϣ */
      EXEC SQL delete from CbsBTxnCd;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:�������ݱ�CbsBTxnCd������%d��!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "�������ݱ�CbsBTxnCd������%d��", SQLCODE );
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
bpErrorLog( trdata, "��������:��%s����%s����%s����%s����%s��!\n", sBankNo,sTxnKnd, sCcyCod, sEffDat,sIvdDat );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert��CbsBTxnCd������%d��-�ļ���%s��!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsBTxnCd������" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert��CbsBTxnCd������" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "CODECD" ) == 0 ) {   /* ϵͳ������Ϣ */
      EXEC SQL delete from CbsCodeCd where CodTyp!='TXNKND';
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:�������ݱ�CbsCodeCd������%d��!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "�������ݱ�CbsCodeCd������%d��", SQLCODE );
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
bpErrorLog( trdata, "��������:��%s����%s����%s����%s����%s��!\n", sCodTyp,sCode, sCodSmr, sEffDat,sIvdDat );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert��CbsCodeCd������%d��-�ļ���%s��!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsCodeCd������" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert��CbsCodeCd������" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "SYIDCD" ) == 0 ) {   /* ϵͳ����Ϣ */
      EXEC SQL delete from CbsSyIdCd;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:�������ݱ�CbsSyIdCd������%d��!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "�������ݱ�CbsSyIdCd������%d��", SQLCODE );
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
          bpErrorLog( trdata, "��������:��%s����%s����%s����%s����%s����%s��!\n", sSysId, sSysNam, sBlArea, sIdType, sEffDat,sIvdDat );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert��CbsSyIdCd������%d��-�ļ���%s��!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsSyIdCd������" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert��CbsSyIdCd������" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "AREACD" ) == 0 ) {   /* ����������Ϣ */
      EXEC SQL delete from CbsAreaCd;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:�������ݱ�CbsAreaCd������%d��!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "�������ݱ�CbsAreaCd������%d��", SQLCODE );
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
bpErrorLog( trdata, "��������:��%s����%s����%s����%s��!\n", sCityCd, sCityNm, sUpgCod, sCityFg );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert��CbsAreaCd������%d��-�ļ���%s��!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsAreaCd������" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert��CbsAreaCd������" );
          etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
          etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
          etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
          return( -1 );
        }
      }
    }
    if( strcmp( sTxnKnd, "ORGACD" ) == 0 ) {   /* ������Ϣ */
      EXEC SQL delete from CbsCenOrg;
      if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
        bpErrorLog( trdata, "CbsMsgFilToDb:�������ݱ�CbsCenOrg������%d��!\n", SQLCODE );
        fclose( mlst_fp );
        fclose( msg_fp );
        strcpy( sMsgTyp, "E" );
        strcpy( sRspCod, "CBS999" );
        sprintf( sRspMsg, "�������ݱ�CbsCenOrg������%d��", SQLCODE );
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
bpErrorLog( trdata, "��������:��%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s����%s��!\n", sOrgCod, sOrgNam, sCityCd, sTBusTp, sTxnKnd, sCcyCod, sBankNo, sOrgAct, sOrgANm, sTelNo, sComman, sEffDat, sIvdDat );
          bpErrorLog( trdata, "CbsMsgFilToDb:insert��CbsCenOrg������%d��-�ļ���%s��!\n", SQLCODE, sFilNam );
          bpAddResult( TrNode, _DB_OPER_ERR, "insert��CbsCenOrg������" );
          fclose( msg_fp );
          fclose( mlst_fp );
          strcpy( sMsgTyp, "E" );
          strcpy( sRspCod, "CBS999" );
          strcpy( sRspMsg, "insert��CbsCenOrg������" );
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
  strcpy( sRspMsg, "���׳ɹ�" );
  etfAddOrRepNode( TrNode, "MsgTyp", sMsgTyp, MsgTypLen );
  etfAddOrRepNode( TrNode, "RspCod", sRspCod, RspCodLen );
  etfAddOrRepNode( TrNode, "RspMsg", sRspMsg, RspMsgLen );
  bpTraceLog( trdata, "End CbsMsgFilToDb.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsDtlFilChk
  Description       : ��ϸ�ļ��˶�
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��( Ϊ��֤����ȫ�棬���κ�һ���ļ����Ϸ������˳� )
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
    char   sTBilNo[TBilNoLen+1];   /*˰Ʊ����*/
    char   sTaxNo[TaxNoLen+1];     /*��˰�˱���*/
    char   sTaxer[TaxerLen+1];     /*��˰������*/
    char   sTaxLvl[TaxLvlLen+1];   /*Ԥ�㼶��*/
    char   sTSubCd[TSubCdLen+1];   /*Ԥ���Ŀ*/
    char   sTOrgCd[TOrgCdLen+1];   /*���ջ��ش���*/
    char   sTActDt[TActDtLen+1];   /*˰Ʊ�޽�����*/
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin CbsDtlFilChk.\n" );
/*
**  ��������������
*/
  if( Step_Args_Num != 5 ) {
    bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ����������" );
    bpErrorLog( trdata, "CbsDtlFilChk: ����������!" );
    return( -1 );
  }
/*
**  ���ֳ�����ֵ
*/
  ClearStr( sSucFlg );
  ClearStr( sBrNo   );
  ClearStr( sActDat );
  ClearStr( sNodNo  );
  ClearStr( sRptDir );
  ClearStr( sChkFil );
  strcpy( sSucFlg, "Y" );
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾BrNo������" );
    bpErrorLog( trdata, "CbsDtlFilChk:��ȡ�ڵ㡾BrNo������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾ActDat������" );
    bpErrorLog( trdata, "CbsDtlFilChk:��ȡ�ڵ㡾ActDat������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾NodNo������" );
    bpErrorLog( trdata, "CbsDtlFilChk:��ȡ�ڵ㡾NodNo������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "RptDir", sRptDir, FNameLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾RptDir������" );
    bpErrorLog( trdata, "CbsDtlFilChk:��ȡ�ڵ㡾RptDir������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "IcsDtlDir", sDtlDir, FNameLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾DtlDir������" );
    bpErrorLog( trdata, "CbsDtlFilChk:��ȡ�ڵ㡾DtlDir������!\n" );
    return( -1 );
  }
/*
**  ���ɶ��ʽ���ļ���ͷ
*/
  sprintf( sChkFil, "%s/%s", getenv("WORKDIR"), Step_Arg5 );
  chk_fp =fopen( sChkFil, "w" );
  if( chk_fp == NULL ) {
    fclose( chk_fp );
    bpAddResult( TrNode, "CBS999", "�򿪶��ʽ���ļ���" );
    bpErrorLog( trdata, "CbsDtlFilChk:�򿪶����ļ������%s��ʧ��!\n", sChkFil );
    return( -1 );
  }
  fprintf( chk_fp, "[1]:RptHead=���ʲ����\n" );
  fprintf( chk_fp, "[2]:TxnKnd=%s|ClrDat=%s|\n", Step_Arg3, Step_Arg4 );
/*
**  ��ʼ������
*/
  ClearStr( sDtlFilLst );
  sprintf( sDtlFilLst, "%s/%s", getenv("WORKDIR"), Step_Arg1 );
  dlst_fp =fopen( sDtlFilLst, "r" );
  if( dlst_fp == NULL ) {
    fclose( chk_fp );
    fclose( dlst_fp );
    bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: �򿪶����б��ļ���" );
    bpErrorLog( trdata, "CbsDtlFilChk:�򿪶����б��ļ���%s��ʧ��!\n", sDtlFilLst );
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
      bpErrorLog( trdata, "CbsDtlFilChk:�����ļ��б������!\n" );
      break;
    }
    bpErrorLog( trdata, "CbsDtlFilChk:���ڴ����ļ���%s��!\n", sFilNam );
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
**  ����ļ�������
*/
    sprintf( sDtl8583Fil, "%s/%s/%s", getenv("WORKDIR"), sDtlDir, sFilNam );
    sprintf( sDtlFil, "%s%s", sDtl8583Fil, ".dat" );
    iFSize=0;
    dtl_fp =fopen( sDtl8583Fil, "r" );
    if( dtl_fp == NULL ) {
      fclose( chk_fp );
      fclose( dlst_fp );
      fclose( dtl_fp );
      bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: �򿪶����ļ���" );
      bpErrorLog( trdata, "CbsDtlFilChk:�������ļ���%s��ʧ��!\n", sDtlFil );
      return( -1 );
    }
    iFSize=hfgetsize( dtl_fp );
    if( iFSize != atol( sFSize ) ) {
      fclose( chk_fp );
      fclose( dlst_fp );
      fclose( dtl_fp );
      bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: �����ļ�������" );
      bpErrorLog( trdata, "CbsDtlFilChk:�����ļ���%s��������!\n", sDtlFil );
      return( -1 );
    }
/*
**  �������ļ�8583ת��Ϊ��ͨ�ļ�
*/
    ret=CbsFilChg( "2", sDtl8583Fil, sDtlFil );
    if( ret!=0 ) {
      fclose( chk_fp );
      fclose( dtl_fp );
      fclose( dlst_fp );
      bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: �����ļ�ת���쳣" );
      bpErrorLog( trdata, "CbsDtlFilChk:�����ļ���%s��ת���쳣!\n", sDtl8583Fil );
      return( -1 );
    }
/*
**  ��ȡ�����ļ�
*/
    dtl_fp =fopen( sDtlFil, "r" );
    if( dtl_fp == NULL ) {
      fclose( chk_fp );
      fclose( dtl_fp );
      fclose( dlst_fp );
      bpAddResult( TrNode, "CBS999", "�������ļ���" );
      bpErrorLog( trdata, "CbsDtlFilChk:�������ļ���%s��ʧ��!\n", sDtlFil );
      return( -1 );
    }
/*
** ����������ϸ
*/
    while( !feof( dtl_fp ) ) {
      ClearStr( sMsgSqn  ); /*��Ϣ���*/
      ClearStr( sRefMsg  ); /*�ο���Ϣ���*/
      ClearStr( sMsgId   ); /*�������ͱ�ʶ��*/
      ClearStr( sTxnKndDtl  ); /*��������ϸ������*/
      ClearStr( sTxnAmt  ); /*���׽��*/
      ClearStr( sTraTm   ); /*���׷������ں�ʱ��*/
      ClearStr( sClrBNo  ); /*ֱ��������*/
      ClearStr( sTmpDat  ); /*ί������*/
      ClearStr( sSndDat  ); /*ί������*/
      ClearStr( sClrDat  ); /*��������*/
      ClearStr( sQryTyp  ); /*��ѯ֪ͨ�����ʶ*/
      ClearStr( sAreaNo  ); /*������*/
      ClearStr( sCcyCod  ); /*���׻��Ҵ���*/
      ClearStr( sSvrCod  ); /*��������뷽ʽ��*/
      ClearStr( sCenId   ); /*���Ŀͻ���*/
      ClearStr( sCusId   ); /*��ҵ�ͻ���*/
      ClearStr( sCenTm   ); /*���Ľ�����������ʱ��*/
      ClearStr( sCenLog  ); /*���Ľ��������*/
      ClearStr( sThdTm   ); /*ҵ������������ʱ��*/
      ClearStr( sThdLog  ); /*ҵ������ˮ��*/
      ClearStr( sRtnCod  ); /*������*/
      ClearStr( sCshFlg  ); /*�ֽ�ת�˱�ʶ*/
      ClearStr( sSmrCod  ); /*ժҪ����*/
      ClearStr( sUsgCod  ); /*�ʽ���;����*/
      ClearStr( sRSdFlg  ); /*�ط���ʶ*/
      ClearStr( sAccFlg  ); /*�Թ���˽��ʶ*/
      ClearStr( sTBusTp  ); /*ҵ������*/
      ClearStr( sCardFg  ); /*���۱�ʶ*/
      ClearStr( sAccKnd  ); /*�����㻧��ʶ*/
      ClearStr( sFeeTyp  ); /*�����ѷ�ʽ*/
      ClearStr( sPayFuc  ); /*֧������*/
      ClearStr( sAuthCd  ); /*��Ȩ��*/
      ClearStr( sPayLvl  ); /*֧�����ȼ�*/
      ClearStr( sOrgId   ); /*ԭ����ҵ��Ψһ��ʶ*/
      ClearStr( sSndBNo  ); /*�������к�*/
      ClearStr( sSOpnBk  ); /*�����˿������к�*/
      ClearStr( sSndNod  ); /*�����������*/
      ClearStr( sSndAct  ); /*�������˺�*/
      ClearStr( sSndNm   ); /*����������*/
      ClearStr( sVchId   ); /*ƾ֤�ύ��*/
      ClearStr( sRcvBNo  ); /*�������к�*/
      ClearStr( sROpnBk  ); /*�����˿������к�*/
      ClearStr( sRcvNod  ); /*�����������*/
      ClearStr( sRcvAct  ); /*�������˺�*/
      ClearStr( sRcvNm   ); /*����������*/
      ClearStr( sAgrNo   ); /*�෽Э���*/
      ClearStr( sSysSts  ); /*ϵͳ����״̬*/
      ClearStr( sCreAmt  ); /*�������*/
      ClearStr( sCreCnt  ); /*��������*/
      ClearStr( sDebAmt  ); /*�跽���*/
      ClearStr( sDebCnt  ); /*�跽����*/
      ClearStr( sCTraKnd ); /*��������*/
      ClearStr( sOSgnId  ); /*�ɵ�½��ʶ*/
      ClearStr( sNSgnId  ); /*�µ�½��ʶ*/
      ClearStr( sSmr     ); /*����ժҪ(300)*/
      ClearStr( sSecKey  ); /*��Ѻ*/
      ClearStr( sTCrpCd  ); /*��ҵ��������*/
      ClearStr( sSvrKnd  ); /*������Ϣ����*/
      ClearStr( sTBilNo  ); /*˰Ʊ����*/
      ClearStr( sTaxNo   ); /*��˰�˱���*/
      ClearStr( sTaxer   ); /*��˰������*/
      ClearStr( sTaxLvl  ); /*Ԥ�㼶��*/
      ClearStr( sTSubCd  ); /*Ԥ���Ŀ*/
      ClearStr( sTOrgCd  ); /*���ջ��ش���*/
      ClearStr( sTActDt  ); /*˰Ʊ�޽�����*/
      ClearStr( sSvrMsg  ); /*������Ϣ����*/
      ClearStr( sSndNm2  ); /*���ӷ���������*/
      ClearStr( sSndAdr  ); /*�����˵�ַ*/
      ClearStr( sRcvNm2  ); /*���ӽ���������*/
      ClearStr( sRcvAdr  ); /*�����˵�ַ*/

      ClearStr( sBilSts  ); /*״̬*/
      ClearStr( sResult );
/*
**  ר�����ڴ�����SIR�����еķǷ��ַ�
*/
      if ( i==1 ) {
        fscanf( dtl_fp, "%[^|]", sMsgSqn );   /*��Ϣ���*/
        i++;
      } else {
        fscanf( dtl_fp, "|\n%[^|]", sMsgSqn );   /*��Ϣ���*/
      }  
      hdelallspace(sMsgSqn);
      if( strlen(sMsgSqn)==0 ) {
        break;
      }
      fscanf( dtl_fp, "|%[^|]", sRefMsg  );   /*�ο���Ϣ���*/
      fscanf( dtl_fp, "|%[^|]", sMsgId   );   /*�������ͱ�ʶ��*/
      fscanf( dtl_fp, "|%[^|]", sTxnKndDtl );   /*��������ϸ��*/
      fscanf( dtl_fp, "|%[^|]", sTxnAmt  );   /*���׽��*/
      fscanf( dtl_fp, "|%[^|]", sTraTm   );   /*���׷������ں�ʱ��*/
      fscanf( dtl_fp, "|%[^|]", sClrBNo  );   /*ֱ��������*/
      fscanf( dtl_fp, "|%[^|]", sTmpDat  );   /*ί������*/
      strncpy( sSndDat, sTmpDat, 8 );         /*ɾ����λ��0*/
      fscanf( dtl_fp, "|%[^|]", sClrDat  );   /*��������*/
      fscanf( dtl_fp, "|%[^|]", sQryTyp  );   /*��ѯ֪ͨ����*/
      fscanf( dtl_fp, "|%[^|]", sAreaNo  );   /*������*/
      fscanf( dtl_fp, "|%[^|]", sCcyCod  );   /*���׻��Ҵ���*/
      fscanf( dtl_fp, "|%[^|]", sSvrCod  );   /*��������뷽ʽ��*/
      fscanf( dtl_fp, "|%[^|]", sCenId   );   /*���Ŀͻ���*/
      fscanf( dtl_fp, "|%[^|]", sCusId   );   /*��ҵ�ͻ���*/
      fscanf( dtl_fp, "|%[^|]", sCenTm   );   /*������������ʱ��*/
      fscanf( dtl_fp, "|%[^|]", sCenLog  );   /*���������*/
      fscanf( dtl_fp, "|%[^|]", sThdTm   );   /*ҵ������������ʱ��*/
      fscanf( dtl_fp, "|%[^|]", sThdLog  );   /*ҵ��������ˮ��*/
      fscanf( dtl_fp, "|%[^|]", sRtnCod  );   /*������*/
      fscanf( dtl_fp, "|%[^|]", sCshFlg  );   /*�ֽ�ת�ʱ�־*/
      fscanf( dtl_fp, "|%[^|]", sSmrCod  );   /*ժҪ����*/
      fscanf( dtl_fp, "|%[^|]", sUsgCod  );   /*�ʽ���;����*/
      fscanf( dtl_fp, "|%[^|]", sRSdFlg  );   /*�ط���ʶ*/
      fscanf( dtl_fp, "|%[^|]", sAccFlg  );   /*�Թ���˽��ʶ*/
      fscanf( dtl_fp, "|%[^|]", sTBusTp  );   /*ҵ������*/
      fscanf( dtl_fp, "|%[^|]", sCardFg  );   /*���۱�ʶ*/
      fscanf( dtl_fp, "|%[^|]", sAccKnd  );   /*�����㻧��ʶ*/
      fscanf( dtl_fp, "|%[^|]", sFeeTyp  );   /*�շѷ�ʽ*/
      fscanf( dtl_fp, "|%[^|]", sPayFuc  );   /*֧������*/
      fscanf( dtl_fp, "|%[^|]", sAuthCd  );   /*��Ȩ��*/
      fscanf( dtl_fp, "|%[^|]", sPayLvl  );   /*֧�����ȼ�*/
      fscanf( dtl_fp, "|%[^|]", sOrgId   );   /*ԭ����Ԫ*/
      fscanf( dtl_fp, "|%[^|]", sSndBNo  );   /*�������к�*/
      fscanf( dtl_fp, "|%[^|]", sSOpnBk  );   /*�����˿������к�*/
      fscanf( dtl_fp, "|%[^|]", sSndNod  );   /*�����������*/
      fscanf( dtl_fp, "|%[^|]", sSndAct  );   /*�������˺�*/
      fscanf( dtl_fp, "|%[^|]", sSndNm   );   /*����������*/
      fscanf( dtl_fp, "|%[^|]", sVchId   );   /*ƾ֤�ύ��*/
      fscanf( dtl_fp, "|%[^|]", sRcvBNo  );   /*�������к�*/
      fscanf( dtl_fp, "|%[^|]", sROpnBk  );   /*�����˿������к�*/
      fscanf( dtl_fp, "|%[^|]", sRcvNod  );   /*�����������*/
      fscanf( dtl_fp, "|%[^|]", sRcvAct  );   /*�������˺�*/
      fscanf( dtl_fp, "|%[^|]", sRcvNm   );   /*����������*/
      fscanf( dtl_fp, "|%[^|]", sAgrNo   );   /*Э���*/
      fscanf( dtl_fp, "|%[^|]", sSysSts  );   /*ϵͳ����״̬*/
      fscanf( dtl_fp, "|%[^|]", sCreAmt  );   /*�������*/
      fscanf( dtl_fp, "|%[^|]", sCreCnt  );   /*��������*/
      fscanf( dtl_fp, "|%[^|]", sDebAmt  );   /*�跽���*/
      fscanf( dtl_fp, "|%[^|]", sDebCnt  );   /*�跽����*/
      fscanf( dtl_fp, "|%[^|]", sCTraKnd );   /*��������*/
      fscanf( dtl_fp, "|%[^|]", sOSgnId  );   /*�ɵ�½��ʶ*/
      fscanf( dtl_fp, "|%[^|]", sNSgnId  );   /*�µ�½��ʶ*/
      fscanf( dtl_fp, "|%[^|]", sSmr     );   /*����ժҪ*/
      fscanf( dtl_fp, "|%[^|]", sSecKey  );   /*��Ѻ*/
      fscanf( dtl_fp, "|%[^|]", sTCrpCd  );   /*��ҵ��������*/
      fscanf( dtl_fp, "|%[^|]", sSvrKnd  );   /*������Ϣ����*/
      fscanf( dtl_fp, "|%[^|]", sTBilNo  );   /*˰Ʊ����*/
      fscanf( dtl_fp, "|%[^|]", sTaxNo   );   /*��˰�˱���*/
      fscanf( dtl_fp, "|%[^|]", sTaxer   );   /*��˰������*/
      fscanf( dtl_fp, "|%[^|]", sTaxLvl  );   /*Ԥ�㼶��*/
      fscanf( dtl_fp, "|%[^|]", sTSubCd  );   /*Ԥ���Ŀ*/
      fscanf( dtl_fp, "|%[^|]", sTOrgCd  );   /*���ջ��ش���*/
      fscanf( dtl_fp, "|%[^|]", sTActDt  );   /*˰Ʊ�޽�����*/
/***
      fscanf( dtl_fp, "|%[^|]", sSvrMsg  );   *������Ϣ����*
***/
      fscanf( dtl_fp, "|%[^|]", sSndNm2  );   /*���ӷ���������*/
      fscanf( dtl_fp, "|%[^|]", sSndAdr  );   /*�����˵�ַ*/
      fscanf( dtl_fp, "|%[^|]", sRcvNm2  );   /*���ӽ���������*/
      fscanf( dtl_fp, "|%[^|]", sRcvAdr  );   /*�����˵�ַ*/
/*
**  ���ݲ�ͬ��ҵ�����ͷֱ���
*/
      switch( atoi( sTxnKnd ) ) {
        case 100101:   /* ͬ������� */
        case 100102:   /* ͬ��MT103 */
        case 100103:   /* ͬ��MT202 */
        case 100104:   /* ����MT103 */
        case 100105:   /* ����MT202 */
        case 100106:   /* �ڲ�ת�� */
        case 100201:   /* ����֧�� */
        case 300101:   /* ͬ��������˻� */
        case 300102:   /* ����MT103�˻� */
          if( memcmp(sRcvBNo,BOCSGN,3)==0 ) {   /*�������*/
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
            if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {  /*���ݿ�����쳣*/
              fclose( chk_fp );
              fclose( dtl_fp );
              fclose( dlst_fp );
              bpErrorLog( trdata, "CbsDtlFilChk:��ѯ������ϸ���%d����%s����%s����%s����%s����%s��!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
              bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ��ѯ������ϸ��CbsTxnJnl����" );
              return( -1 );
            }
            if( SQLCODE == SQL_NOTFOUND ) {  /*���ݿ��������ʼ�¼������*/
              bpErrorLog( trdata, "CbsDtlFilChk:��ϸ���в����ڡ�%s����%s����%s����%s����%s��!\n", sTraKnd, sSndBNo, sSndDat, sVchId, sOIFlag );
              ClearStr( sBilSts );
              ClearStr( sTRspCd );
              ClearStr( sLogNo  );
              strcpy( sBilSts, "U" );
              strcpy( sTRspCd, "000000" );
              if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
                fclose( chk_fp );
                fclose( dtl_fp );
                fclose( dlst_fp );
                bpErrorLog( trdata, "CbsDtlFilChk:ȡǰ����ˮ�Ŵ�!\n" );
                bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ȡǰ����ˮ�Ŵ�" );
                return( -1 );
              }
              Exec SQL insert into CbsTxnJnl( TraKnd,SndBNo,SndDat,VchId,OIFlag,BilSts,MsgId,TxnKnd,AccFlg,ClrDat,LogNo,BrNo,ActDat,CcyCod,TxnAmt,TraTm,CenTm,CenLog,SvrCod,TRspCd,CshFlg,SmrCod,UsgCod,RSdFlg,TBusTp,CardFg,AccKnd,FeeTyp,PayFuc,AuthCd,PayLvl,SOpnBk,SndNod,SndAct,SndNm,SndAdr,RcvBNo,ROpnBk,RcvNod,RcvAct,RcvNm,RcvAdr,OrgId,Smr )
                                      values( :sTraKnd,:sSndBNo,:sSndDat,:sVchId,:sOIFlag,:sBilSts,:sMsgId,:sTxnKnd,:sAccFlg,:sClrDat,:sLogNo,:sBrNo,:sActDat,:sCcyCod,:sTxnAmt,:sTraTm,:sCenTm,:sCenLog,:sSvrCod,:sTRspCd,:sCshFlg,:sSmrCod,:sUsgCod,:sRSdFlg,:sTBusTp,:sCardFg,:sAccKnd,:sFeeTyp,:sPayFuc,:sAuthCd,:sPayLvl,:sSOpnBk,:sSndNod,:sSndAct,:sSndNm,:sSndAdr,:sRcvBNo,:sROpnBk,:sRcvNod,:sRcvAct,:sRcvNm,:sRcvAdr,:sOrgId,:sSmr );
              if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {
                fclose( chk_fp );
                fclose( dtl_fp );
                fclose( dlst_fp );
                bpErrorLog( trdata, "CbsDtlFilChk:������ϸ���SQLCODE��%d��,����I��TraKnd��%s��SndBNo��%s��SndDat��%s��VchId��%s��OIFlag��%s��!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId, sOIFlag );
                bpErrorLog( trdata, "CbsDtlFilChk:����II��BilSts��%s��MsgId��%s��TxnKnd��%s��AccFlg��%s��ClrDat��%s��\n",sBilSts,sMsgId,sTxnKnd,sAccFlg,sClrDat );
                bpErrorLog( trdata, "CbsDtlFilChk:����III��LogNo��%s��BrNo��%s��ActDat��%s��CcyCod��%s��TxnAmt��%s��\n",sLogNo,sBrNo,sActDat,sCcyCod,sTxnAmt );
                bpErrorLog( trdata, "CbsDtlFilChk:����IV��TraTm��%s��CenTm��%s��CenLog��%s��SvrCod��%s��TRspCd��%s��\n",sTraTm,sCenTm,sCenLog,sSvrCod,sTRspCd );
                bpErrorLog( trdata, "CbsDtlFilChk:����V��CshFlg��%s��SmrCod��%s��UsgCod��%s��RSdFlg��%s��TBusTp��%s��\n",sCshFlg,sSmrCod,sUsgCod,sRSdFlg,sTBusTp );
                bpErrorLog( trdata, "CbsDtlFilChk:����VI��CardFg��%s��AccKnd��%s��FeeTyp��%s��PayFuc��%s��AuthCd��%s��\n",sCardFg,sAccKnd,sFeeTyp,sPayFuc,sAuthCd );
                bpErrorLog( trdata, "CbsDtlFilChk:����VII��PayLvl��%s��SOpnBk��%s��SndNod��%s��SndAct��%s��SndNm��%s��\n",sPayLvl,sSOpnBk,sSndNod,sSndAct,sSndNm );
                bpErrorLog( trdata, "CbsDtlFilChk:����VIII��SndAdr��%s��RcvBNo��%s��ROpnBk��%s��RcvNod��%s��RcvAct��%s��\n",sSndAdr,sRcvBNo,sROpnBk,sRcvNod,sRcvAct );
                bpErrorLog( trdata, "CbsDtlFilChk:����IX��RcvNm��%s��RcvAdr��%s��OrgId��%s��Smr��%s��!\n",sRcvNm,sRcvAdr,sOrgId,sSmr );
                bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ������ϸ��CbsTxnJnl����" );
                return( -1 );
              }
              strcpy( sResult, "�����У������ޣ��Ѳ���" );
              fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
              strcpy( sSucFlg, "N" );
            }
          }
          if( memcmp(sSndBNo,BOCSGN,3)==0 ) {   /*�������*/
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
            if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {  /*���ݿ�����쳣*/
              fclose( chk_fp );
              fclose( dtl_fp );
              fclose( dlst_fp );
              bpErrorLog( trdata, "CbsDtlFilChk:��ѯ������ϸ���%d����%s����%s����%s����%s����%s��!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
              bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ��ѯ������ϸ��CbsTxnJnl����" );
              return( -1 );
            }
            if( SQLCODE == SQL_NOTFOUND ) {  /*���ݿ��������ʼ�¼���������������²�Ӧ����*/
              bpErrorLog( trdata, "CbsDtlFilChk:ȱ��������ϸ��%s����%s����%s����%s����%s��!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
              strcpy( sResult, "�����У�������" );
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
                bpErrorLog( trdata, "CbsDtlFilChk:�޸�������ϸ״̬��%s����%s����%s����%s����%s��!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
                strcpy( sResult, "���ĳɹ��������쳣" );
                fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                  sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
                strcpy( sSucFlg, "N" );
              }
            }
          }
          break;
        case 100301:   /* ʵʱ�ۿ� */
          if( memcmp(sRcvBNo,BOCSGN,3)==0 ) {   /*�������*/
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
            if( SQLCODE == SQL_NOTFOUND ) {  /*���ݿ��������ʼ�¼������*/
              strcpy( sResult, "�����У�������" );
              fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
              strcpy( sSucFlg, "N" );
            } else {
              if( SQLCODE == SQL_SUCCESS ) {  /*���ݿ��м�¼*/
                if( ( strcmp( sBilSts, "Z" )!=0 ) && ( strcmp( sBilSts, "S" )!=0 ) ) {
                  bpErrorLog( trdata, "CbsDtlFilChk:���ĳɹ��������쳣��%d����%s����%s����%s����%s����%s��!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId, sBilSts );
                  strcpy( sResult, "���ĳɹ��������쳣" );
                  fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                    sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
                  strcpy( sSucFlg, "N" );
                }
              } else {
                fclose( chk_fp );
                fclose( dtl_fp );
                fclose( dlst_fp );
                bpErrorLog( trdata, "CbsDtlFilChk:��ѯʵʱ��ϸ���%d����%s����%s����%s����%s����%s��!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
                bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ��ѯʵʱ��ϸ��CbsBchJnl����" );
                return( -1 );
              }
            }
          }
          if( memcmp(sSndBNo,BOCSGN,3)==0 ) {   /*�������*/
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
            if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {  /*���ݿ�����쳣*/
              fclose( chk_fp );
              fclose( dtl_fp );
              fclose( dlst_fp );
              bpErrorLog( trdata, "CbsDtlFilChk:��ѯ������ϸ���%d����%s����%s����%s����%s����%s��!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
              bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ��ѯ������ϸ��CbsTxnJnl����" );
              return( -1 );
            }
            if( SQLCODE == SQL_NOTFOUND ) {  /*���ݿ��������ʼ�¼���������������²�Ӧ����*/
              bpErrorLog( trdata, "CbsDtlFilChk:ȱ��������ϸ��%s����%s����%s����%s����%s��!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
              strcpy( sResult, "�����У�������" );
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
                bpErrorLog( trdata, "CbsDtlFilChk:�޸�������ϸ״̬��%s����%s����%s����%s����%s��!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
                strcpy( sResult, "���ĳɹ��������쳣" );
                fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                  sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
                strcpy( sSucFlg, "N" );
              }
            }
          }
          break;
        case 105101:   /* �������� */
        case 105102:   /* ���ڴ��� */
        case 105201:   /* ���ڽ�� */
          if( memcmp(sRcvBNo,BOCSGN,3)==0 ) {   /*�������*/
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
            if( SQLCODE == SQL_NOTFOUND ) {  /*���ݿ��������ʼ�¼������*/
              strcpy( sResult, "�����У�������" );
              fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
              strcpy( sSucFlg, "N" );
            } else {
              if( SQLCODE == SQL_SUCCESS ) {  /*���ݿ��м�¼*/
                if( ( strcmp( sBilSts, "Z" )!=0 ) && ( strcmp( sBilSts, "S" )!=0 ) ) {
                  strcpy( sResult, "���ĳɹ��������쳣" );
                  fprintf( chk_fp, "[3]:OIFlag=%s|SndDat=%s|VchId=%s|SndBNo=%s|SndAct=%s|SndNm=%s|TxnAmt=%s|Result=%s|ROpnBk=%s|RcvAct=%s|RcvNm=%s|Smr=%s\n", \
                                    sOIFlag,sSndDat,sVchId,sSndBNo,sSndAct,sSndNm,sTxnAmt,sResult,sROpnBk,sRcvAct,sRcvNm,sSmr );
                  strcpy( sSucFlg, "N" );
                }
              } else {
                fclose( chk_fp );
                fclose( dtl_fp );
                fclose( dlst_fp );
                bpErrorLog( trdata, "CbsDtlFilChk:��ѯ������ϸ���%d����%s����%s����%s����%s����%s��!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
                bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ��ѯ������ϸ��CbsBchJnl����" );
                return( -1 );
              }
            }
          }
          if( memcmp(sSndBNo,BOCSGN,3)==0 ) {   /*�������*/
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
            if( ( SQLCODE != SQL_SUCCESS ) && ( SQLCODE != SQL_NOTFOUND) ) {  /*���ݿ�����쳣*/
              fclose( chk_fp );
              fclose( dtl_fp );
              fclose( dlst_fp );
              bpErrorLog( trdata, "CbsDtlFilChk:��ѯ������ϸ���%d����%s����%s����%s����%s����%s��!\n", SQLCODE, sTraKnd, sSndBNo, sSndDat, sVchId );
              bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ��ѯ������ϸ��CbsTxnJnl����" );
              return( -1 );
            }
            if( SQLCODE == SQL_NOTFOUND ) {  /*���ݿ��������ʼ�¼���������������²�Ӧ����*/
              bpErrorLog( trdata, "CbsDtlFilChk:ȱ��������ϸ��%s����%s����%s����%s����%s��!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
              strcpy( sResult, "�����У�������" );
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
                bpErrorLog( trdata, "CbsDtlFilChk:�޸�������ϸ״̬��%s����%s����%s����%s����%s��!\n", sTraKnd, sSndBNo, sSndDat, sVchId );
                strcpy( sResult, "���ĳɹ��������쳣" );
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
          bpErrorLog( trdata, "CbsDtlFilChk:ҵ�����Ͳ����ڡ�%s��!", sTxnKnd );
          bpAddResult( TrNode, "CBS999", "CbsDtlFilChk: ҵ�����Ͳ�����!" );
          return( -1 );
      } /* End of Switch(sTxnKnd) */
    }
    fclose( dtl_fp );
  }
  fclose( chk_fp );
  fclose( dlst_fp );
  etfAddOrRepNode(TrNode,"SucFlg", sSucFlg, strlen(sSucFlg));
  bpAddResult(TrNode, "000000", "���׳ɹ�" );
  bpTraceLog( trdata, "End CbsDtlFilChk.\n" );
  return (0);
}
/******************************************************************************
  Function          : CbsNetToFee
  Description       : ��������������
  Input             : ETF *TrNode  ������ 
                      ST_TranData* trdata  �����ṹ
                      char* args  ����  
                      DBConHandle* DBHandle  ���ݿ���   
  Output            : �����������˵����     
  Return            : 0--�ɹ� С��0--ʧ��   
  Others            : ����˵��( Ϊ��֤����ȫ�棬���κ�һ���ļ����Ϸ������˳� )
******************************************************************************/
int CbsNetToFee(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  �������
*/
    char   sTxnMon[TxnMonLen+1];
/*
**  ��Сͨ������
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
**  �α����
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
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin CbsNetToFee.\n" );
/*
**  ����������
*/
  if( Step_Args_Num != 1 ) {
    bpAddResult( TrNode, "CBS999", "����������" );
    bpErrorLog( trdata, "CbsNetToFee:����������!\n" );
    return( -1 );
  }
/*
**  ��ȡ���������·�
*/
  ClearStr( sTxnMon );
  strcpy( sTxnMon, Step_Arg1 );
/*
**  ��Сͨ��������ʼ��
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
**  ��������������̺š�������ڡ���Сͨ��Ŀ�����ǰ�ý����룩
*/
  if( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾DskNo������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾DskNo������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾ActDat������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾ActDat������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TTxnCd������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾TTxnCd������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾HTxnCd������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾HTxnCd������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "IsTxn", sIsTxn, IsTxnLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾IsTxn������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾IsTxn������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFlg", sUpdFlg, UpdFlgLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾UpdFlg������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾UpdFlg������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFld", sUpdFld, UpdFldLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾UpdFld������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾UpdFld������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TxnObj������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾TxnObj������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾TxnCnl������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾TxnCnl������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "CnlSub", sCnlSub, CnlSubLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾CnlSub������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾CnlSub������!\n" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾BrNo������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾BrNo������!\n" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpAddResult( TrNode, "CBS999", "��ȡ�ڵ㡾NodNo������" );
    bpErrorLog( trdata, "CbsNetToFee:��ȡ�ڵ㡾NodNo������!\n" );
    return( -1 );
  }

/*
**  ��������������ˮ��
*/
  EXEC SQL DECLARE c_netdtl CURSOR FOR
    select DrAct, DrNam, rtrim(char(count(*))), rtrim(char(sum(bigint(FeeAmt)))), rtrim(char(sum(bigint(PstAmt))))
      from CbsNetDtl
     where BrNo=:sBrNo and substr(DonDat,1,6)=:sTxnMon and FeeFlg='0'
  group by DrAct, DrNam;
  EXEC SQL OPEN c_netdtl;
  if( SQLCODE != SQL_SUCCESS ) {
    bpAddResult(TrNode, "CBS999", "��ѯ��CbsNetDtl���쳣�����α��");
    bpErrorLog(trdata, "CbsNetToFee:��ѯ��CbsNetDtl���쳣�����α��[%d]", SQLCODE);
    return( -1 );
  }
  for( ; ; ) {
/*
**  �α������ʼ��
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
      bpAddResult(TrNode, "CBS999", "��ѯ��CbsNetDtl���쳣��FETCH����" );
      bpErrorLog(trdata, "CbsNetToFee:��ѯ��CbsNetDtl���쳣��FETCH����[%d]", SQLCODE);
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
    sprintf( sTxnNum, "%06s",  sTmpNum );
    sprintf( sFeeAmt, "%015s", sTmpFee );
    sprintf( sPstAmt, "%015s", sTmpPst );
/*
**  ���ݷ��кźͽ���������ȡ���ӹ�Ա��
*/
    if( sqnGetDumTlr( sBrNo, sTxnCnl, sCnlSub, sTlrId ) < 0 ) {
      bpAddResult(TrNode, "CBS999", "ȡ���ӹ�Ա�ų���" );
      bpErrorLog( trdata, "CbsNetToFee:ȡ���ӹ�Ա�ų�������BrNo��%s��TxnCnl��%s��CnlSub��%s��", sBrNo, sTxnCnl, sCnlSub );
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
    if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
      bpAddResult(TrNode, "CBS999", "ȡǰ����ˮ�ų���" );
      bpErrorLog(trdata, "CbsNetToFee:ȡǰ����ˮ�ų���" );
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
    EXEC SQL insert into CbsNetFee( LogNo,DskNo,ActDat,TlrId,TTxnCd,HTxnCd,IsTxn,TxnCnl,CnlSub,TxnObj,UpdFlg,UpdFld,BrNo,NodNo,TxnMon,DrAct,DrNam,TxnNum,FeeAmt,PstAmt )
                            values( :sLogNo,:sDskNo,:sActDat,:sTlrId,:sTTxnCd,:sHTxnCd,:sIsTxn,:sTxnCnl,:sCnlSub,:sTxnObj,:sUpdFlg,:sUpdFld,:sBrNo,:sNodNo,:sTxnMon,:sDrAct,:sDrNam,:sTxnNum,:sFeeAmt,:sPstAmt );
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, "CBS999", "INSERT��CbsNetFee���쳣" );
      bpErrorLog( trdata, "CbsNetToFee:INSERT��CbsNetFee���쳣��%d��-��������-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sLogNo,sDskNo,sActDat,sTlrId,sIsTxn,sTxnCnl,sCnlSub,sTxnObj,sUpdFlg,sUpdFld,sBrNo,sTxnMon,sDrAct,sDrNam,sTxnNum,sFeeAmt,sPstAmt );
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
    iCount++;
/*
**  �޸�������ˮ��״̬Ϊ�Ѵ���
    EXEC SQL update CbsNetDtl set FeeFlg='1' where BrNo=:sBrNo and substr(DonDat,1,6)=:sTxnMon;
    if( SQLCODE != SQL_SUCCESS ) {
      bpAddResult(TrNode, "CBS999", "Update��CbsNetDtl���쳣" );
      bpErrorLog( trdata, "CbsNetToFee:Update��CbsNetDtl���쳣��%d����%s��",SQLCODE,sTxnMon );
      EXEC SQL CLOSE c_netdtl;
      return( -1 );
    }
*/
  }
  sprintf( sOrnCnt,"%8d", iCount );
  EXEC SQL CLOSE c_netdtl;
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
  bpAddResult(TrNode, "000000", "����������ˮ���" );
  bpTraceLog( trdata, "End CbsNetToFee.\n" );
  return (0);
}
