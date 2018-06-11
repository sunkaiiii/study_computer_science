struct rec{
    int i;
    int j;
    int a[2];
    int *p;
};

void test(struct rec *r){
    r->p=&r->a[r->i+r->j];
}
汇编中，对于结构体的操作

.LFB0:
	.cfi_startproc
	movl	4(%rdi), %eax 获取j
	addl	(%rdi), %eax j+i
	cltq
	leaq	8(%rdi,%rax,4), %rax r->a[j+i]
	movq	%rax, 16(%rdi) r->p
	ret
