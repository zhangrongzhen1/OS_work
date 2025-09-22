.section .text.entry
.global _entry
_entry:
    # 调试输出：向UART发送字符'S'
    li t0, 0x10000000   # UART发送寄存器地址
    li t1, 'S'
    sb t1, 0(t0)        # 输出字符

    # 设置栈指针
    la sp, stack0       # 加载栈基地址
    li t0, 4096         # 栈大小=4KB
    add sp, sp, t0      # sp = stack0 + 4096（栈顶）
    #清零BSS段
    la a0, _edata  # BSS起始地址
    la a1, _end    # BSS结束地址
    bgeu a0, a1, 2f     # 如果范围无效则跳过
1:
    sb zero, 0(a0)      # 逐字节清零
    addi a0, a0, 1
    bltu a0, a1, 1b     # 循环直到结束
2:
    li t0, 0x10000000
    li t1, 'P'
    sb t1, 0(t0)

    # 跳转到C代码
    call start

    # 安全措施：如果意外返回则挂起
spin:
    j spin

# 栈空间定义
.section .bss.stack
.align 16               # 16字节对齐（RISC-V要求）
.global stack0
stack0:
    .skip 4096         # 分配4KB空间