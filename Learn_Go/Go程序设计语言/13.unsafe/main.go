package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

//自行定义的深度相等函数
func equal(x, y reflect.Value, seen map[comparison]bool) bool {
	if !x.IsValid() || !y.IsValid() {
		return x.IsValid() == y.IsValid()
	}
	if x.Type() != y.Type() {
		return false
	}

	// ...cycle check omitted (shown later)...

	switch x.Kind() {
	case reflect.Bool:
		return x.Bool() == y.Bool()
	case reflect.String:
		return x.String() == y.String()

	// ...numeric cases omitted for brevity...

	case reflect.Chan, reflect.UnsafePointer, reflect.Func:
		return x.Pointer() == y.Pointer()
	case reflect.Ptr, reflect.Interface:
		return equal(x.Elem(), y.Elem(), seen)
	case reflect.Array, reflect.Slice:
		if x.Len() != y.Len() {
			return false
		}
		for i := 0; i < x.Len(); i++ {
			if !equal(x.Index(i), y.Index(i), seen) {
				return false
			}
		}
		return true

		// ...struct and map cases omitted for brevity...
	}
	panic("unreachable")
}
func Equal(x, y interface{}) bool {
	seen := make(map[comparison]bool)
	return equal(reflect.ValueOf(x), reflect.ValueOf(y), seen)
}

type comparison struct {
	x, y unsafe.Pointer
	t    reflect.Type
}

func main() {
	fmt.Println(unsafe.Sizeof(float64(0))) //可以得到float在内存当中的大小
	//还可以查看内存当中的对其方式
	var x struct {
		a bool
		b int16
		c []int
	}
	fmt.Println(unsafe.Sizeof(x))
	fmt.Println(unsafe.Sizeof(x.c)) //64位系统里是24，应该是slice默认有一些初始大小
	fmt.Println(unsafe.Alignof(x))
	fmt.Println(unsafe.Offsetof(x.c))

	//虽然以上这几个函数在unsafe包，但是调用他们倒不是真正的不安全。
	//而且对于理解内存优化 还是很有帮助的

	//深度相等判断
	var a, b []string = nil, []string{}
	fmt.Println(reflect.DeepEqual(a, b)) //false
}
