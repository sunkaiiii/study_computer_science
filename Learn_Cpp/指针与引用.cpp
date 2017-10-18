#include<iostream>
/*引用和指针的区别
*在函数传递上，引用和指针对于形参的修改都会反应到对于形参的修改
不同之处在于指针传递传递的是这个实参地址的副本，即修改指针的地址之后是不会影响到原来的实参的
同时在sizeof上，指针传递sizeof出来是一个指针的大小，引用传递sizeof出来是原始对象的大小
传递上，传递指针允许null，引用不可以
同时引用其实相当于一个变量的别名，在声明之后必须紧跟着初始化，指针没有这个限制
引用在声明之后不可以改变引用的对象，在整个引用的生命周期内，它将一直引用着同一个对象
*/
struct c
{
	int a=1;
	int b=2;
	c()=default;
	c(int a,int b):a(a),b(b){}
	c &operator =(const c c2)=delete;
};
void print(struct c *c)
{
	std::cout<<sizeof(c)<<"\n";
	struct c c2(4,55);
	c=&c2; //在这里修改指针的值不会影响到实参内的地址
	c->b=24214; //指向了局部变量之后的指针的任何修改都不会再影响实参
}

void print(struct c &c)
{
	std::cout<<sizeof(c)<<"\n";
	struct c c2(4,5);
	c2.b=4;
	// c=c2; //赋值拷贝构造函数被删除，这句无法通过编译
	//&c=c2 //引用不可改变，不存在这种操作
}
int main()
{
	struct c c,c2(4,5);
	struct c &c3=c;
	std::cout<<"c:"<<&c<<" c2: "<<&c2<<" c3: "<<&c3<<"\n";
	// c3=c2; 赋值拷贝构造函数被删除，这句无法通过编译
	print(&c);
	print(c);
	std::cout<<"c:"<<&c<<" c2: "<<&c2<<" c3: "<<&c3<<"\n"; //可以看到c3和c的地址是一样的
}
