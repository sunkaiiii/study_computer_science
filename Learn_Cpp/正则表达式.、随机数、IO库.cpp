#include<iostream>
#include<regex>
#include<random>
int main()
{
	std::string pattern("[^c]ei"); //查找不在字符c之后的字符串ei
	pattern="[[:alpha:]]*"+pattern+"[[:alpha:]]*"; //我们需要把汗pattern的整个单词
	std::regex r(pattern); //构造一个用于查找模式的regex
	std::smatch results; //定义一个对象保存搜索结果
	std::string test_str="receipt freind theif recevive oeicjasd"; //定义一个string保存于模式匹配和不匹配的文本
	if(std::regex_search(test_str,results,r)) //用r在test_str中查找与pattern匹配的字符串，如果有则打印匹配的单词
	{
		std::cout<<results.str()<<std::endl;
	}
	for(std::sregex_iterator it(test_str.begin(),test_str.end(),r),end_it;it!=end_it;++it) //end_it是一个空的迭代器，起到尾后迭代器的最庸
	{
		std::cout<<it->str()<<std::endl;
	}
	std::default_random_engine e; //生成无符号随机数
	for(size_t i=0;i<10;++i)
	{
		std::cout<<e()<<" ";
	}
	//生成0~9之间（包含）均匀分布的随机数
	std::uniform_int_distribution<unsigned> u(0,9);
	std::default_random_engine e2; //生成无符号随机整数
	std::cout<<"\n";
	for(size_t i=0;i<10;++i)
	{
		//将u作为随机数源
		//每个调用返回在指定范围内并服从均匀分布的值
		std::cout<<u(e)<<" ";
	}
	std::cout<<"\n";

	//cout在输出true和false的时候输出的对应0，1
	std::cout<<false<<" "<<true<<"\n";
	//使用boolalpha之后，便会输出false、true
	std::cout<<std::boolalpha<<true<<" "<<false<<" "<<"noboolalpha "<<std::noboolalpha<<false<<" "<<true<<"\n";
	//指定cout的打印精度
	std::cout.precision(18);
	std::cout<<sqrt(2.0)<<"\n";
}
