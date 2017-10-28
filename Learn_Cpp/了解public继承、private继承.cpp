class a
{
public:
  void f(){}
};
class b :private a
{
public:
  void f2()
  {
    f();
  }
};

class c:public b
{
public:
  void f3()
  {
    f2();
    f(); //因为b是private继承，于是对于c来说，a中的内容就不可见了
  }
};
