	.file	"counter_cas_lock.cc"
	.text
	.p2align 4,,15
	.globl	_Z12my_lock_corev
	.type	_Z12my_lock_corev, @function
_Z12my_lock_corev:
.LFB2713:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	Mutex(%rip), %eax
	cmpl	$1, %eax
	movl	%eax, 12(%rsp)
	je	.L7
	movl	$1, %edx
	lock cmpxchgl	%edx, Mutex(%rip)
	sete	%al
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	.cfi_restore_state
	movl	$1, %edi
	call	usleep
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2713:
	.size	_Z12my_lock_corev, .-_Z12my_lock_corev
	.p2align 4,,15
	.globl	_Z6workerPv
	.type	_Z6workerPv, @function
_Z6workerPv:
.LFB2716:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$10000000, %ebx
	.p2align 4,,10
	.p2align 3
.L10:
	call	_Z12my_lock_corev
	testb	%al, %al
	je	.L10
	addl	$1, Counter(%rip)
	subl	$1, %ebx
	movl	$0, Mutex(%rip)
	mfence
	jne	.L10
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2716:
	.size	_Z6workerPv, .-_Z6workerPv
	.p2align 4,,15
	.globl	_Z9my_unlockv
	.type	_Z9my_unlockv, @function
_Z9my_unlockv:
.LFB2714:
	.cfi_startproc
	movl	$0, Mutex(%rip)
	mfence
	ret
	.cfi_endproc
.LFE2714:
	.size	_Z9my_unlockv, .-_Z9my_unlockv
	.p2align 4,,15
	.globl	_Z7my_lockv
	.type	_Z7my_lockv, @function
_Z7my_lockv:
.LFB2715:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	.p2align 4,,10
	.p2align 3
.L17:
	call	_Z12my_lock_corev
	testb	%al, %al
	je	.L17
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2715:
	.size	_Z7my_lockv, .-_Z7my_lockv
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"ERROR"
.LC1:
	.string	"counter_cas_lock.cc"
.LC2:
	.string	"%16s %4d %16s\n"
.LC3:
	.string	"Counter: %u (Ref. %u)\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB2717:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	xorl	%esi, %esi
	movl	$Lock, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$88, %rsp
	.cfi_def_cfa_offset 112
	call	pthread_mutex_init
	cmpl	$-1, %eax
	je	.L26
	leaq	80(%rsp), %rbp
	movq	%rsp, %rbx
	.p2align 4,,10
	.p2align 3
.L22:
	xorl	%ecx, %ecx
	xorl	%esi, %esi
	movq	%rbx, %rdi
	movl	$_Z6workerPv, %edx
	addq	$8, %rbx
	call	pthread_create
	cmpq	%rbp, %rbx
	jne	.L22
	movq	%rsp, %rbx
	.p2align 4,,10
	.p2align 3
.L24:
	movq	(%rbx), %rdi
	xorl	%esi, %esi
	addq	$8, %rbx
	call	pthread_join
	cmpq	%rbx, %rbp
	jne	.L24
	movl	Counter(%rip), %edx
	movl	$100000000, %ecx
	movl	$.LC3, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L26:
	.cfi_restore_state
	movl	$.LC0, %edi
	call	perror
	movq	stderr(%rip), %rdi
	movl	$_ZZ4mainE8__func__, %r9d
	movl	$45, %r8d
	movl	$.LC1, %ecx
	movl	$.LC2, %edx
	movl	$1, %esi
	xorl	%eax, %eax
	call	__fprintf_chk
	movl	$1, %edi
	call	exit
	.cfi_endproc
.LFE2717:
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I_Counter, @function
_GLOBAL__sub_I_Counter:
.LFB2916:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE2916:
	.size	_GLOBAL__sub_I_Counter, .-_GLOBAL__sub_I_Counter
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_Counter
	.section	.rodata
	.type	_ZZ4mainE8__func__, @object
	.size	_ZZ4mainE8__func__, 5
_ZZ4mainE8__func__:
	.string	"main"
	.globl	Mutex
	.bss
	.align 4
	.type	Mutex, @object
	.size	Mutex, 4
Mutex:
	.zero	4
	.globl	Lock
	.align 32
	.type	Lock, @object
	.size	Lock, 40
Lock:
	.zero	40
	.globl	Counter
	.align 4
	.type	Counter, @object
	.size	Counter, 4
Counter:
	.zero	4
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.4) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
