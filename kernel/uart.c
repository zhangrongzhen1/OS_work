// kernel/uart.c

// UART0 的内存映射地址
#define UART0_BASE 0x10000000
// 发送保持寄存器 (THR) 偏移量
#define UART0_THR (volatile unsigned char *)(UART0_BASE + 0x00)
#define UART0_LSR   (volatile unsigned char *)(UART0_BASE + 0x05)  // 状态寄存器
// LSR 寄存器位定义
#define LSR_THRE    0x20  // 发送保持寄存器空 (Transmit Holding Register Empty)
// 输出单个字符
void uart_putc(char c)
 { while ((*UART0_LSR & LSR_THRE) == 0); // 等待发送缓冲区空
  *UART0_THR = c;  }
// 输出字符串
void uart_puts(const char *s) { while (*s) { uart_putc(*s++); } }
void uart_init() {
    // QEMU virt 平台的 UART 默认已初始化
    // 此函数可为空，或添加必要的硬件初始化代码
    // 例如设置波特率（但 QEMU 中通常不需要）
}

