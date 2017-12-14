/**
 * Created by sunkai on 2017/12/14
 */

fun main(args: Array<String>) {
    val a = 1
    val b = 2
    val c = if (a <= b) b else a
    //等同于
//    if(a<=b)
//        return b
//    else
//        return a

    //when表达式
    var x:Int
    x=1
    when(x){
        1,2,3-> println("x=$x")
        !is Int->println("x is not integer")
        else-> println("x is nothing")
    }

    val arrayInt= intArrayOf(1,2,3,4,5)
    for(item in arrayInt){
        println("$item")
    }
    //如果需要遍历下标/索引，可以使用indices
    for(i in arrayInt.indices){
        println("arraiInt[$i] is ${arrayInt[i]}")
    }
    //遍历索引和值
    for((index,value) in arrayInt.withIndex()){
        println("arrayInt[$index] is $value")
    }

    //区间迭代
    for(i in 1..5)
        println(i)
    //倒叙循环
    for(i in 5 downTo 1)
        println(i)
    //特定步长
    for(i in 5 downTo 1 step 3)
        println(i)

    //使用标签停止循环
    thisLoop@ for(i in 1..10){
        for(j in 1..10)
            if(j==3)break@thisLoop else println(i.toString()+" "+j)
    }//如果我们不使用loop标签，break将会终止j循环
    aSimple()
}
fun aSimple(){
    val ints= intArrayOf(1,2,3)
    ints.forEach lit@{
        if(it==2)
            return@lit //仅仅跳出这个lambda表达式
        println(it)
    }
    ints.forEach {
        if(it==2)return@forEach else println(it) //使用隐式标签
    }
}