#include<mutex>
#include<iostream>

std::mutex mutex;
class singleClass
{
private:
	static singleClass *instance;
	singleClass() = default;
public:
	void f()
	{
		std::cout << "out" << std::endl;
	}
	static singleClass* getInstance()
	{
		std::unique_lock<std::mutex> lck{ mutex };
		if (instance == nullptr)
		{
			instance = new singleClass();
		}
		lck.unlock();
		return instance;
	}
	virtual ~singleClass()
	{
		std::unique_lock<std::mutex> lck{ mutex };
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
		lck.unlock();
	}
};
singleClass* singleClass::instance = nullptr;

void f()
{
	singleClass *a = singleClass::getInstance();
}

int main()
{
	singleClass *a = singleClass::getInstance();
	singleClass *b = singleClass::getInstance();
	singleClass *c = a;
	f();
	std::cout << a << " " << b << " "<<c<<std::endl;
	a->f();

}
