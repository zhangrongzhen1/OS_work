# Makefile
CC = riscv64-unknown-elf-gcc
LD = riscv64-unknown-elf-ld
OBJCOPY = riscv64-unknown-elf-objcopy
CFLAGS = -nostdlib -ffreestanding -mno-relax -march=rv64gc -mabi=lp64d -Iinclude -mcmodel=medany

# 查找所有源文件
SRCS = $(wildcard kernel/*.c kernel/boot/*.c kernel/*.S kernel/boot/*.S)
OBJS = $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRCS)))

all: kernel.elf

# 编译C源文件为对象文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 编译汇编源文件为对象文件
%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

# 链接所有对象文件生成ELF可执行文件
kernel.elf: $(OBJS) kernel/kernel.ld
	$(LD) -T kernel/kernel.ld -o $@ $(OBJS)

# 运行QEMU
qemu: kernel.elf
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel kernel.elf

# 清理构建产物
clean:
	rm -f $(OBJS) kernel.elf

.PHONY: all qemu clean
