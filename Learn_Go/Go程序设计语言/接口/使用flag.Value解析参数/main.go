package main

import (
	"flag"
	"fmt"
	"time"
)

//下面定义了一个celsiusFlag类型来允许在参数中使用摄氏温度或者华氏温度。
type celsifusFlag struct{ Celsuius }

type Celsuius float64
type Fahrenheit float64

const (
	AbsoluteZeroC Celsuius = -273.15
	FreezingC     Celsuius = 0
	BoilingC      Celsuius = 100
)

func CToF(c Celsuius) Fahrenheit {
	return Fahrenheit(c*9/5 + 32)
}

func FToC(f Fahrenheit) Celsuius {
	return Celsuius((f - 32) * 5 / 9)
}

func (f *celsifusFlag) Set(s string) error { //实现了flag.Value接口中的set方法
	var unit string
	var value float64
	fmt.Sscanf(s, "%f%s", &value, &unit)
	switch unit {
	case "C":
		f.Celsuius = Celsuius(value)
		return nil
	case "F":
		f.Celsuius = FToC(Fahrenheit(value))
		return nil
	}
	return fmt.Errorf("invalid temperature %q", s)
}

func (c Celsuius) String() string {
	return fmt.Sprintf("%gC", c)
}

//CelsiusFlag 根据给定的name、默认值和使用方法
//定义了一个Celsius标志，返回了标志值的指针
//标志必须包含一个数值和一个单位，比如：100C
func CelsisusFlag(name string, value Celsuius, usage string) *Celsuius {
	f := celsifusFlag{value}
	flag.CommandLine.Var(&f, name, usage)
	return &f.Celsuius
}

var temp = CelsisusFlag("temp", 20.0, "the temperature")

func main() {
	//可以用-period命令行标志来控制休眠时间，因为flag.Duration函数创建了一个time.Duration的标识变量
	var period = flag.Duration("period", 1*time.Second, "sleep period")
	flag.Parse()
	fmt.Printf("Sleeping for %v", *period)
	time.Sleep(*period)
	fmt.Println()

	//使用自定义的新标志
	flag.Parse()
	fmt.Println(*temp)
}
