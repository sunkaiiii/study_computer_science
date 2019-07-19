package main

import (
	"fmt"
	"log"
	"net/http"
	"os"

	"golang.org/x/net/html"
)

//一个并发爬虫的实例
var tokens = make(chan struct{}, 20) //同一时间的并发上限
func main() {
	worklist := make(chan []string)

	var n int
	n++ //执行第一个节点
	go func() {
		worklist <- os.Args[1:]
	}()

	//并发开始爬虫
	seen := make(map[string]bool)
	for ; n > 0; n-- {
		list := <-worklist
		for _, link := range list {
			if !seen[link] {
				seen[link] = true
				n++
				go func(list string) {
					worklist <- crawl(link)
				}(link) //以参数传入，避免循环快照的问题
			}
		}
	}
}

func crawl(url string) []string {
	fmt.Println(url)
	tokens <- struct{}{}
	list, err := extract(url)
	<-tokens
	if err != nil {
		log.Print(err)
	}
	return list
}

var cancel = make(chan struct{})

func done() {
	cancel <- struct{}{}
}

func extract(url string) ([]string, error) {
	//在这个版本里，并不是直接把href原封不动的添加存放在链接的slice中
	//而是将他解析成基于当前文档相对路径的resp.Request.URL，结果的链接是绝对路径的形式
	//这样就可以递归的调用http.GET
	select {
	case <-cancel:
		return nil, nil
	default:

	}
	req, _ := http.NewRequest("GET", url, nil)
	req.Cancel = cancel
	resp, err := http.DefaultClient.Do(req)
	// resp, err := http.Get(url)
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
