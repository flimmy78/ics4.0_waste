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

/* �⺯�������ṹ/�ڵ� */
struct _x_func {
    char   func_name[FUN_NAME_LEN+1]; /* �������� */
    void * func_hndl;                 /* ����ָ�� */
    struct _x_func * next;           /* ����ָ�� */
};
typedef struct _x_func XFunc;

/* ��̬�������ṹ/�ڵ� */
struct _x_dllib {
    char   dll_name[DLL_NAME_LEN+1]; /* ��̬������ */
    void * dll_hndl;                 /* ����ʾ�� */
    struct _x_func * dll_func;       /* �⺯������ */
    struct _x_dllib * next;          /* ������ָ�� */
};
typedef struct _x_dllib XDLLib;

/* ��̬��ǼǱ� */
struct _x_dll_reg {
	pthread_mutex_t	upd_lock;
	struct _x_dllib	* head_node;
};
typedef struct _x_dll_reg XDllReg;

/* ��ʼ����̬��ǼǱ� */
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
