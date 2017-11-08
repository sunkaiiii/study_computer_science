#include<iostream>

class Employee
{
public:
	virtual bool isTimeToPay()
	{
		return true;
	}

	virtual void pay()
	{

	}
};

class Null_Employee:public Employee
{
public:
	virtual bool isTimeToPay() override
	{
		return false;
	}
	virtual void pay() override
	{
	}
};


class DB
{
public:
	static Employee* getEmployee(std::string name)
	{
		if (name == "tom")
		{
			return new Employee();
		}
		else
		{
			return new Null_Employee();
		}
	}
};


void judge(Employee* employee)
{
	if (employee->isTimeToPay())
	{
		std::cout << "true" << std::endl;
	}
	else
	{
		std::cout << "false" << std::endl;
	}
}

int main()
{
	Employee* tom = DB::getEmployee("tom");
	Employee* sam = DB::getEmployee("sam");

	judge(tom);
	judge(sam);

	delete tom;
	delete sam;
}
