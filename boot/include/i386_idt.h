#pragma pack(1)

#include "types.h"

struct _idt {
	u16_t low;
	u16_t selector;
	u16_t flags;
	u16_t high;
};

struct registers{
    u32_t 
		ss,gs,fs,es,ds,
        edi,esi,edx,ecx,ebx,eax,ebp,esp,
        N,errorcode,
        eip,cs,eflags,
        old_esp,old_ss,
        old_es,old_ds,
        old_fs,old_gs ;
};

extern char const * exceptions [32] ;