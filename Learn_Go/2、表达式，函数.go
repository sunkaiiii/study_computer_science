package test

import (
	"fmt"
	"log"
	"sync"
	"testing"
)

//变参传递的是一个切片，这就可以对元素组进行操作
func test4(a ...int) {
	for i := range a {
		a[i] += 100
	}
}

//普通函数和匿名函数都可以当做结构体的字段，或者经过通道传递
func testStruct() {
	type calc struct {
		mul func(x, y int) int
	}
	x := calc{
		func(x, y int) int {
			return x * y
		},
	}
	println(x.mul(2, 3))
}

func testChannel() {
	c := make(chan func(int, int) int, 2)
	c <- func(x, y int) int {
		return x + y
	}
	println((<-c)(1, 2))
}

//一个简单的闭包的实现
func testClosure(x int) func() {
	println(&x)
	return func() {
		println(&x, x)
	}
}

//演示闭包函数延迟求值的特性
//最终将会输出结果2
//因为在声明中仅仅是把匿名函数放入列表，没有最终的执行
func testClosure2() []func() {
	var s []func()
	for i := 0; i < 2; i++ {
		s = append(s, func() {
			println(&i, i)
		})
	}
	return s
}

//解决延迟求值中，i的输出结果都为2的方法
//每次使用不同的变量传参
func testClosure3() []func() {
	var s []func()

	for i := 0; i < 2; i++ {
		x := i
		s = append(s, func() {
			println(&x, x)
		})
	}
	return s
}

//多个匿名函数操作同一个环境变量
func testClosure4(x int) (func(), func()) {
	return func() {
			println(x)
			x += 10
		}, func() {
			println(x)
		}
}

//执行顺序为 z=100，call defer
func deferTest() (z int) {
	defer func() {
		println("defer:", z)
		z += 100
	}()
	return 100
}

//延迟调用对性能的影响
var m sync.Mutex

func call() {
	m.Lock()
	m.Unlock()
}

func deferCall() {
	m.Lock()
	defer m.Unlock()
}

func BenchmarkCall(b *testing.B) {
	for i := 0; i < b.N; i++ {
		call()
	}
}

func BenchmarkDefer(b *testing.B) {
	for i := 0; i < b.N; i++ {
		deferCall()
	}
}

//自定义错误类型的使用
type DivError struct {
	x, y int
}

func (DivError) Error() string {
	return "divisiton by zero"
}

func div(x, y int) (int, error) {
	if y == 0 {
		return 0, DivError{x, y}
	}
	return x / y, nil
}
func checkDivError() {
	z, err := div(5, 0)
	if err != nil {
		switch e := err.(type) {
		case DivError:
			fmt.Println(e, e.x, e.y)
		default:
			fmt.Println(e)
		}
	}
	println(z)
}

//panic recover
//go中的try...catch
func testPanic() {
	defer func() {
		if err := recover(); err != nil { //捕获错误
			log.Fatalln(err)
		}
	}()
	panic("i am dead")
	println("exit..")
}

//连续抛出panic，仅仅会捕获最后一个
func testPanic2() {
	defer func() {
		for {
			if err := recover(); err != nil {
				log.Println(err)
			} else {
				log.Fatalln("Fatal")
			}
		}
	}()
	defer func() {
		panic("you are dead")
	}()
	panic("i am dead")
}
