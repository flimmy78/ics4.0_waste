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
	short          conn_num;       /*��������*/
	short          busy_num;       /*æµ������*/
	short          ill_num;        /*��Ч������*/
	short          idle_num;       /*����������*/
	ContextEntry   * space;        /*������Ŀ�洢�ռ�ָ��*/
	ContextEntry   * idle_head;    /*������������*/
	ContextEntry   * ill_head;     /*ʧЧ��������*/
	ContextEntry   ** busy_conn;   /*æµ���ӵǼǱ�*/
	XmlNode		   * conn_info;    /*���ݿ�������Ϣ*/
	pthread_mutex_t con_lock;      /*������*/
	pthread_cond_t  con_cond;      /*��������*/
};
typedef struct _db_conn_pool DBConnPool;

#ifndef _LIB_DB_POOL_
#define EXTERN extern
#else
#define EXTERN
#endif
  
/*�������ݿ����ӳ�*/
EXTERN DBConnPool * dbcpCreate(int num, DBDriver * driver, XmlNode * info);
/*�������ݿ����ӳ�*/
EXTERN void dbcpDestroy(DBConnPool * dbpool, DBDriver * driver);
/*�������ݿ�����*/
EXTERN int dbcpBackConn(DBConnPool * dbpool, DBConHandle * handle);
/*��ȡ���ݿ�����*/
EXTERN int dbcpGetConn(DBConnPool * dbpool, 
						   DBConHandle * handle, 
						   long timeout);
/*���ݿ����ӳ��Ƿ����*/
EXTERN int dbcpIsUseable(DBConnPool * dbpool);
/*���ص�ǰ���ݿ���Ϣ*/
EXTERN  XmlNode * dbcpPrintState(DBConnPool * dbpool);
/*��鲢�޸�ʧЧ�����ݿ�����*/
EXTERN  int dbcpCheckAndRepair(DBConnPool * dbpool, 
							   DBDriver * driver, 
							   short max_times,
							   int	* ill_count,
							   int  * repaied_count);
#undef EXTERN

#endif /*_HI_DBPOOL_H_*/
