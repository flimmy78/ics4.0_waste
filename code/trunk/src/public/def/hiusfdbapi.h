#ifndef _HI_USF_DB_API_H_
#define _HI_USF_DB_API_H_

#include "hidbhdl.h"

#ifndef _LIB_USF_DB_API_
#define EXTERN extern
#else
#define EXTERN
#endif /*_LIB_USF_DB_API_*/

EXTERN int usfSetDBAccessEnv(void * lib_handle);
EXTERN int initDBConnectionPool(void);
EXTERN void	freeDBConnectionPool(void);
EXTERN int setDBEnvForTaskModule(void);
EXTERN int usfOpenDBConnection(const char * ds_name, DBConHandle * handle, long timeout);
EXTERN int usfCloseDBConnection(DBConHandle * handle);
EXTERN int usfCloseAllDBConnection(void);
EXTERN int usfDBIsConnected(const char * ds_name);
EXTERN int usfSetDBContext(DBConHandle *handle);
EXTERN DBConHandle * usfGetCurrConnHandle(void);
EXTERN int usfSwitchDataSource(DBConHandle * handle, const char * ds_name, long timeout);
EXTERN short usfSwitchToSysDS(DBConHandle * handle, long timeout);
EXTERN int usfSwitchToDsOfID(DBConHandle * handle, short ds_id, long timeout);
#undef EXTERN
#endif/*_HI_USF_DB_API_H_*/
