#include<iostream>
template<typename T>
class SmartPtr
{
public:
  template<typename U>
  SmartPtr(const SmartPtr<U>& other) //一个泛化的拷贝构造函数
    :heldPtr(other.get()){}
  template<typename U>
  SmartPtr(U* u):heldPtr(u){}
  T* get() const{ return heldPtr; }
private:
  T* heldPtr;
};
class A
{
public:
  virtual void func()
  {
    std::cout<<"A\n";
  }
};
class B:public A
{
public:
  virtual void func()
  {
    std::cout<<"B\n";
  }
};
int main()
{
  A *a=new A;
  B *b=new B;
  SmartPtr<A> p(a);
  SmartPtr<A> p2(b); //此处隐士转换为基类指针
  p2.get()->func(); //获取原始指针，并执行虚函数
  SmartPtr<A> p3=p2; //执行泛化拷贝构造函数
  p3.get()->func();  //获取原始指针，执行虚函数
  std::cout<<a<<" "<<b<<" "<<p.get()<<" "<<p2.get()<<" "<<p3.get()<<"\n";
  SmartPtr<B> p4=p3; //反过来是不行的,即使p3指向的是B的实例
}
