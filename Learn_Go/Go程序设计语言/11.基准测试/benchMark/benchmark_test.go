package benchMark

import "testing"

func factorial(n int) int64 {
	return factorialHelper(1, n)
}

func factorialHelper(result int64, n int) int64 {
	if n == 0 {
		return result
	} else {
		return factorialHelper(result*int64(n), n-1)
	}
}

func BenchmarkFactorial(b *testing.B) {
	for i := 0; i < b.N; i++ {
		factorial(i)
	}
}
