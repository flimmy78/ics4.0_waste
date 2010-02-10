#ifndef _HI_DBPOOL_H_
#define _HI_DBPOOL_H_

#include "hidbhdl.h"
#include "hidbdriver.h"
#include "hixml.h"
#include "libdbalog.h"

struct _context_entry{
	short			id;				/*entry id*/
	conn_context	ctx;			/*context*/
	short			rpt; 			/*repair times*/
	struct _context_entry  * next;
};
typedef struct _context_entry ContextEntry;

struct _db_conn_pool {
	short          conn_num;       /*总连接数*/
	short          busy_num;       /*忙碌连接数*/
	short          ill_num;        /*无效连接数*/
	short          idle_num;       /*空闲连接数*/
	ContextEntry   * space;        /*连接条目存储空间指针*/
	ContextEntry   * idle_head;    /*空闲连接链表*/
	ContextEntry   * ill_head;     /*失效连接链表*/
	ContextEntry   ** busy_conn;   /*忙碌连接登记表*/
	XmlNode		   * conn_info;    /*数据库连接信息*/
	pthread_mutex_t con_lock;      /*条件锁*/
	pthread_cond_t  con_cond;      /*条件变量*/
};
typedef struct _db_conn_pool DBConnPool;

#ifndef _LIB_DB_POOL_
#define EXTERN extern
#else
#define EXTERN
#endif
  
/*创建数据库连接池*/
EXTERN DBConnPool * dbcpCreate(int num, DBDriver * driver, XmlNode * info);
/*销毁数据库连接池*/
EXTERN void dbcpDestroy(DBConnPool * dbpool, DBDriver * driver);
/*返回数据库连接*/
EXTERN int dbcpBackConn(DBConnPool * dbpool, DBConHandle * handle);
/*获取数据库连接*/
EXTERN int dbcpGetConn(DBConnPool * dbpool, 
						   DBConHandle * handle, 
						   long timeout);
/*数据库连接池是否可用*/
EXTERN int dbcpIsUseable(DBConnPool * dbpool);
/*返回当前数据库信息*/
EXTERN  XmlNode * dbcpPrintState(DBConnPool * dbpool);
/*检查并修复失效的数据库连接*/
EXTERN  int dbcpCheckAndRepair(DBConnPool * dbpool, 
							   DBDriver * driver, 
							   short max_times,
							   int	* ill_count,
							   int  * repaied_count);
#undef EXTERN

#endif /*_HI_DBPOOL_H_*/
