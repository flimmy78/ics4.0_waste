#ifndef _HI_DBCONN_HANDLE_H_
#define _HI_DBCONN_HANDLE_H_
#include <stdio.h>
#include "hidbdriver.h"

struct _db_con_handle {
	short         ds_id;		/* 数据源id */
	short         con_id;		/* 数据库连接id */
	conn_context  ctx;			/* 上下文 */
	DBDriver      * driver;		/* 数据库驱动 */
};
typedef struct _db_con_handle DBConHandle;

struct _db_conn_rec {
	char                  * ds_name;   /*数据源名称*/
	short                 ds_id;       /*数据源ID*/
	DBConHandle          * handle;    /*数据库连接*/
	struct _db_conn_rec   * next;
};
typedef struct _db_conn_rec DBConnRec;

#ifndef _LIB_DBCONN_HANDLE_
#define EXTERN extern
#else
#define EXTERN
#endif

EXTERN DBConnRec * hdlAddConnRec(DBConnRec ** head, char * ds_name, short ds_id, DBConHandle * handle);
EXTERN int hdlDelConnRec(DBConnRec ** head, DBConHandle * handle);
EXTERN int hdlDelAllConnRec(DBConnRec ** head);
EXTERN DBConnRec * hdlQryConnRec(const DBConnRec * head, const char * ds_name);

#undef EXTERN

#endif /*_HI_DBCONN_HANDLE_H_*/
