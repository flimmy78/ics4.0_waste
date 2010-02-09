#ifndef _HI_DB_DRIVER_
#define _HI_DB_DRIVER_

#include "libdbalog.h"
#include "hietf.h"
#include "hixml.h"
#include "hash.h"

#define DRIVER_DB_SPECDATA_FILE "etc/DBSPECSQL_PUB.XML"

typedef void * conn_context;

struct _db_driver {
	/*Ŀ�����ݿ�����*/
	char * db_type;
	/*���������ļ�*/
	char * driver_file;  
	/*����������*/
	void * driver_handle;
	/*����˽������*/
	void * driver_data;
	/*Ŀ�����ݿ��������*/
	hash_t * db_specdatas;
	/*��ִ̬��SQL��ѯ���*/   
	int (*dbtsqlquery)(ETF *, char *, int *, conn_context, long *sqlcode);
	/*��ִ̬��SQL��ѯ��䣨����¼�����ƣ�*/
	int (*dbtsqlquery_limit)(ETF *, char *, int, int *, conn_context, long *sqlcode);
	/*��ִ̬��SQL��ѯ���(����һ����¼)*/
	int (*dbtsqlqueryrec)(ETF *, char *, conn_context, long *sqlcode);
	/*����ETF�����ڱ��в���һ����¼*/
	int (*dbtsqlinsrec)(ETF *, char *, conn_context, long *sqlcode);
	/*��ѯ���һ����¼�������ETF��*/
	int (*dbtsqlrdrec)(ETF *, char *, char *, char *, int, conn_context, long *sqlcode);
	/*����ETF���ݸ��±��һ����¼*/
	int (*dbtsqlupdrec)(ETF *, char *, char *, char *, int, conn_context, long *sqlcode);
	/*��ִ̬��SQL��ѯ���*/
	int (*dbtsqlqueryxml)(ETF *, char *, int *, conn_context, long *sqlcode);
	/*����ETF�����ڱ��в���һ����¼(��XML������ȡ�������ֵ�) */
	int (*dbtsqlinsrecxml)(ETF *, XmlNode *, char *, conn_context, long *sqlcode);
	/*��ѯ���һ����¼�������ETF��*/
	int (*dbtsqlrdrecxml)(ETF *, char *, char *, char *, int, conn_context, long *sqlcode);
	/*����ETF���ݸ��±��һ����¼(��XML������ȡ�������ֵ�) */
	int (*dbtsqlupdrecxml)(ETF *, XmlNode *, char *, char *, char *, int, conn_context, long *sqlcode);
	/*����ETF����ɾ�����һ����¼(��XML������ȡ�������ֵ�) */
	int (*dbtsqldelrecdaxml)(ETF *, XmlNode *, char *, char *, conn_context, long *sqlcode);
	/*��̬SQL�α����*/
	int (*dbtsqlcursor)(ETF *, char *, void **, unsigned char, conn_context, long *sqlcode);
	/*������������ѯ��չ��Ķ�����¼�������ETF��*/
	int (*dbtextquery)(ETF *, char *, char *, int *, conn_context, long *sqlcode);
	/*������������ѯ��չ��Ķ�����¼�������ETF��������¼�����ƣ�*/
	int (*dbtextquery_limit)(ETF *, char *, char *, int, int *, conn_context, long *sqlcode);
	/*����ETF��������չ���в���һ����¼*/
	int (*dbtextinsrec)(ETF *, char *, conn_context, long *sqlcode);
	/*����ETF��������չ���в���һ����¼(��XML������ȡ�������ֵ�) */
	int (*dbtextinsrecxml)(ETF *, XmlNode *, char *, conn_context, long *sqlcode);
	/*������������ѯ��չ���һ����¼�������ETF��*/
	int (*dbtextrdreccon)(ETF *, char *, char *, conn_context, long *sqlcode);
	/*�����������ɾ����չ���һ����¼*/
	int (*dbtextdelreccon)(char *, char *, conn_context, long *sqlcode);
	/*�������������ETF���ݸ�����չ���һ����¼*/
	int (*dbtextupdreccon)(ETF *, char *, char *, conn_context, long *sqlcode);
	/*�������������ETF���ݸ�����չ���һ����¼(��XML������ȡ�������ֵ�) */
	int (*dbtextupdrecconxml)(ETF *, XmlNode *, char *, char *, conn_context, long *sqlcode);
	/*������չ��Ķ�̬SQL�α����*/
	int (*dbtextcursor)(ETF *, char *, char *, void **, unsigned char, conn_context, long *sqlcode);
	/*����ETF���ݸ��±��һ����¼(��XML������ȡ�������ֵ�)*/
	int (*dbtsqlupdrecdaxml)( ETF *, XmlNode *, char *, char *, conn_context, long *);
	/*��̬SQL�α����(��ָ���α���CURSOR_X)*/
	int (*dbtsqlcursor_x)(ETF *, char *, void **, unsigned char, char *, conn_context, long *);
	int (*dbtextcursor_x)(ETF *, char *, char *, void **, char, char *, conn_context, long *);
	/* ���ܣ����ݿ�������Ч�Բ���
	 * ���룺����һ�����ݿ�������
	 ���������������SQLCODE
	 * ���أ�0  -- ������Ч
	 *       1  -- ����ʧЧ
	 *      <0  -- Others Errors
	 */
	int (*dbttestdbconn)(void * driver_data, conn_context ctx, long *sqlcode);
	
	/*�������ݿ�*/
	int (*dbtconndb)(void * driver_data, conn_context * ctx, long *sqlcode);
	/*�ر����ݿ�����*/
	int (*dbtclosedbconn)(void * driver_data, conn_context  ctx, long *sqlcode);
	/*����������*/
	int (*dbtsetctx)(void * driver_data, conn_context ctx, long *sqlcode);
	/*ȡ��������*/
	int (*dbtunsetctx)(void * driver_data, conn_context ctx, long *sqlcode);
	/*�ع�����*/
	int (*dbtrollback)(conn_context, long *sqlcode);
	/*�ύ����*/
	int (*dbtcommit)(conn_context, long *sqlcode);
	/*ִ�зǲ�ѯSQL���*/
	int (*dbtexecsql)(char * sql_cmd, conn_context, long *sqlcode);
	/*������ʼ��*/
	void * (*dbtinitdriver)(XmlNode * init_info);
	/*�����˳��������������Դ�ͷţ����������ӣ�������dba�رգ�*/
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
