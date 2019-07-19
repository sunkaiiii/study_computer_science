package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"sync"
	"time"
)

var done = make(chan struct{})

func cancelled() bool {
	select {
	case <-done:
		return true
	default:
		return false
	}
}

func walkDir(dir string, n *sync.WaitGroup, fileSizes chan<- int64) {
	defer n.Done()
	if cancelled() { //如果轮询状态是取消，就直接返回
		return
	}
	for _, entry := range dirents(dir) {
		if entry.IsDir() {
			n.Add(1)
			subdir := filepath.Join(dir, entry.Name())
			go walkDir(subdir, n, fileSizes)
		} else {
			fileSizes <- entry.Size()
		}
	}
}

//如果不受控制的话，这个程序会在高峰期创建成百上千个goroutine
//于是需要加一个限制条件
var sema = make(chan struct{}, 100)

func dirents(dir string) []os.FileInfo {
	select { //这种select操作可以将取消时的延迟从几百毫秒降低到几十毫秒
	case sema <- struct{}{}:
	case <-done:
		return nil
	}
	defer func() {
		<-sema
	}()
	entries, err := ioutil.ReadDir(dir)
	if err != nil {
		fmt.Fprintf(os.Stderr, "du1: %v\n", err)
		return nil
	}
	return entries
}

var verbose = flag.Bool("v", false, "show verbose progress messages")

func main() {
	//两个goroutine，后台的goroutine调用walkDir来遍历命令行给出的每一个路径
	//主goroutine会从中获取大小相加
	flag.Parse()
	roots := flag.Args()

	if len(roots) == 0 {
		roots = []string{"."}
	}

	var tick <-chan time.Time
	if *verbose {
		tick = time.Tick(500 * time.Millisecond)
	}
	//开始遍历
	fileSizes := make(chan int64)
	var n sync.WaitGroup //使用sync.WaitGroup来对仍旧活跃的walkDir调用进行计数
	for _, root := range roots {
		n.Add(1)
		go walkDir(root, &n, fileSizes)
	}
	go func() {
		n.Wait()
		close(fileSizes)
	}()
	var nfiles, nbytes int64
loop:
	for {
		select {
		case <-done: //如果发送了close doen的广播，则程序将会执行完收尾工作之后关闭
			for size := range fileSizes {
				nfiles++
				nbytes += size
				return
			}
		case size, ok := <-fileSizes:
			if !ok {
				break loop
			}
			nfiles++
			nbytes += size
		case <-tick:
			printDiskUsage(nfiles, nbytes) //如果-v flag没有在运行时传入的话，tick这个channel就会保持nill，这样在select里的case就相当于禁用了
		}
	}
	printDiskUsage(nfiles, nbytes)
}
func printDiskUsage(nfiles, nbytes int64) {
	fmt.Printf("%d files  %.1f GB\n", nfiles, float64(nbytes)/1e9)
}
