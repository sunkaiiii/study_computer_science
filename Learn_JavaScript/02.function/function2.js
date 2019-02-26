//在对象中绑定函数，成为这个对象的方法
var xiaoming={
    name:'小明',
    birth:1990,
    age:function(){
        var v=new Date().getFullYear();
        return y-this.birth;
    }
};
xiaoming.age;
xiaoming.age();

//假设拆开写
function getAge(){
    var y=new Date().getFullYear();
    return y-this.birth;
}

var xiaoming2={
    name:'小明',
    birth:1990,
    age:getAge
};
xiaoming.age();
getAge(); //NaN
//原因在于函数内部调用this，只想的结果是依情况而定。
//单独调用的时候，指向window
var fn=xiaoming.age;
fn(); //甚至这样也会返回NaN
//什么垃圾设计……

var xiaoming3={
    name:'小明',
    birth:1990,
    age:function(){
        function getAgeFromBirth(){
            var y=new Date().getFullYear();
            return y-this.birth;
        }
        return getAgeFromBirth();
    }
};
xiaoming3.age(); //继续报错，原因是匿名函数里面的this指向了undefined
var xiaoming4={
    name:'小明',
    birth:1990,
    age:function(){
        var that=this; //解决方法，用that捕获this
        function getAgeFromBirth(){
            var y=new Date().getFullYear();
            return y-that.birth; 
        }
        return getAgeFromBirth();
    }
};
xiaoming4.age(); //不会出错

//函数本身的apply方法可以指定函数的this指向哪个对象
//它接受两个参数，第一个参数就是需要绑定的this变量，第二个参数是Array，表示函数本身的参数
var xiaoming5={
    name:'小明',
    birth:1999,
    age:getAge
};
getAge.apply(xiaoming5,[]);
//另外一个与apply类似的方法是call
getAge.call(xiaoming5);

//apply的用处，装饰器
//JS所有对象都是动态的，即使内置的函数，我们也可以重新指向新的函数
var count=0;
var oldParseInt=parseInt;
window.parseInt=function(){
    count+=1;
    return oldParseInt.apply(null,arguments); //调用原函数
}

//ES6标准增加了一种新的函数，箭头函数
var func=x=>x*x;
func(2);
//等同于
var func=function(x){
    return x*x;
}
func(3);
//箭头函数可以包含多条语句
var func=x=>{
    if(x>0){
        return x*x;
    }else{
        return -x*x;
    }
}
//如果参数不是一个，就需要用()括起来
var func=(x,y)=>x*x+y*y;
var func=()=>3.14; //无参数
var func=(x,y,...rest)=>{
    var i,sum=x+y;
    for(i=0;i<rest.length;i++){
        sum+=rest[i];
    }
    return sum;
}
//如果要返回一个对象，就需要注意表达式
//x => { foo: x } 这样时错误的
var func=x=>({foo:x})//这样是正确的
//箭头函数对于this的修复
var obj={
    birth:1990,
    getAge:function(){
        var b=this.birth;
        var fn=()=>new Date().getFullYear()-this.birth;//this指向obj对象
        return fn;
    }
};
obj.getAge();
//使用箭头函数，以前那种that写法，就不需要了。
//由于this再箭头函数中已经按照词法作用域绑定了，所以，用call()或者apply()调用箭头函数的时候，无法对this进行绑定
//传入的第一个参数会被忽略。
var obj={
    birth:1990,
    getAge:function(year){
        var b=this.birth;
        var fn=(y)=>y-this.birth;
        return fn.call({birth:2000},year); //被忽略2000
    }
};
obj.getAge(2015);

//请使用箭头函数简化排序时传入的函数
var arr = [10, 20, 1, 2];
arr.sort((x,y)=>x-y);

//generator是ES6标准引入的新的数据类型。
//一个generator看上去象一个函数，但可以返回多次。
//和Python的generator很像。
function* foo(x){
    yield x+1;
    yield x+2;
    return x+3;
} //通过yield可以返回多次
//实例，使用yield返回斐波那契数列
function* fib(max){
    var
        t,
        a=0,
        b=1,
        n=0;
    while(n<max){
        yield a;
        [a,b]=[b,a+b];
        n++;
    }
    return;
}
var f=fib(5);
f.next();
f.next();
f.next();
f.next();
f.next();
f.next(); //value:undefined,done:true
//next会执行generator代码，每次遇到yield x就返回一个对象{value:x,done:true/false}
//第二种方式是使用for循环
for(var x of fib(10)){
    console.log(x);
}
//使用generator，就可以很好的处理异步代码
/*
try {
    r1 = yield ajax('http://url-1', data1);
    r2 = yield ajax('http://url-2', data2);
    r3 = yield ajax('http://url-3', data3);
    success(r3);
}
catch (err) {
    handle(err);
}
*/
//练习
//要生成一个自增id，可以编写一个next_id()函数
//需要一个全局变量
var current_id=0;
function next_id(){
    current_id++;
    return current_id;
}
//使用generator
function* next_id2(){
    var a=0;
    while(true){
        yield ++a;
    }
}
