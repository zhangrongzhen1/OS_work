/* 修改后的链接脚本 */
OUTPUT_ARCH("riscv")
ENTRY(_entry)
SECTIONS
{
    /* 内核加载地址 */
    . = 0x80000000;

    /* 代码段 */
    .text : {
        *(.text.entry)
        *(.text .text.*)
        . = ALIGN(0x1000);
         etext = .;
    }

    /* 只读数据段 */
    .rodata : {
        *(.rodata .rodata.*)
        . = ALIGN(0x1000);
    }

    /* 已初始化数据段 */
    .data : {
        *(.data .data.*)
        . = ALIGN(0x1000);
        _edata = .;
    }

    /* 未初始化数据段 */
    .bss : {
        *(.bss .bss.*)
        . = ALIGN(0x1000);
        _end = .;
    }

    /* 确保关键符号在合理范围内 */
    PROVIDE(__global_pointer$ = . + 0x800);
}
