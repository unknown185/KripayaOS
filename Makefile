#
#  Makefile
#  KripayaOS
#
#  Created by Ashwin Paudel on 2021-05-31.
#


### Tokens
# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
all:
	make clean
	mkdir Build
	mkdir Build/Products
	mkdir Build/Boot
	mkdir Build/Kernel
	make run

# Notice how dependencies are built as needed
Build/Products/Kernel.bin: Build/Boot/KernelEntry.o Build/Kernel/Kernel.o
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

Build/Boot/KernelEntry.o: Boot/KernelEntry.asm
	nasm $< -f elf -o $@

Build/Kernel/Kernel.o: Kernel/Kernel.cpp
	x86_64-elf-gcc -m32 -ffreestanding -c $< -o $@

# Disassemble
kernel.dis: Build/Products/Kernel.bin
	ndisasm -b 32 $< > $@

Build/Boot/MBR.bin: Boot/MBR.asm
	nasm $< -f bin -o $@

Build/Products/KripayaOS.bin: Build/Boot/MBR.bin Build/Products/Kernel.bin
	cat $^ > $@

run: Build/Products/KripayaOS.bin
	qemu-system-i386 -fda $<

echo: Build/Products/KripayaOS.bin
	xxd $<

clean:
	rm -r Build
