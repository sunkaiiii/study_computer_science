package main

import (
	"fmt"
	"math/rand"
	"time"
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

func mergeSort2(elements []int, channel chan []int) {
	if len(elements) == 1 {
		channel <- elements
		close(channel)
		return
	}
	lchan := make(chan []int)
	rchan := make(chan []int)
	mid := int(len(elements) / 2)
	go mergeSort2(elements[:mid], lchan)
	go mergeSort2(elements[mid:], rchan)
	merge2(<-lchan, <-rchan, channel)
}

func merge2(left, right []int, resultChan chan []int) {
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
	resultChan <- result
	close(resultChan)
}

func mergeSortMuiltiProcess(a []int) []int {
	resultChan := make(chan []int)
	go mergeSort2(a, resultChan)
	return <-resultChan
}

func main() {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	size := 1000000
	var a []int
	for i := 0; i < size; i++ {
		a = append(a, r.Intn(size))
	}
	startTime := time.Now()
	mergeSort(a)
	endTime := time.Since(startTime)
	fmt.Println(endTime)

	startTime = time.Now()
	mergeSortMuiltiProcess(a)
	endTime = time.Since(startTime)
	fmt.Println(endTime)

}
