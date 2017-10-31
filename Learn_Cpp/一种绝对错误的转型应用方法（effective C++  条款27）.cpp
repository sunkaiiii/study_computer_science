#include<iostream>
class A
{
	int a=1;
public:
	void print()
	{
		std::cout << a << '\n';
	}
	virtual void func()
	{
		a= 1 + a;
	}
};

class B :public A
{
	int b=2;
public:
	virtual void func()
	{
    //错误的方法，此举调用的是转型动作所建立的*this对象的A部分的func（）方法
    //不会对本身这个对象上的数据有任何修改
    //整个func函数调用完成后，a=1，b=3，这个赋值操作是残缺的
    static_cast<A>(*this).func();
    // A::func(); /*正确的调用方法*/
		b=1 + b;
	}
	void print()
	{
		A::print();
    std::cout<<b<<"\n";
	}
};
int main()
{
  B b;
  b.func();
  b.print();
}
