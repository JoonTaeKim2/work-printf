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


char prt_buf[256] ; // sufficient memory for printing 1 line

int myprintf(const char *format, ...)
{
    int rc ;
    va_list ap;

    va_start(ap, format);

    rc = vprintf(prt_buf, format, ap) ; // rc is a length of filled buff

    va_end(ap);

    puts(prt_buf) ;

    return rc ; 
}


int main(void)
{
    const char msg[] = "hello world" ;
    void *ptr ;

    printf("message length : %d\n",(int)strlen(msg));

    ptr = memchr(msg, 'r', strlen(msg)) ;

    printf("w is n %d'th value in a message\n",(int)(ptr-(void *)msg+1));

    printf("%d\n", sum(10, 1,2,3,4,5,6,7,8,9,10));

    // Test 2nd va_list example
    print_dcs("d",10);
    print_dcs("dc",10,'a');
    print_dcs("dcs",10,'a',"Hello World");

    myprintf("my name is %s\n", "jtkim");
    myprintf("my age is %d\n", 55);
    myprintf("my blood type  is %c\n", 'B');

    return  0 ;
}

