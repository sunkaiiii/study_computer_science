package test

import (
	"fmt"
	"log"
	"reflect"
	"sync"
)

//方法
//go里面的方法类似于c#的扩展方法
//为N指定toString方法
type N int

func (n N) toString() string {
	return fmt.Sprintf("%#x", n)
}
func testFunction() {
	var a N = 5
	println(a.toString())
}

func testAnyousFunction() {
	type data struct {
		sync.Mutex
		buf [1024]byte
	}

	d := data{}
	d.Lock() //编译器会处理为data.sync.(*Mutex).Lock()调用
	defer d.Unlock()
}

//匿名字段的方法掩盖
//但是他们并不属于继承关系
type user struct{}
type manager struct {
	user
}

func (user) toString() string {
	return "user"
}
func (m manager) toString() string {
	return m.user.toString() + "; manager"
}

func testOverride() {
	var m manager
	println(m.toString())
	println(m.user.toString())
}

//方法集
type S struct{}
type T struct {
	S //匿名嵌入字段
}

func (S) sVal()  {}
func (*S) sPtr() {}
func (T) tVal()  {}
func (*T) tPtr() {}

func methodSet(a interface{}) {
	t := reflect.TypeOf(a)
	for i, n := 0, t.NumMethod(); i < n; i++ {
		m := t.Method(i)
		fmt.Println(m.Name, m.Type)
	}
}

func testMethodSet() {
	var t T
	methodSet(t)
	println("-------")
	methodSet(&t)
}

//表达式
//分为expression和value两种状态
func (n N) test() {
	fmt.Printf("test..n : %p,%d\n", &n, n)
}

func testByExpression() {
	var n N = 25
	fmt.Printf("testByExpression:%p,%d\n", &n, n)
	f1 := N.test //by Method Expression
	f1(n)
	f2 := (*N).test
	f2(&n)
}

func testMethodValue() {
	var n N = 100
	p := &n
	n++
	f1 := n.test //此时f1其实复制了n
	n++
	f2 := p.test //复制了*p，此时等于102
	n++
	fmt.Printf("testMethodValue:%p,%v\n", p, n)
	f1()
	f2()
}

//接口演示
type tester interface { //通常接口以er作为后缀
	test()
	string() string
}
type data struct{}

func (*data) test()         {}
func (data) string() string { return "" }
func testInterface() {
	var d data
	//var t tester=d //错误，d的方法集中并没有全部的实现接口
	var t tester = &d //正确，在*data中，获得了全部的方法集，实现了接口
	t.test()
	println(t.string())
}

//嵌入接口的情况
type stringer interface {
	string() string
}
type tester2 interface {
	stringer //嵌入其他接口
	test()
}
type data2 struct{}

func (*data2) test() {}
func (data2) string() string {
	return ""
}
func testInterface2() {
	var d data2
	var t tester2 = &d
	t.test()
	println(t.string())
}

//只有当接口内部的两个指针（itab，data）都为nil的时候，接口才等于nil
//由此造成的错误并不罕见
type TestError struct{}

func (*TestError) Error() string {
	return "error"
}

func testerror(x int) (int, error) {
	var err *TestError

	if x < 0 {
		err = new(TestError)
		x = 0
	} else {
		x += 100
	}
	return x, err //因为err是有类型的，所以接口TestError并不为nil
	//return x,nil //正确的做法
}

func testTestErr() {
	x, err := testerror(100)
	if err != nil {
		log.Fatalln("err!=nil") //此处将被执行
	}
	println(x)
}

//接口的类型转换
//类型推断可以将接口变量还原为原始类型，或用来判断是否实现了某个更具体的接口
type data3 int

func (d data3) String() string {
	return fmt.Sprintf("data:%d", d)
}
func testInterfaceConvert() {
	var d data3 = 15
	var x interface{} = d
	if n, ok := x.(fmt.Stringer); ok { //转换为更具体的接口类型
		fmt.Println(n)
	}
	if d2, ok := x.(data3); ok { //转换为原始类型
		fmt.Println(d2)
	}
	e := x.(error) //错误，data并不是error,推荐使用ok_idiom模式
	fmt.Println(e)
}

//ok_idiom模式配合switch
func testInterfaceOkIdiom() {
	var x interface{} = func(x int) string {
		return fmt.Sprintf("d:%d", x)
	}
	switch v := x.(type) {
	case nil:
		println("nil")
	case *int:
		println(*v)
	case func(int) string:
		println(v(100))
	case fmt.Stringer:
		fmt.Println(v)
	default:
		println("unknown")
	}
	//要注意的是，type switch不支持fallthrought
}

//interface的使用技巧
//让编译器检查，确保类型实现了指定的接口
type x int

func init() {
	//var a x = 2
	//var _ fmt.Stringer = a //包初始化函数
}

//定义函数类型，让相同签名的函数自动实现某个接口
type FuncString func() string

func (f FuncString) String() string {
	return f()
}
func testFunc() {
	var t fmt.Stringer = FuncString(func() string {
		return "hello"
	})
	fmt.Println(t)
	println(t.String())
}
