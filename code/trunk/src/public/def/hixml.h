

#ifndef _HIXML_H
#define _HIXML_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
/*
#ifndef _HI_VARARGS
#include <varargs.h>
#else
#include <stdarg.h>
#endif
*/

#include <expat.h>

/*added by kixiong*/
#include <errno.h>

#define MALLOC  malloc
#define CALLOC  calloc
#define REALLOC realloc
#define FREE    free
#define STRDUP  strdup

enum ReplaceFlag {
	XML_NODE_NO_REPLACE = 0,
	XML_NODE_REPLACE,
	XML_NODE_APPEND
};

enum HiXmlError {
   HX_ERR_NONE,
   HX_ERR_NO_MEM,
   HX_ERR_NO_NODE,
   HX_ERR_INVALID_PARAM,
   HX_ERR_INVALID_NODE_TYPE,
   HX_ERR_INCONSISTENT,
   HX_ERR_CREATE_FILE,
   HX_ERR_OPEN_FILE,
   HX_ERR_UNSORT,
   HX_ERR_PARSE,
   HX_ERR_OPEN_MODE,   /* add by tunjia 2001-02-02 */
   HX_ERR_APPEND_FILE, /* add by tunjia 2001-02-02 */
   HX_ERR_NO_VALUE,    /* add by tunjia 2001-03-06 */
   HX_ERR_MAX_NUM

};

#define xmlGetParserErrStr(p) XML_ErrorString(XML_GetErrorCode(p->parser))
#define xmlGetParserErrLine(p) XML_GetCurrentLineNumber(p->parser)
#define xmlGetParserErrCol(p) XML_GetCurrentColumnNumber(p->parser)

#define DEFAULT_PROLOG "<?xml version='1.0' encoding='ISO-8859-1'?>"
#define DEFAULT_PROLOG_LEN strlen(DEFAULT_PROLOG)

#define TEXT_NODE_NAME                "#text"
#define COMMENT_NODE_NAME             "#comment"
#define CDATA_SECTION_NODE_NAME       "#cdata-section"
#define DOCUMENT_NODE_NAME            "#document"
#define DOCUMENT_FRAGMENT_NODE_NAME   "#document-fragment"

enum NodeType {
   MIN_NODE_TYPE = 0,
   ELEMENT_NODE,
   ATTRIBUTE_NODE,
   TEXT_NODE,
   CDATA_SECTION_NODE,
   ENTITY_REFERENCE_NODE,
   ENTITY_NODE,
   PROCESSING_INSTRUCTION_NODE,
   COMMENT_NODE,
   DOCUMENT_NODE,
   DOCUMENT_TYPE_NODE,
   DOCUMENT_FRAGMENT_NODE,
   NOTATION_NODE,
   MAX_NODE_TYPE
};

#ifdef _HIXML_NODE
   static char *def_node_name[] = {
      NULL,
      NULL,
      NULL,
      TEXT_NODE_NAME,
      CDATA_SECTION_NODE_NAME,
      NULL,
      NULL,
      NULL,
      COMMENT_NODE_NAME,
      DOCUMENT_NODE_NAME,
      NULL,
      DOCUMENT_FRAGMENT_NODE_NAME,
      NULL,
      ""
   };
#endif

struct _xml_node_list;
typedef struct _xml_node ElemAttr;

typedef struct _xml_node {
   int    type;                          /* 类型 */  
   char * name;                          /* 名字 */ 
   char * value;                         /* 值 */
   ElemAttr * attrs;                     /* 属性 */

   struct _xml_node * parent;            /* 父节点 */
   struct _xml_node * first_child;       /* 长子节点 */
   struct _xml_node * last_child;        /* 幼子节点 */
   struct _xml_node * prev_sibling;      /* 上一兄弟节点 */
   struct _xml_node * next_sibling;      /* 下一兄弟节点 */
   struct _xml_nodelist * child_list;    /* 子节点列表 */  
} XmlNode;

typedef struct _xml_document {
   XmlNode element;                      /* 元素节点 */
   int doctype;                          /* 文件类型 */
} XmlDocument;

enum OrderMethod {
  NO_ORDER,
  ASCEND_ORDER,
  DESCEND_ORDER,
  ORDER_METHOD_NUM
};

typedef struct _xml_nodelist {
   int num;                              /* 个数 */
   XmlNode ** item;                      /* 节点指针数组 */
   int size;                             /* item大小 >= num */
   int order;                            /* 排序方法 */
} XmlNodeList;

typedef struct _xml_parser {
   XML_Parser parser;
   XmlDocument * doc_node;               /* 文件节点 */
   XmlNode * curnt_node;                 /* 当前节点 */
   int done;                             /* 完成标志 */
   int if_prolog;                        /* 是否含前言 */
   int if_space;                         /* 是否处理空白 */
} XmlParser;

typedef struct _xml_block {
   int size;                            /* 缓冲区大小 */
   char * s;                            /* 缓冲区指针 */
   int len;                             /* 当前长度 */
   struct _xml_block * next;            /* 下一个块 */
} XmlBlock;

typedef struct _xml_builder {
   XmlDocument * doc_node;              /* 文件节点 */
   XmlNode * curnt_node;                /* 当前节点 */
   XmlBlock * first_block;              /* 第一个存储块 */
   XmlBlock * curnt_block;              /* 当前存储块, 也是最后一个 */
   int curnt_len;                       /* 当前长度 */
   int block_size;                      /* 块大小 */
   int if_file;                         /* 是否文件 */
} XmlBuilder;

enum NodeDataType {
   NDT_INT,
   NDT_LONG,
   NDT_FLOAT,
   NDT_DOUBLE,
   NDT_CHAR,        /* 字符 */
   NDT_CHAR_ARRAY,  /* 字符数组 */
   NDT_STRING,      /* 字符串指针 */
   NDT_OTHER
};

typedef struct _xml_node_desc {
   char * name;                         /* 名字 */
   int data_type;                       /* 数据类型 */
   int len;                             /* 长度 : FLOAT和DOUBLE(精度) */
                                        /*        CHAR_ARRAY(长度)    */
   int offset;                          /* 偏移量 */
} XmlNodeDesc;

/* add by tunjia 2001-02-02 */
enum SaveMode
{
    WRITE,
    APPEND
};
/* end add */

/* add by liangwj 2003-04-15 */
typedef	struct _quick_search_node {
	char	* id;
	XmlNode	* node;
}QuickSearchNode;

typedef struct _quick_search_list {
	int				num;
	QuickSearchNode	** item;
}QuickSearchList;
/* end add */

#define _XML_NODE_SIZE       sizeof(XmlNode)
#define _XML_DOCUMENT_SIZE   sizeof(XmlDocument)
#define _ELEM_ATTR_SIZE      sizeof(ElemAttr)
#define _XML_NODE_LIST_SIZE   sizeof(XmlNodeList)
#define _XML_PARSER_SIZE     sizeof(XmlParser)
#define _XML_BLOCK_SIZE      sizeof(XmlBlock)
#define _XML_BUILDER_SIZE    sizeof(XmlBuilder)
#define _XML_NODE_DESC_SIZE  sizeof(XmlNodeDesc)

#ifndef _HIXML_PUBLIC
   #define EXTERN extern
#else /* _HIXML_PUBLIC */
   #define EXTERN
#endif /* _HIXML_PUBLIC */

EXTERN char * xmlJoinString( char *, char * );
EXTERN void * xmlDebugMalloc( size_t );
EXTERN void * xmlDebugRealloc( void *, size_t );
EXTERN void xmlDebugFree( void * );
EXTERN char * xmlDebugStrdup( const char * );
EXTERN int xmlGetErrno();
EXTERN void xmlSetErrno( int );
EXTERN const char * xmlGetErrStr( int );

#undef EXTERN

#ifndef _HIXML_ATTRIBUTE
   #define EXTERN extern
#else /* _HIXML_ATTRIBUTE */
   #define EXTERN
#endif /* _HIXML_ATTRIBUTE */

/*
EXTERN ElemAttr * xmlNewElemAttr();
*/
#ifdef _LINUX_SYSTEM_
EXTERN ElemAttr * xmlNewElemAttr(char **, ...);
#else
EXTERN ElemAttr * xmlNewElemAttr();
#endif

EXTERN ElemAttr * xmlCloneElemAttr( ElemAttr * );
EXTERN void xmlFreeElemAttr( ElemAttr * );
EXTERN int xmlAppendElemAttr( ElemAttr *, char *, char * );
EXTERN int xmlRemoveElemAttr( ElemAttr *, char * );
EXTERN int xmlReplaceElemAttr( ElemAttr *, char *, char * );
EXTERN char * xmlGetElemAttrValue( ElemAttr *, char * );
#undef EXTERN

#ifndef _HIXML_NODE
   #define EXTERN extern
#else /* _HIXML_NODE */
   #define EXTERN
#endif /* _HIXML_NODE */

EXTERN XmlNode * xmlNewNode( int, char *, char *, ElemAttr * );
EXTERN XmlNode * xmlNewTextNode( char *, char *, ElemAttr * );
EXTERN void xmlFreeNode( XmlNode *, int );
/* add by tunjia 2001-04-06 */
EXTERN void xmlFreeDocument( XmlDocument* , int );
/* end add */
EXTERN XmlNodeList * xmlSortNode( XmlNode *, int );

EXTERN XmlNode * xmlAppendNode( XmlNode *, XmlNode * );
EXTERN XmlNode * xmlInsertNode( XmlNode *, XmlNode *, XmlNode * );
EXTERN XmlNode * xmlRemoveNode( XmlNode * );
EXTERN XmlNode * xmlReplaceNode( XmlNode *, XmlNode * );

EXTERN XmlNode * xmlCloneNode( XmlNode *, int );
EXTERN XmlNode * xmlGetNode( XmlNode *, XmlNode *, char * );
EXTERN XmlNode * xmlGetNodeQuick( XmlNode *, int *, char * );
extern char * xmlGetValue( XmlNode * );
/* add by tunjia 2001-02-08 */
EXTERN int xmlSetValue( XmlNode*, char* );
/* end add */
extern XmlNodeList * xmlGetAllNode( XmlNode *, char * );
EXTERN XmlNode * xmlGetRootNode( XmlNode * );

EXTERN XmlNode * xmlFormatNode( XmlNode * );

/* add by tunjia 2001-03-06 */
EXTERN XmlNode * xmlNewBinNode( char*, void*, int, ElemAttr* );
EXTERN void* xmlGetBinValue( XmlNode*, int* );
EXTERN int xmlSetBinValue( XmlNode*, void*, int );
/* end add */

/* add by tunjia 2001-03-14 */
/*EXTERN XmlNode * newElemCDataNode( char*, char*, ElemAttr* );
extern char * getElemNodeCData( XmlNode* );
EXTERN int setElemNodeCData( XmlNode*, char* );*/
/* end add */


EXTERN XmlNodeList * xmlNewNodeList( int );
EXTERN XmlNodeList * xmlAppendNodeToList( XmlNodeList *, int, XmlNode **, int );
EXTERN XmlNodeList * xmlRemoveNodeFromList( XmlNodeList *, XmlNode * );
EXTERN XmlNodeList * xmlChangeNodeListOrder( XmlNodeList *, int );
EXTERN void xmlFreeNodeList( XmlNodeList * );

/* add by liang_wj 2003-03-24 */
EXTERN char	* xmlGetAttrValue( XmlNode *, char * );
EXTERN int xmlAddAttrValue(XmlNode *, char *, char *);
EXTERN XmlNode * xmlGetChildNode( XmlNode *, XmlNode *, char * );
EXTERN XmlNode * xmlGetNodeByValue( XmlNode *, XmlNode *, char *, char * );
EXTERN XmlNode * xmlGetChildNodeByValue( XmlNode *, XmlNode *, char *, char * );
EXTERN XmlNode * xmlGetNodeByAttr( XmlNode *, XmlNode *, char *, char *, char * );
EXTERN XmlNode * xmlGetChildNodeByAttr( XmlNode *, XmlNode *, char *, char *, char * );
EXTERN char	* xmlGetChildValue( XmlNode *, char * );
EXTERN int xmlSetChildValue( XmlNode *, char *, char * );
EXTERN int xmlDelChildValue( XmlNode *, char * );
EXTERN int xmlDelNode( XmlNode * );
EXTERN XmlNode * xmlStringToTree( char *, int );
EXTERN XmlNode * xmlStringToTreeNS( char *, int );
EXTERN char	* xmlTreeToString( XmlNode * , int * );
EXTERN void	xmlFreeTree( XmlNode * );
EXTERN void	xmlFreeString( char * );
EXTERN XmlNode * xmlAddNode(XmlNode * , char *, int);
EXTERN XmlNode * xmlAddTextNode(XmlNode * , char *, char *, int);
EXTERN int xmlCombine(XmlNode *, XmlNode *, int);
EXTERN int xmlCombineReplace(XmlNode *, XmlNode *);
EXTERN int xmlCombineNoReplace(XmlNode *, XmlNode *);

/* add by yu_qj 2003-4-22 */
EXTERN char * xmlReadField(XmlNode *, char *);
/* add by yu_qj 2003-5-29 */
EXTERN XmlNode * xmlGetPrevNode(XmlNode *, char *);
EXTERN XmlNode * xmlGetNextNode(XmlNode *, char *);
EXTERN int xmlNodeRename(XmlNode *, char *);

#undef EXTERN

#ifndef _HIXML_PARSE
   #define EXTERN extern
#else /* _HIXML_PARSE */
   #define EXTERN
#endif /* _HIXML_PARSE */

extern XmlParser * xmlCreateParser( int, int );
extern XmlParser * xmlCreateParserNS( int, int );
extern int xmlParse( XmlParser * , char *, int, int );
extern void xmlFreeParser( XmlParser *, int );
extern XmlDocument * xmlLoadFile( char *, int );
extern XmlDocument * xmlLoadFileNS( char *, int );
#undef EXTERN

#ifndef _HIXML_BUILD
   #define EXTERN extern
#else /* _HIXML_BUILD */
   #define EXTERN
#endif /* _HIXML_BUILD */

extern XmlBuilder * xmlCreateBuilder( XmlDocument *, int, int );
extern int xmlBuild( XmlBuilder * , char **, int *, int * );
extern void xmlFreeBuilder( XmlBuilder * );
/* modify by tunjia 2001-02-02 */
extern int xmlSaveFile( XmlDocument *, char *, int );
/* end modify */
#undef EXTERN

#ifndef _HIXML_QSEARCH
   #define EXTERN extern
#else
   #define EXTERN
#endif
EXTERN QuickSearchList * xmlNewQuickSearchList(XmlNode *, char *, char *);
EXTERN XmlNode * xmlQuickSearch(QuickSearchList *, char *);
EXTERN void xmlFreeQuickSearchList(QuickSearchList *);
#undef EXTERN

#ifdef __cplusplus


}
#endif

#endif /* _HIXML_H */
