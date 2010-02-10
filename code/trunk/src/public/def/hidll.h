/*
 * History: Date         Position        Author        Action
 * ----------------------------------------------------------------------------
 *          2000-12-11   ShangHai        L.Ben         Create
 ******************************************************************************/

#ifndef _HIDLL_H_
#define _HIDLL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <errno.h>
#include <pthread.h>
#include "hiconstant.h"

#define DLL_NAME_LEN  60
#define DLL_PATH_LEN 180
#define FUN_NAME_LEN  60

/* 库函数描述结构/节点 */
struct _x_func {
    char   func_name[FUN_NAME_LEN+1]; /* 函数名字 */
    void * func_hndl;                 /* 函数指针 */
    struct _x_func * next;           /* 链表指针 */
};
typedef struct _x_func XFunc;

/* 动态库描述结构/节点 */
struct _x_dllib {
    char   dll_name[DLL_NAME_LEN+1]; /* 动态库名称 */
    void * dll_hndl;                 /* 库访问句柄 */
    struct _x_func * dll_func;       /* 库函数链表 */
    struct _x_dllib * next;          /* 库链表指针 */
};
typedef struct _x_dllib XDLLib;

/* 动态库登记表 */
struct _x_dll_reg {
	pthread_mutex_t	upd_lock;
	struct _x_dllib	* head_node;
};
typedef struct _x_dll_reg XDllReg;

/* 初始化动态库登记表 */
#define	DLL_REGIST_INITIALIZER	\
{\
	PTHREAD_MUTEX_INITIALIZER,	\
	NULL						\
}

#ifdef _HIDLL_LIB_
   #define EXTERN
#else
   #define EXTERN extern
#endif
EXTERN int      dllInit(XDllReg *);
EXTERN XDLLib * dllOpenLib(XDllReg *, char *, int (*)(void *));
EXTERN void * 	dllLoadFunc(XDllReg *, char *, char *, int (*)(void *));
EXTERN void *   dllFindFunc(XDLLib *, char *);
EXTERN XDLLib * dllFindLib(XDllReg *, char *);
EXTERN void *   dllGetFuncHandle(XDllReg *, char *, char *);
EXTERN int      dllCloseLib(XDllReg *);
EXTERN void     dllDestroy(XDllReg *);
EXTERN void     dllMove(XDllReg *, XDllReg *);
#undef EXTERN

#endif /* _HIDLL_H_ */
