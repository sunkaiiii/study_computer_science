package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"sync"
	"time"
)

type memo struct {
	f     Func
	cache map[string]*entry
	mu    sync.Mutex
}

// 用于缓存的类型
type Func func(key string) (interface{}, error)

type result struct {
	value interface{}
	err   error
}

//包含一个channel，当条目被设置之后，通道就会关闭，表明它是安全的了。
type entry struct {
	res   result
	ready chan struct{} // closed when res is ready
}

func httpGetBody(url string) (interface{}, error) {
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()
	return ioutil.ReadAll(resp.Body)
}

func New(f Func) *memo {
	return &memo{f: f, cache: make(map[string]*entry)}
}

func incomingURLs() []string {
	var urls []string
	urls = append(urls, "www.baidu.com")
	urls = append(urls, "www.google.com")
	urls = append(urls, "www.google.com")
	return urls
}

//一个线程不安全的
func (memo *memo) get(key string) (interface{}, error) {
	memo.mu.Lock()
	e := memo.cache[key]
	if e == nil {
		e = &entry{ready: make(chan struct{})}
		memo.cache[key] = e
		memo.mu.Unlock()
		e.res.value, e.res.err = memo.f(key)
		close(e.ready)
	} else {
		memo.mu.Unlock()
		<-e.ready
	}
	return e.res.value, e.res.err
}

func main() {
	m := New(httpGetBody)
	var n sync.WaitGroup
	for _, url := range incomingURLs() {
		n.Add(1)
		go func(url string) {
			start := time.Now()
			value, err := m.get(url)
			if err != nil {
				log.Print(err)
			}
			fmt.Printf("%s,%s,%d bytes\n", url, time.Since(start), len(value.([]byte)))
			n.Done()
		}(url)
	}
	n.Wait()
}
