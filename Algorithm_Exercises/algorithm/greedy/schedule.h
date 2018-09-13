#pragma once
#include<vector>
#include<algorithm>
struct Customer {
	int serveTime;
	int hopeTime;

	bool operator <(const Customer &other) {
		return this->hopeTime < other.hopeTime;
	}
};

int schedule(std::vector<Customer> customers) {
	std::sort(customers.begin(), customers.end());
	int thistime=0;
	int max = 0;
	for (auto customer : customers) {
		thistime += customer.serveTime;
		if (thistime > customer.hopeTime) {
			max = std::max(max, thistime - customer.hopeTime);
		}
	}

	return max;
}