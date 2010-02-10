#ifndef _HI_DBDSC_H_
#define _HI_DBDSC_H_

#include "hidbds.h"
#include "hixml.h"
#include "libdbalog.h"

struct _datasource_leaf {
	DBDataSource		* ds;
	unsigned int		radix;
	unsigned int		remain;
	struct _datasource_leaf * next;
};
typedef struct _datasource_leaf DataSourceLeaf;

struct _datasource_trunk {
	char					* name;
	unsigned int			ds_leaf_num;
	DataSourceLeaf			* leaf_head;
	pthread_mutex_t			lock;
	DataSourceLeaf			* curr;
	struct _datasource_trunk	* next;
};
typedef struct _datasource_trunk DataSourceTrunk;

struct _datasource_container {
  short            ds_num;        /*数据源数量*/
  DBDataSource     **dbds;        /*数据源登记表*/
  DataSourceLeaf   * dslf;
  DataSourceTrunk  * dstk;
};
typedef struct _datasource_container DataSourceContainer;

#ifndef _LIB_DBDSC_
#define EXTERN extern
#else
#define EXTERN
#endif
/*创建数据源容器*/
EXTERN DataSourceContainer * dbdscCreate(XmlNode * server_node, int * retcod);
/*销毁数据源容器*/
EXTERN void dbdscDestroy(DataSourceContainer * dsc);
/*从数据源容器申请数据库连接*/
EXTERN int dbdscGetConn(DataSourceContainer *dsc, 
						char 				*ds_name, 
						DBConHandle 		* handle,
						long				timeout);
/*归还数据库连接给数据源容器*/
EXTERN int dbdscBackConn(DataSourceContainer *dsc, DBConHandle * handle);

EXTERN XmlNode * dbdscPrintContainerState(DataSourceContainer *dsc);
EXTERN const char * dbdscGetDefaultDS(DataSourceContainer *c);
EXTERN const char * dbdscGetDSNameFromId(DataSourceContainer * dsc, short dsid);
#undef EXTERN

#endif /*_HI_DBDSC_H_*/
