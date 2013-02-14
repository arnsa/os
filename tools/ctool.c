#include <stdio.h>
#include <string.h>
#include <assert.h>

int main (int c,char ** v) {

FILE *i,*o ;

static char src [0x200] ;

static char dst [0x200] ;

if (c < 2) {

printf ("file-boot1st [source] [dest]\n") ;

return 0 ;

}

assert (i = fopen (v [1],"rb")) ;

assert (o = fopen (v [2],"r+b")) ;

if (!i || !o) {

printf ("Can't open '%s' or '%s'\n",v [1],v [2]) ;

return 0 ;

}

assert (fread (src,1,0x200,i) >= 0x200) ;

assert (fread (dst,1,0x200,o) >= 0x200) ;

memcpy (src+3,dst+3,59) ;

rewind (o) ;

assert (fwrite (src,1,0x200,o) >= 0x200) ;

fclose (i) ;

fclose (o) ;

printf ("Boot sector from file \"%s\" successfully copied to image file \"%s\"\n", v [1], v [2]) ;

return 0 ;

}
