#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b)
{
  int64_t res;
  asm("addq %%rbx, %%rax;" : "=a"(res) : "a"(a), "b"(b));
  return res;
}

int asm_popcnt(uint64_t x)
{
  int result = 0;
  asm volatile(
      "1: \n\t"
      "test %1, %1 \n\t"
      "jz 2f \n\t"
      "shr $1, %1 \n\t"
      "adc $0, %0 \n\t"
      "jmp 1b \n\t"
      "2: \n\t"
      : "+r"(result), "+r"(x)
      :
      : "cc");
  return result;
}

void *asm_memcpy(void *dest, const void *src, size_t n)
{
  asm volatile(
      "rep movsb"
      : "+D"(dest), "+S"(src), "+c"(n)
      :
      : "memory");
  return dest;
}

int asm_setjmp(asm_jmp_buf env)
{
  asm volatile(
      "mov %%rbx, (%[buf])\n\t"
      "mov %%rbp, 8(%[buf])\n\t"
      "mov %%r12, 16(%[buf])\n\t"
      "mov %%r13, 24(%[buf])\n\t"
      "mov %%r14, 32(%[buf])\n\t"
      "mov %%r15, 40(%[buf])\n\t"
      "lea 8(%%rsp), %%rdx\n\t"
      "mov %%rdx, 48(%[buf])\n\t"
      "mov (%%rsp), %%rdx\n\t"
      "mov %%rdx, 56(%[buf])\n\t"
      "xor %%eax, %%eax\n\t"
      :
      : [buf] "r"(env));
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val)
{
  int result;
  asm volatile(
      "xor %%eax, %%eax\n\t"
      "cmp $1, %%esi\n\t"
      "adc %%esi, %%eax\n\t"
      "mov (%[buf]), %%rbx\n\t"
      "mov 8(%[buf]), %%rbp\n\t"
      "mov 16(%[buf]), %%r12\n\t"
      "mov 24(%[buf]), %%r13\n\t"
      "mov 32(%[buf]), %%r14\n\t"
      "mov 40(%[buf]), %%r15\n\t"
      "mov 48(%[buf]), %%rsp\n\t"
      "jmp *56(%[buf])\n\t"
      : "=a"(result)
      : [buf] "r"(env), "S"(val));
}
