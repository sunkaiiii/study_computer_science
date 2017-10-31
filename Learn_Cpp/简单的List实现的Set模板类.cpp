#include<iostream>
#include<list>
#include<algorithm>
template<typename T>
class Set
{
public:
  bool member(const T& item) const;
  void insert(const T& item);
  void remove(const T& item);
  const typename std::list<T>::iterator  begin();
  const typename std::list<T>::iterator end();
  const typename std::list<T>::const_iterator cbegin();
  const typename std::list<T>::const_iterator cend();
  std::size_t size() const;
private:
  std::list<T> rep;
};

template<typename T>
bool Set<T>::member(const T& item) const
{
  return std::find(rep.begin(),rep.end(),item)!=rep.end();
}
template<typename T>
void Set<T>::insert(const T& item)
{
  if(!member(item))
    rep.push_back(item);
};

template<typename T>
void Set<T>::remove(const T& item)
{
  auto it=std::find(rep.begin(),rep.end(),item);
  if(it!=rep.end())
    rep.erase(it);
}

template<typename T>
std::size_t Set<T>::size() const
{
  return rep.szie();
}

template<typename T>
const typename std::list<T>::iterator  Set<T>::begin()
{
  return rep.begin();
}

template<typename T>
const typename std::list<T>::iterator Set<T>::end()
{
  return rep.end();
}
template<typename T>
const typename std::list<T>::const_iterator  Set<T>::cbegin()
{
  return rep.cbegin();
}

template<typename T>
const typename std::list<T>::const_iterator Set<T>::cend()
{
  return rep.cend();
}
int main()
{
  Set<int> set;
  int a;
  for(int i=0;i<10;i++)
  {
    std::cin>>a;
    set.insert(a);
  }
  auto it=set.cbegin();
  for(;it!=set.cend();++it)
  {
    std::cout<<*it<<" ";
  }
  std::cout<<"\n";
}
