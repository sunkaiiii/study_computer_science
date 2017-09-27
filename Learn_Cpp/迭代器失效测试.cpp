#include<iostream>
#include<vector>
void vectorTest()
{
    std::vector<int> container;
    for (int i = 0; i < 10; i++)
    {
        container.push_back(i);
    }

    std::vector<int>::iterator iter;
     for (iter = container.begin(); iter != container.end();)
    {
            if (*iter > 3)
              iter=container.erase(iter);
						else
							iter++;
    }
		/*
		迭代器失效的代码
		for (iter = container.begin(); iter != container.end(); iter++)
    {
            if (*iter > 3)
              container.erase(iter);
    }
		*/
     for (iter = container.begin(); iter != container.end(); iter++)
    {
            std::cout<<*iter<<std::endl;
    }
}
int main()
{
	vectorTest();
}
