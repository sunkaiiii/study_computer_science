#include<stdio.h>
#include<iostream>
#include<vector>
#include<time.h>
#include<Windows.h>

long calFibonacci(const int n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	return calFibonacci(n - 2)+calFibonacci(n-1);
}


long calFibonacci2(const long n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	long resultSet[3]{0,1};
	for (long i = 2; i <= n; i++) {
		resultSet[i % 3] = resultSet[(i - 1) % 3] + resultSet[(i - 2) % 3];
	}
	return resultSet[(n) % 3];
}

struct Matrix :std::vector<std::vector<long> >
{
	Matrix(int x = 0, int y = 0, int z = 0)
	{
		assign(x, vector<long>(y, z));
	}
	int h_size()const
	{
		return size();
	}
	int l_size()const
	{
		return empty() ? 0 : front().size();
	}
	Matrix pow(long k);
};
Matrix operator*(const Matrix &m, const Matrix &n)
{
	if (m.l_size() != n.h_size())return Matrix();
	Matrix ans(m.h_size(), n.l_size());
	for (int i = 0; i != ans.h_size(); ++i)
		for (int j = 0; j != ans.l_size(); ++j)
			for (int k = 0; k != m.l_size(); ++k)
				ans[i][j] += m[i][k] * n[k][j];
	return ans;
}
Matrix Matrix::pow(long k)
{
	if (k == 0)
	{
		Matrix ans(h_size(), h_size());
		for (int i = 0; i != ans.h_size(); ++i)
			ans[i][i] = 1;
		return ans;
	}
	if (k == 2)return (*this)*(*this);
	if (k % 2)return pow(k - 1)*(*this);
	return pow(k / 2).pow(2);
}

long calFibonacci3(const long n) {
	Matrix *m = new Matrix();
	std::vector<long> x{ 1,1 };
	std::vector<long> y{ 1,0 };
	m->push_back(x);
	m->push_back(y);
	*m=m->pow(n-1);
	return (*m)[0][0];
}


int main() {
	auto startTime = time(0);
	//std::cout << calFibonacci(80)<<std::endl;
	auto endTime = time(0);
	std::cout << endTime - startTime <<"Ãë"<< std::endl;
	startTime = endTime;

	std::cout << calFibonacci2(2000000000l) << std::endl;
	endTime = time(0);
	std::cout << endTime - startTime << "Ãë" << std::endl;
	startTime = endTime;

	std::cout << calFibonacci3(2000000000l) << std::endl;
	endTime = time(0);
	std::cout << endTime - startTime << "Ãë" << std::endl;
	startTime = endTime;
}