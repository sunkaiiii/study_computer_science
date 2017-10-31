#include<iostream>
template<typename T>
bool compare(const T& a,const T& b)
{
  return a>b;
}

class A
{
private:
  int a;
public:
  A(int a2):a(a2){}
  A():a(0){}
  friend bool operator<(const A& l,const A& r);
  friend bool operator>(const A& l,const A& r);
  friend bool operator==(const A& l,const A& r);
  friend bool operator!=(const A& l,const A& r);
  void operator=(const A& c)
  {
    a=c.a;
  }
};
bool operator<(const A& l,const A& r)
{
  return l.a<r.a;
}
bool operator>(const A& l,const A& r)
{
  return !(l<r);
}
bool operator==(const A& l,const A& r)
{
  return (l.a==r.a);
}
bool operator!=(const A& l,const A& r)
{
  return !(l.a==r.a);
}

int main()
{
  int a=2,b=3;
  std::cout << compare(a,b) << '\n';
  A c,c2(2);
  std::cout << compare(c,c2) << '\n';
  std::cout<<(c!=c2)<<"\n";
}
