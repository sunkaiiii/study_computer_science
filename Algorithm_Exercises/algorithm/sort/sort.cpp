#include<stdio.h>
#include<vector>
#include<random>
#include<time.h>
#include<iostream>
#include<algorithm>
#include<thread>
#include<future>
#include<mutex>
std::vector<int> mergeSortPartition(std::vector<int> &result, int64_t p, int64_t r);
std::vector<int> merge(std::vector<int> &left, std::vector<int> &right);
std::vector<int> generateVector(long long n) {
	std::uniform_int_distribution<int> u(-INT32_MAX, INT32_MAX);
	std::default_random_engine engine(time(0));
	std::vector<int> result;
	for (; n > 0; n--) {
		result.push_back(u(engine));
	}
	return result;
}

int64_t partition(std::vector<int> &elements, int64_t p, int64_t r) {
	int x = elements[p];
	int64_t i = p;
	int64_t j = r + 1;
	while (true) {
		while (--j >= 0) {
			if (elements[j] <= x) {
				break;
			}
		}
		while (++i <= r) {
			if (elements[i] > x) {
				break;
			}
		}
		if (i < j) {
			std::swap(elements[i], elements[j]);
		}
		else {
			return j;
		}
	}
}

void quickSort(std::vector<int> &elements, int64_t   p, int64_t r) {
	if (p >= r) {
		return;
	}
	int64_t q = partition(elements, p, r);
	std::swap(elements[p], elements[q]);
	quickSort(elements, p, q - 1);
	quickSort(elements, q + 1, r);
}


void mergeSort(std::vector<int> &elements, int64_t p, int64_t r) {
	std::vector<int> result = elements;
	elements = mergeSortPartition(result, p, r);
}

std::vector<int> mergeSortPartition(std::vector<int> &result, int64_t p, int64_t r) {
	if (result.size() <= 1) {
		return result;
	}
	auto mid = result.size() / 2;
	std::vector<int> leftPart(result.begin(), result.begin() + mid);
	std::vector<int> rightPart(result.begin() + mid + 1, result.end());
	auto left = mergeSortPartition(leftPart, 0, mid);
	auto right = mergeSortPartition(rightPart, mid + 1, r);
	return merge(left, right);
}

std::vector<int> merge(std::vector<int> &left, std::vector<int> &right) {
	std::vector<int> result;
	int i = 0, j = 0;
	while (i < left.size() && j < right.size()) {
		if (left[i] < right[j]) {
			result.push_back(left[i++]);
		}
		else {
			result.push_back(right[j++]);
		}
	}
	while (i < left.size()) {
		result.push_back(left[i++]);
	}
	while (j < right.size()) {
		result.push_back(right[j++]);
	}
	return result;
}

void selectSort(std::vector<int> &elements) {
	for (size_t i = 0; i < elements.size(); i++) {
		size_t min = i;
		for (size_t j = i; j < elements.size(); j++) {
			if (elements[min] > elements[j]) {
				min = j;
			}
		}
		std::swap(elements[i], elements[min]);
	}
}

const unsigned currentCpuCores = std::thread::hardware_concurrency();
std::mutex mutex;
std::mutex coutnMutex;
int i = 0;

void  count() {
	std::lock_guard<std::mutex> lck(mutex);
	i++;
	if (i+1 == currentCpuCores) {
		coutnMutex.unlock();
	}
}

std::vector<int> multiProcessMergeSort(std::vector<int> &result, int64_t p, int64_t r) {
	if (coutnMutex.try_lock()) {
		std::vector<std::thread> workers;
		for (int i = 0; i < currentCpuCores; i++) {
			int64_t start = result.size() / currentCpuCores * i;
			int64_t end = result.size() / currentCpuCores * i;
			if (i == currentCpuCores - 1) {
				end = result.size();
			}
			auto func = [](std::vector<int> &&elements, std::vector<int>::iterator begin, std::vector<int>::iterator end)mutable -> std::vector<int> {
				std::sort(begin, end);
				count();
				return std::vector<int>(begin, end);
			};
			workers.push_back(std::thread(func, result, result.begin() + start, result.begin() + end));
			//return gotoSort(std::move(workers));
		}
		for (auto &work : workers) {
			work.join();
		}
	}
	return std::vector<int>();
}
std::vector<int> gotoSort(std::vector < std::future<std::vector<int>>> workers) {
	auto it = workers.begin();
	return std::vector<int>();
	//auto mid = workers.size() / 2;
	//std::vector<std::future<std::vector<int>>> left;
	//std::vector<std::future<std::vector<int>>> right;
	//std::move(workers.begin(), workers.begin() + mid, std::back_inserter(left));
	//std::move(workers.begin() + mid, workers.end(), std::back_inserter(right));
}


void startMultiThreadMergeSort(std::vector<int> &elements, int64_t p, int64_t r) {
	std::vector<int> result = elements;
	elements = multiProcessMergeSort(result, p, r);
}

int main() {
	auto a = generateVector(100000000L);
	auto b = a;
	auto c = a;
	auto d = a;
	//uint64_t start_time = time(0);
	//quickSort(a, 0, a.size() - 1);
	//uint64_t end_time = time(0);
	//std::cout << end_time - start_time << "취\n";
	//for (int i : a) {
	//	std::cout << i << ",";
	//}

	uint64_t start_time = time(0);
	startMultiThreadMergeSort(b, 0, b.size() - 1);
	uint64_t end_time = time(0);
	std::cout << end_time - start_time << "취\n";
	for (int i : b) {
		std::cout << i << ",";
	}


	//start_time = end_time;
	//std::sort(b.begin(), b.end());
	//end_time = time(0);
	//std::cout << end_time - start_time << "취\n";

	//start_time = end_time;
	//mergeSort(c, 0, c.size());
	//end_time = time(0);
	//std::cout << end_time - start_time << "취\n";

	//start_time = end_time;
	//selectSort(d);
	//end_time = time(0);
	//std::cout << end_time - start_time << "취\n";

}