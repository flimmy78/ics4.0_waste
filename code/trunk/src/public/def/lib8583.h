/*
 * History: Date	Position	Author		Action
 * ----------------------------------------------------------------------------
 * 	    2001-02-01	ShenZhen	liangwj		Create
 ******************************************************************************/
#ifndef    _LIB_8583_H_
#define    _LIB_8583_H_

#define    DP_FAIL    -1
#define    DP_SUCC    0 

#define			ETF_NAME_LEN		512							/* etf������󳤶� */
#define     FIELD_MAXLEN    1000            /* 8583��������    */
#define     FIELD_NUM        128            /* 8583������   */
#define     FIELD_EXIST     0x01            /* BitMap�д��� */
#define     FIELD_NoEXIST   0x00            /* BitMap�в����� */

#define     BITMAP_EXPEND   2               /* BitMap������չ*/
#define     BITMAP_NoEXPEND 1               /* BitMap������չ*/

/*  LenType */
#define     ConstLen        0               /* �̶���       */
#define     VarLen2         2               /* 2BCD�䳤     */
#define     VarLen3         3               /* 3BCD�䳤     */

/*  DataType */
#define     NumAsciiType    0               /* ������ASCII��*/
#define	    CharAsciiType   1               /* �ַ���ASCII��*/
#define     BitType         2               /* Bit λ��     */
#define     NumBCDType      3               /* ����BCD      */
#define     ASCBCDType      4               /* �ַ�BCD      */

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
{                               /*  8583����Ľṹ                  */
    int     ID;                 /*  8583 �ؼ�����                   */
    int     Len;                /*  ��������ݳ���                  */
    char    *Data;              /*  �������������                  */ 
    struct  _iso8583_ *Next;      /*  ��ָ��                          */
} ISO8583;

#ifdef _LIB_8583_
#define EXTERN 
#else
#define EXTERN extern
#endif 
/*
 * ���ܣ�ͨ��xml�����ļ���ʼ��������Ϣ
 */
EXTERN int 	init8583FromXml(char * filename, Field8583 * field8583);

/**
 * ����: ȡISO8583�������������8583����
 */
EXTERN int packetTo8583(Field8583 * field8583, ISO8583 * p8583, char ** out_data, int * out_data_len);

/**
 * ����: ��8583���Ľ����ISO8583������
 */
EXTERN int unpacketFrom8583(Field8583 * field8583, char * in_data, ISO8583 * p8583);

#undef EXTERN
#endif /*_LIB_8583_H_*/
