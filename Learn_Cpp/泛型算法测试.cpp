#include<iostream>
#include<algorithm>
#include<vector>
#include<iterator>
int main()
{
	int a=2;
	std::vector<int> v(10);
	for(int i=0;i<10;i++)
	{
		std::cin>>v[i];
	}
	/*
	替换方法测试
	std::replace(v.begin(),v.end(),2,42);
	std::vector<int> v2;
	std::replace_copy(v.begin(),v.end(),back_inserter(v2),2,42);
	for(int i:v2)
	{
		std::cout<<i<<std::endl;
	}*/

	/*unique方法测试
	std::sort(v.begin(),v.end());
	for(int i:v)
	{
		std::cout<<i<<std::endl;
	}
	auto end_unique=std::unique(v.begin(),v.end());
	std::cout<<"end_unique:"<<*end_unique<<std::endl;
	v.erase(end_unique,v.end());
	for(int i:v)
	{
		std::cout<<i<<std::endl;
	}*/

	/*指定lambda返回类型
	std::transform(v.begin(),v.end(),v.begin(),[](int i)->int{if(i<0)return -i;else return i;});//使用尾置返回类型
	for(int i:v)
		std::cout<<i<<std::endl;
	*/

	/*使用istream_iterator从标准输入读取数据，存入vector*/
	// std::istream_iterator<int> in_iter(std::cin); //从cin读取int
	// std::istream_iterator<int> eof; //istream尾后迭代器

	/*
	while(in_iter!=eof)
	{
		//后置递增运算读取流，返回迭代器的旧值
		//解引用迭代器，获取从流读取的前一个值
		v.push_back(*in_iter++);
	}
	//下一句话等同于上面的循环
	// std::vector<int> v2(in_iter,eof);
	//
	// //复制v2的内容到v1用于显示，注意v2的长度不能长于v1
	// std::copy(v2.begin(),v2.end(),v.begin());
	//
	// for(int i:v)
	// {
	// 	std::cout<<i<<std::endl;
	// }
	*/


	/*使用ostream_iterator输出vector
	std::ostream_iterator<int> out_iter(std::cout," ");
	// for(auto i:v)
	// 	*out_iter++=i; //实际是写到了cout上
	// std::cout<<std::endl;
	//等价写法
	//copy(v.begin(),v.end(),out_iter);
	//或者
	// for(auto i:v)
	// 	out_iter=i;
	// std::cout<<std::endl;
	*/
}
