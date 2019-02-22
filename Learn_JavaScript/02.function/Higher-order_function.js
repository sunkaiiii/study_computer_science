//引子
//函数的参数可以接受以函数作为的参数，那么这个函数就是高阶函数
function add(x,y,f){
    return f(x)+f(y);
}

add(-5,-8,Math.abs);

//map/reduce
function pow(x){
    return x*x;
}
var arr=[1,2,3,4,5,6,7,8,9,10];
var results=arr.map(pow); //注意，这里传入的是函数本身
console.log(results);
//还可以利用map进行更为复杂的操作
arr.map(String); //转换为字符串数组
//reduce：[x1,x2,x3,x4].reduce(f)=f(f(f(x1,x2),x3),x4)
//比如对一个array求和
arr.reduce(function(x,y){
    return x+y;
}); //25
//也可以转换数组位对应的十进制整数
arr.reduce(function(x,y){
    return x*10+y;
});

//输入一个字符串，转换为Array后在转换为Int
function string2int(s){
    return [...s].map(function(x){
        return x-'0';
    }).reduce(function(x,y){
        return x*10+y;
    });
}

//请把用户输入的不规范的英文名字，变为首字母大写，其他小写的规范名字。输入：['adam', 'LISA', 'barT']，输出：['Adam', 'Lisa', 'Bart']
function normalize(arr){
   return arr.map(function(x){
       return String(x).charAt(0).toUpperCase()+String(x).slice(1).toLowerCase();
   })
}

//小明希望利用map()把字符串变成整数，他写的代码很简洁：
/*
var arr = ['1', '2', '3'];
var r;
r = arr.map(parseInt);
*/
// 结果竟然是1, NaN, NaN，小明百思不得其解，请帮他找到原因并修正代码。
function mapToInt(arr){
    r = arr.map(x=>parseInt(x));
}
//原因在于parseInt的可选入参是不止一个的，这里map迭代中，传入paseInt的带有数组的下标('1',0),('2',1),('3',2)，造成了奇怪的结果
//https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/map


//filter也是一个常用操作，它用于把Array的某些元素过滤掉，返回剩下的元素
var arr=[1,2,3,4,5,6,7,8,9,10];
var r=arr.filter(x=>x%2===0); //删掉奇数，保留偶数
var arr = ['A', '', 'B', null, undefined, 'C', '  ']; 
var r=arr.filter(s=>s&&s.trim()); //删除空字符串
//filter接受的回调函数，其实可以有多个参数。表示元素的位置和自身
var arr=['A','B','C'];
var r=arr.filter(function(element,index,self){
    console.log(element);
    console.log(index);
    console.log(self);
    return true;
});
//利用filter，可以巧妙地出去重复元素
var
    r,
    arr = ['apple', 'strawberry', 'banana', 'pear', 'apple', 'orange', 'orange', 'strawberry'];
r=arr.filter(function(element,index,self){
    return self.indexOf(element)===index;
});


//请尝试用filter()筛选出素数：
function get_primes(arr){
    return arr.filter(function(x){
        if(x===1){
            return false;
        }
        for(let i=2;i<=Math.sqrt(x);i++){
            if(x%i===0){
                return false;
            }
        }
        return true;
    });
}

//sort
//JS的sort方法就是用于排序的，但是结果可能让人大吃一斤
//[10, 20, 1, 2].sort(); // [1, 10, 2, 20]
//原因是默认的sort方法是把所有的元素转换为String再排序，'10'排在了'2'的前面，因为字符'1'比字符'2'小
var arr=[10,20,1,2];
arr.sort(function(x,y){
    if(x<y){
        return -1;
    }
    if(x>y){
        return 1;
    }
    return 0;
})
//sort方法是会对Array进行修改的
log.console(arr);//[1,2,10,20]

