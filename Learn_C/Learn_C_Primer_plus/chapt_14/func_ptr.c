//func_ptr.c -- 使用函数指针
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LEN 81
char *s_gets(char *st, int n);
char showmenu(void);
void eatline(void);
void show(void(*fp)(char *),char *str);
void ToUpper(char *);
void ToLower(char *);
void Transpose(char *);
void Dummy(char *); 
//以上四个函数的声明都是相同的，所以他们都可以传递给show函数
int main(void)
{
    char line[LEN];
    char copy[LEN];
    char choice;
    void (*pfun)(char *); //声明一个函数指针，指向一个接受char*类型参数，无返回值的函数

    puts("Enter a string (empty line to quit):");
    while(s_gets(line,LEN)!=NULL&&line[0]!='\0')
    {
        while((choice=showmenu())!='n')
        {
            switch (choice)
            {
                case 'u': pfun = ToUpper;   break;                
                case 'l': pfun = ToLower;   break;                
                case 't': pfun = Transpose; break;                
                case 'o': pfun = Dummy;     break; 
            }
            strcpy(copy,line); //为show()函数拷贝一份
            show(pfun,copy);
        }
    }
    puts("Bye!");

    return 0;
}

char showmenu(void)
{
    char ans; 
    puts("Enter menu choice:"); 
    puts("u) uppercase       l) lowercase");
    puts("t) transposed case o) original case");
    puts("n) next string");
    ans = getchar();  // 获取用户的输入
    ans = tolower(ans); // 转换为小写
    eatline();   // 清理输入行
    while (strchr("ulton", ans) == NULL)
    {
        puts("Please enter a u, l, t, o, or n:"); 
        ans = tolower(getchar()); 
        eatline();
    }
    return ans;
}

void eatline(void)
{
    while (getchar() != '\n')
        continue;
}

void ToUpper(char *str)
{
    while(*str)
    {
        *str=toupper(*str);
        str++;
    }
}
void ToLower(char * str) 
{      
    while (*str)      
    {           
        *str = tolower(*str);           
        str++;      
    } 
} 
void Transpose(char * str) 
{      
    while (*str)      
    {           
        if (islower(*str))                
            *str = toupper(*str);           
        else if (isupper(*str))                
            *str = tolower(*str);          
        str++;      
    } 
}
void Dummy(char * str) 
{}

void show(void(*fp)(char *),char *str)
{
    fp(str);
    puts(str);
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;
    ret_val=fgets(st,n,stdin);
    if(ret_val)
    {
        find=strchr(st,'\n'); //查找换行符
        if(find)
            *find='\0';
        else
        {
            while(getchar()!='\n')
                continue; //处理输入行的剩余字符
        }
        
        return ret_val;
    }
}