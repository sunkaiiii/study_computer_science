package main

import (
	"fmt"
	"sort"
)

func mergeSort(elements []int) []int {
	if len(elements) == 1 {
		return elements
	}
	mid := int(len(elements) / 2)
	left := mergeSort(elements[:mid])
	right := mergeSort(elements[mid:])
	return merge(left, right)
}

func merge(left, right []int) []int {
	var result []int
	i, j := 0, 0
	for i < len(left) && j < len(right) {
		if left[i] <= right[j] {
			result = append(result, left[i])
			i++
		} else {
			result = append(result, right[j])
			j++
		}
	}
	result = append(result, left[i:]...)
	result = append(result, right[j:]...)
	return result
}

func MergeBU(c []int) {
	var aux = make([]int, len(c))
	var merge = func(c []int, lo, mid, hi int, wait chan int) {
		defer func() {
			wait <- 1
		}()
		i, j := lo, mid+1
		for k := lo; k <= hi; k++ {
			aux[k] = c[k]
		}
		for k := lo; k <= hi; k++ {
			if i > mid {
				c[k] = aux[j]
				j++
			} else if j > hi {
				c[k] = aux[i]
				i++
			} else if aux[j] < aux[i] {
				c[k] = aux[j]
				j++
			} else {
				c[k] = aux[i]
				i++
			}
		}
	}
	var sort = func(c []int) {
		l := len(c)
		for sz := 1; sz < l; sz = sz + sz {
			count := 0
			wait := make(chan int, 1024)
			for lo := 0; lo < l-sz; lo += sz + sz {
				count++
				go merge(c, lo, lo+sz+1, min(lo+sz+sz-1, l-1), wait)
			}
			for {
				count -= <-wait
				if count == 0 {
					close(wait)
					break
				}
			}
		}
	}
	sort(c)
}

func min(x, y int) int {
	if x < y {
		return x
	} else {
		return y
	}
}

func mergeSortMuiltiProcess(a []int) {
	MergeBU(a)
}

func arraySource(a ...int) <-chan int {
	out := make(chan int)
	go func() {
		for _, v := range a {
			out <- v
		}
		close(out)
	}()
	return out
}

func inMemSort(in <-chan int) <-chan int {
	out := make(chan int)
	go func() {
		a := []int{}
		for v := range in {
			a = append(a, v)
		}
		sort.Ints(a)

		for _, v := range a {
			out <- v
		}
		close(out)
	}()
	return out
}

func main() {
	// r := rand.New(rand.NewSource(time.Now().UnixNano()))
	// size := 10
	// var a []int
	// for i := 0; i < size; i++ {
	// 	a = append(a, r.Intn(size))
	// }
	// startTime := time.Now()
	// mergeSort(a)
	// endTime := time.Since(startTime)
	// fmt.Println(endTime)

	// startTime = time.Now()
	// mergeSortMuiltiProcess(a)
	// fmt.Println(a)
	// endTime = time.Since(startTime)
	// fmt.Println(endTime)
	p := inMemSort(arraySource(1, 2, 3, 4, 5))
	for i := range p {
		fmt.Println(i)
	}
}
