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