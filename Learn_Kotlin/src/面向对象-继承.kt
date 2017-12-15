/**
 * Created by sunkai on 2017/12/15
 */
//1、Kotlin 中所有类的最终父类是 Any，而非 Java 中的 Object
//
//2、Kotlin 中 非抽象类默认不可继承
//
//3、Kotlin 中 非抽象类函数和类属性默认不可覆盖

//open关键字可以定义“非抽象的类和函数之前”用来标记他是可继承的
open class openPerson(val name:String){
    open var age=0
    open fun say()="My name is $name,$age years old."
}
//如果类不是open的，类里面的属性和函数都不能是open的

//override关键字用在定义“子类覆盖父类的函数和属性“之前，用来标记覆盖了父类的函数和属性
class Student(name:String):openPerson(name){
    override var age=0
    override fun say()="i'm a student named $name,$age yeas old"
}


fun main(args:Array<String>){
    val c1=openPerson("asd")
    println(c1.say())
    val c2=Student("sadas")
    println(c2.say())
    val c3:openPerson=c2
    println(c3.say())
}