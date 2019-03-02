#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
    #define Log(...) printf(__VA_ARGS__); printf("\n");
#else
    #define Log(...);
#endif

#endif // LOG_H
