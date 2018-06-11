long P(long x,long y){
    long u=Q(y);
    long v=Q(x);
    return u+v;
}

P:
	pushq	%rbp
	pushq	%rbx
	subq	$8, %rsp
	movq	%rdi, %rbp 保存x的值
	movq	%rsi, %rdi 把y作为函数第一个参数
	movl	$0, %eax
	call	Q@PLT Q(y)
	movslq	%eax, %rbx 保存返回值
	movq	%rbp, %rdi 将x作为第一个参数
	movl	$0, %eax
	call	Q@PLT Q(y)
	cltq
	addq	%rbx, %rax u+v
	addq	$8, %rsp 恢复栈空间
	popq	%rbx
	popq	%rbp
	ret
