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


//  variable arguments list 
int sum(int count, ...){
    int res = 0 ;

    va_list ap ;
    int i ;

    va_start(ap, count);

    for ( i = 0 ; i < count ; i++)
        res += va_arg(ap, int);

    va_end(ap);

    return res ;
}

// Another example of variable arguments
void print_dcs(char *dcs, ...)
{
	va_list ap;    //가변 인자 목록을 ap에 담을 것이다.
    size_t i = 0;

    va_start(ap, dcs);	//dcs라는 문자열의 개수 만큼 ap가 이동할 것.
    while (dcs[i] != '\0')
    {
    	if (dcs[i] == 'd')
        	printf("%d ", va_arg(ap, int));
        if (dcs[i] == 'c')
        	printf("%c ", (char)va_arg(ap, int));
        if  (dcs[i] == 's')
        	printf("%s ", va_arg(ap, char *));
        i++;
    }
    va_end(ap);     //ap가 NULL을 가리키도록 만든다.
                    //end는 안정성을 위해 써주도록 한다.
    printf("\n");
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
    return  0 ;
}

