/******************************************************************************

				Copyright (C),1998-2006,Hisuntech Co.,Ltd.
 
 File name		: histack.h 
 Author			: kixiong
 Version		: V1.0 
 Date			: 2006.11.14 
 Description	: ջ
 Others			: 
 History		: 

  No.	Date		Author		Modification
  ===	==========	========	========================================
  001   2006.11.14      kixiong         Created
********************************************************************************/
#ifndef _HISTACK_H_
#define _HISTACK_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct _histack
{
    void **data;        /** current number of elements */
    int size;           /** total capacity */
    int capacity;
    int is_empty;
}HiStack;

#ifdef _HISTACK_LIB
#define EXTERN 
#else
#define EXTERN extern
#endif

EXTERN HiStack * histackCreate(void);
EXTERN void      histackFree(void * stack);
EXTERN void *    histackPop(HiStack * stack);
EXTERN int       histackPush(HiStack * stack, void * data);
EXTERN int       histackSize(HiStack * stack);
EXTERN void *    histackGet(HiStack * stack);
EXTERN void *    histackGetAt(HiStack * stack, int index);

#endif
