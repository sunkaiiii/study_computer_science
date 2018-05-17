package test

import (
	"fmt"
	"os"

	"github.com/shirou/gopsutil/process"
)

var ps *process.Process

func mem(n int) {
	if ps == nil {
		p, err := process.NewProcess(int32(os.Getpid()))
		if err != nil {
			panic(err)
		}

		ps = p

	}
	mem, _ := ps.MemoryInfoEx()
	fmt.Printf("%d. VMS: %d MB,RSS:%d MB\n", n, mem.VMS>>20, mem.RSS>>20)
}
func testMemoryAlloc() {
	//1.初始化结束后的内存状态
	mem(1)
	//2、创建一个10*1M数组后的状态
	data := new([10][1024 * 1024]byte)
	mem(2)
	//3、填充数组后内存的状态
	for i := range data {
		for x, n := 0, len(data[i]); x < n; x++ {
			data[i][x] = 1
		}
		mem(3)
	}
}
