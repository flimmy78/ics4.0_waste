/******************************************************************************       
      Copyright (C),1998-2003,Hisuntech Co.,Ltd.            
                                                                                      
  File name   : mdf.cp
  Author      : Jamez
  Version     : 2.0  
  Date        : 2009.02.03  
  Description : MDF 广州市医保系统原子函数
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
  Description     : 根据POS入帐明细生成入帐数据
  Calls           : 被本函数调用的函数清单
  Called By       : 调用本函数的函数清单
  Table Accessed  : MDFYHYSMX PclCusAgr MDFTXNJNL
  Table Updated    : MDFYHYSMX
  Input           : ETF *TrNode  输入树
                    ST_TranData* trdata  公共结构
                    char* args  参数
                    DBConHandle* DBHandle  数据库句柄
  Output          : 对输出参数的说明
  Return          : 0--成功 小于0--失败
  Others          : 其它说明
******************************************************************************/
int MdfCrtJnl(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  传入参数
*/
    char   sYSPC[YSPCLen+1];
    char   sBokNum[BokNumLen+1];
    char   sJYSJ[JYSJLen+1];
/*
**  大小通道数据
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
**  游标一参数【处理冲正记录】
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
**  游标一参数【处理扣费记录】
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
**  程序变量
*/
    char   sOrnCnt[OrnCntLen+1];
  EXEC SQL END DECLARE SECTION;
    long   iCount=0;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin MdfCrtJnl.\n" );
/*
**  检查参数个数
*/
  if( Step_Args_Num != 2 ) {
    bpErrorLog( trdata, "MdfCrtJnl:参数个数错!\n" );
    bpAddResult( TrNode, "MDF999", "参数个数错" );
    return( -1 );
  }
/*
**  大小通道参数初始化
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
**  传入参数处理（磁盘号、会计日期、大小通道目标服务、银联清算日期、前置交易码）
*/
  if( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【TTxnCd】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TTxnCd】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCod", sTxnCod, TxnCodLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【TxnCod】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TxnCod】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【HTxnCd】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【HTxnCd】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【ActDat】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【ActDat】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【NodNo】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【NodNo】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【BrNo】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【BrNo】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【DskNo】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【DskNo】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【TxnObj】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TxnObj】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【TxnCnl】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TxnCnl】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "IsTxn", sIsTxn, IsTxnLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【IsTxn】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【IsTxn】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFlg", sUpdFlg, UpdFlgLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【UpdFlg】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【UpdFlg】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFld", sUpdFld, UpdFldLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【UpdFld】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【UpdFld】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TlrId", sTlrId, TlrIdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCrtJnl:获取节点【TlrId】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TlrId】错误" );
    return( -1 );
  }
/*
**  获取应收批次，笔数
*/
  ClearStr( sYSPC );
  ClearStr( sJYSJ );
  strcpy( sYSPC, Step_Arg1 );
  strcpy( sBokNum, Step_Arg2 );
  hgetdatetime( sJYSJ );
/* 
**  批量获取流水号
*/
  ClearStr( sLogNo );
  ClearStr( sDate  );
  ClearStr( sSeqNo );
  if( sqnGetLogNo( sLogNo, atol(sBokNum) ) < 0 ) {
    bpErrorLog(trdata, "MdfCrtJnl:取前置流水号出错" );
    bpAddResult(TrNode, "MDF999", "取前置流水号出错" );
    return( -1 );
  }
  memcpy( sDate, sLogNo, DateLen );
  memcpy( sSeqNo, sLogNo+DateLen, SeqNoLen );
  bpErrorLog(trdata, "MdfCrtJnl:1.取前置流水号【%s】【%s】【%s】", sLogNo,sDate,sSeqNo);
/*
**  先处理冲正的记录
*/
  bpTraceLog( trdata, "MdfCrtJnl:开始处理冲正记录.\n" );
  EXEC SQL DECLARE c_ysmx1 CURSOR FOR
      select YSLSH, DYSBLSH, KDM, JE
        from MDFYHYSMX
       where YSPC=:sYSPC
          and YSMXZT='U'
          and CdFlag='C';
  EXEC SQL OPEN c_ysmx1;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog(trdata, "MdfCrtJnl:查询表【MDFYHYSMX】异常－打开冲正游标c_ysmx1错[%d]", SQLCODE);
    bpAddResult(TrNode, "MDF999", "查询表【MDFYHYSMX】异常－打开冲正游标c_ysmx1错" );
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
      bpErrorLog( trdata, "MdfCrtJnl:查询表【MDFYHYSMX】异常－FETCH出错[%d]", SQLCODE );
      bpAddResult( TrNode, "MDF999", "查询表【MDFYHYSMX】异常－FETCH出错" );
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
      bpErrorLog( trdata, "MdfCrtJnl:查询表【MDFYHYSMX】对应扣费记录异常【%s】【%s】【%d】", sDYSBLSH,sKDM,SQLCODE );
      bpAddResult( TrNode, "MDF999", "查询表【MDFYHYSMX】对应扣费记录异常" );
      EXEC SQL CLOSE c_ysmx1;
      return( -1 );
    }
    if( SQLCODE == SQL_NOTFOUND ) {
      strcpy( sYSMXZT, "S" );
      strcpy( sSJZT, "0003" );
    } else {
      if ( ( strcmp( sYSMXZT, "F" )==0 ) || ( strcmp( sYSMXZT, "U" )==0 ) ) {
/*
**  状态为处理失败或未处理过
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
            bpErrorLog( trdata, "MdfCrtJnl:更新表【MDFYHYSMX】被冲正明细异常【%s】【%s】【%s】【%d】【%s】", sDYSBLSH,sKDM,sYSMXZT,SQLCODE,SQLERRMSG );
            bpAddResult( TrNode, "MDF999", "更新表【MDFYHYSMX】被冲正明细异常" );
            EXEC SQL CLOSE c_ysmx1;
            return( -1 );
          }
          strcpy( sYSMXZT, "S" );
          strcpy( sSJZT, "0003" );
        }
      } else {
          if ( strcmp( sYSMXZT, "S" )==0 ) { /*已扣款*/
            strcpy( sYSMXZT, "F" );
            strcpy( sSJZT, "0051" );
          } else {
/*
**  若为其他状态，这说明记帐进程正在处理，留在柜台交易时计算
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
      bpErrorLog(trdata, "MdfCrtJnl:更新表【MDFYHYSMX】冲正明细异常【%s】【%s】【%d】【%s】", sYSLSH,sKDM,SQLCODE,SQLERRMSG);
      bpAddResult(TrNode, "MDF999", "更新表【MDFYHYSMX】冲正明细异常" );
      EXEC SQL CLOSE c_ysmx1;
      return( -1 );
    }
  }
  EXEC SQL CLOSE c_ysmx1;
/*
**  遍历交易明细表所有可以等待处理记录
*/
  bpTraceLog( trdata, "MdfCrtJnl:开始生成汇总扣费记录.\n" );
  EXEC SQL DECLARE c_ysmx2 CURSOR FOR
      select TBSDM, rtrim(SBBM), CDFlag, TZNY, rtrim(char(sum(bigint(BokAmt))))
        from MDFYHYSMX
       where YSPC=:sYSPC
         and YSMXZT='U'
         and CdFlag='D'
    group by TBSDM, SBBM, CDFlag, TZNY;
  EXEC SQL OPEN c_ysmx2;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog(trdata, "MdfCrtJnl:查询表【MDFYHYSMX】异常－打开游标错[%d]", SQLCODE);
    bpAddResult(TrNode, "MDF999", "查询表【MDFYHYSMX】异常－打开游标错" );
    return( -1 );
  }
  for( ; ; ) {
/*
**  游标参数初始化
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
      bpErrorLog(trdata, "MdfCrtJnl:查询表【MDFYHYSMX】异常－FETCH出错[%d]", SQLCODE);
      bpAddResult(TrNode, "MDF999", "查询表【MDFYHYSMX】异常－FETCH出错" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
    sprintf( sTxnAmt,"%015s", sTmpAmt );
/*
**  获取最新签约账号、账户

    EXEC SQL select YHZH, YHHM
               into :sYHZH, :sYHHM
               from MDFCUSINF
              where TBSDM=:sTBSDM
                and SBBM=:sSBBM;
    if( ( SQLCODE != SQL_SUCCESS )&&( SQLCODE != SQL_NOTFOUND ) ) {
      bpErrorLog(trdata, "MdfCrtJnl:获取客户资料出错TBSDM【%s】【%s】【%d】", sTBSDM,sSBBM,SQLCODE);
      bpAddResult(TrNode, "MDF999", "获取客户资料出错" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
*/
/*
    if( sqnGetLogNo( sLogNo, 1 ) < 0 ) {
      bpErrorLog(trdata, "MdfCrtJnl:取前置流水号出错" );
      bpAddResult(TrNode, "MDF999", "取前置流水号出错" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
*/
/*
**  登记流水表
*/
    EXEC SQL insert into MDFTXNJNL( LogNo,TTxnCd,TxnCod,HTxnCd,TxnTyp,OIFlag,BusTyp,CrpCod,ActDat,CcyCod,TxnAmt,NodNo,BrNo,TlrId,TTxnSt,TxnSts,HTxnSt,DskNo,TxnObj,TxnCnl,IsTxn,UpdFlg,UpdFld,CdFLag,TBSDM,SBBM,TZNY )
                            values( :sLogNo,:sTTxnCd,:sTxnCod,:sHTxnCd,'N','1','','MDF999999999',:sActDat,'CNY',:sTxnAmt,:sNodNo,:sBrNo,:sTlrId,'U','U','U',:sDskNo,:sTxnObj,:sTxnCnl,:sIsTxn,:sUpdFlg,:sUpdFld,:sCdFlag,:sTBSDM,:sSBBM,:sTZNY );
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfCrtJnl:INSERT表【MDFTXNJNL】异常[%d]", SQLCODE );
      bpErrorLog( trdata, "MdfCrtJnl:INSERT表【MDFTXNJNL】异常[%d]-数据内容-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sLogNo,sTTxnCd,sTxnCod,sHTxnCd,sActDat,sTxnAmt,sNodNo,sBrNo,sTlrId,sDskNo,sTxnObj,sTxnCnl,sIsTxn,sUpdFlg,sUpdFld,sCdFlag,sTBSDM,sSBBM,sTZNY );
      bpAddResult(TrNode, "MDF999", "INSERT表【MDFTXNJNL】异常" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
    EXEC SQL update MDFYHYSMX set LogNo=:sLogNo, DskNo=:sDskNo, YSMXZT='B' where YSPC=:sYSPC and YSMXZT='U' and TBSDM=:sTBSDM and SBBM=:sSBBM and TZNY=:sTZNY and CdFlag='D';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfCrtJnl:UPDATE表【MDFYHYSMX】异常[%d]-数据内容-[%s]-[%s]-[%s]-[%s]", SQLCODE,sYSPC,sLogNo,sTBSDM,sSBBM );
      bpAddResult(TrNode, "MDF999", "UPDATE表【MDFYHYSMX】异常" );
      EXEC SQL CLOSE c_ysmx2;
      return( -1 );
    }
    iCount++;
    ClearStr( sLogNo );
    sprintf( sSeqNo,"%08ld", atol(sSeqNo)+1 );
    sprintf( sLogNo,"%s%s", sDate, sSeqNo );
    bpErrorLog(trdata, "MdfCrtJnl:2.取前置流水号【%s】【%s】", sLogNo,sSeqNo);
  }
  sprintf( sOrnCnt,"%d", iCount );
  EXEC SQL CLOSE c_ysmx2;
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
  bpAddResult(TrNode, "000000", "数据表【MdfCrtJnl】整理完成" );
  bpTraceLog( trdata, "End MdfCrtJnl.\n" );
  return (0);
}
/******************************************************************************
  Function        : MdfCanProc
  Description     : 根据批次号处理对应批次的冲正记录
  Calls           : 被本函数调用的函数清单
  Called By       : 调用本函数的函数清单
  Table Accessed  : MDFYHYSMX 
  Table Updated   : MDFYHYSMX
  Input           : ETF *TrNode  输入树
                    ST_TranData* trdata  公共结构
                    char* args  参数
                    DBConHandle* DBHandle  数据库句柄
  Output          : 对输出参数的说明
  Return          : 0--成功 小于0--失败
  Others          : 其它说明
******************************************************************************/
int MdfCanProc(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  传入参数
*/
    char   sYSPC[YSPCLen+1];
    char   sJYSJ[JYSJLen+1];
    char   sActDat[ActDatLen+1];
/*
**  游标一参数【处理冲正记录】
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
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin MdfCanProc.\n" );
/*
**  检查参数个数
*/
  if( Step_Args_Num != 1 ) {
    bpErrorLog( trdata, "MdfCanProc:参数个数错!\n" );
    bpAddResult( TrNode, "MDF999", "参数个数错" );
    return( -1 );
  }
/*
**  获取应收批次，笔数
*/
  ClearStr( sYSPC );
  ClearStr( sJYSJ );
  strcpy( sYSPC, Step_Arg1 );
  hgetdatetime( sJYSJ );
	ClearStr( sActDat );
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfCanProc:获取节点【ActDat】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【ActDat】错误" );
    return( -1 );
  }
/*
**  处理冲正的记录
*/
  bpTraceLog( trdata, "MdfCanProc:开始处理冲正记录.\n" );
  EXEC SQL DECLARE cur_ysmx1 CURSOR FOR
      select YSLSH, DYSBLSH, KDM, JE
        from MDFYHYSMX
       where YSPC=:sYSPC
          and YSMXZT='U'
          and CdFlag='C';
  EXEC SQL OPEN cur_ysmx1;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog(trdata, "MdfCanProc:查询表【MDFYHYSMX】OPEN游标cur_ysmx1错【%d】YSPC【%s】",SQLCODE,sYSPC);
    bpAddResult(TrNode, "MDF999", "查询表【MDFYHYSMX】OPEN游标cur_ysmx1错" );
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
      bpErrorLog( trdata, "MdfCanProc:查询表【MDFYHYSMX】FETCH游标cur_ysmx1错【%d】", SQLCODE );
      bpAddResult( TrNode, "MDF999", "查询表【MDFYHYSMX】FETCH游标cur_ysmx1错" );
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
      bpErrorLog( trdata, "MdfCanProc:查询表【MDFYHYSMX】对应扣费记录异常【%s】【%s】【%d】", sDYSBLSH,sKDM,SQLCODE );
      bpAddResult( TrNode, "MDF999", "查询表【MDFYHYSMX】对应扣费记录异常" );
      EXEC SQL CLOSE cur_ysmx1;
      return( -1 );
    }
    if( SQLCODE == SQL_NOTFOUND ) {
      strcpy( sYSMXZT, "S" );
      strcpy( sSJZT, "0003" );
    } else {
      if ( ( strcmp( sYSMXZT, "F" )==0 ) || ( strcmp( sYSMXZT, "U" )==0 ) ) {
/*
**  状态为处理失败或未处理过
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
            bpErrorLog( trdata, "MdfCanProc:更新表【MDFYHYSMX】被冲正明细异常【%s】【%s】【%s】【%d】【%s】", sDYSBLSH,sKDM,sYSMXZT,SQLCODE,SQLERRMSG );
            bpAddResult( TrNode, "MDF999", "更新表【MDFYHYSMX】被冲正明细异常" );
            EXEC SQL CLOSE cur_ysmx1;
            return( -1 );
          }
          strcpy( sYSMXZT, "S" );
          strcpy( sSJZT, "0003" );
        }
      } else {
          if ( strcmp( sYSMXZT, "S" )==0 ) { /*已扣款*/
            strcpy( sYSMXZT, "F" );
            strcpy( sSJZT, "0051" );
          } else {
/*
**  若为其他状态，这说明记帐进程正在处理，留在柜台交易时计算
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
      bpErrorLog(trdata, "MdfCanProc:更新表【MDFYHYSMX】冲正明细异常【%s】【%s】【%d】【%s】", sYSLSH,sKDM,SQLCODE,SQLERRMSG);
      bpAddResult(TrNode, "MDF999", "更新表【MDFYHYSMX】冲正明细异常" );
      EXEC SQL CLOSE cur_ysmx1;
      return( -1 );
    }
  }
  EXEC SQL CLOSE cur_ysmx1;
  bpAddResult(TrNode, "000000", "MdfCanProc:处理完成" );
  bpTraceLog( trdata, "End MdfCanProc.\n" );
  return (0);
}
/******************************************************************************
  Function        : MdfBokProc
  Description     : 根据批次号处理对应批次的入帐数据
  Calls           : 被本函数调用的函数清单
  Called By       : 调用本函数的函数清单
  Table Accessed  : MDFYHYSMX MDFCUSINF
  Table Updated    : MDFYHYSMX
  Input           : ETF *TrNode  输入树
                    ST_TranData* trdata  公共结构
                    char* args  参数
                    DBConHandle* DBHandle  数据库句柄
  Output          : 对输出参数的说明
  Return          : 0--成功 小于0--失败
  Others          : 其它说明
******************************************************************************/
int MdfBokProc(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
/*
**  传入参数
*/
    char   sYSPC[YSPCLen+1];
    char   sBokNum[BokNumLen+1];
    char   sJYSJ[JYSJLen+1];
/*
**  大小通道数据
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
**  游标一参数【处理冲正记录】
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
**  游标一参数【处理扣费记录】
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
**  程序变量
*/
    char   sOrnCnt[OrnCntLen+1];
  EXEC SQL END DECLARE SECTION;
    long   iCount=0;
/*
**  设置跟踪信息
*/
  bpTraceLog( trdata, "Begin MdfBokProc.\n" );
/*
**  检查参数个数
*/
  if( Step_Args_Num != 2 ) {
    bpErrorLog( trdata, "MdfBokProc:参数个数错!\n" );
    bpAddResult( TrNode, "MDF999", "参数个数错" );
    return( -1 );
  }
/*
**  大小通道参数初始化
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
**  传入参数处理（磁盘号、会计日期、大小通道目标服务、银联清算日期、前置交易码）
*/
  if( etfGetChildValue(TrNode, "TTxnCd", sTTxnCd, TTxnCdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【TTxnCd】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TTxnCd】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCod", sTxnCod, TxnCodLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【TxnCod】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TxnCod】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "HTxnCd", sHTxnCd, HTxnCdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【HTxnCd】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【HTxnCd】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "ActDat", sActDat, ActDatLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【ActDat】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【ActDat】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "NodNo", sNodNo, NodNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【NodNo】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【NodNo】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "BrNo", sBrNo, BrNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【BrNo】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【BrNo】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "DskNo", sDskNo, DskNoLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【DskNo】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【DskNo】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnObj", sTxnObj, TxnObjLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【TxnObj】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TxnObj】错误" );
    return( -1 );
  }
  if( etfGetChildValue(TrNode, "TxnCnl", sTxnCnl, TxnCnlLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【TxnCnl】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TxnCnl】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "IsTxn", sIsTxn, IsTxnLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【IsTxn】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【IsTxn】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFlg", sUpdFlg, UpdFlgLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【UpdFlg】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【UpdFlg】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "UpdFld", sUpdFld, UpdFldLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【UpdFld】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【UpdFld】错误" );
    return( -1 );
  }
  if ( etfGetChildValue(TrNode, "TlrId", sTlrId, TlrIdLen+1) <= 0 ) {
    bpErrorLog( trdata, "MdfBokProc:获取节点【TlrId】错误!\n" );
    bpAddResult( TrNode, "MDF999", "获取节点【TlrId】错误" );
    return( -1 );
  }
/*
**  获取应收批次，笔数
*/
  ClearStr( sYSPC );
  ClearStr( sJYSJ );
  strcpy( sYSPC, Step_Arg1 );
  strcpy( sBokNum, Step_Arg2 );
  hgetdatetime( sJYSJ );
/* 
**  批量获取流水号
*/
  ClearStr( sLogNo );
  ClearStr( sDate  );
  ClearStr( sSeqNo );
  if( sqnGetLogNo( sLogNo, atol(sBokNum) ) < 0 ) {
    bpErrorLog(trdata, "MdfBokProc:取前置流水号出错" );
    bpAddResult(TrNode, "MDF999", "取前置流水号出错" );
    return( -1 );
  }
  memcpy( sDate, sLogNo, DateLen );
  memcpy( sSeqNo, sLogNo+DateLen, SeqNoLen );
  bpErrorLog(trdata, "MdfBokProc:1.取前置流水号【%s】【%s】【%s】", sLogNo,sDate,sSeqNo);

/*
**  遍历交易明细表所有可以等待处理记录
*/
  bpTraceLog( trdata, "MdfBokProc:开始生成汇总扣费记录.\n" );
  EXEC SQL DECLARE cur_ysmx2 CURSOR FOR
      select TBSDM, rtrim(SBBM), CDFlag, TZNY, rtrim(char(sum(bigint(BokAmt))))
        from MDFYHYSMX
       where YSPC=:sYSPC
         and YSMXZT='U'
         and CdFlag='D'
    group by TBSDM, SBBM, CDFlag, TZNY;
  EXEC SQL OPEN cur_ysmx2;
  if( SQLCODE != SQL_SUCCESS ) {
    bpErrorLog(trdata, "MdfBokProc:查询表【MDFYHYSMX】异常－打开游标错[%d]", SQLCODE);
    bpAddResult(TrNode, "MDF999", "查询表【MDFYHYSMX】异常－打开游标错" );
    return( -1 );
  }
  for( ; ; ) {
/*
**  游标参数初始化
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
      bpErrorLog(trdata, "MdfBokProc:查询表【MDFYHYSMX】异常－FETCH出错[%d]", SQLCODE);
      bpAddResult(TrNode, "MDF999", "查询表【MDFYHYSMX】异常－FETCH出错" );
      EXEC SQL CLOSE cur_ysmx2;
      return( -1 );
    }
    sprintf( sTxnAmt,"%015s", sTmpAmt );
/*
**  登记流水表
*/
    EXEC SQL insert into MDFTXNJNL( LogNo,TTxnCd,TxnCod,HTxnCd,TxnTyp,OIFlag,BusTyp,CrpCod,ActDat,CcyCod,TxnAmt,NodNo,BrNo,TlrId,TTxnSt,TxnSts,HTxnSt,DskNo,TxnObj,TxnCnl,IsTxn,UpdFlg,UpdFld,CdFLag,TBSDM,SBBM,TZNY )
                            values( :sLogNo,:sTTxnCd,:sTxnCod,:sHTxnCd,'N','1','','MDF999999999',:sActDat,'CNY',:sTxnAmt,:sNodNo,:sBrNo,:sTlrId,'U','U','U',:sDskNo,:sTxnObj,:sTxnCnl,:sIsTxn,:sUpdFlg,:sUpdFld,:sCdFlag,:sTBSDM,:sSBBM,:sTZNY );
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfBokProc:INSERT表【MDFTXNJNL】异常[%d]", SQLCODE );
      bpErrorLog( trdata, "MdfBokProc:INSERT表【MDFTXNJNL】异常[%d]-数据内容-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]-[%s]", SQLCODE,sLogNo,sTTxnCd,sTxnCod,sHTxnCd,sActDat,sTxnAmt,sNodNo,sBrNo,sTlrId,sDskNo,sTxnObj,sTxnCnl,sIsTxn,sUpdFlg,sUpdFld,sCdFlag,sTBSDM,sSBBM,sTZNY );
      bpAddResult(TrNode, "MDF999", "INSERT表【MDFTXNJNL】异常" );
      EXEC SQL CLOSE cur_ysmx2;
      return( -1 );
    }
    EXEC SQL update MDFYHYSMX set LogNo=:sLogNo, DskNo=:sDskNo, YSMXZT='B' where YSPC=:sYSPC and YSMXZT='U' and TBSDM=:sTBSDM and SBBM=:sSBBM and TZNY=:sTZNY and CdFlag='D';
    if( SQLCODE != SQL_SUCCESS ) {
      bpErrorLog( trdata, "MdfBokProc:UPDATE表【MDFYHYSMX】异常[%d]-数据内容-[%s]-[%s]-[%s]-[%s]", SQLCODE,sYSPC,sLogNo,sTBSDM,sSBBM );
      bpAddResult(TrNode, "MDF999", "UPDATE表【MDFYHYSMX】异常" );
      EXEC SQL CLOSE cur_ysmx2;
      return( -1 );
    }
    iCount++;
    ClearStr( sLogNo );
    sprintf( sSeqNo,"%08ld", atol(sSeqNo)+1 );
    sprintf( sLogNo,"%s%s", sDate, sSeqNo );
    bpErrorLog(trdata, "MdfBokProc:2.取前置流水号【%s】【%s】", sLogNo,sSeqNo);
  }
  sprintf( sOrnCnt,"%d", iCount );
  EXEC SQL CLOSE cur_ysmx2;
  etfAddOrRepNode( TrNode, "OrnCnt", sOrnCnt, OrnCntLen );
  bpAddResult(TrNode, "000000", "MdfBokProc:处理完成" );
  bpTraceLog( trdata, "End MdfBokProc.\n" );
  return (0);
}
