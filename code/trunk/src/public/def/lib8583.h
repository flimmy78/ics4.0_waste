/*
 * History: Date	Position	Author		Action
 * ----------------------------------------------------------------------------
 * 	    2001-02-01	ShenZhen	liangwj		Create
 ******************************************************************************/
#ifndef    _LIB_8583_H_
#define    _LIB_8583_H_

#define    DP_FAIL    -1
#define    DP_SUCC    0 

#define			ETF_NAME_LEN		512							/* etf名字最大长度 */
#define     FIELD_MAXLEN    1000            /* 8583各域的最大长    */
#define     FIELD_NUM        128            /* 8583域行数   */
#define     FIELD_EXIST     0x01            /* BitMap中存在 */
#define     FIELD_NoEXIST   0x00            /* BitMap中不存在 */

#define     BITMAP_EXPEND   2               /* BitMap包括扩展*/
#define     BITMAP_NoEXPEND 1               /* BitMap不含扩展*/

/*  LenType */
#define     ConstLen        0               /* 固定长       */
#define     VarLen2         2               /* 2BCD变长     */
#define     VarLen3         3               /* 3BCD变长     */

/*  DataType */
#define     NumAsciiType    0               /* 数字型ASCII码*/
#define	    CharAsciiType   1               /* 字符型ASCII码*/
#define     BitType         2               /* Bit 位段     */
#define     NumBCDType      3               /* 数字BCD      */
#define     ASCBCDType      4               /* 字符BCD      */

#define     SetBit( c, n )  ( c | (0x01 << (7-n) ) )
#define     GetBit( c, n )  ( ( c >> (7-n) ) & 0x01 )
#define     ClrBit( c, n )  ( c & (0x00 << (7-n) ) ) 

#define	HEX_TO_ASCII hhextoasc;
#define	ASCII_TO_HEX hasctohex;

typedef struct  _field8583_
{
        int			nFieldID;
        char		etfName[ETF_NAME_LEN];
        int     nLenType;
        int     nDataType;
        int     nDataLen;
} Field8583;

typedef struct _iso8583_
{                               /*  8583链表的结构                  */
    int     ID;                 /*  8583 关键字域                   */
    int     Len;                /*  该域的数据长度                  */
    char    *Data;              /*  该域的数据内容                  */ 
    struct  _iso8583_ *Next;      /*  链指针                          */
} ISO8583;

#ifdef _LIB_8583_
#define EXTERN 
#else
#define EXTERN extern
#endif 
/*
 * 功能：通过xml配置文件初始化各域信息
 */
EXTERN int 	init8583FromXml(char * filename, Field8583 * field8583);

/**
 * 功能: 取ISO8583链表数据中组成8583报文
 */
EXTERN int packetTo8583(Field8583 * field8583, ISO8583 * p8583, char ** out_data, int * out_data_len);

/**
 * 功能: 把8583报文解包到ISO8583链表中
 */
EXTERN int unpacketFrom8583(Field8583 * field8583, char * in_data, ISO8583 * p8583);

#undef EXTERN
#endif /*_LIB_8583_H_*/
