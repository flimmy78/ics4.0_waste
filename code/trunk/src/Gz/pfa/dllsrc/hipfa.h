/******************************************************************************

                Copyright (C),1998-2003,Hisuntech Co.,Ltd.

 File name      : hipfa.h
 Author         : Chen YG
 Version        : 1.0
 Date           : 2004-04-13
 Description    : �������֧��
 Others         : ��
 History        :

  No.   Date        Author      Modification
  ===   ==========  ========    ==============================================
  001   2003-11-04  ChenYG      ���

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

#define MaxPNmLen   4   /*ÿҳ������*/
#define PageNmLen   4   /*��ѯҳ��*/
#define RecNumLen   4   /*�ṹ�����*/
#define MaxRecLen   4   /*������*/

#define BVchTpLen      3   /*ƾ֤����*/
#define BVchTpLen      3   /*ƾ֤����*/
#define VchNoLen       8   /*ƾ֤����*/
#define CountLen       3   /*��������*/
#define AmtLen        15   /*���*/
#define FeeCodLen      4   /*�����Ѵ���*/

#endif /* _HIPFA_H */
