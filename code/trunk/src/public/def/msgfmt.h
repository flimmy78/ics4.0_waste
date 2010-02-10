#ifndef CC_MSGFMT_H_
#define CC_MSGFMT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "error.h"


#define MSG_SEP_CHR    		'.'   /* 节点名字的分隔符, 不允许名字中包含分隔符, 
								所有函数暂时不作转义处理 */
#define MSG_MAX_NAME_LEN	1024  /* 节点名称最大长度(全路径名称) */
#define STRLEN_LEN			4     /* 在流状数据格式中长度位数 */

/*	消息格式中的节点类型(实际没有利用!!) */
#define MSG_NT_ROOT		'R'		/* 根节点 */
#define MSG_NT_BRANCH	'B'		/* 树枝节点 */
#define MSG_NT_LEAF		'L'		/* 叶子节点 */

/*	消息格式中的数据类型 */
#define MSG_DT_LNG		'L'
#define MSG_DT_INT		'I'
#define MSG_DT_SHT		'H'		/* 短整型 */
#define MSG_DT_FLT		'F'		/* 浮点型 */
#define MSG_DT_DBL		'D'		/* 双精度 */
#define MSG_DT_STR		'S'		/* 字符串,调用GetValue时判断为S,自动补加0 */
#define MSG_DT_CHR		'C'
#define MSG_DT_BOL		'B'		/* 布尔型 */

typedef struct _message_node{
	char * name;          	/*节点名字，保存记录名字或者域的名字*/
	unsigned char nodeType; /*节点类型，可以是'R'或者'F'*/
	unsigned char dataType; /*域节点的数据类型，包括数字/字符串/布尔值等等*/
	char * data;           	/*数据内容，全部使用字符串表示*/
	int dataLen;           	/*域节点数据内容的长度*/
	struct _message_node *parent;
	struct _message_node *firstChild;
	struct _message_node *lastChild;
	struct _message_node *prevSibling;
	struct _message_node *nextSibling;
}MessageNode;

/*	对于某些情况需要把一些节点连接起来 */
typedef struct _msg_node_list{
	MessageNode *msgNode;
	struct _msg_node_list *next;
}MsgNodeList;

#define MSGNOD_SIZE 		sizeof(MessageNode)

/*========================以下为函数说明================================*/
/*========================树状消息处理函数==============================*/

/* 
 * 函数名称: MessageNode * MSGNewNode
 * 函数功能: 建立新的节点
 * 输入参数: 
 *			char *name		节点名称
 *			unsigned char nodeType	节点类型
 *			unsigned char dataType	数据类型
 *			char *data				数据内容
 *			char dataLen			数据长度
 * 输出参数：无
 * 返    回：生成的节点指针(失败为NULL)
 */
MessageNode * MSGNewNode(char *name, unsigned char nodeType, unsigned char dataType, char *data, int dataLen);

/* 
 * 函数名称: MessageNode * MSGAppendNode()
 * 函数功能: 将一个节点作为另外一个节点的最后一个子节点添加上去,
 *			 如果父节点为空,返回子节点,子节点为空,不作改动返回父节点
 * 输入参数: 
 *			MessageNode * msgParent	起始节点
 *			MessageNode * msgChild	起始节点
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
 */
MessageNode * MSGAppendNode(MessageNode *msgParent, MessageNode *msgChild);

/* 
 * 函数名称: MessageNode * MSGGetNode
 * 函数功能: 从指定节点开始根据名字查找一个节点, 名字可以是层次的, 如Root.Agent
 * 输入参数: 
 *			MessageNode * msgRoot	起始节点
 *			char *nodeName			节点名称
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
 */
MessageNode * MSGGetNode(MessageNode * msgRoot, char * nodeName);

/* 
 * 函数名称: MessageNode * MSGGetNodeAllOver
 * 函数功能: 从指定节点开始根据名字查找一个节点, 名字(不可以)是层次的
 * 输入参数: 
 *			MessageNode * parent	父节点
 *			MessageNode * ref_child	参考子节点
 *			char * name				节点名称
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
 */
MessageNode * MSGGetNodeAllOver(MessageNode * parent, MessageNode * ref_child, char * name);

/* 
 * 函数名称: MessageNode * MSGRemoveNode
 * 函数功能: 将子节点在树中移走
 * 输入参数: 
 *			MessageNode * old_child	子节点
 * 输出参数：
 * 返    回：
 *			NULL					失败
 *			Not NULL				节点指针
 */
MessageNode * MSGRemoveNode(MessageNode * old_child);

/* 
 * 函数名称: MessageNode * MSGGetChildNodeBynum
 * 函数功能: 查找指定节点的第n个子节点
 * 输入参数: 
 *			MessageNode * msgRoot	起始节点
 *			int  occ				序号(<=0 为最后一个)
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
 */
MessageNode * MSGGetChildNodeBynum(MessageNode * msgRoot, int occ);

/* 
 * 函数名称: MessageNode * MSGGetChildNode
 * 函数功能: 根据名字查找子节点
 * 输入参数: 
 *			MessageNode * msgRoot	起始节点
 *			char *nodeName			节点名称
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
 */
MessageNode * MSGGetChildNode(MessageNode * msgRoot, char *nodeName);

/* 
 * 函数名称: MessageNode * MSGGetChildNodeX
 * 函数功能: 在参考子节点后根据名字查找子节点
 * 输入参数: 
 *			MessageNode * msgRoot	起始节点
 *			MessageNode * refChild	参考子节点
 *			char *nodeName			节点名称
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
 */
MessageNode * MSGGetChildNodeX(MessageNode * msgRoot, MessageNode * refChild, char *nodeName);

/* 
 * 函数名称: MessageNode * MSGGetSibNode
 * 函数功能: 查找指定节点的第n个兄弟节点
 * 输入参数: 
 *			MessageNode * msgRoot	起始节点
 *			int  dir				查找方向(>=0往后,<0往前)
 *			int  occ				序号(<0 为最后一个)
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
 */
MessageNode * MSGGetSibNode(MessageNode * msgRoot, int dir, int occ);

/* 
 * 函数名称: MessageNode * MSGSearchNode 
 * 函数功能: 查找一个基准点下满足条件的下一个节点(不比较起始节点)
 * 输入参数: 
 *			MessageNode *msgRoot	查询的基节点
 *			char *nodeName			查询节点名称
 *			MessageNode *msgStart	查询的起始节点(为空相当msgRoot)
 *			int  deep				搜索深度(<=0遍历所有子节点,>0搜索deep层)
 *			int  occ				查询第几个(<0最后一个)
 * 输出参数：
 * 返    回：
 */
MessageNode * MSGSearchNode(MessageNode * msgRoot, char * nodeName, MessageNode *msgStart, int deep, int occ);

/* 
 * 函数名称: MessageNode * MSGSearchNode2 
 * 函数功能: 查找一个基准点下满足条件的下一个节点(不比较起始节点)
 * 输入参数: 
 *			MessageNode *msgRoot	查询的基节点
 *			char *nodeName			查询节点名称(可以有层次关系,与前一差别)
 *			MessageNode *msgStart	查询的起始节点(为空相当msgRoot)
 *			int  deep				搜索深度(<=0遍历所有子节点,>0搜索deep层)
 *			int  occ				查询第几个(<0最后一个)
 * 输出参数：
 * 返    回：
 */
MessageNode * MSGSearchNode2(MessageNode * msgRoot, char * nodeName, MessageNode *msgStart, int deep, int occ);

/* 
 * 函数名称: int MSGFreeNode
 * 函数功能: 释放一个节点的内存空间,没有任何指针处理
 * 输入参数: 
 *			MessageNode *msgNode	节点
 * 输出参数：无
 * 返    回：
 *			0		成功
 *			-1		失败
 */
int  MSGFreeNode(MessageNode *msgNode);

/* 
 * 函数名称: int MSGAddNode
 * 函数功能: 将指定长度消息增加在指定节点为父节点下面
 * 输入参数: 
 *			MessageNode *msgRoot	根节点
 *			char *parent			父节点名称(如果为空则在当前节点下)
 *			char *name				节点名称
 *			unsigned char nodeType	节点类型
 *			unsigned char dataType	数据类型
 *			char *data				数据内容
 *			char dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			MSG_DATA_LEN_ERR		长度错误
 *			MSG_NEW_ERR				建立新节点出错
 *			MSG_NODE_EXIST			节点已经存在
 *			MSG_NODE_APPEND_ERR		连接节点出错
 */
int  MSGAddNode(MessageNode *msgRoot, char *parent, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * 函数名称: int MSGAddOrRepNode
 * 函数功能: 将指定长度消息增加在指定节点为父节点下面,如果节点存在,则重新赋值
 * 输入参数: 
 *			MessageNode *msgRoot	根节点
 *			char *parent			父节点名称
 *			char *name				节点名称
 *			unsigned char nodeType	节点类型
 *			unsigned char dataType	数据类型
 *			char *data				数据内容
 *			char dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			MSG_DATA_LEN_ERR		长度错误
 *			MSG_NEW_ERR				建立新节点出错
 *			MSG_NODE_EXIST			节点已经存在
 *			MSG_NODE_APPEND_ERR		连接节点出错
 */
int  MSGAddOrRepNode(MessageNode *msgRoot, char *parent, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * 函数名称: int MSGAppValue
 * 函数功能: 将数据追加到指定节点数据后面
 * 输入参数: 
 *			MessageNode *msgRoot	根节点
 *			char *parent			父节点名称
 *			char *name				节点名称
 *			unsigned char nodeType	节点类型
 *			unsigned char dataType	数据类型
 *			char *data				数据内容
 *			char dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			MSG_DATA_LEN_ERR		长度错误
 *			MSG_NEW_ERR				建立新节点出错
 *			MSG_NODE_EXIST			节点已经存在
 *			MSG_NODE_APPEND_ERR		连接节点出错
 */
int  MSGAppValue(MessageNode *msgRoot, char *parent, char *nodeName, char * data, int dataLen, int mode);

/* 
 * 函数名称: int MSGAddChildNode
 * 函数功能: 将指定长度消息增加在指定节点为父节点下面
 * 输入参数: 
 *			MessageNode *msgRoot	根节点
 *			char *parent			父节点名称(如果为空则在当前节点下)
 *			char *name				节点名称
 *			unsigned char nodeType	节点类型
 *			unsigned char dataType	数据类型
 *			char *data				数据内容
 *			char dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			MSG_DATA_LEN_ERR		长度错误
 *			MSG_NEW_ERR				建立新节点出错
 *			MSG_NODE_EXIST			节点已经存在
 *			MSG_NODE_APPEND_ERR		连接节点出错
 */
int  MSGAddChildNode(MessageNode *msgRoot, char *parent, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * 函数名称: int MSGAddOrRepChildNode
 * 函数功能: 将指定长度消息增加在指定节点为父节点下面,如果节点存在,则重新赋值
 * 输入参数: 
 *			MessageNode *msgRoot	根节点
 *			char *parent			父节点名称
 *			char *name				节点名称
 *			unsigned char nodeType	节点类型
 *			unsigned char dataType	数据类型
 *			char *data				数据内容
 *			char dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			MSG_DATA_LEN_ERR		长度错误
 *			MSG_NEW_ERR				建立新节点出错
 *			MSG_NODE_EXIST			节点已经存在
 *			MSG_NODE_APPEND_ERR		连接节点出错
 */
int  MSGAddOrRepChildNode(MessageNode *msgRoot, char *parent, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * 函数名称: int MSGSetValue
 * 函数功能: 修改一个节点的数据
 * 输入参数: 
 *			MessageNode *msgRoot	根节点指针
 *			char *nodeName			节点名称(如果为空则根节点)
 *			unsigned char nodeType	节点类型
 *			unsigned char dataType	数据类型
 *			char *data				数据内容
 *			char dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			MSG_DATA_LEN_ERR		长度错误
 *			MSG_MALLOC_ERR			分配节点空间错
 *			MSG_NODE_NOT_FOUND		节点不存在
 */
int  MSGSetValue(MessageNode *msgRoot, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * 函数名称: int MSGSetChildValue
 * 函数功能: 修改一个节点的数据
 * 输入参数: 
 *			MessageNode *msgRoot	根节点指针
 *			char *nodeName			节点名称(如果为空则根节点)
 *			unsigned char nodeType	节点类型
 *			unsigned char dataType	数据类型
 *			char *data				数据内容
 *			char dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			MSG_DATA_LEN_ERR		长度错误
 *			MSG_MALLOC_ERR			分配节点空间错
 *			MSG_NODE_NOT_FOUND		节点不存在
 */
int  MSGSetChildValue(MessageNode *msgRoot, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * 函数名称: int  MSGChgNodeValue()
 * 函数功能: 修改节点数据
 * 输入参数: 
 *			MessageNode *node	    节点
 *			char *data	     		新数据
 *			int dataLen			    新数据长度
 * 输出参数：
 * 返    回：
 *			0 					成功
 *			-1          		失败
 */
int MSGChgNodeValue(MessageNode *node, char *data, int dataLen);

/* 
 * 函数名称: int MSGGetValue
 * 函数功能: 取得一个节点的数据
 * 输入参数: 
 *			MessageNode *msgRoot	消息的根节点
 *			char *nodeName          节点名称
 *			char maxlen				数据最大长度
 * 输出参数：
 *			unsigned char *nodeType	节点类型
 *			unsigned char *dataType	数据类型
 *			char *data				数据内容
 * 返    回：
 *			>=0						成功,数据长度
 *			PUB_STR2SHORT			长度不足
 *			MSG_NODE_NOT_FOUND		节点不存在
 */
int  MSGGetValue(MessageNode *msgRoot, char *nodeName, unsigned char *nodeType, unsigned char *dataType, char * data, int maxlen);

/* 
 * 函数名称: int MSGGetChildValue
 * 函数功能: 取得一个子节点的数据(不需要输入当前节点的名字)
 * 输入参数: 
 *			MessageNode *msgRoot	消息的根节点
 *			char *nodeName          节点名称
 *			char maxlen				数据最大长度
 * 输出参数：
 *			unsigned char *nodeType	节点类型
 *			unsigned char *dataType	数据类型
 *			char *data				数据内容
 * 返    回：
 *			>=0						成功,数据长度
 *			PUB_STR2SHORT			长度不足
 *			PUB_STR2LONG			名字太长
 *			MSG_NODE_NOT_FOUND		节点不存在
 */
int  MSGGetChildValue(MessageNode *msgRoot, char *nodeName, unsigned char *nodeType, unsigned char *dataType, char * data, int maxlen);

/* 
 * 函数名称: int MSGDelAllNode
 * 函数功能: 删除一个节点的所有子节点以及后续子节点,并释放自身节点
 * 输入参数: 
 *			MessageNode *msgNode	节点
 * 输出参数：无
 * 返    回：
 *			0						成功
 * 备    注：最好调用MSGDelNode
 */
int  MSGDelAllNode(MessageNode *msgNode);

/* 
 * 函数名称: int MSGDelNode
 * 函数功能: 删除一个节点及其下的所有子节点,并修改父节点、上下兄弟节点指针
 * 输入参数: 
 *			MessageNode *msgNode	节点
 *			char *nodeName          子节点名称(NULL则删除整个消息)
 * 输出参数：无
 * 返    回：
 *			0						成功
 */
int  MSGDelNode(MessageNode *msgRoot, char *nodeName);

/* 
 * 函数名称: int MSGDetach
 * 函数功能: 断开一个子节点和消息树的连接,但不释放空间(使用时需要谨慎,
 *			 避免指针遗失而不能释放内存空间)
 * 输入参数: 
 *			MessageNode *msgNode	释放节点
 * 输出参数：无
 * 返    回：
 *			Not NULL			断开的子节点指针, 成功
 *			NULL				失败(没有找到等)
 */
MessageNode * MSGDetach(MessageNode *msgNode);

/* 
 * 函数名称: int MSGDetachChildNode
 * 函数功能: 断开一个子节点和消息树的连接,但不释放空间(使用时需要谨慎,
 *			 避免指针遗失而不能释放内存空间)
 * 输入参数: 
 *			MessageNode *msgRoot	消息根节点
 *			char *nodeName			节点名称
 *			int occ					找到的序号(同Search) 
 *			int deep				搜索深度(同Search) 
 * 输出参数：无
 * 返    回：
 *			Not NULL			断开的子节点指针, 成功
 *			NULL				失败(没有找到等)
 */
MessageNode * MSGDetachChildNode(MessageNode *msgRoot, char *nodeName, int occ, int deep);

/* 
 * 函数名称: MessageNode *MSGClone
 * 函数功能: 复制消息(包括子节点)
 * 输入参数: 
 *			MessageNode *msgRootSrc	根节点
 *			char *name				复制的节点名称(NULL则从根节点开始)
 * 输出参数：无
 * 返    回：
 *			Not NULL				复制的消息指针
 *			NULL					失败
 */
MessageNode * MSGClone(MessageNode *msgRootSrc, char *nodeName);

/* 
 * 函数名称: MessageNode *MSGCloneNode
 * 函数功能: 复制第二个消息的一个节点到第一个节点下
 * 输入参数: 
 *			MessageNode **msgFst	第一个消息的节点
 *			MessageNode *msgSnd		第二个消息的节点
 *			char *name				复制节点名称(NULL为根节点,否则为当前子节点)
 *			int  opflag				操作标志
 *				MSG_ADD		只增加,如果已经存在报错
 *				MSG_REP		1有则先删除
 * 输出参数：无
 * 返    回：
 *			0					成功
 *			MSG_NODE_NOT_FOUND	复制节点没有找到
 *			MSG_NODE_EXIST		节点已经存在
 *			MSG_NEW_ERR			建新节点出错
 *			MSG_NODE_APPEND_ERR	连接节点出错
 */
int MSGCloneNode(MessageNode **msgFst, MessageNode *msgSnd, char *nodeName, int opflag);

/* 
 * 函数名称: MessageNode * MSGJoin()
 * 函数功能: 合并两个消息,父节点名称等由参数给出
 * 输入参数: 
 *			MessageNode * msgRootFirst	第一个节点
 *			MessageNode * msgRootSecond	第二个节点
 *			char *nodeName              总结点名称
 *			unsigned char nodeType		总节点类型
 *			unsigned char dataType		总节点数据类型
 *			char *data				数据内容
 *			char dataLen			数据长度
 * 输出参数：
 * 返    回：
 *			Not NULL				节点指针
 *			NULL					失败
 */
MessageNode *MSGJoin(MessageNode * msgRootFirst, MessageNode * msgRootSecond, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * 函数名称: MessageNode * MSGCombine()
 * 函数功能: 将第二个消息合并到第一个消息,返回总消息,如果两个的根节点名不同
 *			 则返回错误
 * 输入参数: 
 *			MessageNode **msgFrst	第一个节点
 *			MessageNode * msgSnd	第二个节点
 * 输出参数：
 * 返    回：
 *			0 					成功
 *			MSG_NODE_NULL		失败
 * 备    注：对于同名节点,第二个消息的数据将忽略;用复制法不修改第二个节点,而删除法第二个节点多余的被删除(不可恢复)
 */
int MSGCombine(MessageNode **msgFst, MessageNode * msgSnd);

/* 
 * 函数名称: int  MSGCopy()
 * 函数功能: 将第二个消息合并到第一个消息,返回总消息,如果两个的根节点名不同
 *			 则返回错误
 * 输入参数: 
 *			MessageNode *msgFrst	第一个节点
 *			char		*name1		第一个节点名称
 *			MessageNode *msgSnd		第二个节点
 *			char		*name2		第二个节点名称
 * 输出参数：
 * 返    回：
 *			0 					成功
 *			MSG_NODE_NULL		失败
 */
int MSGCopy(MessageNode *msgFst, char *name1, MessageNode *msgSnd, char *name2);

/* 
 * 函数名称: int  MSGChgNodeName()
 * 函数功能: 修改节点名称
 * 输入参数: 
 *			MessageNode *msgRoot	节点
 *			char *nodeName			节点名称
 *			char *newName			新名称
 * 输出参数：
 * 返    回：
 *			0 					成功
 *			MSG_MALLOC_ERR		失败
 */
int MSGChgNodeName(MessageNode *msgRoot, char *nodeName, char *newName);

/* 
 * 函数名称: int MSGGetNodename
 * 函数功能: 得到一个节点的全名
 * 输入参数: 
 *			MessageNode * msgRoot	根节点
 *			char *nodeName          节点名称
 *			char maxlen				存放节点名称的最大长度
 * 输出参数：
 *			MessageNode * msgNode	节点指针
 * 返    回：
 *			0						成功
 *			PUB_STR2SHORT			长度不足
 *			MSG_NODE_NOT_FOUND		没有找到
 */
int MSGGetNodename(MessageNode *msgRoot, char * nodeName, int maxlen);













/*========================格式转换函数==============================*/


/* 
 * 函数名称: Int MSGNode2String
 * 函数功能: 将一个节点数据转换为字符格式(不是一个通过结束符标识字符串!)
 * 输入参数: 
 *			MessageNode * msgNode	节点
 *			int  maxlen				最大长度(可写长度,不包括结束符等)
 * 输出参数：
 *			char *string			流状数据格式
 * 返    回：
 *			>=0						成功,流状数据长度
 *			PUB_STR2SHORT			可写长度不足
 *			MSG_NODE_NULL			节点为空
 */
int MSGNode2String(MessageNode * msgNode, char * string, int maxlen);

/* 
 * 函数名称: Int MSGTree2Stream
 * 函数功能: 将树状格式消息转换成流状格式消息
 * 输入参数: 
 *			MessageNode * msgRoot	起始节点
 *			int  maxlen				最大长度(可写长度,不包括结束符等)
 * 输出参数：
 *			char *streamMessage		流状数据格式
 * 返    回：
 *			>=0						成功,流状数据长度
 *			PUB_STR2SHORT			可写长度不足
 *			MSG_NODE_NULL			节点为空
 */
int MSGTree2Stream(MessageNode * msgRoot, char * streamMessage, int  maxlen);

/* 
 * 函数名称: Int MSGTree2Stream
 * 函数功能: 将树状格式消息转换成流状格式消息
 * 输入参数: 
 *			MessageNode * msgRoot	起始节点
 *			int  maxlen				最大长度(可写长度,不包括结束符等)
 * 输出参数：
 *			char *streamMessage		流状数据格式
 * 返    回：
 *			>=0						成功,流状数据长度
 *			PUB_STR2SHORT			可写长度不足
 *			MSG_NODE_NULL			节点为空
 */
int MSGTree2Stream(MessageNode * msgRoot, char * streamMessage, int  maxlen);








/*========================打印函数=================================*/

/* 
 * 函数名称: 
 * 函数功能: 测试用的打印函数
 * 输入参数: 
 *			MessageNode * msgNode	起始节点
 *			char *nodeName			节点名称
 *			int  Level				打印层次
 *			int  deep				打印树的深度
 * 输出参数：
 * 返    回：
 */
 
int MSGPrnTree(MessageNode *msgNode, int Level, int deep);
int MSGPrnTreeByname(MessageNode *msgRoot, char *nodeName, int deep);

int MSGFPrnTree(char *filename, char *file, int line, MessageNode *msgNode, int Level, int deep, char *str);
int MSGFPrnTreeByname(char *filename, char *file, int line, MessageNode *msgRoot, char *nodeName, int deep, char *str);

#endif
