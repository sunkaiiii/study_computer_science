package main

import (
	"fmt"
	"image/color"
	"math"
)

type Point struct {
	X float64
	Y float64
}

//函数
func Distance(p, q Point) float64 {
	return math.Hypot(q.X-p.X, q.Y-p.Y)
}

//方法
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X-p.X, q.Y-p.Y)
}

//指针接受者方法
//这样执行方法之后，就会更新实参变量
//通常，指针方式和传值方式不应该同时出现
func (p *Point) ScaleBy(factor float64) {
	p.X *= factor
	p.Y *= factor
}

//不过go语言禁止本身类型是指针的类型声明方法

func main() {
	q := Point{1, 2}
	p := Point{4, 6}

	//使用函数
	fmt.Println(Distance(p, q))
	//使用方法
	fmt.Println(p.Distance(q))
	//使用指针接受者方法
	p.ScaleBy(32.0)
	//上面这句话被编译器隐形的转换成了指针调用方法
	fmt.Println(p)
	//效果等同于,只有变量才允许这么做
	(&p).ScaleBy(32.0)

	//同理,指针类型的变量会被编译器解引用，以此来执行distance
	fmt.Println((&p).Distance(q))

	var cp ColoredPoint
	//组合过后的结构体，可以得到Point类型的所有字段，和更多的自有字段
	cp.X = 1
	cp.Point.X = 1
	//以上两句效果是一样的

	//同样ColoredPoint可以使用Point的方法
	fmt.Println(cp.Distance(p))

	//但是他们并不是基类于继承的关系
	//p.Distance(cp) 这句编译是不通过的
	p.Distance(cp.Point) //Distance方法需要的是一个Point，需要显示的传递
}

//结构体的组合
type ColoredPoint struct {
	Point
	Color color.RGBA
}
