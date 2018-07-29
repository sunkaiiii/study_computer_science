package main

import (
	"fmt"
	"sort"
)

//以下提供了学习某一门课程所需要的先决条件
var prereqs = map[string][]string{
	"algorithms":            {"data structures"},
	"calculus":              {"linear algebra"},
	"compilers":             {"data structures", "formal languages", "computer organization"},
	"data structures":       {"discrete math"},
	"databases":             {"data structures"},
	"discrete math":         {"intro to programming"},
	"formal languages":      {"discrete math"},
	"networks":              {"operating systems"},
	"operating systems":     {"data structures", "computer organization"},
	"programming languages": {"data structures", "computer organization"},
}

//这样的问题是熟知的拓扑排序
//在概念上，先觉内容构成一张有向图，每一个节点代表一门课程
//每一条边代表一门课程所依赖的另一门课程的关系
//图书无环的，没有节点可以通过图上的路径找到自己
//可以使用深度优先算法得到合法地学习路径
func topoSort(m map[string][]string) []string {
	var order []string
	seen := make(map[string]bool)
	var visitAll func(items []string)
	visitAll = func(items []string) {
		for _, item := range items {
			if !seen[item] {
				seen[item] = true
				visitAll(m[item]) //当匿名函数需要递归的时候，必须要先声明这个变量
				order = append(order, item)
			}
		}
	}
	var keys []string
	for key := range m {
		keys = append(keys, key)
	}
	sort.Strings(keys)
	visitAll(keys)
	return order

}

func main() {
	for i, course := range topoSort(prereqs) {
		fmt.Printf("%d:\t%s\n", i+1, course)
	}
}
