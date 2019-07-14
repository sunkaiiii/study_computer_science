package No2_Java8_in_Action.part_additional;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Main {
    public static void main(String[] args) {
        //一些在Java8之后的改变


        //Stream API的一些改进
        //无限流添加了一些重载
        //可以给无限流添加谓词了,而当谓词不满足的时候，就是流终止的时候
        IntStream.iterate(1, i -> i < 100, i -> i + 1).forEach(System.out::println);
        //比如输出大于1且小于第一个不能被4整除的数字
        IntStream.iterate(1, i -> i % 4 != 0, i -> i + 1).forEach(System.out::println);

        //现在可以将Optionl对象转换为流了
        Stream<Integer> s = Optional.of(1).stream();
        s.forEach(System.out::println);

        //在之前的例子里用的也挺多的了
        //在Java 10中，可以使用var来声明变量了
        //但是不能使用如下的形式
        //var i; 没有初始化
        //var i,j=0; 复合赋值
        //var i=null; 也不能赋值给null

        //在Java 10当中。给optional添加了orElseThrow方法
        //我在想书中还推荐在流处理当中不推荐抛出异常……
        Optional<String> test = Optional.of("asdsad");
        System.out.println(test.orElseThrow());
        test = Optional.ofNullable(null);
        try {
            System.out.println(test.orElseThrow());
        } catch (Exception e) {
            e.printStackTrace();
        }

        //Java10当中可以拷贝Collection了
        var list1 = Arrays.asList(1, 2, 4, 5);
        var list2 = List.copyOf(list1);

        //在Java11当中，String添加了一些新的方法
        //比如可以方便的去除头部和尾部的空格
        String s1 = "   s adsa   ";
        System.out.println(s1.strip());
        System.out.println(s1.stripLeading());
        System.out.println(s1.stripTrailing());
        //还可以判断某一个字符串是否是空串
        System.out.println("   ".isBlank());
        System.out.println("".isBlank());
        //以行为单位，转换为stream
        var s2 = "1\n2\n3\n";
        System.out.println(s2.lines().collect(Collectors.toList()));
        //重复某一段String
        var s3 = s2.repeat(5);
        //给定一个字符串模式s3.lines().filter(parttern)，返回一个谓词
        var parttern = Pattern.compile("2").asPredicate();
        System.out.println(s3.lines().filter(parttern).collect(Collectors.toList()));
        //Java11当中，var可用在lambda表达式里面的(如果能匹配到给定的接口的参数列表的话)
        Test test3 = (var testString) -> System.out.println("Hey");
        test3.testMethod("!@34213");

        //Java12，对于Switch也可以当作表达式了
        //可以说很像Kotlin的When表达式
        //但是现在正式版还用不了，可以开启实验性模式……
//        int number=switch(s3){
//            case "1"->1;
//            case "2"->2;
//            case "3"->3;,Collectors.counting(),
//            default->2;
//        };
        //Stream提供了一个新的Collector
        //传入两个Collector，然后根据两个Collector得到的答案在转换为最终结果
        double average=Stream.of(1,4,2,7,4,6,5).collect(Collectors.teeing(Collectors.summingDouble(i->i),Collectors.counting(),(sum,n)->sum/n));
        System.out.println(average);
    }

    interface Test {
        public void testMethod(String s);
    }

    //在Java9中，默认方法可以具有可见性了
    //越来越像抽象类了。。。
    public interface MyInterface {
        void normalInterfaceMethod();

        default void interfaceMethodWithDefault() {
            init();
        }

        default void anotherDefaultMethod() {
            init();
        }

        private void init() {
            System.out.println("beginning initialise");
        }
    }
}
