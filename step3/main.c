// ItoA function converts decimal value to a string
// Radix determines the representation format
// ex: ItoA(16, str, 10) => '1''6''\0'
//     ItoA(16, str, 16) => '0''x''1''0''\0'

// buffer is a temporary memory that stores 
// the converted ascii scring of decimal number
#include <stdio.h>

#define BUFSIZE 10
char buffer[BUFSIZE] ;

extern size_t strlen(const char *str) ;
void flipstr(char *str) ;

const char hex[] = "0123456789abcdef" ;
int ItoA(int ivalue, char *buffer, int radix)
{
    int count, i;
    unsigned int uivalue ;

    uivalue = ivalue ;

    //printf("uivalue : %x, ivalue : %x \n", uivalue, ivalue);

    switch(radix){
        case 2:
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

int main(void){
    int x = 135 ;
    int y = -257 ;
    int len ; 

    len = ItoA(x, buffer, 10);
    printf("%d value is %s\n", x, buffer);
    len = ItoA(y, buffer, 10);
    printf("%d value is %s\n", y, buffer);

    len = ItoA(x, buffer, 16);
    printf("%x value is %s\n", x, buffer);
    len = ItoA(y, buffer, 16);
    printf("%x value is %s\n", y, buffer);

    len = ItoA(x, buffer, 2);
    printf("%x value is %s\n", x, buffer);
    len = ItoA(y, buffer, 2);
    printf("%x value is %s\n", y, buffer);

    //printf("-135 is %x, 257 is %lx address of x is %p\n", x, &y, &x);
    return 0 ;
}
