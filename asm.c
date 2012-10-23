#include <stdio.h>
// disassembly exercise

#define get_seg_byte(seg,addr) ({ \
    register unsigned int __res; \
    __asm__("leal 7(%%ebx, %%ebx, 2), %%eax" \
        :"=a" (__res):"b" (seg),"m" (*(addr))); \
    __res;})

#define get_seg_mov(seg,addr) ({ \
    register unsigned int  __res; \
    __asm__("movl %2, %%eax" \
        :"=a" (__res):"0" (seg),"m" (*(addr))); \
    __res;})

int main(void)
{
  unsigned int a = 0x400440;
  printf("%x\n", &a);
  //unsigned int *res = get_seg_byte(0x400440, &a);
  //printf("%x\n", *res);
  unsigned int res3 = get_seg_byte(2, &a);
  printf("%x\n", res3);
  printf("%x\n", a);
  //printf("%x\n", *(unsigned int *)(res3));
  unsigned int res2 = get_seg_mov(2, &a);
  printf("res2 %x\n", res2);

  return 0;
}
