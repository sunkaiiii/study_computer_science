/**
 * Created by sunkai on 2017/12/14
 */
fun main(args:Array<String>){
    //println实际就是对System.out.println的一个封装
    println("Hello World")

    val a=1//定义一个常量
    var b=1//定义一个变量
//    a=1+1 无法重复赋值
    b=1+1 //可以重复赋值

//    val c //如果没有赋初值，不可以忽略类型
    val c:Int //指定一个类型

    println(add(2,3))
    println(add(2,3,4,5,6,7,8,9))
    println(sayHello("aha"))
    println(multiply(4.0,5.0))


    //kotlin中的赋值没有自动类型转换
    val i:Short=1
//    val j:Int=i //这句是无法编译通过的
    val j:Int=i.toInt() //要显示调用

    val s="@312124"
    val s1="The value of i is $s" //字符串转义

    //使用arrayOf创造一个数组
    val aa= arrayOf("Hello","World")
    //创建一个都是空的数组
    var nullArray:Array<String?> = arrayOfNulls(2)
    //创建一个数组，长度为10，包含从1到10的平方
    val squars=Array<Int>(10,{i->(i+1)*(i+1)})
    //创建一个空数组
    val emptyArray:Array<String?> = emptyArray();

    //创建基本类型的数组，kotlin对其有特殊的优化
    val intArray= intArrayOf(1,2,3)
    val normalArray= arrayOf(1,2,3)
//    intArray并不是normalArray的子类

    val s3="abc!#%#@TH35g3rwg4gw345uh3w4563wh4w5jne6gy456u"
    val s4="abc!#%#@TH35g3rwg4gw345uh3w4563wh4w5jne6gy456u"
    println(s3==s4)//比较对象是否相等
    println(s3===s4)//比较引用是否相等
}

//定义一些函数
fun sayHello(name:String):Unit =println("My name is ${name}.")
fun multiply(a:Double,b:Double)=a*b //不写返回类型编译器可以根据单句函数推断出返回类型
fun add(a:Int,b:Int,c:Int=0)=a+b+c //支持默认参数，减少重载
fun add(a:Int,b:Int,vararg n:Int):Int{//vararg代表着可变数量参数
    var sum=a+b
    for (i in n) //n是Int，所以可以自动推断出Int，进行foreach
        sum+=i
    return sum
}