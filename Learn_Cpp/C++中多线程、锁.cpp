#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<string>
std::mutex m;
std::condition_variable mcond;
std::string s;
void f()
{
	std::unique_lock<std::mutex> lck{ m }; //获得锁
	mcond.wait(lck); //等待mcond唤醒，此时，会释放锁
	std::string s2 = s;
	std::cout << "function f()\n";
	std::cout << "获取的信息是:"<<s2 << "\n";
	lck.unlock(); //输出完成，释放锁
}
struct F
{
	void operator()();
};
void F::operator()()
{
	std::unique_lock<std::mutex> lck{ m }; //获得锁
	std::cout << "Struct operator f()\n请输入信息:";
	std::cin >> s; //输入信息
	mcond.notify_one(); //唤醒某一个mcond
	lck.unlock(); //释放锁，以让另外一个线程启动
}

void start()
{
	std::thread t1{ f}; //两个线程
	std::thread t2{ F() };

	t1.join();
	t2.join();
}
int main()
{
	start();
}
