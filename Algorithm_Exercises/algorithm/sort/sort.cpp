#include<stdio.h>
#include<vector>
#include<random>
#include<time.h>
#include<iostream>
#include<algorithm>
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

void quickSort(std::vector<int> &elements,int64_t   p, int64_t r) {
	if (p >= r) {
		return;
	}
	int64_t q = partition(elements, p, r);
	std::swap(elements[p], elements[q]);
	quickSort(elements, p, q - 1);
	quickSort(elements, q + 1, r);
}

int main() {
	auto a = generateVector(10000000L);
	auto b = a;
	auto c = a;
	uint64_t start_time = time(0);
	quickSort(a, 0, a.size() - 1);
	uint64_t end_time = time(0);
	std::cout << end_time - start_time << "Ãë\n";


	start_time = end_time;
	std::sort(b.begin(), b.end());
	end_time = time(0);
	std::cout << end_time - start_time << "Ãë\n";

	start_time = end_time;
	std::stable_sort(c.begin(), c.end());
	end_time = time(0);
	std::cout << end_time - start_time << "Ãë\n";
	
}