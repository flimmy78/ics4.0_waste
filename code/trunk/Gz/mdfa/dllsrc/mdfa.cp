/******************************************************************************       
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.            
                                                                                      
  File name   : mdf.cp
  Author      : Jamez
  Version     : 2.0  
  Date        : 2009.02.03  
  Description : MDF ������ҽ��ϵͳԭ�Ӻ���
  History     :


  No.  Date    Author    Modification                 
  ===  ==========  ========  ============================

******************************************************************************/
#include <sql.h>
#include "himdf.h"
#include "hionline.h"
#include "hidatabase.h"
#include "hibusmsg.h"
#include "hibppubdef.h"
#include "hipex.h"
#define ClearStr(str) memset(str,'\0',sizeof(str))
/******************************************************************************
  Function        : MdfCrtJnl
  Description     : ����POS������ϸ������������
  Calls           : �����������õĺ����嵥
  Called By       : ���ñ������ĺ����嵥
  Table Accessed  : MDFYHYSMX PclCusAgr MDFTXNJNL
  Table Updated    : MDFYHYSMX
  Input           : ETF *TrNode  ������
                    ST_TranData* trdata  �����ṹ
                    char* args  ����
                    DBConHandle* DBHandle  ���ݿ���
  Output          : �����������˵��
  Return          : 0--�ɹ� С��0--ʧ��
  Others          : ����˵��
******************************************************************************/
int MdfCrtJnl(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  �������
*/
    char   sYSPC[YSPCLen+1];
    char   sBokNum[BokNumLen+1];
    char   sJYSJ[JYSJLen+1];
/*
**  ��Сͨ������
*/
    char   sTTxnCd[TTxnCdLen+1];
    char   sTxnCod[TxnCodLen+1];
    char   sHTxnCd[HTxnCdLen+1];
    char   sActDat[ActDatLen+1];
    char   sNodNo[NodNoLen+1];
    char   sBrNo[BrNoLen+1];
    char   sDskNo[DskNoLen+1];
    char   sTxnObj[TxnObjLen+1];
    char   sTxnCnl[TxnCnlLen+1];
    char   sIsTxn[IsTxnLen+1];
    char   sUpdFlg[UpdFlgLen+1];
    char   sUpdFld[UpdFldLen+1];
    char   sTlrId[TlrIdLen+1];
/*
**  �α�һ���������������¼��
*/
    char   sYSLSH[YSLSHLen+1];
    char   sDYSBLSH[YSLSHLen+1];
    char   sKDM[KDMLen+1];
    char   sJE[AmtLen+1];
    char   sBokAmt[AmtLen+1];
    char   sYSMXZT[YSMXZTLen+1];
    char   sSJZT[SJZTLen+1];
    char   sOJE[AmtLen+1];
/*
**  �α�һ����������۷Ѽ�¼��
*/
    char   sLogNo[LogNoLen+1];
    char   sDate[DateLen+1];
    char   sSeqNo[SeqNoLen+1];
    char   sTBSDM[TBSDMLen+1];
    char   sSBBM[SBBMLen+1];
    char   sTZNY[TZNYLen+1];
    char   sCdFlag[CdFlagLen+1];
    char   sTmpAmt[AmtLen+1];
    char   sTxnAmt[AmtLen+1];
    char   sYHZH[YHZHLen+1];
    char   sYHHM[YHHNLen+1];
/*
**  �������
*/
    char   sOrnCnt[OrnCntLen+1];
  EXEC SQL END DECLARE SECTION;
    long   iCount=0;
/*
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin MdfCrtJnl.\n" );
/*
**  ����������
*/
  if( Step_Args_Num != 2 ) {
    bpErrorLog( trdata, "MdfCrtJnl:����������!\n" );
    bpAddResult( TrNode, "MDF999", "����������" );
    return( -1 );
  }
/*
**  ��Сͨ��������ʼ��
*/
  ClearStr( sTTxnCd );
  ClearStr( sTxnCod );
  ClearStr( sHTxnCd );
  ClearStr( sActDat );
  ClearStr( sNodNo  );
  ClearStr( sBrNo   );
  ClearStr( sDskNo  );
  ClearStr( sTxnObj );
  ClearStr( sTxnCnl );
  ClearStr( sIsTxn  );
  ClearStr( sUpdFlg );
  ClearStr( sUpdFld );
  ClearStr( sTlrId  );
/*
**  ��������������̺š�������ڡ���Сͨ��Ŀ����������������ڡ�ǰ�ý����룩
*/
  if( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾TTxnCd������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TTxnCd������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCod", sTxnCod, TxnCodLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾TxnCod������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TxnCod������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾HTxnCd������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾HTxnCd������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾ActDat������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾ActDat������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾NodNo������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾NodNo������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾BrNo������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾BrNo������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾DskNo������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾DskNo������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾TxnObj������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TxnObj������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾TxnCnl������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TxnCnl������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "IsTxn", sIsTxn, IsTxnLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾IsTxn������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾IsTxn������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFlg", sUpdFlg, UpdFlgLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾UpdFlg������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾UpdFlg������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFld", sUpdFld, UpdFldLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾UpdFld������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾UpdFld������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TlrId", sTlrId, TlrIdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:��ȡ�ڵ㡾TlrId������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TlrId������" );
    return( -1 );
  }
/*
**  ��ȡӦ�����Σ�����
*/
  ClearStr( sYSPC );
  ClearStr( sJYSJ );
  strcpy( sYSPC, Step_Arg1 );
  strcpy( sBokNum, Step_Arg2 );
  hgetdatetime( sJYSJ );
/* 
**  ������ȡ��ˮ��
*/
  ClearStr( sLogNo );
  ClearStr( sDate  );
  ClearStr( sSeqNo );
  if( sqnGetLogNo( sLogNo, atol(sBokNum) ) < 0 ) {
    bpErrorLog(trdata, "MdfCrtJnl:ȡǰ����ˮ�ų���" );
    bpAddResult(TrNode, "MDF999", "ȡǰ����ˮ�ų���" );
    return( -1 );
  }
  memcpy( sDate, sLogNo, DateLen );
  memcpy( sSeqNo, sLogNo+DateLen, SeqNoLen );
  bpErrorLog(trdata, "MdfCrtJnl:1.ȡǰ����ˮ�š�%s����%s����%s��", sLogNo,sDate,sSeqNo);
/*
**  �ȴ�������ļ�¼
*/
  bpTraceLog( trdata, "MdfCrtJnl:��ʼ���������¼.\n" );
  EXEC SQL DECLARE c_ysmx1 CURSOR FOR
      select YSLSH, DYSBLSH, KDM, JE
        from MDFYHYSMX
       where YSPC=:sYSPC
          and YSMXZT='U'
          and CdFlag='C';
  EXEC SQL OPEN c_ysmx1;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog(trdata, "MdfCrtJnl:��ѯ��MDFYHYSMX���쳣���򿪳����α�c_ysmx1��[%d]", SQLCODE);
    bpAddResult(TrNode, "MDF999", "��ѯ��MDFYHYSMX���쳣���򿪳����α�c_ysmx1��" );
    return( -1 );
  }
  for( ; ; ) {
    ClearStr( sYSLSH   );
    ClearStr( sDYSBLSH );
    ClearStr( sKDM     );
    ClearStr( sJE      );
    ClearStr( sYSMXZT  );
    ClearStr( sSJZT    );
    ClearStr( sOJE     );
    EXEC SQL FETCH c_ysmx1 INTO :sYSLSH, :sDYSBLSH, :sKDM, :sJE;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfCrtJnl:��ѯ��MDFYHYSMX���쳣��FETCH����[%d]", SQLCODE );
      bpAddResult( TrNode, "MDF999", "��ѯ��MDFYHYSMX���쳣��FETCH����" );
      EXEC SQL CLOSE c_ysmx1;
      return( -1 );
    }
    hdelbothspace( sYSLSH );
    hdelbothspace( sDYSBLSH );
    EXEC SQL select YSMXZT, SJZT, JE
               into :sYSMXZT, :sSJZT, :sOJE
               from MDFYHYSMX
              where SBLSH=:sDYSBLSH
                and KDM=:sKDM
                and CdFlag='D';
    if( ( SQLCODE != SQL_SUCCESS )&&( SQLCODE != SQL_NOTFOUND ) ) {
      bpErrorLog( trdata, "MdfCrtJnl:��ѯ��MDFYHYSMX����Ӧ�۷Ѽ�¼�쳣��%s����%s����%d��", sDYSBLSH,sKDM,SQLCODE );
      bpAddResult( TrNode, "MDF999", "��ѯ��MDFYHYSMX����Ӧ�۷Ѽ�¼�쳣" );
      EXEC SQL CLOSE c_ysmx1;
      return( -1 );
    }
    if( SQLCODE == SQL_NOTFOUND ) {
      strcpy( sYSMXZT, "S" );
      strcpy( sSJZT, "0003" );
    } else {
      if ( ( strcmp( sYSMXZT, "F" )==0 ) || ( strcmp( sYSMXZT, "U" )==0 ) ) {
/*
**  ״̬Ϊ����ʧ�ܻ�δ�����
*/
        if( atoi(sJE)>atoi(sOJE) ) {
          strcpy( sYSMXZT, "F" );
          strcpy( sSJZT, "0052" );
        } else {
          ClearStr( sBokAmt );
          sprintf( sBokAmt, "%015d", atoi(sOJE)-atoi(sJE) );
          EXEC SQL update MDFYHYSMX
                      set BokAmt=:sBokAmt
                    where SBLSH=:sDYSBLSH
                      and KDM=:sKDM
                      and CdFlag='D'
                      and YSMXZT=:sYSMXZT;
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "MdfCrtJnl:���±�MDFYHYSMX����������ϸ�쳣��%s����%s����%s����%d����%s��", sDYSBLSH,sKDM,sYSMXZT,SQLCODE,SQLERRMSG );
            bpAddResult( TrNode, "MDF999", "���±�MDFYHYSMX����������ϸ�쳣" );
            EXEC SQL CLOSE c_ysmx1;
            return( -1 );
          }
          strcpy( sYSMXZT, "S" );
          strcpy( sSJZT, "0003" );
        }
      } else {
          if ( strcmp( sYSMXZT, "S" )==0 ) { /*�ѿۿ�*/
            strcpy( sYSMXZT, "F" );
            strcpy( sSJZT, "0051" );
          } else {
/*
**  ��Ϊ����״̬����˵�����ʽ������ڴ������ڹ�̨����ʱ����
*/
            continue;
          }
      }
    }
    EXEC SQL update MDFYHYSMX
                set YSMXZT=:sYSMXZT,SJZT=:sSJZT,JYSJ=:sJYSJ,ZSFS='03',BokDat=:sActDat
              where YSLSH=:sYSLSH
                and KDM=:sKDM
                and CdFlag='C'
                and YSMXZT='U';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog(trdata, "MdfCrtJnl:���±�MDFYHYSMX��������ϸ�쳣��%s����%s����%d����%s��", sYSLSH,sKDM,SQLCODE,SQLERRMSG);
      bpAddResult(TrNode, "MDF999", "���±�MDFYHYSMX��������ϸ�쳣" );
      EXEC SQL CLOSE c_ysmx1;
      return( -1 );
    }
  }
  EXEC SQL CLOSE c_ysmx1;
/*
**  ����������ϸ�����п��Եȴ������¼
*/
  bpTraceLog( trdata, "MdfCrtJnl:��ʼ���ɻ��ܿ۷Ѽ�¼.\n" );
  EXEC SQL DECLARE c_ysmx2 CURSOR FOR
      select TBSDM, rtrim(SBBM), CDFlag, TZNY, rtrim(char(sum(bigint(BokAmt))))
        from MDFYHYSMX
       where YSPC=:sYSPC
         and YSMXZT='U'
         and CdFlag='D'
    group by TBSDM, SBBM, CDFlag, TZNY;
  EXEC SQL OPEN c_ysmx2;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog(trdata, "MdfCrtJnl:��ѯ��MDFYHYSMX���쳣�����α��[%d]", SQLCODE);
    bpAddResult(TrNode, "MDF999", "��ѯ��MDFYHYSMX���쳣�����α��" );
    return( -1 );
  }
  for( ; ; ) {
/*
**  �α������ʼ��
*/
    ClearStr( sTBSDM  );
    ClearStr( sSBBM   );
    ClearStr( sCdFlag );
    ClearStr( sTZNY   );
    ClearStr( sTmpAmt );
    ClearStr( sTxnAmt );
    ClearStr( sYHZH   );
    ClearStr( sYHHM   );
    EXEC SQL FETCH c_ysmx2 INTO :sTBSDM, :sSBBM, :sCdFlag, :sTZNY, :sTmpAmt;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog(trdata, "MdfCrtJnl:��ѯ��MDFYHYSMX���쳣��FETCH����[%d]", SQLCODE);
      bpAddResult(TrNode, "MDF999", "��ѯ��MDFYHYSMX���쳣��FETCH����" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
    sprintf( sTxnAmt,"%015s", sTmpAmt );
/*
**  ��ȡ����ǩԼ�˺š��˻�

    EXEC SQL select YHZH, YHHM
               into :sYHZH, :sYHHM
               from MDFCUSINF
              where TBSDM=:sTBSDM
                and SBBM=:sSBBM;
    if( ( SQLCODE != SQL_SUCCESS )&&( SQLCODE != SQL_NOTFOUND ) ) {
      bpErrorLog(trdata, "MdfCrtJnl:��ȡ�ͻ����ϳ���TBSDM��%s����%s����%d��", sTBSDM,sSBBM,SQLCODE);
      bpAddResult(TrNode, "MDF999", "��ȡ�ͻ����ϳ���" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
*/
/*
    if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
      bpErrorLog(trdata, "MdfCrtJnl:ȡǰ����ˮ�ų���" );
      bpAddResult(TrNode, "MDF999", "ȡǰ����ˮ�ų���" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
*/
/*
**  �Ǽ���ˮ��
*/
    EXEC SQL insert into MDFTXNJNL( LogNo,TTxnCd,TxnCod,HTxnCd,TxnTyp,OIFlag,BusTyp,CrpCod,ActDat,CcyCod,TxnAmt,NodNo,BrNo,TlrId,TTxnSt,TxnSts,HTxnSt,DskNo,TxnObj,TxnCnl,IsTxn,UpdFlg,UpdFld,CdFLag,TBSDM,SBBM,TZNY )
                            values( :sLogNo,:sTTxnCd,:sTxnCod,:sHTxnCd,'N','1','','MDF999999999',:sActDat,'CNY',:sTxnAmt,:sNodNo,:sBrNo,:sTlrId,'U','U','U',:sDskNo,:sTxnObj,:sTxnCnl,:sIsTxn,:sUpdFlg,:sUpdFld,:sCdFlag,:sTBSDM,:sSBBM,:sTZNY );
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfCrtJnl:INSERT��MDFTXNJNL���쳣[%d]", SQLCODE );
      bpErrorLog( trdata, "MdfCrtJnl:INSERT��MDFTXNJNL���쳣[%d]-��������-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sLogNo,sTTxnCd,sTxnCod,sHTxnCd,sActDat,sTxnAmt,sNodNo,sBrNo,sTlrId,sDskNo,sTxnObj,sTxnCnl,sIsTxn,sUpdFlg,sUpdFld,sCdFlag,sTBSDM,sSBBM,sTZNY );
      bpAddResult(TrNode, "MDF999", "INSERT��MDFTXNJNL���쳣" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
    EXEC SQL update MDFYHYSMX set LogNo=:sLogNo, DskNo=:sDskNo, YSMXZT='B' where YSPC=:sYSPC and YSMXZT='U' and TBSDM=:sTBSDM and SBBM=:sSBBM and TZNY=:sTZNY and CdFlag='D';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfCrtJnl:UPDATE��MDFYHYSMX���쳣[%d]-��������-[%s]-[%s]-[%s]-[%s]", SQLCODE,sYSPC,sLogNo,sTBSDM,sSBBM );
      bpAddResult(TrNode, "MDF999", "UPDATE��MDFYHYSMX���쳣" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
    iCount++;
    ClearStr( sLogNo );
    sprintf( sSeqNo,"%08ld", atol(sSeqNo)+1 );
    sprintf( sLogNo,"%s%s", sDate, sSeqNo );
    bpErrorLog(trdata, "MdfCrtJnl:2.ȡǰ����ˮ�š�%s����%s��", sLogNo,sSeqNo);
  }
  sprintf( sOrnCnt,"%d", iCount );
  EXEC SQL CLOSE c_ysmx2;
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
  bpAddResult(TrNode, "000000", "���ݱ�MdfCrtJnl���������" );
  bpTraceLog( trdata, "End MdfCrtJnl.\n" );
  return (0);
}
/******************************************************************************
  Function        : MdfCanProc
  Description     : �������κŴ����Ӧ���εĳ�����¼
  Calls           : �����������õĺ����嵥
  Called By       : ���ñ������ĺ����嵥
  Table Accessed  : MDFYHYSMX 
  Table Updated   : MDFYHYSMX
  Input           : ETF *TrNode  ������
                    ST_TranData* trdata  �����ṹ
                    char* args  ����
                    DBConHandle* DBHandle  ���ݿ���
  Output          : �����������˵��
  Return          : 0--�ɹ� С��0--ʧ��
  Others          : ����˵��
******************************************************************************/
int MdfCanProc(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  �������
*/
    char   sYSPC[YSPCLen+1];
    char   sJYSJ[JYSJLen+1];
    char   sActDat[ActDatLen+1];
/*
**  �α�һ���������������¼��
*/
    char   sYSLSH[YSLSHLen+1];
    char   sDYSBLSH[YSLSHLen+1];
    char   sKDM[KDMLen+1];
    char   sJE[AmtLen+1];
    char   sBokAmt[AmtLen+1];
    char   sYSMXZT[YSMXZTLen+1];
    char   sSJZT[SJZTLen+1];
    char   sOJE[AmtLen+1];
  EXEC SQL END DECLARE SECTION;
/*
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin MdfCanProc.\n" );
/*
**  ����������
*/
  if( Step_Args_Num != 1 ) {
    bpErrorLog( trdata, "MdfCanProc:����������!\n" );
    bpAddResult( TrNode, "MDF999", "����������" );
    return( -1 );
  }
/*
**  ��ȡӦ�����Σ�����
*/
  ClearStr( sYSPC );
  ClearStr( sJYSJ );
  strcpy( sYSPC, Step_Arg1 );
  hgetdatetime( sJYSJ );
	ClearStr( sActDat );
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCanProc:��ȡ�ڵ㡾ActDat������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾ActDat������" );
    return( -1 );
  }
/*
**  ��������ļ�¼
*/
  bpTraceLog( trdata, "MdfCanProc:��ʼ���������¼.\n" );
  EXEC SQL DECLARE cur_ysmx1 CURSOR FOR
      select YSLSH, DYSBLSH, KDM, JE
        from MDFYHYSMX
       where YSPC=:sYSPC
          and YSMXZT='U'
          and CdFlag='C';
  EXEC SQL OPEN cur_ysmx1;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog(trdata, "MdfCanProc:��ѯ��MDFYHYSMX��OPEN�α�cur_ysmx1��%d��YSPC��%s��",SQLCODE,sYSPC);
    bpAddResult(TrNode, "MDF999", "��ѯ��MDFYHYSMX��OPEN�α�cur_ysmx1��" );
    return( -1 );
  }
  for( ; ; ) {
    ClearStr( sYSLSH   );
    ClearStr( sDYSBLSH );
    ClearStr( sKDM     );
    ClearStr( sJE      );
    ClearStr( sYSMXZT  );
    ClearStr( sSJZT    );
    ClearStr( sOJE     );
    EXEC SQL FETCH cur_ysmx1 INTO :sYSLSH, :sDYSBLSH, :sKDM, :sJE;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfCanProc:��ѯ��MDFYHYSMX��FETCH�α�cur_ysmx1��%d��", SQLCODE );
      bpAddResult( TrNode, "MDF999", "��ѯ��MDFYHYSMX��FETCH�α�cur_ysmx1��" );
      EXEC SQL CLOSE cur_ysmx1;
      return( -1 );
    }
    hdelbothspace( sYSLSH );
    hdelbothspace( sDYSBLSH );
    EXEC SQL select YSMXZT, SJZT, JE
               into :sYSMXZT, :sSJZT, :sOJE
               from MDFYHYSMX
              where SBLSH=:sDYSBLSH
                and KDM=:sKDM
                and CdFlag='D';
    if( ( SQLCODE != SQL_SUCCESS )&&( SQLCODE != SQL_NOTFOUND ) ) {
      bpErrorLog( trdata, "MdfCanProc:��ѯ��MDFYHYSMX����Ӧ�۷Ѽ�¼�쳣��%s����%s����%d��", sDYSBLSH,sKDM,SQLCODE );
      bpAddResult( TrNode, "MDF999", "��ѯ��MDFYHYSMX����Ӧ�۷Ѽ�¼�쳣" );
      EXEC SQL CLOSE cur_ysmx1;
      return( -1 );
    }
    if( SQLCODE == SQL_NOTFOUND ) {
      strcpy( sYSMXZT, "S" );
      strcpy( sSJZT, "0003" );
    } else {
      if ( ( strcmp( sYSMXZT, "F" )==0 ) || ( strcmp( sYSMXZT, "U" )==0 ) ) {
/*
**  ״̬Ϊ����ʧ�ܻ�δ�����
*/
        if( atoi(sJE)>atoi(sOJE) ) {
          strcpy( sYSMXZT, "F" );
          strcpy( sSJZT, "0052" );
        } else {
          ClearStr( sBokAmt );
          sprintf( sBokAmt, "%015d", atoi(sOJE)-atoi(sJE) );
          EXEC SQL update MDFYHYSMX
                      set BokAmt=:sBokAmt
                    where SBLSH=:sDYSBLSH
                      and KDM=:sKDM
                      and CdFlag='D'
                      and YSMXZT=:sYSMXZT;
          if( SQLCODE != SQL_SUCCESS ) {
            bpErrorLog( trdata, "MdfCanProc:���±�MDFYHYSMX����������ϸ�쳣��%s����%s����%s����%d����%s��", sDYSBLSH,sKDM,sYSMXZT,SQLCODE,SQLERRMSG );
            bpAddResult( TrNode, "MDF999", "���±�MDFYHYSMX����������ϸ�쳣" );
            EXEC SQL CLOSE cur_ysmx1;
            return( -1 );
          }
          strcpy( sYSMXZT, "S" );
          strcpy( sSJZT, "0003" );
        }
      } else {
          if ( strcmp( sYSMXZT, "S" )==0 ) { /*�ѿۿ�*/
            strcpy( sYSMXZT, "F" );
            strcpy( sSJZT, "0051" );
          } else {
/*
**  ��Ϊ����״̬����˵�����ʽ������ڴ������ڹ�̨����ʱ����
*/
            continue;
          }
      }
    }
    EXEC SQL update MDFYHYSMX
                set YSMXZT=:sYSMXZT,SJZT=:sSJZT,JYSJ=:sJYSJ,ZSFS='03',BokDat=:sActDat
              where YSLSH=:sYSLSH
                and KDM=:sKDM
                and CdFlag='C'
                and YSMXZT='U';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog(trdata, "MdfCanProc:���±�MDFYHYSMX��������ϸ�쳣��%s����%s����%d����%s��", sYSLSH,sKDM,SQLCODE,SQLERRMSG);
      bpAddResult(TrNode, "MDF999", "���±�MDFYHYSMX��������ϸ�쳣" );
      EXEC SQL CLOSE cur_ysmx1;
      return( -1 );
    }
  }
  EXEC SQL CLOSE cur_ysmx1;
  bpAddResult(TrNode, "000000", "MdfCanProc:�������" );
  bpTraceLog( trdata, "End MdfCanProc.\n" );
  return (0);
}
/******************************************************************************
  Function        : MdfBokProc
  Description     : �������κŴ����Ӧ���ε���������
  Calls           : �����������õĺ����嵥
  Called By       : ���ñ������ĺ����嵥
  Table Accessed  : MDFYHYSMX MDFCUSINF
  Table Updated    : MDFYHYSMX
  Input           : ETF *TrNode  ������
                    ST_TranData* trdata  �����ṹ
                    char* args  ����
                    DBConHandle* DBHandle  ���ݿ���
  Output          : �����������˵��
  Return          : 0--�ɹ� С��0--ʧ��
  Others          : ����˵��
******************************************************************************/
int MdfBokProc(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  �������
*/
    char   sYSPC[YSPCLen+1];
    char   sBokNum[BokNumLen+1];
    char   sJYSJ[JYSJLen+1];
/*
**  ��Сͨ������
*/
    char   sTTxnCd[TTxnCdLen+1];
    char   sTxnCod[TxnCodLen+1];
    char   sHTxnCd[HTxnCdLen+1];
    char   sActDat[ActDatLen+1];
    char   sNodNo[NodNoLen+1];
    char   sBrNo[BrNoLen+1];
    char   sDskNo[DskNoLen+1];
    char   sTxnObj[TxnObjLen+1];
    char   sTxnCnl[TxnCnlLen+1];
    char   sIsTxn[IsTxnLen+1];
    char   sUpdFlg[UpdFlgLen+1];
    char   sUpdFld[UpdFldLen+1];
    char   sTlrId[TlrIdLen+1];
/*
**  �α�һ���������������¼��
*/
    char   sYSLSH[YSLSHLen+1];
    char   sDYSBLSH[YSLSHLen+1];
    char   sKDM[KDMLen+1];
    char   sJE[AmtLen+1];
    char   sBokAmt[AmtLen+1];
    char   sYSMXZT[YSMXZTLen+1];
    char   sSJZT[SJZTLen+1];
    char   sOJE[AmtLen+1];
/*
**  �α�һ����������۷Ѽ�¼��
*/
    char   sLogNo[LogNoLen+1];
    char   sDate[DateLen+1];
    char   sSeqNo[SeqNoLen+1];
    char   sTBSDM[TBSDMLen+1];
    char   sSBBM[SBBMLen+1];
    char   sTZNY[TZNYLen+1];
    char   sCdFlag[CdFlagLen+1];
    char   sTmpAmt[AmtLen+1];
    char   sTxnAmt[AmtLen+1];
    char   sYHZH[YHZHLen+1];
    char   sYHHM[YHHNLen+1];
/*
**  �������
*/
    char   sOrnCnt[OrnCntLen+1];
  EXEC SQL END DECLARE SECTION;
    long   iCount=0;
/*
**  ���ø�����Ϣ
*/
  bpTraceLog( trdata, "Begin MdfBokProc.\n" );
/*
**  ����������
*/
  if( Step_Args_Num != 2 ) {
    bpErrorLog( trdata, "MdfBokProc:����������!\n" );
    bpAddResult( TrNode, "MDF999", "����������" );
    return( -1 );
  }
/*
**  ��Сͨ��������ʼ��
*/
  ClearStr( sTTxnCd );
  ClearStr( sTxnCod );
  ClearStr( sHTxnCd );
  ClearStr( sActDat );
  ClearStr( sNodNo  );
  ClearStr( sBrNo   );
  ClearStr( sDskNo  );
  ClearStr( sTxnObj );
  ClearStr( sTxnCnl );
  ClearStr( sIsTxn  );
  ClearStr( sUpdFlg );
  ClearStr( sUpdFld );
  ClearStr( sTlrId  );
/*
**  ��������������̺š�������ڡ���Сͨ��Ŀ����������������ڡ�ǰ�ý����룩
*/
  if( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾TTxnCd������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TTxnCd������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCod", sTxnCod, TxnCodLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾TxnCod������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TxnCod������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾HTxnCd������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾HTxnCd������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾ActDat������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾ActDat������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾NodNo������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾NodNo������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾BrNo������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾BrNo������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾DskNo������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾DskNo������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾TxnObj������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TxnObj������" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾TxnCnl������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TxnCnl������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "IsTxn", sIsTxn, IsTxnLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾IsTxn������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾IsTxn������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFlg", sUpdFlg, UpdFlgLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾UpdFlg������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾UpdFlg������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFld", sUpdFld, UpdFldLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾UpdFld������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾UpdFld������" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TlrId", sTlrId, TlrIdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:��ȡ�ڵ㡾TlrId������!\n" );
    bpAddResult( TrNode, "MDF999", "��ȡ�ڵ㡾TlrId������" );
    return( -1 );
  }
/*
**  ��ȡӦ�����Σ�����
*/
  ClearStr( sYSPC );
  ClearStr( sJYSJ );
  strcpy( sYSPC, Step_Arg1 );
  strcpy( sBokNum, Step_Arg2 );
  hgetdatetime( sJYSJ );
/* 
**  ������ȡ��ˮ��
*/
  ClearStr( sLogNo );
  ClearStr( sDate  );
  ClearStr( sSeqNo );
  if( sqnGetLogNo( sLogNo, atol(sBokNum) ) < 0 ) {
    bpErrorLog(trdata, "MdfBokProc:ȡǰ����ˮ�ų���" );
    bpAddResult(TrNode, "MDF999", "ȡǰ����ˮ�ų���" );
    return( -1 );
  }
  memcpy( sDate, sLogNo, DateLen );
  memcpy( sSeqNo, sLogNo+DateLen, SeqNoLen );
  bpErrorLog(trdata, "MdfBokProc:1.ȡǰ����ˮ�š�%s����%s����%s��", sLogNo,sDate,sSeqNo);

/*
**  ����������ϸ�����п��Եȴ������¼
*/
  bpTraceLog( trdata, "MdfBokProc:��ʼ���ɻ��ܿ۷Ѽ�¼.\n" );
  EXEC SQL DECLARE cur_ysmx2 CURSOR FOR
      select TBSDM, rtrim(SBBM), CDFlag, TZNY, rtrim(char(sum(bigint(BokAmt))))
        from MDFYHYSMX
       where YSPC=:sYSPC
         and YSMXZT='U'
         and CdFlag='D'
    group by TBSDM, SBBM, CDFlag, TZNY;
  EXEC SQL OPEN cur_ysmx2;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog(trdata, "MdfBokProc:��ѯ��MDFYHYSMX���쳣�����α��[%d]", SQLCODE);
    bpAddResult(TrNode, "MDF999", "��ѯ��MDFYHYSMX���쳣�����α��" );
    return( -1 );
  }
  for( ; ; ) {
/*
**  �α������ʼ��
*/
    ClearStr( sTBSDM  );
    ClearStr( sSBBM   );
    ClearStr( sCdFlag );
    ClearStr( sTZNY   );
    ClearStr( sTmpAmt );
    ClearStr( sTxnAmt );
    ClearStr( sYHZH   );
    ClearStr( sYHHM   );
    EXEC SQL FETCH cur_ysmx2 INTO :sTBSDM, :sSBBM, :sCdFlag, :sTZNY, :sTmpAmt;
    if( SQLCODE == SQL_NOTFOUND ) break;
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog(trdata, "MdfBokProc:��ѯ��MDFYHYSMX���쳣��FETCH����[%d]", SQLCODE);
      bpAddResult(TrNode, "MDF999", "��ѯ��MDFYHYSMX���쳣��FETCH����" );
      EXEC SQL CLOSE cur_ysmx2;
      return( -1 );
    }
    sprintf( sTxnAmt,"%015s", sTmpAmt );
/*
**  �Ǽ���ˮ��
*/
    EXEC SQL insert into MDFTXNJNL( LogNo,TTxnCd,TxnCod,HTxnCd,TxnTyp,OIFlag,BusTyp,CrpCod,ActDat,CcyCod,TxnAmt,NodNo,BrNo,TlrId,TTxnSt,TxnSts,HTxnSt,DskNo,TxnObj,TxnCnl,IsTxn,UpdFlg,UpdFld,CdFLag,TBSDM,SBBM,TZNY )
                            values( :sLogNo,:sTTxnCd,:sTxnCod,:sHTxnCd,'N','1','','MDF999999999',:sActDat,'CNY',:sTxnAmt,:sNodNo,:sBrNo,:sTlrId,'U','U','U',:sDskNo,:sTxnObj,:sTxnCnl,:sIsTxn,:sUpdFlg,:sUpdFld,:sCdFlag,:sTBSDM,:sSBBM,:sTZNY );
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfBokProc:INSERT��MDFTXNJNL���쳣[%d]", SQLCODE );
      bpErrorLog( trdata, "MdfBokProc:INSERT��MDFTXNJNL���쳣[%d]-��������-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sLogNo,sTTxnCd,sTxnCod,sHTxnCd,sActDat,sTxnAmt,sNodNo,sBrNo,sTlrId,sDskNo,sTxnObj,sTxnCnl,sIsTxn,sUpdFlg,sUpdFld,sCdFlag,sTBSDM,sSBBM,sTZNY );
      bpAddResult(TrNode, "MDF999", "INSERT��MDFTXNJNL���쳣" );
      EXEC SQL CLOSE cur_ysmx2;
      return( -1 );
    }
    EXEC SQL update MDFYHYSMX set LogNo=:sLogNo, DskNo=:sDskNo, YSMXZT='B' where YSPC=:sYSPC and YSMXZT='U' and TBSDM=:sTBSDM and SBBM=:sSBBM and TZNY=:sTZNY and CdFlag='D';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfBokProc:UPDATE��MDFYHYSMX���쳣[%d]-��������-[%s]-[%s]-[%s]-[%s]", SQLCODE,sYSPC,sLogNo,sTBSDM,sSBBM );
      bpAddResult(TrNode, "MDF999", "UPDATE��MDFYHYSMX���쳣" );
      EXEC SQL CLOSE cur_ysmx2;
      return( -1 );
    }
    iCount++;
    ClearStr( sLogNo );
    sprintf( sSeqNo,"%08ld", atol(sSeqNo)+1 );
    sprintf( sLogNo,"%s%s", sDate, sSeqNo );
    bpErrorLog(trdata, "MdfBokProc:2.ȡǰ����ˮ�š�%s����%s��", sLogNo,sSeqNo);
  }
  sprintf( sOrnCnt,"%d", iCount );
  EXEC SQL CLOSE cur_ysmx2;
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
  bpAddResult(TrNode, "000000", "MdfBokProc:�������" );
  bpTraceLog( trdata, "End MdfBokProc.\n" );
  return (0);
}
