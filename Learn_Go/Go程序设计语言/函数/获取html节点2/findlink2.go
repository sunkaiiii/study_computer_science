package main

import (
	"fmt"
	"net/http"
	"os"

	"golang.org/x/net/html"
)

func main() {
	for _, url := range os.Args[1:] {
		links, err := findLinks(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "findlink2:%v\n", err)
			continue
		}
		for _, link := range links {
			fmt.Println(link)
		}
	}
}

//findLinks发起一个http get请求，解析返回的HTML页面，并返回所有链接
func findLinks(url string) ([]string, error) {
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	if resp.StatusCode != http.StatusOK {
		resp.Body.Close()
		//为了让资源得到释放，要显示的关闭resp.Body
		return nil, fmt.Errorf("getting %s:%s", url, resp.Status)
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return nil, fmt.Errorf("parsing %s as HTML :%v", url, err)
	}
	defer forEachNode(doc, startElement, endElement)
	return visit(nil, doc), nil
}

//遍历HTML树上的所有节点，找到超链接，并i企鹅将字符串添加到slice中，最终返回slice
func visit(links []string, n *html.Node) []string {
	if n.Type == html.ElementNode && n.Data == "a" {
		for _, a := range n.Attr {
			if a.Key == "href" {
				links = append(links, a.Val)
			}
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		links = visit(links, c)
	}
	return links
}

//使用函数变量，将每个节点的操作逻辑从遍历树状结构中分开
func forEachNode(n *html.Node, pre, post func(n *html.Node)) {
	//两个函数是可选的
	//pre前序调用
	//post后序调用
	if pre != nil {
		pre(n)
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		forEachNode(c, pre, post)
	}
	if post != nil {
		post(n)
	}
}

//给forEachNode提供两个函数作为参数
var depth int

func startElement(n *html.Node) {
	if n.Type == html.ElementNode {
		fmt.Printf("%*s<%s>\n", depth*2, "", n.Data)
		depth++
	}
}

func endElement(n *html.Node) {
	if n.Type == html.ElementNode {
		depth--
		fmt.Printf("%*s</%s>\n", depth*2, "", n.Data)
	}
}
