#pragma once
#include <stdarg.h>

// 硬件层
void uart_init();
void uart_putc(char c);
void uart_puts(const char* s);

// 控制台层
void console_putc(char c);
void console_puts(const char *s);
void console_clear();

// 格式化层
int printf(const char *fmt, ...);
int sprintf(char *buf, const char *fmt, ...);


