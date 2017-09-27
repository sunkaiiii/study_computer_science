#include<iostream>
#include<list>
template <class T>
T f(const T t1,const T t2)
{
	std::cout<<"normal template "<<t1<<" "<<t2<<std::endl;
}
template<>
const char* f(const char *a,const char *b)
{
	std::cout<<"tehua template "<<a<<" "<<b<<std::endl;
}
template <class T2>
void f(T2 t1)
{
	std::cout<<"normal template2 "<<t1<<std::endl;
}
template<>
void f(double c)
{
	std::cout<<"tehua double moban"<<c<<std::endl;
}
void f(int a,int b)
{
	std::cout<<"putong hanshu "<<a<<" "<<b<<std::endl;
}
void f(double c)
{
	std::cout<<"double hanshu"<<c<<std::endl;
}
int main()
{
	f(1,2);
	f(1.1,1.2);
	const char a[]="asdasd";
	const char b[]="123";
	f(a,b);
	char c[]="1";
	char d[]="e";
	f(c,d);
	double d2=1.23123;
	f(d2);
}
