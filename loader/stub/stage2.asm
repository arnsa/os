bits 16

org 0x8000

jmp start

%define VIDMEM 0xB8000
%define X      0x50
%define Y      0x19
%define ATTR   0X07

CurX dd 0
CurY dd 0

done16 db "Done", 13, 10, 0
done32 db "Done", 0
load_gdt_msg db "[CPU] Loading GDT... ", 0
pmode_msg db "[CPU] Switching to Protected Mode... ", 0
a20_msg db "[CPU] Enabling A20 line... ", 0

Print16:
    lodsb
    or al, al
    jz short .Done
    mov ah, 0x0E
    int 0x10
    jmp short Print16
    .Done:
        ret

ClrScr16:
	mov cx, 0x7D0
	.clear:
		mov al, ' '
		or cx, cx
		jz .done
		mov ah, 0x0E
		int 0x10
		dec cx 
		jmp short .clear  
	.done:
		mov al, 0x00
		mov ah, 0x02
		int 0x10
		ret 

start:
	call ClrScr16 
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
	mov si, load_gdt_msg
	call Print16
	lgdt [gdt_pointer]
	mov si, done16
	call Print16
	jmp pmode

; Turn on protected mode
pmode:
	mov si, pmode_msg
	call Print16 
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

Puts32:
	pusha
	mov	edi, VIDMEM
	xor	eax, eax
	mov	ecx, X*2
	mov	al, byte[CurY]
	mul	ecx
	push eax
	mov	al, byte[CurX]
	mov	cl, 0x02
	mul	cl
	pop	ecx
	add	eax, ecx
	xor	ecx, ecx
	add	edi, eax
	cmp	bl, 0x0A
	je	.Row
	mov	dl, bl
	mov	dh, ATTR
	mov	word[edi], dx
	inc	byte[CurX]
	cmp	byte[CurX], X
	je	.Row
	jmp	.done

	.Row:
		mov	byte[CurX], 0x00
		inc	byte[CurY]

	.done:
		popa 
		ret

Print32:
	pusha
	push ebx
	pop	edi

.loop:
	mov	bl, byte[edi]
	cmp	bl, 0
	je	.done
	call Puts32	
	inc	edi
	jmp	.loop

.done:
	mov	bh, byte[CurY]
	mov	bl, byte[CurX]
	popa
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
	mov ebx, done32
	mov byte[CurY], 0x01
	mov byte[CurX], 0x25
	call Print32
	inc byte[CurY]
	mov byte[CurX], 0x00
	mov ebx, a20_msg
	call Print32
    %include "a20.inc"
