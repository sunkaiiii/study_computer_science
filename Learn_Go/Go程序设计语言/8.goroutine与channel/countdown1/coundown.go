package main

import (
	"fmt"
	"os"
	"time"
)

func main() {
	fmt.Println("Commencing countdown.")
	tick := time.NewTicker(1 * time.Second)
	abort := make(chan struct{})
	go func() {
		os.Stdin.Read(make([]byte, 1))
		abort <- struct{}{}
	}()
	fmt.Println("Commencing countdown.  Press return to abort.")
	for countdown := 10; countdown > 0; countdown-- {
		select {
		case <-tick.C:
			fmt.Println(countdown)
		case <-abort:
			tick.Stop() //可以及时的关闭它
			fmt.Println("Launch aborted")
			return
		}
	}
	//do some thing...
}
