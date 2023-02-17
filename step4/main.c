#include <stdio.h>
#include <stdarg.h>

#define _INTSIZEOF(n) ((sizeof(n))+sizeof(int)-1) & ~(sizeof(int)-1)

void print_ap(const char *msg, va_list ap){
    printf("%s : %p\n", msg, ap);
}

//  variable arguments list 
int sum(int count, ...){
    int res = 0 ;

    va_list ap ;
    int i, tmp ;

    va_start(ap, count);
    printf("First Argument Address : %p, ap Address : %p, int_size of count%ld\n", &count, ap, _INTSIZEOF(count));

/*
    for ( i = 0 ; i < count ; i++){
        res += va_arg(ap, int);
        print_ap("current ap : ", ap);
    }
*/
    for(;;){
        tmp = va_arg(ap, int);
        if(tmp == 0)
            break ;
        res += tmp ;
    }

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

    printf("%d\n", sum(10, 1,2,3,4,5,6,7,8,9,10));

    // Test 2nd va_list example
    print_dcs("d",10);
    print_dcs("dc",10,'a');
    print_dcs("dcs",10,'a',"Hello World");
    return  0 ;
}

