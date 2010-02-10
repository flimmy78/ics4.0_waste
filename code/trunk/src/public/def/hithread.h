#ifndef	_HITHREAD_H_
#define	_HITHREAD_H_

#include <pthread.h>

#ifdef	_HP_SYSTEM_
#ifndef	PTHREAD_CREATE_UNDETACHED
#define	PTHREAD_CREATE_UNDETACHED	PTHREAD_CREATE_JOINABLE
#endif
#endif

#ifdef	_HITHD_LIB_
#define	EXTERN
#else
#define	EXTERN extern
#endif

EXTERN int thdInitAttr(pthread_attr_t *);
EXTERN int thdDestroyAttr(pthread_attr_t *);
EXTERN int thdSetDetachState(pthread_attr_t *, int);
EXTERN int thdSetScope(pthread_attr_t *, int);
EXTERN int thdInitAttr(pthread_attr_t *);
EXTERN int thdCreate(pthread_t *, const pthread_attr_t *, void * (*)(void *), void *);
EXTERN void thdExit(void *);
EXTERN void thdTestCancel();
EXTERN int thdJoin(pthread_t, void **);
EXTERN int thdCancel(pthread_t);
EXTERN int thdInitMutex(pthread_mutex_t *);
EXTERN int thdLockMutex(pthread_mutex_t *);
EXTERN int thdUnlockMutex(pthread_mutex_t *);
EXTERN int thdDestroyMutex(pthread_mutex_t *);
EXTERN int thdInitCond(pthread_cond_t *);
EXTERN int thdWaitOnCond(pthread_cond_t *, pthread_mutex_t *, long);
EXTERN int thdSignalCond(pthread_cond_t *);
EXTERN int thdBroadcastCond(pthread_cond_t *);
EXTERN int thdDestroyCond(pthread_cond_t *);
EXTERN int thdSetCancelType(int, int *);
EXTERN int thdSetCancelState(int, int *);

#ifdef	_AIX_SYSTEM_
EXTERN void thdCleanupPush(void (*)(void *), void *);
EXTERN void thdCleanupPop(int);
#endif

#ifdef	_HP_SYSTEM_
#define	thdCleanupPush(a,b)	pthread_cleanup_push(a,b)
#define	thdCleanupPos(a)	pthread_cleanup_pop(a)
#endif

#undef	EXTERN

#endif /* _HITHREAD_H_ */
