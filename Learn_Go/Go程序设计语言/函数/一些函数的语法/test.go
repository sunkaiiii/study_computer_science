package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"time"
)

//go函数存在一种简写，如果形参或者返回值类型相同，那么类型只需要写一次
//当然我觉得这种写法看起来也比原来的写法高多少
func f(i, j, k int, s, t string) {}

//一个函数如果有命名的返回值，可以省略return语句的操作数
//但我觉得这并没有什么简洁的效果，而且还会让代码变得不容易读
func somethingFunction() (a, b int, err error) {
	resp, err := http.Get("https://www.baidu.com")
	if err != nil {
		return
	}
	resp.Body.Close()
	a, b = 0, 1
	return
}

//错误处理机制
//对于不固定或者不可预测的错误，使用指数避退策略
func waitForServer(url string) error {
	const timeout = 1 * time.Minute
	deadline := time.Now().Add(timeout)
	for tries := 0; time.Now().Before(deadline); tries++ {
		_, err := http.Head(url)
		if err == nil {
			return nil //成功
		}
		log.Printf("server not responding (%s);retrying...", err)
		time.Sleep(time.Second << uint(tries))
	}
	return fmt.Errorf("server %s failed to respond after %s", url, timeout)
}

//读取文件结束标识
func readFile() error {
	in := bufio.NewReader(os.Stdin)
	for {
		r, _, err := in.ReadRune()
		if err == io.EOF {
			break //文件读取结束
		}
		if err != nil {
			return fmt.Errorf("read failed %v", err)
		}
		fmt.Println(string(r))
	}
	return nil
}

//匿名函数
//函数返回一个函数，后者包含下一次要用到的平方数
func squares() func() int {
	var x int
	return func() int {
		x++
		return x * x
	}
}

func main() {
	//测试匿名函数
	f := squares()
	fmt.Println(f())
	fmt.Println(f())
	fmt.Println(f())
	fmt.Println(f())
	//可以看到函数里面变量的生命周期不再由他们的作用域决定
	//变量x在squares返回后依然存在，不过这个时候是隐藏在匿名函数里面的
}
