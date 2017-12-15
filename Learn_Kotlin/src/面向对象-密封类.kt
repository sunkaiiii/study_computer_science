/**
 * Created by sunkai on 2017/12/15
 */

//密封类是为继承设计的，是一个抽象类
//密封类的子类是确定的，除了已经定义好的子类外，他不能再有其他的子类
sealed class sealPerson(val name:String,var age:Int){
    class Adult(name:String,age:Int):sealPerson(name,age)
    class Child(name:String,age:Int):sealPerson(name,age)
}
fun main(args:Array<String>){
    val c1:sealPerson=sealPerson.Adult("123",1)
}