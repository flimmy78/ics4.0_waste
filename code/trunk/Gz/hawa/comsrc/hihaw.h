#define   FmpSrcLen   22   /*加密前数据*/
#define   FmpValLen   32   /*加密后数据*/
#define   MaxLen       8   /*序号数据*/

#define   MaxMsgLen 8192   /*最大数据长度*/
#define   HexDatLen    4   /*十六进制数据长度*/
#define   DecDatLen    8   /*十进制数据长度*/
#define   StatusLen    2   /*十六状态域长度（一位变两位）*/

#define   TComCdLen    6   /*交易码长度*/
#define   PrvFrmLen   20   /*个人表号长度*/
#define   TCrpCdLen   50   /*组织机构代码长度*/
#define   RecNumLen    5   /*循环笔数长度*/

#define   TotLenOffSet   0
#define   ComIdOffSet    TotLenOffSet+HexDatLen
#define   SeqIdOffSet    ComIdOffSet+HexDatLen
#define   StatusOffSet   SeqIdOffSet+HexDatLen

#define   TotLenLen    4   /*报文总长度*/
#define   ComIdLen     4   /*响应类型*/
#define   SeqIdLen     4   /*消息流水号*/
