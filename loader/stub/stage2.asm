bits 16

org 0x8000

jmp start

%define VIDMEM	0xB8000
%define X		0x50
%define Y		0x19
%define ATTR	0x07		

start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ax, 0x9000
    mov ss, ax
    mov sp, 0xFC00
	jmp load_gdt

gdt:
; NULL the first descriptor
	dd 0 			
	dd 0 

; Setup code descriptor
	dw 0xffff
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0
 
; Setup data descriptor
	dw 0xffff
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0

gdt_end:

gdt_pointer:
	dw gdt_end - gdt - 1
	dd gdt

load_gdt:
	lgdt [gdt_pointer]
	jmp pmode

; Turn on protected mode
pmode:
	cli
	mov eax, cr0
	or eax, 1
	mov cr0,eax
	jmp 0x8:a20

bits 32

ClrScr32:
	mov ax, 0x700
	mov ecx, X*Y
	mov edi, VIDMEM
	cld
	rep stosw
	ret

; Enable A20 Gate
a20:
    mov ax, 0x10
    mov ss, ax
    mov es, ax
	mov fs, ax
	mov gs, ax
    mov ds, ax
    mov esp, 0x90000
	call ClrScr32
    %include "a20.inc"
