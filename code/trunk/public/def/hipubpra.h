#ifndef _HIPUBPRA_H_
#define _HIPUBPRA_H_
#include "hibase.h"
#include "hiconstant.h"
#include "hixml.h"

#ifdef _LIB_PUBPRA
#define	EXTERN
#else
#define	EXTERN extern
#endif

/*读取参数*/
EXTERN char * usfGetPubPara(char *name);

/* 读取路径参数
 * 返回为非NULL时，需要调用者释放返回的内存空间
 */
EXTERN char * usfGetPathPara(char *name);

/*
 * 设置参数
 */
EXTERN int usfSetPubPara(char *name, char *value);

/*
 * 装载参数
 * Added by liangwj at 2008-11-04
 */
EXTERN int usfLoadPubPara(char *para_file);

/*
 * 取文件的绝对路径
 * flag取值说明：
   	1：从平台基础目录（WORKDIR）下取
   	2：从应用基础目录（APP_DIR）下取
   	3：先从应用基础目录（APP_DIR）下取，如不存在则在平台基础目录（WORKDIR）取
 */
EXTERN int usfGetFullPath(int flag, char *filename, char *fullpath);

/*
 * 获取本地节点ID
 */
EXTERN char * usfGetLocalID();

/*
 * 获取指定节点的IP
 */
EXTERN long usfGetNodeIP(char *id, char *ip);

/*
 * 获取本地节点IP
 */
EXTERN long usfGetLocalIP(char *ip);

#undef EXTERN
#endif
