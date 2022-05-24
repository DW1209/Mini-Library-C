%macro gensys 2
	global sys_%2:function
sys_%2:
	push 	r10
	mov 	r10, rcx
	mov 	rax, %1
	syscall 
	pop 	r10
	ret
%endmacro

; RDI, RSI, RDX, RCX, R8, R9

extern	errno

	section .data

	section .text

	gensys	0, 		read
	gensys  1, 		write
	gensys	2, 		open
	gensys	3, 		close
	gensys	9, 		mmap
	gensys	10, 	mprotect
	gensys	11, 	munmap
	gensys	13, 	rt_sigaction
	gensys	14, 	rt_sigprocmask
	gensys	22, 	pipe
	gensys	32, 	dup
	gensys	33, 	dup2
	gensys  34, 	pause
	gensys	35, 	nanosleep
	gensys	37, 	alarm
	gensys	57, 	fork
	gensys  60, 	exit
	gensys	79, 	getcwd
	gensys	80, 	chdir
	gensys	82, 	rename
	gensys	83, 	mkdir
	gensys	84, 	rmdir
	gensys	85, 	creat
	gensys	86, 	link
	gensys	88, 	unlink
	gensys	89, 	readlink
	gensys	90, 	chmod
	gensys	92, 	chown
	gensys	95, 	umask
	gensys	96, 	gettimeofday
	gensys	102, 	getuid
	gensys	104, 	getgid
	gensys	105, 	setuid
	gensys	106, 	setgid
	gensys	107, 	geteuid
	gensys	108, 	getegid
	gensys	127, 	rt_sigpending

	global open:function
open:
	call 	sys_open
	cmp 	rax, 0
	jge 	open_success	; no error
open_error:
	neg 	rax
%ifdef NASM
	mov 	rdi, 	[rel errno wrt ..gotpc]
%else
	mov 	rdi, 	[rel errno wrt ..gotpcrel]
%endif
	mov 	[rdi], 	rax		; errno = -rax
	mov 	rax, 	-1	
	jmp 	open_quit
open_success:
%ifdef NASM
	mov 	rdi, 			[rel errno wrt ..gotpc]
%else
	mov 	rdi, 			[rel errno wrt ..gotpcrel]
%endif
	mov 	QWORD[rdi], 	0 	; errno = 0
open_quit:
	ret

	global sigreturn:function
sigreturn:
	mov		rax, 	15
	syscall

	global setjmp:function
setjmp:
	push 	rbp
	mov 	rbp, 				rsp

	; set jmp_buf[8]
	mov 	QWORD [rdi], 		rbx 		; jmp_buf[0] = rbx
	lea 	r10, 				[rbp + 16]
	mov 	QWORD [rdi + 8], 	r10 		; jmp_buf[1] = rsp
	mov 	r10, 				[rbp]
	mov 	QWORD [rdi + 16], 	r10 		; jmp_buf[2] = rbp
	mov 	QWORD [rdi + 24], 	r12 		; jmp_buf[3] = r12
	mov 	QWORD [rdi + 32], 	r13 		; jmp_buf[4] = r13
	mov 	QWORD [rdi + 40], 	r14 		; jmp_buf[5] = r14
	mov 	QWORD [rdi + 48], 	r15 		; jmp_buf[6] = r15
	mov 	r10, 				[rbp + 8]
	mov 	QWORD [rdi + 56], 	r10			; jmp_buf[7] = return address

	; set sigmask
	push 	rdi
	sub 	rsp, 				8
	mov 	rdi, 				1 			; 1st argument (rdi) = SIG_UNBLOCK
	mov 	rsi, 				0 			; 2nd argument (rsi) = NULL
	mov 	rdx, 				rsp 		; 3rd argument (rdx) = sigmask
	mov 	rcx, 				8 			; 4th argument (rcx) = sizeof(sigset_t)
	call 	sys_rt_sigprocmask
	mov 	r10, 				[rsp]
	add 	rsp, 				8
	pop 	rdi
	mov 	QWORD [rdi + 64], 	r10 		; mask = sigmask

	mov 	rsp, 				rbp
	pop 	rbp

	; set return value
	mov 	rax, 				0 			; return 0
	ret

	global longjmp:function
longjmp:
	push 	rbp
	mov 	rbp, 				rsp

	; recover sigmask
	push 	rdi
	push 	rsi	
	mov		r10,				[rdi + 64]
	mov 	rdi, 				2 			; 1st argument (rdi) = SIG_SETMASK
	mov 	rsi, 				r10 		; 2nd argument (rsi) = sigmask
	mov 	rdx, 				0			; 3rd argument (rdx) = NULL	
	mov 	rcx, 				8 			; 4th argument (rcx) = sizeof(sigset_t)
	call 	sys_rt_sigprocmask
	pop 	rsi
	pop 	rdi

	; recover from jmp_buf[8]
	mov 	QWORD rbx, 			[rdi] 		; rbx = jmp_buf[0]
	mov 	QWORD rsp, 			[rdi + 8] 	; rsp = jmp_buf[1]
	mov 	QWORD rbp, 			[rdi + 16] 	; rbp = jmp_buf[2]
	mov 	QWORD r12, 			[rdi + 24] 	; r12 = jmp_buf[3]
	mov 	QWORD r13, 			[rdi + 32] 	; r13 = jmp_buf[4]
	mov 	QWORD r14, 			[rdi + 40] 	; r14 = jmp_buf[5]
	mov 	QWORD r15, 			[rdi + 48] 	; r15 = jmp_buf[6]
	mov 	rax, 				rsi
	mov 	QWORD r10, 			[rdi + 56]
	jmp 	r10 							; jump to jmp_buf[7]

	; return (ignored)
	ret
