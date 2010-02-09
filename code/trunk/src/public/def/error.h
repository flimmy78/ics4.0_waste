#ifndef CC_ERROR_H_
#define CC_ERROR_H_

/* 共用错误码*/ 
#define PUB_STR2SHORT			-1
#define PUB_STR2LONG			-2
#define PUB_SEMERR				-3



/* 消息格式模块 */
#define MSG_NEW_ERR				-151	/*建立新节点出错*/
#define MSG_NODE_EXIST			-152	/*节点已经存在*/
#define MSG_NODE_NOT_FOUND		-153	/*节点没有找到*/
#define MSG_NODE_APPEND_ERR		-154	/*增加子节点出错*/
#define MSG_DATA_LEN_ERR		-155	/*数据长度指示错误	*/
#define MSG_MALLOC_ERR			-156	/*分配空间出错*/
#define MSG_NODE_NULL			-157	/*节点为空*/
#define MSG_PTR_ERR				-158	/*MSG中指针出错,出现此错误要仔细检查程序!*/
#define MSG_STRFMT_ERR			-159	/*流状消息格式错误*/
#define MSG_NAME_NOT_MATCH		-160	/*流状消息格式错误*/
#define MSG_NODENAME_ERR		-161

#endif
