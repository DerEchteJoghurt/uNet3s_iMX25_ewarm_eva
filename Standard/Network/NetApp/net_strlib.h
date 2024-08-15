/***************************************************************************
    MICRO C CUBE / COMPACT/STANDARD, NETWORK Application
    String Library header
    Copyright (c) 2012-2014, eForce Co., Ltd. All rights reserved.

    Version Information
      2012.10.02: Created
      2013.06.28: Add net_strstr(), net_strcasestr()
      2014.03.31: Add net_strncmp(), net_strncat(), net_atoi(), net_itoa()
                  , net_ltoa()
      2014.04.01: Changed to ANSI equivalent to the type of arguments and re-
                  turn value. But, 'size_t' was replace by 'SIZE' in uITRON.
      2015.02.06: Add definition of NULL
 ***************************************************************************/

#ifndef NET_STRLIB_H
#define NET_STRLIB_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kernel.h"

#ifndef NULL
#define NULL    ((void*)0)
#endif

int net_atoi(const char *str);
long net_atol(const char *str);
char* net_itoa(int num, char *str, int base);

int net_strncmp(const char *str1, const char *str2, SIZE len);
int net_strcmp(const char *str1, const char *str2);
char* net_strcpy(char *str1, const char *str2);
SIZE net_strlen(const char *str);
char* net_strncat(char *str1, const char *str2, SIZE len);
char* net_strcat(char *str1, const char *str2);
char* net_strchr(const char *str, int ch);
char* net_strstr(const char *str1, const char *str2);
int net_strncasecmp(const char *str1, const char *str2, SIZE len);
char *net_strcasestr(const char *str1, const char *str2);


#ifdef __cplusplus
}
#endif
#endif

