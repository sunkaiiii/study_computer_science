package main

import (
	"bytes"
	"fmt"
	"io"
	"os"
)

//一个类型断言和检查的函数
func writeString(w io.Writer, s string) (n int, err error) {
	type stringWriter interface {
		WriteString(string) (n int, err error)
	}

	if sw, ok := w.(stringWriter); ok {
		return sw.WriteString(s) //避免了内存分配
	}
	return w.Write([]byte(s))
}

//使用switch进行类型分支
func interfaceType(x interface{}) {
	switch x.(type) {
	case nil:
		fmt.Println("null")
	case int, uint:
		fmt.Println("int")
	case bool:
		fmt.Println("bool")
	}
	//类型分支不允许fallthrough
}

func main() {
	var w io.Writer
	w = os.Stdout
	//f := w.(*os.File) //成功， f==os.Stdout
	//c := w.(*bytes.Buffer) //崩溃，接口持有的是os.File，而不是byte.Buffer

	//wr := w.(io.ReadWriter) //os.File中有read和write方法

	if f, ok := w.(*bytes.Buffer); ok {
		//不会崩溃的方法
		fmt.Println(f)
	}
}
