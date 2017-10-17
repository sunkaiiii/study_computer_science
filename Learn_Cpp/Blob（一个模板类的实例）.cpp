#include<iostream>
#include<vector>
#include<memory>
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
