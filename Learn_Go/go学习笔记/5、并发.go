package test

import (
	"fmt"
	"os"
	"os/signal"
	"runtime"
	"sync"
	"syscall"
	"time"
)

//与defer一样，goroutine也会因“延迟执行”而立即计算并复制执行参数
var c int

func counter() int {
	c++
	return c
}

func testGoroutine() {
	a := 100
	go func(x, y int) {
		time.Sleep(time.Second) //让goroutine在main逻辑之后执行
		println("go:", x, y)
	}(a, counter()) //在这里会立即计算并复制参数
	a += 100
	println("main:", a, counter()) //于是在这里输出了c=2
	time.Sleep(time.Second * 3)
}

//使用WaitGroup来等待多个任务结束
func testSyncWaitGroup() {
	var wg sync.WaitGroup
	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			time.Sleep(time.Second)
			println("goroutine", id, "done.")
		}(i)
	}
	//可以在多处使用wait阻塞，他们都能接收到通知
	go func() {
		wg.Wait()
		println("function wait exit")
	}()

	println("main....")
	wg.Wait()
	println("main exit.")
}

var n = runtime.GOMAXPROCS(0) //go运行时同一时刻可以运行的最大的线程数

//goroutine的优先级
func testGosched() {
	runtime.GOMAXPROCS(1) //设置当前最大同时执行线程数为1
	exit := make(chan struct{})
	go func() {
		defer close(exit)
		go func() {
			println("b")
		}()
		for i := 0; i < 4; i++ {
			println("a", i)
			if i == 1 {
				runtime.Gosched() //让出当前线程，调度执行b
			}
		}
	}()
	<-exit
}

//goexit可以立即停止当前任务
func testGoexit() {
	exit := make(chan struct{})
	go func() {
		defer close(exit)  //执行
		defer println("a") //执行
		func() {
			defer func() {
				println("b", recover() == nil) //goexit不会引起panic，所以不会捕获到任何东西
			}()
			func() {
				println("c")
				runtime.Goexit()  //多层调用中使用goexit，立即终止整个调用栈
				println("c done") //不会执行
			}()
			println("b done") //不会执行
		}()
		println("a done") //不会执行
	}()

	<-exit
}

//channel用作通知
func testChannelNotification() {
	done := make(chan struct{})
	text := make(chan string)
	go func() {
		s := <-text
		println(s)
		close(done)
	}()
	text <- "hi"
	<-done
}

//异步模式带有缓冲区的channel
func testAysncChannel() {
	s := make(chan int, 3) //创建一个大小为3的缓冲区
	s <- 1
	s <- 2
	println(<-s)
	println(<-s) //缓冲区未满，不会阻塞
}

//收发群体数据
func testRageRecevieChannelInfo() {
	done := make(chan struct{})
	c := make(chan int)
	go func() {
		defer close(done)
		for x := range c { //循环获取消息，直到通道被关闭
			println(x)
		}
	}()
	c <- 1
	c <- 2
	c <- 3
	close(c) //要及时关闭通道，否则可能会导致死锁
	<-done
}

//通知可以是群体性的，也未必是通知结束，可以是任何需要表达的事件
func testChannelBroadCast() {
	var wg sync.WaitGroup
	ready := make(chan struct{})
	for i := 0; i < 3; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			println(id, ": ready.")
			<-ready //等待通道关闭
			println(id, ": running...")
		}(i)
	}
	time.Sleep(time.Second)
	println("Ready?Go!")
	close(ready) //通道关闭，goroutine中方法执行
	wg.Wait()
}

//单向通道
func singleChannel() {
	var wg sync.WaitGroup
	wg.Add(2)
	c := make(chan int)
	var send chan<- int = c //发送方
	var recv <-chan int = c //接收方
	//注意的是无法将单向通道转换回去
	go func() {
		defer wg.Done()
		for x := range recv {
			println(x) //不断地接受信息
		}
	}()
	go func() {
		defer wg.Done()
		defer close(c) //传输结束的时候，关闭发送端通道，注意的是不能在接收端使用close
		for i := 0; i < 3; i++ {
			send <- i
		}
	}()
	wg.Wait()
}

//通道的选择
//如果要处理多个通道，可选用select语句。他会随机选择一个可用通道做手法操作
func testSelect() {
	var wg sync.WaitGroup
	wg.Add(2)
	a, b := make(chan int), make(chan int)
	go func() { //接收端
		defer wg.Done()
		for {
			var (
				name string
				x    int
				ok   bool
			)
			select {
			case x, ok = <-a:
				name = "a"
			case x, ok = <-b:
				name = "b"
			}
			if !ok {
				return
			}
			println(name, x)
		}
	}()

	go func() {
		defer wg.Done()
		defer close(a)
		defer close(b)
		for i := 0; i < 10; i++ {
			select { //随机选择一个发送的channel
			case a <- i:
			case b <- i * 10:
			}
		}
	}()
	wg.Wait()
}

//如果等全部通道消息处理结束（close），可将已完成的通道设置为nil，这样他就会阻塞
func testNilSelect() {
	var wg sync.WaitGroup
	wg.Add(3)
	a, b := make(chan int), make(chan int)
	go func() {
		defer wg.Done()
		for {
			select {
			case x, ok := <-a:
				if !ok { //通道关闭，则设置为nil，阻塞
					a = nil
					break
				}
				println("a", x)
			case x, ok := <-b:
				if !ok {
					b = nil
					break
				}
				println("b", x)
			}
			if a == nil && b == nil { //如果宣布结束，则退出循环
				return
			}
		}
	}()

	go func() {
		defer wg.Done()
		defer close(a)
		for i := 0; i < 3; i++ {
			a <- i
		}
	}()

	go func() {
		defer wg.Done()
		defer close(b)
		for i := 0; i < 5; i++ {
			b <- i * 10
		}
	}()
	wg.Wait()
}

//即使是同一个通道，也可以使用select随机case执行
func selectBySingleChannel() {
	var wg sync.WaitGroup
	wg.Add(2)
	c := make(chan int)
	go func() {
		defer wg.Done()
		var v int
		var ok bool
		for {
			select {
			case v, ok = <-c:
				println("a1:", v)
			case v, ok = <-c:
				println("a2", v)
			}
			if !ok {
				return
			}
		}
	}()
	go func() {
		defer wg.Done()
		defer close(c)

		for i := 0; i < 10; i++ {
			select {
			case c <- i:
			case c <- i * 10:
			}
		}
	}()
	wg.Wait()
}

//当所有的通道都不可用时，select会执行default语句。
//如此可避开select阻塞，但需注意的是处理外层循环，避免陷入空耗
func testSelectDefault() {
	done := make(chan struct{})
	c := make(chan int)
	go func() {
		defer close(done)
		for {
			select {
			case x, ok := <-c:
				if !ok {
					return
				}
				fmt.Println("data:", x)
			default: //避免select阻塞
				fmt.Println(time.Now()) //处理循环，避免空耗
				time.Sleep(time.Second)
			}

		}
	}()
	time.Sleep(time.Second * 5)
	c <- 100
	close(c)
	<-done
}

//使用工厂模式将goroutine与通道绑定
type recevier struct {
	sync.WaitGroup
	data chan int
}

func newReceiver() *recevier {
	r := &recevier{
		data: make(chan int),
	}
	r.Add(1) //隐式调用sync.WaitGroup.add
	go func() {
		defer r.Done()
		for x := range r.data { //接收消息，直到通道关闭
			println("recv:", x)
		}
	}()
	return r
}

func testRecevier() {
	r := newReceiver()
	r.data <- 1
	r.data <- 2
	close(r.data)
	r.Wait()
}

//用通道实现信号量
func semaphoreByChannel() {
	runtime.GOMAXPROCS(4)
	var wg sync.WaitGroup
	sem := make(chan struct{}, 2)
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			sem <- struct{}{}        //获得信号
			defer func() { <-sem }() //释放信号
			time.Sleep(time.Second * 2)
			fmt.Println(id, time.Now())
		}(i)
	}
	wg.Wait()
}

//标准库提供了timeout和tick channel的实现
func tikeChannel() {
	go func() {
		for {
			select {
			case <-time.After(time.Second * 5):
				fmt.Println("timeout...")
				os.Exit(0)
			}
		}
	}()

	go func() {
		tick := time.Tick(time.Second)
		for {
			select {
			case <-tick:
				fmt.Println(time.Now())
			}
		}
	}()
	<-chan (struct{})(nil)
}

//捕获INT、TERM信号
//当捕获SIGINT的时候，执行对应函数
var exits = &struct {
	sync.RWMutex
	funcs    []func()
	singnals chan os.Signal
}{}

func atexit(f func()) {
	exits.Lock()
	defer exits.Unlock()
	exits.funcs = append(exits.funcs, f)
}

func waitExit() {
	if exits.singnals == nil {
		exits.singnals = make(chan os.Signal)
		signal.Notify(exits.singnals, syscall.SIGINT, syscall.SIGTERM) //响应SIGINT和SIGTERM,如果没有声明响应信号，则所有的信号都会发送到通道中
	}
	exits.RLock()
	for _, f := range exits.funcs {
		defer f() //即便某些函数panic，延迟调用可以确保后续的执行
	}
	exits.RUnlock()
	<-exits.singnals //等待一个信号
}
func testAtexit() {
	atexit(func() { println("exit1...") })
	atexit(func() { println("exit2....") })
	waitExit()
}

//将发往通道的数据打包，减少传输次数，可以有效地提升性能
//从实现上来说，通道队列使用的其实还是锁的机制，单次更多数据的处理，可以减少锁造成的性能问题
const (
	max     = 50000000 //数据统计上限
	block   = 500
	bufsize = 100
)

func lowPerfChannel() { //普通模式：每次传递一个整数

	done := make(chan struct{})
	c := make(chan int, bufsize)
	go func() {
		count := 0
		for x := range c {
			count += x
		}
		close(done)
	}()
	for i := 0; i < max; i++ {
		c <- i
	}
	close(c)
	<-done
}

func highPerfChannel() { //块模式，每次将500个数字打包传输
	done := make(chan struct{})
	c := make(chan [block]int, bufsize)
	go func() {
		count := 0
		for a := range c {
			for _, x := range a {
				count += x
			}
		}
		close(done)
	}()
	for i := 0; i < max; i += block { //使用数组对数据打包
		var b [block]int
		for n := 0; n < block; n++ {
			b[n] = i + n
			if i+n == max-1 {
				break
			}
		}
		c <- b
	}
	close(c)
	<-done
}

type mutexData struct {
	sync.Mutex
}

func (d *mutexData) noLockTest(s string) { //使用*data来避免数据复制造成的锁失效
	d.Lock()
	defer d.Unlock()

	for i := 0; i < 5; i++ {
		println(s, i)
		time.Sleep(time.Second)
	}
}

func testNoLockTest() {
	var wg sync.WaitGroup
	wg.Add(2)
	var d mutexData
	go func() {
		defer wg.Done()
		d.noLockTest("read")
	}()

	go func() {
		defer wg.Done()
		d.noLockTest("write")
	}()
	wg.Wait()
}
