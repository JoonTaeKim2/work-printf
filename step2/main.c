#include <stdio.h>
#include <stdarg.h>

size_t strlen (const char *str)
{
    int len ; 

    const char *sptr = str ;

    while (*sptr)
        sptr++ ;

    len = sptr - str ;
    
    return len ;
}


// find the address in the memory pointed by ptr
// whose content is equal to value within n bytes
void *memchr(const void *ptr, int value, size_t num)
{
    const unsigned char *src = (const void *)ptr ;

    value &= 0xff ; // only consider a byte data

    while (num--){
        if ( *src == value )
            return (void *)src ;
        src++;
    }
    return NULL ;
}


int main(void)
{
    const char msg[] = "hello world" ;
    void *ptr ;

    printf("message length : %d\n",(int)strlen(msg));

    ptr = memchr(msg, 'r', strlen(msg)) ;

    printf("w is n %d'th value in a message\n",(int)(ptr-(void *)msg+1));

    return  0 ;
}

