#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
 
#define UART_BUF_SIZE   256
 
char uart_buf[UART_BUF_SIZE];
 
 
#define to_digit(c)     ((c) - '0')
#define is_digit(c)     ((unsigned)to_digit(c) <= 9)
#define to_char(n)      ((n) + '0')
 
#define BUF             68
 
#define ALT             0X001
#define HEXPREFIX       0X002
#define LADJUST         0X004

#define LONGINT         0X010
#define QUADINT         0X020
#define SHORTINT        0X040
#define ZEROPAD         0X080
 
extern void PutCh(char ch);
extern void PutSt(char *ch);

static char *__uitoa(register uint16_t  val,
                     char               *endp,
                     int                base,
                     int                octzero,
                     char               *xdigs)
{
    register char       *cp = endp;
    register int16_t    sval;
 
    switch (base)
    {
        case 8:
            do
            {
                *--cp = to_char(val & 7);
                val >>= 3;
            } while(val);
            if (octzero && *cp != '0')
                *--cp = '0';
            break;
 
        case 10:
            if (val < 10)
            {
                *--cp = to_char(val);
                return cp;
            }

            sval = val;
 
            do
            {
                *--cp = to_char(sval % 10);
                sval /= 10;
            } while(sval != 0);
            break;
 
        case 16:
            do
            {
                *--cp = xdigs[val & 15];
                val >>= 4;
            } while(val);
            break;
 
        default:
            break;
    }
 
    return cp;
}
 
int vprintf(char *strbuf, const char *format, va_list ap)
{

    register char   *fmt;
    register char   *cp;
    register char   ch;
    register int    n;
    register int    flags;
    char            sign;
    int             ret;
    int             width;
    int             prec;
    int             dprec = 0;
    int             size;
    int             fieldsz;
    int             realsz;
    int             base;
    char            *xdigs = NULL;
    uint16_t        uival = 0;
    char            buf[BUF];
    char            ox[2];
 
 
#define PADSIZE 16
    static char blanks[PADSIZE] =
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    static char zeroes[PADSIZE] =
     {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
 
#define PRINT(ptr, len)                 \
    do {                                \
        int     i;                      \
        for (i=0; i<len; i++)           \
            *strbuf++ = ptr[i];         \
    }while(0)
 
#define PAD(howmany, with)              \
    do {                                \
        if ((n = (howmany)) > 0) {      \
            while (n > PADSIZE) {       \
                PRINT(with, PADSIZE);   \
                n -= PADSIZE;           \
            }                           \
            PRINT(with, n);             \
        }                               \
    }while(0)
 
#define SARG()                                          \
    (flags & LONGINT ? va_arg(ap, long) :               \
     flags & SHORTINT ? (long)(short)va_arg(ap, int) :  \
     (long)va_arg(ap, int))

//#define UARG() va_arg(ap, uint16_t)
 
 
    fmt = (char *)format;
    ret = 0;
 
    while (1)
    {
        for (cp = fmt; (ch = *fmt) != '\0' && ch != '%'; fmt++);
 
        if ((n = fmt - cp) != 0)
        {
            PRINT(cp, n);
            ret += n;
        }
 
        if (ch == '\0')
            goto done;
 
        fmt++;
 
        flags = 0;
        width = 0;
        prec  = -1;
        sign  = '\0';
 
        ch = *fmt++;

        switch (ch)
        {
            case 'c':
                *(cp = buf) = va_arg(ap, int);
                size = 1;
                sign = '\0';
                break;
 
            case 'd':
            case 'i':
                uival = SARG();
                if ((int)uival < 0)
                {
                    uival = -uival;
                    sign = '-';
                }
                 
                base = 10;
                goto number;
 
            case 'p':
                uival = (uint16_t)va_arg(ap, void *);
                base = 16;
                xdigs = "0123456789abcdef";
                flags = (flags & ~QUADINT) | HEXPREFIX;
                ch = 'x';
                goto nosign;
 
            case 's':
                if ((cp = va_arg(ap, char *)) == NULL)
                    cp = "(null)";
                if (prec >= 0)
                {
                    char *p = memchr(cp, 0, prec);
                    if (p != NULL)
                    {
                        size = p - cp;
                        if (size > prec)
                            size = prec;
                    }
                    else
                        size = prec;
                }
                else
                    size = strlen(cp);
                sign = '\0';
                break;
 
            case 'X':
                xdigs = "0123456789ABCDEF";
                goto hex;
            case 'x':

                xdigs = "0123456789abcdef";
hex:
                PutSt("Here is case x\n");
                //uival = UARG();
                uival = SARG();
                PutCh(to_char(uival&0x0f)) ;
                PutCh(to_char((uival>>4)&0x0f)) ;
                base = 16;
 
                if (flags & ALT && uival != 0)
                    flags |= HEXPREFIX;
nosign:
                sign = '\0';
number:
                if ((dprec = prec) >= 0)
                    flags &= ~ZEROPAD;
                cp = buf + BUF;

                if (uival != 0 || prec != 0)
                    cp = __uitoa(uival, cp, base, flags & ALT, xdigs);
                size = buf + BUF - cp;
                break;
 
            default:
                if (ch == '\0')
                    goto done;
                cp = buf;
                *cp = ch;
                size = 1;
                sign = '\0';
                break;
        }
 
        fieldsz = size;
        if (sign)
            fieldsz++;
        else if (flags & HEXPREFIX)
            fieldsz += 2;
        realsz = dprec > fieldsz ? dprec : fieldsz;
 
        if ((flags & (LADJUST | ZEROPAD)) == 0)
            PAD(width - realsz, blanks);
 
        if (sign)
        {
            *strbuf++ = sign;
        }
        else if (flags & HEXPREFIX)
        {
            ox[0] = '0';
            ox[1] = ch;
            PRINT(ox, 2);
        }
 
        if ((flags & (LADJUST | ZEROPAD)) == ZEROPAD)
            PAD(width - realsz, zeroes);
 
        PAD(dprec - fieldsz, zeroes);
        PRINT(cp, size);
 
        if (flags & LADJUST)
            PAD(width - realsz, blanks);
 
        ret += width > realsz ? width : realsz;
    }
 
done:
    *strbuf = '\0';
    return ret;
}
 
int myprintf(const char *format, ...)
{
    int     rc;
    va_list ap;
 
    va_start(ap, format);
 
    rc = vprintf(uart_buf, format, ap);
 
    va_end(ap);
 
    puts(uart_buf);
 
    return rc;
}
 
 
void putc(char ch)
{
 
    PutCh(ch);
 
    if (ch == '\n')
        PutCh('\r');
}
 
void puts(const char *str)
{
    while(*str)
        putc(*str++);
}
