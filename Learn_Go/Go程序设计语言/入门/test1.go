package main

import (
	"bytes"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"math/cmplx"
	"os"
	"strings"
	"unicode/utf8"
)

func main() {
	//go的取模所得出的余数的正负号，有被除数决定
	a := -4
	b := 9
	c := -9
	b = a % b
	c = a % c
	fmt.Println(b, c)

	//与c语言一样，go语言存在字符溢出的问题
	var u uint8 = 255
	fmt.Println(u, u+1, u*u)
	var i int8 = 127
	fmt.Println(i, i+1, i*i)

	//go支持复数
	var x complex128 = complex(1, 2) //1+2i
	var y complex128 = complex(3, 4) //3+4i
	fmt.Println(x * y)
	fmt.Println(real(x * y))
	fmt.Println(imag(x * y))

	//绘制一个Mandelbrot集
	//createMandelbrot()

	//字符串会有越界问题
	s := "hello word"
	//println(s[len(s)])

	//字符串是不可变的，这就意味着他可以安全的共享同一个内存，并且复制的开销将会很小
	s2 := s[:5]
	s3 := s[7:]
	fmt.Println(&s, &s2, &s3)

	//使用``标记的原生字符串可以忽视转义符
	text := `kjdklajj\gdwqerkv\nawdsjkewlnbv\a
	asdfaweghsrhsrenb`
	println(text)

	//Go默认使用utf8编码，这使得喝多操作都无需解码
	//可以判断某个字符串是否为另一个的前缀
	s = "123456789"
	s2 = "123"
	s3 = "456"
	fmt.Println(HasPrefix(s, s2))
	fmt.Println(HasSuffix(s, s2))
	fmt.Println(Contains(s, s3))

	//utf8编码的处理
	s = "Hello, 世界"
	fmt.Println(len(s))
	fmt.Println(utf8.RuneCountInString(s)) //本质上s是9个码点的字符串编码
	//可以使用utf8解码器来处理每一个字符
	for i := 0; i < len(s); {
		r, size := utf8.DecodeRuneInString(s[i:])
		fmt.Printf("%d\t%c\n", i, r)
		i += size
	}

	//Go当中，有4个标准包对于字符串操作特别重要
	//strings提供了许多函数，包括搜索、替换、比较、修整、切分、连接字符串
	//bytes包也有类似的函数，用于操作字节slice
	//strconv主要用于转换布尔值、整数、浮点数为与之对应的字符串形式，或者反过来转换
	//unicode有判断文字符号值特性的函数
	fmt.Println(basename("a/b/c.go"))
	fmt.Println(basename("c.d.go"))
	fmt.Println(basename("abc"))

	fmt.Println(basenameUseLib("a/b/c.go"))
	fmt.Println(basenameUseLib("c.d.go"))
	fmt.Println(basenameUseLib("abc"))

	fmt.Println(comma("123456789"))
	//演示字符串拼接
	ints := []int{1, 2, 3, 4, 5, 6}
	fmt.Println(intsToString(ints))

	//声明常量
	//使用itoa，常量表达式会从0开始依次类推
	type Weekday int
	const (
		Sunday Weekday = iota
		Monday
		Tuesday
		WednesDay
		Thursday
		Friday
		Saturday
	)
	fmt.Println(Sunday, Monday, Tuesday, WednesDay, Thursday, Friday, Saturday)
}

//判断是否为另一个字符串的前缀
func HasPrefix(s, prefix string) bool {
	return len(s) >= len(prefix) && s[:len(prefix)] == prefix
}

//判断是否为另一个字符串的后缀
func HasSuffix(s, suffix string) bool {
	return len(s) >= len(suffix) && s[len(s)-len(suffix):] == suffix
}

//判断是否为字串
func Contains(s, substr string) bool {
	for i := 0; i < len(s); i++ {
		if HasPrefix(s[i:], substr) {
			return true
		}
	}
	return false
}

//移除路径部分和.后缀
func basename(s string) string {
	//将最后一个/之前的部分全部舍弃
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] == '/' {
			s = s[i+1:]
			break
		}
	}
	//保留最后一个'.'之前的所有内容
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] == '.' {
			s = s[:i]
			break
		}
	}
	return s
}

func basenameUseLib(s string) string {
	slash := strings.LastIndex(s, "/") //如果没有找到"/",则slash取值为-1
	s = s[slash+1:]
	if dot := strings.LastIndex(s, "."); dot >= 0 {
		s = s[:dot]
	}
	return s
}

func comma(s string) string {
	//向表示十进制非负数的字符串中插入逗号
	//这是一个递归实现
	n := len(s)
	if n <= 3 {
		return s
	}
	return comma(s[:n-3]) + "," + s[n-3:]
}

func createMandelbrot() {
	const (
		xmin, ymin, xmax, ymax = -2, -2, +2, +2
		width, height          = 10240, 10240
	)
	img := image.NewRGBA(image.Rect(0, 0, width, height))
	for py := 0; py < height; py++ {
		y := float64(py)/height*(ymax-ymin) + ymin
		for px := 0; px < width; px++ {
			x := float64(px)/width*(xmax-xmin) + xmin
			z := complex(x, y)
			img.Set(px, py, mandelbrot(z))
		}
	}
	f, _ := os.Create("1.png")
	png.Encode(f, img)
}

func intsToString(values []int) string {
	//高效拼接字符串
	//bytes.Buffer的用途极广
	var buf bytes.Buffer
	buf.WriteByte('[')
	for i, v := range values {
		if i > 0 {
			buf.WriteString(", ")
		}
		fmt.Fprintf(&buf, "%d", v)
	}
	buf.WriteByte(']')
	return buf.String()
}

func mandelbrot(z complex128) color.Color {
	const iterations = 200
	const contrast = 15

	var v complex128
	for n := uint8(0); n < iterations; n++ {
		v = v*v + z
		if cmplx.Abs(v) > 2 {
			return color.Gray{255 - contrast*n}
		}
	}
	return color.Black
}
