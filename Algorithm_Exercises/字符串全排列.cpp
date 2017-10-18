#include<iostream>
#include<algorithm>
void Permutation(char*);
void Permutation(char*,char*);
void Permutation(char *pStr)
{
  if(pStr==NULL)
    return;
  Permutation(pStr,pStr);
}
void Permutation(char *pStr,char *pBegin)
{
  if(*pBegin=='\0')
  {
    std::cout<<pStr<<std::endl;
  }
  else
  {
    for(char* pCh=pBegin;*pCh!='\0';++pCh)
    {
      char temp=*pCh;
      *pCh=*pBegin;
      *pBegin=temp;
      Permutation(pStr,pBegin+1);
      temp=*pCh;
      *pCh=*pBegin;
      *pBegin=temp;
    }
  }
}
int main()
{
  char s[50];
  std::cin>>s;
  std::string s2(s);
  Permutation(s);
  std::cout<<"\n";
  do {
    std::cout<<s2<<std::endl;
  } while(std::next_permutation(s2.begin(),s2.end()));
}
