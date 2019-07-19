package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"time"
)

func main() {
	listener, err := net.Listen("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster() //broadcaster

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Println(err)
			continue
		}

		go handleConn(conn)
	}
}

type client chan<- string

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) //所有到来的消息
)

func broadcaster() {
	//broadcaster内部变量clients会记录当前建立链接的客户端集合
	//其记录的内容是每一个客户端的消息发出channel的“资格”信息
	clients := make(map[client]bool) //所有链接的用户
	for {
		select {
		case msg := <-messages:
			//广播消息给所有的用户
			for cli := range clients {
				cli <- msg
			}
		case cli := <-entering:
			clients[cli] = true
		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

func handleConn(conn net.Conn) {
	ch := make(chan string) //即将到来的客户端信息
	go clientWriter(conn, ch)

	who := conn.RemoteAddr().String()
	ch <- "You are " + who
	messages <- who + " has arrived"
	entering <- ch

	input := bufio.NewScanner(conn)
	tick := time.NewTicker(5 * time.Second)
	cancel := make(chan struct{})
	done := make(chan struct{})
	var timer = func(tick *time.Ticker) { //超时自动断开
		select {
		case <-cancel:
			tick.Stop()
			return
		case <-tick.C:
			conn.Close()
			done <- struct{}{}
			return
		}
	}
	go timer(tick)
	for input.Scan() {
		select {
		case <-done:
			break
		default:
			cancel <- struct{}{}
			tick = time.NewTicker(5 * time.Second)
			go timer(tick)
			messages <- who + ": " + input.Text()
		}
	}

	leaving <- ch
	messages <- who + " has left"
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg)
	}
}
