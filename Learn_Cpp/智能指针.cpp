#include<iostream>
#include<memory>
#include<vector>
class StrBlob
{
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob(){}
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const{return data->size();}
	bool empty() const{return data->empty();}
	void push_back(const std::string &t){data->push_back(t);}
	void pop_back();

	std::string& front();
	std::string& back();
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i,const std::string &msg) const;
};

StrBlob::StrBlob(std::initializer_list<std::string> il):data(std::make_shared<std::vector<std::string>>(il))
{

}

void StrBlob::check(size_type i,const std::string &msg) const
{
	if(i>=data->size())
		throw "out of range "+msg;
}

std::string& StrBlob::back()
{
	check(0,"back on empty StrBlob");
	return data->back();
}

std::string& StrBlob::front()
{
	check(0,"front on empty StrBlob");
	return data->front();
}

void StrBlob::pop_back()
{
	check(0,"pop_back on empty StrBlob");
	data->pop_back();
}

int main()
{
	//初始化一个智能指针
	std::shared_ptr<int> p3=std::make_shared<int>(42); //指向一个值为42的int的shared_ptr
	std::shared_ptr<std::string> p4=std::make_shared<std::string>(10,'9'); //p4指向一个值为“9999999”的string
	auto p5=std::make_shared<std::string>(); //使用auto简化分配
	std::cout<<*p3<<"\n"<<*p4<<"\n"<<*p5<<"\n";
	auto p6(p3);//现在，p6和p3指向同一个对象
	std::cout<<p6.use_count()<<"\n"; //查看与p共享对象的智能指针的数量，可能较慢，用于调试

	//测试StrBlob类
	StrBlob str({"123","234"}); //使用初始化列
	StrBlob str2; //使用默认构造函数
	StrBlob b1;
	{
		StrBlob b2={"a","an","the"};
		b1=b2;  //b1的计数器减1为0，b1原对象销毁
		b2.push_back("about");
		std::cout<<"b1:"<<b1.size()<<"\n"<<"b2:"<<b2.size()<<"\n";
	}
	std::cout<<"b2 destroy,b1 size:"<<b1.size()<<"\n";

	/*资源的动态申请与释放*/
	for(int i=0;i<10;i++){
		int *b=new int[10000000]{0};
		delete[] b;
	}

	int *c=new int(42);
	std::shared_ptr<int> sp(c);
	//std::shared_ptr<int> sp=std::make_shared<int>(42);
	/*不要删除由get而得来的指针，这会导致原智能指针出现未定义错误
	int *test=sp.get();
	delete test;
	*/
	/*不要使用相同的内置指针初始化多个智能指针，这会导致当某个智能指针失效后，其他全部的指针将指向未定义区域
	std::shared_ptr<int> sp2(c);
	sp2=sp;
	*/
	/*不要使用get()初始化或者reset另一个智能指针，这同样会导致当某个智能指针销毁后，另外一个指针会指向未定义区域
	std::shared_ptr<int> sp2(sp.get());
	sp=sp2;
	*/
	/*如果你使用get()返回的指针，当最后一个对应的智能指针销毁后，你的指针就变得无效了
	auto i=sp.get();
	std::cout<<*i<<std::endl;
	sp=p3; //现在sp的引用计数为0，原指针被释放，现在i也将失效
	std::cout<<*i<<std::endl;
	*/
	std::cout<<*sp<<std::endl;

	/*unique_ptr相关*/
	std::unique_ptr<int> p1(new int(42));
	std::cout<<"unique_ptr: int locate:"<<p1.get()<<" value:"<<*p1<<"\n";
	std::unique_ptr<int> p2(p1.release()); //将所有权从p1转移给p2
	std::cout<<"p2 int locate"<<p2.get()<<" value:"<<*p2<<"\n";
	std::unique_ptr<int> p8;
	p8.reset(p2.release()); //将所有权从p2转移到p3
	std::cout<<"p8 int locate:"<<p8.get()<<" value:"<<*p8<<"\n";
}
