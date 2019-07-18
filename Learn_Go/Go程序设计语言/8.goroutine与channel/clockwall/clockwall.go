package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	for {
		port, _ := reader.ReadString('\n')
		port = strings.Replace(port, "\n", "", -1)
		conn, err := net.Dial("tcp", fmt.Sprintf("localhost:%s", port))
		if err != nil {
			log.Fatal(err)
		}
		defer conn.Close()
		go mustCopy(os.Stdout, conn)
	}
}

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}
