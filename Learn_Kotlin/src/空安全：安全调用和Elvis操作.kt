/**
 * Created by sunkai on 2017/12/15
 */

//安全调用符
//?.是一个语法糖，会将目标编译为一个三目表达式，如果?.前的方法不为空，则调用之后的方法，否则返回null
fun printLengthOfString(s:String?)=println(s?.length)

fun evis(s:String?)=println(s?.length?:"error")//等于 s!=null?s.length:"error"

fun main(args:Array<String>){
    printLengthOfString("!23")
    printLengthOfString(null)
    evis("123")
    evis(null)
}