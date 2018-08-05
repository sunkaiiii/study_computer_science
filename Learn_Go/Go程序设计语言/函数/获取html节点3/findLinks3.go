package main

import (
	"fmt"
	"log"
	"net/http"
	"os"

	"golang.org/x/net/html"
)

func Extract(url string) ([]string, error) {
	//在这个版本里，并不是直接把href原封不动的添加存放在链接的slice中
	//而是将他解析成基于当前文档相对路径的resp.Request.URL，结果的链接是绝对路径的形式
	//这样就可以递归的调用http.GET
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	if resp.StatusCode != http.StatusOK {
		resp.Body.Close()
		return nil, fmt.Errorf("getting %s:%s", url, resp.Status)
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return nil, fmt.Errorf("parsing %s as HTML:%v", url, err)
	}
	var links []string
	visitNode := func(n *html.Node) {
		if n.Type == html.ElementNode && n.Data == "a" {
			for _, a := range n.Attr {
				if a.Key != "href" {
					continue
				}
				link, err := resp.Request.URL.Parse(a.Val)
				if err != nil {
					continue
				}
				links = append(links, link.String())
			}
		}
	}
	forEachNode(doc, visitNode, nil)
	return links, nil
}
func forEachNode(n *html.Node, pre, post func(n *html.Node)) {
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

func breadthFirst(f func(item string) []string, worlist []string) {
	//将返回的内容添加到workList中，对每一个元素，最多调用一次f
	seen := make(map[string]bool)
	for len(worlist) > 0 {
		items := worlist
		worlist = nil
		for _, item := range items {
			if !seen[item] {
				seen[item] = true
				worlist = append(worlist, f(item)...)
			}
		}
	}
}

func crawl(url string) []string {
	fmt.Println(url)
	list, err := Extract(url)
	if err != nil {
		log.Print(err)
	}
	return list
}

func main() {
	//开始执行广度遍历
	breadthFirst(crawl, os.Args[1:])
}
