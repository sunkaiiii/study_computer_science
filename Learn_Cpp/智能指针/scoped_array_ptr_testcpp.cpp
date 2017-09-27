#include"scoped_array_ptr_test.h"
/*
用于管理动态数组的智能指针
*/
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
	void extendString(std::string ex)
	{
		str += ex;
	}
};
void TestScopedArray_ptr()
{
	boost::scoped_array<test_ptr> array_memory(new test_ptr[3]);
	if (array_memory.get())
	{
		array_memory[0].show();
		array_memory[0].extendString("add_string");
		array_memory[0].show();
		
		boost::scoped_array<test_ptr> array_memory2;
		//编译不通过，没有重载‘=’ array_memory2 = array_memory;
		//scoped_array也是不支持复制，初始化的时候需要使用动态数组，并且没有重载'*'
	}
}
