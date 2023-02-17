#include <stdio.h>
#include <stdarg.h> // va_list, va_start, va_end, va_arg are defined 

// return the string length pointed by str
size_t strlen(const char *str) ;

// reverse the order of the string  pointed by str
void flipstr(char *str) ;

// Converts integer number into dicimal, hex, binary, ...
int ItoA(int ivaue, char *buffer, int radix) ;

int myvprintf(char *pbuf, const char *format, va_list ap) ;

int myprintf(const char *format, ...);
