#include"greedySelect.h"
#include"schedule.h"
#include<iostream>
int main() {
	//int n;
	//std::cin >> n;
	//std::vector<Activity> activities;
	//while (n--) {
	//	struct Activity activity;
	//	std::cin >> activity.startTime >> activity.endTime;
	//	activities.push_back(activity);
	//}
	//auto result = select(activities);
	//for (Activity activity : result) {
	//	std::cout << activity.startTime << "," << activity.endTime << std::endl;
	//}

	//服务问题
	int n;
	std::cin >> n;
	std::vector<Customer> customers;
	while (n--) {
		struct Customer customer;
		std::cin >> customer.serveTime >> customer.hopeTime;
		customers.push_back(customer);
	}
	std::cout << schedule(customers) << std::endl;
}
