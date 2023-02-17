#include <stdio.h>

extern int myprintf(const char *format, ...);
extern void UART_Init(void) ;

int main(int argc, char *argv[])
{
    UART_Init() ;

    char ch = '!' ;
    int data = 52 ;
    char *str = "world" ;

    myprintf("This is %s text\n","sample");
    myprintf("Integer data : %d %x\n", data, data);
    myprintf("Hello %s %c\n",str, ch);
    myprintf("pointer value of str is  %p \n",str);
    myprintf("int size : %d, long size : %d, char size : %d\n",sizeof(int), sizeof(long), sizeof(char));

    while(1) ;

    return 0 ;
}
