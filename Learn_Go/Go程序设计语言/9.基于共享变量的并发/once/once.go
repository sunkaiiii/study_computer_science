package main

import (
	"sync"
)

var loadIconsOnce sync.Once
var icons map[string]string

func loadIcons() {
	icons = make(map[string]string)
	icons["spades.png"] = "spades.png"
	icons["hearts.png"] = "hearts.png"
	icons["diamonds.png"] = "diamonds.png"
	icons["clubs.png"] = "clubs.png"
}
func getIcon(name string) string {
	//内部存放了一个boolean来记录初始化是不是已完成了
	//当boolean为true的时候，将不再执行这个Do方法
	loadIconsOnce.Do(loadIcons)
	return icons[name]
}

func main() {

}
