//在JS的世界里一切都是对象
//可以用typeof来区分对象的类型
typeof 123; // 'number'
typeof NaN; // 'number'
typeof 'str'; // 'string'
typeof true; // 'boolean'
typeof undefined; // 'undefined'
typeof Math.abs; // 'function'
typeof null; // 'object'
typeof []; // 'object'
typeof {}; // 'object'
//注意null的类型是object
//JS也提供了包装对象，和Java的装箱就很像
var n = new Number(123); // 123,生成了新的包装类型
var b = new Boolean(true); // true,生成了新的包装类型
var s = new String('str'); // 'str',生成了新的包装类型
typeof n; // 'object'
typeof b; // 'object'
typeof s; // 'object'
//所以别一言不合就new String()，看着蛋疼
//parseInt和parseFloat可以转换任意类型到number
//用String来转换应以类型到string，或者直接调用toString()
//判断Array要用Array.isArray(arr)
//判断null要用myVar===null
//判断某个全局变量是否存在用typeof window.myVar==='undefined'
//函数内部判断某个变量是否存在用typeof myVar==='undefined'
//null和undefined没有toString()方法
//number对象调用toString报错
// 123.toString() //error
//以下两个ok
123..toString();
(123).toString(); 

