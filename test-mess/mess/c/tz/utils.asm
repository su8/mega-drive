;+---------------------------------------------------------------------------
; utils.asm 
;
; GetCpuID() executes the cpuid instruction. 
; Called from main.c

; Built using the nasm assembler for x86_64 Linux.
; Minor changes are needed for a 32bit x86 Linux.
; 
; nasm -Wall -f elf64 -o utils.o utils.asm
; gcc -Wall -c -o main.o main.c
; gcc -Wall -o cpuid main.o utils.o
;+---------------------------------------------------------------------------

global vendor_id, input, GetCpuID

section .bss 

vendor_id resd 12 ;reserve 12 bytes of memory

section .text

GetCpuID:

; get vendor id 
mov eax,0
cpuid
mov [vendor_id],ebx
mov [vendor_id+4],edx
mov [vendor_id+8],ecx

ret
