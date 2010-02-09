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

/*��ȡ����*/
EXTERN char * usfGetPubPara(char *name);

/* ��ȡ·������
 * ����Ϊ��NULLʱ����Ҫ�������ͷŷ��ص��ڴ�ռ�
 */
EXTERN char * usfGetPathPara(char *name);

/*
 * ���ò���
 */
EXTERN int usfSetPubPara(char *name, char *value);

/*
 * װ�ز���
 * Added by liangwj at 2008-11-04
 */
EXTERN int usfLoadPubPara(char *para_file);

/*
 * ȡ�ļ��ľ���·��
 * flagȡֵ˵����
   	1����ƽ̨����Ŀ¼��WORKDIR����ȡ
   	2����Ӧ�û���Ŀ¼��APP_DIR����ȡ
   	3���ȴ�Ӧ�û���Ŀ¼��APP_DIR����ȡ���粻��������ƽ̨����Ŀ¼��WORKDIR��ȡ
 */
EXTERN int usfGetFullPath(int flag, char *filename, char *fullpath);

/*
 * ��ȡ���ؽڵ�ID
 */
EXTERN char * usfGetLocalID();

/*
 * ��ȡָ���ڵ��IP
 */
EXTERN long usfGetNodeIP(char *id, char *ip);

/*
 * ��ȡ���ؽڵ�IP
 */
EXTERN long usfGetLocalIP(char *ip);

#undef EXTERN
#endif
