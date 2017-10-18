#include<iostream>
#include<vector>
#include<memory>
#include<functional>
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

int main()
{
	std::cout<<compare(2,1)<<std::endl; //模板默认实参的测试

	int *a=new int(4);
	DebugDelete *a2=new DebugDelete();
	DebugDelete debug_delete(std::cout); //成员模板的一个使用测试
	debug_delete(a);
	debug_delete(a2);
}
