package test

import (
	"errors"
	"fmt"
	"reflect"
	"sync"
	"time"
	"unsafe"
)

//字符串的两种遍历形式
func forString() {
	s := "测试"
	for i := 0; i < len(s); i++ { //byte
		fmt.Printf("%d:[%c]\n", i, s[i])
	}

	for i, c := range s { //rune
		fmt.Printf("%d,[%c]\n", i, c)
	}
}

//一种非安全的转换方法，此方法效率很高
func toString(bs []byte) string {
	return *(*string)(unsafe.Pointer(&bs))
}

//使用切片实现的交错数组功能
func jaggedArray() {
	x := [][]int{
		{1, 2},
		{10, 20, 30},
		{100},
	}
	fmt.Println(x[1])
	x[2] = append(x[2], 200, 300)
	fmt.Println(x[2])
}

//reslice操作，但要注意的是，他们都是对原数组进行的操作
func reslice() {
	d := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	s1 := d[3:7]
	s2 := s1[1:3]
	for i := range s2 {
		s2[i] += 100
	}
	fmt.Println(d)
	fmt.Println(s1)
	fmt.Println(s2)
}

//reslice实现的栈式数据结构
func stack() {
	stack := make([]int, 0, 5)

	//入栈
	push := func(x int) error {
		n := len(stack)
		if n == cap(stack) {
			return errors.New("stack is full")
		}
		stack = stack[:n+1]
		stack[n] = x
		return nil
	}
	pop := func() (int, error) {
		n := len(stack)
		if n == 0 {
			return 0, errors.New("stack is empty")
		}
		x := stack[n-1]
		stack = stack[:n-1]
		return x, nil
	}

	//入栈测试
	for i := 0; i < 7; i++ {
		fmt.Printf("push %d: %v,%v\n", i, push(i), stack)
	}

	for i := 0; i < 7; i++ {
		x, err := pop()
		fmt.Printf("pop:%d,%v,%v\n", x, err, stack)
	}
}

//两个切片之间复制数据，允许目标区域重叠，最终复制的长度以长度较短的切片为准
func copyTest() {
	s := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	s1 := s[5:8]
	n := copy(s[4:], s1)
	fmt.Println(n, s)
	s2 := make([]int, 6)
	n = copy(s2, s)
	fmt.Println(n, s2)
}

//并发环境下字典的竞争读写引发的问题
func mutiThreadMapRead() {
	m := make(map[string]int)
	go func() {
		for {
			m["a"] += 1
			time.Sleep(time.Microsecond)
		}
	}()
	go func() {
		for {
			_ = m["b"]
			time.Sleep(time.Microsecond)
		}
	}()
	select {} //阻止进程退出
}

//解决方法是通过sync.RWMutex进行同步
func mutiThreadMapReadByMutex() {
	var lock sync.RWMutex //使用读写锁以获得最高性能
	m := make(map[string]int)
	go func() {
		for {
			lock.Lock()
			m["a"] += 1
			lock.Unlock()
			time.Sleep(time.Microsecond)
		}
	}()
	go func() {
		for {
			lock.RLock()
			_ = m["b"]
			lock.RUnlock()
			time.Sleep(time.Microsecond)
		}
	}()
	select {}
}

//空结构指向runtime.zerobase，通常用于处理通道通知
func testEmptyStruct() {
	exit := make(chan struct{})
	go func() {
		println("hello")
		exit <- struct{}{}
	}()
	<-exit
	println("end")
}

//匿名字段
func anonymousFiled() {
	type attr struct {
		perm int
	}
	type file struct {
		name string
		attr //匿名字段
	}
	f := file{
		name: "test.dat",
		attr: attr{
			perm: 0744,
		}, //显示初始化匿名字段
	}

	f.perm = 0644 //直接设置匿名字段成员
}

func testTag() {
	type user struct {
		name string `昵称`
		sex  byte   `性别`
	}

	u := user{"Tom", 1}
	v := reflect.ValueOf(u)
	t := v.Type()
	for i, n := 0, t.NumField(); i < n; i++ {
		fmt.Printf("%s:%v\n", t.Field(i).Tag, v.Field(i))
	}
}
