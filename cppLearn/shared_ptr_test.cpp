#include<iostream>
#include<cstring>
#include"share_ptr_test.h"
/*
与scoped_ptr和auto_ptr的独享不同
share_ptr是专们迎来共享所有权的，既可以使用复制操作
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
};
void TestSharePtr(boost::shared_ptr<test_ptr> memory)//无需使用reference（或const，reference）
{
	memory->show();
	std::cout << "TestSharedPtr2 count " << memory.use_count() << std::endl;
}
void goTestShare_ptr()
{
	boost::shared_ptr<test_ptr> share_memory(new test_ptr(1, "test1"));
	if (share_memory.get())
	{
		share_memory->show();
		(*share_memory).show();
	}
	std::cout << "TestSharedPtr2 count " << share_memory.use_count() << std::endl;
	TestSharePtr(share_memory);
	std::cout << "TestSharedPtr2 count " << share_memory.use_count() << std::endl;
}
