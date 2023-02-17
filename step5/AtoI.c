// ItoA function converts decimal value to a string
// Radix determines the representation format
// ex: ItoA(16, str, 10) => '1''6''\0'
//     ItoA(16, str, 16) => '0''x''1''0''\0'

// buffer is a temporary memory that stores 
// the converted ascii scring of decimal number
#include <mylib.h>

//#define BUFSIZE 10
//char buffer[BUFSIZE] ;

const char hex[] = "0123456789abcdef" ;
int ItoA(int ivalue, char *buffer, int radix)
{
    int i = 0;
    unsigned int uivalue ;

    uivalue = ivalue ;

    //printf("uivalue : %x, ivalue : %x \n", uivalue, ivalue);

    switch(radix){
        case 2:
        case 8:
        case 16:
        /*
            buffer[0] = '0' ;
            buffer[1] = 'x' ;
            i = 2 ;
        */
            i = 0 ; 

            for (; uivalue ; i++){
                buffer[i] = hex[uivalue % radix] ;
                uivalue /= radix ;
            }
            /*
            for (; uivalue > 0; i++){
                buffer[i] = hex[uivalue & 0x0F] ;
                uivalue >>= 4 ;
            }*/

            buffer[i]='\0';
            flipstr(buffer) ;
            break ;

        case 10:
            if ( ivalue == 0){
                buffer[0] = '0' ;
                buffer[1] = '\0';
                return 1 ;
            }
            // check negative or positive
            if ( ivalue < 0){
                buffer[0] = '-';
                ivalue = -ivalue ;
                i = 1 ;
            }
            else{
                i = 0 ;
            }

            for ( ; ivalue > 0 ; i++){
                buffer[i] = '0' + ivalue % 10 ;
                ivalue /= 10 ;
            }
            buffer[i] = '\0';

            // now we reorder the buffer contents in reverse
            if (buffer[0] == '-')
                flipstr(&buffer[1]) ;
            else
                flipstr(buffer) ;
    }
    return i ;
}

void flipstr(char *str)
{
    int i, len ;
    char ctmp ;

    len = (int)strlen(str) ;
    for ( i = 0 ; i  < len / 2 ; i++){
        ctmp = str[i] ;
        str[i] = str[len-1-i];
        str[len-1-i] = ctmp ;
    }
}

