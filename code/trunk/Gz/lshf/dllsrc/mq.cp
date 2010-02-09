#include <sql.h>
/**
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <math.h>
*/
#include "hibase.h"
#include "hionline.h"
#include "hidatabase.h"
#include "hibusmsg.h"
#include "hibppubdef.h"
#include "hipex.h"
#include "MQCServer.h"
#include "MQCQueue.h"
#include "MQCSession.h"
#include "MQCMsg.h"

#define ClearStr(str) memset(str,'\0',sizeof(str))

HMQServer	hMQServer = NULL;
HMQQueue	hSendQ = NULL;
HMQQueue	hRecvQ = NULL;
HMQMsg		hSendMsg = NULL;
HMQMsg		hRecvMsg = NULL;
HMQSession	hMQSession = NULL;

/* MQ������IP */
char	MqSysConf[200];
char	MqAddress[30];
/* �˿ں� */
char	MqPort[10];
/* �û��� */
char	MqUserName[20];
/* ���� */
char	MqPassWord[20];
char	MqSendName[20];
char	MqRecvName[20];
char	 sSendBuf[1024];
char	 sRevBuf[1024];

char	Msg[80];
/******************************************************************************
	Function          : MqLoginandPay
	Description       : ������ͨ����ǩ���ͳ�ֵ
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : 
	Table Updated	    : ��
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
					  3 ������( ǰ��λ�̶�Ϊ MQ������IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName )
					  2 : ������
					  3 : ��ֵ������
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int MqLoginandPay(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	char    sSend[1024];
	int		ret;
	char    sRev[1024];
	char tmp[1024];
  	

	ClearStr( sSend );
	ClearStr( sRev );
	ClearStr( sSendBuf );
	ClearStr( sRevBuf );
	ClearStr( MqSysConf );
	ClearStr( tmp );
	
	
	strcpy( MqSysConf, Step_Arg1 );
	strcpy( sSend, Step_Arg2 );
	
	memcpy( tmp , sSend ,4 );
	bpErrorLog( trdata, "FILE[%s] LINE[%d][%s] ",__FILE__,__LINE__,tmp);
  if((strcmp(tmp,"0800")==0)||(strcmp(tmp,"0801")==0)||(strcmp(tmp,"0203")==0)||(strcmp(tmp,"0200")==0)||(strcmp(tmp,"0201")==0))
 		bpErrorLog( trdata, "FILE[%s] LINE[%d][%s] ",__FILE__,__LINE__,tmp); 
	else 
	{
    bpErrorLog( trdata, "FILE[%s] LINE[%d] ���Ĵ���!",__FILE__,__LINE__);
    etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
    return (-1);
  }	
	SetMqSysConf( MqSysConf );
	sprintf(sSendBuf,"|4000|%s|",sSend);
/*	if(strcmp(tmp,"0200")==0)
	{
		bpErrorLog( trdata, "FILE[%s] LINE[%d],test\n",__FILE__,__LINE__);
    etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
    return (-1);
	}
*/
	bpErrorLog( trdata, " FILE[%s] LINE[%d]sSendBuf [%s]!",__FILE__,__LINE__,sSendBuf);
	ret = MqTrans(trdata,sSendBuf,sRevBuf);
	if(ret)
	{
		 bpErrorLog( trdata, " FILE[%s] LINE[%d]���н���ʧ�� [%s]!",__FILE__,__LINE__,Msg);
		 etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		 return (-1);
	}
/*	if(strcmp(tmp,"0200")==0)
  {
    bpErrorLog( trdata, "FILE[%s] LINE[%d],test\n",__FILE__,__LINE__);
    etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
    return (-1);
  }*/	
	strcpy( sRev, sRevBuf );
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] sRev[%s]!",__FILE__,__LINE__,sRev);
	bpErrorLog( trdata, "FILE[%s] LINE[%d] ���׳ɹ�!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	etfAddOrRepNode( TrNode, "sRev", sRev, sizeof(sRev));

	return (0);

}
/******************************************************************************
	Function          : MqSingIn
	Description       : ������ͨ����ǩ������
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : 
	Table Updated	    : ��
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
					  8 ������( ǰ��λ�̶�Ϊ MQ������IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName )
					  2 : ��ֵǩ����
					  3 : IP��ַ
					  4 : �ն˱��
					  5 : ���׽��
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int MqSingIn(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;
		char	 sDate[8+1]; /* ���� */
		char	 sStatus[1+1]; /* ״̬ */
	EXEC SQL END DECLARE SECTION;
		char	 sCode[4+1]; /* ǩ���� */
		char	 sAddress[15+1]; /* IP��ַ */
		char	 sTermNo[12+1];
		char	 ReturnCode[1+1];
		char	 MaxPay[5+1];
		char	 sTransje[15];
		char	 sBalance[10];
		char	 sTemp[10];
		long	 sTemp1;
		long	 sTemp2;
		long	 sTemp3;
  		int		 ret;

	ClearStr( sDate );
	ClearStr( sStatus );
	ClearStr( sCode );
	ClearStr( sAddress );
	ClearStr( sTermNo );
	ClearStr( sSendBuf );
	ClearStr( sRevBuf );
	ClearStr( MqSysConf );
	ClearStr( ReturnCode );
	ClearStr( MaxPay ); 
	ClearStr( sTransje );
	ClearStr( sBalance );
	ClearStr( sTemp );
	
	strcpy( MqSysConf, Step_Arg1 );
	strcpy( sCode, Step_Arg2 );
	strcpy( sAddress, Step_Arg3 );
	strcpy( sTermNo, Step_Arg4 );
	strcpy( sTransje,Step_Arg5 );
	strcpy( sBalance,Step_Arg6 );
	
	SetMqSysConf( MqSysConf );
	
	sprintf(sSendBuf,"|%s|%s|%s|",sCode,sAddress,sTermNo);
	/* ���г�ֵǩ������ */
	
	ret = MqTrans(trdata,sSendBuf,sRevBuf);
	if(ret)
	{
		bpErrorLog( trdata, "���г�ֵǩ������ʧ�� [%s]!",Msg);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}
		
	
	/* ����ǩ�����׷��� */
	memcpy(ReturnCode,sRevBuf,1);
	memcpy(MaxPay,sRevBuf+1,5);

	if( ReturnCode[0] != '0' )
	{
		bpErrorLog( trdata, "ǩ��ʧ��,����ϵ��ͨ����˾! [%s]",ReturnCode);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}

	/* ����ֵ����Ƿ��������  */
	if( atol(sTransje)/100 > atol(MaxPay) )
	{
		bpErrorLog( trdata, "���׽���������! ");
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}

	/* �������ת�� */
	sprintf(sTemp,"%08.8d",strtol(sBalance,NULL,16));
	etfAddOrRepNode( TrNode, "RsFld1", sTemp, 8 );
	sTemp1 = atol(sTemp);
	sTemp2 = atol(sTransje);
	sTemp3 = sTemp1 + sTemp2;
	
	ClearStr( sTemp );

	sprintf( sTemp ,"%08.8d",sTemp3);
	etfAddOrRepNode( TrNode, "RsFld2", sTemp, 8 );
	bpErrorLog( trdata, "FILE[%s] LINE[%d] ��ֵǩ���ɹ�!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	return (0);

}
/******************************************************************************
	Function          : MqQuery
	Description       : ������ͨ���г�ֵ���˲�ѯ
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : 
	Table Updated	    : ��
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
					  3 ������( ǰ��λ�̶�Ϊ MQ������IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName )
					  2 : ������
					  3 : ��ֵ������
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int MqQuery(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	
	
	char	sCmd[4+1];
	char	sCardNo[16+1];
	char	sReturnCode[1+1];
	char	sReturnMoney[8+1];
	char	sReturnMoney1[8+1];
	int		ret;
	int		sTemp;
  	

	ClearStr( sCmd );
	ClearStr( sCardNo );
	ClearStr( sReturnCode );
	ClearStr( sReturnMoney );
	ClearStr( sSendBuf );
	ClearStr( sRevBuf );
	ClearStr( MqSysConf );
	ClearStr( sReturnMoney1 );
	
	
	strcpy( MqSysConf, Step_Arg1 );
	strcpy( sCmd, Step_Arg2 );
	strcpy( sCardNo, Step_Arg3 );

	SetMqSysConf( MqSysConf );
	
	sprintf(sSendBuf,"|%4.4s|%16.16s|",sCmd,sCardNo);
	/* ���г�ֵ���˲�ѯ���� */
	
	ret = MqTrans(trdata,sSendBuf,sRevBuf);
	if(ret)
	{
		 bpErrorLog( trdata, " FILE[%s] LINE[%d]���г�ֵ���˲�ѯʧ�� [%s]!",__FILE__,__LINE__,Msg);
		 etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		 return (-1);
	}
	

	
	memcpy( sReturnCode, sRevBuf , 1 );
	etfAddOrRepNode( TrNode, "RsFld3", sReturnMoney, 8 );
	memcpy( sReturnMoney ,sRevBuf+1,8 );
	
	
	/*
	if( sReturnCode[0] != '0' )
	{
		bpErrorLog( trdata, "��ֵ���˲�ѯ����ʧ��! [%s] [%s]",sCardNo,sReturnCode);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);		
	}
	*/
	
	sTemp = atof(sReturnMoney) * 100;
	sprintf(sReturnMoney1,"%d",sTemp );
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] sReturnMoney1[%s]!",__FILE__,__LINE__,sReturnMoney1);
	sprintf(sReturnMoney,"%08.8d",atol(sReturnMoney1));


	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] ��ֵ���˲�ѯ�ɹ�!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	etfAddOrRepNode( TrNode, "ReturnMoney", sReturnMoney, 8);

	return (0);

}
/******************************************************************************
	Function          : MqPayQue
	Description       : ������ͨ���г�ֵ����
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : 
	Table Updated	    : ��
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
					  17 ������( ǰ��λ�̶�Ϊ MQ������IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName)
					  2 : ��ֵ;����
					  3 : ����������
					  4 : �����������
					  5 : ��ֵ�����к�
					  6 : ��ֵ�ն˱���
					  7 : ��ֵ����ǰ���
					  8 : ��ֵ����ǰ�����������к�
					  9 : ��ֵ����ǰ�ѻ��������к�
					 10 : ������Կ�汾
					 11 : �����㷨�汾
					 12 : �����
					 13 : MAC1��
					 14 : ��ֵ���
					 15 : ���˽��
					 16 : ����Ա���
					 17 : IP��ַ
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int MqPayQue(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	
	
	char	sPayChangel[4+1];
	char	sTransType[2+1];
	char	sCmd[4+1];
	char	sCardNo[16+1];
	char	sTermNo[12+1];
	char	sBalance[8+1];
	char	sConnectNo[4+1];
	char	sNoConnectNo[4+1];
	char	sEdition[2+1];
	char	sArith[2+1];
	char	sRanDom[8+1];
	char	sMAC1[8+1];
	char	sTransMoney[8+1];
	char	sReturnMoney[8+1];
	char	sIdNo[16+1];
	char	sAddress[15+1];
	char	sReturnCode[1+1];
	char	sDataHead[4+1];
	char	sMAC2[12+1];
	char	sPayDateTime[14+1];
	int		ret;
  	

	ClearStr( sPayChangel );
	ClearStr( sTransType );
	ClearStr( sCmd );
	ClearStr( sCardNo );
	ClearStr( sTermNo );
	ClearStr( sBalance );
	ClearStr( sConnectNo );
	ClearStr( sNoConnectNo );
	ClearStr( sEdition );
	ClearStr( sArith );
	ClearStr( sRanDom );
	ClearStr( sMAC1 );
	ClearStr( sTransMoney );
	ClearStr( sReturnMoney );
	ClearStr( sIdNo );
	ClearStr( sAddress );
	ClearStr( sSendBuf );
	ClearStr( sRevBuf );
	ClearStr( sReturnCode );
	ClearStr ( sDataHead );
	ClearStr ( sMAC2 );
	ClearStr ( sPayDateTime );
	ClearStr( MqSysConf );
	
	
	strcpy( MqSysConf, Step_Arg1 );
	strcpy( sPayChangel, Step_Arg2 );
	strcpy( sTransType, Step_Arg3 );
	strcpy( sCmd, Step_Arg4 );
	strcpy( sCardNo, Step_Arg5 );
	strcpy( sTermNo, Step_Arg6 );
	strcpy( sBalance, Step_Arg7 );
	strcpy( sConnectNo, Step_Arg8 );
	strcpy( sNoConnectNo, Step_Arg9 );
	strcpy( sEdition, Step_Arg10 );
	strcpy( sArith, Step_Arg11 );
	strcpy( sRanDom, Step_Arg12 );
	strcpy( sMAC1, Step_Arg13  );
	strcpy( sTransMoney, Step_Arg14 );
	strcpy( sReturnMoney, Step_Arg15  );
	

	SetMqSysConf( MqSysConf );
	
	sprintf(sSendBuf,"|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|",
		sPayChangel,sTransType,sCmd,sCardNo,sTermNo,sBalance,sConnectNo,
		sNoConnectNo,sEdition,sArith,sRanDom,sMAC1,sTransMoney,sReturnMoney);
	/* ���г�ֵ���뽻�� */
	
	ret = MqTrans(trdata,sSendBuf,sRevBuf);
	if(ret)
	{
		 bpErrorLog( trdata, " FILE[%s] LINE[%d]���г�ֵ���뽻��ʧ�� [%s]!",__FILE__,__LINE__,Msg);
		 etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		 return (-1);
	}

	
	
	memcpy( sReturnCode, sRevBuf , 1 );
	memcpy( sDataHead ,sRevBuf+1, 4 );
	memcpy( sMAC2 ,sRevBuf+5, 8 );
	memcpy( sPayDateTime ,sRevBuf+13, 14 );
		
	if( sReturnCode[0] != '0' )
	{
		bpErrorLog( trdata, "��ֵ���뽻��ʧ��! [%s] [%s]",sCardNo,sReturnCode);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}


	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] ��ֵ����ɹ�!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	etfAddOrRepNode( TrNode, "MAC2", sMAC2, 8 );
	etfAddOrRepNode( TrNode, "PayDateTime", sPayDateTime, 14 );
	return (0);

}
/******************************************************************************
	Function          : MqPaySure
	Description       : ������ͨ���г�ֵȷ��
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : 
	Table Updated	    : ��
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
					  8 ������( ǰ��λ�̶�Ϊ MQ������IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName )
					  2 : ��ֵȷ����
					  3 : ��ֵ�����к�
					  4 : ��ֵ����ʱ��
					  5 : ������
					  6 : �����������к�
					  7 : �ѻ��������к�
					  8 : ��ֵ���˽��
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int MqPaySure(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	
	
	char	sCode[4+1];
	char	sCardNo[12+1];
	char	sPayDateTime[14+1];
	char	sBalance[8+1];
	char	sConnectNo[8+1];
	char	sNoConnectNo[8+1];
	char	sReturnMoney[8+1];
	char	sReturnCode[1+1];
	int		ret;
  	

	ClearStr( sCode );
	ClearStr( sCardNo );
	ClearStr( sPayDateTime );
	ClearStr( sBalance );
	ClearStr( sConnectNo );
	ClearStr( sNoConnectNo );
	ClearStr( sReturnMoney );
	ClearStr( sReturnCode );
	ClearStr( sSendBuf );
	ClearStr( sRevBuf );
	ClearStr( MqSysConf );
	
	strcpy( MqSysConf, Step_Arg1 );
	strcpy( sCode, Step_Arg2 );
	strcpy( sCardNo, Step_Arg3 );
	strcpy( sPayDateTime, Step_Arg4 );
	strcpy( sBalance, Step_Arg5 );
	strcpy( sConnectNo, Step_Arg6 );
	strcpy( sNoConnectNo, Step_Arg7 );
	strcpy( sReturnMoney, Step_Arg8 );
	
	SetMqSysConf( MqSysConf );
	sprintf(sSendBuf,"|%s|%s|%s|%s|%s|%s|%s|",
		sCode,sCardNo,sPayDateTime,sBalance,sConnectNo,sNoConnectNo,sReturnMoney);
	/* ���г�ֵ���˲�ѯ���� */
	
	ret = MqTrans(trdata,sSendBuf,sRevBuf);
	if(ret)
	{
		 bpErrorLog( trdata, " FILE[%s] LINE[%d]���г�ֵȷ��ʧ�� [%s]!",__FILE__,__LINE__,Msg);
		 etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		 return (-1);
	}

	
	memcpy( sReturnCode, sRevBuf , 1 );
	
		
	if( sReturnCode[0] != '0' )
	{
		bpErrorLog( trdata, "��ֵȷ�Ͻ���ʧ��! [%s] [%s]",sCardNo,sReturnCode);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}


	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] ��ֵȷ�ϳɹ�!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	
	return (0);

}
/******************************************************************************
	Function          : exitMQ
	Description       : �˳�MQ֮ǰ����������
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : 
	Table Updated	    : ��
	Input             ��
	Output            : �� 
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
void exitMQ() {
	if(hMQSession != NULL ) {
		deleteMQSessionHandle( hMQSession );
		hMQSession = NULL;
	}
	if(hRecvMsg != NULL ) {
		clearMsg( hRecvMsg );
		deleteMQMsgHandle( hRecvMsg );
		hRecvMsg = NULL;
	}
	if(hSendMsg != NULL ) {
		deleteMQMsgHandle( hSendMsg );
		hSendMsg = NULL;
	}
	if(hSendQ != NULL ) {
		closeQueue( hSendQ );
		deleteMQQueueHandle( hSendQ );
		hSendQ = NULL;
	}
	if(hRecvQ != NULL ) {
		closeQueue( hRecvQ );
		deleteMQQueueHandle( hRecvQ );
		hRecvQ = NULL;
	}
	if(hMQServer != NULL ) {
		logout( hMQServer );
		deleteMQServerHandle( hMQServer );
		hMQServer = NULL;
	}
}
/******************************************************************************
	Function          : MqTrans
	Description       : ������ͨ����ͨѶ����
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : 
	Table Updated	    : ��
	Input             SenfBuf     ��������
                      RevBuf	  ��������
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int MqTrans( TranData *trdata,char *SenfBuf, char *RevBuf )
{
	int		i=0;
	int		iRet;
	uint32 iTimeout = 60;
	uint32 len = strlen( SenfBuf );

	
	memset(Msg,0,sizeof(Msg));
	
	
	

	
	/*==========================��½ �� �򿪶��� =========================== */
	hMQServer = createMQServerHandle();

	bpErrorLog( trdata, "FILE[%s] LINE[%d] [%s] [%s] [%s] [%s] [%s] [%s]...!",
		__FILE__,__LINE__,MqAddress,MqPort,MqUserName,MqPassWord,MqSendName,MqRecvName);

	iRet = login( hMQServer, MqAddress,atoi(MqPort),MqUserName,MqPassWord ) ;
	if( iRet != 0) {
		exitMQ();
		sprintf( Msg,"��½ʧ��!Code:[ %d ]", iRet);
		bpErrorLog( trdata, "FILE[%s] LINE[%d] ��½ʧ��...!",__FILE__,__LINE__);
		return -1;
	}
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] ��½�ɹ�...!",__FILE__,__LINE__);
	
	hSendQ = createMQQueueHandle();
	set_m_pMQServer(hSendQ, hMQServer);
	iRet = openQueue( hSendQ, MqSendName, "w" );
	if( iRet != 0) {
		exitMQ();
		sprintf( Msg,"�򿪷��Ͷ���ʧ��!Code:[ %d ]", iRet);
		return -4;
	}

	bpErrorLog( trdata, "FILE[%s] LINE[%d] �򿪷��Ͷ��гɹ�...!",__FILE__,__LINE__);
	
	hRecvQ = createMQQueueHandle();
	set_m_pMQServer(hRecvQ, hMQServer);
	iRet = openQueue( hRecvQ, MqRecvName, "r" );
	if( iRet != 0) {
		exitMQ();
		sprintf( Msg,"�򿪽��ն���ʧ��!Code:[ %d ]", iRet);
		return -5;
	}

	bpErrorLog( trdata, "FILE[%s] LINE[%d] �򿪽��ն��гɹ�...!",__FILE__,__LINE__);

	hMQSession = createMQSessionHandle();
	set_m_pQFrom( hMQSession, hRecvQ );
	set_m_pQTo( hMQSession, hSendQ );
	set_m_iTimeout( hMQSession, iTimeout );
	set_m_iTryTimes( hMQSession, 1 );

	hSendMsg = createMQMsgHandle();
	hRecvMsg = createMQMsgHandle();

	bpErrorLog( trdata, "FILE[%s] LINE[%d] ��ʼMQCall[%s]...!",__FILE__,__LINE__,SenfBuf);
	for(  i=0; i < strlen(SenfBuf); i++ )
			if( SenfBuf[i] == '|' )  SenfBuf[i] = '\x01';
	setMsg( hSendMsg, SenfBuf, &len );


	bpErrorLog( trdata, "FILE[%s] LINE[%d] ��ʼMQCall...!",__FILE__,__LINE__);

	iRet = MQCall( hMQSession, hSendMsg, hRecvMsg );
	if( iRet != 0) {
		exitMQ();
		sprintf( Msg,"mqcallʧ��!Code:[ %d ]", iRet);
		return -6;
	}

	
	strcpy( RevBuf , getMsg( hRecvMsg ) );
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] MQCall�ɹ�  [%s]...!",__FILE__,__LINE__,RevBuf);

	clearMsg( hRecvMsg ); /* �ͷ���Ϣ�����������ڴ�й© */

	exitMQ();

	return 0;
}
/******************************************************************************
	Function          : TrimSpace
	Description       : ȥ���ո�
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : 
	Table Updated	    : ��
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
					  1 ������
					  1 : ���滻���ַ�
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int TrimSpace(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	
	
	char	recv[1024];
	int	  i;
  	

	ClearStr( recv );
	

	
	strcpy( recv, Step_Arg1 );
	bpErrorLog( trdata, "FILE[%s] LINE[%d] ȥ�����з�ǰ[%s]!",__FILE__,__LINE__,recv);
	for(i=0;i<=strlen(recv);i++)
	{
		if( recv[i] == '')
			recv[i] = ' ';
		if( recv[i] == '\n' )
			recv[i] = ' ';
	}
	/* trimspace(recv,'
'); */
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] ȥ�����з���[%s]!",__FILE__,__LINE__,recv);
	etfAddOrRepNode( TrNode, "Remark1", recv, strlen(recv) );
	
	return (0);

}


int SetMqSysConf( char *MqSysConf )
{
	ClearStr( MqAddress );
	ClearStr( MqPort );
	ClearStr( MqUserName );
	ClearStr( MqPassWord );
	ClearStr( MqSendName );
	ClearStr( MqRecvName );

	splitby( MqSysConf,"|",1,MqAddress,30);
	splitby( MqSysConf,"|",2,MqPort,30);
	splitby( MqSysConf,"|",3,MqUserName,30);
	splitby( MqSysConf,"|",4,MqPassWord,30);
	splitby( MqSysConf,"|",5,MqSendName,30);
	splitby( MqSysConf,"|",6,MqRecvName,30);
	return 0;
}

/*************************************************
	���ܣ�ȡ�ָ�������
	���룺input:��������
		s: �ָ���
		count���ڼ����ָ���
		output: �������
		len ��������ݱ�����󳤶�
	
****************************************************/
int splitby(char *input,char *s,long count,char *output,long len)
{
	int i,iCount=0;
	int k=0;
	char *p;

	if(count < 1 ) return 0;
	p=input;
	
	for(i=0;i<strlen(input);)
	{
		if( (input[i] > 0x80)  || input[i] < 0 ) /*�������еķָ���*/
		{
			i=i+2;
			continue;
		}

		if(strncmp(input+i, s,strlen(s)) == 0)
		{
			iCount ++;
			if(iCount == count)
			{
				if(len <= (input + i - p ))
					strncpy(output,p,len);
				else
					strncpy(output,p,input + i - p);
				return 0;
			}
			else
			{
				p=input + i + strlen(s);
			}
			i=i+strlen(s);
		}
		else
			i++;
	}
	if( strncmp(input+ (strlen(input) - strlen(s)), s ,strlen(s) ) != 0)
	{
		if(count == iCount + 1)
		{
			if(len <= (input + i - p ))
				strncpy(output,p,len);
			else
				strncpy(output,p,input + i - p);
			return 0;
		}
	}
	return -1;
}
/******************************************************************************
	Function          : ReadCCSUpdate
	Description       : ����˰�������������ݸ���
	Calls             : �����������õĺ����嵥
	Called By         : ���ñ������ĺ����嵥 
	Table Accessed    : 
	Table Updated	    : ��
	Input             : ETF *TrNode	������ 
                      ST_TranData* trdata	�����ṹ
                      char* args	����  
                      DBConHandle* DBHandle	���ݿ���   
					  1 ������
					  1 : �����������ļ�
	Output            : �����������˵����     
	Return            : 0--�ɹ� С��0--ʧ��   
	Others            : ����˵��             
******************************************************************************/
int ReadCCSUpdate(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;		
		char	 STAN[12+1]; /* ϵͳ�ο��� */
		char	 SETTLE_DATE[4+1]; /* �������� */
		char	 TXN_DATE[8+1]; /* �������� */
		char	 TXN_TIME[6+1]; /* ����ʱ�� */
		char	 TXN_ACCOUNT[19+1]; /*�����ʺ� */
		char	 MTI[4+1];/* ��Ϣ�� */
		char	 PROCESS_CODE[6+1]; /* ������ */
		char	 B_L_sign[1+1];/* �����־ */
		char	 AMOUNT[12+1];/* ��� */
		char	 ADJ_STAN[12+1];/* ԭϵͳ�ο��� */
		char	 MERCHANT_ID[15+1];/* �̻��� */
		char	 TERM_ID[8+1];/*�ն˻���  */
		char	 TERM_SERIAL[6+1];/* ��ˮ�� */
		char	 RESPONSE_CODE[6+1];/* ��Ӧ�� */
		char	 TELEPHONE_NO[47+1];/* ���Ѻ��� */
		char	 BANK[6+1];/* ���д��� */
		char	 BUSINESS[4+1];/* ҵ����� */
		char	 AERA[2+1];/* ������ */
		char	 FORM[1+1];/* ���׷�ʽ */
		char	 jysj[14+1];
	EXEC SQL END DECLARE SECTION;
		char	 sFilename[100+1]; /* �����ļ� */
		FILE *fp;
		int  i=0;
		char	buf[1024];
		
		ClearStr( jysj );

		ClearStr( sFilename );
		ClearStr( STAN );
		ClearStr( SETTLE_DATE );
		ClearStr( TXN_DATE );
		ClearStr( TXN_TIME );
		ClearStr( TXN_ACCOUNT );
		ClearStr( MTI );
		ClearStr( PROCESS_CODE );
		ClearStr( B_L_sign );
		ClearStr( AMOUNT );
		ClearStr( ADJ_STAN );
		ClearStr( MERCHANT_ID );
		ClearStr( TERM_ID);
		ClearStr( TERM_SERIAL );
		ClearStr( RESPONSE_CODE );
		ClearStr( TELEPHONE_NO );
		ClearStr( BANK );
		ClearStr( BUSINESS );
		ClearStr( AERA );
		ClearStr( FORM );

	
	strcpy( sFilename, Step_Arg1 );
	bpErrorLog( trdata, "�������ļ� [%s]!",sFilename);
	
	
	if( access(sFilename,F_OK) != 0 )
	{
		bpErrorLog( trdata, "FILE[%s] LINE[%d] �ļ�������!",__FILE__,__LINE__);
		etfAddOrRepNode( TrNode, "MQCODE", "000001", 6 );
		return (0);
	}

	fp = fopen(sFilename,"r");
	if( fp == NULL )
	{
		bpErrorLog( trdata, "FILE[%s] LINE[%d] �ļ�������!",__FILE__,__LINE__);
		etfAddOrRepNode( TrNode, "MQCODE", "000001", 6 );
		return (-1);
	}

	while(1)
	{
		if ( fgets(buf,1024,fp) == NULL )
			break;
		if ( strlen(buf)<50 )
			break;
		/*sscanf(buf,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",STAN,SETTLE_DATE,TXN_DATE,TXN_TIME,
				TXN_ACCOUNT,MTI,PROCESS_CODE,B_L_sign,AMOUNT,ADJ_STAN,
				MERCHANT_ID,TERM_ID,TERM_SERIAL,RESPONSE_CODE,TELEPHONE_NO,
				BANK,BUSINESS,AERA,FORM );*/
		splitby(buf,",",1,STAN,12);
		splitby(buf,",",2,SETTLE_DATE,4);
		splitby(buf,",",3,TXN_DATE,8);
		splitby(buf,",",4,TXN_TIME,6);
		splitby(buf,",",5,TXN_ACCOUNT,19);
		splitby(buf,",",6,MTI,4);
		splitby(buf,",",7,PROCESS_CODE,6);
		splitby(buf,",",8,B_L_sign,1);
		splitby(buf,",",9,AMOUNT,12);
		splitby(buf,",",10,ADJ_STAN,12);
		splitby(buf,",",11,MERCHANT_ID,15);
		splitby(buf,",",12,TERM_ID,8);
		splitby(buf,",",13,TERM_SERIAL,6);
		splitby(buf,",",14,RESPONSE_CODE,6);
		splitby(buf,",",15,TELEPHONE_NO,47);
		splitby(buf,",",16,BANK,6);
		splitby(buf,",",17,BUSINESS,4);
		splitby(buf,",",18,AERA,2);
		splitby(buf,",",19,FORM,1);
		strcat(jysj,TXN_DATE);
		strcat(jysj,TXN_TIME);
		bpErrorLog( trdata, "FILE[%s] LINE[%d] %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s!",__FILE__,__LINE__,STAN,SETTLE_DATE,TXN_DATE,TXN_TIME,
				TXN_ACCOUNT,MTI,PROCESS_CODE,B_L_sign,AMOUNT,ADJ_STAN,
				MERCHANT_ID,TERM_ID,TERM_SERIAL,RESPONSE_CODE,TELEPHONE_NO,
				BANK,BUSINESS,AERA,FORM );
		bpErrorLog( trdata, "FILE[%s] LINE[%d] %s %s",__FILE__,__LINE__,jysj,STAN);
		if( strncmp(RESPONSE_CODE , "00",2) == 0 )
		{
			/*EXEC SQL update afetxnjnl set ThdChk='1' where TLogNo =:STAN and FTxnTm =:jysj and ActNo =:TXN_ACCOUNT and Rsfld2=:BUSINESS ;	*/
					
			EXEC SQL update afetxnjnl set ThdChk='1',Ttxnst='S' where FTxnTm =:jysj and ActNo =:TXN_ACCOUNT and Rsfld2=:BUSINESS ;
		}
		else
		{
			EXEC SQL update afetxnjnl set ThdChk='0' where TLogNo =:STAN and FTxnTm =:jysj and ActNo =:TXN_ACCOUNT and Rsfld2=:BUSINESS ;			
		}
		if( SQLCODE )
		{
			bpErrorLog( trdata, "FILE[%s] LINE[%d] ��¼������!",__FILE__,__LINE__);
			etfAddOrRepNode( TrNode, "MQCODE", "000001", 6 );
			//return (-2);
		}
		i ++;
		ClearStr( jysj );
		ClearStr( buf );
		ClearStr( STAN );
		ClearStr( SETTLE_DATE );
		ClearStr( TXN_DATE );
		ClearStr( TXN_TIME );
		ClearStr( TXN_ACCOUNT );
		ClearStr( MTI );
		ClearStr( PROCESS_CODE );
		ClearStr( B_L_sign );
		ClearStr( AMOUNT );
		ClearStr( ADJ_STAN );
		ClearStr( MERCHANT_ID );
		ClearStr( TERM_ID );
		ClearStr( TERM_SERIAL );
		ClearStr( RESPONSE_CODE );
		ClearStr( TELEPHONE_NO );
		ClearStr( BANK );
		ClearStr( BUSINESS );
		ClearStr( AERA );
		ClearStr( FORM );
	}
	fclose(fp);



	bpErrorLog( trdata, "FILE[%s] LINE[%d] �������,������[%d]��!",__FILE__,__LINE__,i);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	return (0);

}

int MakeTime(char *day)
{
    char aczYear[5], aczMonth[3], aczDay[3];
    struct tm t;
    time_t t_day;

    memset(aczYear, 0, sizeof(aczYear));
    memset(aczMonth, 0, sizeof(aczMonth));
    memset(aczDay, 0, sizeof(aczDay));

    strncpy(aczYear, day, 4);
    strncpy(aczMonth, day + 4, 2);
    strncpy(aczDay, day + 6, 2);

    memset(&t, 0, sizeof(struct tm));
    t.tm_year = atoi(aczYear)- 1900;
    t.tm_mon = atoi(aczMonth) - 1;
    t.tm_mday = atoi(aczDay);
    t_day = mktime(&t);
    return  t_day;
}

/*
day1��ʽΪ20061201
*/
int DiffDay(char *day1, char *day2)
{
    time_t t_day1, t_day2;
    double diffSecond = 0;
    int diffDays = 0;

    if(strlen(day1) != 8 || strlen(day2) != 8)
        return -1;

    t_day1 = MakeTime(day1);
    t_day2 = MakeTime(day2);

    diffSecond = difftime(t_day1 , t_day2);
    diffDays =  diffSecond / 86400;

    return diffDays;
}

int CaclValidDays(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	char	Use_Date[32];
	char  Valid_Begin_Date[32];
	char	Valid_End_Date[32];
	char	Valid_Days[32];
	char  Today[32];
	char  aczTemp[32];
	int i = 0;
	int j = 0;
	int iValid = 0;
  	
	ClearStr( Use_Date );
	ClearStr( Valid_Begin_Date );
	ClearStr( Valid_End_Date );
	ClearStr( Valid_Days );
	ClearStr( Today );
	ClearStr( aczTemp );
		
	strcpy( Use_Date, Step_Arg1 );	
	strcpy( Valid_Begin_Date, Step_Arg2 );
	strcpy( Valid_End_Date, Step_Arg3 );	
	strcpy( Valid_Days, Step_Arg4 );
	strcpy( Today, Step_Arg5 );
	
	if(!(DiffDay(Use_Date, Valid_Begin_Date) >=0 
			&& DiffDay(Use_Date, Valid_End_Date) <=0 
			&& DiffDay(Use_Date, Today) >=0)){
		bpErrorLog( trdata, "��������ڲ��Ϸ������������Ӧ������Ч���ڷ�Χ��!");
		etfAddOrRepNode( TrNode, "MQCODE", "482199", 6 );
		return (-1);				
	}	
	
	i = DiffDay(Valid_End_Date, Use_Date);
	j = atol(Valid_Days);
	
	i = i + 1;
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] Use_Date[%s],Valid_End_Date[%s],Valid_Days[%s]Today[%s]",__FILE__,__LINE__, Use_Date,Valid_End_Date, Valid_Days, Today);
	bpErrorLog( trdata, "FILE[%s] LINE[%d] diffday[%d],Valid_Days[%d]",__FILE__,__LINE__, i, j);
	
	if( i < j && i > 0)	
		sprintf(aczTemp, "%d", i);
	else 
		sprintf(aczTemp, "%d", j);
		
	etfAddOrRepNode( TrNode, "Valid_Days", aczTemp, strlen(aczTemp) );	
		
	return (0);

}
int HextoDec(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	int i,value=0,length;
	char aczTemp[32];
	char p[32];
	
    ClearStr( aczTemp );
	ClearStr( p );
	strcpy( p, Step_Arg1 );	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] p[%s]",__FILE__,__LINE__, p);
	length=strlen(p);
	bpErrorLog( trdata, "FILE[%s] LINE[%d] length[%d]",__FILE__,__LINE__, length);
    for(i=0;i<length;i++)
    {
        if(('0' <= *(p+i)) && (*(p+i)<='9') )
        {
            value=value+(*(p+i)-'0')*pow(16,(length-i-1));
			bpErrorLog( trdata, "FILE[%s] LINE[%d] value1[%d]",__FILE__,__LINE__, value);
        }
       else if(*(p+i)>='a')
        {
            value=value+(*(p+i)-'a'+10)*pow(16,(length-i-1));
			bpErrorLog( trdata, "FILE[%s] LINE[%d] value1[%d]",__FILE__,__LINE__, value);
        }
        else
        {
			value=value+(*(p+i)-'A'+10)*pow(16,(length-i-1));
			bpErrorLog( trdata, "FILE[%s] LINE[%d] value1[%d]",__FILE__,__LINE__, value);
        }
        if(*(p+i)=='\0')
            break;
		bpErrorLog( trdata, "FILE[%s] LINE[%d] value[%d]",__FILE__,__LINE__, value);
    }
	
	sprintf(aczTemp, "%d", value);	
	etfAddOrRepNode( TrNode, "DEC", aczTemp, strlen(aczTemp) );	
		
	return (0);

}
