#ifndef	_HI_DADABASE_
#define	_HI_DADABASE_

#define	DB_USERNAME_MAX_LEN	128			/* 数据库用户名最长					*/
#define	DB_PASSWORD_MAX_LEN	128			/* 数据库密码最长					*/

/*modified by kixiong at 2008-10-30 15:48*/
//#ifdef SYBASE							/* SYBASE 相关的sqlcode宏定义		*/
//#define	SQLCODE				sqlca.sqlcode			/* 返回码 				*/
//#define	SQLERRMSG			sqlca.sqlerrm.sqlerrmc  /* 错误信息				*/
//#define	SQLCOUNT			sqlca.sqlerrd[2]		/* 受影响的记录数		*/
//
//#define	SQL_SUCCESS			0			/* 成功								*/
//#define	SQL_NOTFOUND		100			/* 没有记录							*/
//#define	SQL_ERRSYN			-102		/* 语法错误							*/
//#define	SQL_IVDCOL			-207		/* 无效的字段名						*/
//#define	SQL_IVDOBJ			-208		/* 无效的对象						*/
//#define	SQL_IVDCNN			-33620271	/* 无效的连接						*/
//										/* 或者环境变量的数据库服务名错误	*/
//#define	SQL_IVDCSR			-33620273	/* 无效的游标名，FETCH出错			*/
//#define	SQL_NOTDCL			-16843026	/* 游标未声明，OPEN出错				*/
//#define	SQL_DATOVR			-9502		/* 数据越界							*/
//#define	SQL_ERRPRM			-16843013	/* 参数错误							*/
//										/* 声明和取值的参数个数不一致		*/
//#define	SQL_NULVAL			-16843097	/* 存在NULL值						*/
//#define	SQL_REINSERT		-2601		/* 重复插入错误						*/
//#define	SQL_DELRKERR		-547		/* 外键删除失败						*/
//#endif /* SYBASE */
//
//#ifdef DB2							/* DB2 相关的sqlcode宏定义		*/
//#define	SQLCODE				sqlca.sqlcode			/* 返回码 				*/
//#define	SQLERRMSG			"请查询sqlcode"  		/* 错误信息				*/
//#define	SQLCOUNT			sqlca.sqlerrd[2]		/* 受影响的记录数		*/
//
//#define	SQL_SUCCESS			0			/* 成功								*/
//#define	SQL_NOTFOUND		100			/* 没有记录							*/
//#define	SQL_ERRSYN			-104		/* 语法错误							*/
//#define	SQL_IVDCOL			-206		/* 无效的字段名						*/
//#define	SQL_IVDOBJ			-204		/* 无效的对象						*/
//#define	SQL_IVDCNN			-1024		/* 无效的连接						*/
//										/* 或者环境变量的数据库服务名错误	*/
//#define	SQL_IVDCSR			-501		/* 无效的游标名，FETCH出错			*/
//#define	SQL_NOTDCL			-4946		/* 游标未声明，OPEN出错				*/
//#define	SQL_DATOVR			-433		/* 数据越界							*/
//#define	SQL_ERRPRM			-4943		/* 参数错误							*/
//										/* 声明和取值的参数个数不一致		*/
//#define	SQL_NULVAL			-305		/* 存在NULL值						*/
//#define	SQL_REINSERT		-803		/* 重复插入错误						*/
//#define	SQL_DELRKERR		-547		/* 外键删除失败						*/
//#endif /* DB2 */

/**
 **要求所有的数据库句柄的名字都必须为DBHandle
 **/
#define SQL_SUCCESS		(atol(dbdGetSpecData(DBHandle->driver, "SQL_SUCCESS")))
#define SQL_NOTFOUND	(atol(dbdGetSpecData(DBHandle->driver, "SQL_NOTFOUND")))
#define SQL_ERRSYN	(atol(dbdGetSpecData(DBHandle->driver, "SQL_ERRSYN")))
#define SQL_IVDCOL	(atol(dbdGetSpecData(DBHandle->driver, "SQL_IVDCOL")))
#define SQL_IVDCNN	(atol(dbdGetSpecData(DBHandle->driver, "SQL_IVDCNN")))
#define SQL_IVDCSR	(atol(dbdGetSpecData(DBHandle->driver, "SQL_IVDCSR")))
#define SQL_NOTDCL	(atol(dbdGetSpecData(DBHandle->driver, "SQL_NOTDCL")))
#define SQL_ERRPRM	(atol(dbdGetSpecData(DBHandle->driver, "SQL_ERRPRM")))
#define SQL_NULVAL	(atol(dbdGetSpecData(DBHandle->driver, "SQL_NULVAL")))
#define SQL_REINSERT	(atol(dbdGetSpecData(DBHandle->driver, "SQL_REINSERT")))
#define SQL_DELRKERR	(atol(dbdGetSpecData(DBHandle->driver, "SQL_DELRKERR")))
#define SQLERRMSG	"请查询sqlcode"

#endif /* _HI_DADABASE_ */
