package No2_Java8_in_Action.part1;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.*;
import java.util.function.*;
import java.util.stream.Collectors;

public class Main {
    static class Apple {
        private String color;
        private int weight;

        public String getColor() {
            return color;
        }

        public void setColor(String color) {
            this.color = color;
        }

        public int getWeight() {
            return weight;
        }

        public void setWeight(int weight) {
            this.weight = weight;
        }

        public static boolean isGreenApple(Apple apple) {
            return "green".equals(apple.getColor());
        }

        public static boolean isHeavyApple(Apple apple) {
            return apple.getWeight() > 150;
        }
    }


    //使用Java8，就可以将方法转换为参数传给另外一个方法
    static List<Apple> filterApples(List<Apple> inventory, Predicate<Apple> p) {
        var result = new ArrayList<Apple>();
        for (var apple : inventory) {
            if (p.test(apple)) {
                result.add(apple);
            }
        }
        return result;
    }

    //还可以为筛选这个方法制定一个泛型方法以适应不同的类
    public static <T> List<T> filter(List<T> list, Predicate<T> p) {
        List<T> result = new ArrayList<>();
        for (T e : list) {
            if (p.test(e)) {
                result.add(e);
            }
        }
        return result;
    }

    static class Person {
        private int number;
        private String name;

        Person(int number) {
            this.number = number;
        }

        Person(int number, String name) {
            this.number = number;
            this.name = name;
        }
    }

    public static void main(String[] args) {
        var testApples = new ArrayList<Apple>();
        testApples.add(new Apple());
        testApples.add(new Apple());
        //将方法传入给另外一个方法
        System.out.println(filterApples(testApples, Apple::isGreenApple));
        System.out.println(filterApples(testApples, Apple::isHeavyApple));

        //再进一步简化可以利用lambda表达式
        System.out.println(filterApples(testApples, apple -> apple.getWeight() > 150));
        System.out.println(filterApples(testApples, apple -> apple.getWeight() > 150 || "green".equals(apple.getColor())));

        //利用stream API，甚至filterApples这个方法都不需要了
        System.out.println(testApples.stream().filter(apple -> apple.getWeight() > 150).collect(Collectors.toList()));

        //使用泛型方法进行筛选
        System.out.println(filter(testApples, apple -> "green".equals(apple.getColor())));

        //使用bufferedReader类
        try {
            String oneLine = BufferedReaderProducer.processFile(BufferedReader::readLine);
            String twoLines = BufferedReaderProducer.processFile(br -> br.readLine() + br.readLine());
            System.out.println(oneLine);
            System.out.println(twoLines);
        } catch (IOException e) {
            e.printStackTrace();
        }

        //Java8当中方法引用的一些示例
        List<String> str = Arrays.asList("a", "b", "c", "d");
        str.sort((s1, s2) -> s1.compareToIgnoreCase(s2)); //使用一般的写法
        str.sort(String::compareToIgnoreCase); //使用方法引用
        Function<String, Integer> stringIntegerFunction = (String s) -> Integer.parseInt(s);
        Function<String, Integer> stringIntegerFunction1 = Integer::parseInt; //等效写法
        BiPredicate<List<String>, String> contains = (list, element) -> list.contains(element);
        BiPredicate<List<String>, String> contains2 = List::contains; //等效写法
        Supplier<String> c1 = String::new; //指向构造函数的方法引用
        //如果构造函数的签名是有参数的，那么他I就适合Function接口的签名
        Function<Integer, Person> getPerson = Person::new;
        //如果具有两个参数的构造函数，那么就适合BiFunction接口的签名
        BiFunction<Integer, String, Person> getPerson2 = Person::new;

        //现在回到一开始的苹果的实例。
        testApples.sort(Comparator.comparing(Apple::getWeight)); //按照苹果重量排序
        //对应的，comparing方法就是构建了一个Comparator
        var c = Comparator.comparing(Apple::getWeight);
        c.reversed(); //逆序
        c.reversed().thenComparing(Apple::getColor);//如果一样重的时候，就按照颜色排序
        //谓词复合，带来更加灵活的谓词逻辑和依旧清晰的表达
        Predicate<Apple> redApple = apple -> "red".equalsIgnoreCase(apple.getColor());
        var notRedApple = redApple.negate(); //取非
        var redAndHeavyApple = redApple.and(a -> a.getWeight() > 150);
        var redAndHeavyAppleOrGreen = redApple
                .and(a -> a.getWeight() > 150)
                .or(a -> "green".equalsIgnoreCase(a.getColor()));

        //函数组合
        Function<Integer, Integer> f = x -> x + 1;
        Function<Integer, Integer> g = x -> x * 2;
        var h = f.andThen(g);
        int result = h.apply(1); //这里会返回4
        System.out.println(result);
        var h2 = f.compose(g);
        System.out.println(h2.apply(1)); //会输出3
    }
}
