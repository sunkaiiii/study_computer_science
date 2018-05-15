package test

import (
	"fmt"
	"reflect"
	"strings"
	"unsafe"
)

func testReflect() {
	type X int
	var a X = 100
	t := reflect.TypeOf(a)
	fmt.Println(t.Name(), t.Kind()) //Type代表着静态类型（真实类型），Kind代表着对应的底层类型
}

//反射复合类型
func multiReflect() {
	a := reflect.ArrayOf(10, reflect.TypeOf(byte(0)))
	b := reflect.MapOf(reflect.TypeOf(""), reflect.TypeOf(0))
	fmt.Println(a, b)
}

//获取结构体指针的基类型之后，才能遍历它的字段
type user2 struct {
	name string
	age  int
}

type manager2 struct {
	user
	title string
}

func testReflectStruct() {
	var m manager2
	t := reflect.TypeOf(&m)
	if t.Kind() == reflect.Ptr {
		t = t.Elem()
	}
	for i := 0; i < t.NumField(); i++ {
		f := t.Field(i)
		fmt.Println(f.Name, f.Type, f.Offset)
		if f.Anonymous { //输出匿名字段结构
			for x := 0; x < f.Type.NumField(); x++ {
				af := f.Type.Field(x)
				fmt.Println(" ", af.Name, af.Type)
			}
		}
	}
}

//对于匿名字段，可以用多级索引（按定义顺序）直接访问
func multiIndexReflectStruct() {
	var m manager
	t := reflect.TypeOf(m)
	name, _ := t.FieldByName("name") //按名称查找
	fmt.Println(name.Name, name.Type)

	age := t.FieldByIndex([]int{0, 1}) //按多级索引查找
	fmt.Println(age.Name, age.Type)
}

//可以用反射提取struct tag，还可以自动分解
type newUser struct {
	name string `filed:"name" type:"varchar(50)"`
	age  int    `filed:"age" type:"int"`
}

func testRefelctStructTag() {
	var u newUser
	t := reflect.TypeOf(u)
	for i := 0; i < t.NumField(); i++ {
		f := t.Field(i)
		fmt.Printf("%s:%s %s\n", f.Name, f.Tag.Get("filed"), f.Tag.Get("type"))
	}
}

//辅助判断方法Implements，ConvertibleTo，AssignableTo
type X int

func (X) String() string {
	return ""
}
func reflectHelper() {
	var a X
	t := reflect.TypeOf(a)

	//Implements的调用方法比较别扭
	st := reflect.TypeOf((*fmt.Stringer)(nil)).Elem()
	fmt.Println(t.Implements(st))

	it := reflect.TypeOf(0)
	fmt.Println(t.ConvertibleTo(it))

	fmt.Println(t.AssignableTo(st), t.AssignableTo(it))
}

//不能对非导出字段进行设置操作,要进行指针转换，无论是当前包还是外包
func getReflectValue() {
	type User struct {
		Name string
		code int
	}
	p := new(User)
	v := reflect.ValueOf(p).Elem() //如果不加Elem，元素将是不可取地址和不可读写的

	name := v.FieldByName("Name")
	code := v.FieldByName("code")

	fmt.Println("name:canaddr=%v,canset=%v\n", name.CanAddr(), name.CanSet())
	fmt.Println("name:canaddr=%v,canset=%v\n", code.CanAddr(), code.CanSet())
	if name.CanSet() {
		name.SetString("Tom")
	}
	if code.CanAddr() {
		*(*int)(unsafe.Pointer(code.UnsafeAddr())) = 100
	}
	fmt.Println("%+v\n", p)
}

//通过Interface方法进行类型推断和转换
func typeInterfaceConvert() {
	type user struct {
		Name string
		Age  int
	}
	u := user{
		"sunkai",
		60,
	}
	v := reflect.ValueOf(&u)
	if !v.CanInterface() {
		println("CanInterface fail.")
		return
	}

	p, ok := v.Interface().(*user) //取到interface之后，再转换成user对应的结构体
	if !ok {
		println("Interface fail.")
		return
	}
	p.Age++
	fmt.Printf("%+v\n", u)
}

//接口的nil判断是值+类型为nil才为nil，这造成了很多麻烦，解决方法是通过IsNil判断值是否为nil
func judgeInterfaceIsNil() {
	var a interface{} = nil
	var b interface{} = (*int)(nil)

	fmt.Println(a == nil)
	fmt.Println(b == nil, reflect.ValueOf(b).IsNil()) //用IsNil判断值是否为空

	//也可以使用unsafe转换后直接判断iface.data是否为零值
	iface := (*[2]uintptr)(unsafe.Pointer(&b))
	fmt.Println(iface, iface[1] == 0)
}

//动态调用方法
type Y struct{}

func (Y) Test(x, y int) (int, error) {
	return x + y, fmt.Errorf("err:%d", x+y)
}

func testReflectFunction() {
	var a Y
	v := reflect.ValueOf(&a)
	m := v.MethodByName("Test")
	in := []reflect.Value{
		reflect.ValueOf(1),
		reflect.ValueOf(2),
	}
	out := m.Call(in)
	for _, v := range out {
		fmt.Println(v)
	}

}

//对于变参来说，CallSlice要更方便一些
func (Y) Format(s string, a ...interface{}) string {
	return fmt.Sprintf(s, a...)
}

func testRefelctCallSlice() {
	var a Y
	v := reflect.ValueOf(&a)
	m := v.MethodByName("Format")
	out := m.Call([]reflect.Value{
		reflect.ValueOf("%s=%d"),
		reflect.ValueOf("x"),
		reflect.ValueOf(100),
	})
	fmt.Println(out)

	//使用callSlice
	out = m.CallSlice([]reflect.Value{
		reflect.ValueOf("%s=%d"),
		reflect.ValueOf([]interface{}{"x", 100}),
	})
	fmt.Println(out)
}

//反射库提供了内置函数make和new的对应操作，其中makeFunc可以实现一类通用模板
func generateFunc(args []reflect.Value) (results []reflect.Value) {
	if len(args) == 0 {
		return nil
	}

	var ret reflect.Value

	switch args[0].Kind() {
	case reflect.Int:
		n := 0
		for _, a := range args {
			n += int(a.Int())
		}
		ret = reflect.ValueOf(n)
	case reflect.String:
		ss := make([]string, 0, len(args))
		for _, s := range args {
			ss = append(ss, s.String())
		}
		ret = reflect.ValueOf(strings.Join(ss, ""))
	}
	results = append(results, ret)
	return
}

func makeGenerateFunc(fptr interface{}) {
	fn := reflect.ValueOf(fptr).Elem()             //传入的是函数的地址，是unAdressable的，Elem()将解析其对应的函数
	v := reflect.MakeFunc(fn.Type(), generateFunc) //这里是构建的关键
	fn.Set(v)
}
func callGenerateFunc() {
	var intAdd func(x, y int) int
	var strAdd func(a, b string) string

	makeGenerateFunc(&intAdd)
	makeGenerateFunc(&strAdd)

	println(intAdd(100, 200))
	println(strAdd("hello", "world!"))

}
