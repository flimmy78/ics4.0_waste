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
  short            ds_num;        /*����Դ����*/
  DBDataSource     **dbds;        /*����Դ�ǼǱ�*/
  DataSourceLeaf   * dslf;
  DataSourceTrunk  * dstk;
};
typedef struct _datasource_container DataSourceContainer;

#ifndef _LIB_DBDSC_
#define EXTERN extern
#else
#define EXTERN
#endif
/*��������Դ����*/
EXTERN DataSourceContainer * dbdscCreate(XmlNode * server_node, int * retcod);
/*��������Դ����*/
EXTERN void dbdscDestroy(DataSourceContainer * dsc);
/*������Դ�����������ݿ�����*/
EXTERN int dbdscGetConn(DataSourceContainer *dsc, 
						char 				*ds_name, 
						DBConHandle 		* handle,
						long				timeout);
/*�黹���ݿ����Ӹ�����Դ����*/
EXTERN int dbdscBackConn(DataSourceContainer *dsc, DBConHandle * handle);

EXTERN XmlNode * dbdscPrintContainerState(DataSourceContainer *dsc);
EXTERN const char * dbdscGetDefaultDS(DataSourceContainer *c);
EXTERN const char * dbdscGetDSNameFromId(DataSourceContainer * dsc, short dsid);
#undef EXTERN

#endif /*_HI_DBDSC_H_*/
