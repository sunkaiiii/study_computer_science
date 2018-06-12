float float_mov(float v1,float *src,float *dst){
    float v2=*src;
    *dst=v1;
    return v2;
}

//简单的浮点数操作

.LFB0:
	movss	(%rdi), %xmm1 //保存src
	movss	%xmm0, (%rsi) //写入v1到dst
	movaps	%xmm1, %xmm0 //src写入v2，并作为返回值
	ret
