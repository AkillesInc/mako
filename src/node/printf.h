/*!
 * printf.h - printf for libsatoshi
 * Copyright (c) 2021, Christopher Jeffrey (MIT License).
 * https://github.com/chjj/libsatoshi
 */

#ifndef BTC_PRINTF_H
#define BTC_PRINTF_H

#include <stdarg.h>
#include <stdio.h>

/*
 * STDIO
 */

void
btc_putc(int ch);

void
btc_fputc(FILE *stream, int ch);

void
btc_puts(const char *str);

void
btc_fputs(FILE *stream, const char *str);

int
btc_printf(const char *fmt, ...);

int
btc_fprintf(FILE *stream, const char *fmt, ...);

int
btc_vprintf(const char *fmt, va_list ap);

int
btc_vfprintf(FILE *stream, const char *fmt, va_list ap);

#endif /* BTC_PRINTF_H */