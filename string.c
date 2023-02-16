#include <stddef.h>
#include <string.h>


void *memchr (const void *s, int c, size_t n)
{
    const unsigned char *src = (const void *)s;

    c &= 0xFF;

    while (n--)
    {
        if (*src == c)
        {
            return (void *)src;
        }
        src++;
    }

    return NULL;
}

size_t strlen (const char *s)
{
    int retval;

    const char *start = s;

    while (*s)
        s++;

    retval = s - start;

    return retval;
}
