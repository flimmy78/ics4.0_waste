#include <sql.h>
#include "hibase.h"
#include "hionline.h"
#include "hidatabase.h"
#include "hibusmsg.h"
#include "hibppubdef.h"
#include "hipex.h"
#define ClearStr(str) memset(str,'\0',sizeof(str))
/******************************************************************************
  Function          : RtyGetMD5
  Description       :
  Calls             : 被本函数调用的函数清单
  Called By         : 调用本函数的函数清单
  Table Accessed    :
  Table Updated     : 无
  Input             : ETF *TrNode 输入树
                      ST_TranData* trdata 公共结构
                      char* args  参数
                      DBConHandle* DBHandle 数据库句柄
  Output            : 对输出参数的说明。
  Return            : 0--成功 小于0--失败
  Others            : 其它说明
******************************************************************************/
int RtyGetMD5(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sMsgTyp[2];
  EXEC SQL END DECLARE SECTION;
  char  sOrgDat[22+1];
  char  sNewDat[32+1];
  int ret;

  ClearStr( sMsgTyp );
  ClearStr( sOrgDat );
  ClearStr( sNewDat );

  bpTraceLog( trdata, "开始调用RtyRtyGetMD5函数\n");
  strcpy( sOrgDat, Step_Arg1 );
  bpTraceLog( trdata, "sOrgDat=[%s]\n",sOrgDat);
  /*ret=MD5X(sOrgDat,sNewDat);*/
  ret=md5(sOrgDat,sNewDat);
  bpTraceLog( trdata, "sNewDat=[%s]\n",sNewDat);
  etfAddOrRepNode( TrNode, "FMPVal", sNewDat, 32 );
  bpTraceLog( trdata, "结束调用RtyRtyGetMD5函数\n");
  return (0);
}





