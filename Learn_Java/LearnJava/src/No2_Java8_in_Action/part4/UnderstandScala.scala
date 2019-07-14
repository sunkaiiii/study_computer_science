package No2_Java8_in_Action.part4

import No2_Java8_in_Action.part3.OptionalModel.Person

import scala.collection.MapOps


//scala当中的单例
object UnderstandScala {
  def helloBeer(): Unit = {
    var n = 2
    while (n <= 6) {
      println(s"Hello $n bottles of beer")
      n += 1
    }
  }

  private def getCarInsuranceName(person: Option[Person], minAge: Int) = person.filter(_.getCar.equals("car")).getOrElse("Unknow")


  def rangeForeach(): Unit = {
    2 to 6 foreach { n => println(s"Hello $n bottles of bear") }
  }

  //scala当中的函数
  def isJavaMentioned(tweet: String): Boolean = tweet.contains("Java")

  def isShortTweet(tweet: String): Boolean = tweet.length < 20

  //科里化所使用的函数
  def multiplyCurry(x: Int)(y: Int) = x * y

  def understandScala(): Unit = {
    //创建map
    val authorsToAge = Map("Raoul" -> 23, "Mario" -> 40, "Alan" -> 53)
    //创建List
    var authors = List("Raoul", "Mario", "Alan")
    //创建Set
    val numbers = Set(1, 1, 2, 3, 5, 8)
    val newNumbers = numbers + 8 //这会添加一个数字，并且返回一个新的对象
    val linesLongUpper = authors.filter(l => l.length() > 10).map(l => l.toUpperCase) //将所有作者名长度大于10的转换为大写
    //scala支持元组
    val raoul = ("Raoul", "+44 124214214")
    val book = (2014, "Java 8 in action", "Manning")
    //还可以根据他们的位置，通过存储器访问元组当中的元素
    println(book._1)
    println(raoul._2)

    //再Scala中，可以直接传递这两个方法给内嵌的filter
    val tweets = List("I love the new features in Java 8", "How's it going?", "An SQL query walks into a bar, sees two tables and says 'Can I join you?'")
    tweets.filter(isJavaMentioned).foreach(println)
    tweets.filter(isShortTweet).foreach(println)
    //Scala理所应当的会支持匿名函数
    val isLongTweet = (tweet: String) => tweet.length > 60
    println(isLongTweet("21242142")) //这个相当于调用了isLongTweet.apply()

    //Scala当中添加了对于闭包的支持
    var count = 0
    val inc = () => count += 1
    inc()
    println(count)
    inc()
    println(count)

    val r = multiplyCurry(2)(10) //这里，先进行multiply(2)，然后进行multiply(10)
    //所以可以对中间结果进行复用
    val multiplyByTwo: Int => Int = multiplyCurry(2)
    val r2 = multiplyByTwo(2)
    println(r2)

    //Scala当中的类
    println(new Empty().isEmpty())
    class Box
    val b1 = new Box() with sized //在实例化的时候构建trait
    println(b1.isEmpty())
    val b2 = new Box()
    //    b2.isEmpty() //编译错误，没有这个方法。
  }

  //Scala当中的接口：trait
  trait sized {
    var size: Int = 0 //Scala当中的接口可以有成员变量
    def isEmpty() = size == 0 //默认实现
  }

  class Empty extends sized

}
