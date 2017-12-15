/**
 * Created by sunkai on 2017/12/15
 */

//定义一个类
class c1(name:String){ //主构造函数
    val name:String
    init { //init定义主构造函数行为
        this.name=name
    }
    fun outInfo(){
        println(name)
    }
}

class c2 private constructor(){
    val name="123"
    fun outInfo(){
        println(name)
    }
}

class c3(val name:String){ //主构造函数中如果有参数用val和var修饰，就会创建一个同名的成员变量
    fun outInfo(){
        println(name)
    }
}

//kotlin中支持构造函数的默认参数
class Person(val id:Long,val name:String="",val age:Int=0){
    fun outInfo(){
        println(id.toString()+" "+name+" "+age)
    }
}

class Persoon2(val id:Long){
    var name:String=""

    //如果一个类有主构造函数，那么所有的此构造函数都要委托给主构造函数
    //次构造函数不能在参数列表中声明并初始化变量
    constructor(name:String): this(name.hashCode().toLong()){
        this.name=name
    }
    fun outInfo(){
        println(id.toString()+" "+name)
    }
}

fun main(args:Array<String>){
    val c1=c1("c1")
//    val c2=c2() //构造函数私有，无法实例化
    val c3=c3("c3")
    c1.outInfo()
    c3.outInfo()

    val c4=Person(1)
    val c5=Person(id=1,age = 3)
    val c6=Person(1,"hah",3)
    c4.outInfo()
    c5.outInfo()
    c6.outInfo()
    val c7=Persoon2(2)
    val c8=Persoon2("hahah")
    c7.outInfo()
    c8.outInfo()
}