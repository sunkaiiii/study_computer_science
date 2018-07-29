package main

import (
	"fmt"
	"os"

	"golang.org/x/net/html"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "outline:%v\n", err)
		os.Exit(1)
	}
	outline(nil, doc)
}

func outline(stack []string, n *html.Node) {
	//这是一个深度优先遍历
	if n.Type == html.ElementNode {
		//把标签压栈,在这里其实是没有出栈操作的
		//当outline递归调用的时候，被调用的函数回家收到stack的副本，尽管调用者可能会对slice进行元素的添加，但这并不会修改调用者原来传递的元素
		stack = append(stack, n.Data)
		fmt.Println(stack)
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		outline(stack, c)
	}
}
