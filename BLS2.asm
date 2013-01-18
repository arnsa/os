bits 16

org 0x8000

jmp GDT

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

; Setup GDT
GDT:
	mov SI, Good
	call Print

; Prepare registers
	xor	ax, ax
	mov	ds, ax
	mov	es, ax
	mov	ax, 0x9000
	mov	ss, ax
	mov	sp, 0xFFFF

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

GDT_END:
	nop

GDT_POINTER:
	dw GDT_END - GDT - 1
	dd GDT

lgdt [GDT_POINTER]
jmp P_MODE

; Turn on protected mode
P_MODE:
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov esp, 0x90000
	mov eax, cr0
	or eax, 1
	mov cr0,eax

jmp 0x8:a20

bits 32

; Enable A20 Gate
a20:
	mov al, 0xDD
	out 0x64, al