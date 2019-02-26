//可以在JavaScript中直接使用JSON
var xiaoming={
    name:'小明',
    age:14,
    gender:true,
    height:1.65,
    grade:null,
    'middle-school':'\"W3C\" Middle School',
    skills:['JavaScript','Java','Python','Lisp']
};
var s=JSON.stringify(xiaoming);
console.log(s);
//要想输出的好看一些，可以加上参数，按缩进输出
JSON.stringify(xiaoming,null,'  ');
//第二个参数用于控制如何筛选对象的键值
//如果只想输出特定的属性，可以传入Array
JSON.stringify(xiaoming,['name','skills','  ']);
//还可以传入一个函数，这样对象的每个键值都会被这个函数处理
JSON.stringify(xiaoming,function(key,value){
    if(typeof value==='string'){
        return value.toUpperCase();
    }
    return value;
},' ');
//如果我们还相对小明进行更精确的控制，可以给xiaoming定义一个toJSON()方法，直接放回JSON应该序列化的数据
var newXiaoming={
    name: '小明',
    age: 14,
    gender: true,
    height: 1.65,
    grade: null,
    'middle-school': '\"W3C\" Middle School',
    skills: ['JavaScript', 'Java', 'Python', 'Lisp'],
    toJSON: function () {
        return { // 只输出name和age，并且改变了key：
            'Name': this.name,
            'Age': this.age
        };
    }
};
JSON.stringify(xiaoming);

//反序列化
//拿到一个JSON格式的字符串，可以直接用JSON.parse把它变成一个JavaScript对象
JSON.parse('[1,2,3,true');//[1,2,3,true]
JSON.parse('{"name":"小明","age":14}'); // Object {name: '小明', age: 14}
JSON.parse('true'); // true
JSON.parse('123.45'); // 123.45
//JSON.parse还可以接受一个函数，用来转换解析出的属性
var obj=JSON.parse('{"name":"小明","age":14}',function(key,value){
    if(key=='name'){
        return value+'同学';
    }
    return value;
});
console.log(JSON.stringify(obj)); //小明同学

//解析Yahoo天气的JSON
var url = 'https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20%3D%202151330&format=json';
// 从远程地址获取JSON:
$.getJSON(url, function (data) {
    // 获取结果:
    var city = data.query.results.channel.location.city;
    var forecast = data.query.results.channel.item.forecast;
    var result = {
        city: city,
        forecast: forecast
    };
    alert(JSON.stringify(result, null, '  ')); 
});