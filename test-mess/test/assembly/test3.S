#cpuinfo.s Sample program to extract processor Info
#Author: Rossano Pablo Pinto
.section .data
vendor:
   .ascii "The processor Vendor ID is 'xxxxxxxxxxxx'\n"        # 42 bytes
brand: 
   .ascii "                                                \n" # 49 bytes
	
.section .text
.globl main
main:
	nop
	call vendorid
	call modelname
	call myexit
			
vendorid:
	########### VENDOR ID OPTION OF cpuid		
	mov  $0, %eax
	cpuid
	########### PUT ADDRESS OF vendor variable INTO edi REGISTER
	movl $vendor, %edi
	movl %ebx, 28(%edi)   
	movl %edx, 32(%edi)
	movl %ecx, 36(%edi)
	########### CALL LINUX PRINT SERVICE - SYSTEM CALL
	movl $4, %eax
	movl $1, %ebx
	movl $vendor, %ecx   ## POINTER TO START OF STRING
	movl $42, %edx       ## STRING SIZE
	int  $0x80
	ret
	
modelname:	
	movl $brand, %edi
	
	movl $0x80000002, %eax
	cpuid
	movl %eax, 0(%edi)
	movl %ebx, 4(%edi)
	movl %ecx, 8(%edi)
	movl %edx, 12(%edi)
	
	movl $0x80000003, %eax
	cpuid
	movl %eax, 16(%edi)
	movl %ebx, 20(%edi)
	movl %ecx, 24(%edi)
	movl %edx, 28(%edi)

	movl $0x80000004, %eax
	cpuid
	movl %eax, 32(%edi)
	movl %ebx, 36(%edi)
	movl %ecx, 40(%edi)
	movl %edx, 44(%edi)

        ########### CALL LINUX PRINT SERVICE - SYSTEM CALL
	movl $4, %eax      ##### WRITE SYSCALL
	movl $1, %ebx      ##### STDOUT
	movl $brand, %ecx
	movl $49, %edx     ## POINTER TO START OF STRING
	int  $0x80         ## STRING SIZE
	ret
	
	
myexit:			
	########### CALL LINUX EXIT SERVICE - SYSTEM CALL
	movl $1, %eax      ##### EXIT SYSCALL
	movl $0, %ebx      ##### EXIT CODE OF 0
	int  $0x80
