offset:    dw 0

boot_elf:
    call ClrScr
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
