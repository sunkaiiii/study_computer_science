#include<vector>
#include<iostream>
#include<algorithm>
#include"bitCompress.h"
//数据压缩
void compress(std::vector<int> origin) {
	//header存储两个信息 前8个存储数量，后3位每一段的存储位数，则一共需要11位长
	const static int maxLength = 256;
	const static int header = 11;
	std::vector<int> s;
	std::vector<int> b;
	std::vector<int> l;
	s.push_back(0);
	b.push_back(0);
	l.push_back(0);
	std::vector<int> p{ 0 };
	for (int value : origin) {
		p.push_back(value);
	}
	for (int i = 1; i < p.size(); i++) {
		b.push_back(length(p[i])); //表示当前数字的位数
		int bmax = b[i];
		s.push_back(s[i - 1] + bmax); //这一次循环的数字单成一段
		l.push_back(1);
		for (int j = 2; j <= std::min(i, maxLength); j++) { //开始判断与前面的数字共成一段的效果
			if (bmax < b[i - j + 1]) { //统一这一段数字的位数，如果当前位数小，则扩大到统一大小
				bmax = b[i - j + 1];
			}
			if (s[i] > s[i - j] + j * bmax) { //开始判断这一段是否为当前的最优解
				s[i] = s[i - j] + j * bmax;
				l[i] = j;
			}
		}
		s[i] += header;
	}
	for (int count : s) {
		std::cout << count << " ";
	}
	std::cout << std::endl;
	std::cout << s[p.size() - 1] << std::endl;
	traceBack(p.size() - 1, l);
}

int length(int i) {
	int ii = ceil(log10(i + 1) / log10(2));
	return ii;
}

void traceBack(int n, std::vector<int> l) {
	std::vector<int> c;
	while (n != 0) {
		c.push_back(l[n]);
		n -= l[n];
	}
	for (int i : c) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}