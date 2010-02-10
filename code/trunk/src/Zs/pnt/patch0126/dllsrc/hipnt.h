/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hipnt.h
 Author         : Jamez
 Version        : 1.0
 Date           : 20081013
 Description    : 非税业务
 Others         : 无
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
   1    20081013    Jamez       Create

******************************************************************************/
#ifndef _HIPNT_H
#define _HIPNT_H

#include "hibase.h"
#include "hionline.h"
#include "hidatabase.h"
#include "hibusmsg.h"
#include "hibppubdef.h"
#include "hidbt.h"
#include "hipex.h"

#define ClearStr(str) memset(str,'\0',sizeof(str))

#define MaxDataLen 102400
#define RecNumLen  2
#define RecNamLen  20

/*原子函数返回值定义*/
#define   MsgTypLen      1   /*返回码类型*/
#define   RspCodLen      6   /*返回码*/
#define   RspMsgLen     56   /*返回信息*/
#define CrcCodLen 5 
#define FulCrcLen 5 
#define TCrpCdLen 20 
#define TVchIdLen 50
#define BilAmtLen 16
#define OutDataLen 100

#define TBilTpLen 8
#define PayNamLen 100
#define ActNoLen  50
#define ActNamLen 50
#define TxnAmtLen 16
#define PrjNumLen 1
#define PrjCodLen 14
#define PrjNamLen 100
#define FeeNumLen 50
#define FeeStdLen 16
#define FeeAmtLen 16
#define PrjAmtLen 16
#define SmrLen    500
#define RmkNumLen 1
#define RmkLen    500

#endif /* _HIPNT_H */
