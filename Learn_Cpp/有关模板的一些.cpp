#include<iostream>
#include<vector>
#include<memory>
#include<functional>
#include<utility>
template <typename T> class Blob
{
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	//构造函数
	Blob();
	Blob(std::initializer_list<T> il);
	//Blob中的元素数目
	size_type size() const{return data->size();}
	bool empty() const { return data->empty();}
	//添加和删除元素
	void push_back(const T &t){ data->push_back(t); }
	void push_back(T &&t){ data->push_back(std::move(t)); }
	void pop_back();
	//元素访问
	T& back();
	T& operator[](size_type i);
private:
	std::shared_ptr<std::vector<T>> data;
	//若data[i]无效，则跑出msg
	void check(size_type i,const std::string &msg) const;
};

/*
*模板的默认实参，名为F的一个可调用类型，并用一个函数参数f绑定到了一个可调用对象上
*调用的时候如果不做说明，则调用less
*/
template <typename T=int,typename F=std::less<T>> //模板默认为int
int compare(const T &v1,const T &v2,F f=F())
{
	return 1;
}

class DebugDelete
{
private:
	std::ostream &os;
public:
	DebugDelete(std::ostream &s=std::cerr):os(s){}
	template<typename T> void operator()(T *p) const
	{
		os<<"delete!"<<std::endl;
		delete p;
	}
};


template<typename T> T fcn(T val)
{
	val=3;
	return val;
}
//当用右值调用的时候，局部变量t是int，当对t进行赋值的时候，val保持不变
//当用左值调用的时候，t是&int，因此t初始化绑定了val，对t的修改也会体现在val上，val==t也为true
template<typename T> void f3(T&& val)
{
	T t=val;
	t=fcn(t);
	if(val==t)
		std::cout<<"true\n";
	else
		std::cout<<"false\n";
}

template<typename F,typename T1,typename T2>
void flip(F f,T1 &&t1,T2 &&t2)
{
	//forward函数它能够保持原始实参的类型，类似std::move
	//forward返回改显示实参的右值引用
	//如果实参是一个普通类型，则返回Type&&
	//如果实参是一个左值，则通过引用折叠，返回一个指向左值引用的右值引用
	f(std::forward<T2>(t2),std::forward<T1>(t1));
}

void f(int v1,int &v2)
{
	std::cout<<v1<<" "<<++v2<<std::endl;
}

int main()
{
	std::cout<<compare(2,1)<<std::endl; //模板默认实参的测试

	int *a=new int(4);
	DebugDelete *a2=new DebugDelete();
	DebugDelete debug_delete(std::cout); //成员模板的一个使用测试
	debug_delete(a);
	debug_delete(a2);
	int val=4;
	f3(val); //val的值被改变
	int &&a3=2; //a3的值被改变
	f3(a3);
	f3(42); //42的值不会被改变
	std::cout<<val<<"\n";
	std::cout<<a3<<"\n";
	int v1=3;
	int v2=4;
	std::cout<<"v1,v2: "<<v1<<" "<<v2<<"\n";
	flip(f,v1,v2);
	std::cout<<"v1,v2: "<<v1<<" "<<v2<<"\n";
}
