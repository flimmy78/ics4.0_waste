#ifndef _HI_DBDS_H_
#define _HI_DBDS_H_

#include "hidbhdl.h"
#include "hidbdriver.h"
#include "libdbalog.h"
#include "hidbpool.h"
#include <pthread.h>

struct _db_datasource {
	short        id;                /*数据源ID*/
	char         * name;            /*数据源名称*/
	DBDriver     * driver;          /*数据库驱动*/
	DBConnPool   * pool;            /*数据库连接池*/
	pthread_t    test_thread;       /*数据库连接检测线索*/
	unsigned int test_interval;     /*检测时间间隔*/
	short int    max_reconn_times;  /*最大重连接次数*/
};
typedef struct _db_datasource DBDataSource;

#ifndef _LIB_DBDS_
#define EXTERN extern
#else
#define EXTERN
#endif

/*创建数据源*/
EXTERN DBDataSource * dbdsCreate(   short id, \
									char * ds_name, \
									char * ds_type, \
									char * driver_name, \
									int pool_size, \
									unsigned int test_interval, \
									short max_reconn_times, \
									XmlNode * conn_info);
/*销毁数据源*/
EXTERN void dbdsDestroy(DBDataSource * dbds);

/*从数据源获取数据库连接*/
EXTERN int dbdsGetConn(DBDataSource * dbds, DBConHandle * handle, long timeout);

/*返回数据库连接给数据源*/
EXTERN int dbdsBackConn(DBDataSource *dbds, DBConHandle * handle);

/*获取数据源名字*/
EXTERN const char * dbdsGetName(DBDataSource *dbds);

EXTERN XmlNode * dbdsPrintState(DBDataSource *ds);
#undef EXTERN

#endif /*_HI_DBDS_H_*/
