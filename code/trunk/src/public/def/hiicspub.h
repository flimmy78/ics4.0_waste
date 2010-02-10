/******************************************************************************

                Copyright (C),1998-2004,Hisuntech Co.,Ltd.

 File name      : hiicspub.h
 Author         : Liang Wen Jian
 Version        : 1.0
 Date           : 2004-03-30
 Description    : ICS公共基本库头文件
 Others         : 无
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2004-03-30  LiangWJ     完成

******************************************************************************/
#ifndef	_H_HIICSPUB_
#define	_H_HIICSPUB_

#include "hixml.h"
#include "hipubpra.h"

#define	ALIAS_PARA		"_"
#define ENV_PARA		'$'
#define	ALIAS_PARA_LEN	strlen(ALIAS_PARA)

/* 
 * 函数: icsReplacePara
 * 功能: 替换XML参数
 */
int icsReplacePara (
    XmlNode *root,          /* XML树的根节点 */
	char	*node_name);    /* 参数父节点名 */


/* 
 * 函数: icsRepIncludeAndMacroNode
 * 功能: 替换XML配置中的Include和Macro节点
 */
int icsRepIncludeAndMacroNode (
    XmlNode *root);          /* XML树的根节点 */

#endif /* _H_HIICSPUB_ */
