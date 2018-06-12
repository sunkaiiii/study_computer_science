double func(int *ip,float *fp,double *dp,long l){
    int i=*ip;
    float f=*fp;
    double d=*dp;
    *ip=(int)val1;
    *fp=(float)val2;
    *dp=(double)val3;
    return (double)val4;
}

//一个练习题

.LFB0:
	movl	(%rdi), %eax
	movss	(%rsi), %xmm0
	cvttsd2si	(%rdx), %r8d
	movl	%r8d, (%rdi)
	pxor	%xmm1, %xmm1
	cvtsi2ss	%eax, %xmm1
	movss	%xmm1, (%rsi)
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rcx, %xmm1
	movsd	%xmm1, (%rdx)
	cvtss2sd	%xmm0, %xmm0
	ret


val1-val4分别是d,i,l,f