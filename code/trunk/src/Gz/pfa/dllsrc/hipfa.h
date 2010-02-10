/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hipfa.h
 Author         : Chen YG
 Version        : 1.0
 Date           : 2004-04-13
 Description    : 代理财政支付
 Others         : 无
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-11-04  ChenYG      完成

******************************************************************************/
#ifndef  _HIPFA_H
#define  _HIPFA_H

#include "hionline.h"
#include "hionlinedb.h"
#include "hibusmsg.h"
#include "hidatabase.h"
#include "msgfmt.h"
#include "hietf.h"
#include "hibppubdef.h"
#include "hidbt.h"
#include "hiafp.h"
#include "hipex.h"

#define MaxLen   200


#define ARECOD_LEN          3
#define DEPTNO_LEN          3
#define TTLRID_LEN          4
#define TTRMNO_LEN          4
#define CCYTYP_LEN          2
#define VCHTYP_LEN          3
#define VCHNO_LEN           8
#define UDWDAT_LEN          8
#define CCLNO_LEN          12
#define PFAPIN_LEN         16
#define CCLSQN_LEN          4
#define RECV_ACCT_LEN      30
#define RECV_NAME_LEN      60
#define SMR_LEN            60
#define PPS_LEN           254
#define PFASUB_LEN          4
#define BufLen           4096

#define ArgNamLen   20
#define RecNamLen   30

#define ClearStr(str) memset(str,'\0',sizeof(str))

#define MaxPNmLen   4   /*每页最大笔数*/
#define PageNmLen   4   /*查询页号*/
#define RecNumLen   4   /*结构体笔数*/
#define MaxRecLen   4   /*最大笔数*/

#define BVchTpLen      3   /*凭证种类*/
#define BVchTpLen      3   /*凭证种类*/
#define VchNoLen       8   /*凭证号码*/
#define CountLen       3   /*购买数量*/
#define AmtLen        15   /*金额*/
#define FeeCodLen      4   /*手续费代码*/

#endif /* _HIPFA_H */
