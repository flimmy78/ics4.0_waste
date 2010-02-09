
void Str2CStr(char *str, char *cstr)
{
    unsigned char c;
    int i,j;

    i = 0;
    j = 0;
    while( str[i]!='\0' )
    {
        c = str[i];
        if ( c >= 0x80 ) {  /*** c>=128 ***/
            c = str[i+1];
            if ( c >=0x80 ) { /*** CHINESE ***/
                cstr[j]=str[i];
                cstr[j+1]=str[i+1];
                i+=2;
                j+=2;
                continue;
            } else {
                cstr[j]=str[i];
                i++;
                j++;
                continue;
            }
        }
        if ( c<0x20 || c==0x7f ) {
            cstr[j]=str[i];
            i++;
            j++;
            continue;
         }
         switch (c)
         {
             case ' ':
                 cstr[j] = 0xa1;
                 cstr[j+1] = 0xa1;
                 break;
             case '$':
                 cstr[j] = 0xa1;
                 cstr[j+1] = 0xe7;
                 break;
             case '~':
                 cstr[j] = 0xa1;
                 cstr[j+1] = 0xab;
                 break;
             default:
                 cstr[j] = 0xa3;
                 cstr[j+1] = c+0x80;
                 break;
         }
         i++;
         j+=2;
    }
    cstr[j]='\0';
}

void CStr2Str(char *cstr, char *str)
{
    int i,j;
    unsigned char c,d;

    i = 0;
    j = 0;
    while ( cstr[i] !='\0' )
    {
        c = cstr[i];
        if ( c<0x80 ) {  /*** NOT CHINESE ***/
            str[j]=cstr[i];
            i++;
            j++;
            continue;
        }
        d = cstr[ i+1 ];
        if ( d<0x80 ) {  /*** NOT CHINESE ***/
            str[j]=cstr[i];
            i++;
            j++;
            continue;
        }
        if ( c == 0xa1 && d == 0xa1 ) {
            str[j] = ' ';
            i+=2;
            j++;
            continue;
        }
        if ( c == 0xa1 && d == 0xe7 ) {
            str[j] = '$';
            i+=2;
            j++;
            continue;
        }
        if ( c == 0xa1 && d == 0xab ) {
            str[j]='~';
            i+=2;
            j++;
            continue;
        }
        if ( c != 0xa3 ) {
            str[j] = c;
            str[j+1] = d;
            i+=2;
            j+=2;
            continue;
        }
        if ( d <0xa1 || d>0xfd || d==0xa4) {
            str[j] = c;
            str[j+1] = d;
            i+=2;
            j+=2;
            continue;
        }
        str[j] = d-0x80;
        i+=2;
        j++;
    }
    str[j]='\0';
}

int TruncCStr( char * cstr, int len )
{
    int i,j;
    unsigned char c,d;

    if ( cstr == (void *) 0 ) return 0;

    if ( len <=0 ) {
        cstr[0]='\0';
        return 0;
    }

    i = 0;
    while ( cstr[i]!='\0' ) {
        c = cstr[i];
        d = cstr[i+1];
        if ( c<0x80 || d<0x80) j = 1;
            else j = 2;
        if ( i+j > len ) {
            cstr[i]='\0';
            return i;
        }
        i += j;
    }
    return i-1;
}

int CheckCStr( char * str )
{
    int i,len;

    len = strlen(str);
    i = 0;
    if (len % 2 != 0 )
        return -1;

    while ( i<len ) {
        if ( (str[i] & 0x80) == 0 )
            return -1;
        i++;
    }
    return 0;
}
