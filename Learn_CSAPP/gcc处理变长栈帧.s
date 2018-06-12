long vframe(long n,long idx,long *q){
    long i;
    long *p[n];
    p[0]=&i;
    for(i=1;i<n;i++){
        p[i]=q;
    }
    return *p[idx];
}

//gcc对于变长栈帧的处理

vframe:
.LFB0:
	pushq	%rbp //保存老的%rdb
	movq	%rsp, %rbp //设置基准指针
	subq	$16, %rsp //给局部变量i分配空间
	leaq	22(,%rdi,8), %rax 
	andq	$-16, %rax //计算所需要的空间
	subq	%rax, %rsp //给数组p分配空间
	leaq	7(%rsp), %rax
	shrq	$3, %rax
	leaq	0(,%rax,8), %r8 //p[0]
	movq	%r8, %rcx //让rcx=p[0]
	leaq	-8(%rbp), %r9
	movq	%r9, 0(,%rax,8)
	movq	$1, -8(%rbp)
	jmp	.L2
.L3:
	movq	%rdx, (%rcx,%rax,8) //p[i]=q
	addq	$1, -8(%rbp) //i++
.L2:
	movq	-8(%rbp), %rax //从栈里回复i
	cmpq	%rax, %rdi //判断i是否小于n
	jg	.L3
	movq	(%r8,%rsi,8), %rax
	movq	(%rax), %rax
	leave
	ret
