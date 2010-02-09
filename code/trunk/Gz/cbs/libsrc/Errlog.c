/*
 * Project:     交通银行综合业务系统
 * Source :     
 * Version:     V1.0
 * Description: 
 * Authors:     XuHongCan, BaiYue, ChenBin, ChenZhuoHui, XuJian ( NanTian Co. )
 *              Create at 1998/05/10
 * Update History:
 * Date          Position    Author        Description
 * ---------------------------------------------------
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>

#ifndef  ERR_LOG_FILE
#define  ERR_LOG_FILE    "/app/ics/tmp/errlog.8583"
#endif

int GetTime( char * );

void
ErrLog( char *file, int line, char *fmt, ... )
{
    va_list ap;
    FILE   *fp;
    int    fd;
    char timebuf[20];

    if ( (fp=fopen(ERR_LOG_FILE, "a+")) == NULL ) {
        fprintf(stderr, "Open 【%s】 file error.\n", ERR_LOG_FILE);
        return;
    }
    fd = fileno(fp);
    lockf (fd, F_LOCK, 0l);
    GetTime( timebuf );
    fprintf (fp, "\n时间【%s】 ", timebuf );
    fprintf (fp, "文件【%s】中第【%d】行\n", file, line);
    va_start( ap, fmt );
    vfprintf( fp, fmt, ap );
    va_end( ap );
    lockf(fd, F_ULOCK, 0l);
    fclose(fp);
    return;
}
