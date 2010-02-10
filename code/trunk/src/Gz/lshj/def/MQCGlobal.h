
#include "mqcclient.h"

#define false 0
#define true 1

int getAttributeStringValue( char* srcStr, char* strName, char* buf, int len );
int getAttributeIntValue( char* srcStr, char* strName );
char* findSubString( char* srcStr, char* subStr, int beginPos );
int _stdDes3Decrypt( char *pdes, char *psrc, int src_len, char *pkey, int key_len);
int _stdDes3Encrypt( char *pdes, char *psrc, int src_len, char *pkey, int key_len);
int _stdDesDecrypt( char *pdes, char *psrc, int src_len, char *pkey, int key_len);
int _stdDesEncrypt( char *pdes, char *psrc, int src_len, char *pkey, int key_len);
int checkReadSocketReturnCode( int iRead, int iPredictRead );
int checkSendSocketReturnCode( int iSend, int iPredictSend );
int closeSocket(int* socketID);

char* _compress(char* in, int lenIn, char** ppOut, int* pLenOut );
char* _decompress(char* in, int lenIn, char** ppOut, int* pLenOut );
void  _cryptDES(char *in, char *userkey, int encrypt, int len );
int recvn( int fd, char* vptr, int n, int flags );
int sendn( int fd, char* vptr, int n, int flags );
uint32 _getCRC32(char *p, uint32 len);
void  _cryptDES(char *in, char *userkey, int encrypt, int len );
void aaDecode( char* pSource, char* pEncode, int iEncodeLen );
void aaEncode( char* pEncode, char* pSource, int iSourceLen );
void cleanUp();
void startUp();
int printSocketError( char* pStr );
void changeToNetByteOrder_MQMessage(_MQMessage* _this );
void changeToNetByteOrder_MQMsgHead(_MQMsgHead* _this );
char* _compress(char* in, int lenIn, char** ppOut, int* pLenOut );
char* _decompress(char* in, int lenIn, char** ppOut, int* pLenOut );

char* getMQErrDescription( int errCode );

