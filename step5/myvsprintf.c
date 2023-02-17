#include <mylib.h> //  strlen, memchr, AtoI functions are defined

char pbuf[256] ;  //   Print Buffer in which all %? are converted to strings

void print_ap(const char *msg, va_list ap){
    printf("%s : %p\n", msg, ap);
}

int myvprintf(char *pbuf, const char *format, va_list ap){

    int format_len = strlen(format) ;
    int i, pbuf_i = 0; 
    char *str_s, len_s ;

    for ( i = 0 ; i < format_len ; i++){
        if (format[i] == '%'){
        // Do % handling routine ;
        // move to next char of %
            i++;
            switch(format[i]){
                case 's':
                    // copy argument string to print buffer
                    print_ap("before string : ", ap);
                    str_s = (char *)(va_arg(ap, char *)) ;
                    print_ap("after  string : ", ap);
                    len_s = strlen(str_s);
                    while(len_s--)
                        pbuf[pbuf_i++] = *str_s++ ;
                    break ;
                case 'c':
                    print_ap("before char : ", ap);
                    pbuf[pbuf_i++] = (char)(va_arg(ap, int)) ;
                    print_ap("after char : ", ap);
                    break ; 
                case 'd':
                    print_ap("before decimal : ", ap);
                    pbuf_i += ItoA(va_arg(ap,int), pbuf+pbuf_i, 10);
                    print_ap("after  decimal : ", ap);
                    break ;
                case 'x':
                    print_ap("before hexdecimal : ", ap);
                    pbuf_i += ItoA(va_arg(ap,int), pbuf+pbuf_i, 16);
                    print_ap("after  hexdecimal : ", ap);
                    break ;
                case 'b':
                    print_ap("before binary : ", ap);
                    pbuf_i += ItoA(va_arg(ap,int), pbuf+pbuf_i, 2);
                    print_ap("after  binary : ", ap);
                    break ;
                case 'o':
                    print_ap("before octal : ", ap);
                    pbuf_i += ItoA(va_arg(ap,int), pbuf+pbuf_i, 8);
                    print_ap("after octal : ", ap);
                    break ;
            }
        }
        else{
        // Do copying the format[i] character to prt buffer
            pbuf[pbuf_i++] = format[i] ;
        }
    }
    // Add Null Character to make a perfect string, and return converted length
    pbuf[pbuf_i] = '\0' ;
    return pbuf_i ;
}


#define _INTSIZEOF(n) ((sizeof(n))+sizeof(int)-1) & ~(sizeof(int)-1)

int myprintf(const char *format, ...)
{
    int len ;
    va_list ap;

    va_start(ap, format);
    printf("_ADDR format is %p, _INTSIZE of format is %lu \n", &format, _INTSIZEOF(format));
    print_ap("start at ap", ap);

    len = myvprintf(pbuf, format, ap) ; // rc is a length of filled buff

    va_end(ap);

    //puts(pbuf) ;
    printf("%s",pbuf) ;

    return len ;
}
