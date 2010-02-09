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
  Calls             : ±»±¾º¯Êýµ÷ÓÃµÄº¯ÊýÇåµ¥
  Called By         : µ÷ÓÃ±¾º¯ÊýµÄº¯ÊýÇåµ¥
  Table Accessed    :
  Table Updated     : ÎÞ
  Input             : ETF *TrNode ÊäÈëÊ÷
                      ST_TranData* trdata ¹«¹²½á¹¹
                      char* args  ²ÎÊý
                      DBConHandle* DBHandle Êý¾Ý¿â¾ä±ú
  Output            : ¶ÔÊä³ö²ÎÊýµÄËµÃ÷¡£
  Return            : 0--³É¹¦ Ð¡ÓÚ0--Ê§°Ü
  Others            : ÆäËüËµÃ÷
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

  strcpy( sOrgDat, Step_Arg1 );
  ret=MD5X(sOrgDat,sNewDat);
  etfAddOrRepNode( TrNode, "FMPVal", sNewDat, 32 );
  return (0);
}

/******************************************************************************
  Function          : RtyToHex
  Description       : ½«×Ö·ûÊý×Ö×ª»»Îª×Ö·ûÊ®Áù½øÖÆ
  Calls             : ±»±¾º¯Êýµ÷ÓÃµÄº¯ÊýÇåµ¥
  Called By         : µ÷ÓÃ±¾º¯ÊýµÄº¯ÊýÇåµ¥
  Table Accessed    :
  Table Updated     : ÎÞ
  Input             : ETF *TrNode ÊäÈëÊ÷
                      ST_TranData* trdata ¹«¹²½á¹¹
                      char* args  ²ÎÊý
                      DBConHandle* DBHandle Êý¾Ý¿â¾ä±ú
  Output            : ¶ÔÊä³ö²ÎÊýµÄËµÃ÷¡£
  Return            : 0--³É¹¦ Ð¡ÓÚ0--Ê§°Ü
  Others            : ÆäËüËµÃ÷
******************************************************************************/
int RtyToHex(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sMsgTyp[2];
  EXEC SQL END DECLARE SECTION;
  char  *sAscDat;
  char  *sHexDat;
  long  i,len;
  int ret;

  len = strlen(Step_Arg1);

  if (!(sAscDat = (char *) malloc(len)))
      return(-1);

  if (!(sHexDat = (char *) malloc(len)))
      return(-1);

  ClearStr( sMsgTyp );
  ClearStr( sAscDat );
  ClearStr( sHexDat );

  strcpy( sAscDat, Step_Arg1 );
  i=atol(sAscDat);
  sprintf(sHexDat,"%X",i);
  etfAddOrRepNode( TrNode, "HexDat", sHexDat, len );

  free(sAscDat);
  free(sHexDat);
  return(0);
}

/******************************************************************************
  Function          : RtyRevOrd
  Description       : ×Ö·û´®´ÓºóÃ¿Á½¸ö×Ö·ûµ¹ÅÅÆ
  Example           : 00000156×ª»»Îª56010000
  Calls             : ±»±¾º¯Êýµ÷ÓÃµÄº¯ÊýÇåµ¥
  Called By         : µ÷ÓÃ±¾º¯ÊýµÄº¯ÊýÇåµ¥
  Table Accessed    :
  Table Updated     : ÎÞ
  Input             : ETF *TrNode ÊäÈëÊ÷
                      ST_TranData* trdata ¹«¹²½á¹¹
                      char* args  ²ÎÊý
                      DBConHandle* DBHandle Êý¾Ý¿â¾ä±ú
  Output            : ¶ÔÊä³ö²ÎÊýµÄËµÃ÷¡£
  Return            : 0--³É¹¦ Ð¡ÓÚ0--Ê§°Ü
  Others            : ÆäËüËµÃ÷
******************************************************************************/
int RtyRevOrd(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char   sMsgTyp[2];
  EXEC SQL END DECLARE SECTION;
  char  *sAscDat;
  char  *sRevDat;
  long  i,len;
  int ret;
  char sTmpDat[3];

  len = strlen(Step_Arg1);

  if (!(sAscDat = (char *) malloc(len)))
      return(-1);

  if (!(sRevDat = (char *) malloc(len)))
      return(-1);

  ClearStr( sMsgTyp );
  ClearStr( sAscDat );
  ClearStr( sRevDat );
  ClearStr( sTmpDat );

  strcpy( sAscDat, Step_Arg1 );

  for ( i=len-2;i>=0;i=i-2 )
  {
      memcpy( sTmpDat, sAscDat+i, 2 );
      strcat( sRevDat, sTmpDat );
  }
  etfAddOrRepNode( TrNode, "RevDat", sRevDat, len );

  free(sAscDat);
  free(sRevDat);
  return(0);
}

/******************************************************************************
  Function          : RtyVchfToDb
  Description       : ½«½ðÈÚ´«Æ±ÆÕÍ¨ÎÄ¼þÊý¾Ý²åÈëÊý¾Ý¿â±írtytvchf
  Input             : ETF *TrNode ÊäÈëÊ÷
                      ST_TranData* trdata ¹«¹²½á¹¹
                      char* args  ²ÎÊý
                      DBConHandle* DBHandle Êý¾Ý¿â¾ä±ú
  Output            : ¶ÔÊä³ö²ÎÊýµÄËµÃ÷¡£
  Return            : 0--³É¹¦ Ð¡ÓÚ0--Ê§°Ü
  Others            : ÆäËüËµÃ÷
******************************************************************************/
int RtyVchfToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char  svchf_jrn_no          [9+1];    /*½»Ò×ÈÕÖ¾ºÅ*/
    char  svchf_vch_seq         [4+1];    /*´«Æ±ÄÚÌ×ºÅ*/
    char  svchf_ap_code         [2+1];    /*Ó¦ÓÃÂë*/
    char  svchf_ap_mmo          [2+1];    /*Ó¦ÓÃ·û*/
    char  svchf_tr_code         [4+1];    /*½»Ò×Âë*/
    char  svchf_tr_mmo          [3+1];    /*½»Ò××ÓÂë*/
    char  svchf_tr_date         [8+1];    /*½»Ò×ÈÕÆÚ*/
    char  svchf_tr_time         [6+1];    /*½»Ò×Ê±¼ä*/
    char  svchf_bk              [6+1];    /*½»Ò×»ú¹¹ËùÊô·ÖÐÐ*/
    char  svchf_br              [6+1];    /*½»Ò×»ú¹¹ºÅ*/
    char  svchf_dp              [3+1];    /*²¿ÃÅºÅ*/
    char  svchf_vch_no          [12+1];   /*´«Æ±ºÅ*/
    char  svchf_tm_no           [7+1];    /*½»Ò×ÖÕ¶ËºÅ*/
    char  svchf_his_prt         [1+1];    /*ÀúÊ·Ïî´òÓ¡±êÖ¾£¨Y/N£©*/
    char  svchf_reen_flag       [1+1];    /*ÖØÈë±êÖ¾(Y/N/F)*/
    char  svchf_vch_ec_ind      [1+1];    /*¸üÕý½»Ò×´«Æ±±êÖ¾£¨¿Õ/Y£©*/
    char  svchf_wff_flag        [1+1];    /*¸´ºË±êÖ¾(Y/N/F/C)*/
    char  svchf_sup1_id         [7+1];    /*½»Ò×ÊÚÈ¨Ö÷¹Ü1*/
    char  svchf_sup2_id         [7+1];    /*½»Ò×ÊÚÈ¨Ö÷¹Ü2*/
    char  svchf_conf_id         [7+1];    /*½»Ò×¸´ºË¹ñÔ±*/
    char  svchf_vch_type        [1+1];    /*ÀúÊ·¼ÇÂ¼ÀàÐÍ£¨A/B/C/D/N/F£©*/
    char  svchf_vch_confirm     [1+1];    /*´«Æ±ÉúÐ§ÈÕ±êÖ¾*/
    char  svchf_vch_bk          [6+1];    /*ÕÊ»§»ú¹¹ËùÊô·ÖÐÐ*/
    char  svchf_vch_br          [6+1];    /*ÕÊ»§»ú¹¹ºÅ*/
    char  svchf_vch_ccy         [3+1];    /*»õ±ÒÂë*/
    char  svchf_vch_jj          [3+1];    /*×÷ÒµÂë*/
    char  svchf_vch_tt          [3+1];    /*ÒµÎñÀà±ðÂë*/
    char  svchf_vch_ac          [21+1];   /*ÕÊºÅ*/
    char  svchf_vch_sign        [1+1];    /*½è´û·½±êÖ¾*/
    char  svchf_vch_amt         [17+1];   /*½ð¶î*/
    char  svchf_vch_val_date    [8+1];    /*ÆðÏ¢ÈÕ*/
    char  svchf_vch_stno_type   [3+1];    /*Æ¾Ö¤ÀàÐÍ*/
    char  svchf_vch_stno        [8+1];    /*µ¥¾ÝºÅÂë*/
    char  svchf_vch_opp_ind     [1+1];    /*ÏµÍ³ÄÚÕËºÅ±êÖ¾*/
    char  svchf_vch_opp_ac      [32+1];   /*¶Ô·½ÕÊºÅ*/
    char  svchf_vch_part        [24+1];   /*¼¼ÊõÕªÒª*/
    char  svchf_vch_part_b      [60+1];   /*ÒµÎñÕªÒª*/
    char  svchf_vch_m_ind       [1+1];    /*´«Æ±ºÏ²¢±êÖ¾*/
    char  svch_c_ind            [1+1];    /*¼à¶½±êÖ¾  */
  EXEC SQL END DECLARE SECTION;

    FILE  *fp;
    char  sFilename[255];

    ClearStr( svchf_jrn_no       );
    ClearStr( svchf_vch_seq      );
    ClearStr( svchf_ap_code      );
    ClearStr( svchf_ap_mmo       );
    ClearStr( svchf_tr_code      );
    ClearStr( svchf_tr_mmo       );
    ClearStr( svchf_tr_date      );
    ClearStr( svchf_tr_time      );
    ClearStr( svchf_bk           );
    ClearStr( svchf_br           );
    ClearStr( svchf_dp           );
    ClearStr( svchf_vch_no       );
    ClearStr( svchf_tm_no        );
    ClearStr( svchf_his_prt      );
    ClearStr( svchf_reen_flag    );
    ClearStr( svchf_vch_ec_ind   );
    ClearStr( svchf_wff_flag     );
    ClearStr( svchf_sup1_id      );
    ClearStr( svchf_sup2_id      );
    ClearStr( svchf_conf_id      );
    ClearStr( svchf_vch_type     );
    ClearStr( svchf_vch_confirm  );
    ClearStr( svchf_vch_bk       );
    ClearStr( svchf_vch_br       );
    ClearStr( svchf_vch_ccy      );
    ClearStr( svchf_vch_jj       );
    ClearStr( svchf_vch_tt       );
    ClearStr( svchf_vch_ac       );
    ClearStr( svchf_vch_sign     );
    ClearStr( svchf_vch_amt      );
    ClearStr( svchf_vch_val_date );
    ClearStr( svchf_vch_stno_type);
    ClearStr( svchf_vch_stno     );
    ClearStr( svchf_vch_opp_ind  );
    ClearStr( svchf_vch_opp_ac   );
    ClearStr( svchf_vch_part     );
    ClearStr( svchf_vch_part_b   );
    ClearStr( svchf_vch_m_ind    );
    ClearStr( svch_c_ind         );

    bpTraceLog( trdata, "¿ªÊ¼µ÷ÓÃRtyVchfToDbº¯Êý£¬½øÐÐµ¼ÈëÊý¾Ý.\n" );

    strcpy( sFilename, Step_Arg1 );

    fp = fopen( sFilename, "r" );
    if( fp == NULL ) {
      bpErrorLog( trdata, "RtyVchfToDb:´ò¿ªÊý¾ÝÎÄ¼þ¡¾%s¡¿Ê§°Ü!\n", sFilename );
      fclose( fp );
      return( -1 );
    }

    while ( !feof(fp) )
    {
      fscanf( fp, "%[^:]",   svchf_jrn_no        );
      fscanf( fp, ":%[^:]",  svchf_vch_seq       );
      fscanf( fp, ":%[^:]",  svchf_ap_code       );
      fscanf( fp, ":%[^:]",  svchf_ap_mmo        );
      fscanf( fp, ":%[^:]",  svchf_tr_code       );
      fscanf( fp, ":%[^:]",  svchf_tr_mmo        );
      fscanf( fp, ":%[^:]",  svchf_tr_date       );
      fscanf( fp, ":%[^:]",  svchf_tr_time       );
      fscanf( fp, ":%[^:]",  svchf_bk            );
      fscanf( fp, ":%[^:]",  svchf_br            );
      fscanf( fp, ":%[^:]",  svchf_dp            );
      fscanf( fp, ":%[^:]",  svchf_vch_no        );
      fscanf( fp, ":%[^:]",  svchf_tm_no         );
      fscanf( fp, ":%[^:]",  svchf_his_prt       );
      fscanf( fp, ":%[^:]",  svchf_reen_flag     );
      fscanf( fp, ":%[^:]",  svchf_vch_ec_ind    );
      fscanf( fp, ":%[^:]",  svchf_wff_flag      );
      fscanf( fp, ":%[^:]",  svchf_sup1_id       );
      fscanf( fp, ":%[^:]",  svchf_sup2_id       );
      fscanf( fp, ":%[^:]",  svchf_conf_id       );
      fscanf( fp, ":%[^:]",  svchf_vch_type      );
      fscanf( fp, ":%[^:]",  svchf_vch_confirm   );
      fscanf( fp, ":%[^:]",  svchf_vch_bk        );
      fscanf( fp, ":%[^:]",  svchf_vch_br        );
      fscanf( fp, ":%[^:]",  svchf_vch_ccy       );
      fscanf( fp, ":%[^:]",  svchf_vch_jj        );
      fscanf( fp, ":%[^:]",  svchf_vch_tt        );
      fscanf( fp, ":%[^:]",  svchf_vch_ac        );
      fscanf( fp, ":%[^:]",  svchf_vch_sign      );
      fscanf( fp, ":%[^:]",  svchf_vch_amt       );
      fscanf( fp, ":%[^:]",  svchf_vch_val_date  );
      fscanf( fp, ":%[^:]",  svchf_vch_stno_type );
      fscanf( fp, ":%[^:]",  svchf_vch_stno      );
      fscanf( fp, ":%[^:]",  svchf_vch_opp_ind   );
      fscanf( fp, ":%[^:]",  svchf_vch_opp_ac    );
      fscanf( fp, ":%[^:]",  svchf_vch_part      );
      fscanf( fp, ":%[^:]",  svchf_vch_part_b    );
      fscanf( fp, ":%[^:]",  svchf_vch_m_ind     );
      fscanf( fp, ":%[^\n]%\n", svch_c_ind          );

      EXEC SQL insert into rtytvchf (
                  vchf_jrn_no       ,
                  vchf_vch_seq      ,
                  vchf_ap_code      ,
                  vchf_ap_mmo       ,
                  vchf_tr_code      ,
                  vchf_tr_mmo       ,
                  vchf_tr_date      ,
                  vchf_tr_time      ,
                  vchf_bk           ,
                  vchf_br           ,
                  vchf_dp           ,
                  vchf_vch_no       ,
                  vchf_tm_no        ,
                  vchf_his_prt      ,
                  vchf_reen_flag    ,
                  vchf_vch_ec_ind   ,
                  vchf_wff_flag     ,
                  vchf_sup1_id      ,
                  vchf_sup2_id      ,
                  vchf_conf_id      ,
                  vchf_vch_type     ,
                  vchf_vch_confirm  ,
                  vchf_vch_bk       ,
                  vchf_vch_br       ,
                  vchf_vch_ccy      ,
                  vchf_vch_jj       ,
                  vchf_vch_tt       ,
                  vchf_vch_ac       ,
                  vchf_vch_sign     ,
                  vchf_vch_amt      ,
                  vchf_vch_val_date ,
                  vchf_vch_stno_type,
                  vchf_vch_stno     ,
                  vchf_vch_opp_ind  ,
                  vchf_vch_opp_ac   ,
                  vchf_vch_part     ,
                  vchf_vch_part_b   ,
                  vchf_vch_m_ind   ,
                  vch_c_ind )
              values(
                  :svchf_jrn_no       ,
                  :svchf_vch_seq      ,
                  :svchf_ap_code      ,
                  :svchf_ap_mmo       ,
                  :svchf_tr_code      ,
                  :svchf_tr_mmo       ,
                  :svchf_tr_date      ,
                  :svchf_tr_time      ,
                  :svchf_bk           ,
                  :svchf_br           ,
                  :svchf_dp           ,
                  :svchf_vch_no       ,
                  :svchf_tm_no        ,
                  :svchf_his_prt      ,
                  :svchf_reen_flag    ,
                  :svchf_vch_ec_ind   ,
                  :svchf_wff_flag     ,
                  :svchf_sup1_id      ,
                  :svchf_sup2_id      ,
                  :svchf_conf_id      ,
                  :svchf_vch_type     ,
                  :svchf_vch_confirm  ,
                  :svchf_vch_bk       ,
                  :svchf_vch_br       ,
                  :svchf_vch_ccy      ,
                  :svchf_vch_jj       ,
                  :svchf_vch_tt       ,
                  :svchf_vch_ac       ,
                  :svchf_vch_sign     ,
                  :svchf_vch_amt      ,
                  :svchf_vch_val_date ,
                  :svchf_vch_stno_type,
                  :svchf_vch_stno     ,
                  :svchf_vch_opp_ind  ,
                  :svchf_vch_opp_ac   ,
                  :svchf_vch_part     ,
                  :svchf_vch_part_b   ,
                  :svchf_vch_m_ind    ,
                  :svch_c_ind  );

      if( SQLCODE != SQL_SUCCESS )
      {
        bpErrorLog( trdata, "RtyVchfToDb:insert¡¾rtyvchf¡¿ÒÔÏÂ¼ÇÂ¼³ö´í,SQLCODE=¡¾%d¡¿!\n",SQLCODE );
        bpErrorLog( trdata, "svchf_jrn_no        =[%s]\n",svchf_jrn_no       );
        bpErrorLog( trdata, "svchf_vch_seq       =[%s]\n",svchf_vch_seq      );
        bpErrorLog( trdata, "svchf_ap_code       =[%s]\n",svchf_ap_code      );
        bpErrorLog( trdata, "svchf_ap_mmo        =[%s]\n",svchf_ap_mmo       );
        bpErrorLog( trdata, "svchf_tr_code       =[%s]\n",svchf_tr_code      );
        bpErrorLog( trdata, "svchf_tr_mmo        =[%s]\n",svchf_tr_mmo       );
        bpErrorLog( trdata, "svchf_tr_date       =[%s]\n",svchf_tr_date      );
        bpErrorLog( trdata, "svchf_tr_time       =[%s]\n",svchf_tr_time      );
        bpErrorLog( trdata, "svchf_bk            =[%s]\n",svchf_bk           );
        bpErrorLog( trdata, "svchf_br            =[%s]\n",svchf_br           );
        bpErrorLog( trdata, "svchf_dp            =[%s]\n",svchf_dp           );
        bpErrorLog( trdata, "svchf_vch_no        =[%s]\n",svchf_vch_no       );
        bpErrorLog( trdata, "svchf_tm_no         =[%s]\n",svchf_tm_no        );
        bpErrorLog( trdata, "svchf_his_prt       =[%s]\n",svchf_his_prt      );
        bpErrorLog( trdata, "svchf_reen_flag     =[%s]\n",svchf_reen_flag    );
        bpErrorLog( trdata, "svchf_vch_ec_ind    =[%s]\n",svchf_vch_ec_ind   );
        bpErrorLog( trdata, "svchf_wff_flag      =[%s]\n",svchf_wff_flag     );
        bpErrorLog( trdata, "svchf_sup1_id       =[%s]\n",svchf_sup1_id      );
        bpErrorLog( trdata, "svchf_sup2_id       =[%s]\n",svchf_sup2_id      );
        bpErrorLog( trdata, "svchf_conf_id       =[%s]\n",svchf_conf_id      );
        bpErrorLog( trdata, "svchf_vch_type      =[%s]\n",svchf_vch_type     );
        bpErrorLog( trdata, "svchf_vch_confirm   =[%s]\n",svchf_vch_confirm  );
        bpErrorLog( trdata, "svchf_vch_bk        =[%s]\n",svchf_vch_bk       );
        bpErrorLog( trdata, "svchf_vch_br        =[%s]\n",svchf_vch_br       );
        bpErrorLog( trdata, "svchf_vch_ccy       =[%s]\n",svchf_vch_ccy      );
        bpErrorLog( trdata, "svchf_vch_jj        =[%s]\n",svchf_vch_jj       );
        bpErrorLog( trdata, "svchf_vch_tt        =[%s]\n",svchf_vch_tt       );
        bpErrorLog( trdata, "svchf_vch_ac        =[%s]\n",svchf_vch_ac       );
        bpErrorLog( trdata, "svchf_vch_sign      =[%s]\n",svchf_vch_sign     );
        bpErrorLog( trdata, "svchf_vch_amt       =[%s]\n",svchf_vch_amt      );
        bpErrorLog( trdata, "svchf_vch_val_date  =[%s]\n",svchf_vch_val_date );
        bpErrorLog( trdata, "svchf_vch_stno_type =[%s]\n",svchf_vch_stno_type);
        bpErrorLog( trdata, "svchf_vch_stno      =[%s]\n",svchf_vch_stno     );
        bpErrorLog( trdata, "svchf_vch_opp_ind   =[%s]\n",svchf_vch_opp_ind  );
        bpErrorLog( trdata, "svchf_vch_opp_ac    =[%s]\n",svchf_vch_opp_ac   );
        bpErrorLog( trdata, "svchf_vch_part      =[%s]\n",svchf_vch_part     );
        bpErrorLog( trdata, "svchf_vch_part_b    =[%s]\n",svchf_vch_part_b   );
        bpErrorLog( trdata, "svchf_vch_m_ind     =[%s]\n",svchf_vch_m_ind    );
        bpErrorLog( trdata, "svch_c_ind          =[%s]\n",svch_c_ind         );
        fclose( fp );
        return( -1 );
      }
    }
    bpTraceLog( trdata, "½áÊøµ÷ÓÃRtyVchfToDbº¯Êý.\n" );
    fclose( fp );
    return( 0 );
}

/******************************************************************************
  Function          : RtyCdtmstToDb
  Description       : ½«»îÆÚÆÕÍ¨ÎÄ¼þÊý¾Ý²åÈëÊý¾Ý¿â±írtytvchf
  Input             : ETF *TrNode ÊäÈëÊ÷
                      ST_TranData* trdata ¹«¹²½á¹¹
                      char* args  ²ÎÊý
                      DBConHandle* DBHandle Êý¾Ý¿â¾ä±ú
  Output            : ¶ÔÊä³ö²ÎÊýµÄËµÃ÷¡£
  Return            : 0--³É¹¦ Ð¡ÓÚ0--Ê§°Ü
  Others            : ÆäËüËµÃ÷
******************************************************************************/
int RtyCdtmstToDb(ETF *TrNode, TranData *trdata, PbItemData args,  DBConHandle *DBHandle)
{
  EXEC SQL INCLUDE SQLCA;
  EXEC SQL BEGIN DECLARE SECTION;
    char  sac_no             [21+1];
    char  slast_dt           [8+1];
    char  slast_tlr          [7+1];
    char  stt_tmp            [3+1];
    char  sac_sts            [1+1];
    char  sac_name           [60+1];
    char  sopen_br           [6+1];
    char  sac_bk             [6+1];
    char  sac_stswrd         [30+1];
    char  sccy               [3+1];
    char  sccy_type          [1+1];
    char  sbal               [17+1];
    char  slast_bal          [17+1];
    char  saccu_date         [8+1];
    char  saccu              [19+1];
    char  sadp_accu          [19+1];
    char  sovr_accu          [19+1];
    char  sday_fbal          [17+1];
    char  sibp_fbal          [17+1];
    char  snday_fbal         [17+1];
    char  sadp_valdate       [8+1];
    char  sadp_bal           [17+1];
    char  sadp_int_code      [4+1];
    char  sadp_int_rate      [8+1];
    char  sibac_flag         [1+1];
    char  spay_type          [1+1];
    char  sint_method        [1+1];
    char  sfee_period        [1+1];
    char  scom_type          [2+1];
    char  sdep_type          [1+1];
    char  sfrg_code          [8+1];
    char  sfrg_kind          [3+1];
    char  scny_kind          [2+1];
    char  spage_flg          [1+1];
    char  slicense_expdate   [8+1];
    char  sac_expdate        [8+1];
    char  shold_cnt          [8+1];
    char  shold_amt          [17+1];
    char  stemp_hold_date    [8+1];
    char  stemp_hold_type    [1+1];
    char  stemp_code_amt     [17+1];
    char  sunint_amt         [17+1];
    char  sbud_int           [15+1];
    char  sint               [15+1];
    char  sovr_int           [15+1];
    char  slast_int_date     [8+1];
    char  slast_ovrint_date  [8+1];
    char  sint_date          [8+1];
    char  ssub_int_date      [8+1];
    char  ssub_adpint_date   [8+1];
    char  ssub_ovrint_date   [8+1];
    char  sint_code          [4+1];
    char  sint_rsel          [1+1];
    char  sint_rate          [8+1];
    char  sovr_int_code      [4+1];
    char  sovr_int_rate      [8+1];
    char  sovr_limit         [17+1];
    char  smax_ovrbal        [17+1];
    char  sovr_tt            [3+1];
    char  sovr_valdate       [8+1];
    char  sovr_expdate       [8+1];
    char  sfirst_ovrdate     [8+1];
    char  sovr_enddate       [8+1];
    char  sovr_flag          [1+1];
    char  sfeerate_flg       [1+1];
    char  sopen_date         [8+1];
    char  sdorm_type         [1+1];
    char  sdorm_date         [8+1];
    char  sln_cnt            [8+1];
    char  std_cnt            [8+1];
    char  sbe_cnt            [8+1];
    char  srm_cnt            [8+1];
    char  sdc_cnt            [8+1];
    char  sedi_cnt           [8+1];
    char  sgm_cnt            [8+1];
    char  sclose_br          [6+1];
    char  sclose_tlr         [7+1];
    char  sclose_date        [8+1];
    char  scp_flg            [1+1];
    char  tmpflg1            [20+1];
    char  tmpflg2            [20+1];
    char  tmpflg3            [20+1];
    char  tmpflg4            [20+1];
    char  tmpflg5            [20+1];
    char  tmpflg6            [20+1];
    char  tmpflg7            [20+1];
    char  tmpflg8            [20+1];
    char  tmpflg9            [20+1];
  EXEC SQL END DECLARE SECTION;

    FILE  *fp;
    char  sFilename[255];

    ClearStr( sac_no               );
    ClearStr( slast_dt             );
    ClearStr( slast_tlr            );
    ClearStr( stt_tmp              );
    ClearStr( sac_sts              );
    ClearStr( sac_name             );
    ClearStr( sopen_br             );
    ClearStr( sac_bk               );
    ClearStr( sac_stswrd           );
    ClearStr( sccy                 );
    ClearStr( sccy_type            );
    ClearStr( sbal                 );
    ClearStr( slast_bal            );
    ClearStr( saccu_date           );
    ClearStr( saccu                );
    ClearStr( sadp_accu            );
    ClearStr( sovr_accu            );
    ClearStr( sday_fbal            );
    ClearStr( sibp_fbal            );
    ClearStr( snday_fbal           );
    ClearStr( sadp_valdate         );
    ClearStr( sadp_bal             );
    ClearStr( sadp_int_code        );
    ClearStr( sadp_int_rate        );
    ClearStr( sibac_flag           );
    ClearStr( spay_type            );
    ClearStr( sint_method          );
    ClearStr( sfee_period          );
    ClearStr( scom_type            );
    ClearStr( sdep_type            );
    ClearStr( sfrg_code            );
    ClearStr( sfrg_kind            );
    ClearStr( scny_kind            );
    ClearStr( spage_flg            );
    ClearStr( slicense_expdate     );
    ClearStr( sac_expdate          );
    ClearStr( shold_cnt            );
    ClearStr( shold_amt            );
    ClearStr( stemp_hold_date      );
    ClearStr( stemp_hold_type      );
    ClearStr( stemp_code_amt       );
    ClearStr( sunint_amt           );
    ClearStr( sbud_int             );
    ClearStr( sint                 );
    ClearStr( sovr_int             );
    ClearStr( slast_int_date       );
    ClearStr( slast_ovrint_date    );
    ClearStr( sint_date            );
    ClearStr( ssub_int_date        );
    ClearStr( ssub_adpint_date     );
    ClearStr( ssub_ovrint_date     );
    ClearStr( sint_code            );
    ClearStr( sint_rsel            );
    ClearStr( sint_rate            );
    ClearStr( sovr_int_code        );
    ClearStr( sovr_int_rate        );
    ClearStr( sovr_limit           );
    ClearStr( smax_ovrbal          );
    ClearStr( sovr_tt              );
    ClearStr( sovr_valdate         );
    ClearStr( sovr_expdate         );
    ClearStr( sfirst_ovrdate       );
    ClearStr( sovr_enddate         );
    ClearStr( sovr_flag            );
    ClearStr( sfeerate_flg         );
    ClearStr( sopen_date           );
    ClearStr( sdorm_type           );
    ClearStr( sdorm_date           );
    ClearStr( sln_cnt              );
    ClearStr( std_cnt              );
    ClearStr( sbe_cnt              );
    ClearStr( srm_cnt              );
    ClearStr( sdc_cnt              );
    ClearStr( sedi_cnt             );
    ClearStr( sgm_cnt              );
    ClearStr( sclose_br            );
    ClearStr( sclose_tlr           );
    ClearStr( sclose_date          );
    ClearStr( scp_flg              );
    ClearStr( tmpflg1              );
    ClearStr( tmpflg2              );
    ClearStr( tmpflg3              );
    ClearStr( tmpflg4              );
    ClearStr( tmpflg5              );
    ClearStr( tmpflg6              );
    ClearStr( tmpflg7              );
    ClearStr( tmpflg8              );
    ClearStr( tmpflg9              );

    bpTraceLog( trdata, "¿ªÊ¼µ÷ÓÃRtyCdtmstToDbº¯Êý£¬½øÐÐµ¼ÈëÊý¾Ý.\n" );

    strcpy( sFilename, Step_Arg1 );

    fp = fopen( sFilename, "r" );
    if( fp == NULL ) {
      bpErrorLog( trdata, "RtyCdtmstToDb:´ò¿ªÊý¾ÝÎÄ¼þ¡¾%s¡¿Ê§°Ü!\n", sFilename );
      fclose( fp );
      return( -1 );
    }

    while ( !feof(fp) )
    {
      fscanf( fp, "%[^:]",  sac_no                );
      fscanf( fp, ":%[^:]", slast_dt              );
      fscanf( fp, ":%[^:]", slast_tlr             );
      fscanf( fp, ":%[^:]", stt_tmp               );
      fscanf( fp, ":%[^:]", sac_sts               );
      fscanf( fp, ":%[^:]", sac_name              );
      fscanf( fp, ":%[^:]", sopen_br              );
      fscanf( fp, ":%[^:]", sac_bk                );
      fscanf( fp, ":%[^:]", sac_stswrd            );
      fscanf( fp, ":%[^:]", sccy                  );
      fscanf( fp, ":%[^:]", sccy_type             );
      fscanf( fp, ":%[^:]", sbal                  );
      fscanf( fp, ":%[^:]", slast_bal             );
      fscanf( fp, ":%[^:]", saccu_date            );
      fscanf( fp, ":%[^:]", saccu                 );
      fscanf( fp, ":%[^:]", sadp_accu             );
      fscanf( fp, ":%[^:]", sovr_accu             );
      fscanf( fp, ":%[^:]", sday_fbal             );
      fscanf( fp, ":%[^:]", sibp_fbal             );
      fscanf( fp, ":%[^:]", snday_fbal            );
      fscanf( fp, ":%[^:]", sadp_valdate          );
      fscanf( fp, ":%[^:]", sadp_bal              );
      fscanf( fp, ":%[^:]", sadp_int_code         );
      fscanf( fp, ":%[^:]", sadp_int_rate         );
      fscanf( fp, ":%[^:]", sibac_flag            );
      fscanf( fp, ":%[^:]", spay_type             );
      fscanf( fp, ":%[^:]", sint_method           );
      fscanf( fp, ":%[^:]", sfee_period           );
      fscanf( fp, ":%[^:]", scom_type             );
      fscanf( fp, ":%[^:]", sdep_type             );
      fscanf( fp, ":%[^:]", sfrg_code             );
      fscanf( fp, ":%[^:]", sfrg_kind             );
      fscanf( fp, ":%[^:]", scny_kind             );
      fscanf( fp, ":%[^:]", spage_flg             );
      fscanf( fp, ":%[^:]", slicense_expdate      );
      fscanf( fp, ":%[^:]", sac_expdate           );
      fscanf( fp, ":%[^:]", shold_cnt             );
      fscanf( fp, ":%[^:]", shold_amt             );
      fscanf( fp, ":%[^:]", stemp_hold_date       );
      fscanf( fp, ":%[^:]", stemp_hold_type       );
      fscanf( fp, ":%[^:]", stemp_code_amt        );
      fscanf( fp, ":%[^:]", sunint_amt            );
      fscanf( fp, ":%[^:]", sbud_int              );
      fscanf( fp, ":%[^:]", sint                  );
      fscanf( fp, ":%[^:]", sovr_int              );
      fscanf( fp, ":%[^:]", slast_int_date        );
      fscanf( fp, ":%[^:]", slast_ovrint_date     );
      fscanf( fp, ":%[^:]", sint_date             );
      fscanf( fp, ":%[^:]", ssub_int_date         );
      fscanf( fp, ":%[^:]", ssub_adpint_date      );
      fscanf( fp, ":%[^:]", ssub_ovrint_date      );
      fscanf( fp, ":%[^:]", sint_code             );
      fscanf( fp, ":%[^:]", sint_rsel             );
      fscanf( fp, ":%[^:]", sint_rate             );
      fscanf( fp, ":%[^:]", sovr_int_code         );
      fscanf( fp, ":%[^:]", sovr_int_rate         );
      fscanf( fp, ":%[^:]", sovr_limit            );
      fscanf( fp, ":%[^:]", smax_ovrbal           );
      fscanf( fp, ":%[^:]", sovr_tt               );
      fscanf( fp, ":%[^:]", sovr_valdate          );
      fscanf( fp, ":%[^:]", sovr_expdate          );
      fscanf( fp, ":%[^:]", sfirst_ovrdate        );
      fscanf( fp, ":%[^:]", sovr_enddate          );
      fscanf( fp, ":%[^:]", sovr_flag             );
      fscanf( fp, ":%[^:]", sfeerate_flg          );
      fscanf( fp, ":%[^:]", sopen_date            );
      fscanf( fp, ":%[^:]", sdorm_type            );
      fscanf( fp, ":%[^:]", sdorm_date            );
      fscanf( fp, ":%[^:]", sln_cnt               ); 
      fscanf( fp, ":%[^:]", std_cnt               ); 
      fscanf( fp, ":%[^:]", sbe_cnt               ); 
      fscanf( fp, ":%[^:]", srm_cnt               ); 
      fscanf( fp, ":%[^:]", sdc_cnt               ); 
      fscanf( fp, ":%[^:]", sedi_cnt              ); 
      fscanf( fp, ":%[^:]", sgm_cnt               ); 
      fscanf( fp, ":%[^:]", sclose_br             ); 
      fscanf( fp, ":%[^:]", sclose_tlr            ); 
      fscanf( fp, ":%[^:]", sclose_date           );
      fscanf( fp, ":%[^:]", scp_flg               );
      fscanf( fp, ":%[^:]", tmpflg1               ); 
      fscanf( fp, ":%[^:]", tmpflg2               ); 
      fscanf( fp, ":%[^:]", tmpflg3               ); 
      fscanf( fp, ":%[^:]", tmpflg4               ); 
      fscanf( fp, ":%[^:]", tmpflg5               ); 
      fscanf( fp, ":%[^:]", tmpflg6               ); 
      fscanf( fp, ":%[^:]", tmpflg7               ); 
      fscanf( fp, ":%[^:]", tmpflg8               ); 
      fscanf( fp, ":%[^\n]%\n", tmpflg9           ); 
                                                                                                                                          
                            
      EXEC SQL insert into rtycdtmst (
            ac_no              ,     
            last_dt            ,      
            last_tlr           ,      
            tt_tmp             ,      
            ac_sts             ,      
            ac_name            ,      
            open_br            ,      
            ac_bk              ,      
            ac_stswrd          ,      
            ccy                ,      
            ccy_type           ,      
            bal                ,      
            last_bal           ,      
            accu_date          ,      
            accu               ,      
            adp_accu           ,      
            ovr_accu           ,      
            day_fbal           ,      
            ibp_fbal           ,      
            nday_fbal          ,      
            adp_valdate        ,      
            adp_bal            ,      
            adp_int_code       ,      
            adp_int_rate       ,      
            ibac_flag          ,      
            pay_type           ,      
            int_method         ,      
            fee_period         ,      
            com_type           ,      
            dep_type           ,      
            frg_code           ,      
            frg_kind           ,      
            cny_kind           ,      
            page_flg           ,      
            license_expdate    ,      
            ac_expdate         ,      
            hold_cnt           ,      
            hold_amt           ,      
            temp_hold_date     ,      
            temp_hold_type     ,      
            temp_code_amt      ,      
            unint_amt          ,      
            bud_int            ,      
            int                ,      
            ovr_int            ,      
            last_int_date      ,      
            last_ovrint_date   ,      
            int_date           ,      
            sub_int_date       ,      
            sub_adpint_date    ,      
            sub_ovrint_date    ,      
            int_code           ,      
            int_rsel           ,      
            int_rate           ,      
            ovr_int_code       ,      
            ovr_int_rate       ,      
            ovr_limit          ,      
            max_ovrbal         ,      
            ovr_tt             ,      
            ovr_valdate        ,      
            ovr_expdate        ,      
            first_ovrdate      ,      
            ovr_enddate        ,      
            ovr_flag           ,      
            feerate_flg        ,      
            open_date          ,      
            dorm_type          ,      
            dorm_date          ,      
            ln_cnt             ,      
            td_cnt             ,      
            be_cnt             ,      
            rm_cnt             ,      
            dc_cnt             ,      
            edi_cnt            ,      
            gm_cnt             ,      
            close_br           ,  
            close_tlr          ,  
            close_date         ,  
            cp_flg             )
          values(
            :sac_no            ,     
            :slast_dt          ,    
            :slast_tlr         ,    
            :stt_tmp           ,    
            :sac_sts           ,    
            :sac_name          ,    
            :sopen_br          ,    
            :sac_bk            ,    
            :sac_stswrd        ,    
            :sccy              ,    
            :sccy_type         ,    
            :sbal              ,    
            :slast_bal         ,    
            :saccu_date        ,    
            :saccu             ,    
            :sadp_accu         ,    
            :sovr_accu         ,    
            :sday_fbal         ,    
            :sibp_fbal         ,    
            :snday_fbal        ,    
            :sadp_valdate      ,    
            :sadp_bal          ,    
            :sadp_int_code     ,    
            :sadp_int_rate     ,    
            :sibac_flag        ,    
            :spay_type         ,    
            :sint_method       ,    
            :sfee_period       ,    
            :scom_type         ,    
            :sdep_type         ,    
            :sfrg_code         ,    
            :sfrg_kind         ,    
            :scny_kind         ,    
            :spage_flg         ,    
            :slicense_expdate  ,    
            :sac_expdate       ,    
            :shold_cnt         ,    
            :shold_amt         ,    
            :stemp_hold_date   ,    
            :stemp_hold_type   ,    
            :stemp_code_amt    ,    
            :sunint_amt        ,    
            :sbud_int          ,    
            :sint              ,    
            :sovr_int          ,    
            :slast_int_date    ,    
            :slast_ovrint_date ,    
            :sint_date         ,    
            :ssub_int_date     ,    
            :ssub_adpint_date  ,    
            :ssub_ovrint_date  ,    
            :sint_code         ,    
            :sint_rsel         ,    
            :sint_rate         ,    
            :sovr_int_code     ,    
            :sovr_int_rate     ,    
            :sovr_limit        ,    
            :smax_ovrbal       ,    
            :sovr_tt           ,    
            :sovr_valdate      ,    
            :sovr_expdate      ,    
            :sfirst_ovrdate    ,    
            :sovr_enddate      ,    
            :sovr_flag         ,    
            :sfeerate_flg      ,    
            :sopen_date        ,    
            :sdorm_type        ,    
            :sdorm_date        ,    
            :sln_cnt           ,    
            :std_cnt           ,    
            :sbe_cnt           ,    
            :srm_cnt           ,    
            :sdc_cnt           ,    
            :sedi_cnt          ,    
            :sgm_cnt           ,    
            :sclose_br         ,    
            :sclose_tlr        ,    
            :sclose_date       ,    
            :scp_flg           );                       
          
      if( SQLCODE != SQL_SUCCESS )
      {
        bpErrorLog( trdata, "RtyVchfToDb:insert¡¾rtycdtmst¡¿ÒÔÏÂ¼ÇÂ¼³ö´í,SQLCODE=¡¾%d¡¿!\n",SQLCODE );
        bpErrorLog( trdata, "sac_no            =[%s]\n",sac_no            );
        bpErrorLog( trdata, "slast_dt          =[%s]\n",slast_dt          );
        bpErrorLog( trdata, "slast_tlr         =[%s]\n",slast_tlr         );
        bpErrorLog( trdata, "stt_tmp           =[%s]\n",stt_tmp           );
        bpErrorLog( trdata, "sac_sts           =[%s]\n",sac_sts           );
        bpErrorLog( trdata, "sac_name          =[%s]\n",sac_name          );
        bpErrorLog( trdata, "sopen_br          =[%s]\n",sopen_br          );
        bpErrorLog( trdata, "sac_bk            =[%s]\n",sac_bk            );
        bpErrorLog( trdata, "sac_stswrd        =[%s]\n",sac_stswrd        );
        bpErrorLog( trdata, "sccy              =[%s]\n",sccy              );
        bpErrorLog( trdata, "sccy_type         =[%s]\n",sccy_type         );
        bpErrorLog( trdata, "sbal              =[%s]\n",sbal              );
        bpErrorLog( trdata, "slast_bal         =[%s]\n",slast_bal         );
        bpErrorLog( trdata, "saccu_date        =[%s]\n",saccu_date        );
        bpErrorLog( trdata, "saccu             =[%s]\n",saccu             );
        bpErrorLog( trdata, "sadp_accu         =[%s]\n",sadp_accu         );
        bpErrorLog( trdata, "sovr_accu         =[%s]\n",sovr_accu         );
        bpErrorLog( trdata, "sday_fbal         =[%s]\n",sday_fbal         );
        bpErrorLog( trdata, "sibp_fbal         =[%s]\n",sibp_fbal         );
        bpErrorLog( trdata, "snday_fbal        =[%s]\n",snday_fbal        );
        bpErrorLog( trdata, "sadp_valdate      =[%s]\n",sadp_valdate      );
        bpErrorLog( trdata, "sadp_bal          =[%s]\n",sadp_bal          );
        bpErrorLog( trdata, "sadp_int_code     =[%s]\n",sadp_int_code     );
        bpErrorLog( trdata, "sadp_int_rate     =[%s]\n",sadp_int_rate     );
        bpErrorLog( trdata, "sibac_flag        =[%s]\n",sibac_flag        );
        bpErrorLog( trdata, "spay_type         =[%s]\n",spay_type         );
        bpErrorLog( trdata, "sint_method       =[%s]\n",sint_method       );
        bpErrorLog( trdata, "sfee_period       =[%s]\n",sfee_period       );
        bpErrorLog( trdata, "scom_type         =[%s]\n",scom_type         );
        bpErrorLog( trdata, "sdep_type         =[%s]\n",sdep_type         );
        bpErrorLog( trdata, "sfrg_code         =[%s]\n",sfrg_code         );
        bpErrorLog( trdata, "sfrg_kind         =[%s]\n",sfrg_kind         );
        bpErrorLog( trdata, "scny_kind         =[%s]\n",scny_kind         );
        bpErrorLog( trdata, "spage_flg         =[%s]\n",spage_flg         );
        bpErrorLog( trdata, "slicense_expdate  =[%s]\n",slicense_expdate  );
        bpErrorLog( trdata, "sac_expdate       =[%s]\n",sac_expdate       );
        bpErrorLog( trdata, "shold_cnt         =[%s]\n",shold_cnt         );
        bpErrorLog( trdata, "shold_amt         =[%s]\n",shold_amt         );
        bpErrorLog( trdata, "stemp_hold_date   =[%s]\n",stemp_hold_date   );
        bpErrorLog( trdata, "stemp_hold_type   =[%s]\n",stemp_hold_type   );
        bpErrorLog( trdata, "stemp_code_amt    =[%s]\n",stemp_code_amt    );
        bpErrorLog( trdata, "sunint_amt        =[%s]\n",sunint_amt        );
        bpErrorLog( trdata, "sbud_int          =[%s]\n",sbud_int          );
        bpErrorLog( trdata, "sint              =[%s]\n",sint              );
        bpErrorLog( trdata, "sovr_int          =[%s]\n",sovr_int          );
        bpErrorLog( trdata, "slast_int_date    =[%s]\n",slast_int_date    );
        bpErrorLog( trdata, "slast_ovrint_date =[%s]\n",slast_ovrint_date );
        bpErrorLog( trdata, "sint_date         =[%s]\n",sint_date         );
        bpErrorLog( trdata, "ssub_int_date     =[%s]\n",ssub_int_date     );
        bpErrorLog( trdata, "ssub_adpint_date  =[%s]\n",ssub_adpint_date  );
        bpErrorLog( trdata, "ssub_ovrint_date  =[%s]\n",ssub_ovrint_date  );
        bpErrorLog( trdata, "sint_code         =[%s]\n",sint_code         );
        bpErrorLog( trdata, "sint_rsel         =[%s]\n",sint_rsel         );
        bpErrorLog( trdata, "sint_rate         =[%s]\n",sint_rate         );
        bpErrorLog( trdata, "sovr_int_code     =[%s]\n",sovr_int_code     );
        bpErrorLog( trdata, "sovr_int_rate     =[%s]\n",sovr_int_rate     );
        bpErrorLog( trdata, "sovr_limit        =[%s]\n",sovr_limit        );
        bpErrorLog( trdata, "smax_ovrbal       =[%s]\n",smax_ovrbal       );
        bpErrorLog( trdata, "sovr_tt           =[%s]\n",sovr_tt           );
        bpErrorLog( trdata, "sovr_valdate      =[%s]\n",sovr_valdate      );
        bpErrorLog( trdata, "sovr_expdate      =[%s]\n",sovr_expdate      );
        bpErrorLog( trdata, "sfirst_ovrdate    =[%s]\n",sfirst_ovrdate    );
        bpErrorLog( trdata, "sovr_enddate      =[%s]\n",sovr_enddate      );
        bpErrorLog( trdata, "sovr_flag         =[%s]\n",sovr_flag         );
        bpErrorLog( trdata, "sfeerate_flg      =[%s]\n",sfeerate_flg      );
        bpErrorLog( trdata, "sopen_date        =[%s]\n",sopen_date        );
        bpErrorLog( trdata, "sdorm_type        =[%s]\n",sdorm_type        );
        bpErrorLog( trdata, "sdorm_date        =[%s]\n",sdorm_date        );
        bpErrorLog( trdata, "sln_cnt           =[%s]\n",sln_cnt           );
        bpErrorLog( trdata, "std_cnt           =[%s]\n",std_cnt           );
        bpErrorLog( trdata, "sbe_cnt           =[%s]\n",sbe_cnt           );
        bpErrorLog( trdata, "srm_cnt           =[%s]\n",srm_cnt           );
        bpErrorLog( trdata, "sdc_cnt           =[%s]\n",sdc_cnt           );
        bpErrorLog( trdata, "sedi_cnt          =[%s]\n",sedi_cnt          ); 
        bpErrorLog( trdata, "sgm_cnt           =[%s]\n",sgm_cnt           ); 
        bpErrorLog( trdata, "sclose_br         =[%s]\n",sclose_br         ); 
        bpErrorLog( trdata, "sclose_tlr        =[%s]\n",sclose_tlr        ); 
        bpErrorLog( trdata, "sclose_date       =[%s]\n",sclose_date       ); 
        bpErrorLog( trdata, "scp_flg           =[%s]\n",scp_flg           );
        bpErrorLog( trdata, "tmpflg1           =[%s]\n",tmpflg1           ); 
        bpErrorLog( trdata, "tmpflg2           =[%s]\n",tmpflg2           );
        bpErrorLog( trdata, "tmpflg3           =[%s]\n",tmpflg3           );
        bpErrorLog( trdata, "tmpflg4           =[%s]\n",tmpflg4           );
        bpErrorLog( trdata, "tmpflg5           =[%s]\n",tmpflg5           );
        bpErrorLog( trdata, "tmpflg6           =[%s]\n",tmpflg6           );
        bpErrorLog( trdata, "tmpflg7           =[%s]\n",tmpflg7           );
        bpErrorLog( trdata, "tmpflg8           =[%s]\n",tmpflg8           );
        bpErrorLog( trdata, "tmpflg9           =[%s]\n",tmpflg9           ); 
        fclose( fp );                            
        return( -1 );                            
      }                                          
    }                                            
    bpTraceLog( trdata, "½áÊøµ÷ÓÃRtyCdtmstToDbº¯Êý.\n" );
    fclose( fp );                                
    return( 0 );
}






























