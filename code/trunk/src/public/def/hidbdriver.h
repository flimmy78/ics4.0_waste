#ifndef _HI_DB_DRIVER_
#define _HI_DB_DRIVER_

#include "libdbalog.h"
#include "hietf.h"
#include "hixml.h"
#include "hash.h"

#define DRIVER_DB_SPECDATA_FILE "etc/DBSPECSQL_PUB.XML"

typedef void * conn_context;

struct _db_driver {
	/*目标数据库类型*/
	char * db_type;
	/*驱动程序文件*/
	char * driver_file;  
	/*驱动程序句柄*/
	void * driver_handle;
	/*驱动私有数据*/
	void * driver_data;
	/*目标数据库个性数据*/
	hash_t * db_specdatas;
	/*动态执行SQL查询语句*/   
	int (*dbtsqlquery)(ETF *, char *, int *, conn_context, long *sqlcode);
	/*动态执行SQL查询语句（带记录数限制）*/
	int (*dbtsqlquery_limit)(ETF *, char *, int, int *, conn_context, long *sqlcode);
	/*动态执行SQL查询语句(生成一条记录)*/
	int (*dbtsqlqueryrec)(ETF *, char *, conn_context, long *sqlcode);
	/*根据ETF数据在表中插入一条记录*/
	int (*dbtsqlinsrec)(ETF *, char *, conn_context, long *sqlcode);
	/*查询表的一条记录并输出到ETF树*/
	int (*dbtsqlrdrec)(ETF *, char *, char *, char *, int, conn_context, long *sqlcode);
	/*根据ETF数据更新表的一条记录*/
	int (*dbtsqlupdrec)(ETF *, char *, char *, char *, int, conn_context, long *sqlcode);
	/*动态执行SQL查询语句*/
	int (*dbtsqlqueryxml)(ETF *, char *, int *, conn_context, long *sqlcode);
	/*根据ETF数据在表中插入一条记录(从XML配置中取表数据字典) */
	int (*dbtsqlinsrecxml)(ETF *, XmlNode *, char *, conn_context, long *sqlcode);
	/*查询表的一条记录并输出到ETF树*/
	int (*dbtsqlrdrecxml)(ETF *, char *, char *, char *, int, conn_context, long *sqlcode);
	/*根据ETF数据更新表的一条记录(从XML配置中取表数据字典) */
	int (*dbtsqlupdrecxml)(ETF *, XmlNode *, char *, char *, char *, int, conn_context, long *sqlcode);
	/*根据ETF数据删除表的一条记录(从XML配置中取表数据字典) */
	int (*dbtsqldelrecdaxml)(ETF *, XmlNode *, char *, char *, conn_context, long *sqlcode);
	/*动态SQL游标操作*/
	int (*dbtsqlcursor)(ETF *, char *, void **, unsigned char, conn_context, long *sqlcode);
	/*根据条件语句查询扩展表的多条记录并输出到ETF树*/
	int (*dbtextquery)(ETF *, char *, char *, int *, conn_context, long *sqlcode);
	/*根据条件语句查询扩展表的多条记录并输出到ETF树（带记录数限制）*/
	int (*dbtextquery_limit)(ETF *, char *, char *, int, int *, conn_context, long *sqlcode);
	/*根据ETF数据在扩展表中插入一条记录*/
	int (*dbtextinsrec)(ETF *, char *, conn_context, long *sqlcode);
	/*根据ETF数据在扩展表中插入一条记录(从XML配置中取表数据字典) */
	int (*dbtextinsrecxml)(ETF *, XmlNode *, char *, conn_context, long *sqlcode);
	/*根据条件语句查询扩展表的一条记录并输出到ETF树*/
	int (*dbtextrdreccon)(ETF *, char *, char *, conn_context, long *sqlcode);
	/*根据条件语句删除扩展表的一条记录*/
	int (*dbtextdelreccon)(char *, char *, conn_context, long *sqlcode);
	/*根据条件语句由ETF数据更新扩展表的一条记录*/
	int (*dbtextupdreccon)(ETF *, char *, char *, conn_context, long *sqlcode);
	/*根据条件语句由ETF数据更新扩展表的一条记录(从XML配置中取表数据字典) */
	int (*dbtextupdrecconxml)(ETF *, XmlNode *, char *, char *, conn_context, long *sqlcode);
	/*包含扩展表的动态SQL游标操作*/
	int (*dbtextcursor)(ETF *, char *, char *, void **, unsigned char, conn_context, long *sqlcode);
	/*根据ETF数据更新表的一条记录(从XML配置中取表数据字典)*/
	int (*dbtsqlupdrecdaxml)( ETF *, XmlNode *, char *, char *, conn_context, long *);
	/*动态SQL游标操作(可指定游标名CURSOR_X)*/
	int (*dbtsqlcursor_x)(ETF *, char *, void **, unsigned char, char *, conn_context, long *);
	int (*dbtextcursor_x)(ETF *, char *, char *, void **, char, char *, conn_context, long *);
	/* 功能：数据库连接有效性测试
	 * 输入：参数一　数据库上下文
	 　输出：参数二　SQLCODE
	 * 返回：0  -- 连接有效
	 *       1  -- 连接失效
	 *      <0  -- Others Errors
	 */
	int (*dbttestdbconn)(void * driver_data, conn_context ctx, long *sqlcode);
	
	/*连接数据库*/
	int (*dbtconndb)(void * driver_data, conn_context * ctx, long *sqlcode);
	/*关闭数据库连接*/
	int (*dbtclosedbconn)(void * driver_data, conn_context  ctx, long *sqlcode);
	/*设置上下文*/
	int (*dbtsetctx)(void * driver_data, conn_context ctx, long *sqlcode);
	/*取消上下文*/
	int (*dbtunsetctx)(void * driver_data, conn_context ctx, long *sqlcode);
	/*回滚事务*/
	int (*dbtrollback)(conn_context, long *sqlcode);
	/*提交事务*/
	int (*dbtcommit)(conn_context, long *sqlcode);
	/*执行非查询SQL语句*/
	int (*dbtexecsql)(char * sql_cmd, conn_context, long *sqlcode);
	/*驱动初始化*/
	void * (*dbtinitdriver)(XmlNode * init_info);
	/*驱动退出，完成驱动的资源释放（不包括连接，连接由dba关闭）*/
     void (*dbtenddriver)(void * driver_data);
};

typedef struct _db_driver DBDriver;

#ifndef _LIB_HI_DRIVER_
#define EXTERN extern
#else
#define EXTERN 
#endif
EXTERN DBDriver * loadDBDriver(char * driver_name, char * db_type, XmlNode * db_info);
EXTERN void deleteDBDriver(DBDriver * driver);
EXTERN char * dbdGetSpecData(DBDriver * driver, char * name);
#undef EXTERN

#endif /*_HI_DB_DRIVER_*/
