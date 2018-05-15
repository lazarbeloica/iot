#ifndef _DEBUG_HH_
#define _DEBUG_HH_

#include <iostream>

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
#define LOG_DEBUG(x, ...)   printf("%s %d:",__FILE__, __LINE__);\
                            printf(FGRN(x),  ##__VA_ARGS__);\
                            printf("\n");

#define LOG_WARNING(x, ...) printf("%s %d:",__FILE__, __LINE__);\
                            printf(FYEL(x),  ##__VA_ARGS__);\
                            printf("\n");

#define LOG_ERROR(x, ...)   printf("%s %d:",__FILE__, __LINE__);\
                            printf(FRED(x),  ##__VA_ARGS__);\
                            printf("\n");
#else
#define LOG_DEBUG(x, ...)
#define LOG_WARNING(x, ...)
#define LOG_ERROR(x, ...)
#endif

#endif //_DEBUG_HH_