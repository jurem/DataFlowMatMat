#ifndef COMMON_H
#define COMMON_H


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


void error(const int status, const char * fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, argp);
    fprintf(stderr, "\n");
    va_end(argp);
    exit(status);
}


#endif
