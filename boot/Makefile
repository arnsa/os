CC = gcc
AS = nasm
LD = ld
CFLAGS = -c -m32 -nostdlib -nostartfiles -nodefaultlibs -o
ASFLAGS = -f
LDFLAGS = -m elf_i386 -e main -T linkers --strip-all -o idt
LDNAMES = idt.o idtc.o

ALL: IDTC IDTA BLS2 LINK LOAD

BS:
	$(AS) bootsector.asm $(ASFLAGS) bin -o bootsector

IDTC:
	$(CC) idt.c $(CFLAGS) idt.o

IDTA:
	$(AS) include/idt.inc $(ASFLAGS) elf -o idtc.o

BLS2:
	$(AS) BLS2.asm $(ASFLAGS) bin -o BLS2.SY

LINK:
	$(LD) $(LDNAMES) $(LDFLAGS)

LOAD:
	cat BLS2.SY idt > BLS2.SYS
	mkdir boots
	sudo mount -o loop win98.ima boots
	sudo cp BLS2.SYS boots
	sudo umount -f boots
	rm -rf boots
