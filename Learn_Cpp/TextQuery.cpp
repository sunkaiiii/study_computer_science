#include<iostream>
#include<vector>
#include<memory>
#include<map>
#include<set>
#include<string>
#include<sstream>
#include<fstream>
class QueryResult;
class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};
TextQuery::TextQuery(std::ifstream &is) :file(new std::vector<std::string>)
{
	std::string text;
	while (std::getline(is, text)) //对文件中的每一行
	{
		file->push_back(text);  //保存此文本
		int n = file->size() - 1; //当前行号
		std::istringstream line(text);  //将文本分解为单词
		std::string word;
		while (line >> word)  //对行中每一个单词
		{
			auto &lines = wm[word];  //如果单词不在wm中，则为此单词的下标添加一项，同时lines是个shared_ptr，此指针为空
			if (!lines)//第一次遇到这个单词的时候，此指针为空
				lines.reset(new std::set<line_no>); //分配一个set，初始化这个单词
			lines->insert(n); //将此行的行号插入到set中
		}
	}
}
class QueryResult
{
	friend std::ostream &print(std::ostream&, const QueryResult&);
	using line_no = std::vector<std::string>::size_type;
public:
	QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) :sought(s), lines(p), file(f) {}
private:
	std::string sought;
	std::shared_ptr<std::set<line_no>> lines; //出现的行号
	std::shared_ptr<std::vector<std::string>> file;  //输入文件
};
QueryResult TextQuery::query(const std::string &sought) const
{
  //如果未找到sought，我们将返回一个指向此set的指针
	static std::shared_ptr <std::set<line_no >> nodata(new std::set<line_no>);
  //使用find而不是下标运算查找单词，避免将单词添加到wm中
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file); //未找到
	else
		return QueryResult(sought, loc->second, file);
}
std::string make_plural(size_t ctr, const std:: string &word, const std::string &ending)
{
	return (ctr == 1) ? word : word + ending;//make_plural(wc, "word ", "s ")当输入中文本中
											 //word数大于一是在word后加s，为words为word的复数！
}
std::ostream &print(std::ostream & os, const QueryResult &qr)
{
  //如果找到了单词，打印出现次数和所有出现的位置
	os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ")" << *(qr.file->begin() + num) << std::endl;
	return os;
}
int main()
{
	std::ifstream ifs("123.txt");
	TextQuery tq(ifs);
	QueryResult qr = tq.query("we");
	print(std::cout, qr);
}
