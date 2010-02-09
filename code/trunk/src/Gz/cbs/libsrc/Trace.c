/*
 * Project:     交通银行综合业务系统
 * Source :     
 * Version:     V1.0
 * Description: 
 * Update History:
 * Date          Position    Author        Description
 * ---------------------------------------------------
 * 1998.05.15    Shanghai    张  兵           Create
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <varargs.h>
#include <time.h>

#ifndef TRACE_LOG_FILE
#define TRACE_LOG_FILE   "/app/ics/tmp/tracelog.8583"
#endif

int
Trace(  va_alist )
va_dcl
{
    va_list ap;
    char   *fmt;    
    FILE   *fp;
    int    fd;
    char timenow[9];

    if( ( fp = fopen( TRACE_LOG_FILE, "a" )) == ( FILE * )NULL )
        return( 0 );

    fd = fileno(fp);
    lockf (fd, F_LOCK, 0l);

    fprintf( fp, "\n");
    GetTime( timenow );fprintf( fp, "%8s  ", timenow );
 
    va_start( ap );
    fmt = va_arg( ap, char * );
    va_end( ap );
    vfprintf( fp, fmt, ap );
    fflush( fp );
    lockf(fd, F_ULOCK, 0l);
    fclose( fp );
}

int 
GetTime( char *bp )
  {
    long t;
    struct tm *tbp;

    time( ( long * )&t );
    tbp = localtime( &t );
    IntToStr( bp, tbp->tm_hour, 2 );
    bp[2] = ':';
    IntToStr( bp + 3, tbp->tm_min, 2 );
    bp[5] = ':';
    IntToStr( bp + 6, tbp->tm_sec, 2 );
    bp[8] = '\0';
  }

int 
IntToStr( unsigned char *bp, unsigned int s, int len )
  {
    register int i;

    for ( i = len - 1; i >= 0; i -- )
      {
        bp[i] = ( unsigned char )( s % 10 ) + '0';
        s = s / 10; 
      }
    return ( s );
  }

