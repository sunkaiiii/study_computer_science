#include"share_array_test.h"
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
void TestSharedArray(boost::shared_array<test_ptr> memory)
{
	std::cout << "TestSharedArray UseCount: " << memory.use_count() << std::endl;
}

void TestShareArray2()
{
	boost::shared_array<test_ptr> my_memory(new test_ptr[2]);
	if (my_memory.get())
	{
		my_memory[0].show();
		my_memory.get()[0].extendString("extend");
		my_memory[0].show();
		my_memory[1].show();
		my_memory.get()[1].extendString("extengd2");
		my_memory[1].show();
	}
	std::cout << "TestSharedArray2 UserCount " << my_memory.use_count() << std::endl;
	TestSharedArray(my_memory);
	std::cout << "TestSharedArray2 UseCount" << my_memory.use_count() << std::endl;
}