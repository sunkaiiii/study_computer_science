#define N 16
typedef int fix_matrix[N][N];

int fix_prod_ele(fix_matrix A,fix_matrix B,long i,long k){
    long j;
    int result=0;

    for(j=0;j<N;j++){
        result+=A[i][j]*B[j][k];
    }
    return result;
}

经过O1优化过的汇编代码

.LFB0:
	salq	$6, %rdx 计算64*i
	addq	%rdx, %rdi 局部变量pa到a[i][0]
	salq	$2, %rcx 
	leaq	(%rsi,%rcx), %rdx 局部变量pb定位到b[0][k]
	leaq	1024(%rsi,%rcx), %rsi 定位局部变量到数组尾部
	movl	$0, %eax
.L2:
	movl	(%rdi), %ecx 读取pa
	imull	(%rdx), %ecx 相乘
	addl	%ecx, %eax  结果相加
	addq	$4, %rdi pa累加
	addq	$64, %rdx pb累加数组一行的长度
	cmpq	%rsi, %rdx 比较是否到了数组结果
	jne	.L2
	rep ret


优化过的代码等同于
int fix_prod_ele(fix_matrix A,fix_matrix B,long i,long K){
   int *pa=&A[i][0];
   int *pb=&B[0][K];
   int *end=&B[N][K];
   int result=0;
   do{
       result+=*pa**pb;
       pa++;
       pb+=N;
   }while(pb!=end);
   return result;
}