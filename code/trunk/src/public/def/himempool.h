#ifndef _HIMEMPOOL_H_
#define _HIMEMPOOL_H_
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef MIN
#define MIN(x, y) ((x > y) ? y : x)
#endif

struct _memory_pool {
	short cursize;
	short maxsize;
	short unitsize;
	short expandflag;
	short expandscale;
	void (*initfun)(void *);
	void ** addr;
	short available;
	short fidle;
	short lidle;
	short * idles;
	short * allocedpos;
	pthread_mutex_t memlock;
};
typedef struct _memory_pool MemoryPool;

#ifdef _HIMEMPOOL_LIB_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

EXTERN void mplFree(MemoryPool *, short);
EXTERN void mplDestroy(MemoryPool *);
EXTERN MemoryPool * mplCreate(short, short, short, short, short, void (*)(void *));
EXTERN short mplMalloc(MemoryPool *);
#undef	EXTERN

#endif /* _HIMEMPOOL_H_ */
