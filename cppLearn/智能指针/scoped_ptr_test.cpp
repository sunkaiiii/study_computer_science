#include<iostream>
#include<cstring>
#include<boost/smart_ptr.hpp>
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
void test_scoped_ptr()
{
	boost::scoped_ptr<test_ptr> sp(new test_ptr(6, "test1"));
	sp.get()->show();
	sp.reset(new test_ptr(7, "test2")); //用法和auto_ptr是一样的
	sp.get()->show();
	//sp.release(); 错误，scoped没有release这个函数
}