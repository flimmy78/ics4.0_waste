/******************************************************************************

                Copyright (C),1998-2004,Hisuntech Co.,Ltd.

 File name      : hiicspub.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2004-03-30
 Description    : ICS����������ͷ�ļ�
 Others         : ��
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2004-03-30  LiangWJ     ���

******************************************************************************/
#ifndef	_H_HIICSPUB_
#define	_H_HIICSPUB_

#include "hixml.h"
#include "hipubpra.h"

#define	ALIAS_PARA		"_"
#define ENV_PARA		'$'
#define	ALIAS_PARA_LEN	strlen(ALIAS_PARA)

/* 
 * ����: icsReplacePara
 * ����: �滻XML����
 */
int icsReplacePara (
    XmlNode *root,          /* XML���ĸ��ڵ� */
	char	*node_name);    /* �������ڵ��� */


/* 
 * ����: icsRepIncludeAndMacroNode
 * ����: �滻XML�����е�Include��Macro�ڵ�
 */
int icsRepIncludeAndMacroNode (
    XmlNode *root);          /* XML���ĸ��ڵ� */

#endif /* _H_HIICSPUB_ */
