#ifndef	_HI_DADABASE_
#define	_HI_DADABASE_

#define	DB_USERNAME_MAX_LEN	128			/* ���ݿ��û����					*/
#define	DB_PASSWORD_MAX_LEN	128			/* ���ݿ������					*/

/*modified by kixiong at 2008-10-30 15:48*/
//#ifdef SYBASE							/* SYBASE ��ص�sqlcode�궨��		*/
//#define	SQLCODE				sqlca.sqlcode			/* ������ 				*/
//#define	SQLERRMSG			sqlca.sqlerrm.sqlerrmc  /* ������Ϣ				*/
//#define	SQLCOUNT			sqlca.sqlerrd[2]		/* ��Ӱ��ļ�¼��		*/
//
//#define	SQL_SUCCESS			0			/* �ɹ�								*/
//#define	SQL_NOTFOUND		100			/* û�м�¼							*/
//#define	SQL_ERRSYN			-102		/* �﷨����							*/
//#define	SQL_IVDCOL			-207		/* ��Ч���ֶ���						*/
//#define	SQL_IVDOBJ			-208		/* ��Ч�Ķ���						*/
//#define	SQL_IVDCNN			-33620271	/* ��Ч������						*/
//										/* ���߻������������ݿ����������	*/
//#define	SQL_IVDCSR			-33620273	/* ��Ч���α�����FETCH����			*/
//#define	SQL_NOTDCL			-16843026	/* �α�δ������OPEN����				*/
//#define	SQL_DATOVR			-9502		/* ����Խ��							*/
//#define	SQL_ERRPRM			-16843013	/* ��������							*/
//										/* ������ȡֵ�Ĳ���������һ��		*/
//#define	SQL_NULVAL			-16843097	/* ����NULLֵ						*/
//#define	SQL_REINSERT		-2601		/* �ظ��������						*/
//#define	SQL_DELRKERR		-547		/* ���ɾ��ʧ��						*/
//#endif /* SYBASE */
//
//#ifdef DB2							/* DB2 ��ص�sqlcode�궨��		*/
//#define	SQLCODE				sqlca.sqlcode			/* ������ 				*/
//#define	SQLERRMSG			"���ѯsqlcode"  		/* ������Ϣ				*/
//#define	SQLCOUNT			sqlca.sqlerrd[2]		/* ��Ӱ��ļ�¼��		*/
//
//#define	SQL_SUCCESS			0			/* �ɹ�								*/
//#define	SQL_NOTFOUND		100			/* û�м�¼							*/
//#define	SQL_ERRSYN			-104		/* �﷨����							*/
//#define	SQL_IVDCOL			-206		/* ��Ч���ֶ���						*/
//#define	SQL_IVDOBJ			-204		/* ��Ч�Ķ���						*/
//#define	SQL_IVDCNN			-1024		/* ��Ч������						*/
//										/* ���߻������������ݿ����������	*/
//#define	SQL_IVDCSR			-501		/* ��Ч���α�����FETCH����			*/
//#define	SQL_NOTDCL			-4946		/* �α�δ������OPEN����				*/
//#define	SQL_DATOVR			-433		/* ����Խ��							*/
//#define	SQL_ERRPRM			-4943		/* ��������							*/
//										/* ������ȡֵ�Ĳ���������һ��		*/
//#define	SQL_NULVAL			-305		/* ����NULLֵ						*/
//#define	SQL_REINSERT		-803		/* �ظ��������						*/
//#define	SQL_DELRKERR		-547		/* ���ɾ��ʧ��						*/
//#endif /* DB2 */

/**
 **Ҫ�����е����ݿ��������ֶ�����ΪDBHandle
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
#define SQLERRMSG	"���ѯsqlcode"

#endif /* _HI_DADABASE_ */
