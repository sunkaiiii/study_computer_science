#include<iostream>
template<typename T>
class NamedObject
{
public:
  NamedObject(const char *name,const T& value):namevalue(name),objectValue(value){}
  NamedObject(const std::string &name,const T& value):namevalue(name),objectValue(value){}
private:
  std::string namevalue;
  T objectValue;
};
/*
由于类中没有拷贝构造函数和拷贝复制构造函数，编译器将会为其自动添加*/
template<typename T>
class NamedObject2
{
public:
  NamedObject2(const char *name,const T& value):namevalue(name),objectValue(value){}
  NamedObject2(const std::string &name,const T& value):namevalue(name),objectValue(value){}
private:
  std::string& namevalue;
  T& objectValue;
};
//由于是引用类型，编译器无法为他添加默认的拷贝赋值构造函数

int main()
{
  NamedObject<int> o1("no1",2);
  NamedObject<int> o2(o1); //调用拷贝构造函数
  NamedObject<int> o3("no3",3); //调用编译器默认生成的default构造函数
  o3=o2; //调用编译器默认生成的拷贝复制构造函数

  NamedObject2<int> o21("no1",2);
  NamedObject2<int> o22("no2",3);
  NamedObject2<int> o33(o21);
  // o22=o21; //词句无法执行，因为编译器并乜有生成拷贝赋值构造函数
}
