#include <stdio.h> 
#include <string.h> 

int main(int argc,char **argv) 
{ 
    char *haystack="aaa||a||bbb||c||ee||"; 
    char *needle="||"; 
    char* buf = strstr( haystack, needle); 
    while( buf != NULL ) 
    { 
        buf[0]='\0'; 
        printf( "%s\n ", haystack); 
        haystack = buf + strlen(needle); 
        /* Get next token: */ 
        buf = strstr( haystack, needle); 
    } 
    return 0;
}
