package main

import (
	"bytes"
	"fmt"
)

//IntSet是一个包含非负整数的集合
//零值代表空的集合
type IntSet struct {
	words []uint64
}

//Has方法的返回值表示是否存在非负数x
func (s *IntSet) Has(x int) bool {
	word, bit := x/64, uint(x%64)
	return word < len(s.words) && s.words[word]&(1<<bit) != 0
}

//Add添加非负数x到集合中
func (s *IntSet) Add(x int) {
	word, bit := x/64, uint(x%64)
	for word >= len(s.words) {
		s.words = append(s.words, 0)
	}
	s.words[word] |= 1 << bit
}

//UnionWith将会对s和t做并集并将结果存在s中
func (s *IntSet) UnionWith(t *IntSet) {
	for i, tword := range t.words {
		if i < len(s.words) {
			s.words[i] |= tword
		} else {
			s.words = append(s.words, tword)
		}
	}
}

//String方法以字符串 “{1,2,3}” 的形式返回集中
func (s *IntSet) String() string {
	var buf bytes.Buffer
	buf.WriteByte('{')
	for i, word := range s.words {
		if word == 0 {
			continue
		}
		for j := 0; j < 64; j++ {
			if word&(1<<uint(j)) != 0 {
				if buf.Len() > len("{") {
					buf.WriteByte(' ')
				}
				fmt.Fprintf(&buf, "%d", 64*i+j)
			}
		}
	}
	buf.WriteByte('}')
	return buf.String()
}

func main() {
	var x, y IntSet
	x.Add(1)
	x.Add(144)
	x.Add(9)
	fmt.Println(x.String()) //"{1,9,144}"
	y.Add(9)
	y.Add(42)
	fmt.Println(y.String()) //"{9,42}"
	x.UnionWith(&y)
	fmt.Println(x.String())           //"{1,9,42,144}"
	fmt.Println(x.Has(9), x.Has(123)) //true false
}
