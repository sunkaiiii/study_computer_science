#include<iostream>
#include<cstring>
#include<memory>
class test_ptr
{
private:
	int a;
	std::string str;
public:
	test_ptr() :a(1), str("default") {}
	test_ptr(int a, std::string s) :
		a(a),
		str(s)
	{}
	void show()
	{
		std::cout << a << " " << str.data() << std::endl;
	}
	~test_ptr()
	{
		std::cout << str.data() << " xigou" << std::endl;
	}
};
void auto_ptr_test()
{
	test_ptr a; //默认构造函数
	std::string s = "testb";
	test_ptr b(4, s);  //带参数的构造函数
	std::auto_ptr<test_ptr> my_ptr(new test_ptr(5, "testc"));  //智能指针
	std::string s2 = "testd";
	test_ptr *d = new test_ptr(6, s2); //一般的new
	a.show();
	b.show();
	my_ptr.get()->show();
	d->show();
	(*my_ptr).show();
	//delete d;
	/*
	释放auto_ptr的内部资源
	*/
	if (my_ptr.get())
	{
		my_ptr.reset(); //释放内存
						/*也可以使用
						test_ptr *tp=my_ptr.release();
						or
						auto *tp=my_ptr.release();
						delete tp;
						*/
	}
	/*
	reset另一种用法
	*/
	s = "teste";
	my_ptr.reset(new test_ptr(7, s));
	(*my_ptr).show();
	s = "testf";
	my_ptr.reset(new test_ptr(8, s)); //释放当前管理的对象，装入传递的新对象
	(*my_ptr).show();
	delete d;
}