#include<algorithm>
#include<vector>
#include<random>
#include<time.h>
std::vector<int> generateVector(int64_t n) {
	std::uniform_int_distribution<int> u(-INT32_MAX, INT32_MAX);
	std::default_random_engine engine(time(0));
	std::vector<int> result;
	for (; n > 0; n--) {
		result.push_back(u(engine));
	}
	return result;
}

int select(std::vector<int> &elements, int64_t n) {
	if (n >= elements.size()) {
		return INT64_MIN;
	}
	std::sort(elements.begin(), elements.end());
	return elements[n];
}

int select2(std::vector<int> &elements, int64_t n) {

}

int main() {

}