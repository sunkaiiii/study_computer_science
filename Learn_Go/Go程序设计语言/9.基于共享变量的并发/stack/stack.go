package main

import "fmt"

func factorial(n int) int64 {
	return factorialHelper(1, n)
}

func factorialHelper(result int64, n int) int64 {
	fmt.Println(n)
	if n == 1 {
		return result
	} else {
		return factorialHelper(result*int64(n), n-1)
	}
}

func main() {
	//golang的占空间为1g
	//启动这个之后，就会看到结果
	//runtime: goroutine stack exceeds 1000000000-byte limit
	//就这个递归层数来说，在我的电脑桑拿为为5592387
	fmt.Println(factorial(2000000000))
}
