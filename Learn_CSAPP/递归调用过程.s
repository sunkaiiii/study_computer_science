long rfact(long n){
    long result;
    if(n<=1)
        result=1;
    else
        result=n*rfact(n-1);
    return result;
}

.LFB0:
	cmpq	$1, %rdi
	jle	.L3
	pushq	%rbx 保存rbx
	movq	%rdi, %rbx 保存n
	leaq	-1(%rdi), %rdi n-1
	call	rfact rfact(n-1)
	imulq	%rbx, %rax n*nfact(n-1)
	popq	%rbx
	ret
.L3:
	movl	$1, %eax
	ret
