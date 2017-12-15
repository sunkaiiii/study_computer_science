/**
 * Created by sunkai on 2017/12/15
 */

fun let(s:String?)= println(s?.let { s }) //if not null then

fun 非空操作符(s:String?){
    val notNullString=s!! //当s为空的时候，抛出异常，此时notNUllString是一个绝对非空的类型
    println(notNullString)
}
fun main(args:Array<String>){
    let(null)
    let("!@3")

    非空操作符(null)
    非空操作符("124124")
}