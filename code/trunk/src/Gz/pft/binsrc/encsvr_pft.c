static char sqla_program_id[162] = 
{
 0,42,68,65,76,65,73,65,69,78,67,83,86,82,95,80,89,66,119,98,
 79,69,67,97,48,49,49,49,49,32,50,32,0,8,73,67,83,65,68,77,
 32,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "encsvr_pft.sqc"
  
                          
                               
                      
                             
                                
                  
                                                      
                                                      
  
   

#include <signal.h>
#define  __MAIN

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

char sMasterKey[8+1] = "ying5876";
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
 int  len;
 int  i;
 
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

int MyErrLog(char *fmt, ...)
{
 time_t  timer; 
 struct tm *tblock;
 char  sDate[9];                        
 char fname[200];
 va_list ap;
 FILE * fp;
 int fd = 0;

 memset(sDate,0,9);
 timer = time(NULL);                                         
 tblock = localtime(&timer); 
 sprintf(sDate, "%04d%02d%02d",  tblock->tm_year+1900,tblock->tm_mon+1, tblock->tm_mday);
  
  memset( fname, 0, sizeof(fname) );
  strcpy(fname,"encsvr_pft.log");
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
  int  pid1, pid2, pid3, sockfd, i;
  char pline[200], line[7], buf1[30], buf2[30], buf3[30];
  FILE *fp;

 if( argc != 2 ) 
 {
    printf("用法: encsvr_pft [port] \n");
    printf("信息头解密报文格式:2位信息类型(01)+5位正文长度+解密正文 \n");
    printf("信息体解密报文格式:2位信息类型(02)+5位正文长度+解密正文 \n");
    printf("信息体加密报文格式:2位信息类型(03)+5位正文长度+加密正文 \n");
    printf("文件解压缩报文格式:2位信息类型(12)+5位正文长度(200)+100位原文件名+100位新文件名 \n");
    printf("文件加压缩报文格式:2位信息类型(13)+5位正文长度(200)++100位原文件名+100位新文件名 \n");
    printf("返回失败报文格式: 6位失败返回码(非000000) \n");
    printf("返回成功报文格式:6位成功返回码(000000)+5位正文长度+结果正文 \n");
    exit( 0 );
 } 
 
 if( ( pid3 = fork() ) > 0 ) 
 {
    MyErrLog( "守护进程建立成功!\n" );
    exit( 0 );
 } 
 else if ( pid3 < 0 ) 
 {   
  MyErrLog( "守护进程建立失败!\n" );
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
    int   cpid, sockfd1, sockfd2, addr_len;
    struct sockaddr_in addr;
    char  temp[20];

    memset( (char *)&addr, 0, sizeof(addr) );
    if( ( sockfd1 = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ) 
    {
     MyErrLog("建立SOCKET连接失败!\n" );
     return(-1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );
    if( bind( sockfd1, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 ) 
    {
     MyErrLog("SOCKET-BIND失败!\n" );
    return(-1);
    }
    if( getsockname( sockfd1, (struct sockaddr *)&addr, &addr_len ) < 0 ) 
    {
     MyErrLog("SOCKET-GETSOCKNAME失败!\n" );
     return(-1);
    }
    if( listen( sockfd1, Qnum ) < 0 ) 
    {
     MyErrLog("SOCKET-LISTEN失败!\n" );
     return(-1);
    }
    addr_len = sizeof(addr);
  
                            
  
    while( 1 ) 
    {
      sockfd2 = accept( sockfd1, (struct sockaddr *)&addr, &addr_len );
                                                                  
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
 char   msg[MY_DATA_LEN+1];
 char      sTxnTyp[3];
 char      sDatLen[5+1];
 char      sDeaDat[MY_DATA_LEN+1];
 int       iDatLen; 
 int       iRet=-1;
  char      sEndMsg[MY_DATA_LEN + 1];
  int       iEndLen;
  char      sFileIn[100+1];
  char      sFileOut[100+1];

  memset( msg, 0, sizeof(msg) );
  memset( sTxnTyp, 0, sizeof(sTxnTyp) );
  memset( sDatLen, 0, sizeof(sDatLen) );
  memset( sDeaDat, 0, sizeof(sDeaDat) );
  memset( sEndMsg, 0, sizeof(sEndMsg) );
    
  if( read( iSockId, &msg, sizeof(msg) ) > 0 ) 
  {
    MyErrLog("收到信息：[%s]\n", msg );
    memcpy(sTxnTyp,msg,2);
    MyErrLog("信息类型：[%s]\n", sTxnTyp );
    memcpy(sDatLen,msg+2,5);
    iDatLen=atoi(sDatLen);
    MyErrLog("信息长度：[%d]\n", iDatLen );
    memcpy(sDeaDat,msg+7,iDatLen);
    switch(atoi(sTxnTyp))
    { 
      case 1: 
                        
        iRet=DoCypHead(sEndMsg,&iEndLen,sDeaDat,iDatLen);
        if(iRet !=0)
          ReturnErr(iSockId,"000001");
        else
          Return01(iSockId,sEndMsg,iEndLen);
        break;                       
      case 2: 
                      
        iRet=DoUncBody(sEndMsg,&iEndLen,sDeaDat,iDatLen);
        if(iRet !=0)
          ReturnErr(iSockId,"000002");
        else
          Return01(iSockId,sEndMsg,iEndLen);
        break; 
      case 3: 
                      
        iRet=DoEncBody(sEndMsg,&iEndLen,sDeaDat,iDatLen);
        if(iRet !=0)
          ReturnErr(iSockId,"000003");
        else
          Return01(iSockId,sEndMsg,iEndLen);        
        break;
      case 12: 
                      
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
      default: 
        MyErrLog("报文处理异常![%s]\n", msg );
        ReturnErr(iSockId,"999999");
        return(-1);
        break; 
    }  
  } 
  else
  {
   MyErrLog("接收报文异常!\n");   
   return(-1);
  }
  return(0);
}


int ReturnErr( int iSockId, char * RetCod )
{
    write( iSockId, RetCod, 6 );
    MyErrLog("返回失败报文：[%s]\n", RetCod );
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
   MyErrLog("返回结果报文：[%d][%s]\n", iOutLen,sOutMsg );
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
