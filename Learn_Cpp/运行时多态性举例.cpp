#include<iostream>
class A
{
public:
	virtual void func()
	{
		std::cout<<"A\n";
	}
	virtual void func2(int i=1)
	{
		std::cout<<"A "<<i<<"\n";
	}
	virtual ~A(){}
};
class B:public A
{
public:
	virtual void func() override //显示的著名覆盖了基类的虚函数
	{
		std::cout<<"B\n";
	}
	virtual void func2(int i=2)
	{
		std::cout<<"B "<<i<<"\n";
	}
	virtual ~B(){}
};

void print(A temp)
{
	temp.func();
}

//当传递的是引用或者指针并调用虚函数的时候
//就会发生动态绑定
void print_by_refrece(A &temp)
{
	temp.func();
}
void print(A *temp)
{
	temp->func();
}
int main()
{
	A a;
	B b;
	print(a);
	print(b);
	print_by_refrece(a);
	print_by_refrece(b);
	print(&a);
	print(&b);
	A *a2=new B;
	a2->func2(); //在这里，根据动态绑定，a2指向的是B，所以执行B的func2，但是默认实参是根据调用函数的静态类型决定的，所以这里是A对象的指针a2调用的func2，于是默认实参是1，输出B 1
	delete a2;
}
