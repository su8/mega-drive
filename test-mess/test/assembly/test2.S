.section .data
output:
  .ascii "XXXXXXXXXXXX\n"
.section .text
.global main
main:
  movl $0, %eax
  cpuid
  movl $output, %edi
  movl %ebx, 0(%edi)
  movl %edx, 4(%edi)
  movl %ecx, 8(%edi)

  /* */
  movl $4, %eax      /* write */
  movl $1, %ebx      /* out */
  movl $output, %ecx /* low level "pointer" */
  movl $12, %edx     /* 12 bytes */
  int $0x80

/* exit */
  movl $1, %eax
  movl $0, %ebx
  int $0x80
