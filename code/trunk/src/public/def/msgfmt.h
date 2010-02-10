#ifndef CC_MSGFMT_H_
#define CC_MSGFMT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "error.h"


#define MSG_SEP_CHR    		'.'   /* �ڵ����ֵķָ���, �����������а����ָ���, 
								���к�����ʱ����ת�崦�� */
#define MSG_MAX_NAME_LEN	1024  /* �ڵ�������󳤶�(ȫ·������) */
#define STRLEN_LEN			4     /* ����״���ݸ�ʽ�г���λ�� */

/*	��Ϣ��ʽ�еĽڵ�����(ʵ��û������!!) */
#define MSG_NT_ROOT		'R'		/* ���ڵ� */
#define MSG_NT_BRANCH	'B'		/* ��֦�ڵ� */
#define MSG_NT_LEAF		'L'		/* Ҷ�ӽڵ� */

/*	��Ϣ��ʽ�е��������� */
#define MSG_DT_LNG		'L'
#define MSG_DT_INT		'I'
#define MSG_DT_SHT		'H'		/* ������ */
#define MSG_DT_FLT		'F'		/* ������ */
#define MSG_DT_DBL		'D'		/* ˫���� */
#define MSG_DT_STR		'S'		/* �ַ���,����GetValueʱ�ж�ΪS,�Զ�����0 */
#define MSG_DT_CHR		'C'
#define MSG_DT_BOL		'B'		/* ������ */

typedef struct _message_node{
	char * name;          	/*�ڵ����֣������¼���ֻ����������*/
	unsigned char nodeType; /*�ڵ����ͣ�������'R'����'F'*/
	unsigned char dataType; /*��ڵ���������ͣ���������/�ַ���/����ֵ�ȵ�*/
	char * data;           	/*�������ݣ�ȫ��ʹ���ַ�����ʾ*/
	int dataLen;           	/*��ڵ��������ݵĳ���*/
	struct _message_node *parent;
	struct _message_node *firstChild;
	struct _message_node *lastChild;
	struct _message_node *prevSibling;
	struct _message_node *nextSibling;
}MessageNode;

/*	����ĳЩ�����Ҫ��һЩ�ڵ��������� */
typedef struct _msg_node_list{
	MessageNode *msgNode;
	struct _msg_node_list *next;
}MsgNodeList;

#define MSGNOD_SIZE 		sizeof(MessageNode)

/*========================����Ϊ����˵��================================*/
/*========================��״��Ϣ������==============================*/

/* 
 * ��������: MessageNode * MSGNewNode
 * ��������: �����µĽڵ�
 * �������: 
 *			char *name		�ڵ�����
 *			unsigned char nodeType	�ڵ�����
 *			unsigned char dataType	��������
 *			char *data				��������
 *			char dataLen			���ݳ���
 * �����������
 * ��    �أ����ɵĽڵ�ָ��(ʧ��ΪNULL)
 */
MessageNode * MSGNewNode(char *name, unsigned char nodeType, unsigned char dataType, char *data, int dataLen);

/* 
 * ��������: MessageNode * MSGAppendNode()
 * ��������: ��һ���ڵ���Ϊ����һ���ڵ�����һ���ӽڵ������ȥ,
 *			 ������ڵ�Ϊ��,�����ӽڵ�,�ӽڵ�Ϊ��,�����Ķ����ظ��ڵ�
 * �������: 
 *			MessageNode * msgParent	��ʼ�ڵ�
 *			MessageNode * msgChild	��ʼ�ڵ�
 * ���������
 * ��    �أ�
 *			NULL					û���ҵ�
 *			Not NULL				�ڵ�ָ��
 */
MessageNode * MSGAppendNode(MessageNode *msgParent, MessageNode *msgChild);

/* 
 * ��������: MessageNode * MSGGetNode
 * ��������: ��ָ���ڵ㿪ʼ�������ֲ���һ���ڵ�, ���ֿ����ǲ�ε�, ��Root.Agent
 * �������: 
 *			MessageNode * msgRoot	��ʼ�ڵ�
 *			char *nodeName			�ڵ�����
 * ���������
 * ��    �أ�
 *			NULL					û���ҵ�
 *			Not NULL				�ڵ�ָ��
 */
MessageNode * MSGGetNode(MessageNode * msgRoot, char * nodeName);

/* 
 * ��������: MessageNode * MSGGetNodeAllOver
 * ��������: ��ָ���ڵ㿪ʼ�������ֲ���һ���ڵ�, ����(������)�ǲ�ε�
 * �������: 
 *			MessageNode * parent	���ڵ�
 *			MessageNode * ref_child	�ο��ӽڵ�
 *			char * name				�ڵ�����
 * ���������
 * ��    �أ�
 *			NULL					û���ҵ�
 *			Not NULL				�ڵ�ָ��
 */
MessageNode * MSGGetNodeAllOver(MessageNode * parent, MessageNode * ref_child, char * name);

/* 
 * ��������: MessageNode * MSGRemoveNode
 * ��������: ���ӽڵ�����������
 * �������: 
 *			MessageNode * old_child	�ӽڵ�
 * ���������
 * ��    �أ�
 *			NULL					ʧ��
 *			Not NULL				�ڵ�ָ��
 */
MessageNode * MSGRemoveNode(MessageNode * old_child);

/* 
 * ��������: MessageNode * MSGGetChildNodeBynum
 * ��������: ����ָ���ڵ�ĵ�n���ӽڵ�
 * �������: 
 *			MessageNode * msgRoot	��ʼ�ڵ�
 *			int  occ				���(<=0 Ϊ���һ��)
 * ���������
 * ��    �أ�
 *			NULL					û���ҵ�
 *			Not NULL				�ڵ�ָ��
 */
MessageNode * MSGGetChildNodeBynum(MessageNode * msgRoot, int occ);

/* 
 * ��������: MessageNode * MSGGetChildNode
 * ��������: �������ֲ����ӽڵ�
 * �������: 
 *			MessageNode * msgRoot	��ʼ�ڵ�
 *			char *nodeName			�ڵ�����
 * ���������
 * ��    �أ�
 *			NULL					û���ҵ�
 *			Not NULL				�ڵ�ָ��
 */
MessageNode * MSGGetChildNode(MessageNode * msgRoot, char *nodeName);

/* 
 * ��������: MessageNode * MSGGetChildNodeX
 * ��������: �ڲο��ӽڵ��������ֲ����ӽڵ�
 * �������: 
 *			MessageNode * msgRoot	��ʼ�ڵ�
 *			MessageNode * refChild	�ο��ӽڵ�
 *			char *nodeName			�ڵ�����
 * ���������
 * ��    �أ�
 *			NULL					û���ҵ�
 *			Not NULL				�ڵ�ָ��
 */
MessageNode * MSGGetChildNodeX(MessageNode * msgRoot, MessageNode * refChild, char *nodeName);

/* 
 * ��������: MessageNode * MSGGetSibNode
 * ��������: ����ָ���ڵ�ĵ�n���ֵܽڵ�
 * �������: 
 *			MessageNode * msgRoot	��ʼ�ڵ�
 *			int  dir				���ҷ���(>=0����,<0��ǰ)
 *			int  occ				���(<0 Ϊ���һ��)
 * ���������
 * ��    �أ�
 *			NULL					û���ҵ�
 *			Not NULL				�ڵ�ָ��
 */
MessageNode * MSGGetSibNode(MessageNode * msgRoot, int dir, int occ);

/* 
 * ��������: MessageNode * MSGSearchNode 
 * ��������: ����һ����׼����������������һ���ڵ�(���Ƚ���ʼ�ڵ�)
 * �������: 
 *			MessageNode *msgRoot	��ѯ�Ļ��ڵ�
 *			char *nodeName			��ѯ�ڵ�����
 *			MessageNode *msgStart	��ѯ����ʼ�ڵ�(Ϊ���൱msgRoot)
 *			int  deep				�������(<=0���������ӽڵ�,>0����deep��)
 *			int  occ				��ѯ�ڼ���(<0���һ��)
 * ���������
 * ��    �أ�
 */
MessageNode * MSGSearchNode(MessageNode * msgRoot, char * nodeName, MessageNode *msgStart, int deep, int occ);

/* 
 * ��������: MessageNode * MSGSearchNode2 
 * ��������: ����һ����׼����������������һ���ڵ�(���Ƚ���ʼ�ڵ�)
 * �������: 
 *			MessageNode *msgRoot	��ѯ�Ļ��ڵ�
 *			char *nodeName			��ѯ�ڵ�����(�����в�ι�ϵ,��ǰһ���)
 *			MessageNode *msgStart	��ѯ����ʼ�ڵ�(Ϊ���൱msgRoot)
 *			int  deep				�������(<=0���������ӽڵ�,>0����deep��)
 *			int  occ				��ѯ�ڼ���(<0���һ��)
 * ���������
 * ��    �أ�
 */
MessageNode * MSGSearchNode2(MessageNode * msgRoot, char * nodeName, MessageNode *msgStart, int deep, int occ);

/* 
 * ��������: int MSGFreeNode
 * ��������: �ͷ�һ���ڵ���ڴ�ռ�,û���κ�ָ�봦��
 * �������: 
 *			MessageNode *msgNode	�ڵ�
 * �����������
 * ��    �أ�
 *			0		�ɹ�
 *			-1		ʧ��
 */
int  MSGFreeNode(MessageNode *msgNode);

/* 
 * ��������: int MSGAddNode
 * ��������: ��ָ��������Ϣ������ָ���ڵ�Ϊ���ڵ�����
 * �������: 
 *			MessageNode *msgRoot	���ڵ�
 *			char *parent			���ڵ�����(���Ϊ�����ڵ�ǰ�ڵ���)
 *			char *name				�ڵ�����
 *			unsigned char nodeType	�ڵ�����
 *			unsigned char dataType	��������
 *			char *data				��������
 *			char dataLen			���ݳ���
 * �����������
 * ��    �أ�
 *			0						�ɹ�
 *			MSG_DATA_LEN_ERR		���ȴ���
 *			MSG_NEW_ERR				�����½ڵ����
 *			MSG_NODE_EXIST			�ڵ��Ѿ�����
 *			MSG_NODE_APPEND_ERR		���ӽڵ����
 */
int  MSGAddNode(MessageNode *msgRoot, char *parent, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * ��������: int MSGAddOrRepNode
 * ��������: ��ָ��������Ϣ������ָ���ڵ�Ϊ���ڵ�����,����ڵ����,�����¸�ֵ
 * �������: 
 *			MessageNode *msgRoot	���ڵ�
 *			char *parent			���ڵ�����
 *			char *name				�ڵ�����
 *			unsigned char nodeType	�ڵ�����
 *			unsigned char dataType	��������
 *			char *data				��������
 *			char dataLen			���ݳ���
 * �����������
 * ��    �أ�
 *			0						�ɹ�
 *			MSG_DATA_LEN_ERR		���ȴ���
 *			MSG_NEW_ERR				�����½ڵ����
 *			MSG_NODE_EXIST			�ڵ��Ѿ�����
 *			MSG_NODE_APPEND_ERR		���ӽڵ����
 */
int  MSGAddOrRepNode(MessageNode *msgRoot, char *parent, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * ��������: int MSGAppValue
 * ��������: ������׷�ӵ�ָ���ڵ����ݺ���
 * �������: 
 *			MessageNode *msgRoot	���ڵ�
 *			char *parent			���ڵ�����
 *			char *name				�ڵ�����
 *			unsigned char nodeType	�ڵ�����
 *			unsigned char dataType	��������
 *			char *data				��������
 *			char dataLen			���ݳ���
 * �����������
 * ��    �أ�
 *			0						�ɹ�
 *			MSG_DATA_LEN_ERR		���ȴ���
 *			MSG_NEW_ERR				�����½ڵ����
 *			MSG_NODE_EXIST			�ڵ��Ѿ�����
 *			MSG_NODE_APPEND_ERR		���ӽڵ����
 */
int  MSGAppValue(MessageNode *msgRoot, char *parent, char *nodeName, char * data, int dataLen, int mode);

/* 
 * ��������: int MSGAddChildNode
 * ��������: ��ָ��������Ϣ������ָ���ڵ�Ϊ���ڵ�����
 * �������: 
 *			MessageNode *msgRoot	���ڵ�
 *			char *parent			���ڵ�����(���Ϊ�����ڵ�ǰ�ڵ���)
 *			char *name				�ڵ�����
 *			unsigned char nodeType	�ڵ�����
 *			unsigned char dataType	��������
 *			char *data				��������
 *			char dataLen			���ݳ���
 * �����������
 * ��    �أ�
 *			0						�ɹ�
 *			MSG_DATA_LEN_ERR		���ȴ���
 *			MSG_NEW_ERR				�����½ڵ����
 *			MSG_NODE_EXIST			�ڵ��Ѿ�����
 *			MSG_NODE_APPEND_ERR		���ӽڵ����
 */
int  MSGAddChildNode(MessageNode *msgRoot, char *parent, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * ��������: int MSGAddOrRepChildNode
 * ��������: ��ָ��������Ϣ������ָ���ڵ�Ϊ���ڵ�����,����ڵ����,�����¸�ֵ
 * �������: 
 *			MessageNode *msgRoot	���ڵ�
 *			char *parent			���ڵ�����
 *			char *name				�ڵ�����
 *			unsigned char nodeType	�ڵ�����
 *			unsigned char dataType	��������
 *			char *data				��������
 *			char dataLen			���ݳ���
 * �����������
 * ��    �أ�
 *			0						�ɹ�
 *			MSG_DATA_LEN_ERR		���ȴ���
 *			MSG_NEW_ERR				�����½ڵ����
 *			MSG_NODE_EXIST			�ڵ��Ѿ�����
 *			MSG_NODE_APPEND_ERR		���ӽڵ����
 */
int  MSGAddOrRepChildNode(MessageNode *msgRoot, char *parent, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * ��������: int MSGSetValue
 * ��������: �޸�һ���ڵ������
 * �������: 
 *			MessageNode *msgRoot	���ڵ�ָ��
 *			char *nodeName			�ڵ�����(���Ϊ������ڵ�)
 *			unsigned char nodeType	�ڵ�����
 *			unsigned char dataType	��������
 *			char *data				��������
 *			char dataLen			���ݳ���
 * �����������
 * ��    �أ�
 *			0						�ɹ�
 *			MSG_DATA_LEN_ERR		���ȴ���
 *			MSG_MALLOC_ERR			����ڵ�ռ��
 *			MSG_NODE_NOT_FOUND		�ڵ㲻����
 */
int  MSGSetValue(MessageNode *msgRoot, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * ��������: int MSGSetChildValue
 * ��������: �޸�һ���ڵ������
 * �������: 
 *			MessageNode *msgRoot	���ڵ�ָ��
 *			char *nodeName			�ڵ�����(���Ϊ������ڵ�)
 *			unsigned char nodeType	�ڵ�����
 *			unsigned char dataType	��������
 *			char *data				��������
 *			char dataLen			���ݳ���
 * �����������
 * ��    �أ�
 *			0						�ɹ�
 *			MSG_DATA_LEN_ERR		���ȴ���
 *			MSG_MALLOC_ERR			����ڵ�ռ��
 *			MSG_NODE_NOT_FOUND		�ڵ㲻����
 */
int  MSGSetChildValue(MessageNode *msgRoot, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * ��������: int  MSGChgNodeValue()
 * ��������: �޸Ľڵ�����
 * �������: 
 *			MessageNode *node	    �ڵ�
 *			char *data	     		������
 *			int dataLen			    �����ݳ���
 * ���������
 * ��    �أ�
 *			0 					�ɹ�
 *			-1          		ʧ��
 */
int MSGChgNodeValue(MessageNode *node, char *data, int dataLen);

/* 
 * ��������: int MSGGetValue
 * ��������: ȡ��һ���ڵ������
 * �������: 
 *			MessageNode *msgRoot	��Ϣ�ĸ��ڵ�
 *			char *nodeName          �ڵ�����
 *			char maxlen				������󳤶�
 * ���������
 *			unsigned char *nodeType	�ڵ�����
 *			unsigned char *dataType	��������
 *			char *data				��������
 * ��    �أ�
 *			>=0						�ɹ�,���ݳ���
 *			PUB_STR2SHORT			���Ȳ���
 *			MSG_NODE_NOT_FOUND		�ڵ㲻����
 */
int  MSGGetValue(MessageNode *msgRoot, char *nodeName, unsigned char *nodeType, unsigned char *dataType, char * data, int maxlen);

/* 
 * ��������: int MSGGetChildValue
 * ��������: ȡ��һ���ӽڵ������(����Ҫ���뵱ǰ�ڵ������)
 * �������: 
 *			MessageNode *msgRoot	��Ϣ�ĸ��ڵ�
 *			char *nodeName          �ڵ�����
 *			char maxlen				������󳤶�
 * ���������
 *			unsigned char *nodeType	�ڵ�����
 *			unsigned char *dataType	��������
 *			char *data				��������
 * ��    �أ�
 *			>=0						�ɹ�,���ݳ���
 *			PUB_STR2SHORT			���Ȳ���
 *			PUB_STR2LONG			����̫��
 *			MSG_NODE_NOT_FOUND		�ڵ㲻����
 */
int  MSGGetChildValue(MessageNode *msgRoot, char *nodeName, unsigned char *nodeType, unsigned char *dataType, char * data, int maxlen);

/* 
 * ��������: int MSGDelAllNode
 * ��������: ɾ��һ���ڵ�������ӽڵ��Լ������ӽڵ�,���ͷ�����ڵ�
 * �������: 
 *			MessageNode *msgNode	�ڵ�
 * �����������
 * ��    �أ�
 *			0						�ɹ�
 * ��    ע����õ���MSGDelNode
 */
int  MSGDelAllNode(MessageNode *msgNode);

/* 
 * ��������: int MSGDelNode
 * ��������: ɾ��һ���ڵ㼰���µ������ӽڵ�,���޸ĸ��ڵ㡢�����ֵܽڵ�ָ��
 * �������: 
 *			MessageNode *msgNode	�ڵ�
 *			char *nodeName          �ӽڵ�����(NULL��ɾ��������Ϣ)
 * �����������
 * ��    �أ�
 *			0						�ɹ�
 */
int  MSGDelNode(MessageNode *msgRoot, char *nodeName);

/* 
 * ��������: int MSGDetach
 * ��������: �Ͽ�һ���ӽڵ����Ϣ��������,�����ͷſռ�(ʹ��ʱ��Ҫ����,
 *			 ����ָ����ʧ�������ͷ��ڴ�ռ�)
 * �������: 
 *			MessageNode *msgNode	�ͷŽڵ�
 * �����������
 * ��    �أ�
 *			Not NULL			�Ͽ����ӽڵ�ָ��, �ɹ�
 *			NULL				ʧ��(û���ҵ���)
 */
MessageNode * MSGDetach(MessageNode *msgNode);

/* 
 * ��������: int MSGDetachChildNode
 * ��������: �Ͽ�һ���ӽڵ����Ϣ��������,�����ͷſռ�(ʹ��ʱ��Ҫ����,
 *			 ����ָ����ʧ�������ͷ��ڴ�ռ�)
 * �������: 
 *			MessageNode *msgRoot	��Ϣ���ڵ�
 *			char *nodeName			�ڵ�����
 *			int occ					�ҵ������(ͬSearch) 
 *			int deep				�������(ͬSearch) 
 * �����������
 * ��    �أ�
 *			Not NULL			�Ͽ����ӽڵ�ָ��, �ɹ�
 *			NULL				ʧ��(û���ҵ���)
 */
MessageNode * MSGDetachChildNode(MessageNode *msgRoot, char *nodeName, int occ, int deep);

/* 
 * ��������: MessageNode *MSGClone
 * ��������: ������Ϣ(�����ӽڵ�)
 * �������: 
 *			MessageNode *msgRootSrc	���ڵ�
 *			char *name				���ƵĽڵ�����(NULL��Ӹ��ڵ㿪ʼ)
 * �����������
 * ��    �أ�
 *			Not NULL				���Ƶ���Ϣָ��
 *			NULL					ʧ��
 */
MessageNode * MSGClone(MessageNode *msgRootSrc, char *nodeName);

/* 
 * ��������: MessageNode *MSGCloneNode
 * ��������: ���Ƶڶ�����Ϣ��һ���ڵ㵽��һ���ڵ���
 * �������: 
 *			MessageNode **msgFst	��һ����Ϣ�Ľڵ�
 *			MessageNode *msgSnd		�ڶ�����Ϣ�Ľڵ�
 *			char *name				���ƽڵ�����(NULLΪ���ڵ�,����Ϊ��ǰ�ӽڵ�)
 *			int  opflag				������־
 *				MSG_ADD		ֻ����,����Ѿ����ڱ���
 *				MSG_REP		1������ɾ��
 * �����������
 * ��    �أ�
 *			0					�ɹ�
 *			MSG_NODE_NOT_FOUND	���ƽڵ�û���ҵ�
 *			MSG_NODE_EXIST		�ڵ��Ѿ�����
 *			MSG_NEW_ERR			���½ڵ����
 *			MSG_NODE_APPEND_ERR	���ӽڵ����
 */
int MSGCloneNode(MessageNode **msgFst, MessageNode *msgSnd, char *nodeName, int opflag);

/* 
 * ��������: MessageNode * MSGJoin()
 * ��������: �ϲ�������Ϣ,���ڵ����Ƶ��ɲ�������
 * �������: 
 *			MessageNode * msgRootFirst	��һ���ڵ�
 *			MessageNode * msgRootSecond	�ڶ����ڵ�
 *			char *nodeName              �ܽ������
 *			unsigned char nodeType		�ܽڵ�����
 *			unsigned char dataType		�ܽڵ���������
 *			char *data				��������
 *			char dataLen			���ݳ���
 * ���������
 * ��    �أ�
 *			Not NULL				�ڵ�ָ��
 *			NULL					ʧ��
 */
MessageNode *MSGJoin(MessageNode * msgRootFirst, MessageNode * msgRootSecond, char *nodeName, unsigned char nodeType, unsigned char dataType, char * data, int dataLen);

/* 
 * ��������: MessageNode * MSGCombine()
 * ��������: ���ڶ�����Ϣ�ϲ�����һ����Ϣ,��������Ϣ,��������ĸ��ڵ�����ͬ
 *			 �򷵻ش���
 * �������: 
 *			MessageNode **msgFrst	��һ���ڵ�
 *			MessageNode * msgSnd	�ڶ����ڵ�
 * ���������
 * ��    �أ�
 *			0 					�ɹ�
 *			MSG_NODE_NULL		ʧ��
 * ��    ע������ͬ���ڵ�,�ڶ�����Ϣ�����ݽ�����;�ø��Ʒ����޸ĵڶ����ڵ�,��ɾ�����ڶ����ڵ����ı�ɾ��(���ɻָ�)
 */
int MSGCombine(MessageNode **msgFst, MessageNode * msgSnd);

/* 
 * ��������: int  MSGCopy()
 * ��������: ���ڶ�����Ϣ�ϲ�����һ����Ϣ,��������Ϣ,��������ĸ��ڵ�����ͬ
 *			 �򷵻ش���
 * �������: 
 *			MessageNode *msgFrst	��һ���ڵ�
 *			char		*name1		��һ���ڵ�����
 *			MessageNode *msgSnd		�ڶ����ڵ�
 *			char		*name2		�ڶ����ڵ�����
 * ���������
 * ��    �أ�
 *			0 					�ɹ�
 *			MSG_NODE_NULL		ʧ��
 */
int MSGCopy(MessageNode *msgFst, char *name1, MessageNode *msgSnd, char *name2);

/* 
 * ��������: int  MSGChgNodeName()
 * ��������: �޸Ľڵ�����
 * �������: 
 *			MessageNode *msgRoot	�ڵ�
 *			char *nodeName			�ڵ�����
 *			char *newName			������
 * ���������
 * ��    �أ�
 *			0 					�ɹ�
 *			MSG_MALLOC_ERR		ʧ��
 */
int MSGChgNodeName(MessageNode *msgRoot, char *nodeName, char *newName);

/* 
 * ��������: int MSGGetNodename
 * ��������: �õ�һ���ڵ��ȫ��
 * �������: 
 *			MessageNode * msgRoot	���ڵ�
 *			char *nodeName          �ڵ�����
 *			char maxlen				��Žڵ����Ƶ���󳤶�
 * ���������
 *			MessageNode * msgNode	�ڵ�ָ��
 * ��    �أ�
 *			0						�ɹ�
 *			PUB_STR2SHORT			���Ȳ���
 *			MSG_NODE_NOT_FOUND		û���ҵ�
 */
int MSGGetNodename(MessageNode *msgRoot, char * nodeName, int maxlen);













/*========================��ʽת������==============================*/


/* 
 * ��������: Int MSGNode2String
 * ��������: ��һ���ڵ�����ת��Ϊ�ַ���ʽ(����һ��ͨ����������ʶ�ַ���!)
 * �������: 
 *			MessageNode * msgNode	�ڵ�
 *			int  maxlen				��󳤶�(��д����,��������������)
 * ���������
 *			char *string			��״���ݸ�ʽ
 * ��    �أ�
 *			>=0						�ɹ�,��״���ݳ���
 *			PUB_STR2SHORT			��д���Ȳ���
 *			MSG_NODE_NULL			�ڵ�Ϊ��
 */
int MSGNode2String(MessageNode * msgNode, char * string, int maxlen);

/* 
 * ��������: Int MSGTree2Stream
 * ��������: ����״��ʽ��Ϣת������״��ʽ��Ϣ
 * �������: 
 *			MessageNode * msgRoot	��ʼ�ڵ�
 *			int  maxlen				��󳤶�(��д����,��������������)
 * ���������
 *			char *streamMessage		��״���ݸ�ʽ
 * ��    �أ�
 *			>=0						�ɹ�,��״���ݳ���
 *			PUB_STR2SHORT			��д���Ȳ���
 *			MSG_NODE_NULL			�ڵ�Ϊ��
 */
int MSGTree2Stream(MessageNode * msgRoot, char * streamMessage, int  maxlen);

/* 
 * ��������: Int MSGTree2Stream
 * ��������: ����״��ʽ��Ϣת������״��ʽ��Ϣ
 * �������: 
 *			MessageNode * msgRoot	��ʼ�ڵ�
 *			int  maxlen				��󳤶�(��д����,��������������)
 * ���������
 *			char *streamMessage		��״���ݸ�ʽ
 * ��    �أ�
 *			>=0						�ɹ�,��״���ݳ���
 *			PUB_STR2SHORT			��д���Ȳ���
 *			MSG_NODE_NULL			�ڵ�Ϊ��
 */
int MSGTree2Stream(MessageNode * msgRoot, char * streamMessage, int  maxlen);








/*========================��ӡ����=================================*/

/* 
 * ��������: 
 * ��������: �����õĴ�ӡ����
 * �������: 
 *			MessageNode * msgNode	��ʼ�ڵ�
 *			char *nodeName			�ڵ�����
 *			int  Level				��ӡ���
 *			int  deep				��ӡ�������
 * ���������
 * ��    �أ�
 */
 
int MSGPrnTree(MessageNode *msgNode, int Level, int deep);
int MSGPrnTreeByname(MessageNode *msgRoot, char *nodeName, int deep);

int MSGFPrnTree(char *filename, char *file, int line, MessageNode *msgNode, int Level, int deep, char *str);
int MSGFPrnTreeByname(char *filename, char *file, int line, MessageNode *msgRoot, char *nodeName, int deep, char *str);

#endif
