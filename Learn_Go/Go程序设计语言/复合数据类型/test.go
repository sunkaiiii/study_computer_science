package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"sort"
	"unicode"
	"unicode/utf8"
)

func main() {
	//注意两种声明的区别，a是一个数组，b是一个slice
	a := [...]int{0, 1, 2, 3, 4, 5, 6, 7}
	b := []int{1, 2, 3}
	reverse(a[:])
	reverse(b)
	fmt.Println(a)
	fmt.Println(b)
	c := []int{1, 2, 3}
	fmt.Println(c)
	//尽管b，c的声明是一样的，但是slice是不能进行比较的
	//fmt.Println(b == c)
	//slice唯一能进行比较的是nil
	//slice进行比较的方法是对[]byte使用bytes.Equal

	//实际调用appendInt来看看
	var x, y []int
	for i := 0; i < 10; i++ {
		y = appendInt(x, i)
		fmt.Printf("%d cap=%d\t%v\n", i, cap(y), y)
		x = y
	}
	//不仅仅在调用append的情况下需要更新slice变量
	//对于任何函数，只要有可能改变slice的长度或者容量，抑或是是的slice指向不同的底层数组
	//都需要更新slice变量
	//appendInt可以添加多个值
	x = appendInt(x, 1, 2, 3, 4, 5)
	fmt.Println(x)

	data := []string{"1", "", "3"}
	fmt.Printf("%q\n", nonempty(data))
	//执行完nonempty之后，底层元素发生了变化
	fmt.Printf("%q\n", data)
	data = []string{"1", "", "3"}
	fmt.Printf("%q\n", nonempty2(data))
	fmt.Printf("%q\n", data)

	//遍历map所获得的值的顺序是不相同的
	m := map[int]string{
		0: "a",
		1: "b",
		2: "c",
		3: "d",
		4: "e",
	}
	var values []string
	for k, v := range m {
		fmt.Printf("%d\t%s\n", k, v)
		values = append(values, v)
	}
	//可以使用sort对字符串进行排序
	sort.Strings(values)
	fmt.Println(values)

	//既然键值是int，可以用另外一种方法
	values = make([]string, len(m))
	for k, v := range m {
		values[k] = v
	}
	fmt.Println(values)

	//有时候，我们需要map并且他的键是slice，那么可以按照这个方法做
	//这个方法演示了一个字符串列表对于Add函数调用的次数，并由map来记录
	s := []string{"1"}
	s2 := []string{"@"}
	Add(s)
	Add(s)
	Add(s)
	Add(s2)
	fmt.Println(Count(s), Count(s2))

	//charCount()
}

//当传入的是slice的时候，对于slice修改就等于对底层数组的修改
//实际上的感觉就和c语言传递数组默认传递首元素的引用差不多
func reverse(s []int) {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
}

//理解append函数
func appendInt(x []int, y ...int) []int {
	var z []int
	zlen := len(x) + len(y)
	if zlen <= cap(x) {
		//slice还有增长空间，扩展slice内容
		z = x[:zlen]
	} else {
		//slice已经没有空间，为他分配一个新的底层数组
		//为了达到分摊线性复杂性，容量扩展一倍
		zcap := zlen
		if zcap < 2*len(x) {
			zcap = 2 * len(x)
		}
		z = make([]int, zlen, zcap)
		copy(z, x)
	}
	copy(z[len(x):], y)
	return z
}

func nonempty(strings []string) []string {
	//演示slice就地修改算法
	//返回一个新的slice，里面的元素都是非空字符串
	//在函数调用的过程中，底层数组的元素发生了改变
	i := 0
	for _, s := range strings {
		if s != "" {
			strings[i] = s
			i++
		}
	}
	return strings[:i]
}

func nonempty2(strings []string) []string {
	//nonempty还有第二种写法
	//使用append方法
	out := strings[:0]
	for _, s := range strings {
		if s != "" {
			out = append(out, s)
		}
	}
	return out
}

var m = make(map[string]int)

func k(list []string) string {
	return fmt.Sprintf("%q", list)
}

func Add(list []string) {
	m[k(list)]++
}

func Count(list []string) int {
	return m[k(list)]
}

func charCount() {
	//统计Unicode字符的个数
	counts := make(map[rune]int)
	var utflen [utf8.UTFMax + 1]int
	invalid := 0
	in := bufio.NewReader(os.Stdin)
	for {
		r, n, err := in.ReadRune()
		if err == io.EOF {
			break
		}
		if err != nil {
			fmt.Fprintf(os.Stderr, "charcount:%v\n", err)
			os.Exit(1)
		}
		if r == unicode.ReplacementChar && n == 1 {
			invalid++
			continue
		}
		counts[r]++
		utflen[n]++
	}
	fmt.Printf("rune\tcount\n")
	for c, n := range counts {
		fmt.Printf("%q\t%d\n", c, n)
	}
	fmt.Print("\nlen\tcount\n")
	for i, n := range utflen {
		if i > 0 {
			fmt.Printf("%d\t%d\n", i, n)
		}
	}
	if invalid > 0 {
		fmt.Printf("\n%d invalid UTF-8 characters\n", invalid)
	}
}
