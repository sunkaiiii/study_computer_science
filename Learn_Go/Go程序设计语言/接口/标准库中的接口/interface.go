package main

import (
	"fmt"
	"log"
	"net/http"
	"sort"
	"syscall"
)

type StringSlice []string

//实现sort.Interface接口
func (p StringSlice) Len() int {
	return len(p)
}
func (p StringSlice) Less(i, j int) bool {
	return p[i] < p[j]
}
func (p StringSlice) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]
}

//实现http.Handler接口
type dollars float32

func (d dollars) String() string {
	return fmt.Sprintf("%.2f", d)
}

type database map[string]dollars

func (db database) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	switch req.URL.Path {
	case "/list":
		for item, price := range db {
			fmt.Fprintf(w, "%s:%s\n", item, price)
		}
	case "/price":
		item := req.URL.Query().Get("item")
		price, ok := db[item]
		if !ok {
			w.WriteHeader(http.StatusNotFound) //给他一个404错误
			fmt.Fprintf(w, "no such item :%q\n", item)
			return
		}
		fmt.Fprintf(w, "%s\n", price)
	default:
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(w, "no such page:%s\n", req.URL)
	}

}

func (db database) list(w http.ResponseWriter, req *http.Request) {
	for item, price := range db {
		fmt.Fprintf(w, "%s:%s\n", item, price)
	}
}

func (db database) price(w http.ResponseWriter, req *http.Request) {
	item := req.URL.Query().Get("item")
	price, ok := db[item]
	if !ok {
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(w, "no such item :%q\n", item)
		return
	}
	fmt.Fprintf(w, "%s\n", price)
}

//实现系统error接口
type Errno uintptr //操作系统错误码
var errors = [...]string{
	1: "operation not permitted",
	2: "no such file or directory",
	3: "no such process",
}

func (e Errno) Error() string {
	if 0 <= int(e) && int(e) < len(errors) {
		return errors[e]
	}
	return fmt.Sprintf("errno %d", e)
}

func main() {
	names := StringSlice{"321", "532532", "!23"}
	sort.Sort(names) //实现了接口，所以可以使用sort进行排序
	fmt.Println(names)

	//测试服务器
	db := database{"something": 50, "something2": 100}
	go log.Fatal(http.ListenAndServe("localhost:8000", db))

	//使用ServerMux
	mux := http.NewServeMux()
	mux.Handle("/list", http.HandlerFunc(db.list))
	mux.Handle("/price", http.HandlerFunc(db.price))
	// log.Fatal(http.ListenAndServe("localhost:8008", mux))

	//使用error接口
	var err error = syscall.Errno(2)
	fmt.Println(err.Error())
	fmt.Println(err)
}
