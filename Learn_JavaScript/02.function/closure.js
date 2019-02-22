//高阶函数除了可以接受函数作为参数外
//还可以把函数作为结果值返回

//定义立即求和的函数
function sum(arr){
    return arr.reduce(function(x,y){
        return x+y;
    });
}
sum([1,2,3,4,5]);
//但是如果不需要立即求和，而是在后面的代码中根据需要再计算。
//这时就可以定义求和的函数
function lazy_sum(arr){
    var sum=function(){
        return arr.reduce(function(x,y){
            return x+y;
        });
    }
    return sum;
}
var f=lazy_sum([1,2,3,4,5]);
f(); //执行求和
//这就是令人非常熟悉的闭包了。内部函数sum可以引用外部函数lazy_sum的变量，当lazy_sum返回函数sum时
//相关参数和变量都保存在返回的函数中。
//每次调用lazy_sum()的时候，它返回的都是一个新的函数
var f1=lazy_sum([1,2,3,4,5]);
var f2=lazy_sum([1,2,3,4,5]);
f1===f2; //false

//闭包当中要注意的事情
function count(){
    var arr=[];
    for(var i=1;i<=3;i++){
        arr.push(function(){
            return i*i;
        });
    }
    return arr;
}
var results=count();
var f1=results[0];
var f2=results[1];
var f3=results[2];
f1();
f2();
f3();
//实际的结果是16，16，16
//原因在于返回的函数引用了变量i，但他并非立即执行，等到3个函数都返回的时候，i已经变成了4
//所以结果是16
//返回闭包的时候，要牢记的一点就是
//不要引用任何循环变量，或者后续会发生变化的变量
//如果一定要引用循环变量的话，方法是再创建一个函数，用该函数的参数绑定当前循环变更量的值
function count2(){
    var arr=[];
    for(var i=1;i<=3;i++){
        arr.push((function(n){
            return function(){
                return n*n;
            }
        })(i)); //类似别的语言当中的捕获变量
    }
    return arr;
}
var results=count2();
var f1=results[0];
var f2=results[1];
var f3=results[2];
//理论上讲，创建一个匿名函数并立即执行可以这么写
//function (x) { return x * x } (3);
//但是由于JS语法解析的问题，需要把括号把整个函数定义括起来
//(function (x) { return x * x }) (3);
//通常，一个立即执行的匿名函数可以把函数体拆开，一般这么写
(function(x){
    return x*x;
})(3);

//在没有class机制，只有函数的语言里，借助闭包，同样可以封装一个私有变量。
function create_counter(initial){
    var x=initial||0;
    return{
        inc:function(){
            x+=1;
            return x;
        }
    }
}
//用起来像是这样
var c1=create_counter();
c1.inc(); //1
c1.inc(); //2
//该闭包携带了局部变量x，并且，从外部代码是无法访问到x的

//闭包还可以把多参数的函数变成单参数的函数
//比如常见的算平方

function make_pow(n){
    return function(x){
        return Math.pow(x,n);
    }
}
var pow2=make_pow(2);
var pow3=make_pow(3);
console.log(pow2(5));
console.log(pow3(7));

