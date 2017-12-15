/**
 * Created by sunkai on 2017/12/15
 */

//定义一个伴生对象,这就构成了一个简单的单例
object Resource{
    val name="Alex"
    fun say(){
        println("Hello")
    }
}

//使用伴生对象，用半生对象的成员来替代静态成员
class objectPerson(val name:String){
    companion object { //实际上伴生对象是在这个类里面创建了一个名为Compainion的静态单例内部类
        val anonymousPerson=objectPerson("Anoymous")
        fun sayHello()=println("Hello")
    }
    var age=0
    fun sayName()=println("My name is $name")
}


class jvmPerson(val name:String){
    companion object {
        //JVM注解将属性和函数编译为真正的JVM静态资源。
        //在伴生对象里使用注解，没有添加注解的属性和函数将不会被编译为静态成员
        @JvmStatic val anonymous=jvmPerson("Anonymous")
        fun say()=println("Hello") //没有被注解，在java中，只可以用Person.Companion.say()调用
    }
}

fun main(args:Array<String>){
    val c1=objectPerson("haha")
    objectPerson.sayHello() //可以直接使用类名+方法调用方法
    jvmPerson.say()
}

