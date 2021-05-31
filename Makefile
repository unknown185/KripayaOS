#
#  Makefile
#  KripayaOS
#
#  Created by Ashwin Paudel on 2021-05-31.
#

# $@ = target file
# $< = first dependency
# $^ = all dependencies

# detect all .o files based on their .c source
C_SOURCES = $(wildcard src/Kernel/*.cpp src/Drivers/*.cpp)
HEADERS = $(wildcard include/Kernel/*.h  include/Drivers/*.h)
OBJ_FILES = ${C_SOURCES:.cpp=.o}

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: src/Boot/KernelEntry.o ${OBJ_FILES}
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

os-image.bin: src/Boot/MBR.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-i386 -fda $<

echo: os-image.bin
	xxd $<

# only for debug
kernel.elf: src/Boot/KernelEntry.o ${OBJ_FILES}
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -S -fda os-image.bin &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.cpp ${HEADERS}
	x86_64-elf-gcc -Iinclude -g -m32 -ffreestanding -c $< -o $@ # -g for debugging

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

%.dis: %.bin
	ndisasm -b 32 $< > $@

clean:
	$(RM) *.bin *.o *.dis *.elf
	$(RM) src/Kernel/*.o
	$(RM) src/Boot/*.o src/Boot/*.bin
	$(RM) src/Drivers/*.o