package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"time"
)

func main() {
	port := "8080"
	if len(os.Args) > 1 {
		port = os.Args[1]
	}
	listener, err := net.Listen("tcp", fmt.Sprintf("localhost:%s", port))
	if err != nil {
		log.Fatal(err)
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn) //这样就可以支持多个客户端了
	}
}

func handleConn(c net.Conn) {
	defer c.Close()

	for {
		_, err := io.WriteString(c, time.Now().Format("15:04:05\n"))
		if err != nil {
			return
		}
		time.Sleep(1 * time.Second)
	}
}
