#ifndef _LIBHIDES_H_
#define _LIBHIDES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _D3DES_H_
#define _D3DES_H_
#include "d3des.h"
#endif

int des_decryption(unsigned char *szIn, int nInlen, unsigned char * key, int type);

#endif
