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
 *                          ���̼��ڴ������Ӧ�ýӿ�                          *
------------------------------------------------------------------------------*/
/*���������ڴ������*/
EXTERN int pmm_create(unsigned int block_size, \
			   unsigned short pool_init_size, \
			   unsigned short pool_max_size, \
			   unsigned short pool_add_step, \
			   unsigned short page_size, \
   		       unsigned short max_blocks, \
			   unsigned int timeout);

/*���ٽ����ڴ������*/
EXTERN void    pmm_destroy(void);

/*��ȡ��ǰ�����ڴ��������ʹ��״̬
  ��Ϣ��¼��logĿ¼��PMM_PID.state�ļ���, PIDΪ��ǰ���̵Ľ��̺�
*/
EXTERN void pmm_print_state(char * logname);

/*�����̹߳����ڴ�*/
EXTERN void * tsm_malloc(unsigned int size);

/*�ͷ��̹߳����ڴ�*/
EXTERN void   tsm_free(void * addr);

/*------------------------------------------------------------------------------
 *                          �̼߳��ڴ������Ӧ�ýӿ�                          *
------------------------------------------------------------------------------*/
/*���̼߳��ڴ�������������ڴ�*/
EXTERN void * tmm_malloc(unsigned int size);

/*�����ڴ�ߴ�*/
void * tmm_realloc(void *old_addr, unsigned int new_size);

/*���̼߳��ڴ�������������ڴ沢��ʼ��*/
EXTERN void * tmm_calloc(unsigned int count, unsigned int eltsize);

/*�ú������Կ��ַ��������ַ���s������һ���·�����ַ�����*/
EXTERN char * tmm_strdup(const char *s);

/*�ͷŴ��ڴ�����������뵽���ڴ�*/
EXTERN void   tmm_free( void * addr );

/*�ͷŵ�ǰ�̵߳��̼߳��ڴ�������е�����ʹ��tmm_malloc������ڴ�*/
EXTERN int   tmm_free_all(void);

#undef EXTERN
	
typedef struct _process_mem_manager ProcessMemoryManager;
/*
 * ��̬���а������ļ����붨���_MMG_STATIC_LIB_
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
