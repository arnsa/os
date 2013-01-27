
bits 16

org 0x8000

jmp start

offset:    dd 0
Good db "All good yo!", 0

Print:
    lodsb
    or al, al
    jz short .Done
    mov ah, 0x0E
    int 0x10
    jmp short Print
    .Done:
        ret

start:
	mov si, Good
	call Print
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
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov esp, 0x90000
    mov al, 0x02
    out 0x92, al

boot_elf:
    mov eax, dword[eof+0x1C]
    mov [offset], eax
    movzx ecx, word[eof+0x2C]
    jmp near load_segments

load_segments:
    push ecx
    mov eax, dword[offset]
    add eax, 0x04
    mov esi, dword[eof+eax] ; move p_offset
    add esi, eof
    add eax, 0x04
    mov edi, dword[eof+eax] ; move p_vaddr
    add eax, 0x08
    mov ecx, dword[eof+eax] ; move p_filesz file starts at p_offset, should be loaded at p_vaddr and it's size is p_memsz
    rep movsb
    pop ecx
    mov eax, [offset]
    add eax, [eof+0x2A]
    mov [offset], eax
    dec ecx
    jnz load_segments
    jmp dword[eof+0x18]

eof:
