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
  Calls             : �����������õĺ����嵥
  Called By         : ���ñ������ĺ����嵥
  Table Accessed    :
  Table Updated     : ��
  Input             : ETF *TrNode ������
                      ST_TranData* trdata �����ṹ
                      char* args  ����
                      DBConHandle* DBHandle ���ݿ���
  Output            : �����������˵����
  Return            : 0--�ɹ� С��0--ʧ��
  Others            : ����˵��
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

  bpTraceLog( trdata, "��ʼ����RtyRtyGetMD5����\n");
  strcpy( sOrgDat, Step_Arg1 );
  bpTraceLog( trdata, "sOrgDat=[%s]\n",sOrgDat);
  /*ret=MD5X(sOrgDat,sNewDat);*/
  ret=md5(sOrgDat,sNewDat);
  bpTraceLog( trdata, "sNewDat=[%s]\n",sNewDat);
  etfAddOrRepNode( TrNode, "FMPVal", sNewDat, 32 );
  bpTraceLog( trdata, "��������RtyRtyGetMD5����\n");
  return (0);
}





