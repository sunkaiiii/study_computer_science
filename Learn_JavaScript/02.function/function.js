function abs(x){
    if(x>=0){
        return x;
    }else{
        return -x;
    }
    //如果没有return语句，函数执行完毕后会返回结果，结果是undefined
}
//第二种定义方法
var fabs=function(x){
    if(x>=0){
        return x
    }else{
        return -x;
    }
};
abs(10);
fabs(10);
//可以传入人一个参数，但是不影响调用
abs(1,3,4,5);
abs(); //返回NaN

function absWithCheck(x){
    if(typeof x!=='number'){ //进行类型检查
        throw 'Not a number';
    }
    if(x>=0){
        return x;
    }else{
        return -x;
    }
}

//关键字arguments，只在函数内部起作用，并且永远指向当前函数的调用者传入的所有参数
function foo(x){
    console.log('x= '+x);
    for(var i=0;i<arguments.length;i++){
        console.log('arg '+i+'='+arguments[i]);
    }
}
foo(10,20,30) //利用arguments可以获得调用者传入的所有参数。即使函数声明里没定义参数，也可以从arguments里后的值。

//rest参数
function foo2(a,b,...rest){ //rest参数只能写在最后，前面用...标识
    console.log('a= '+a);
    console.log('b= '+b);
    console.log(rest);
}
foo2(1,2,3,4,5,6);

//JS的函数可以嵌套
function tool(){
    var x=1;
    function bar(){
        x=x+1;
    }
    return x;
}

//变量提升
function foo3(){
    var x='Hello '+y;
    console.log(x);
    var v='cat';
    //并不会报错，因为这里隐式的把y的声明提前到了函数的最前面
    //所以在函数内部，尽量在开头声明所有的变量。
}

//全局变量会绑定到window上，不同的js文件如果使用相同的变量会产生冲突
//减少冲突的一个方法是把自己的所有变量和函数全部绑定到一个全局变量中
var MYAPP={};
MYAPP.name='myapp';
MYAPP.version=1.0;
MYAPP.foo=function(){
    return 'foo';
}
//许多著名的JS库都是这么干的

//JS的变量作用域实际上是函数内部
function foo4(){
    for(var i=0;i<100;i++){

    }
    i+=100; //依然可以引用i
    //解决这个的方法是使用let替代var
    for(let j=0;j<100;j++){

    }
    j+=1;  //将显示错误
}
const PI =3.14 //常量
//JS在ES6开始，支持了解构赋值
var [x,y,z]=['1','2','3']; //还可以嵌套
var {name,version=1,foo}=MYAPP;
name;
version; //如果属性不存在且没有默认值，会为undefined

function buildDate({uear,month,day,hour=0,minute=10,second=0}){
    return new Date(year + '-' + month + '-' + day + ' ' + hour + ':' + minute + ':' + second);
}
buildDat({year:2008,minute:15});