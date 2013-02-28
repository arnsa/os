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
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
global isr32
global isr33
global isr34
global isr35
global isr36
global isr37
global isr38
global isr39
global isr40
global isr41
global isr42
global isr43
global isr44
global isr45
global isr46
global isr47

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

isr19:
	push dword 0x00
	push dword 0x13
	jmp isr_stub

isr20:
	push dword 0x00
	push dword 0x14
	jmp isr_stub

isr21:
	push dword 0x00
	push dword 0x15
	jmp isr_stub

isr22:
	push dword 0x00
	push dword 0x16
	jmp isr_stub

isr23:
	push dword 0x00
	push dword 0x17
	jmp isr_stub

isr24:
	push dword 0x00
	push dword 0x18
	jmp isr_stub

isr25:
	push dword 0x00
	push dword 0x19
	jmp isr_stub

isr26:
	push dword 0x00
	push dword 0x1A
	jmp isr_stub

isr27:
	push dword 0x00
	push dword 0x1B
	jmp isr_stub

isr28:
	push dword 0x00
	push dword 0x1C
	jmp isr_stub

isr29:
	push dword 0x00
	push dword 0x1D
	jmp isr_stub

isr30:
	push dword 0x00
	push dword 0x1E
	jmp isr_stub

isr31:
	push dword 0x00
	push dword 0x1F
	jmp isr_stub

isr32:
	push dword 0x00
	push dword 0x20 
	jmp isr_stub

isr33:
	push dword 0x00
	push dword 0x21
	jmp isr_stub

isr34:
	push dword 0x00
	push dword 0x22
	jmp isr_stub

isr35:
	push dword 0x00
	push dword 0x23
	jmp isr_stub

isr36:
	push dword 0x00
	push dword 0x24
	jmp isr_stub

isr37:
	push dword 0x00
	push dword 0x25
	jmp isr_stub

isr38:
	push dword 0x00
	push dword 0x26
	jmp isr_stub

isr39:
	push dword 0x00
	push dword 0x27
	jmp isr_stub

isr40:
	push dword 0x00
	push dword 0x28
	jmp isr_stub

isr41:
	push dword 0x00
	push dword 0x29
	jmp isr_stub

isr42:
	push dword 0x00
	push dword 0x2A
	jmp isr_stub

isr43:
	push dword 0x00
	push dword 0x2B
	jmp isr_stub

isr44:
	push dword 0x00
	push dword 0x2C
	jmp isr_stub

isr45:
	push dword 0x00
	push dword 0x2D
	jmp isr_stub

isr46:
	push dword 0x00
	push dword 0x2E
	jmp isr_stub

isr47:
	push dword 0x00
	push dword 0x2F
	jmp isr_stub

isr_stub:
	push esp
	add dword [esp], 0x08
	push ebp
	push eax
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ds
	push es
	push fs
	push gs
	push ss
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	push esp
	call i386_handle_exception
	add esp, 0x04
	pop ss
	pop gs
	pop fs
	pop es
	pop ds
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	pop eax
	pop ebp
	pop esp
	iret
