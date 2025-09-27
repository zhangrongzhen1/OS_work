// kernel/main.c
#include "os.h"
// 声明外部函数
//extern void uart_init();
//extern void uart_puts(const char *s);

//基础测试
void test_printf_basic(){
    printf("Testing integer: %d\n", 42);
    printf("Testing negative: %d\n", -123);
    printf("Testing zero: %d\n", 0);
    printf("Testing hex: 0x%x\n", 0xABC);
    printf("Testing string: %s\n", "Hello");
    printf("Testing char: %c\n", 'X');
    printf("Testing percent: %%\n");
}
//边界测试
void test_printf_edge_base(){
    printf("INT_MAX: %d\n", 2147483647);
     printf("INT_MIN: %d\n", -2147483648);
    printf("NULL string: %s\n", (char*)0);
    printf("Empty string: %s\n", "");
}
//性能测试
void test_stress(){
    for(int i=0;i<100000;i++){
        printf("[%d] %s 0X%x\n",i,"stress test",(i+127));
    }
}
//错误测试
void test_error(){
    printf("Test %%k: %k\n", 42);  // 非法格式符
    printf("Test %\n");             // 不完整格式
    printf("Test %d %s\n", 42);     // 参数不足
}
//超长字符串
void test_overflow(){
    char giant[4096];
    for(int i=0;i<4096;i++){
        giant[i]='A';
    }
    giant[4095] = 0;
    printf("%s\n", giant);
}
void main() {
    
    volatile char* uart = (char*)0x10000000;
    *uart = 'K';
    // 2. 初始化串口
    uart_init();
   
    // 3. 通过串口输出目标字符串
    uart_puts("Hello OS\n");

    console_clear();

    printf("===== Test Start =====\n");
    test_error();
    //test_overflow();
    test_printf_basic();
    test_printf_edge_base();
    //test_stress();
    // 4. 程序结束后进入无限循环
    // 在裸机环境中，没有操作系统可返回。无限循环是防止CPU执行随机内存代码的安全措施。
    while (1) {
        // 可以在此处添加休眠指令（如`wfi`）以节省功耗
        asm volatile ("wfi");
    }
}
