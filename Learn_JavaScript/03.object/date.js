//在JS中，Date对象用来表示日期和时间
//获取系统当前时间
var now=new Date();
now;
now.getFullYear(); // 2015, 年份
now.getMonth(); // 5, 月份，注意月份范围是0~11，5表示六月
now.getDate(); // 24, 表示24号
now.getDay(); // 3, 表示星期三
now.getHours(); // 19, 24小时制
now.getMinutes(); // 49, 分钟
now.getSeconds(); // 22, 秒
now.getMilliseconds(); // 875, 毫秒数
now.getTime(); // 1435146562875, 以number形式表示的时间戳
//也可以自行创建Date对象
var d=new Date(2015,5,19,20,15,30,123);
//第二种创建的方式是解析一个符合ISO 8601格式的字符串
var d=Date.parse('2015-06-24T19:49:22.875+08:00');
//返回的是一个时间戳，不过很容易给他转换为一个Date()
var d= new Date(d);
d.getMonth();
// 使用Date.parse()时传入的字符串使用实际月份01~12，转换为Date对象后getMonth()获取的月份值为0~11。 

//时区
//既可以显示本地时间，也可以显示调整后的UTC时间
var d= new Date(1435146562875);
d.toLocaleString(); //显示的字符串和操作系统的设定有关
d.toUTCString(); //UTC时间
//只要传入的是一个number类型的时间戳，任何浏览器都可以把它转换为一个正确的本地时间
//获取当前系统的时间戳
if(Date.now){
    console.log(Date.now());
}else{
    console.log(new Date().getTime());
}

//练习
//小明为了和女友庆祝情人节，特意制作了网页，并提前预定了法式餐厅。小明打算用JavaScript给女友一个惊喜留言：
var today = new Date();
if (today.getMonth() === 2 && today.getDate() === 14) {
    alert('亲爱的，我预定了晚餐，晚上6点在餐厅见！');
}
//结果女友并未出现。小明非常郁闷，请你帮忙分析他的JavaScript代码有何问题。

//修正结果
var today = new Date();
if (today.getMonth() === 1 && today.getDate() === 14) { //JS中，0代表1月
    alert('亲爱的，我预定了晚餐，晚上6点在餐厅见！');
}