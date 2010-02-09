/******************************************************************************

                Copyright (C),1998-2004,Hisuntech Co.,Ltd.

 File name      : hidsm.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2004-01-01
 Description    : 数据源管理头文件
 Others         : 无
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2004-01-01  LiangWJ     完成

******************************************************************************/
#ifndef	_H_HIDSM_
#define	_H_HIDSM_

#define	DSM_INIT_SIZE		1024		/* 数据源初始化大小 */
#define	DSM_NAMED_DS		9998		/* 有名数据类型 */
#define	DSM_NON_NAMED_DS	9999		/* 非有名数据类型 */

#define	DSM_RDONLY			1			/* 只读权限 */
#define	DSM_RWONLY			2			/* 读写权限 */


/* 有名数据的节点 */
typedef struct _named_data_node {
	int		type;						/* 读写类型 */
	char	* name;						/* 数据名称 */
	char	* data;						/* 数据数值 */
	int		len;						/* 数据长度 */
	struct _named_data_node * next;		/* 下一个节点 */
}NamedDataNode;
typedef	NamedDataNode	NamedPointerNode;

/* 有名数据的数据源结构 */
typedef struct _named_data_source {
	int		size;						/* 数据源大小 */
	int		count;						/* 当前数据源个数 */
	NamedDataNode	* tbl;				/* 数据源指针 */
	NamedDataNode	** ht;				/* 乱序表 */
}NamedDataSource;
typedef	NamedDataSource	NamedPointerSource;

/* 数据源节点 */
typedef struct _data_source_node {
	int		type;						/* 数据源类型 */
	int		size;						/* 数据源大小 */
	char	* name;						/* 数据源名称 */
	void	* pointer;					/* 数据源指针 */
	void	(*done)(void *);			/* 数据源释放函数指针 */
	struct _data_source_node * next;	/* 下一个节点 */
}DataSourceNode;

/* 数据源结构 */
typedef struct _data_source {
	int		size;						/* 数据源大小 */
	int		count;						/* 当前数据源个数 */
	DataSourceNode	* tbl;				/* 数据源表 */
	DataSourceNode	** ht;				/* 乱序表 */
}DataSource;

#ifdef	_LIB_HIDSM_
#define	EXTERN
#else
#define	EXTERN extern
#endif

/* 创建数据源 */
EXTERN DataSource * dsmNewDataSource(int);
/* 添加数据源 */
EXTERN int dsmAddDataSource(DataSource *, char *, int, void *, int, void (*)(void *));
/* 添加或替换数据源 */
EXTERN int dsmAddOrRepDataSource(DataSource *, char *, int, void *, int, void (*)(void *));
/* 取数据源 */
EXTERN void * dsmGetDataSource(DataSource *, char *, int *, int *);
/* 释放所有数据源 */
EXTERN void dsmFreeDataSource(DataSource *);
/* 删除数据源 */
EXTERN void dsmDelDataSource(DataSource *, char *);
/* 查找数据源节点 */
EXTERN DataSourceNode * dsmFindDataSourceNode(DataSource *, char *);

/* 创建有名数据源 */
EXTERN NamedDataSource * dsmNewNamedDataSource(int);
/* 增加一个有名数据源 */
EXTERN NamedDataSource * dsmAddNamedDataSource(DataSource *, char *);
/* 增加(或替换)一个有名数据项 */
EXTERN int dsmAddNamedData(NamedDataSource *, char *, char *, int, int);
/* 取有名数据项的数据项 */
EXTERN char * dsmGetNamedData(NamedDataSource *, char *, int *);
/* 删除有名数据源的数据项 */
EXTERN void dsmDelNamedData(NamedDataSource *, char *);
/* 释放有名数据源 */
EXTERN void dsmFreeNamedDataSource(NamedDataSource *);
/* 导出有名数据源 */
EXTERN int dsmDumpNamedDataSource(NamedDataSource *, char **, int *);

/* 创建有名指针数据源 */
EXTERN NamedPointerSource * dsmNewNamedPointerSource(int);
/* 增加一个有名指针数据源 */
EXTERN NamedPointerSource * dsmAddNamedPointerSource(NamedPointerSource *, char *);
/* 增加(或替换)一个有名指针 */
EXTERN int dsmAddNamedPointer(NamedPointerSource *, char *, void *, int);
/* 取有名指针 */
EXTERN void * dsmGetNamedPointer(NamedPointerSource *, char *);
/* 删除有名指针 */
EXTERN void dsmDelNamedPointer(NamedPointerSource *, char *);
/* 释放有名数据源 */
EXTERN void dsmFreeNamedPointerSource(NamedPointerSource *);

/*
 * 以下四个API Added by liangwj at 2006-01-11
 */
/* 移出数据源节点 */
EXTERN DataSourceNode * dsmRemoveDataSource(DataSource *, char *);
/* 释放一个数据源节点 */
EXTERN void dsmFreeDataSourceNode(DataSourceNode *);

/* 移出有名数据源节点 */
EXTERN NamedDataNode * dsmRemoveNamedDataNode(NamedDataSource *, char *);
/* 释放一个有名数据源节点 */
EXTERN void dsmFreeNamedDataNode(NamedDataNode *);

/* 移出有名指针节点 */
EXTERN NamedPointerNode * dsmRemoveNamedPointerNode(NamedPointerSource *, char *);
/* 释放一个有名指针节点 */
EXTERN void dsmFreeNamedPointerNode(NamedPointerNode *);
#undef	EXTERN

#endif /* _H_HIDSM */
