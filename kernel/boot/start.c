// kernel/boot/start.c

// 声明main函数，防止编译器警告
extern void main();

void start() {
    // 1. 调试：输出字符 'M'
    volatile char* uart = (char*)0x10000000;
    *uart = 'M';

    // 3. 直接调用main
    main();

    // 4. 安全措施（理论上不会执行到这里）
    while (1);
}