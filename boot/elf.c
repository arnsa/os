#include <stdio.h>
#include <stdlib.h>

#define EI_NIDENT   16
#define HEADER_SIZE 64

typedef unsigned        Elf32_Addr;
typedef unsigned short  Elf32_Half;
typedef unsigned        Elf32_Off;
typedef unsigned        Elf32_Word; 

typedef struct {
    unsigned char   e_ident[EI_NIDENT];
    Elf32_Half      e_type;
    Elf32_Half      e_machine;
    Elf32_Word      e_version;
    Elf32_Addr      e_entry;
    Elf32_Off       e_phoff;
    Elf32_Off       e_shoff;
    Elf32_Word      e_flags;
    Elf32_Half      e_ehsize;
    Elf32_Half      e_phentsize;
    Elf32_Half      e_phnum;
    Elf32_Half      e_shentsize;
    Elf32_Half      e_shnum;
    Elf32_Half      e_shstrndx;
} Elf32_Ehdr;

typedef struct {
    Elf32_Word      p_type;
    Elf32_Off       p_offset;
    Elf32_Addr      p_vaddr;
    Elf32_Addr      p_addr;
    Elf32_Word      p_filesz;
    Elf32_Word      p_memsz;
    Elf32_Word      p_flags;
    Elf32_Word      p_aligh;
} Elf32_Phdr;

void readElfHeader(FILE * elfFile, Elf32_Ehdr * eheader)
{
    fread(eheader, 1, HEADER_SIZE, elfFile); 
}

void readProgramHeaders(FILE * elfFile, Elf32_Phdr *  pheader, Elf32_Ehdr eheader)
{
    int i;

    for(i = 0; i < eheader.e_phnum; i++)
        fread(&pheader[i], 1, eheader.e_phentsize, elfFile);
}

void loadSegments(FILE * elfFile, Elf32_Phdr * pheader, Elf32_Ehdr eheader)
{
    int i;

    for(i = 0; i < eheader.e_phnum; i++){
        fseek(elfFile, pheader[i].p_offset, SEEK_SET);
        fread((void *)pheader[i].p_vaddr, 1, pheader[i].p_memsz, elfFile);
    }
}

int main()
{
    Elf32_Ehdr eheader;
    Elf32_Phdr * pheader;
    FILE * elfFile = fopen("hello", "rb");

    readElfHeader(elfFile, &eheader);
    pheader = (Elf32_Phdr *) malloc(eheader.e_phnum * eheader.e_phentsize);
    readProgramHeaders(elfFile, pheader, eheader);
    //loadSegments(elfFile, pheader, eheader);
    printf("%d\n", eheader.e_phnum);
    fclose(elfFile);

    return 0;
}
