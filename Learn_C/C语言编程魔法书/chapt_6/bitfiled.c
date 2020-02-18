/*bitfiled.c -- 位域*/
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    enum MyEnum
    {
        ENUM1,
        ENUM2,
        ENUM3
    };
    struct MyStruct
    {
        int32_t a:6 ; //a的范围[-32,31]
        int16_t b:5;  //b的范围[-16,15]
        int8_t c:8; //c的范围[-128,127]

        char x:sizeof(enum MyEnum); //相当于char x:4
        bool y :1;

        enum  MyEnum e:ENUM3 //相当于:enum MyEnum e:2
    }s={0x18,0x0a,0x77,'\0',true,ENUM3};
    printf("The size is: %zu\n",sizeof(s));
    //输出0x50770298
    printf("The content of s is :0x%.8x\n",*(u_int32_t*)&s);

    return 0;
}