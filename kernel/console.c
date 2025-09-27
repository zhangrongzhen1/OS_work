#include "os.h"

// 单字符输出（含换行处理）
void console_putc(char c) {
    uart_putc(c);
    if (c == '\n') uart_putc('\r'); 
}

// 字符串输出（优化版）
void console_puts(const char *s) {
    while (*s) {
        console_putc(*s++);
    }
}

// ANSI清屏
void console_clear() {
    console_puts("\033[2J\033[H"); // ESC[2J + ESC[H
}
