/******************************************************************************

                Copyright (C),1998-2004,Hisuntech Co.,Ltd.

 File name      : hidsm.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2004-01-01
 Description    : ����Դ����ͷ�ļ�
 Others         : ��
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2004-01-01  LiangWJ     ���

******************************************************************************/
#ifndef	_H_HIDSM_
#define	_H_HIDSM_

#define	DSM_INIT_SIZE		1024		/* ����Դ��ʼ����С */
#define	DSM_NAMED_DS		9998		/* ������������ */
#define	DSM_NON_NAMED_DS	9999		/* �������������� */

#define	DSM_RDONLY			1			/* ֻ��Ȩ�� */
#define	DSM_RWONLY			2			/* ��дȨ�� */


/* �������ݵĽڵ� */
typedef struct _named_data_node {
	int		type;						/* ��д���� */
	char	* name;						/* �������� */
	char	* data;						/* ������ֵ */
	int		len;						/* ���ݳ��� */
	struct _named_data_node * next;		/* ��һ���ڵ� */
}NamedDataNode;
typedef	NamedDataNode	NamedPointerNode;

/* �������ݵ�����Դ�ṹ */
typedef struct _named_data_source {
	int		size;						/* ����Դ��С */
	int		count;						/* ��ǰ����Դ���� */
	NamedDataNode	* tbl;				/* ����Դָ�� */
	NamedDataNode	** ht;				/* ����� */
}NamedDataSource;
typedef	NamedDataSource	NamedPointerSource;

/* ����Դ�ڵ� */
typedef struct _data_source_node {
	int		type;						/* ����Դ���� */
	int		size;						/* ����Դ��С */
	char	* name;						/* ����Դ���� */
	void	* pointer;					/* ����Դָ�� */
	void	(*done)(void *);			/* ����Դ�ͷź���ָ�� */
	struct _data_source_node * next;	/* ��һ���ڵ� */
}DataSourceNode;

/* ����Դ�ṹ */
typedef struct _data_source {
	int		size;						/* ����Դ��С */
	int		count;						/* ��ǰ����Դ���� */
	DataSourceNode	* tbl;				/* ����Դ�� */
	DataSourceNode	** ht;				/* ����� */
}DataSource;

#ifdef	_LIB_HIDSM_
#define	EXTERN
#else
#define	EXTERN extern
#endif

/* ��������Դ */
EXTERN DataSource * dsmNewDataSource(int);
/* �������Դ */
EXTERN int dsmAddDataSource(DataSource *, char *, int, void *, int, void (*)(void *));
/* ��ӻ��滻����Դ */
EXTERN int dsmAddOrRepDataSource(DataSource *, char *, int, void *, int, void (*)(void *));
/* ȡ����Դ */
EXTERN void * dsmGetDataSource(DataSource *, char *, int *, int *);
/* �ͷ���������Դ */
EXTERN void dsmFreeDataSource(DataSource *);
/* ɾ������Դ */
EXTERN void dsmDelDataSource(DataSource *, char *);
/* ��������Դ�ڵ� */
EXTERN DataSourceNode * dsmFindDataSourceNode(DataSource *, char *);

/* ������������Դ */
EXTERN NamedDataSource * dsmNewNamedDataSource(int);
/* ����һ����������Դ */
EXTERN NamedDataSource * dsmAddNamedDataSource(DataSource *, char *);
/* ����(���滻)һ������������ */
EXTERN int dsmAddNamedData(NamedDataSource *, char *, char *, int, int);
/* ȡ����������������� */
EXTERN char * dsmGetNamedData(NamedDataSource *, char *, int *);
/* ɾ����������Դ�������� */
EXTERN void dsmDelNamedData(NamedDataSource *, char *);
/* �ͷ���������Դ */
EXTERN void dsmFreeNamedDataSource(NamedDataSource *);
/* ������������Դ */
EXTERN int dsmDumpNamedDataSource(NamedDataSource *, char **, int *);

/* ��������ָ������Դ */
EXTERN NamedPointerSource * dsmNewNamedPointerSource(int);
/* ����һ������ָ������Դ */
EXTERN NamedPointerSource * dsmAddNamedPointerSource(NamedPointerSource *, char *);
/* ����(���滻)һ������ָ�� */
EXTERN int dsmAddNamedPointer(NamedPointerSource *, char *, void *, int);
/* ȡ����ָ�� */
EXTERN void * dsmGetNamedPointer(NamedPointerSource *, char *);
/* ɾ������ָ�� */
EXTERN void dsmDelNamedPointer(NamedPointerSource *, char *);
/* �ͷ���������Դ */
EXTERN void dsmFreeNamedPointerSource(NamedPointerSource *);

/*
 * �����ĸ�API Added by liangwj at 2006-01-11
 */
/* �Ƴ�����Դ�ڵ� */
EXTERN DataSourceNode * dsmRemoveDataSource(DataSource *, char *);
/* �ͷ�һ������Դ�ڵ� */
EXTERN void dsmFreeDataSourceNode(DataSourceNode *);

/* �Ƴ���������Դ�ڵ� */
EXTERN NamedDataNode * dsmRemoveNamedDataNode(NamedDataSource *, char *);
/* �ͷ�һ����������Դ�ڵ� */
EXTERN void dsmFreeNamedDataNode(NamedDataNode *);

/* �Ƴ�����ָ��ڵ� */
EXTERN NamedPointerNode * dsmRemoveNamedPointerNode(NamedPointerSource *, char *);
/* �ͷ�һ������ָ��ڵ� */
EXTERN void dsmFreeNamedPointerNode(NamedPointerNode *);
#undef	EXTERN

#endif /* _H_HIDSM */
