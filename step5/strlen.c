#include <mylib.h>

size_t strlen (const char *str)
{
    int len ; 

    const char *sptr = str ;

    while (*sptr)
        sptr++ ;

    len = sptr - str ;
    
    return len ;
}

