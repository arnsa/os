a20_scp:
    mov al, 0x02
    out 0x92, al
    mov eax, 0x11111111
    mov [0x100000], eax
    cmp [0], eax
    jz a20_kp
    jmp elf

a20_kp:
    mov al, 0xDD
    out 0x64, al
    mov eax, 0x11111111
    mov [0x100000], eax
    cmp [0], eax
    jz a20_op
    jmp elf

a20_op:
    call wait_input
    mov al, 0xAD
    out 0x64, al
    
    call wait_input
    mov al, 0xD0
    out 0x64, al

    call wait_output
    in al, 0x60
    push eax

    call wait_input
    mov al, 0xD1
    out 0x64, al

    call wait_input
    pop eax
    or al, 0x02
    out 0x60, al

    call wait_input
    mov al, 0xAE
    out 0x64, al

    mov eax, 0x11111111
    mov [0x100000], eax
    cmp [0], eax
    jz a20_error
    jmp elf

wait_input:
    in al, 0x64
    test al, 0x02
    jnz wait_input
    ret

wait_output:
    in al, 0x64
    test al, 0x01
    jz wait_output
    ret

error_a20 db "Couldn't enable A20 line! Computer will reboot...", 0

a20_error:
    call ClrScr32
    mov edi, VIDMEM 
    mov esi, error_a20 
    .print: 
        lodsb 
        or al, al 
        jz .reboot
        mov dl, al 
        mov dh, 0x0E 
        mov [edi], dx 
        add edi, 2 
        jmp .print 
   .reboot:
        mov eax, 0
        mov ebx, 0
        div ebx

elf:
	mov ebx, done32
	call Print32
	mov al, byte[CurY]
	mov [0x450], al
    jmp boot_elf
    %include "bootelf.inc"

