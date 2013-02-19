bits 16
org 0x7C00
     
jmp near load_rootdir
     
BPB_OEM                 db "OS      "
BPB_BytesPerSector:     dw 512
BPB_SectorsPerCluster:  db 1
BPB_ReservedSectors:    dw 1
BPB_NumberOfFATs:       db 2
BPB_RootEntries:        dw 224
BPB_TotalSectors:       dw 2880
BPB_Media:              db 0xF0
BPB_SectorsPerFAT:      dw 9
BPB_SectorsPerTrack:    dw 18
BPB_HeadsPerTrack:      dw 2
BPB_HiddenSectors:      dd 0
BPB_TotalSectorsBig:    dd 0
BS_DriveNumber:         db 0
BS_Unused:              db 0
BS_ExtBootSignature:    db 0x29
BS_SerialNumber:        dd 0x0
BS_VolumeLabel:         db "NO NAME    "
BS_FileSystem:          db "FAT12   "
     
cluster: dw 0
lba: dw 0
offset: dw 0

bootloader db "BLS2    SYS", 0
errormsg:
db "Read error or system files not present!", 13, 10
db "Press a key to reboot...", 13, 10, 0

load_rootdir:
	xor ax, ax
	mov ss, ax
	mov sp, 0x7C00
	mov ds, ax
	mov es, ax
	mov ax, word[BPB_SectorsPerFAT]
	mul byte[BPB_NumberOfFATs]
	add ax, word[BPB_ReservedSectors] ; ax = lba = SecPerFAT * NumOfFAT + Resv
	mov [offset], ax
	mov [lba], ax
	xor bx, bx
	mov ax, 0x0800
	mov es, ax
	mov ax, word[BPB_RootEntries]
	shl ax, 0x05
	div word[BPB_BytesPerSector] ; al = RootEnt * 32 / BytesPerSec
	add [offset], ax
	call read_sectors
	mov cx, word[BPB_RootEntries]
	xor di, di
	.find_bootloader:
		push cx
		push di
		mov cx, 0x0B
		mov si, bootloader
		repz cmpsb
		pop di
		pop cx
		jz short load_fat
		add di, 32
		loop .find_bootloader
		jmp near not_found

load_fat:
	mov ax, word[BPB_SectorsPerFAT]
	mov bx, word[BPB_BytesPerSector]
	shr bx, 4
	mul bx ; ax = BytesPerSec / 16 * SectorsPerFAT
	mov bx, 0xA000
	sub bx, ax
	mov gs, bx
	mov es, bx
	mov ax, word[BPB_ReservedSectors]
	mov [lba], ax
	xor bx, bx
	mov ax, word[BPB_SectorsPerFAT]
	call read_sectors
	mov ax, 0x0800
	mov es, ax
	mov bx, [es:di+0x001A]
	mov [cluster], bx
	jmp short load_bootloader

load_bootloader:
	mov ax, word[cluster]
	sub ax, 0x0002
	movzx bx, byte[BPB_SectorsPerCluster]
	mul bx
	add ax, word[offset]
	mov [lba], ax
	mov al, byte[BPB_SectorsPerCluster]
	xor bx, bx
	call read_sectors
	call get_next_cluster
	mov [cluster], ax
	cmp ax, 0x0FF8
	jge finished
	mov ax, word[BPB_BytesPerSector]
	movzx bx, byte[BPB_SectorsPerCluster]
	mul bx
	shr ax, 4
	mov bx, es
	add bx, ax
	mov es, bx	
	jmp short load_bootloader

get_next_cluster:
	mov ax, word[cluster]
	mov bx, 0x0003
	mul bx
	xor dx, dx
	mov bx, 0x0002
	div bx
	mov bx, ax
	mov ax, [gs:bx]
	mov bx, word[cluster]
	and bx, 0x0001
	jz short .even
	jnz .odd
	.odd:
		shr ax, 4
		mov [cluster], ax
		ret
	.even:
		and ax, 0x0FFF
		mov [cluster], ax
		ret

print:
	lodsb
	or al, al
	jz short .Done
	mov ah, 0x0E
	int 0x10
	jmp short print
	.Done:
		ret

not_found:
	mov si, errormsg
	call print
	xor ah, ah
	int 0x16
	int 0x19

read_sectors:
	push ax
	push bx
	mov ax, word[lba]
	xor dx, dx
	div word[BPB_SectorsPerTrack]
	mov cl, dl
	inc cl ; cl has sector number
	xor dx, dx
	div word[BPB_HeadsPerTrack]
	mov dh, dl ; dh has head number
	mov dl, byte[BS_DriveNumber]
	push dx
	mov ax, word[BPB_SectorsPerTrack]
	mul word[BPB_HeadsPerTrack]
	mov bx, ax
	mov ax, word[lba]
	xor dx, dx
	div bx
	mov ch, al ; ch has cylinder number
	pop dx
	pop bx
	pop ax
	mov ah, 0x02
	int 0x13
	ret

finished:
	jmp 0x0000:0x8000

times 510 - ($-$$) db 0
dw 0xAA55
