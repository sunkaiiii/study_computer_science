/* floatcnv.c--不匹配的浮点型转换*/
#include<stdio.h>
int main(void)
{
    float n1=3.0;
    double n2=3.0;
    long n3 = 2000000000;
    long n4=1234567890;

    printf("%.1e %.1e %.1e %.1e\n", n1, n2, n3, n4); //.1e会认为double类型，读取8字节。而这里n3和n4都为4字节，所以printf查看n3之后还会查看n3相邻的4字节，共计8单元。
    printf("%ld %ld\n", n3, n4);
    printf("%ld %ld %ld %ld\n", n1, n2, n3, n4); //即使用对了转换说明也会发生错误的结果。因为%ld读取n1和n2的时候，n1对应double，%ld读取前4个字节为第一个值，这是n1的前半部分,然后第二个ld，读取到了n1的后半部分。于是以此类推第三第四个ld读取的n2的前半部分和后半部分.

    return 0;
}