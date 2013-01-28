a20_scp:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov esp, 0x90000
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
    or al, 0x02
    jnz wait_input
    ret

wait_output:
    in al, 0x64
    or al, 0x01
    jz wait_output
    ret 

elf:
    jmp boot_elf
    %include "bootelf.inc"
