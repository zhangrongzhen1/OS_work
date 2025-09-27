#include "os.h"
#include <stdarg.h>

static char digits[]="0123456789abcdef";
static void printint(long long xx, int base,int sign) {
    char buf[32];
    int i = 0;
    unsigned long long x;

    if (xx == -2147483648LL && base == 10 && sign) {
        console_puts("-2147483648");
        return;
    }

    if(sign&&(sign=(xx<0)))
    x=-xx;
    else
    x=xx;

    do{
        buf[i++]=digits[x%base];
    }while((x/=base)!=0);
    
    if (sign) buf[i++] = '-';

    while (--i >= 0) console_putc(buf[i]);
}

// 内核格式化输出
int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int cx;
    char*s;
    for (int i = 0; (cx = fmt[i] & 0xff) != 0; i++) {
        if (cx != '%') {
            console_putc(cx);
            continue;
        }
        
        switch (fmt[++i]) {
        case 'd': printint(va_arg(ap, int), 10,1); break;
        case 'x': printint(va_arg(ap, unsigned int), 16,0); break;
        case 's': 
        s = va_arg(ap, char*);
        if (!s) s = "null";
        while (*s) console_putc(*s++);
        break;
        case 'c': console_putc(va_arg(ap, unsigned int)); break;
        case '%': console_putc('%'); break;
        default:  console_putc('%'); console_putc(fmt[i]);
        }
    }
    
    va_end(ap);
    return 0;
}

