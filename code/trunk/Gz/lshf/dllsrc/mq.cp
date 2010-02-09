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

/* MQ服务器IP */
char	MqSysConf[200];
char	MqAddress[30];
/* 端口号 */
char	MqPort[10];
/* 用户名 */
char	MqUserName[20];
/* 密码 */
char	MqPassWord[20];
char	MqSendName[20];
char	MqRecvName[20];
char	 sSendBuf[1024];
char	 sRevBuf[1024];

char	Msg[80];
/******************************************************************************
	Function          : MqLoginandPay
	Description       : 与粤卡通进行签到和充值
	Calls             : 被本函数调用的函数清单
	Called By         : 调用本函数的函数清单 
	Table Accessed    : 
	Table Updated	    : 无
	Input             : ETF *TrNode	输入树 
                      ST_TranData* trdata	公共结构
                      char* args	参数  
                      DBConHandle* DBHandle	数据库句柄   
					  3 个参数( 前四位固定为 MQ服务器IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName )
					  2 : 命令码
					  3 : 储值卡卡号
	Output            : 对输出参数的说明。     
	Return            : 0--成功 小于0--失败   
	Others            : 其它说明             
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
    bpErrorLog( trdata, "FILE[%s] LINE[%d] 报文错误!",__FILE__,__LINE__);
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
		 bpErrorLog( trdata, " FILE[%s] LINE[%d]进行交易失败 [%s]!",__FILE__,__LINE__,Msg);
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
	bpErrorLog( trdata, "FILE[%s] LINE[%d] 交易成功!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	etfAddOrRepNode( TrNode, "sRev", sRev, sizeof(sRev));

	return (0);

}
/******************************************************************************
	Function          : MqSingIn
	Description       : 与粤卡通进行签到交易
	Calls             : 被本函数调用的函数清单
	Called By         : 调用本函数的函数清单 
	Table Accessed    : 
	Table Updated	    : 无
	Input             : ETF *TrNode	输入树 
                      ST_TranData* trdata	公共结构
                      char* args	参数  
                      DBConHandle* DBHandle	数据库句柄   
					  8 个参数( 前四位固定为 MQ服务器IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName )
					  2 : 充值签到码
					  3 : IP地址
					  4 : 终端编号
					  5 : 交易金额
	Output            : 对输出参数的说明。     
	Return            : 0--成功 小于0--失败   
	Others            : 其它说明             
******************************************************************************/
int MqSingIn(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;
		char	 sDate[8+1]; /* 日期 */
		char	 sStatus[1+1]; /* 状态 */
	EXEC SQL END DECLARE SECTION;
		char	 sCode[4+1]; /* 签到码 */
		char	 sAddress[15+1]; /* IP地址 */
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
	/* 进行充值签到交易 */
	
	ret = MqTrans(trdata,sSendBuf,sRevBuf);
	if(ret)
	{
		bpErrorLog( trdata, "进行充值签到交易失败 [%s]!",Msg);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}
		
	
	/* 进行签到交易返回 */
	memcpy(ReturnCode,sRevBuf,1);
	memcpy(MaxPay,sRevBuf+1,5);

	if( ReturnCode[0] != '0' )
	{
		bpErrorLog( trdata, "签到失败,请联系粤通卡公司! [%s]",ReturnCode);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}

	/* 检查充值金额是否大于上限  */
	if( atol(sTransje)/100 > atol(MaxPay) )
	{
		bpErrorLog( trdata, "交易金额大于上限! ");
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}

	/* 进行余额转换 */
	sprintf(sTemp,"%08.8d",strtol(sBalance,NULL,16));
	etfAddOrRepNode( TrNode, "RsFld1", sTemp, 8 );
	sTemp1 = atol(sTemp);
	sTemp2 = atol(sTransje);
	sTemp3 = sTemp1 + sTemp2;
	
	ClearStr( sTemp );

	sprintf( sTemp ,"%08.8d",sTemp3);
	etfAddOrRepNode( TrNode, "RsFld2", sTemp, 8 );
	bpErrorLog( trdata, "FILE[%s] LINE[%d] 充值签到成功!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	return (0);

}
/******************************************************************************
	Function          : MqQuery
	Description       : 与粤卡通进行充值回退查询
	Calls             : 被本函数调用的函数清单
	Called By         : 调用本函数的函数清单 
	Table Accessed    : 
	Table Updated	    : 无
	Input             : ETF *TrNode	输入树 
                      ST_TranData* trdata	公共结构
                      char* args	参数  
                      DBConHandle* DBHandle	数据库句柄   
					  3 个参数( 前四位固定为 MQ服务器IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName )
					  2 : 命令码
					  3 : 储值卡卡号
	Output            : 对输出参数的说明。     
	Return            : 0--成功 小于0--失败   
	Others            : 其它说明             
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
	/* 进行充值回退查询交易 */
	
	ret = MqTrans(trdata,sSendBuf,sRevBuf);
	if(ret)
	{
		 bpErrorLog( trdata, " FILE[%s] LINE[%d]进行充值回退查询失败 [%s]!",__FILE__,__LINE__,Msg);
		 etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		 return (-1);
	}
	

	
	memcpy( sReturnCode, sRevBuf , 1 );
	etfAddOrRepNode( TrNode, "RsFld3", sReturnMoney, 8 );
	memcpy( sReturnMoney ,sRevBuf+1,8 );
	
	
	/*
	if( sReturnCode[0] != '0' )
	{
		bpErrorLog( trdata, "充值回退查询交易失败! [%s] [%s]",sCardNo,sReturnCode);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);		
	}
	*/
	
	sTemp = atof(sReturnMoney) * 100;
	sprintf(sReturnMoney1,"%d",sTemp );
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] sReturnMoney1[%s]!",__FILE__,__LINE__,sReturnMoney1);
	sprintf(sReturnMoney,"%08.8d",atol(sReturnMoney1));


	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] 充值回退查询成功!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	etfAddOrRepNode( TrNode, "ReturnMoney", sReturnMoney, 8);

	return (0);

}
/******************************************************************************
	Function          : MqPayQue
	Description       : 与粤卡通进行充值申请
	Calls             : 被本函数调用的函数清单
	Called By         : 调用本函数的函数清单 
	Table Accessed    : 
	Table Updated	    : 无
	Input             : ETF *TrNode	输入树 
                      ST_TranData* trdata	公共结构
                      char* args	参数  
                      DBConHandle* DBHandle	数据库句柄   
					  17 个参数( 前四位固定为 MQ服务器IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName)
					  2 : 充值途径码
					  3 : 交易类型码
					  4 : 密码机命令码
					  5 : 储值卡序列号
					  6 : 充值终端编码
					  7 : 储值卡当前余额
					  8 : 储值卡当前联机交易序列号
					  9 : 储值卡当前脱机交易序列号
					 10 : 交易密钥版本
					 11 : 交易算法版本
					 12 : 随机数
					 13 : MAC1码
					 14 : 充值金额
					 15 : 回退金额
					 16 : 操作员编号
					 17 : IP地址
	Output            : 对输出参数的说明。     
	Return            : 0--成功 小于0--失败   
	Others            : 其它说明             
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
	/* 进行充值申请交易 */
	
	ret = MqTrans(trdata,sSendBuf,sRevBuf);
	if(ret)
	{
		 bpErrorLog( trdata, " FILE[%s] LINE[%d]进行充值申请交易失败 [%s]!",__FILE__,__LINE__,Msg);
		 etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		 return (-1);
	}

	
	
	memcpy( sReturnCode, sRevBuf , 1 );
	memcpy( sDataHead ,sRevBuf+1, 4 );
	memcpy( sMAC2 ,sRevBuf+5, 8 );
	memcpy( sPayDateTime ,sRevBuf+13, 14 );
		
	if( sReturnCode[0] != '0' )
	{
		bpErrorLog( trdata, "充值申请交易失败! [%s] [%s]",sCardNo,sReturnCode);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}


	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] 充值申请成功!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	etfAddOrRepNode( TrNode, "MAC2", sMAC2, 8 );
	etfAddOrRepNode( TrNode, "PayDateTime", sPayDateTime, 14 );
	return (0);

}
/******************************************************************************
	Function          : MqPaySure
	Description       : 与粤卡通进行充值确认
	Calls             : 被本函数调用的函数清单
	Called By         : 调用本函数的函数清单 
	Table Accessed    : 
	Table Updated	    : 无
	Input             : ETF *TrNode	输入树 
                      ST_TranData* trdata	公共结构
                      char* args	参数  
                      DBConHandle* DBHandle	数据库句柄   
					  8 个参数( 前四位固定为 MQ服务器IP  MqPort  MqUserName  MqPassWord MqSendName MqRecvName )
					  2 : 充值确认码
					  3 : 储值卡序列号
					  4 : 充值交易时间
					  5 : 储蓄卡余额
					  6 : 联机交易序列号
					  7 : 脱机交易序列号
					  8 : 充值回退金额
	Output            : 对输出参数的说明。     
	Return            : 0--成功 小于0--失败   
	Others            : 其它说明             
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
	/* 进行充值回退查询交易 */
	
	ret = MqTrans(trdata,sSendBuf,sRevBuf);
	if(ret)
	{
		 bpErrorLog( trdata, " FILE[%s] LINE[%d]进行充值确认失败 [%s]!",__FILE__,__LINE__,Msg);
		 etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		 return (-1);
	}

	
	memcpy( sReturnCode, sRevBuf , 1 );
	
		
	if( sReturnCode[0] != '0' )
	{
		bpErrorLog( trdata, "充值确认交易失败! [%s] [%s]",sCardNo,sReturnCode);
		etfAddOrRepNode( TrNode, "MQCODE", "999999", 6 );
		return (-1);
	}


	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] 充值确认成功!",__FILE__,__LINE__);
	etfAddOrRepNode( TrNode, "MQCODE", "000000", 6 );
	
	return (0);

}
/******************************************************************************
	Function          : exitMQ
	Description       : 退出MQ之前进行清理工作
	Calls             : 被本函数调用的函数清单
	Called By         : 调用本函数的函数清单 
	Table Accessed    : 
	Table Updated	    : 无
	Input             无
	Output            : 无 
	Return            : 0--成功 小于0--失败   
	Others            : 其它说明             
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
	Description       : 与粤卡通进行通讯交易
	Calls             : 被本函数调用的函数清单
	Called By         : 调用本函数的函数清单 
	Table Accessed    : 
	Table Updated	    : 无
	Input             SenfBuf     传送数据
                      RevBuf	  返回数据
	Output            : 对输出参数的说明。     
	Return            : 0--成功 小于0--失败   
	Others            : 其它说明             
******************************************************************************/
int MqTrans( TranData *trdata,char *SenfBuf, char *RevBuf )
{
	int		i=0;
	int		iRet;
	uint32 iTimeout = 60;
	uint32 len = strlen( SenfBuf );

	
	memset(Msg,0,sizeof(Msg));
	
	
	

	
	/*==========================登陆 及 打开队列 =========================== */
	hMQServer = createMQServerHandle();

	bpErrorLog( trdata, "FILE[%s] LINE[%d] [%s] [%s] [%s] [%s] [%s] [%s]...!",
		__FILE__,__LINE__,MqAddress,MqPort,MqUserName,MqPassWord,MqSendName,MqRecvName);

	iRet = login( hMQServer, MqAddress,atoi(MqPort),MqUserName,MqPassWord ) ;
	if( iRet != 0) {
		exitMQ();
		sprintf( Msg,"登陆失败!Code:[ %d ]", iRet);
		bpErrorLog( trdata, "FILE[%s] LINE[%d] 登陆失败...!",__FILE__,__LINE__);
		return -1;
	}
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] 登陆成功...!",__FILE__,__LINE__);
	
	hSendQ = createMQQueueHandle();
	set_m_pMQServer(hSendQ, hMQServer);
	iRet = openQueue( hSendQ, MqSendName, "w" );
	if( iRet != 0) {
		exitMQ();
		sprintf( Msg,"打开发送队列失败!Code:[ %d ]", iRet);
		return -4;
	}

	bpErrorLog( trdata, "FILE[%s] LINE[%d] 打开发送队列成功...!",__FILE__,__LINE__);
	
	hRecvQ = createMQQueueHandle();
	set_m_pMQServer(hRecvQ, hMQServer);
	iRet = openQueue( hRecvQ, MqRecvName, "r" );
	if( iRet != 0) {
		exitMQ();
		sprintf( Msg,"打开接收队列失败!Code:[ %d ]", iRet);
		return -5;
	}

	bpErrorLog( trdata, "FILE[%s] LINE[%d] 打开接收队列成功...!",__FILE__,__LINE__);

	hMQSession = createMQSessionHandle();
	set_m_pQFrom( hMQSession, hRecvQ );
	set_m_pQTo( hMQSession, hSendQ );
	set_m_iTimeout( hMQSession, iTimeout );
	set_m_iTryTimes( hMQSession, 1 );

	hSendMsg = createMQMsgHandle();
	hRecvMsg = createMQMsgHandle();

	bpErrorLog( trdata, "FILE[%s] LINE[%d] 开始MQCall[%s]...!",__FILE__,__LINE__,SenfBuf);
	for(  i=0; i < strlen(SenfBuf); i++ )
			if( SenfBuf[i] == '|' )  SenfBuf[i] = '\x01';
	setMsg( hSendMsg, SenfBuf, &len );


	bpErrorLog( trdata, "FILE[%s] LINE[%d] 开始MQCall...!",__FILE__,__LINE__);

	iRet = MQCall( hMQSession, hSendMsg, hRecvMsg );
	if( iRet != 0) {
		exitMQ();
		sprintf( Msg,"mqcall失败!Code:[ %d ]", iRet);
		return -6;
	}

	
	strcpy( RevBuf , getMsg( hRecvMsg ) );
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] MQCall成功  [%s]...!",__FILE__,__LINE__,RevBuf);

	clearMsg( hRecvMsg ); /* 释放消息，否则将引起内存泄漏 */

	exitMQ();

	return 0;
}
/******************************************************************************
	Function          : TrimSpace
	Description       : 去除空格
	Calls             : 被本函数调用的函数清单
	Called By         : 调用本函数的函数清单 
	Table Accessed    : 
	Table Updated	    : 无
	Input             : ETF *TrNode	输入树 
                      ST_TranData* trdata	公共结构
                      char* args	参数  
                      DBConHandle* DBHandle	数据库句柄   
					  1 个参数
					  1 : 被替换的字符
	Output            : 对输出参数的说明。     
	Return            : 0--成功 小于0--失败   
	Others            : 其它说明             
******************************************************************************/
int TrimSpace(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	
	
	char	recv[1024];
	int	  i;
  	

	ClearStr( recv );
	

	
	strcpy( recv, Step_Arg1 );
	bpErrorLog( trdata, "FILE[%s] LINE[%d] 去除换行符前[%s]!",__FILE__,__LINE__,recv);
	for(i=0;i<=strlen(recv);i++)
	{
		if( recv[i] == '')
			recv[i] = ' ';
		if( recv[i] == '\n' )
			recv[i] = ' ';
	}
	/* trimspace(recv,'
'); */
	
	bpErrorLog( trdata, "FILE[%s] LINE[%d] 去除换行符后[%s]!",__FILE__,__LINE__,recv);
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
	功能：取分隔符数据
	输入：input:输入数据
		s: 分隔符
		count：第几个分隔符
		output: 输出数据
		len ：输出数据变量最大长度
	
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
		if( (input[i] > 0x80)  || input[i] < 0 ) /*处理汉字中的分隔符*/
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
	Description       : 车船税第三方交易数据更新
	Calls             : 被本函数调用的函数清单
	Called By         : 调用本函数的函数清单 
	Table Accessed    : 
	Table Updated	    : 无
	Input             : ETF *TrNode	输入树 
                      ST_TranData* trdata	公共结构
                      char* args	参数  
                      DBConHandle* DBHandle	数据库句柄   
					  1 个参数
					  1 : 第三方对帐文件
	Output            : 对输出参数的说明。     
	Return            : 0--成功 小于0--失败   
	Others            : 其它说明             
******************************************************************************/
int ReadCCSUpdate(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
	EXEC SQL INCLUDE SQLCA;
	EXEC SQL BEGIN DECLARE SECTION;		
		char	 STAN[12+1]; /* 系统参考号 */
		char	 SETTLE_DATE[4+1]; /* 清算日期 */
		char	 TXN_DATE[8+1]; /* 交易日期 */
		char	 TXN_TIME[6+1]; /* 交易时间 */
		char	 TXN_ACCOUNT[19+1]; /*交易帐号 */
		char	 MTI[4+1];/* 信息码 */
		char	 PROCESS_CODE[6+1]; /* 处理码 */
		char	 B_L_sign[1+1];/* 借贷标志 */
		char	 AMOUNT[12+1];/* 金额 */
		char	 ADJ_STAN[12+1];/* 原系统参考号 */
		char	 MERCHANT_ID[15+1];/* 商户号 */
		char	 TERM_ID[8+1];/*终端机号  */
		char	 TERM_SERIAL[6+1];/* 流水号 */
		char	 RESPONSE_CODE[6+1];/* 响应码 */
		char	 TELEPHONE_NO[47+1];/* 交费号码 */
		char	 BANK[6+1];/* 银行代码 */
		char	 BUSINESS[4+1];/* 业务代码 */
		char	 AERA[2+1];/* 地区码 */
		char	 FORM[1+1];/* 交易方式 */
		char	 jysj[14+1];
	EXEC SQL END DECLARE SECTION;
		char	 sFilename[100+1]; /* 对帐文件 */
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
	bpErrorLog( trdata, "第三方文件 [%s]!",sFilename);
	
	
	if( access(sFilename,F_OK) != 0 )
	{
		bpErrorLog( trdata, "FILE[%s] LINE[%d] 文件不存在!",__FILE__,__LINE__);
		etfAddOrRepNode( TrNode, "MQCODE", "000001", 6 );
		return (0);
	}

	fp = fopen(sFilename,"r");
	if( fp == NULL )
	{
		bpErrorLog( trdata, "FILE[%s] LINE[%d] 文件不存在!",__FILE__,__LINE__);
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
			bpErrorLog( trdata, "FILE[%s] LINE[%d] 记录不存在!",__FILE__,__LINE__);
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



	bpErrorLog( trdata, "FILE[%s] LINE[%d] 处理完毕,共处理[%d]行!",__FILE__,__LINE__,i);
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
day1格式为20061201
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
		bpErrorLog( trdata, "输入的日期不合法，输入的日期应该在有效日期范围内!");
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
