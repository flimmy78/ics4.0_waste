/*
 * Project       :��ͨ����
 * Source        :ENCSVR_PFT.CP
 * Version       :V1.0
 * Description   :PFTϵͳ����
 * Authors       :wishman 200706
 * Update History:
 * Date          Position    Author        Description
 * ---------------------------------------------------
 * 20090313                  Delfly        Modify
 */

#include <signal.h>
#define	 __MAIN

#include <sys/socket.h>
#include <sys/errno.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <netinet/in.h>
#include <time.h>
#include <fcntl.h>
#include <stdarg.h>


#define Qnum 6
#define MY_DATA_LEN             1024

/*char	sMasterKey[8+1] = "ying5876";*/
char	sMasterKey[8+1] = "12345678"; /*test ������*/
int               _IsEnc=1;

int DoCypHead(char *sEndMsg,int *iEndLen,char *sDeaDat,int iDatLen);
int DoUncBody(char *sEndMsg,int *iEndLen,char *sDeaDat,int iDatLen);
int DoEncBody(char *sEndMsg,int *iEndLen,char *sDeaDat,int iDatLen);
int MyMsgRecv( int port );
int Deal( int iSockId );
int ReturnErr( int iSockId, char * RetCod );
int Return01(int iSockId,char * sEndMsg,int iEndLen);

int DelRSpace( char * buff )
{
	int		len;
	int		i;
	
	len = strlen( buff );
	for( i=len-1; i>=0; i-- )
	{
		if( buff[i] == ' ' )
			buff[i] = '\0';
		else
			break;
	}
	return( 0 );
}

int	MyErrLog(char *fmt, ...)
{
	time_t		timer;	
	struct	tm	*tblock;
	char		sDate[9];	/* gets time of day */	
	char	fname[200];
	va_list	ap;
	FILE * fp;
	int fd = 0;

	memset(sDate,0,9);
	timer = time(NULL);	/* converts date/time to a structure */	
	tblock = localtime(&timer);	
	sprintf(sDate, "%04d%02d%02d",		tblock->tm_year+1900,tblock->tm_mon+1, tblock->tm_mday);
		
  memset( fname, 0, sizeof(fname) );
  strcpy(fname,"encsvr_pft446.log");
	va_start(ap, fmt);

	if ((fp = fopen(fname, "a+")) == NULL) 
	{
		return (-1);
	}
	fd = fileno(fp);
	lockf(fd, F_LOCK, 0l);
  fprintf( fp, "[%s]", sDate);
	vfprintf(fp, fmt, ap);
	fflush(fp);
	lockf(fd, F_ULOCK, 0l);
	fclose(fp);
	
	va_end(ap);
	return (0);
}

int main ( int argc, char *argv[] )
{
  int		pid1, pid2, pid3, sockfd, i;
  char	pline[200], line[7], buf1[30], buf2[30], buf3[30];
  FILE	*fp;

	if( argc != 2 ) 
	{
    printf("�÷�: encsvr_pft [port] \n");
    printf("��Ϣͷ���ܱ��ĸ�ʽ:2λ��Ϣ����(01)+5λ���ĳ���+�������� \n");
    printf("��Ϣ����ܱ��ĸ�ʽ:2λ��Ϣ����(02)+5λ���ĳ���+�������� \n");
    printf("��Ϣ����ܱ��ĸ�ʽ:2λ��Ϣ����(03)+5λ���ĳ���+�������� \n");
    printf("�ļ���ѹ�����ĸ�ʽ:2λ��Ϣ����(12)+5λ���ĳ���(200)+100λԭ�ļ���+100λ���ļ��� \n");
    printf("�ļ���ѹ�����ĸ�ʽ:2λ��Ϣ����(13)+5λ���ĳ���(200)++100λԭ�ļ���+100λ���ļ��� \n");
    printf("�ļ���Ѻ���ĸ�ʽ:2λ��Ϣ����(14)+5λ���ĳ���(200)++100λԭ�ļ���+100λ���ļ��� \n"); 
    printf("�ļ���Ѻ���ĸ�ʽ:2λ��Ϣ����(15)+5λ���ĳ���(200)++100λԭ�ļ���+100λ���ļ��� \n"); 
    printf("����ʧ�ܱ��ĸ�ʽ:6λʧ�ܷ�����(��000000) \n");
    printf("���سɹ����ĸ�ʽ:6λ�ɹ�������(000000)+5λ���ĳ���+������� \n");
    exit( 0 );
	} 
 
	if( ( pid3 = fork() ) > 0 ) 
	{
    MyErrLog( "�ػ����̽����ɹ�!\n" );
    exit( 0 );
	} 
	else if ( pid3 < 0 ) 
	{   
	 MyErrLog( "�ػ����̽���ʧ��!\n" );
	 exit( -1 );
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGCLD, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	i = atoi( argv[1] );
	MyMsgRecv( i );
	return(0);
}
	
int MyMsgRecv( int port )
{
    int			cpid, sockfd1, sockfd2, addr_len;
    struct sockaddr_in	addr;
    char		temp[20];

    memset( (char *)&addr, 0, sizeof(addr) );
    if( ( sockfd1 = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ) 
    {
	    MyErrLog("����SOCKET����ʧ��!\n" );
	    return(-1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );
    if( bind( sockfd1, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 ) 
    {
	    MyErrLog("SOCKET-BINDʧ��!\n" );
	   return(-1);
    }
    if( getsockname( sockfd1, (struct sockaddr *)&addr, &addr_len ) < 0 ) 
    {
	    MyErrLog("SOCKET-GETSOCKNAMEʧ��!\n" );
	    return(-1);
    }
    if( listen( sockfd1, Qnum ) < 0 ) 
    {
	    MyErrLog("SOCKET-LISTENʧ��!\n" );
	    return(-1);
    }
    addr_len = sizeof(addr);
/*
**��ѭ�����ڷ������ܶԷ���Ϣ
*/
    while( 1 ) 
    {
	     sockfd2 = accept( sockfd1, (struct sockaddr *)&addr, &addr_len );
//�ж�IP�ĺϷ���            strcpy(temp,inet_ntoa(addr.sin_addr));
	     if( ( cpid = fork() ) != 0 ) 
	     {
	       if (  cpid < 0 ) MyErrLog("Fork Error" );
	       close( sockfd2 );
	       continue;
	     }
	     Deal( sockfd2 );
	     close( sockfd2 );
	     close( sockfd1 );
	     exit( 0 );
     }
}


int Deal( int iSockId )
{
	char			msg[MY_DATA_LEN+1];
	char      sTxnTyp[3];
	char      sDatLen[5+1];
	char      sDeaDat[MY_DATA_LEN+1];
	int       iDatLen;	
	int       iRet=-1;
  char      sEndMsg[MY_DATA_LEN + 1];
  int       iEndLen;
  char      sFileIn[100+1];
  char      sFileOut[100+1];
	char 		  sBnkCod[8+1];			/*ֱ�Ӳ����к�*/
	char 		  sDate[8+1];				/*�ļ����е�����*/
	char		  sFileName[100];
	long		  *iErrLine;
	FILE		 	*fp;

  memset( msg, 0, sizeof(msg) );
  memset( sTxnTyp, 0, sizeof(sTxnTyp) );
  memset( sDatLen, 0, sizeof(sDatLen) );
  memset( sDeaDat, 0, sizeof(sDeaDat) );
  memset( sEndMsg, 0, sizeof(sEndMsg) );
    
  if( read( iSockId, &msg, sizeof(msg) ) > 0 ) 
  {
    MyErrLog("�յ���Ϣ��[%s]\n", msg );
    memcpy(sTxnTyp,msg,2);
    MyErrLog("��Ϣ���ͣ�[%s]\n", sTxnTyp );
    memcpy(sDatLen,msg+2,5);
    iDatLen=atoi(sDatLen);
    MyErrLog("��Ϣ���ȣ�[%d]\n", iDatLen );
    memcpy(sDeaDat,msg+7,iDatLen);
    switch(atoi(sTxnTyp))
    { 
      case 1: 
        /*�ӽ��ܱ���ͷ*/
        iRet=DoCypHead(sEndMsg,&iEndLen,sDeaDat,iDatLen);
        if(iRet !=0)
          ReturnErr(iSockId,"000001");
        else
          Return01(iSockId,sEndMsg,iEndLen);
        break;                       
      case 2: 
        /*���ܱ�����*/
        iRet=DoUncBody(sEndMsg,&iEndLen,sDeaDat,iDatLen);
        if(iRet !=0)
          ReturnErr(iSockId,"000002");
        else
          Return01(iSockId,sEndMsg,iEndLen);
        break; 
      case 3: 
        /*���ܱ�����*/
        iRet=DoEncBody(sEndMsg,&iEndLen,sDeaDat,iDatLen);
        if(iRet !=0)
          ReturnErr(iSockId,"000003");
        else
          Return01(iSockId,sEndMsg,iEndLen);        
        break;
      case 12: 
        /*�ļ���ѹ��*/
        memset( sFileIn, 0, sizeof(sFileIn) );
        memset( sFileOut, 0, sizeof(sFileOut) );
        memcpy(sFileIn,sDeaDat,100);
        memcpy(sFileOut,sDeaDat+100,100);
        DelRSpace(sFileIn);
        DelRSpace(sFileOut);
        iRet=sftp_decode(sFileIn,sFileOut);
        if(iRet !=1)
          ReturnErr(iSockId,"000012");
        else
        {
        	iEndLen=strlen(sFileOut);
          Return01(iSockId,sFileOut,iEndLen);
        }
        break;
      case 13: 
        /*�ļ���ѹ��*/
        memset( sFileIn, 0, sizeof(sFileIn) );
        memset( sFileOut, 0, sizeof(sFileOut) );
        memcpy(sFileIn,sDeaDat,100);
        memcpy(sFileOut,sDeaDat+100,100);
        DelRSpace(sFileIn);
        DelRSpace(sFileOut);        
        iRet=sftp_encode(sFileIn,sFileOut);
        if(iRet !=1)
          ReturnErr(iSockId,"000013");
        else
        {
        	iEndLen=strlen(sFileOut);
          Return01(iSockId,sFileOut,iEndLen);
        }
        break;        
      case 14: 
        /*�ļ���Ѻ*/
        memset( sFileIn, 0, sizeof(sFileIn) );
        memset( sFileOut, 0, sizeof(sFileOut) );
        memset( sBnkCod, 0, sizeof(sBnkCod) );
        memset( sDate, 0, sizeof(sDate) );
        memset( sFileName, 0, sizeof(sFileName) );
        memcpy(sFileIn,sDeaDat,100);
        memcpy(sFileOut,sDeaDat+100,100);
        strcpy(sFileName,strrchr(sFileIn,'/')+1) ;
        memcpy(sBnkCod,sFileName+7,2);
        memcpy(sDate,sFileName+15,8);
        DelRSpace(sFileIn);
        DelRSpace(sFileOut);        
    	  MyErrLog("sFileIn=[%s],sFileOut=[%s],sBnkCod=[%s],sDate=[%s]\n", sFileIn,sFileOut,sBnkCod,sDate);
        iRet=rtsb_file_mac_proc_snd(sFileIn,sFileOut,sBnkCod,sDate,0,sMasterKey,iErrLine);
        if(iRet !=1) {
    	  	MyErrLog("��Ѻ����,������=[%d]\n", *iErrLine);
          ReturnErr(iSockId,"000014");
				}	
        else
        {
        	iEndLen=strlen(sFileOut);
          Return01(iSockId,sFileOut,iEndLen);
        }
        break;        
      case 15: 
        /*�ļ���Ѻ*/
        memset( sFileIn, 0, sizeof(sFileIn) );
        memset( sFileOut, 0, sizeof(sFileOut) );
        memset( sBnkCod, 0, sizeof(sBnkCod) );
        memset( sDate, 0, sizeof(sDate) );
        memset( sFileName, 0, sizeof(sFileName) );
        memcpy(sFileIn,sDeaDat,100);
        memcpy(sFileOut,sDeaDat+100,100);
        strcpy(sFileName,strrchr(sFileIn,'/')+1) ;
        memcpy(sBnkCod,sFileName+7,2);
        memcpy(sDate,sFileName+15,8);
    	  MyErrLog("sFileIn=[%s],sFileOut=[%s],sBnkCod=[%s],sDate=[%s]\n", sFileIn,sFileOut,sBnkCod,sDate);
        DelRSpace(sFileIn);
        DelRSpace(sFileOut);        
        iRet=rtsb_file_mac_proc_rcv(sFileIn,sFileOut,sBnkCod,sDate,0,sMasterKey,iErrLine);
        if(iRet !=1) {
    	  	MyErrLog("��Ѻ����,������=[%d]\n", *iErrLine);
          ReturnErr(iSockId,"000015");
				}
        else
        {
        	iEndLen=strlen(sFileOut);
          Return01(iSockId,sFileOut,iEndLen);
        }
        break;        
      default: 
        MyErrLog("���Ĵ����쳣![%s]\n", msg );
        ReturnErr(iSockId,"999999");
        return(-1);
        break; 
    } 	
  } 
  else
  {
   MyErrLog("���ձ����쳣!\n");  	
   return(-1);
  }
  return(0);
}


int ReturnErr( int iSockId, char * RetCod )
{
    write( iSockId, RetCod, 6 );
    MyErrLog("����ʧ�ܱ��ģ�[%s]\n", RetCod );
    return(0);
}

int Return01(int iSockId,char * sEndMsg,int iEndLen)
{
  char sOutMsg[MY_DATA_LEN + 1];
  char sEndLen[5+1];
  int  iOutLen;
 
  memset( sOutMsg, 0, sizeof(sOutMsg) );
  memset( sEndLen, 0, sizeof(sEndLen) );
  
  memcpy(sOutMsg,"000000",6);
  sprintf(sEndLen,"%05d",iEndLen);
  memcpy(sOutMsg+6,sEndLen,5);
  memcpy(sOutMsg+11,sEndMsg,iEndLen);
  iOutLen=iEndLen+11;
  write( iSockId, sOutMsg, iOutLen);
  MyErrLog("���ؽ�����ģ�[%d][%s]\n", iOutLen,sOutMsg );
  return(0);  
}

int DoCypHead(char *sEndMsg,int *iEndLen,char *sDeaDat,int iDatLen)
{
	int iBool;
		
  iBool=rtss_header_code(sEndMsg,iEndLen,sDeaDat,iDatLen,sMasterKey);
  if (iBool ==0)
      return(-1);
  return(0);  
}

int DoUncBody(char *sEndMsg,int *iEndLen,char *sDeaDat,int iDatLen)
{
	int iBool;
		
  iBool=rtss_code_proc_rcv(sEndMsg,iEndLen,sDeaDat,iDatLen,_IsEnc,sMasterKey);
  if (iBool ==0)
    return(-1);
  return(0);  
}

int DoEncBody(char *sEndMsg,int *iEndLen,char *sDeaDat,int iDatLen)
{
	int iBool;
		
  iBool=rtss_code_proc_snd(sEndMsg,iEndLen,sDeaDat,iDatLen,_IsEnc,sMasterKey);
  if (iBool ==0)
    return(-1);
  return(0);  
}
