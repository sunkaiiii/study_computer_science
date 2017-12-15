/**
 * Created by sunkai on 2017/12/15
 */
class Person3(val name:String){
    val age:Int
    val id:Long=0
//    val nationality:String //不是抽象属性，必须初始化，否则将编译报错
    init {
        age=0
    }
}

class Person4(name:String){
    var name=name
    set(value){
        field=if(value.isEmpty()) "" else value[0].toUpperCase()+value.substring(1)
    }

    val isValidName
    get()=!name.isEmpty() //getter是一哥没有参数、返回类型与属性相同的函数
}

const val maxID=Int.MAX_VALUE //将maxID声明为编译器常量，只能使用String或原生类型初始化，且不能定义getter

class Person5(val name:String){
    lateinit var hello:String //使用lateinit修饰的参数可以不初始化
    fun initHello(arg:String){
        hello=arg
    }
}

fun main(args:Array<String>){
    val c1=Person3("hahaa")
    c1.name //实际上是调用name的getter方法

    val c2=Person5("asdsa")
//    println(c2.hello) //调用为初始化的变量会报错
    c2.initHello("hsadas") //初始化他
    println(c2.hello)
}