#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

#define MAXS 1024 
void safe_printf(const char* format, ...)
{
    char buf[MAXS];
    va_list args;

    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    if (write(1, buf, strlen(buf)) == 0)
        return;
}
