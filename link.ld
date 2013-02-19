    ENTRY (main)
    SECTIONS {
        . = 0x100000;          
        .text : {
            *(.text)
        }
        .data : {
            *(.rodata)
            *(.rdata)
            *(.data)
        }
        .bss : {
            *(.bss)
        }
        /DISCARD/ : {
            *(.comment)
        }
    }

