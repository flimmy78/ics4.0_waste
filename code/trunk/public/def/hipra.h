#ifndef _LIBHIPRA_H_
#define _LIBHIPRA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hidsm.h"
#include "hixml.h"

#define PARA_TRAN_PARAS_SIZE 100
#define PARA_TRAN_SIZE       100
#define PARA_APP_PARAS_SIZE  50
#define PARA_APP_SIZE        10
#define PARA_SERVER_PARAS_SIZE  25
#define PARA_SYSTEM_PARAS_SIZE  20

struct _SystemLevel;
struct _ServerLevel;
struct _ApplicationLevel;
struct _TransactionLevel;

typedef struct _SystemLevel SystemParaSpace;
typedef struct _ServerLevel ServerParaSpace;
typedef struct _ApplicationLevel AppParaSpace;
typedef struct _TransactionLevel TranParaSpace;

struct _SystemLevel
{
  char            * name;
  NamedDataSource * paras;
  struct _ServerLevel  * curr_server;
};
SystemParaSpace * createSystemParaSpace(char * name);
void   destroySystemParaSpace(SystemParaSpace * space); 
int    setServerParaSpace(SystemParaSpace * sys_space, ServerParaSpace *server_space);
int    addSystemPara(SystemParaSpace * sys_space, char *name, char *value);
char * getSystemPara(SystemParaSpace * sys_space, char * name);
TranParaSpace * getTranParaSpaceFromSystemParaSpace(SystemParaSpace * sys_space, char * app_name, char * tran_name);


struct _ServerLevel
{
  char            * name;
  NamedDataSource * paras;
  DataSource * apps;
  SystemParaSpace * system;
};
ServerParaSpace * createServerParaSpace(char * name);
void   destroyServerParaSpace(ServerParaSpace * space); 
int    addAppParaSpace(ServerParaSpace * server_space, AppParaSpace *app_space);
AppParaSpace * getAppParaSpace(ServerParaSpace * app_space, char * app_name);
int    addServerPara(ServerParaSpace  *server_space, char * paraname, char *value);
char * getServerPara(ServerParaSpace  *server_space, char * paraname);


struct _ApplicationLevel
{
  char            * name;
  NamedDataSource * paras;
  DataSource * trans;
  ServerParaSpace * server;
};
AppParaSpace * createAppParaSpace(char * name);
void   destroyAppParaSpace(AppParaSpace * space);      
int    addTranParaSpace(AppParaSpace * app_space, TranParaSpace *tran_space);
TranParaSpace * getTranParaSpace(AppParaSpace * app_space, char * tran_name);
int    addAppPara(AppParaSpace  *app_space, char * paraname, char *value);
char * getAppPara(AppParaSpace  *app_space, char * paraname);

struct _TransactionLevel
{
  char            * name;
  NamedDataSource * paras;
  AppParaSpace    * app;
};
TranParaSpace * createTranParaSpace(char * name);
void   destroyTranParaSpace( TranParaSpace * space);
char * getTranPara(TranParaSpace * paras, char * paraname);
int    addTranPara(TranParaSpace * paras, char * paraname, char *value);


/*-----------------------------------------------------------------------------
**���º������ⲿ����
-----------------------------------------------------------------------------*/
/**
 * ��SYSCFG.XML����ϵͳ������ϵ
 */
SystemParaSpace * constructSystemParaModule(char * syscfg_file, char * server_name);

/**
 * ��Ӧ�ò��������ļ�����Ӧ�ò�����ϵ
 */
AppParaSpace * constructAppParaModuleFromFile(char * appcfg_file, char *appname);
AppParaSpace * constructAppParaModuleFromXmlNode(XmlNode * app_node, char *appname);
TranParaSpace * constructTranParaSpaceFromXmlNode(XmlNode * tran_node);

/**
 * �Ӳ����ռ��л�ȡָ���������Ĳ���ֵ
 */
char * getParaValueFromParaSpace(TranParaSpace * space, char * name);

#endif /*_LIBHIPRA_H_*/
