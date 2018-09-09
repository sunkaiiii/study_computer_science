package main

import (
	"bytes"
	"fmt"
	"io"
	"os"
)

type ByteCounter int

func (c *ByteCounter) Write(p []byte) (int, error) { //ByteCounter隐式的实现了io.Writer接口
	*c += ByteCounter(len(p)) //转换int位ByteCounter类型
	return len(p), nil
}

func main() {
	//ByteCounter实现了io.Writer，所以可以在Fprintf当中使用
	var c ByteCounter
	c.Write([]byte("hello"))
	fmt.Println(c) //"5",=len("hello")
	c = 0          //重置计数器
	var name = "Dolly"
	fmt.Fprintf(&c, "hello, %s", name)
	fmt.Println(c) //"12"=len("hello, Dolly")

	//接口的赋值规则
	var w io.Writer
	w = os.Stdout         //ok os.File 有wirte方法
	w = new(bytes.Buffer) //ok
	// w=time.Second //no
	w.Write([]byte("something"))

	var rwc io.ReadWriteCloser
	rwc = os.Stdout
	// rws=new (bytes.Buffer) //no 缺少close方法

	w = rwc //OK
	// rwc=w //no
}
