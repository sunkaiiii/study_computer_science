#include<iostream>
#include<algorithm>
class test
{
public:
	test(test &&s) noexcept //这是一个移动构造函数
	:a(s.a) //接管s当中的资源
	{
		std::cout<<"move constructer ";
	}
	test& operator=(test &&rv) //这是移动赋值构造函数
	{
		std::cout<<"move operator = ";
		a=rv.a;
		return *this;
	}
	test& operator=(test &rv)
	{
		std::cout<<"operator = ";
		a=rv.a;
		return *this;
	}
	test(const test &rv)
	{
		std::cout<<"copy constructer ";
		a=rv.a;
	}
	test(){}
	test(int a):a(a){}
public:
	int a;
};
int main()
{
	test a(4),b(7);
	a=std::move(b);
	std::cout<<a.a<<"\n";
	test c=std::move(b);
	std::cout<<c.a<<"\n";
	test d;
	d=a;
	std::cout<<d.a<<"\n";
	test e=a;
	std::cout<<e.a<<"\n";
}
