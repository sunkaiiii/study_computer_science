double funct(double a,float x,double b,int i){
    return a*x-b/i;
}

//浮点数运算简单实例

.LFB0:
	cvtss2sd	%xmm1, %xmm1 //x转双精度
	mulsd	%xmm1, %xmm0 //a*b
	pxor	%xmm1, %xmm1
	cvtsi2sd	%edi, %xmm1 //i转双精度
	divsd	%xmm1, %xmm2 //b/i
	subsd	%xmm2, %xmm0 //a*b-b/i
	ret
