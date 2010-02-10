/******************************************************************************       
			Copyright (C),1998-2003,Hisuntech Co.,Ltd.            

	File name    : pft_446.cp
	Author       : Jamez
	Version      : 1.0  
	Date         : 2007.06.15  
	Description  : ��ɽ��˰����ҵ����Ի�ԭ�Ӻ���
	History      :


	No.	Date		Author		Modification                 
	===	==========	========	============================
	1	  20090311 	  Delfly		Modify
	1	  20090409 	  Delfly		Modify
	1	  20090414 	  Delfly		Modify
******************************************************************************/
#include "hipft.h"
#include "hibase.h"
#include "hionline.h"
#include "hidatabase.h"
#include "hibusmsg.h"
#include "hibppubdef.h"
#include "hidbt.h"
#include "hipex.h"
#define ClearStr(str) memset(str,'\0',sizeof(str))
#define ClearPrtBuf(str) memset(str,'\0',sizeof(str));memset(str,0x20,PrtBufLen)
/******************************************************************************
	Function          : Pft204FromDb
	Description       : ����������ϸ�����˿��˻���ϸ�ļ�
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : Ftt20xSum PftSec203sum PftSec203Dtl
	Table Updated     : Ftt20xSum PftSec203sum PftSec203Dtl
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int Pft204FromDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;
		char   sPftFil[PftFilLen+1];
/*	�ļ�ͷ	*/
		char   sErrNum[ErrNumLen+1];
		char   sErrAmt[ErrAmtLen+1];
/*	�ļ���	*/
		char   sRcvBNo[RcvBNoLen+1];
		char   sActDat[ActDatLen+1];
		char   sLogNo [LogNoLen+1];
		char   sTCrpCd[TCrpCdLen+1];
		char   sTActDt[TActDtLen+1];
		char   sTLogNo[TLogNoLen+1];
		char   sFskCod[FskCodLen+1];
		char   sTTxnTp[TTxnTpLen+1];
		char   sRtnCod[RtnCodLen+1];
		char   sTVchNo[TVchNoLen+1];
		char   sRcvAct[RcvActLen+1];
		char   sSndAct[SndActLen+1];
		char   sTxnAmt[TxnAmtLen+1];
		char   sTPayTp[TPayTpLen+1];
		char   sPrtFlg[PrtFlgLen+1];
		char   sTaxNam[TaxNamLen+1];
		char   sTaxNo[TaxNoLen+1];
		char   sCrpKnd[CrpKndLen+1];
		char   sDtlNum[DtlNumLen+1];
/*	��ϸ��	*/
		char   sDtlSeq[DtlSeqLen+1];
		char   sDtlAmt[DtlAmtLen+1];
		char   sLvlNam[LvlNamLen+1];
		char   sTSubCd[TSubCdLen+1];
		char   sTaxTyp[TaxTypLen+1];
		char   sTRtnCd[TRtnCdLen+1];
		char   sRmk1[Rmk1Len+1];
		char   sRmk2[Rmk2Len+1];
	EXEC SQL END DECLARE SECTION;
		int		 i, j, iRet=0;
		FILE	 *fp;
		char	 sDatFil[RptFilLen];
/*
**	���ø�����Ϣ
*/
	bpTraceLog( trdata, "Begin Pft204FromDb.\n" );
/*
**	��������������
*/
	if( Step_Args_Num != 2 ) {
		bpAddResult( TrNode, _SYSTEM_ERR, "������" );
		bpErrorLog( trdata, "Pft204FromDb: ����������!" );
		return( -1 );
	}
	ClearStr( sPftFil );
	ClearStr( sDatFil );
	ClearStr( sActDat );
	strcpy( sPftFil, Step_Arg1 );
	strcpy( sDatFil, Step_Arg2 );
	if ( etfGetChildValue(TrNode, "ProDat", sActDat, ActDatLen+1) <= 0 ) {
		bpAddResult( TrNode, "PFT999", "Pft204FromDb: ��ȡ�ڵ㡾ProDat������" );
		bpErrorLog( trdata, "Pft204FromDb:��ȡ�ڵ㡾ProDat������!\n" );
		return( -1 );
	}
/*
**	��ʼ�����˿��ļ�
*/
	fp =fopen( sDatFil, "w" );
	if( fp == NULL ) {
		bpAddResult( TrNode, "PFT999", "���ļ���" );
		bpErrorLog( trdata, "Pft204FromDb:���ļ���%s��ʧ��!\n", sDatFil );
		return( -1 );
	}
	EXEC SQL select substr( right( ( '000000'||rtrim(char(count(*)))),6 ),1,6 ),substr( right( ( '000000000000000'||rtrim(char(COALESCE(sum(bigint(TxnAmt)),0))) ),15 ),1,15 )
						 into :sErrNum, :sErrAmt
						 from PftSec203Sum446
						where PftFil=:sPftFil
							and BilSts='F';
	if( SQLCODE != SQL_SUCCESS ) {
		bpErrorLog(trdata, "Pft204FromDb:��ѯ��PftSec203Sum���쳣��%d��", SQLCODE);
		bpAddResult(TrNode, "PFT999", "��ѯ��PftSec203Sum���쳣" );
		fclose( fp );
		return( -1 );
	}
	if( atoi(sErrNum)== 0 ) {
		bpAddResult(TrNode, "000000", "û�����������ļ�¼" );
		fclose( fp );
		return( 0 );
	}
/*
**	�����ļ�ͷ
*/
	fprintf( fp, "%s%-11s%s%6s%15s\n", sActDat, "61", "0001", sErrNum, sErrAmt );
	EXEC SQL declare c_sec203sum CURSOR FOR
					  select rtrim(RcvBNo), ActDat, LogNo, TCrpCd, TActDt, TLogNo, FskCod, TTxnTp, RtnCod, TVchNo, RcvAct, SndAct, TxnAmt, TPayTp, PrtFlg, TaxNam, TaxNo, CrpKnd, DtlNum
							from PftSec203sum446
						 where PftFil = :sPftFil
							 and BilSts = 'F';
	EXEC SQL OPEN c_sec203sum;
	if( SQLCODE != SQL_SUCCESS ) {
		bpErrorLog(trdata, "Pft204FromDb:��ѯ��PftSec203sum���쳣�����α��[%d]", SQLCODE);
		bpAddResult(TrNode, _DB_QUERY_ERR, "��ѯ��PftSec203sum���쳣" );
		EXEC SQL CLOSE c_sec203sum;
		fclose( fp );
		return( -1 );
	}
	for( ; ; ) {
		ClearStr( sRcvBNo);
		ClearStr( sActDat );
		ClearStr( sLogNo  );
		ClearStr( sTCrpCd );
		ClearStr( sTActDt );
		ClearStr( sTLogNo );
		ClearStr( sFskCod );
		ClearStr( sTTxnTp );
		ClearStr( sRtnCod );
		ClearStr( sTVchNo );
		ClearStr( sRcvAct );
		ClearStr( sSndAct );
		ClearStr( sTxnAmt );
		ClearStr( sTPayTp );
		ClearStr( sPrtFlg );
		ClearStr( sTaxNam );
		ClearStr( sTaxNo  );
		ClearStr( sCrpKnd );
		ClearStr( sDtlNum );
		EXEC SQL fetch c_sec203sum into :sRcvBNo, :sActDat, :sLogNo, :sTCrpCd, :sTActDt, :sTLogNo, :sFskCod, :sTTxnTp, :sRtnCod, :sTVchNo, :sRcvAct, :sSndAct, :sTxnAmt, :sTPayTp, :sPrtFlg, :sTaxNam, :sTaxNo, :sCrpKnd, :sDtlNum;
		if( SQLCODE == SQL_NOTFOUND ) break;
		if( SQLCODE != SQL_SUCCESS ) {
			bpErrorLog(trdata, "Pft204FromDb:��ѯ��PftSec203sum���쳣��FETCH����[%d]", SQLCODE);
			bpAddResult(TrNode, _DB_QUERY_ERR, "��ѯ��PftSec203sum���쳣" );
			bpAddSqlMsg(TrNode, SQLCODE, NULL );
			iRet = -1;
			break;
		}
		hdelrightspace(sRcvBNo);
		hdelrightspace(sActDat);
		hdelrightspace(sLogNo );
		hdelrightspace(sTCrpCd);
		hdelrightspace(sTActDt);
		hdelrightspace(sTLogNo);
		hdelrightspace(sFskCod);
		hdelrightspace(sTTxnTp);
		hdelrightspace(sRtnCod);
		hdelrightspace(sTVchNo);
		hdelrightspace(sRcvAct);
		hdelrightspace(sSndAct);
		hdelrightspace(sTxnAmt);
		hdelrightspace(sTPayTp);
		hdelrightspace(sPrtFlg);
		hdelrightspace(sTaxNam);
		hdelrightspace(sTaxNo );
		hdelrightspace(sCrpKnd);
		hdelrightspace(sDtlNum);
		fprintf( fp, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|", sRcvBNo, sActDat, sLogNo, sTCrpCd, sTActDt, sTLogNo, sFskCod, "15", sRtnCod, sTVchNo, sRcvAct, sSndAct, sTxnAmt, sTPayTp, sPrtFlg, sTaxNam, sTaxNo, sCrpKnd, sDtlNum );
		EXEC SQL declare c_sec203dtl CURSOR FOR
						select DtlSeq, DtlAmt, LvlNam, TSubCd, TaxTyp, TRtnCd, Rmk1, Rmk2
							from PftSec203Dtl446
						 where PftFil=:sPftFil
						 	 and TCrpCd=:sTCrpCd
						 	 and TActDt=:sTActDt
						 	 and TLogNo=:sTLogNo;
		EXEC SQL OPEN c_sec203dtl;
		if( SQLCODE != SQL_SUCCESS ) {
			bpErrorLog(trdata, "Pft204FromDb:��ѯ��PftSec203Dtl���쳣��FETCH����[%d]", SQLCODE);
			bpAddResult(TrNode, _DB_QUERY_ERR, "��ѯ��PftSec203Dtl���쳣" );
			EXEC SQL CLOSE c_sec203sum;
			EXEC SQL CLOSE c_sec203dtl;
			iRet = -1;
			break;
		}
		for( ; ; ) {
			ClearStr( sDtlSeq );
			ClearStr( sDtlAmt );
			ClearStr( sLvlNam );
			ClearStr( sTSubCd );
			ClearStr( sTaxTyp );
			ClearStr( sTRtnCd );
			ClearStr( sRmk1   );
			ClearStr( sRmk2   );
			EXEC SQL fetch c_sec203dtl into :sDtlSeq, :sDtlAmt, :sLvlNam, :sTSubCd, :sTaxTyp, :sTRtnCd, :sRmk1, :sRmk2;
			if( SQLCODE == SQL_NOTFOUND ) {
				fprintf( fp, "%s\n", "" );
				EXEC SQL CLOSE c_sec203dtl;
				break;
			}
			if( SQLCODE != SQL_SUCCESS ) {
				bpErrorLog(trdata, "Pft204FromDb:��ѯ��PftSec203Dtl���쳣��FETCH����[%d]", SQLCODE);
				bpAddResult(TrNode, "PFT999", "��ѯ��PftSec203Dtl���쳣" );
				EXEC SQL CLOSE c_sec203sum;
				EXEC SQL CLOSE c_sec203dtl;
				fclose( fp );
				return( -1 );
			}
			hdelrightspace(sDtlSeq);
			hdelrightspace(sDtlAmt);
			hdelrightspace(sLvlNam);
			hdelrightspace(sTSubCd);
			hdelrightspace(sTaxTyp);
			hdelrightspace(sTRtnCd);
			hdelrightspace(sRmk1  );
			hdelrightspace(sRmk2  );
			fprintf( fp, "%s|%s|%s|%s|%s|%s|%s|%s|", sDtlSeq, sDtlAmt, sLvlNam, sTSubCd, sTaxTyp, sTRtnCd, sRmk1, sRmk2 );
		}
	}
	EXEC SQL CLOSE c_sec203sum;
	fclose( fp );
	if( iRet != 0 ) {
		bpAddResult(TrNode, "PFT999", "�ļ����ɴ�" );
		bpErrorLog( trdata, "Pft204FromDb: �ļ���%s�������쳣", sDatFil );
	}
	bpTraceLog( trdata, "End Pft204FromDb.\n" );
	return iRet;
}
/******************************************************************************
	Function          : PftGzVchFromDb
	Description       : �������ݿ��¼������ƾ֤��ӡ�ļ�
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int PftGzVchFromDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;
		char   sMsgFmt[MsgFmtLen+1];
		char   sClrDat[ClrDatLen+1];
		char   sSndCod[SndCodLen+1];
		char   sRcvCod[RcvCodLen+1];
		char   sClrSce[ClrSceLen+1];
		char   sActTyp[ActTypLen+1];
		char   sActNo[ActNoLen+1];
		char   sFilNam[FilNamLen+1];
		char   sPrtDat[PrtDatLen+1];

		char   sFilSeq[FilSeqLen+1];
		char   sRcvBNo[RcvBNoLen+1];
		char   sRcvBNm[RcvBNmLen+1];
		char   sTActDt[ActDatLen+1];
		char   sSndAct[SndActLen+1];
		char   sRcvAct[RcvActLen+1];
		char   sActNam[ActNamLen+1];
		char   sTxnAmt[TxnAmtLen+1];
		char   sTaxNo[TaxNoLen+1];
		char   sTaxNam[TaxNamLen+1];
		char   sTCrpNm[TCrpNmLen+1];
		char   sTLogNo[TLogNoLen+1];
		char   sFskNam[FskNamLen+1];
		char   sDtlNum[DtlNumLen+1];
    char   sSmr[SmrLen+1];

		char   sTCrpTp[TCrpTpLen+1];

		char   sDtlSeq[DtlSeqLen+1];
		char   sTaxTyp[TaxTypLen+1];
		char   sPrjNam[PrjNamLen+1];
		char   sLvlNam[LvlNamLen+1];
		char   sTaxDt[TaxDtLen+1];
		char   sDtlAmt[DtlAmtLen+1];
		char   sTSubCd[TSubCdLen+1];
		char   sTVchNo[TVchNoLen+1];
		char   sPrtCnt[PrtCntLen+1];
		char   sNodNo[NodNoLen+1];
		char   sBrNo[BrNoLen+1];
	EXEC SQL END DECLARE SECTION;
		char   sRptFil[RptFilLen+1];
		FILE   *fp;
		int    i,iCount;
		char   sPrtBuf[PrtBufLen+1];
		char   sCapAmt[AmtBufLen+1];
		char   sTmpAmt[AmtBufLen+1];
		char   sAmt[AmtBufLen+1];
		char   sBuf[BufLen+1];
/*
**���ø�����Ϣ
*/
	bpTraceLog( trdata, "Begin PftGzVchFromDb.\n" );
/*
**��������������
*/
	if( Step_Args_Num != 9 ) {
		bpAddResult( TrNode, "PFT999", "PftGzVchFromDb: ����������" );
		bpErrorLog( trdata, "PftGzVchFromDb: ����������!" );
		return( -1 );
	}
	ClearStr( sMsgFmt );
	ClearStr( sClrDat );
	ClearStr( sSndCod );
	ClearStr( sRcvCod );
	ClearStr( sClrSce );
	ClearStr( sActTyp );
	ClearStr( sActNo  );
	ClearStr( sFilNam );
	ClearStr( sPrtDat );
	ClearStr( sRptFil );
	strcpy( sMsgFmt, Step_Arg1 );
	strcpy( sClrDat, Step_Arg2 );
	strcpy( sSndCod, Step_Arg3 );
	strcpy( sRcvCod, Step_Arg4 );
	strcpy( sClrSce, Step_Arg5 );
	strcpy( sActTyp, Step_Arg6 );
	strcpy( sActNo,  Step_Arg7 );
	strcpy( sFilNam, Step_Arg8 );
	strcpy( sPrtDat, Step_Arg9 );
	sprintf( sRptFil, "%s/%s/%s", getenv("WORKDIR"), RPTPTH, Step_Arg8 );
/*
**��ȡ������������
*/
	if ( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
		bpAddResult( TrNode, "PFT999", "PftGzVchFromDb: ��ȡ�ڵ㡾BrNo������" );
		bpErrorLog( trdata, "PftGzVchFromDb:��ȡ�ڵ㡾BrNo������!\n" );
		return( -1 );
	}
	if ( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
		bpAddResult( TrNode, "PFT999", "PftGzVchFromDb: ��ȡ�ڵ㡾NodNo������" );
		bpErrorLog( trdata, "PftGzVchFromDb:��ȡ�ڵ㡾NodNo������!\n" );
		return( -1 );
	}
	fp =fopen( sRptFil, "w" );
	if( fp == NULL ) {
		fclose( fp );
		bpAddResult( TrNode, "PFT999", "PftGzVchFromDb:�򿪱����ļ���" );
		bpErrorLog( trdata, "PftGzVchFromDb:�򿪱����ļ���%s��ʧ��!\n", sFilNam );
		return( -1 );
	}
/*
**���´�ӡ����
*/
	bpErrorLog( trdata, "PftGzVchFromDb:��%s����%s����%s����%s����%s����%s����%s����%s��", sMsgFmt,sClrDat,sSndCod,sRcvCod,sClrSce,sActTyp,sActNo,sNodNo);
	EXEC SQL update PftSec202Sum446
							set PrtCnt=char(int(PrtCnt)+1)
						where MsgFmt =:sMsgFmt
							and ClrDat =:sClrDat
							and RcvCod =:sRcvCod
							and ClrSce =:sClrSce
							and ( ActTyp =:sActTyp or '' =:sActTyp )
							and ( ActNo =:sActNo or '' =:sActNo )
							and ( OpnNod=:sNodNo or ' '=:sNodNo )
							and OpnBr=:sBrNo;
	if( SQLCODE == SQL_NOTFOUND ) {
		bpAddResult(TrNode, "PFT999", "PftGzVchFromDb:û�����������ļ�¼" );
		bpErrorLog( trdata, "PftGzVchFromDb:û�����������ļ�¼��%d��", SQLCODE );
		return( -1 );
	}
	if( SQLCODE != SQL_SUCCESS ) {
		bpAddResult(TrNode, "PFT999", "PftGzVchFromDb:UpDate��PftSec202Sum446���α��" );
		bpErrorLog( trdata, "PftGzVchFromDb:Update��PftSec202Sum446����ӡ��������%d��", SQLCODE );
		return( -1 );
	}
/*
**�ֱ������ƾ֤�����ϸ���α��ȡƾ֤Ҫ��
*/
	EXEC SQL DECLARE c_gz202sum CURSOR FOR
			select a.FilSeq, rtrim(a.RcvBNo), a.RcvBNm, b.TActDt, a.SndAct, a.RcvAct, a.TxnAmt, a.TaxNo, a.TaxNam, c.TCrpNm, a.FskNam, a.DtlNum, a.PrtCnt, a.Smr, b.TVchNo, substr(b.TCrpCd,1,1)
				from PftSec202Sum446 a, PftTxnJnl446 b, PftCrpInf446 c
			 where a.MsgFmt =:sMsgFmt
				 and a.ClrDat =:sClrDat
				 and a.RcvCod =:sRcvCod
				 and a.ClrSce =:sClrSce
				 and ( a.ActTyp =:sActTyp or '' =:sActTyp )
				 and ( a.ActNo =:sActNo or '' =:sActNo )
				 and ( a.OpnNod=:sNodNo or ' '=:sNodNo )
				 and a.OpnBr=:sBrNo
				 and a.BTxnID=b.BTxnID
				 and b.TCrpCd=c.TCrpCd
		order by a.ActNo;

	EXEC SQL DECLARE c_gz202dtl CURSOR FOR
			select DtlSeq, rtrim(TaxTyp), rtrim(PrjNam), LvlNam, TaxDt, rtrim(DtlAmt), TSubCd
				from PftSec202Dtl446
			 where MsgFmt =:sMsgFmt
				 and ClrDat =:sClrDat
				 and RcvCod =:sRcvCod
				 and ClrSce =:sClrSce
				 and FilSeq =:sFilSeq
		order by DtlSeq;
/*
**���ݻ�ȡ
*/
	EXEC SQL OPEN c_gz202sum;
	if( SQLCODE != SQL_SUCCESS ) {
		bpAddResult(TrNode, "PFT999", "PftGzVchFromDb:OPEN��PftSec202Sum446���α��" );
		bpErrorLog(trdata, "PftGzVchFromDb:OPEN��PftSec202Sum446�α����%d��", SQLCODE);
		EXEC SQL CLOSE c_gz202sum;
		EXEC SQL CLOSE c_gz202dtl;
		return( -1 );
	}
	iCount=0;
	for( ; ; ) {
		ClearStr( sFilSeq );
		ClearStr( sRcvBNo );
		ClearStr( sRcvBNm );
		ClearStr( sTActDt );
		ClearStr( sSndAct );
		ClearStr( sRcvAct );
		ClearStr( sActNam );
		ClearStr( sTxnAmt );
		ClearStr( sTaxNo  );
		ClearStr( sTaxNam );
		ClearStr( sTCrpNm );
		ClearStr( sTLogNo );
		ClearStr( sFskNam );
		ClearStr( sDtlNum );
		ClearStr( sPrtCnt );
		ClearStr( sTVchNo );
		ClearStr( sTCrpTp );
		ClearStr( sSmr    );
		EXEC SQL FETCH c_gz202sum INTO :sFilSeq, :sRcvBNo, :sRcvBNm, :sTActDt, :sSndAct, :sRcvAct, :sTxnAmt, :sTaxNo, :sTaxNam, :sTCrpNm, :sFskNam, :sDtlNum, :sPrtCnt, :sSmr, :sTVchNo, :sTCrpTp;
		if( SQLCODE == SQL_NOTFOUND ) break;
		if( SQLCODE != SQL_SUCCESS ) {
			bpErrorLog( trdata, "PftGzVchFromDb:FETCH��PftSec202Sum446������%d��", SQLCODE );
			bpAddResult(TrNode, "PFT999", "PftGzVchFromDb:FETCH��PftSec202Sum446���α��" );
			EXEC SQL CLOSE c_gz202sum;
			EXEC SQL CLOSE c_gz202dtl;
			return( -1 );
    }
		iCount++;

		fprintf( fp, "\n\n\n" );
/*����ڡ����ӽ�����ˮ��(����˰Ʊ��)*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		sprintf( sBuf, "%s", sPrtDat );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+PrtDatLoc,sBuf,sizeof(sBuf) );
		ClearStr( sBuf );
		sprintf( sBuf, "%s", sTVchNo );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TVchNoLoc,sBuf,sizeof(sBuf) );
		fprintf( fp, "%s\n\n", sPrtBuf );
/*��˰�˴��롢���ջ�������*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		sprintf( sBuf, "%s", sTaxNo );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TaxNoLoc,sBuf,BufLen );

		ClearStr( sBuf );
		sprintf( sBuf, "%s", sTCrpNm );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TCrpNmLoc,sBuf,BufLen );
		fprintf( fp, "%s\n", sPrtBuf );
/*��˰��ȫ�ơ���������*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		sprintf( sBuf, "%s", sTaxNam );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TaxNamLoc,sBuf,BufLen );

		ClearStr( sBuf );
		sprintf( sBuf, "��ͨ����%s", sRcvBNm );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+RcvBNmLoc,sBuf,BufLen );
		fprintf( fp, "%s\n", sPrtBuf );
/*�������˺š��տ��������*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		sprintf( sBuf, "%s", sRcvAct );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+RcvActLoc,sBuf,BufLen );
		ClearStr( sBuf );
		sprintf( sBuf, "%s", sFskNam );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+FskNamLoc,sBuf,BufLen );
		fprintf( fp, "%s\n\n\n\n", sPrtBuf );

/*˰(��)�����ơ�Ԥ���ĿԤ�㼶�Ρ�����ʱ�ڡ�ʵ�ɽ��
**д�����
*/
		EXEC SQL OPEN c_gz202dtl;
		if( SQLCODE != SQL_SUCCESS ) {
			EXEC SQL CLOSE c_gz202sum;
			EXEC SQL CLOSE c_gz202dtl;
			bpAddResult(TrNode, "PFT999", "PftGzVchFromDb:OPEN��PftSec202Dtl446���α��" );
			bpErrorLog(trdata, "PftGzVchFromDb:OPEN��PftSec202Dtl446���α��%d��", SQLCODE);
			return( -1 );
		}
		for( ; ; ) {
			ClearStr( sDtlSeq );
			ClearStr( sTaxTyp );
			ClearStr( sPrjNam );
			ClearStr( sLvlNam );
			ClearStr( sTaxDt  );
			ClearStr( sDtlAmt );
			ClearStr( sTSubCd );
			ClearStr( sTVchNo );
			EXEC SQL FETCH c_gz202dtl INTO :sDtlSeq, :sTaxTyp, :sPrjNam, :sLvlNam, :sTaxDt, :sDtlAmt, :sTSubCd;
			if( SQLCODE == SQL_NOTFOUND ) break;
			if( SQLCODE != SQL_SUCCESS ) {
				EXEC SQL CLOSE c_gz202sum;
				EXEC SQL CLOSE c_gz202dtl;
				bpAddResult(TrNode, "PFT999", "PftGzVchFromDb:FETCH��PftSec202Dtl446���α��" );
				bpErrorLog( trdata, "PftGzVchFromDb:FETCH��PftSec202Dtl446������%d��", SQLCODE );
				return( -1 );
				break;
	    }
			ClearPrtBuf( sPrtBuf );
			ClearStr( sTmpAmt );
			ClearStr( sAmt );
			strcpy( sTmpAmt, sDtlAmt );
			hamtfmt( sTmpAmt );
			sprintf( sAmt, "%s%s", "��", sTmpAmt );
			haddchar( sAmt, AmtBufLen, 0x20, 0 );
			ClearStr(sBuf);
			sprintf( sBuf,"%s(%s)",sTaxTyp,sPrjNam);
			haddchar( sBuf, BufLen, 0x20, 0 );
			memcpy( sPrtBuf+TaxTypLoc,sBuf,BufLen );
			memcpy( sPrtBuf+LvlNamLoc,sLvlNam,LvlNamLen );
			memcpy( sPrtBuf+TaxDtLoc,sTaxDt,TaxDtLen );
			memcpy( sPrtBuf+DtlAmtLoc,sAmt,AmtBufLen );
			fprintf( fp, "%s\n", sPrtBuf );
		}
		for( i=atoi(sDtlNum);i<=MaxRow;i++) fprintf( fp, "\n" );

/*Сд����д���*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		ClearStr( sCapAmt );
		strcpy( sCapAmt, sTxnAmt );
		hamttocap( sCapAmt );
		sprintf( sBuf, "%s", sCapAmt );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+CapAmtLoc,sBuf,BufLen );

		ClearStr( sTmpAmt );
		ClearStr( sAmt );
		ClearStr( sBuf );
		strcpy( sTmpAmt, sTxnAmt );
		hamtfmt( sTmpAmt );
		sprintf( sAmt, "%s%s", "��", sTmpAmt );
		haddchar( sAmt, AmtBufLen, 0x20, 0 );
		sprintf( sBuf, "%s", sAmt );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TxnAmtLoc,sBuf,BufLen );
		fprintf( fp, "%s\n\n", sPrtBuf );
/*�������ݡ��ɿ����ڡ���ӡ���� */
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
	  if( strcmp( sTCrpTp,"1" ) )
		{
			sprintf( sBuf,"�۽ɵ�˰���ѣ���" );
		}
	  else {
			sprintf( sBuf,"�۽ɹ�˰��" );
		}
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+ItmNamLoc,sBuf,BufLen );
		ClearStr( sBuf );
		sprintf( sBuf, "%s", sTActDt );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TActDtLoc,sBuf,BufLen );
		ClearStr( sBuf );
		sprintf( sBuf, "%d", atoi(sPrtCnt) );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+PrtCntLoc,sBuf,BufLen );
		fprintf( fp, "%s\n\n\n\n\n\n\n\n\n\n", sPrtBuf );
		EXEC SQL CLOSE c_gz202dtl;
	}
	EXEC SQL CLOSE c_gz202sum;
	fclose( fp );
	if( iCount==0 ) {
		bpAddResult(TrNode, "PFT999", "PftGzVchFromDb: û�����������ļ�¼" );
		bpErrorLog( trdata, "PftGzVchFromDb: û�����������ļ�¼!" );
		return( -1 );
	}
	bpAddResult(TrNode, "000000", "���׳ɹ�" );
	bpTraceLog( trdata, "End PftGzVchFromDb.\n" );
	return(0);
}

/******************************************************************************
	Function          : PftTsVchFromDb
	Description       : �������ݿ��¼��������˰ƾ֤��ӡ�ļ�
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int PftTsVchFromDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;
		char   sMsgFmt[MsgFmtLen+1];
		char   sClrDat[ClrDatLen+1];
		char   sSndCod[SndCodLen+1];
		char   sRcvCod[RcvCodLen+1];
		char   sClrSce[ClrSceLen+1];
		char   sActTyp[ActTypLen+1];
		char   sActNo[ActNoLen+1];
		char   sFilNam[FilNamLen+1];
		char   sPrtDat[PrtDatLen+1];
		
		char   sRcvBNo[RcvBNoLen+1];
		char   sRcvBNm[RcvBNmLen+1];
		char   sActDat[ActDatLen+1];
		char   sSndAct[SndActLen+1];
		char   sRcvAct[RcvActLen+1];
		char	 sTActDt[TActDtLen+1];
		char   sActNam[ActNamLen+1];
		char   sTxnAmt[TxnAmtLen+1];
		char   sTaxNo[TaxNoLen+1];
		char   sTaxNam[TaxNamLen+1];
		char	 sTCrpCd[TCrpCdLen+1];
		char   sTCrpNm[TCrpNmLen+1];
		char   sTLogNo[TLogNoLen+1];
		char   sFskNam[FskNamLen+1];
		char   sFskCod[FskCodLen+1];
		char   sDtlNum[DtlNumLen+1];
    char   sSmr[SmrLen+1];

		char   sTCrpTp[TCrpTpLen+1];
    
    char	 sPftFil[PftFilLen+1];
		char   sDtlSeq[DtlSeqLen+1];
		char   sTaxTyp[TaxTypLen+1];
		char   sPrjNam[PrjNamLen+1];
		char   sLvlNam[LvlNamLen+1];
		char   sTaxDt[TaxDtLen+1];
		char   sDtlAmt[DtlAmtLen+1];
		char   sTSubCd[TSubCdLen+1];
		char   sTVchNo[TVchNoLen+1];
		char	 sTRtnCd[TRtnCdLen+1];
		char	 sTRtnNm[TRtnNmLen+1];
		char   sTRtnTp[TRtnTpLen+1];
		char   sPrtCnt[PrtCntLen+1];
		char   sNodNo[NodNoLen+1];
		char   sBrNo[BrNoLen+1];
		char	 sTlrId[7+1];
		char	 sPrtNod[NodNoLen+1];
	EXEC SQL END DECLARE SECTION;
		char   sRptFil[RptFilLen+1];
		FILE   *fp;
		int    i,iCount;
		char   sPrtBuf[PrtBufLen+1];
		char   sCapAmt[AmtBufLen+1];
		char   sTmpAmt[AmtBufLen+1];
		char   sAmt[AmtBufLen+1];
		char	 sTmp[BufLen+1];
		char   sBuf[BufLen+1];
/*
**���ø�����Ϣ
*/
	bpTraceLog( trdata, "Begin PftTsVchFromDb.\n" );
/*
**��������������
*/
	if( Step_Args_Num != 9 ) {
		bpAddResult( TrNode, "PFT999", "PftTsVchFromDb: ����������" );
		bpErrorLog( trdata, "PftTsVchFromDb: ����������!" );
		return( -1 );
	}
	ClearStr( sMsgFmt );
	ClearStr( sClrDat );
	ClearStr( sSndCod );
	ClearStr( sRcvCod );
	ClearStr( sClrSce );
	ClearStr( sActTyp );
	ClearStr( sActNo  );
	ClearStr( sFilNam );
	ClearStr( sPrtDat );
	ClearStr( sRptFil );
	strcpy( sMsgFmt, Step_Arg1 );
	strcpy( sClrDat, Step_Arg2 );
	strcpy( sSndCod, Step_Arg3 );
	strcpy( sRcvCod, Step_Arg4 );
	strcpy( sClrSce, Step_Arg5 );
	strcpy( sActTyp, Step_Arg6 );
	strcpy( sActNo,  Step_Arg7 );
	strcpy( sFilNam, Step_Arg8 );
	strcpy( sPrtDat, Step_Arg9 );
	sprintf( sRptFil, "%s/%s/%s", getenv("WORKDIR"), RPTPTH, Step_Arg8 );
/*
**��ȡ������������
*/
	if ( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
		bpAddResult( TrNode, "PFT999", "PftTsVchFromDb: ��ȡ�ڵ㡾BrNo������" );
		bpErrorLog( trdata, "PftTsVchFromDb:��ȡ�ڵ㡾BrNo������!\n" );
		return( -1 );
	}
	if ( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
		bpAddResult( TrNode, "PFT999", "PftTsVchFromDb: ��ȡ�ڵ㡾NodNo������" );
		bpErrorLog( trdata, "PftTsVchFromDb:��ȡ�ڵ㡾NodNo������!\n" );
		return( -1 );
	}
	if ( etfGetChildValue(TrNode, "TlrId", sTlrId, 7+1) <= 0 ) {
		bpAddResult( TrNode, "PFT999", "PftTsVchFromDb: ��ȡ�ڵ㡾TlrId������" );
		bpErrorLog( trdata, "PftTsVchFromDb:��ȡ�ڵ㡾TlrId������!\n" );
		return( -1 );
	}
	if ( etfGetChildValue(TrNode, "BakNod", sPrtNod, NodNoLen+1) <= 0 ) {
		bpAddResult( TrNode, "PFT999", "PftTsVchFromDb: ��ȡ�ڵ㡾BakNod������" );
		bpErrorLog( trdata, "PftTsVchFromDb:��ȡ�ڵ㡾BakNod������!\n" );
		return( -1 );
	}	
	fp =fopen( sRptFil, "w" );
	if( fp == NULL ) {
		fclose( fp );
		bpAddResult( TrNode, "PFT999", "PftTsVchFromDb:�򿪱����ļ���" );
		bpErrorLog( trdata, "PftTsVchFromDb:�򿪱����ļ���%s��ʧ��!\n", sFilNam );
		return( -1 );
	}
/*
**���´�ӡ����
*/
	bpErrorLog( trdata, "PftTsVchFromDb:��%s����%s����%s����%s����%s����%s����%s����%s��", sMsgFmt,sClrDat,sSndCod,sRcvCod,sClrSce,sActTyp,sActNo,sNodNo);
	EXEC SQL update PftSec203Sum446
							set PrtCnt=char(int(PrtCnt)+1)
						where MsgFmt =:sMsgFmt
							and ClrDat =:sClrDat
							and RcvCod =:sRcvCod
							and ClrSce =:sClrSce
							and ( ActTyp =:sActTyp or '' =:sActTyp )
							and ( ActNo =:sActNo or '' =:sActNo )
							and ( OpnNod=:sNodNo or ' '=:sNodNo )
							and OpnBr=:sBrNo
						  and BilSts='S';
	if( SQLCODE == SQL_NOTFOUND ) {
		bpAddResult(TrNode, "PFT999", "PftTsVchFromDb:û�����������ļ�¼" );
		bpErrorLog( trdata, "PftTsVchFromDb:û�����������ļ�¼��%d��", SQLCODE );
		return( -1 );
	}
	if( SQLCODE != SQL_SUCCESS ) {
		bpAddResult(TrNode, "PFT999", "PftTsVchFromDb:UpDate��PftSec202Sum446���α��" );
		bpErrorLog( trdata, "PftTsVchFromDb:Update��PftSec202Sum446����ӡ��������%d��", SQLCODE );
		return( -1 );
	}
/*
**�ֱ������ƾ֤�����ϸ���α��ȡƾ֤Ҫ��
*/
	EXEC SQL DECLARE c_gz203sum CURSOR FOR
			select a.PftFil, rtrim(a.RcvBNo), d.NodNam, a.ActDat, a.RcvAct, a.TxnAmt, 
					a.TaxNo, a.TaxNam, CoalEsce(b.TCrpNm,' '),a.TCrpCd, a.FskCod, CoalEsce(c.FskNam,' '), 
					a.DtlNum, a.PrtCnt, a.Smr, a.TLogNo, substr(a.TCrpCd,1,1) ,
					a.TActDt, a.TLogNo, substr(a.SndAct,33,1)
			from (PftSec203Sum446 a left join PftCrpInf446 b on a.TCrpCd=b.TCrpCd) 
					left join pftFskInf446 c on  a.FskCod=c.FskCod , PftNodInf446 d 
			where a.RcvBNo=d.RcvBNo  
			   and a.MsgFmt =:sMsgFmt
				 and a.ClrDat =:sClrDat
				 and a.RcvCod =:sRcvCod
				 and a.ClrSce =:sClrSce
				 and ( a.ActTyp =:sActTyp or '' =:sActTyp )
				 and ( a.ActNo =:sActNo or '' =:sActNo )
				 and ( a.OpnNod=:sNodNo or ' '=:sNodNo )
				 and a.OpnBr=:sBrNo
			   and a.BilSts='S'
			order by a.ActNo;

	EXEC SQL DECLARE c_gz203dtl CURSOR FOR
			select a.DtlSeq, a.TaxTyp, a.LvlNam, rtrim(a.DtlAmt), a.TSubCd, rtrim(a.TRtnCd), CoalEsce(b.TRtnNm,' ')
				from PftSec203Dtl446 a left join PftRtnCod446 b on a.TRtnCd=b.TRtnCd
			 where a.PftFil =:sPftFil 
			 	and a.TCrpCd=:sTCrpCd
			 	and a.TActDt=:sTActDt
			 	and a.TLogNo=:sTLogNo
		order by DtlSeq;
/*
**���ݻ�ȡ
*/
	EXEC SQL OPEN c_gz203sum;
	if( SQLCODE != SQL_SUCCESS ) {
		bpAddResult(TrNode, "PFT999", "PftTsVchFromDb:OPEN��PftSec202Sum446���α��" );
		bpErrorLog(trdata, "PftTsVchFromDb:OPEN��PftSec202Sum446�α����%d��", SQLCODE);
		EXEC SQL CLOSE c_gz203sum;
		EXEC SQL CLOSE c_gz203dtl;
		return( -1 );
	}
	iCount=0;
	for( ; ; ) {
		ClearStr( sPftFil );
		ClearStr( sRcvBNo );
		ClearStr( sRcvBNm );
		ClearStr( sActDat );
		ClearStr( sRcvAct );
		ClearStr( sTxnAmt );
		ClearStr( sTaxNo  );
		ClearStr( sTaxNam );
		ClearStr( sTCrpNm );
		ClearStr( sTCrpCd );
		ClearStr( sFskCod );
		ClearStr( sFskNam );
		ClearStr( sDtlNum );
		ClearStr( sPrtCnt );
		ClearStr( sSmr    );
		ClearStr( sTLogNo );
		ClearStr( sTCrpTp );
		ClearStr( sTActDt );
		ClearStr( sTLogNo );
		ClearStr( sTRtnTp );
		EXEC SQL FETCH c_gz203sum INTO :sPftFil, :sRcvBNo, :sRcvBNm, :sActDat, :sRcvAct, 
			:sTxnAmt, :sTaxNo, :sTaxNam, :sTCrpNm, :sTCrpCd, :sFskCod, :sFskNam, :sDtlNum, 
			:sPrtCnt, :sSmr, :sTLogNo, :sTCrpTp, :sTActDt, :sTLogNo, :sTRtnTp;
		if( SQLCODE == SQL_NOTFOUND ) break;
		if( SQLCODE != SQL_SUCCESS ) {
			bpErrorLog( trdata, "PftTsVchFromDb:FETCH��PftSec203Sum446������%d��", SQLCODE );
			bpAddResult(TrNode, "PFT999", "PftTsVchFromDb:FETCH��PftSec203Sum446���α��" );
			EXEC SQL CLOSE c_gz203sum;
			EXEC SQL CLOSE c_gz203dtl;
			return( -1 );
    }
		iCount++;
    
		fprintf( fp, "\n\n");
		fprintf( fp, "                                              ��ɽ����\n\n\n");
		fprintf( fp, "            �ص����ͣ�ETS������˰\n\n");
		
/*����ڡ����ӽ�����ˮ��*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		sprintf( sBuf, "����ڣ�%s", sPrtDat );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+PrtDatLoc_Rt,sBuf,sizeof(sBuf) );
		ClearStr( sBuf );
		sprintf( sBuf, "���ӽ�����ˮ�ţ�%s", sTLogNo );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TLogNoLoc_Rt,sBuf,sizeof(sBuf) );
		hdelrightspace(sPrtBuf);
		fprintf( fp, "%s\n\n", sPrtBuf );
/*��˰�˴��롢���ջ�������*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		sprintf( sBuf, "��˰��ʶ��ţ�%s", sTaxNo );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TaxNoLoc_Rt,sBuf,BufLen );

		ClearStr( sBuf );
		sprintf( sBuf, "���ջ������ƣ�%s", sTCrpNm );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TCrpNmLoc_Rt,sBuf,BufLen );
		hdelrightspace(sPrtBuf);
		fprintf( fp, "%s\n", sPrtBuf );
/*��˰��ȫ�ơ���������*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		sprintf( sBuf, "��˰��ȫ�ƣ�%s", sTaxNam );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TaxNamLoc_Rt,sBuf,BufLen );

		ClearStr( sBuf );
		sprintf( sBuf, "�������У���ͨ����%s", sRcvBNm );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+RcvBNmLoc_Rt,sBuf,BufLen );
		hdelrightspace(sPrtBuf);
		fprintf( fp, "%s\n", sPrtBuf );
/*�������˺š��տ��������*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		sprintf( sBuf, "�տ����ʺţ�%s", sRcvAct );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+RcvActLoc_Rt,sBuf,BufLen );
		
		ClearStr( sBuf );
		sprintf( sBuf, "�������ƣ�%s", sFskNam );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+FskNamLoc_Rt,sBuf,BufLen );
		hdelrightspace(sPrtBuf);
		fprintf( fp, "%s\n\n", sPrtBuf );

/*Ԥ���Ŀ��Ԥ�㼶�Ρ��˿�ԭ���˿���
**д�����
*/
		EXEC SQL OPEN c_gz203dtl;
		if( SQLCODE != SQL_SUCCESS ) {
			bpAddResult(TrNode, "PFT999", "PftTsVchFromDb:OPEN��PftSec202Dtl446���α��" );
			bpErrorLog(trdata, "PftTsVchFromDb:OPEN��PftSec202Dtl446���α��%d��", SQLCODE);
			EXEC SQL CLOSE c_gz203sum;
			EXEC SQL CLOSE c_gz203dtl;
			return( -1 );
		}

		fprintf( fp, "            Ԥ���Ŀ   ���뼶��            �˿�ԭ��                 �˿���\n" );

		for( ; ; ) {
			ClearStr( sDtlSeq );
			ClearStr( sTaxTyp );
			ClearStr( sLvlNam );
			ClearStr( sDtlAmt );
			ClearStr( sTSubCd );
			ClearStr( sTRtnCd );
			ClearStr( sTRtnNm );
			EXEC SQL FETCH c_gz203dtl INTO :sDtlSeq, :sTaxTyp, :sLvlNam, :sDtlAmt, :sTSubCd, :sTRtnCd, :sTRtnNm;
			if( SQLCODE == SQL_NOTFOUND ) break;
			if( SQLCODE != SQL_SUCCESS ) {
				bpAddResult(TrNode, "PFT999", "PftTsVchFromDb:FETCH��PftSec203Dtl446���α��" );
				bpErrorLog( trdata, "PftTsVchFromDb:FETCH��PftSec203Dtl446������%d��", SQLCODE );
				EXEC SQL CLOSE c_gz203sum;
				EXEC SQL CLOSE c_gz203dtl;
				return( -1 );
				break;
	    }
			ClearPrtBuf( sPrtBuf );
			ClearStr( sTmpAmt );
			ClearStr( sAmt );
			strcpy( sTmpAmt, sDtlAmt );
			hamtfmt( sTmpAmt );
			sprintf( sAmt, "%s%s", "CNY", sTmpAmt );
			haddchar( sAmt, AmtBufLen, 0x20, 0 );
			memcpy( sPrtBuf+TSubCdLoc_Rt,sTSubCd,TSubCdLen );
			memcpy( sPrtBuf+LvlNamLoc_Rt,sLvlNam,LvlNamLen );
			ClearStr( sTmp );
			sprintf( sTmp, "%s-%s",sTRtnCd,sTRtnNm );
			haddchar( sTmp, BufLen, 0x20, 0 );
			memcpy( sPrtBuf+TRtnCdLoc_Rt,sTmp, BufLen );
			memcpy( sPrtBuf+DtlAmtLoc_Rt,sAmt,AmtBufLen );
			hdelrightspace(sPrtBuf);
			fprintf( fp, "%s\n", sPrtBuf );
		}
		for( i=atoi(sDtlNum);i<=MaxRow;i++) fprintf( fp, "\n" );

/*Сд����д���*/
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		ClearStr( sCapAmt );
		strcpy( sCapAmt, sTxnAmt );
		hamttocap( sCapAmt );
		sprintf( sBuf, "���ϼƣ�%s", sCapAmt );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+CapAmtLoc_Rt,sBuf,BufLen );

		ClearStr( sTmpAmt );
		ClearStr( sAmt );
		ClearStr( sBuf );
		strcpy( sTmpAmt, sTxnAmt );
		hamtfmt( sTmpAmt );
		sprintf( sAmt, "%s%s", "CNY", sTmpAmt );
		haddchar( sAmt, AmtBufLen, 0x20, 0 );
		sprintf( sBuf, "%s", sAmt );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TxnAmtLoc_Rt,sBuf,BufLen );
		hdelrightspace(sPrtBuf);
		fprintf( fp, "%s\n\n", sPrtBuf );
/*�������ݡ���˰���ڡ���ӡ���� */
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
	  if( strcmp( sTCrpTp,"1" ) )
		{
			sprintf( sBuf,"��˰���ͣ���˰��˰" );
		}
	  else {
	  	if( strcmp( sTRtnTp, "1" ) )
				sprintf( sBuf,"��˰���ͣ���˰һ����˰" );
			else
				sprintf( sBuf,"��˰���ͣ���˰������˰" );
		}
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+ItmNamLoc_Rt,sBuf,BufLen );
		ClearStr( sBuf );
		sprintf( sBuf, "��˰���ڣ�%s", sTActDt );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TActDtLoc_Rt,sBuf,BufLen );
		ClearStr( sBuf );
		sprintf( sBuf, "��ӡ������%d", atoi(sPrtCnt) );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+PrtCntLoc_Rt,sBuf,BufLen );
		hdelrightspace(sPrtBuf);
		fprintf( fp, "%s\n", sPrtBuf );

/*��ӡ���㡢��ӡ��Ա*/		
		ClearStr( sBuf );
		ClearPrtBuf( sPrtBuf );
		sprintf( sBuf, "��ӡ���㣺%s", sPrtNod );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+NodNoLoc_Rt,sBuf,BufLen );
		
		ClearStr( sBuf );
		sprintf( sBuf, "��ӡ��Ա��%s", sTlrId );
		haddchar( sBuf, BufLen, 0x20, 0 );
		memcpy( sPrtBuf+TlrIdLoc_Rt,sBuf,BufLen );
		hdelrightspace(sPrtBuf);
		fprintf( fp, "%s\n\n\n\n\n\n", sPrtBuf );
		
		
		EXEC SQL CLOSE c_gz203dtl;
	}
	EXEC SQL CLOSE c_gz203sum;
	fclose( fp );
	if( iCount==0 ) {
		bpAddResult(TrNode, "PFT999", "PftTsVchFromDb: û�����������ļ�¼" );
		bpErrorLog( trdata, "PftTsVchFromDb: û�����������ļ�¼!" );
		return( -1 );
	}
	bpAddResult(TrNode, "000000", "���׳ɹ�" );
	bpTraceLog( trdata, "End PftTsVchFromDb.\n" );
	return(0);
}
