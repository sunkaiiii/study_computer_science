#include<iostream>
#include<future>
#include<vector>
#include<random>
#include<time.h>
double accum(std::vector<double>::const_iterator begin, std::vector<double>::const_iterator end, double sum)
{
	for (;begin != end;++begin)
	{
		sum += *begin;
	}
	return sum;
}
double comp4(const std::vector<double>& v)
{
	if (v.size() < 10000)
	{
		std::cout << "normal\n";
		return accum(v.begin(), v.end(), 0.0);
	}
	std::cout << "comp4\n";
	auto v0 = v.begin();
	auto sz = v.size();

	auto f0 = std::async(accum, v0, v0 + sz / 4, 0.0);
	auto f1 = std::async(accum, v0 + sz / 4, v0 + sz / 2, 0.0);
	auto f2 = std::async(accum, v0 + sz / 2, v0 + sz * 3 / 4, 0.0);
	auto f3 = std::async(accum, v0 + sz * 3 / 4, v0 + sz, 0.0);
	
	return f0.get() + f1.get() + f2.get() + f3.get();
}

int main()
{
	std::default_random_engine re{static_cast<unsigned int>(time(NULL)) };
	std::uniform_real_distribution<double> random_num{ -500,500 };
	std::uniform_int<int> r{ 1000,10000 };
	int size = r(re);
	std::cout << "size=" << size << "\n";
	auto start_random = std::bind(random_num,re);

	std::vector<double> v(size);
	for (std::size_t i = 0; i < size; ++i)
	{
		v[i] = start_random();
	}
	std::cout << comp4(v);
}