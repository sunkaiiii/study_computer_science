package test

import (
	"fmt"
)

func main() {
	const v = 20
	var a byte = 10
	b := v + a //此操作会隐式将v转换为uint8
	fmt.Printf("%T,%v\n", b, b)

	c, d, e, x := 1, 2, 3, 2

	//swirch语句的使用,可以使用变量值
	switch x {
	case c, d:
		println("c|d")
	case e:
		println("e")
	case 4:
		println("f")
		fallthrough //switch不必声明break，声明fallthrough将不会执行break
	default:
		println("z")
	}

	//范围for迭代，完成数据迭代，支持字符串，数组，数组指针，切片，字典，通道类型，返回索引+数据
	data := [3]string{"a", "b", "c"}
	for i, s := range data {
		println(i, s)
	}
	//目前还不支持自定义类型的迭代

	//使用range会复制目标数据，可以看到range返回的依旧是复制值
	data2 := [3]int{1, 2, 3}
	for i, x := range data2 {
		if i == 0 {
			data2[0] += 100
			data2[1] += 100
			data2[2] += 100
		}
		fmt.Printf("x:%d,data :%d\n", x, data2[i])
	}
	//使用切片将返回引用，复制的仅仅是引用，当修改data时，对于x来说他的值也得到了修改
	for i, x := range data2[:] {
		if i == 0 {
			data2[0] += 100
			data2[1] += 100
			data2[2] += 100
		}
		fmt.Printf("x:%d,data :%d\n", x, data2[i])
	}
	//如果range的目标是函数，也仅仅会执行一次
	for i, x := range getData() {
		println(i, x)
	}
	i := 0
outer:
	for {
		for {
			for {
				for {
					i++
					if i == 5 {
						break outer //在多层循环中指定跳出到最外层级
					}
				}
			}
		}
	}

	//这个就是指针参数导致是参变量被分配到堆上的简单实例
	heapX := 100
	p := &heapX
	test(p)
}
func getData() []int {
	return []int{1, 2, 3}
}

func test(p *int) {
	go func() {
		println(p)
	}()
}
