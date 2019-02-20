'use strict'; //强制strict模式，不允许未经 var 声明的变量
var a=2;
if(a>1){
    var b=3;
    alert("hello world");
}else if(a===2){ //请坚持使用===来进行比较
    alert("world hello");
}else if(a===NaN){ //NaN这个特殊的Number与其他值都不相等，包括他自己
 //不可能为真系列
}
//判断NaN的方法应用系统内置的方法
isNaN(a)
//要注意浮点数的相等比较
1/3===(1-2/3) //false

//JS的设计者希望通过用null表示一个空的值，用undefined表示未定义
//但后来被人为，这并没有什么乱用，区分两者的意义不大。

//JS的数组可以包括任意数据的类型
var arr=[1,2,3.14,"Hello",null,true]
arr[0];
arr[1];
arr[5];
arr[10]; //超出范围，返回undefined

//对象，JS的对象是一组key-value组成的无序集合
//key都是字符串类型，值可以是任意数据类型
var person={
    name:'Sun',
    age:20,
    tags:['js','web','mobile'],
}
person.age;
person.name;

var ud; //值是undefined
console.log(ud)

//强制字符串
var strings=`this is 
a string
with the 
line space.`;

//字符串拼接
var name="kai";
var location="shanghai";
var age=20;
var message=`你好, ${name},今年${age}岁，来自${location}`;
alert(message);

//一些常见的字符串操作
var s='Hello, world';
s[0];
s[1];
s[2];
s.length;
//要注意的是，同其它语言一样，字符串是不可变的。
var s2=s.toUpperCase();
var index=s.indexOf("world");

//JS的Array很诡异
var arr2=[1,2,3];
arr.length=6; //给length赋值会直接导致array的变化
arr[1]='啊啊'; //对下标赋值可以直接修改
arr.indexOf('啊啊'); //与string是一样的
var arr3=arr.slice(0,1); //array版本的substring
var copyArr=arr.slice(); //复制array

arr.push("1",2,3); //相当于C++ vector的push_back;
var b=arr.pop();

//如果要往Array的头部添加若干元素，使用unshift方法，shift方法则把Array的第一个元素删掉
var arr3=[1,2];
arr.unshift('A','B') //返回新的长度：4
arr.shift(); //弹出第一个;

//sort()进行排序，会直接修改当前的Array元素位置，直接调用的时候，按照默认顺序排序
arr=['B','C','A'];
arr.sort();
arr;

//reverse方法，反转Array
arr=['one','two','three'];
arr.reverse();
arr;

//splice方法是修改Array的“万能方法”，它可以从指定的索引开始删除若干元素，然后再从该位置添加若干元素,返回值是被删除的元素
arr=['Microsoft','Apple','Yahoo','AOL','Excite','Oracle'];
//从索引2开始删除3个元素，然后再添加两个元素
arr.splice(2,3,'Google','Facebook');
arr.splice(2,2); //只删除，不添加
arr.splice(2,0,'Google','Facebook');  //返回为[]，因为没有元素被删除

//concat，连接函数
arr=['A','B','C'];
arr.concat(1,2,[3,4]);
arr;

//join方法是一个非常实用的方法，他把当前的Array的每个元素用指定的字符串连接起来，然后返回链接后的字符串
arr=['A','B','C',1,2,3];
arr.join('-');
arr;

//JS的对象是动态类型，所以对于对象来说，也可以自由的添加对象的添加或删除属性。
var xiaoming={
    name:'小明'
};
xiaoming.age; //undefined
xiaoming.age=18; //增加了一个属性
delete xiaoming.age; //删除age属性
xiaoming.age; //undefined
delete xiaoming.sex; //删除不存在的属性也没事
//检测属性是否在某一个对象里，用in，但也可能是在它的基类里
'name' in xiaoming //true
'toString' in xiaoming //同样是true
//如果要判断一个属性是否是xiaoming自身拥有的，而不是继承得到的，要用hasOwnProperty()方法
xiaoming.hasOwnProperty('name'); //true

//循环
var x=0;
var i;
for(i=1;i<=10000;i++){
    x=x+i;
}
x;
//也支持foreach循环
var o={
    name:'Jack',
    age:20,
    city:'Beijing'
};
for(var key in o){
    console.log(key);
}
//由于Array也是对象，而它的每个元素的索引被视为对象的属性，因此for...in循环可以输出Array的索引
arr=['A','B','C'];
for(var i in a){
    console.log(i);
    console.log(a[i]);
}
//while循环是一样的
var x=0;
var n=99;
while(n>0){
    x=x+n;
    n=n-2;
}
x;
//do while同理

//使用map可以存储number类型的键值
var m=new Map();
var s =new Set();
console.log(m);
m=new Map(['sun',10],['sun2',75]);
m.get('sun'); //10
m.set('bob',22);
m.get('bob'); //22
m.delete('bob');
s=new Set([1,2,3,4]);
s.add(2); //重复添加 无效果
s.add(7);
s.add("5");

//iterable
//Array、Map、Set都属于iterable类型
for(var x of s){ //for...of遍历的是元素，for...in遍历的是属性名称
    console.log(x);
}
//另一种替代方法是使用foreach
m.forEach(function(element,index,array){
    console.log(element+', index'+index);
});







