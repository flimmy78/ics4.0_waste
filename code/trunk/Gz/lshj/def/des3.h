/*
 *	Copyright (C) 2000-2001 Chen WeiYu GuangZhou China
 *	All Rights Reserved.
 *
 *  This file contains proprietary information of Chen WeiYu.
 *  Copying or reproduction without prior written approval is prohibited.
 *
 *  This software is commercial computer software, protected by the law 
 *  toghter with any related documentation.
 *
 *  This copyrighted software is licensed only for use in strict accordance 
 *  with the Software License Agreement, which should be read carefully 
 *  before commencing use of the software.
 *
 *  Version    :  V1.0
 *  Author     :  Chen Weiyu
 *  File name  :  des.h
 *  Description:  define DES encrypt/decrypt, 3DES encrypt/decrypt
 *                and signature/verify signature
*/

#ifndef __DES_H
#define __DES_H

#include	<string.h>

typedef struct Dea
{
	unsigned char data[8];		/*  Data area to be encrypted/decrypted */
	unsigned char key[8];		/*  Key Identification */
	unsigned char perData[8];	/*  Permutation Area */
	unsigned char temp[8];		/*  Temporary storage area */
} DEA, *LPDEA;

/*
    DES/3DES Manipulation Function Prototypes
*/

#ifdef _KRC_
extern int desEncrypt(  );
extern int desDecrypt(  );
extern int des3Encrypt(  );
extern int des3Decrypt(  );
extern int desSign(  );
extern int desVerifySign(  );
extern int des3Sign( );
extern int des3VerifySign(  );
extern int desVectorSign(  );
extern int desVectorVerifySign( );
extern int des3VectorSign( );
extern int des3VectorVerifySign(  );

#else
extern int desEncrypt( char *pdes, char *psrc, int src_len, char *pkey,
                       int key_len );
extern int desDecrypt( char *pdes, char *psrc, int src_len, char *pkey,
                       int key_len );
extern int des3Encrypt( char *pdes, char *psrc, int src_len, char *pkey,
                        int key_len );
extern int des3Decrypt( char *pdes, char *psrc, int src_len, char *pkey,
                        int key_len );
extern int desSign( char *sign, char *psrc, int src_len, char *pkey,
                    int key_len );
extern int desVerifySign( char *sign, char *psrc, int src_len, char *pkey,
                          int key_len, char *pdes, int des_len );
extern int des3Sign( char *sign, char *psrc, int src_len, char *pkey,
                     int key_len );
extern int des3VerifySign( char *sign, char *psrc, int src_len, char *pkey,
                           int key_len, char *des, int des_len );
extern int desVectorSign( char *sign, char *psrc, int src_len, char *random,
                          char *pkey, int key_len );
extern int desVectorVerifySign( char *sign, char *psrc, int src_len,
                                char *random, char *pkey, int key_len,
                                char *des, int des_len );
extern int des3VectorSign( char *sign, char *psrc, int src_len, char *random,
                           char *pkey, int key_len );
extern int des3VectorVerifySign( char *sign, char *psrc, int src_len,
                                 char *random, char *pkey, int key_len,
                                 char *des, int des_len );

#endif

#endif	/* __DES_H */

