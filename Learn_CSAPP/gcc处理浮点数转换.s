double fcvt(int i,float *fp,double *dp,long *lp){
    float f=*fp;
    double d=*dp;
    long l=*lp;
    *lp=(long)d;
    *fp=(float)i;
    *dp=(double)l;
    return (double)f;
}

//gcc处理浮点数转换

.LFB0:
	movss	(%rsi), %xmm0 //f=*fp 传送单精度
	movq	(%rcx), %rax //获得l
	cvttsd2siq	(%rdx), %r8 //截断方式获得d=*dp
	movq	%r8, (%rcx) //lp=(long)d
	pxor	%xmm1, %xmm1 //
	cvtsi2ss	%edi, %xmm1 //把i转换为float
	movss	%xmm1, (%rsi) //fp=i
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm1 //l转换为double
	movsd	%xmm1, (%rdx) //dp=l
	cvtss2sd	%xmm0, %xmm0 //单精度转双精度
	ret

