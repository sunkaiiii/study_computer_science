package main

import (
	"fmt"
	"sync"
	"time"
)

var (
	mu      sync.Mutex //go语言提供普通的锁。同时也提供RWMutex
	balance int
)

//使用锁进行互斥控制
func deposit(amount int) {
	balance += amount
}

func tryDeposit(amount int) {
	mu.Lock()
	defer mu.Unlock()
	deposit(amount)
}

func getBalance() int {
	mu.Lock()
	defer mu.Unlock()
	return balance
}

func withDraw(amount int) bool {
	mu.Lock()
	defer mu.Unlock()
	deposit(-amount)
	if balance < 0 {
		deposit(amount) //使用无需用锁的，防止死锁（go并没有重用锁）
		return false
	}
	return true
}

func main() {
	var x, y int
	go func() {
		x = 1
		fmt.Print("y:", y, " ")
	}()
	go func() {
		y = 1
		fmt.Print("x: ", x, " ")
	}()
	time.Sleep(100000)
}
