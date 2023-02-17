#include <mylib.h>

int main(void)
{
    char str[] = "hello world\n";
    int  x = -157 ;
    myprintf("%s", str);
    myprintf("%c %c %c %d %x %b   %o\n",'A','B','C', x, x, x, x);

    return 0;
}
