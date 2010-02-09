/******************************************************************************
			Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name   : pfa.cp
 Author      : 陈应刚
 Version     : 1.0  
 Date        : 2004.04.13  
 Description : 代理财政支付应用个性原子函数库 
 History		 :


  No.	Date		Author		Modification
  ===	==========	========	============================
   1   20061205    Jamez
******************************************************************************/
#include "hipfa.h"
/******************************************************************************
  Function      : GenPrvData
  Description   : 将ETF树上的节点转换成数据流
  Calls         : ETFToBuf
  Called By     : 任何包含该库的程序
  Table Accessed:
  Table Updated : 无
  Input         : ETF    *ETFRoot    --ETF树
  Output        : char   *Buf     --输出数据流?
                  int    MaxLen   --数据最大长度
  Return        : 0--成功 
                  小于0--失败
  Others        : 如果要传入Group节点,参数名必须是GrpNam
******************************************************************************/
int GenPrvData(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	char   sBuf[BufLen+1];
	char   sArgNam[ArgNamLen+1];
	char   sRecNam[RecNamLen+1];
	char   *Buff;

	int	   len=0,i=0,j=0,iRet=0;

	ETF    *EtfNode=NULL;
	ETF    *TmpNode=NULL;
	ETF    *CloneNode=NULL;

	bpTraceLog( trdata, "\nBegin GenPrvData!" );
	
	if( Step_Args_Num < 1 ) {
		bpAddResult(TrNode, _GET_PARA_ERR, "参数个数不能为零！");
		bpErrorLog(trdata, "参数个数不能为零！");
		return ( -1 );
	}

	EtfNode = etfNewNode( "ROOT", "111", 3 );
	if( EtfNode == NULL ) {
		bpErrorLog(trdata, "创建节点树【RootNode】失败！");
		bpAddResult(TrNode, _PRE_OTHER_ERR, "创建节点树【RootNode】失败！");
		return(-1);
	}

	for( i=0; i<Step_Args_Num; i++ ) {
		if( !strcmp(args.item_name[i], "GrpNam") ) {
			for( j=1; ;j++ ) {
				hsnprintf(sRecNam, sizeof(sRecNam), "%s_%d", args.data[i], j);
				TmpNode = etfGetChildNode(TrNode, NULL, sRecNam);
				if( TmpNode == NULL ) {
					bpErrorLog(trdata,"提示信息：参数【GrpNam】位置【%d】,层次【%d】！", i,j);
					break;
				}
				CloneNode = etfCloneNode(TmpNode);
				if( CloneNode == NULL ) {
					bpErrorLog(trdata,"按组复制节点树【TmpNode】失败！");
					bpAddResult(TrNode, _PRE_OTHER_ERR, "按组复制节点树【TmpNode】失败！");
					return(-1);
				}
				if( NULL == etfAppendNode( EtfNode, CloneNode ) ) {
					bpErrorLog(trdata,"按组追加节点树【TmpNod】到【EtfNode】失败！");
					bpAddResult(TrNode, _PRE_OTHER_ERR, "按组追加节点树【TmpNod】到【EtfNode】失败！");
					etfDelAllNode(CloneNode);
					return(-1);
				}
			}
		} else {
			TmpNode = etfGetChildNode(TrNode, NULL, args.data[i]);
			if( TmpNode == NULL ) {
				bpErrorLog(trdata,"获取单个节点值【%s】失败！",args.data[i]);
				bpAddResult(TrNode, _PRE_OTHER_ERR, "获取单个节点值失败！");
				return(-1);
			}
			CloneNode = etfCloneNode(TmpNode);
			if( CloneNode == NULL ) {
				bpErrorLog(trdata,"复制单个节点值【%s】失败！",args.data[i]);
				bpAddResult(TrNode, _PRE_OTHER_ERR, "复制单个节点值失败！");
				return(-1);
			}
			if( NULL == etfAppendNode( EtfNode, CloneNode ) ) {
				bpErrorLog(trdata,"追加单个节点值【CloneNode】到【EtfNode】失败！");
				bpAddResult(TrNode, _PRE_OTHER_ERR, "追加单个节点值【CloneNode】到【EtfNode】失败！");
				etfDelAllNode(CloneNode);
				return(-1);
			}
		}
		free(Buff);
	}
	iRet = 0;
	ClearStr( sBuf );
	memset( sBuf, 0, sizeof(sBuf) );
	iRet = ETFToBuf(EtfNode, sBuf, BufLen);
	bpFreeEtf(EtfNode);
	if( iRet < 0 ) {
		bpErrorLog(trdata,"将【EtfNode】树转换成数据流失败！");
		bpAddResult(TrNode, _PRE_OTHER_ERR, "将【EtfNode】树转换成数据流失败！");
		return(-1);
	}
	etfAddOrRepNode( TrNode, "PrvDat", sBuf, BufLen );
	bpTraceLog( trdata, "End GenPrvData.\n" );
	return(0);
}

/******************************************************************************
  Function		: GenHostGroupData
  Description	        : 生成主机其他挂帐接口数据
  Calls                 : 
  Called By             : 任何包含该库的程序 
  Table Accessed        : 
  Table Updated	        : 无
  Input			: ETF           *TrNode	   --ETF报文树 
			  ST_TranData   *trdata	   --交易结构
			  PbItemData    *args	   --参数  
			  DBConHandle   *DBHandle  --数据库句柄   
  Output		:    
  Return		: 0--成功 小于0--失败   
  Others		: 无             
******************************************************************************/
int GenHostGroupData(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	int	   ret=0;
	char   CclTyp[FLAG_LEN+1];
	char   CcyCod[CCYCOD_LEN+1];
	char   PayAct[ACTNO_LEN+1];
	char   PyeAct[ACTNO_LEN+1];
	char   ActNo[ACTNO_LEN+1];
	char   CclAct[ACTNO_LEN+1];
	char   CclNo[CCLNO_LEN+1];
	char   TxnAmt[AMOUNT_LEN+1];
	char   HpcFlg[FLAG_LEN+1];
	char   VchTyp[VCHTYP_LEN+1];
	char   VchNo[VCHNO_LEN+1];
	char   UdwDat[UDWDAT_LEN+1];
	char   Pin[PFAPIN_LEN+1];
	char   Smr[SMR_LEN+1];
	char   Pps[PPS_LEN+1];
	ETF	  *TmpNode=NULL;

	memset( CcyCod, 0, sizeof(CcyCod) );
	memset( CclTyp, 0, sizeof(CclTyp) );
	memset( ActNo,  0, sizeof(ActNo)  ) ;
	memset( PayAct, 0, sizeof(PayAct) ) ;
	memset( PyeAct, 0, sizeof(PyeAct) ) ;
	memset( CclNo,  0, sizeof(CclNo)) ;
	memset( CclAct, 0, sizeof(CclAct) );
	memset( TxnAmt, 0, sizeof(TxnAmt) );
	memset( HpcFlg, 0, sizeof(HpcFlg) );
	memset( VchTyp, 0, sizeof(VchTyp) );
	memset( VchNo,  0, sizeof(VchNo)  );
	memset( UdwDat, 0, sizeof(UdwDat) );
	memset( Pin,    0, sizeof(Pin)    );
	memset( Smr,    0, sizeof(Smr)    );
	memset( Pps,    0, sizeof(Pps)    );
	
	
	ret =bpGetArgument(args, "HpcFlg", HpcFlg, sizeof(HpcFlg) );
	if( ret )	{
		bpErrorLog(trdata, "GenHostGroupData: 取参数错[HpcFlg]");
		bpAddResult(TrNode, _SYSTEM_ERR, "前置系统错");
		return(-1);
	}
	hdelbothspace(HpcFlg);

	ret  = bpGetChildValue( TrNode, "CcyCod", CcyCod, CCYCOD_LEN+1 );
	ret += bpGetChildValue( TrNode, "CclNo",  CclNo,  CCLNO_LEN+1  );
	ret += bpGetChildValue( TrNode, "CclAct", CclAct, ACTNO_LEN+1  );
/**
	ret += bpGetChildValue( TrNode, "ActNo",  ActNo,  ACTNO_LEN+1  );
**/
	if( !memcmp(HpcFlg,"1",1) ) {
		ret += bpGetChildValue( TrNode, "PayAct",  PayAct,  ACTNO_LEN+1  );
	}
	else {
		ret += bpGetChildValue( TrNode, "PyeAct",  PyeAct,  ACTNO_LEN+1  );
	}
	bpGetChildValue( TrNode, "VchTyp", VchTyp, VCHTYP_LEN+1 );
	bpGetChildValue( TrNode, "VchNo",  VchNo,  VCHNO_LEN+1 );
	bpGetChildValue( TrNode, "UdwDat", UdwDat, UDWDAT_LEN+1 );
	bpGetChildValue( TrNode, "Pps",    Pps,    PPS_LEN+1 );

	memcpy(Smr, Pps, SMR_LEN);
	if( !memcmp(HpcFlg,"1",1) ) {
		bpTraceLog(trdata,"1 [%s]", HpcFlg);
		ret += bpGetChildValue( TrNode, "TxnAmt", TxnAmt, AMOUNT_LEN+1 );
	} else {
		bpTraceLog(trdata,"0 [%s]", HpcFlg);
		/*  ret += bpGetChildValue( TrNode, "AbsAmt",  TxnAmt,  AMOUNT_LEN+1 ); */
		ret += bpGetChildValue( TrNode, "TxnAmt", TxnAmt, AMOUNT_LEN+1 );
	}

	ret += bpGetChildValue( TrNode, "CclTyp", CclTyp, FLAG_LEN+1 );
	if( ret != 0 ) {
		bpAddResult(TrNode, _SYSTEM_ERR, "前置系统错");
		bpErrorLog(trdata, "502000: Get CcyCod,CclNo,CclAct,PayAct,PyeAct,TxnAmt,CclTyp Error!" );
		return(-1);
	}

	bpTraceLog(trdata,"CclTyp[%s]CclAct[%s]PayAct[%s]PyeAct[%s]TxnAmt[%s]",CclTyp,CclAct,PayAct,PyeAct,TxnAmt);
	bpTraceLog(trdata,"Smr[%s][%s][%s][%s]",VchNo,UdwDat,VchTyp,Smr);
	/* 付款 */
	if( !memcmp(HpcFlg,"1",1) ) {
		bpGetChildValue( TrNode, "Pin",   Pin, PFAPIN_LEN+1 );
		etfAddOrRepNode( TrNode, "InNum", "2", 1 );

		TmpNode = etfNewNode( "InRec_1", NULL, 0 );
		etfAddOrRepNode(TmpNode, "CcyCod", CcyCod, CCYCOD_LEN);
		etfAddOrRepNode(TmpNode, "CDFlg",  "0",    FLAG_LEN);
		etfAddOrRepNode(TmpNode, "RBFlg",  "0",    FLAG_LEN);
		etfAddOrRepNode(TmpNode, "TxnAmt", TxnAmt, AMOUNT_LEN);
		etfAddOrRepNode(TmpNode, "ActNo",  PayAct, ACTNO_LEN);
		etfAddOrRepNode(TmpNode, "CclNo",  " ",    FLAG_LEN);
		etfAddOrRepNode(TmpNode, "VchTyp", VchTyp, VCHTYP_LEN);
		etfAddOrRepNode(TmpNode, "VchNo",  VchNo,  VCHNO_LEN);
		etfAddOrRepNode(TmpNode, "UdwDat", UdwDat, UDWDAT_LEN);
		etfAddOrRepNode(TmpNode, "Pin",    Pin,    PFAPIN_LEN);
		etfAddOrRepNode(TmpNode, "Smr",    Smr,    SMR_LEN);

		etfAppendNode(TrNode, TmpNode);
		TmpNode = etfNewNode( "InRec_2",   NULL, 0 );
		etfAddOrRepNode(TmpNode, "CcyCod", CcyCod, CCYCOD_LEN);
		etfAddOrRepNode(TmpNode, "CDFlg",  "1",    FLAG_LEN);
		etfAddOrRepNode(TmpNode, "RBFlg",  "0",    FLAG_LEN);
		etfAddOrRepNode(TmpNode, "TxnAmt", TxnAmt, AMOUNT_LEN);
		etfAddOrRepNode(TmpNode, "ActNo",  CclAct, ACTNO_LEN);
		etfAddOrRepNode(TmpNode, "CclNo",  CclNo,  CCLNO_LEN);
		etfAddOrRepNode(TmpNode, "VchTyp", VchTyp, VCHTYP_LEN);
		etfAddOrRepNode(TmpNode, "VchNo",  VchNo,  VCHNO_LEN);
		etfAddOrRepNode(TmpNode, "UdwDat", UdwDat, UDWDAT_LEN);
		etfAddOrRepNode(TmpNode, "Pin",    Pin,    PFAPIN_LEN);
		etfAddOrRepNode(TmpNode, "Smr",    Smr,    SMR_LEN);
		etfAppendNode(TrNode, TmpNode);
	} else { 
		if (!memcmp(HpcFlg,"0",1) ) {  /* 收款 */
			etfAddOrRepNode(TrNode, "InNum",   "2",    1);
			TmpNode = etfNewNode( "InRec_1",   NULL,   0 );
			etfAddOrRepNode(TmpNode, "CcyCod", CcyCod, CCYCOD_LEN);
			etfAddOrRepNode(TmpNode, "CDFlg",  "0",    FLAG_LEN);
			etfAddOrRepNode(TmpNode, "RBFlg",  "0",    FLAG_LEN);
			etfAddOrRepNode(TmpNode, "TxnAmt", TxnAmt, AMOUNT_LEN);
			etfAddOrRepNode(TmpNode, "ActNo",  CclAct, ACTNO_LEN);
			etfAddOrRepNode(TmpNode, "CclNo",  CclNo,  CCLNO_LEN);
			etfAddOrRepNode(TmpNode, "Smr",    Smr,    SMR_LEN);
			etfAppendNode(TrNode, TmpNode);
    	
			TmpNode = etfNewNode( "InRec_2", NULL, 0 );
			etfAddOrRepNode(TmpNode, "CcyCod", CcyCod, CCYCOD_LEN);
			etfAddOrRepNode(TmpNode, "CDFlg", "1",     FLAG_LEN);
			etfAddOrRepNode(TmpNode, "RBFlg", "0",     FLAG_LEN);
			etfAddOrRepNode(TmpNode, "TxnAmt", TxnAmt, AMOUNT_LEN);
			etfAddOrRepNode(TmpNode, "ActNo",  PyeAct,  ACTNO_LEN);
			etfAddOrRepNode(TmpNode, "CclNo", " ",     FLAG_LEN);
			etfAddOrRepNode(TmpNode, "VchTyp", VchTyp, VCHTYP_LEN);
			etfAddOrRepNode(TmpNode, "VchNo",  VchNo,  VCHNO_LEN);
			etfAddOrRepNode(TmpNode, "UdwDat", UdwDat, UDWDAT_LEN);
			etfAddOrRepNode(TmpNode, "Smr",    Smr,    SMR_LEN);
			etfAppendNode(TrNode, TmpNode);
		} else {
			bpErrorLog(trdata, "GenHostGroupData: 参数值错[HpcFlg]");
			bpAddResult(TrNode, _SYSTEM_ERR, "前置系统错");
			return(-1);
		}
	}
	return(0);
}
/******************************************************************************
  Function		: DelNode
  Description	        : 删除多余节点
  Calls                 : 
  Called By             : 任何包含该库的程序 
  Table Accessed        : 
  Table Updated	        : 无
  Input			: ETF           *TrNode	   --ETF报文树 
			  ST_TranData   *trdata	   --交易结构
			  PbItemData    *args	   --参数  
			  DBConHandle   *DBHandle  --数据库句柄   
  Output		:    
  Return		: 0--成功 小于0--失败   
  Others		: 无             
******************************************************************************/
int DelNode(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	int	ret=0;
	int	i=0;
	
	if( Step_Args_Num < 1 )
    {
        bpAddResult(TrNode, _GET_PARA_ERR, "没有参数！");
        bpErrorLog(trdata, "DelNode:错误，没有参数！");
        return ( -1 );
    }

	for( i=0; i<Step_Args_Num; i++)
	{
		hdelbothspace(args.data[i]);
		ret = etfDelNode(TrNode, args.data[i]);
		bpTraceLog(trdata, "DelNode [%s][%d]", args.data[i], ret);
	}

	return(0);
}

/******************************************************************************
  Function		: DEBUG
  Description	: 
  Calls         : 
  Called By     : 任何包含该库的程序
  Table Accessed:
  Table Updated	: 无
  Input			: ETF		  * TrNode		--ETF报文树
				  TranData * trdata	    	--交易结构
				  PbItemData args			--参数
				  DBConHandle * DBHandle	--数据库句柄
  Output		:
  Return		: -1 :错误
				  0 ：正确
  Others		: 无
******************************************************************************/
int PFADEBUG(ETF *TrNode, TranData *trdata, PbItemData args, DBConHandle *DBHandle )
{

	int	i;
	char tmp[128];
	
	for( i=0; i<Step_Args_Num; i++ )
	{
		memset( tmp, 0, sizeof(tmp) );
/*
		etfGetChildValue(TrNode, args.data[i], tmp, 128+1);
*/
		etfGetValue(TrNode, args.data[i], tmp, 128+1);
		bpTraceLog( trdata, "节点[%s] 值[%s]", args.data[i], tmp);
	}
	return(0);
}

/******************************************************************************
  Function				: 账号户名信息追加函数
  Description	        : 根据柜员的输入追加或更新账号户名信息表
  Calls                 : 被本函数调用的函数清单
  Called By             : 调用本函数的函数清单
  Table Accessed        : besactnam
  Table Updated	        : besactnam
  Input					: ETF *TrNode	输入树
			  			ST_TranData* trdata	公共结构
			  			char* args	参数
			  			DBConHandle* DBHandle	数据库句柄
  Output				: 对输出参数的说明。
  Return				: 0--成功 小于0--失败
  Others				: 其它说明
******************************************************************************/
int AppActInf(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;
	char aActNo[RECV_ACCT_LEN+1];     /*账号*/
	char aActNam[RECV_NAME_LEN+1];    /*户名*/
	EXEC SQL END DECLARE SECTION;
	int  iRet;

	/* 初始化数据*/
	memset(aActNo,0x00,sizeof(aActNo));
	memset(aActNam,0x00,sizeof(aActNam));
	iRet=0;

	/*设置数据库上下文*/
    iRet=bpSetDBContext(DBHandle);
    if (iRet<0)
    {
    	bpAddResult(TrNode, _DB_OPER_ERR, "设置数据库上下文错误" );
    	bpErrorLog(trdata,"634017: 执行usfSetDBContext函数错误");
    	return(-1);
    }

	/* 从ETF树中获得账号*/
	etfGetValue(TrNode, "ActNo",  aActNo, RECV_ACCT_LEN+1);
	if (aActNo[0] == 0x00)
	{
		bpAddResult(TrNode, _ETF_GET_ERR, "获取ETF节点错误" );
		bpErrorLog(trdata,"634018: 获取ETF节点错误 节点名[%s]","ActNo");
		return( -1 );
	}


	/* 从ETF树中获得户名*/
	etfGetValue(TrNode, "ActNam",  aActNam, RECV_NAME_LEN+1);
	if (aActNam[0] == 0x00)
	{
		bpAddResult(TrNode, _ETF_GET_ERR, "获取ETF节点错误" );
		bpErrorLog(trdata,"634019: 获取ETF节点错误 节点名[%s]","ActNam");
		return( -1 );
	}

	/* 追加账号户名信息 */
	EXEC SQL UPDATE besactnam SET ActNam= :aActNam WHERE ActNo=:aActNo;
	if( SQLCODE == SQL_NOTFOUND)
	{
		EXEC SQL INSERT INTO besactnam VALUES(:aActNo,:aActNam);
		if( SQLCODE != 0)
		{
			bpAddResult(TrNode, _DB_EXEC_ERR, "执行数据库命令串错误" );
			bpErrorLog(trdata,"634020: 数据库错误[%d] [%s]", SQLCODE, SQLERRMSG);
			EXEC SQL ROLLBACK WORK;
			return( -1 );
		}
		EXEC SQL COMMIT WORK;
	}
	else
	{
			if (SQLCODE != 0)
			{
				bpAddResult(TrNode, _DB_EXEC_ERR, "执行数据库命令串错误" );
				bpErrorLog(trdata,"634021: 数据库错误[%d] [%s]", SQLCODE, SQLERRMSG);
				EXEC SQL ROLLBACK WORK;
				return( -1 );
			}
		EXEC SQL COMMIT WORK;
	}

	bpAddResult(TrNode, _SUCCEED, "交易成功");
	return(0);
}


/******************************************************************************
  Function      : ParsePrvData
  Description   : 将数据流转换成ETF树上的节点
  Calls         : BufToETF
  Called By     : 任何包含该库的程序
  Table Accessed:
  Table Updated : 无
  Input         : char   *Buf     --输入数据流
                  int    DataLen  --数据长度
  Output        : 
  Return        : NULL       失败
                  NOT NULL   成功
  Others        : 无
******************************************************************************/
int ParsePrvData(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	int	   ret=0;
	ETF	   *TmpNode=NULL;
	char   sBuf[BufLen+1];
	char   sArgNam[ArgNamLen+1];

	if( Step_Args_Num != 1 ) {
		bpAddResult(TrNode, _GET_PARA_ERR, "传入参数个数错误！");
		bpErrorLog(trdata, "传入参数个数错误！");
		return ( -1 );
	}

	ClearStr( sBuf );
	ClearStr( sArgNam );
	snprintf( sArgNam, sizeof(sArgNam), "%s", Step_Arg1 );

	etfAddOrRepNode( TrNode, "ArgNam", sArgNam, ArgNamLen+1);
	etfGetValue( TrNode, sArgNam, sBuf, BufLen+1 );

	ret = strlen(sBuf);
	TmpNode = (ETF *)BufToETF(sBuf, ret);
	if( TmpNode == NULL ) {
		bpAddResult(TrNode, _GET_PARA_ERR, "将数据流转换成ETF树错误！");
		bpErrorLog(trdata, "将数据流转换成ETF树错误！");
		return ( -1 );
	}

	etfCombineReplace(TrNode, TmpNode);
	bpFreeEtf(TmpNode);
	return(0);
}
/******************************************************************************
  Function		    : GenHostGroupFilData
  Description     : 生成主机补充接口数据
  Calls           : 
  Called By       : 任何包含该库的程序 
  Table Accessed  : 
  Table Updated   : 无
  Input           : ETF   *TrNode	   --ETF报文树 
                    ST_TranData   *trdata	   --交易结构
			              PbItemData    *args	   --参数  
			              DBConHandle   *DBHandle  --数据库句柄   
  Output		:    
  Return		: 0--成功 小于0--失败   
  Others		: 无             
******************************************************************************/
int GenHostGroupFilData(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;
	EXEC SQL END DECLARE SECTION;
		char   sMaxRec[MaxRecLen+1];
		char   sRecNum[RecNumLen+1];
		char   sRecNam[RecNamLen+1];
		int		 iRecNum=0;
		ETF	   *DataNode=NULL;

/*
**	设置跟踪信息
*/
	bpTraceLog( trdata, "Begin GenCrdDtlData." );
/*
**	检查参数个数
*/
	if( Step_Args_Num != 2 ) {
		bpAddResult( TrNode, "PFA999", "参数个数错" );
		bpErrorLog( trdata, "GenCrdDtlData: 参数个数错!" );
		return( -1 );
	}
	ClearStr( sRecNum );
	ClearStr( sMaxRec );
	strcpy( sRecNum, Step_Arg1 );
	strcpy( sMaxRec, Step_Arg2 );
	iRecNum=atoi(sRecNum);
	for( ; ; ) {
/*
**	当获得记录数(iRecNum)等于每次查询最大记录数时，结束查询
*/
		if( iRecNum==atoi(sMaxRec) ) break;
		iRecNum++;
		ClearStr( sRecNam );
		sprintf( sRecNam, "Rec_%d", iRecNum );
		DataNode = etfNewNode( sRecNam, NULL, 0 );
		etfAddOrRepNode(DataNode, "BVchTp", "", BVchTpLen);
		etfAddOrRepNode(DataNode, "BegNo" , "00000000", VchNoLen);
		etfAddOrRepNode(DataNode, "EndNo" , "00000000", VchNoLen);
		etfAddOrRepNode(DataNode, "Count" , "000", CountLen);
		etfAddOrRepNode(DataNode, "TotAmt", "000000000000000", AmtLen);
		etfAddOrRepNode(DataNode, "WrkFee", "000000000000000", AmtLen);
		etfAddOrRepNode(DataNode, "FeeCod", "", FeeCodLen );
		etfAddOrRepNode(DataNode, "HndFee", "000000000000000", AmtLen);
		etfAppendNode(TrNode, DataNode);
	}
	sprintf( sRecNum, "%d", iRecNum );
	etfAddOrRepNode( TrNode, "RecNum", sRecNum, RecNumLen );
	bpAddResult(TrNode, "000000", "交易成功" );
	bpTraceLog( trdata, "End GenHostGroupFilData.\n" );
	return 0;
}
