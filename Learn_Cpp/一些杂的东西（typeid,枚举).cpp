#include<iostream>
#include<typeinfo>
#include<vector>
class A
{
};
enum Tokens{INLINE=128,VIRTUAL=129};
enum Tokens2:unsigned char{INLINE2=128,VIRTUAL2=129};
void f1(unsigned char)
{
  std::cout << "f1 char" << '\n';
}
void f1(int)
{
  std::cout << "f1 int" << '\n';
}

void f1(Tokens)
{
  std::cout << "f1 Tokens" << '\n';
}

int main()
{
  /*一些有关typeid的用法*/
  A *a1=new A;
  std::cout<<typeid(*a1).name()<<std::endl;
  std::cout<<typeid(a1).name()<<std::endl;
  std::cout<<typeid(42).name()<<std::endl;
  std::cout<<typeid(std::string).name()<<std::endl;
  std::cout<<typeid(A).name()<<std::endl;
  std::cout<<typeid(std::vector<int>).name()<<std::endl;

  /*枚举类型与形参匹配*/
  unsigned char uc=VIRTUAL;
  f1(VIRTUAL);
  f1(uc);
  f1(INLINE2);
}
