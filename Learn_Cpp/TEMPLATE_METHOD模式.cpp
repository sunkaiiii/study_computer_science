#include<iostream>
#include<string>
class A
{
private:
  bool a=false;
protected:
  void setDone(){
    a=true;
  }

  bool done(){
    return a;
  }

  virtual void init()=0;
  virtual void idle()=0;
  virtual void cleanup()=0;
public:
  void run(){
    init();
    while(!done()){
      idle();
    }
    cleanup();
  }
};

class B:public A{
protected:
  void init() override{
    std::cout<<"init\n";
  }
  void idle() override{
    std::string s;
    std::cin>>s;
    if(s.size()==0)
      setDone();
    std::cout<<"input is :"<<s<<"\n";
  }

  void cleanup() override{
    std::cout<<"clean up \n";
  }
};

int main(){
  B b;
  b.run();
}
