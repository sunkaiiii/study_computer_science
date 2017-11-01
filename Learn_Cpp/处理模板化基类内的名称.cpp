#include<iostream>
class CompnayA
{
public:
  void sendClearText(const std::string& msg)
  {
    std::cout<<"CompnayA "<<msg<<"\n";
  }
};
class CompnayB
{
public:
  void sendClearText(const std::string& msg)
  {
    std::cout<<"CompnayB "<<msg<<"\n";
  }
};

template<typename Company>
class MsgSender
{
public:
  void sendClear(const std::string& msg)
  {
    Company c;
    c.sendClearText(msg);
  }
};

template<typename Compnay>
class LogginMsgSender:public MsgSender<Compnay>
{

public:
  void sendCLearMsg(const std::string& msg)
  {
    //sendClear(msg); //这句话将无法编译，对于变异而言，sendClear是个并不存在的函数
    //因为被继承的模板是可能被特化的，如果特化版本提供、不提供某些针对一般template的函数，就会出现问题

    //使用这个方法
    this->sendClear(msg); //最好使用此方法
    //or
    MsgSender<CompnayA>::sendClear(msg); //这么做可能会关闭虚函数的绑定行为
    //or
    sendClear(msg);
  }
  using MsgSender<Compnay>::sendClear; //使用using声明
};

int main()
{
  MsgSender<CompnayA> sender;
  sender.sendClear("123");
  LogginMsgSender<CompnayA> sender2;
  sender2.sendCLearMsg("!@412");
}
