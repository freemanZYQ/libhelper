//===--------------------------- strutils ----------------------------===//
//
//                         The Libhelper Project
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//
//  Copyright (C) 2019, Is This On?, @h3adsh0tzz
//  me@h3adsh0tzz.com.
//
//
//===------------------------------------------------------------------===//

/**
 *  Original license: The Ni Programming Language
 */

#ifndef LIBHELPER_STRUTILS_H
#define LIBHELPER_STRUTILS_H

#include "libhelper/libhelper.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Error codes */
#define ERR_NOT_DEBUG   "Debug mode not set"

/* Text Colours */
typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_DEBUG,
    LOG_PRINT
} log_type;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* String type */
typedef struct StringList {
    char    **ptrs;
    int     count;
} StringList;

/* String appending */
char *strappend (char *a, char *b);
char *mstrappend (char *fmt, ...);

/* String splits */
StringList *strsplit (const char *s, const char *delim);

/* Boyermoore Horspool memmem() */
//static unsigned char *
//boyermoore_horspool_memmem(const unsigned char* haystack, size_t hlen,
//                           const unsigned char* needle,   size_t nlen);

/* Logging */
int __printf(log_type msgType, char *fmt, ...);
#define errorf(fmt, ...)  __printf(LOG_ERROR, fmt, ##__VA_ARGS__)
#define debugf(fmt, ...)  __printf(LOG_DEBUG, fmt, ##__VA_ARGS__)
#define warningf(fmt, ...)  __printf(LOG_WARNING, fmt, ##__VA_ARGS__)

//#define __UCHAR_MAX 255

#endif /* libhelper_strutils_h */