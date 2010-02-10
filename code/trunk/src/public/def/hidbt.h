#ifndef _HIDBT_H_
#define _HIDBT_H_

#include "hiserver.h"
#include "hietf.h"

#define  _MAX_COLUMNS			128
#define  _INI_VAL_LEN			512
#define  _MAX_SQL_LEN			6144
#define  _MAX_SQL_COL_LEN		1024
#define	 _MAX_SQL_VAL_LEN		5120
#define  _TBLNAM_MAX_LEN		30
#define  _MAX_COL_VAL_LEN		4096
#define  _MAX_COL_NAM_LEN		30
#define  _MAX_CHAR_FOR_DOUBLE	20
#define  _MAX_CHAR_FOR_LONG		15
#define  _MAX_CHAR_FOR_DATETIME	30
#define  _MAX_CHAR_FOR_DEFAULT	100

/* modified by yuqj, use SQL_IVDCOL to replace it
#define  _DB_NO_COL			-207
*/

#ifdef DB2
#include <sqlenv.h>
#include <sqlcodes.h>
#include <sqlda.h>
typedef struct sqlda SQLDA;
#endif

#ifdef _LIB_DBT_EXTERN_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

EXTERN int dbtextquery(ETF *, char *, char *, int *, DBConHandle *);
EXTERN int dbtextquery_limit(ETF *, char *, char *, int, int *, DBConHandle *);
EXTERN int dbtextinsrec(ETF *, char *, DBConHandle *);
EXTERN int dbtextinsrecxml(ETF *, XmlNode *, char *, DBConHandle *);
EXTERN int dbtextrdreccon(ETF *, char *, char *, DBConHandle *);
EXTERN int dbtextdelreccon(char *, char *, DBConHandle *);
EXTERN int dbtextupdreccon(ETF *, char *, char *, DBConHandle *);
EXTERN int dbtextupdrecconxml(ETF *, XmlNode *, char *, char *, DBConHandle *);
/*
EXTERN int dbtextcursor(ETF *, char *, char *, SQLDA **, unsigned char, DBConHandle *);
*/

EXTERN int dbtsqlquery(ETF *, char *, int *, DBConHandle *);
EXTERN int dbtsqlquery_limit(ETF *, char *, int, int *, DBConHandle *);
EXTERN int dbtsqlqueryrec(ETF *, char *, DBConHandle *);
EXTERN int dbtsqlinsrec(ETF *, char *, DBConHandle *);
EXTERN int dbtsqlrdrec(ETF *, char *, char *, char *, int, DBConHandle *);
EXTERN int dbtsqlupdrec(ETF *, char *, char *, char *, int, DBConHandle *);
EXTERN int dbtsqlqueryxml(ETF *, char *, int *, DBConHandle *);
EXTERN int dbtsqlinsrecxml(ETF *, XmlNode *, char *, DBConHandle *);
EXTERN int dbtsqlrdrecxml(ETF *, char *, char *, char *, int, DBConHandle *);
EXTERN int dbtsqlupdrecxml(ETF *, XmlNode *, char *, char *, char *, int, DBConHandle *);
EXTERN int dbtsqldelrecdaxml(ETF *, XmlNode *, char *, char *, DBConHandle *);
/*
EXTERN int dbtsqlcursor(ETF *, char *, SQLDA **, unsigned char, DBConHandle *);
*/

EXTERN int mallocsqlda( SQLDA **, int );
EXTERN int initsqlda( SQLDA * );
EXTERN int freesqlda( SQLDA * );
EXTERN char * readCol(SQLDA *, short);
#undef	EXTERN

#ifdef _LIB_DBBASE_EXTERN_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

EXTERN int dbtConnectDB(char *, char *, char *);
EXTERN int dbtDisconnectDB(int);
EXTERN int dbtCommit(char *);
EXTERN int dbtRollback(char *);
#undef	EXTERN

#endif /* _HIDBT_H_ */ 

