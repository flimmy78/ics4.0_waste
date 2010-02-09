#ifndef _HI_DBDS_H_
#define _HI_DBDS_H_

#include "hidbhdl.h"
#include "hidbdriver.h"
#include "libdbalog.h"
#include "hidbpool.h"
#include <pthread.h>

struct _db_datasource {
	short        id;                /*����ԴID*/
	char         * name;            /*����Դ����*/
	DBDriver     * driver;          /*���ݿ�����*/
	DBConnPool   * pool;            /*���ݿ����ӳ�*/
	pthread_t    test_thread;       /*���ݿ����Ӽ������*/
	unsigned int test_interval;     /*���ʱ����*/
	short int    max_reconn_times;  /*��������Ӵ���*/
};
typedef struct _db_datasource DBDataSource;

#ifndef _LIB_DBDS_
#define EXTERN extern
#else
#define EXTERN
#endif

/*��������Դ*/
EXTERN DBDataSource * dbdsCreate(   short id, \
									char * ds_name, \
									char * ds_type, \
									char * driver_name, \
									int pool_size, \
									unsigned int test_interval, \
									short max_reconn_times, \
									XmlNode * conn_info);
/*��������Դ*/
EXTERN void dbdsDestroy(DBDataSource * dbds);

/*������Դ��ȡ���ݿ�����*/
EXTERN int dbdsGetConn(DBDataSource * dbds, DBConHandle * handle, long timeout);

/*�������ݿ����Ӹ�����Դ*/
EXTERN int dbdsBackConn(DBDataSource *dbds, DBConHandle * handle);

/*��ȡ����Դ����*/
EXTERN const char * dbdsGetName(DBDataSource *dbds);

EXTERN XmlNode * dbdsPrintState(DBDataSource *ds);
#undef EXTERN

#endif /*_HI_DBDS_H_*/
