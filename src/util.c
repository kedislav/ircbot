#include "../includes/util.h"
char* format(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    if (len < 0) return "";

    char* formatted = (char*) malloc(sizeof(char) * (len + 1));
    va_start(args, fmt);
    vsnprintf(formatted, len + 1, fmt, args);
    va_end(args);
    return formatted;
}