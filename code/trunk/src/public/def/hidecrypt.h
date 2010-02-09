#ifndef _HIDECRYPT_H_
#define _HIDECRYPT_H_

#include <stdio.h>
#include <stdlib.h>

#define DEST_MAX_LEN 1024

/*
 * added by kixiong at 10/17/2007 5:08PM
*/
char *hdecrypt(char *);
char *hdecrypt_t(char *);
char *hencrypt(char *);
char *hencrypt_t(char *);


#endif /* _HIDECRYPT_H_ */
