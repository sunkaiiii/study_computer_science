package main

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"reflect"
	"strconv"
	"strings"
	"time"
)

func search(resp http.ResponseWriter, req *http.Request) {
	var data struct {
		Labels     []string `http:"l"`
		MaxResults int      `http:"max"`
		Exact      bool     `http:"x"`
	}
	data.MaxResults = 10 //默认值
	if err := unpack(req, &data); err != nil {
		http.Error(resp, err.Error(), http.StatusBadRequest)
		return
	}

	fmt.Fprintf(resp, "Search %+v\n", data)
}

func unpack(req *http.Request, ptr interface{}) error {
	if err := req.ParseForm(); err != nil {
		return err
	}

	//构建map
	fileds := make(map[string]reflect.Value)
	v := reflect.ValueOf(ptr).Elem() //变量的结构
	for i := 0; i < v.NumField(); i++ {
		filedInfo := v.Type().Field(i) //通过反射得来的结构
		tag := filedInfo.Tag
		name := tag.Get("http")
		if name == "" {
			name = strings.ToLower(filedInfo.Name)
		}
		fileds[name] = v.Field(i)
	}

	for name, values := range req.Form {
		f := fileds[name]
		if !f.IsValid() {
			continue //过滤不认得的参数
		}

		for _, value := range values {
			if f.Kind() == reflect.Slice {
				elem := reflect.New(f.Type().Elem()).Elem()
				if err := populate(elem, value); err != nil {
					return fmt.Errorf("%s: %v", name, err)
				}
				f.Set(reflect.Append(f, elem))
			} else {
				if err := populate(f, value); err != nil {
					return fmt.Errorf("%s: %v", name, err)
				}
			}
		}
	}
	return nil
}

func populate(v reflect.Value, value string) error {
	switch v.Kind() {
	case reflect.String:
		v.SetString(value)

	case reflect.Int:
		i, err := strconv.ParseInt(value, 10, 64)
		if err != nil {
			return err
		}
		v.SetInt(i)

	case reflect.Bool:
		b, err := strconv.ParseBool(value)
		if err != nil {
			return err
		}
		v.SetBool(b)

	default:
		return fmt.Errorf("unsupported kind %s", v.Type())
	}
	return nil
}

//使用反射打印任意值的类型和枚举它的方法
func print(x interface{}) {
	v := reflect.ValueOf(x)
	t := v.Type()
	fmt.Printf("type %s\n", t)
	for i := 0; i < v.NumMethod(); i++ {
		methType := v.Method(i).Type()
		fmt.Printf("func (%s) %s%s\n", t, t.Method(i).Name, strings.TrimPrefix(methType.String(), "func"))
	}
}
func main() {
	t := reflect.TypeOf(3) //使用反射获取它的类型
	fmt.Println(t.String())
	fmt.Println(t)

	var w io.Writer = os.Stdout
	fmt.Println(reflect.TypeOf(w)) //会打印具体的类型，os.File

	//Type接口是满足fmt.Stringer的接口的
	fmt.Printf("%T\n", 3) //int

	v := reflect.ValueOf(3)
	fmt.Println(v)        //3
	fmt.Printf("%v\n", v) //3
	fmt.Println(v.String())
	t = v.Type()
	fmt.Println(t.String())

	//有些变量还可以通过reflect.Value修改值
	x := 2
	a := reflect.ValueOf(2)
	b := reflect.ValueOf(x)
	c := reflect.ValueOf(&x)
	d := c.Elem()
	fmt.Println(a.CanAddr())          // "false"
	fmt.Println(b.CanAddr())          // "false"
	fmt.Println(c.CanAddr())          // "false"
	fmt.Println(d.CanAddr())          // "true" ，它是可取地址的
	px := d.Addr().Interface().(*int) //通过这个方法强制转换为指针
	*px = 3
	fmt.Println(x) //可以看到原始值被修改了
	//也可以通过调用可取地址的reflect.Value的reflect.Value.Set方法来更新
	d.Set(reflect.ValueOf(4))
	fmt.Println(x)

	//尽管反射可以读取一些未导出的成员
	//但是反射机制并不能修改这些成员
	// stdout := reflect.ValueOf(os.Stdout).Elem()
	// fmt.Println(stdout.Type())
	// fd := stdout.FieldByName("fd")
	// fmt.Println(fd.Int())
	//fd.SetInt(2) //panic

	print(time.Hour)
}
