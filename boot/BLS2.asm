
bits 16

org 0x8000

jmp start

%define VIDMEM 0xB8000

Good db "All good yo!", 0

Print16:
    lodsb
    or al, al
    jz short .Done
    mov ah, 0x0E
    int 0x10
    jmp short Print16
    .Done:
        ret

start:
	mov si, Good
	call Print16
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ax, 0x9000
    mov ss, ax
    mov sp, 0xFFFF
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
	nop

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

; Enable A20 Gate
a20:
    %include "a20.inc"

a20_error:
    error db "Couldn't enable A20 line!", 0, 13, 10
    mov edi, VIDMEM
    mov si, error
    .print:
        lodsb
        or al, al
        jz .done
        mov dl, al
        mov dh, 0x0E
        mov [edi], dx
    .done:
        cli
        hlt
