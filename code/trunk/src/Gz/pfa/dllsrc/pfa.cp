/******************************************************************************
			Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name   : pfa.cp
 Author      : ��Ӧ��
 Version     : 1.0  
 Date        : 2004.04.13  
 Description : �������֧��Ӧ�ø���ԭ�Ӻ����� 
 History		 :


  No.	Date		Author		Modification
  ===	==========	========	============================
   1   20061205    Jamez
******************************************************************************/
#include "hipfa.h"
/******************************************************************************
  Function      : GenPrvData
  Description   : ��ETF���ϵĽڵ�ת����������
  Calls         : ETFToBuf
  Called By     : �κΰ����ÿ�ĳ���
  Table Accessed:
  Table Updated : ��
  Input         : ETF    *ETFRoot    --ETF��
  Output        : char   *Buf     --���������?
                  int    MaxLen   --������󳤶�
  Return        : 0--�ɹ� 
                  С��0--ʧ��
  Others        : ���Ҫ����Group�ڵ�,������������GrpNam
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
		bpAddResult(TrNode, _GET_PARA_ERR, "������������Ϊ�㣡");
		bpErrorLog(trdata, "������������Ϊ�㣡");
		return ( -1 );
	}

	EtfNode = etfNewNode( "ROOT", "111", 3 );
	if( EtfNode == NULL ) {
		bpErrorLog(trdata, "�����ڵ�����RootNode��ʧ�ܣ�");
		bpAddResult(TrNode, _PRE_OTHER_ERR, "�����ڵ�����RootNode��ʧ�ܣ�");
		return(-1);
	}

	for( i=0; i<Step_Args_Num; i++ ) {
		if( !strcmp(args.item_name[i], "GrpNam") ) {
			for( j=1; ;j++ ) {
				hsnprintf(sRecNam, sizeof(sRecNam), "%s_%d", args.data[i], j);
				TmpNode = etfGetChildNode(TrNode, NULL, sRecNam);
				if( TmpNode == NULL ) {
					bpErrorLog(trdata,"��ʾ��Ϣ��������GrpNam��λ�á�%d��,��Ρ�%d����", i,j);
					break;
				}
				CloneNode = etfCloneNode(TmpNode);
				if( CloneNode == NULL ) {
					bpErrorLog(trdata,"���鸴�ƽڵ�����TmpNode��ʧ�ܣ�");
					bpAddResult(TrNode, _PRE_OTHER_ERR, "���鸴�ƽڵ�����TmpNode��ʧ�ܣ�");
					return(-1);
				}
				if( NULL == etfAppendNode( EtfNode, CloneNode ) ) {
					bpErrorLog(trdata,"����׷�ӽڵ�����TmpNod������EtfNode��ʧ�ܣ�");
					bpAddResult(TrNode, _PRE_OTHER_ERR, "����׷�ӽڵ�����TmpNod������EtfNode��ʧ�ܣ�");
					etfDelAllNode(CloneNode);
					return(-1);
				}
			}
		} else {
			TmpNode = etfGetChildNode(TrNode, NULL, args.data[i]);
			if( TmpNode == NULL ) {
				bpErrorLog(trdata,"��ȡ�����ڵ�ֵ��%s��ʧ�ܣ�",args.data[i]);
				bpAddResult(TrNode, _PRE_OTHER_ERR, "��ȡ�����ڵ�ֵʧ�ܣ�");
				return(-1);
			}
			CloneNode = etfCloneNode(TmpNode);
			if( CloneNode == NULL ) {
				bpErrorLog(trdata,"���Ƶ����ڵ�ֵ��%s��ʧ�ܣ�",args.data[i]);
				bpAddResult(TrNode, _PRE_OTHER_ERR, "���Ƶ����ڵ�ֵʧ�ܣ�");
				return(-1);
			}
			if( NULL == etfAppendNode( EtfNode, CloneNode ) ) {
				bpErrorLog(trdata,"׷�ӵ����ڵ�ֵ��CloneNode������EtfNode��ʧ�ܣ�");
				bpAddResult(TrNode, _PRE_OTHER_ERR, "׷�ӵ����ڵ�ֵ��CloneNode������EtfNode��ʧ�ܣ�");
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
		bpErrorLog(trdata,"����EtfNode����ת����������ʧ�ܣ�");
		bpAddResult(TrNode, _PRE_OTHER_ERR, "����EtfNode����ת����������ʧ�ܣ�");
		return(-1);
	}
	etfAddOrRepNode( TrNode, "PrvDat", sBuf, BufLen );
	bpTraceLog( trdata, "End GenPrvData.\n" );
	return(0);
}

/******************************************************************************
  Function		: GenHostGroupData
  Description	        : ���������������ʽӿ�����
  Calls                 : 
  Called By             : �κΰ����ÿ�ĳ��� 
  Table Accessed        : 
  Table Updated	        : ��
  Input			: ETF           *TrNode	   --ETF������ 
			  ST_TranData   *trdata	   --���׽ṹ
			  PbItemData    *args	   --����  
			  DBConHandle   *DBHandle  --���ݿ���   
  Output		:    
  Return		: 0--�ɹ� С��0--ʧ��   
  Others		: ��             
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
		bpErrorLog(trdata, "GenHostGroupData: ȡ������[HpcFlg]");
		bpAddResult(TrNode, _SYSTEM_ERR, "ǰ��ϵͳ��");
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
		bpAddResult(TrNode, _SYSTEM_ERR, "ǰ��ϵͳ��");
		bpErrorLog(trdata, "502000: Get CcyCod,CclNo,CclAct,PayAct,PyeAct,TxnAmt,CclTyp Error!" );
		return(-1);
	}

	bpTraceLog(trdata,"CclTyp[%s]CclAct[%s]PayAct[%s]PyeAct[%s]TxnAmt[%s]",CclTyp,CclAct,PayAct,PyeAct,TxnAmt);
	bpTraceLog(trdata,"Smr[%s][%s][%s][%s]",VchNo,UdwDat,VchTyp,Smr);
	/* ���� */
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
		if (!memcmp(HpcFlg,"0",1) ) {  /* �տ� */
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
			bpErrorLog(trdata, "GenHostGroupData: ����ֵ��[HpcFlg]");
			bpAddResult(TrNode, _SYSTEM_ERR, "ǰ��ϵͳ��");
			return(-1);
		}
	}
	return(0);
}
/******************************************************************************
  Function		: DelNode
  Description	        : ɾ������ڵ�
  Calls                 : 
  Called By             : �κΰ����ÿ�ĳ��� 
  Table Accessed        : 
  Table Updated	        : ��
  Input			: ETF           *TrNode	   --ETF������ 
			  ST_TranData   *trdata	   --���׽ṹ
			  PbItemData    *args	   --����  
			  DBConHandle   *DBHandle  --���ݿ���   
  Output		:    
  Return		: 0--�ɹ� С��0--ʧ��   
  Others		: ��             
******************************************************************************/
int DelNode(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	int	ret=0;
	int	i=0;
	
	if( Step_Args_Num < 1 )
    {
        bpAddResult(TrNode, _GET_PARA_ERR, "û�в�����");
        bpErrorLog(trdata, "DelNode:����û�в�����");
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
  Called By     : �κΰ����ÿ�ĳ���
  Table Accessed:
  Table Updated	: ��
  Input			: ETF		  * TrNode		--ETF������
				  TranData * trdata	    	--���׽ṹ
				  PbItemData args			--����
				  DBConHandle * DBHandle	--���ݿ���
  Output		:
  Return		: -1 :����
				  0 ����ȷ
  Others		: ��
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
		bpTraceLog( trdata, "�ڵ�[%s] ֵ[%s]", args.data[i], tmp);
	}
	return(0);
}

/******************************************************************************
  Function				: �˺Ż�����Ϣ׷�Ӻ���
  Description	        : ���ݹ�Ա������׷�ӻ�����˺Ż�����Ϣ��
  Calls                 : �����������õĺ����嵥
  Called By             : ���ñ������ĺ����嵥
  Table Accessed        : besactnam
  Table Updated	        : besactnam
  Input					: ETF *TrNode	������
			  			ST_TranData* trdata	�����ṹ
			  			char* args	����
			  			DBConHandle* DBHandle	���ݿ���
  Output				: �����������˵����
  Return				: 0--�ɹ� С��0--ʧ��
  Others				: ����˵��
******************************************************************************/
int AppActInf(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;
	char aActNo[RECV_ACCT_LEN+1];     /*�˺�*/
	char aActNam[RECV_NAME_LEN+1];    /*����*/
	EXEC SQL END DECLARE SECTION;
	int  iRet;

	/* ��ʼ������*/
	memset(aActNo,0x00,sizeof(aActNo));
	memset(aActNam,0x00,sizeof(aActNam));
	iRet=0;

	/*�������ݿ�������*/
    iRet=bpSetDBContext(DBHandle);
    if (iRet<0)
    {
    	bpAddResult(TrNode, _DB_OPER_ERR, "�������ݿ������Ĵ���" );
    	bpErrorLog(trdata,"634017: ִ��usfSetDBContext��������");
    	return(-1);
    }

	/* ��ETF���л���˺�*/
	etfGetValue(TrNode, "ActNo",  aActNo, RECV_ACCT_LEN+1);
	if (aActNo[0] == 0x00)
	{
		bpAddResult(TrNode, _ETF_GET_ERR, "��ȡETF�ڵ����" );
		bpErrorLog(trdata,"634018: ��ȡETF�ڵ���� �ڵ���[%s]","ActNo");
		return( -1 );
	}


	/* ��ETF���л�û���*/
	etfGetValue(TrNode, "ActNam",  aActNam, RECV_NAME_LEN+1);
	if (aActNam[0] == 0x00)
	{
		bpAddResult(TrNode, _ETF_GET_ERR, "��ȡETF�ڵ����" );
		bpErrorLog(trdata,"634019: ��ȡETF�ڵ���� �ڵ���[%s]","ActNam");
		return( -1 );
	}

	/* ׷���˺Ż�����Ϣ */
	EXEC SQL UPDATE besactnam SET ActNam= :aActNam WHERE ActNo=:aActNo;
	if( SQLCODE == SQL_NOTFOUND)
	{
		EXEC SQL INSERT INTO besactnam VALUES(:aActNo,:aActNam);
		if( SQLCODE != 0)
		{
			bpAddResult(TrNode, _DB_EXEC_ERR, "ִ�����ݿ��������" );
			bpErrorLog(trdata,"634020: ���ݿ����[%d] [%s]", SQLCODE, SQLERRMSG);
			EXEC SQL ROLLBACK WORK;
			return( -1 );
		}
		EXEC SQL COMMIT WORK;
	}
	else
	{
			if (SQLCODE != 0)
			{
				bpAddResult(TrNode, _DB_EXEC_ERR, "ִ�����ݿ��������" );
				bpErrorLog(trdata,"634021: ���ݿ����[%d] [%s]", SQLCODE, SQLERRMSG);
				EXEC SQL ROLLBACK WORK;
				return( -1 );
			}
		EXEC SQL COMMIT WORK;
	}

	bpAddResult(TrNode, _SUCCEED, "���׳ɹ�");
	return(0);
}


/******************************************************************************
  Function      : ParsePrvData
  Description   : ��������ת����ETF���ϵĽڵ�
  Calls         : BufToETF
  Called By     : �κΰ����ÿ�ĳ���
  Table Accessed:
  Table Updated : ��
  Input         : char   *Buf     --����������
                  int    DataLen  --���ݳ���
  Output        : 
  Return        : NULL       ʧ��
                  NOT NULL   �ɹ�
  Others        : ��
******************************************************************************/
int ParsePrvData(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	int	   ret=0;
	ETF	   *TmpNode=NULL;
	char   sBuf[BufLen+1];
	char   sArgNam[ArgNamLen+1];

	if( Step_Args_Num != 1 ) {
		bpAddResult(TrNode, _GET_PARA_ERR, "���������������");
		bpErrorLog(trdata, "���������������");
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
		bpAddResult(TrNode, _GET_PARA_ERR, "��������ת����ETF������");
		bpErrorLog(trdata, "��������ת����ETF������");
		return ( -1 );
	}

	etfCombineReplace(TrNode, TmpNode);
	bpFreeEtf(TmpNode);
	return(0);
}
/******************************************************************************
  Function		    : GenHostGroupFilData
  Description     : ������������ӿ�����
  Calls           : 
  Called By       : �κΰ����ÿ�ĳ��� 
  Table Accessed  : 
  Table Updated   : ��
  Input           : ETF   *TrNode	   --ETF������ 
                    ST_TranData   *trdata	   --���׽ṹ
			              PbItemData    *args	   --����  
			              DBConHandle   *DBHandle  --���ݿ���   
  Output		:    
  Return		: 0--�ɹ� С��0--ʧ��   
  Others		: ��             
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
**	���ø�����Ϣ
*/
	bpTraceLog( trdata, "Begin GenCrdDtlData." );
/*
**	����������
*/
	if( Step_Args_Num != 2 ) {
		bpAddResult( TrNode, "PFA999", "����������" );
		bpErrorLog( trdata, "GenCrdDtlData: ����������!" );
		return( -1 );
	}
	ClearStr( sRecNum );
	ClearStr( sMaxRec );
	strcpy( sRecNum, Step_Arg1 );
	strcpy( sMaxRec, Step_Arg2 );
	iRecNum=atoi(sRecNum);
	for( ; ; ) {
/*
**	����ü�¼��(iRecNum)����ÿ�β�ѯ����¼��ʱ��������ѯ
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
	bpAddResult(TrNode, "000000", "���׳ɹ�" );
	bpTraceLog( trdata, "End GenHostGroupFilData.\n" );
	return 0;
}
