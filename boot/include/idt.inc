section .text:
	extern i386_handle_exception

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18

isr0:
	push dword 0x00
	push dword 0x00
	jmp isr_stub

isr1:
	push dword 0x00
	push dword 0x01
	jmp isr_stub

isr2:
	push dword 0x00
	push dword 0x02
	jmp isr_stub

isr3:
	push dword 0x00
	push dword 0x03
	jmp isr_stub

isr4:
	push dword 0x00
	push dword 0x04
	jmp isr_stub

isr5:	
	push dword 0x00
	push dword 0x05
	jmp isr_stub

isr6:	
	push dword 0x00
	push dword 0x06
	jmp isr_stub

isr7:
	push dword 0x00
	push dword 0x07
	jmp isr_stub

isr8:
	push dword 0x08
	jmp isr_stub

isr9:
	push dword 0x00
	push dword 0x09
	jmp isr_stub

isr10:
	push dword 0x0A
	jmp isr_stub

isr11:
	push dword 0x0B
	jmp isr_stub

isr12:
	push dword 0x0C
	jmp isr_stub

isr13:	
	push dword 0x0D
	jmp isr_stub

isr14:	
	push dword 0x0E
	jmp isr_stub

isr15:
	push dword 0
	push dword 0x0F
	jmp isr_stub

isr16:
	push dword 0
	push dword 0x10
	jmp isr_stub

isr17:
	push dword 0x11
	jmp isr_stub

isr18:
	push dword 0x00
	push dword 0x12
	jmp isr_stub

isr_stub:
	push esp
	add dword [esp], 0x04
	push ebp
	push eax
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push dword ds
	push dword es
	push dword fs
	push dword gs
	push dword ss
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	push esp
	call i386_handle_exception
	add esp,4 
	pop dword ss
	pop dword gs
	pop dword fs
	pop dword es
	pop dword ds
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	pop eax
	iret
