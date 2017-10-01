#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include<sstream>
struct people
{
  std::string name;
  std::vector<std::string> v;
};
int main()
{
  std::string line,word;
  std::vector<people> peoples;
  std::ifstream input("1.txt");
  while(getline(input,line))
  {
    people p;
    std::istringstream record(line);
    record>>p.name;
    while(record>>word)
    {
      p.v.push_back(word);
    }
    peoples.push_back(p);
  }
  for(people p:peoples)
  {
    std::cout<<p.name<<" ";
    for(std::string word:p.v)
    {
      std::cout<<word<<" ";
    }
    std::cout<<std::endl;
  }
}
