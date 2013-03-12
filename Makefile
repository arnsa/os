AC = nasm
CC = gcc
LD = ld

CFLAGS = -c -m32 -nostdlib -nostartfiles -nodefaultlibs
AFLAGS = -f
LDFLAGS = -m elf_i386 -e kmain -T link.ld --strip-all -o

all: compile_a compile_c link finish

#COMPILE ASM
compile_a:

	cd loader/booter && ${AC} bootsector.asm ${AFLAGS} bin -o bootsector && ${AC} idt.asm ${AFLAGS} elf -o idt.o

	cd loader/stub && ${AC} stage2.asm ${AFLAGS} bin -o stage2.bin
	mv loader/booter/bootsector bootsector
	mv loader/booter/idt.o idt.o
	mv loader/stub/stage2.bin stage2.bin

#COMPILE C
compile_c:

	${CC} tools/ctool.c -o ctool
	${CC} loader/booter/i386.c ${CFLAGS} -I include -o i386.o
	${CC} loader/booter/pic.c ${CFLAGS} -I include -o pic.o
	${CC} loader/booter/main.c ${CFLAGS} -I include -o main.o
	${CC} include/clib/printf.c ${CFLAGS} -o printf.o
	${CC} include/clib/stdlib.c ${CFLAGS} -o stdlib.o
	${CC} include/clib/string.c ${CFLAGS} -o string.o

#LINK
link:

	${LD} main.o i386.o idt.o pic.o printf.o stdlib.o string.o ${LDFLAGS} stage2.elf

#FINISH
finish:

	./ctool bootsector win98.ima
	cat stage2.bin stage2.elf > stage2.sys
	mkdir boots
	sudo mount -o loop win98.ima boots
	sudo cp stage2.sys boots
	sudo umount -f boots
	rm -rf boots
