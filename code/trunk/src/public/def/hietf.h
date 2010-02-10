/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hietf.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2003-05-10
 Description    : 报文数据格式头文件
 Others         : 无
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-05-10  LiangWJ     完成

******************************************************************************/
#ifndef	_HIETF_H_
#define	_HIETF_H_

typedef	void	ETF;

/* 名字层次分隔符 */
#define	MSG_SEP_CHR		'.'

#ifdef	_HIETF_LIB_
#define	EXTERN
#else
#define	EXTERN	extern
#endif

/*========================以下为函数说明================================*/
/*========================树状消息处理函数==============================*/

/*=======================================================================
 * 函数名称: ETF * etfNewNode
 * 函数功能: 建立新的节点
 * 输入参数: 
 *			char * name	        	节点名称
 *			char * data				数据内容
 *			int  dataLen			数据长度
 * 输出参数：无
 * 返    回：生成的节点指针(失败为NULL)
=======================================================================*/
EXTERN ETF * etfNewNode(char * name, char * data, int dataLen);

/*=======================================================================
 * 函数名称: char * etfGetNodeName
 * 函数功能: 取指定节点的名字
 * 输入参数:
 *          ETF * node              节点指针
 * 输出参数：无
 * 返    回：节点名字指针
=======================================================================*/
EXTERN char * etfGetNodeName(ETF * node);

/*======================================================================= 
 * 函数名称: ETF * etfAppendNode()
 * 函数功能: 将一个节点作为另外一个节点的最后一个子节点添加上去,
 *			 如果父节点为空,返回子节点,子节点为空,不作改动返回父节点
 * 输入参数: 
 *			ETF * parent			起始节点
 *			ETF * child				起始节点
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
=======================================================================*/
EXTERN ETF * etfAppendNode(ETF * parent, ETF * child);

/*=======================================================================
 * 函数名称: ETF * etfGetChildNode
 * 函数功能: 根据名字查找子节点
 * 输入参数: 
 *			ETF * parent			父节点
 *			ETF * ref_child			参考子节点(起始节点)
 *			char * name				节点名称
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
=======================================================================*/
EXTERN ETF * etfGetChildNode(ETF * parent, ETF * ref_child, char * name);

/*======================================================================= 
 * 函数名称: ETF * etfGetNode
 * 函数功能: 按名字在指定节点下取节点
 * 输入参数: 
 *			ETF * parent			父节点
 *			ETF * ref_child			参考子节点
 *			char * name				节点名称
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
=======================================================================*/
EXTERN ETF * etfGetNode(ETF * parent, ETF * ref_child, char * name);

/*======================================================================= 
 * 函数名称: ETF * etfGetRootNode
 * 函数功能: 根据一个节点取根节点
 * 输入参数: 
 *			ETF * node				当前节点
 * 输出参数：
 * 返    回：
 *			NULL					没有找到
 *			Not NULL				节点指针
=======================================================================*/
EXTERN ETF * etfGetRootNode(ETF * node);

/*=======================================================================
 * 函数名称: int etfFreeNode
 * 函数功能: 释放一个节点的内存空间,没有任何指针处理
 * 输入参数: 
 *			ETF * node				节点
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			-1						失败
=======================================================================*/
EXTERN int  etfFreeNode(ETF * node);

/*=======================================================================
 * 函数名称: int etfAddNode
 * 函数功能: 将指定长度消息增加在指定节点为父节点下面
 * 输入参数: 
 *			ETF * parent			父节点
 *			char * name				节点名称
 *			char * data				数据内容
 *			int  dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			-1						失败
=======================================================================*/
EXTERN int  etfAddNode(ETF * parent, char * name, char * data, int dataLen);

/*=======================================================================
 * 函数名称: int etfAddOrRepNode
 * 函数功能: 将指定长度消息增加在指定节点为父节点下面,如果节点存在,则重新赋值
 * 输入参数: 
 *			ETF * parent			父节点
 *			char * name				节点名称
 *			char * data				数据内容
 *			int  dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			-1						失败
=======================================================================*/
EXTERN int  etfAddOrRepNode(ETF * parent, char * name, char * data, int dataLen);

/*=======================================================================
 * 函数名称: int etfSetValue
 * 函数功能: 修改一个节点的数据
 * 输入参数: 
 *			ETF * root				根节点指针
 *			char * name				节点名称(如果为空则根节点)
 *			char * data				数据内容
 *			int  dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			-1						失败
=======================================================================*/
EXTERN int  etfSetValue(ETF * root, char * name, char * data, int dataLen);

/*=======================================================================
 * 函数名称: int etfSetChildValue
 * 函数功能: 修改一个子节点的数据
 * 输入参数: 
 *			ETF * root				根节点指针
 *			char * name				节点名称(如果为空则根节点)
 *			char * data				数据内容
 *			int  dataLen			数据长度
 * 输出参数：无
 * 返    回：
 *			0						成功
 *			-1						失败
=======================================================================*/
EXTERN int  etfSetChildValue(ETF * root, char * name, char * data, int dataLen);

/*=======================================================================
 * 函数名称: Int etfGetValue
 * 函数功能: 取得一个节点的数据
 * 输入参数: 
 *			ETF * root	            根节点
 *			char * name             节点名称
 *			int maxlen	            数据最大长度
 * 输出参数：
 *			char * data	            数据内容
 * 返    回：
 *			>=0						成功,数据长度
 *			-1						失败
=======================================================================*/
int	etfGetValue(ETF * root, char * name, char * data, int maxlen);

/*=======================================================================
 * 函数名称: char * etfReturnValue
 * 函数功能: 返回一个节点的数据
 * 输入参数: 
 *			ETF * root	            根节点
 *			char * name             节点名称
 * 输出参数：
 *			int * datalen	        数据长度
 * 返    回：
 *			非NULL				    成功,数据首地址
 *			NULL				    失败
=======================================================================*/
char * etfReturnValue(ETF * root, char * name, int * datalen);

/*=======================================================================
 * 函数名称: Int etfGetChildValue
 * 函数功能: 取得一个子节点的数据
 * 输入参数: 
 *			ETF * root	            根节点
 *			char * name             节点名称
 *			int maxlen	            数据最大长度
 * 输出参数：
 *			char * data	            数据内容
 * 返    回：
 *			>=0						成功,数据长度
 *			-1						失败
=======================================================================*/
EXTERN int	etfGetChildValue(ETF * root, char * name, char * data, int maxlen);

/*=======================================================================
 * 函数名称: char * etfReturnChildValue
 * 函数功能: 返回一个子节点的数据
 * 输入参数: 
 *			ETF * root	            根节点
 *			char * name             节点名称
 * 输出参数：
 *			int * datalen	        数据长度
 * 返    回：
 *			非NULL				    成功,数据首地址
 *			NULL				    失败
=======================================================================*/
char * etfReturnChildValue(ETF * root, char * name, int * datalen);

/*=======================================================================
 * 函数名称: char * etfReturnNodeValue
 * 函数功能: 返回当前节点的数据
 * 输入参数: 
 *			ETF * node	            当前节点
 * 输出参数：
 *			int * datalen	        数据长度
 * 返    回：
 *			非NULL				    成功,数据首地址
 *			NULL				    失败
=======================================================================*/
char * etfReturnNodeValue(ETF * root, int * datalen);

/*=======================================================================
 * 函数名称: int etfDelAllNode
 * 函数功能: 删除一个节点的所有子节点以及后续子节点,并释放自身节点
 * 输入参数: 
 *			ETF * root				根节点
 * 输出参数：无
 * 返    回：
 *			0						成功
=======================================================================*/
EXTERN int  etfDelAllNode(ETF * root);

/*=======================================================================
 * 函数名称: int etfDelNode
 * 函数功能: 删除一个节点及其下的所有子节点,并修改父节点、上下兄弟节点指针
 * 输入参数: 
 *			ETF * node				节点
 *			char * name          	子节点名称(NULL则删除整个消息)
 * 输出参数：无
 * 返    回：
 *			0						成功
=======================================================================*/
EXTERN int  etfDelNode(ETF * node, char * name);

/*=======================================================================
 * 函数名称: ETF * etfCloneNode
 * 函数功能: 复制消息(包括子节点)
 * 输入参数: 
 *			ETF * root				根节点
 * 输出参数：无
 * 返    回：
 *			Not NULL				复制的消息指针
 *			NULL					失败
=======================================================================*/
EXTERN ETF * etfCloneNode(ETF * root);

/*========================格式转换函数==============================*/

/*=======================================================================
 * 函数名称: char * etfTree2Stream
 * 函数功能: 将树状格式消息转换成流状格式消息
 * 输入参数: 
 *			ETF * root				起始节点
 * 输出参数：
 *			int * len				数据长度
 * 返    回：
 *			Not NULL				复制的消息指针
 *			NULL					失败
=======================================================================*/
EXTERN char * etfTree2Stream(ETF * root, int * len);

/*=======================================================================
 * 函数名称: Int etfStream2Tree
 * 函数功能: 将流状格式消息转换成树状格式消息
 * 输入参数: 
 *			char * stream			流状数据格式
 *			int  strlen				流状数据长度
 * 输出参数：
 *			ETF ** root             树状根节点的指针
 * 返    回：
 *			0						成功
 *			-1						失败
=======================================================================*/
EXTERN int etfStream2Tree(char * stream, int strlen, ETF ** root);

/*=======================================================================
 * 函数名称: Int etfCombineNoReplace
 * 函数功能: 合并两个数据树, 如果源树的节点在目标树已存在, 不进行替换
 * 输入参数: 
 *			ETF * d_root            目标树根节点
 *			ETF * s_root            源树根节点
 * 输出参数：
 *			int						处理结果
 * 返    回：
 *			0						成功
 *			-1						失败
=======================================================================*/
EXTERN int etfCombineNoReplace(ETF * d_root, ETF * s_root);

/*=======================================================================
 * 函数名称: Int etfCombineReplace
 * 函数功能: 合并两个数据树, 如果源树的节点在目标树已存在, 进行替换
 * 输入参数: 
 *			ETF * d_root            目标树根节点
 *			ETF * s_root            源树根节点
 * 输出参数：
 *			int						处理结果
 * 返    回：
 *			0						成功
 *			-1						失败
=======================================================================*/
EXTERN int etfCombineReplace(ETF * d_root, ETF * s_root);

/*=======================================================================
 * 函数名称: Int etfNodeRename
 * 函数功能: 改变节点名字
 * 输入参数: 
 *			ETF * node	            需要改名的节点
 *			char * name	            新节点名
 * 输出参数：
 *			int						处理结果
 * 返    回：
 *			0						成功
 *			-1						失败
=======================================================================*/
EXTERN int etfNodeRename(ETF * node, char * name);

/*=======================================================================
 * 函数名称: ETF * etfGetFirstChild
 * 函数功能: 取第一个子节点
 * 输入参数: ETF * parent	        - 父节点
 * 输出参数：
 * 返    回：ETF *         			- 子节点指针
             NOT NULL      			- 成功
			 NULL          			- 失败
=======================================================================*/
EXTERN ETF * etfGetFirstChild(ETF * parent);

/*=======================================================================
 * 函数名称: ETF * etfGetNextNode
 * 函数功能: 取下一个兄弟节点
 * 输入参数: ETF * node	            - 当前节点
 * 输出参数：
 * 返    回：ETF *         			- 下一个节点指针
             NOT NULL      			- 成功
			 NULL          			- 失败
=======================================================================*/
EXTERN ETF * etfGetNextNode(ETF * node);

/*=======================================================================
 * 函数名称: int etfGetNodeValue
 * 函数功能: 取当前节点的数据
 * 输入参数: ETF * node	            - 当前节点
			 int maxlen				- 数据最大长度
 * 输出参数：char * data 			- 节点数据
 * 返    回：int					- 数据长度
             >=0           			- 成功
			 <0            			- 失败
=======================================================================*/
EXTERN int	etfGetNodeValue(ETF * node, char * data, int maxlen);

/*=======================================================================
 * 函数名称: ETF * etfRemoveNode
 * 函数功能: 将当前节点从树中移开
 * 输入参数: ETF * node	            - 当前节点
 * 输出参数：无
 * 返    回：ETF *					- 当前节点
             NOT NULL      			- 成功
			 NULL          			- 失败
=======================================================================*/
EXTERN ETF * etfRemoveNode(ETF * node);

/*=======================================================================
 * 函数名称: ETF * etfSetAttrValue
 * 函数功能: 向节点添加属性
 * 输入参数: ETF * node	            - 当前节点
 　　　　　　char * name            - 属性名
             char * value           - 属性值
 * 输出参数：无
 * 返    回：ETF *					- 当前节点
             NOT NULL      			- 成功
			 NULL          			- 失败
=======================================================================*/
int etfSetAttrValue(ETF * node, char *name, char *value);

#undef	EXTERN

#endif	/* _HIETF_H_ */
