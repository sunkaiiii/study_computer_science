package main

import (
	"fmt"
	"image/color"
	"math"
	"sync"
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

	distanceFromP := p.Distance //方法变量
	fmt.Println(distanceFromP(q))
	var orgin Point
	fmt.Println(distanceFromP(orgin))
	scaleP := p.ScaleBy
	scaleP(2) //p的数据会因此改变
	scaleP(3)
	scaleP(10)

	scaleP2 := (*Point).ScaleBy //方法表达式
	scaleP2(&p, 2)
	fmt.Println(p)
	fmt.Printf("%T\n", scaleP2)
}

//结构体的组合
type ColoredPoint struct {
	Point
	Color color.RGBA
}

//下面这个例子展示了一个简单的缓存实现，其中使用了两个包级的变量：互斥锁和map，互斥锁会保护map的数据
var (
	mu      sync.Mutex //保护mapping
	mapping = make(map[string]string)
)

func LookUp(key string) string {
	mu.Lock()
	v := mapping[key]
	mu.Unlock()
	return v
}

//下面这个版本的功能和上面完全相同，但是将两个相关变量放到了一个包级别变量cache中
var cache = struct {
	sync.Mutex
	mapping map[string]string
}{
	mapping: make(map[string]string),
}

func LookUp2(key string) string {
	cache.Lock()
	v := cache.mapping[key]
	cache.Unlock()
	return v
}
