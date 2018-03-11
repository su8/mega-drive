.code32
ProtectMode:
   movw $0x10,%ax
   movw %ax,%ds
   movw %ax,%es
   movw %ax,%ss

   xorl %esi,%esi
   movl $0x00001001,(,%esi,8)
   movl $0x00000000,4(,%esi,8)
   movl $0x100,%esi
   movl $0x00004001,0(,%esi,8)
   movl $0x00000000,4(,%esi,8)

   xorl %esi,%esi
   movl $0x00002001,0x1000(,%esi,8)
   movl $0x00000000,0x1004(,%esi,8)

   movl $0x00003001,0x2000(,%esi,8)
   movl $0x00000000,0x2004(,%esi,8)

   movl $256,%ecx
   movl $0x00000001,%ebx

NextPage_0x0000000000000000:   
   movl %ebx,0x3000(,%esi,8)
   movl $0x00000000,0x3004(,%esi,8)
   
   incl %esi
   addl $0x1000,%ebx
   decl %ecx
   jnz NextPage_0x0000000000000000

   xorl %esi,%esi
   movl $0x00005001,0x4000(,%esi,8)
   movl $0x00000000,0x4004(,%esi,8)

   movl $0x00006001,0x5000(,%esi,8)
   movl $0x00000000,0x5004(,%esi,8)

   movl $256,%ecx
   movl $0x00000001,%ebx

NextPage_0x0000800000000000:   
   movl %ebx,0x6000(,%esi,8)
   movl $0x00000000,0x6004(,%esi,8)
   
   incl %esi
   addl $4096,%ebx
   decl %ecx
   jnz NextPage_0x0000800000000000

   /*Enable PAE*/
   movl %cr4,%eax
   orl $0x20,%eax
   movl %eax,%cr4

   movl $0x0,%eax
   movl %eax,%cr3
   
   movl $0xc0000080,%ecx  /*EFER MSR number*/
   rdmsr                  /*Read EFER*/
   orl $0x100,%eax         /*Set LME=1*/
   wrmsr                  /*Write EFER*/

   /*Page Enable*/
   movl %cr0,%eax
   orl $0x80000001,%eax
   movl %eax, %cr0

   ljmp $0x08,$(0x90000+ProtectMode64)

.code64
ProtectMode64:
   movq $0x80000,%rsp
   movq $0x80000,%rbp

   pushq $0
   popfq

   lgdt gdt_80
   /*lidt idt_80*/
   
   movq   c_start(%rip),%rax
   pushq   $0      # fake return address to stop unwinder
   pushq   $0x10   # set correct cs
   pushq   %rax      # target address in negative space
   lret
       .....
      gdt64:
   .word 0,0,0,0

   .word 0xffff
   .word 0x0000
   .word 0xb000
   .word 0x0020

   .word 0x0000
   .word 0x0000
   .word 0xa000
   .word 0x0000

gdt_80:
   .word 0x8000
   .quad gdt64
