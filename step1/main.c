#include <stdio.h>

size_t strlen (const char *str)
{
    int len ; 

    const char *sptr = str ;

    while (*sptr)
        sptr++ ;

    len = sptr - str ;
    
    return len ;
}


int main(void)
{
    const char msg[] = "hello world" ;

    printf("message length : %d\n",(int)strlen(msg));

    return  0 ;
}

