#include<iostream>
#include<map>
#include<functional>
class test
{
public:
	int a,b,c;
public:
	test():a(0),b(0),c(0){}
	test(int a2,int b2,int c2):a(a2),b(b2),c(c2){}
	test operator+=(const test &t2) //重载+=运算符
	{
		this->a+=t2.a;
		this->b+=t2.b;
		this->c+=t2.c;
		return *this;
	}
	void operator() (void) const //重载()运算符
	{
		std::cout<<a<<" "<<b<<" "<<c;
	}
};

std::ostream &operator<<(std::ostream &os,const test &t) //重载输出流
{
	os<<t.a<<" "<<t.b<<" "<<t.c;
	return os;
}

std::istream &operator>>(std::istream &is,test &t) //重载输入流
{
	is>>t.a>>t.b>>t.c;
	if(!is)
		t=test();
	return is;
}

test operator+(const test &lhs,const test &rhs) //重载+
{
	test sum=lhs;
	sum+=rhs;
	return sum;
}

bool operator==(const test &lhs,const test &rhs) //重载==
{
	return lhs.a==rhs.a&&lhs.b==rhs.b&&lhs.c==rhs.c;
}

bool operator!=(const test &lhs,const test &rhs) //重载！=
{
	return !(lhs==rhs);
}

int add(const int a,const int b)
{
	return a+b;
}

struct divide
{
	int operator()(const int denminator,const int divisor)
	{
		return denminator/divisor;
	}
};

int main()
{
	test a;
	std::cin>>a;
	// std::cout<<a;
	test b;
	std::cin>>b;
	std::cout<<a+b<<"\n";
	std::string s=(a==b)?"true":"false";
	std::cout<<s<<"\n";
	a();
	std::cout<<"\n\n\n";

	auto mod=[](const int a,const int b){return a%b;};
	std::map<std::string,std::function<int(int,int)>> binops={ //定义一个函数表，使用function包含各个调用形式一样的函数
		{"+",add},
		{"-",std::minus<int>()},
		{"*",[](const int i,const int j){return i*j;}},
		{"/",divide()},
		{"%",mod}
	};
	std::cout<<binops["+"](10,5)<<"\n";
	std::cout<<binops["-"](10,5)<<"\n";
	std::cout<<binops["*"](10,5)<<"\n";
	std::cout<<binops["/"](10,5)<<"\n";
	std::cout<<binops["%"](10,5)<<"\n";
}
