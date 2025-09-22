// kernel/main.c

// 声明外部函数
extern void uart_init();
extern void uart_puts(const char *s);

// 声明来自链接脚本的符号，用于清零BSS段
extern char _edata[];
extern char _end[];

void main() {
    
    volatile char* uart = (char*)0x10000000;
    *uart = 'K';
    // 2. 初始化串口
    uart_init();
   
    // 3. 通过串口输出目标字符串
    uart_puts("Hello OS\n");

    // 4. 程序结束后进入无限循环
    // 在裸机环境中，没有操作系统可返回。无限循环是防止CPU执行随机内存代码的安全措施。
    while (1) {
        // 可以在此处添加休眠指令（如`wfi`）以节省功耗
        asm volatile ("wfi");
    }
}
