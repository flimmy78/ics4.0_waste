#ifndef _HI_MMG_H_
#define _HI_MMG_H_
#include <stdio.h>
#include <pthread.h>

#ifdef _LIB_HIMMG_
#define EXTERN
#else
#define EXTERN extern
#endif

/*------------------------------------------------------------------------------
 *                          进程级内存管理器应用接口                          *
------------------------------------------------------------------------------*/
/*创建进程内存管理器*/
EXTERN int pmm_create(unsigned int block_size, \
			   unsigned short pool_init_size, \
			   unsigned short pool_max_size, \
			   unsigned short pool_add_step, \
			   unsigned short page_size, \
   		       unsigned short max_blocks, \
			   unsigned int timeout);

/*销毁进程内存管理器*/
EXTERN void    pmm_destroy(void);

/*获取当前进程内存管理器的使用状态
  信息记录到log目录的PMM_PID.state文件中, PID为当前进程的进程号
*/
EXTERN void pmm_print_state(char * logname);

/*申请线程共享内存*/
EXTERN void * tsm_malloc(unsigned int size);

/*释放线程共享内存*/
EXTERN void   tsm_free(void * addr);

/*------------------------------------------------------------------------------
 *                          线程级内存管理器应用接口                          *
------------------------------------------------------------------------------*/
/*从线程级内存管理器中申请内存*/
EXTERN void * tmm_malloc(unsigned int size);

/*更改内存尺寸*/
void * tmm_realloc(void *old_addr, unsigned int new_size);

/*从线程级内存管理器中申请内存并初始化*/
EXTERN void * tmm_calloc(unsigned int count, unsigned int eltsize);

/*该函数将以空字符结束的字符串s拷贝到一个新分配的字符串中*/
EXTERN char * tmm_strdup(const char *s);

/*释放从内存管理器中申请到的内存*/
EXTERN void   tmm_free( void * addr );

/*释放当前线程的线程级内存管理器中的所有使用tmm_malloc申请的内存*/
EXTERN int   tmm_free_all(void);

#undef EXTERN
	
typedef struct _process_mem_manager ProcessMemoryManager;
/*
 * 静态库中包含此文件必须定义宏_MMG_STATIC_LIB_
 */
#if !defined(SERVER_EXTERN) && !defined(_MMG_EXTERN_) && !defined(_MMG_STATIC_LIB_)
#define _MMG_EXTERN_
ProcessMemoryManager	* _gProcessMemMng = NULL;
pthread_key_t  			* _gThreadMngKey = NULL;
#else
extern ProcessMemoryManager	   	* _gProcessMemMng;
extern pthread_key_t  			* _gThreadMngKey;
#endif
#endif /*_HI_MMG_H_*/
