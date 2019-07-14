package java8_in_action.part4;

import java8_in_action.part2.Dish;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.function.DoubleUnaryOperator;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.LongStream;
import java.util.stream.Stream;

public class Main {

    private static List<List<Integer>> subsets(List<Integer> list) {
        if (list.isEmpty()) {
            List<List<Integer>> ans = new ArrayList<>();
            ans.add(Collections.emptyList());
            return ans;
        }
        var first = list.get(0);
        var rest = list.subList(1, list.size());
        var subans = subsets(rest);
        var subans2 = insertAll(first, subans);
        return concat(subans, subans2);
    }

    //函数式的方法
    //合并并返回一个新的对象
    private static List<List<Integer>> concat(List<List<Integer>> subans, List<List<Integer>> subans2) {
        List<List<Integer>> r = new ArrayList<>(subans);
        r.addAll(subans2);
        return r;
    }

    //函数式的方法
    //没有改变原始对象
    private static List<List<Integer>> insertAll(Integer first, List<List<Integer>> subans) {
        List<List<Integer>> result = new ArrayList<>();
        for (List<Integer> list : subans) {
            List<Integer> copyList = new ArrayList<>();
            copyList.add(first);
            copyList.addAll(list);
            result.add(copyList);
        }
        return result;
    }

    //迭代式阶乘计算
    private static int factorialIterative(int n) {
        int r = 1;
        for (int i = 1; i <= n; i++) {
            r *= i;
        }
        return r;
    }

    //递归式的阶乘计算
    private static long factorialRecursive(long n) {
        return n == 1 ? 1 : n * factorialRecursive(n - 1);
    }

    //基于Stream的阶乘
    private static long factorialStream(long n) {
        return LongStream.rangeClosed(1, n).reduce(1, (a, b) -> a * b);
    }

    private static long factorialTailRecursive(long n) {
        return factorialHelper(1, n);
    }

    private static long factorialHelper(long i, long n) {
        return n == 1 ? i : factorialHelper(i * n, n - 1);
    }

    //科里化的例子1
    private static DoubleUnaryOperator curriedConverter(double f, double b) {
        return x -> x * f + b;
    }

    //1.构造数字流
    private IntStream numbers() {
        return IntStream.iterate(2, n -> n + 1);
    }

    //2.取得首元素
    private static int head(IntStream numbers) {
        return numbers.findFirst().getAsInt();
    }

    //3.取得Stream的尾部元素
    private static IntStream tail(IntStream numbers) {
        return numbers.skip(1);
    }

    //4递归创建由质数组成的Stream
    private static IntStream primes(IntStream numbers) {
        int head = head(numbers);
        return IntStream.concat(
                IntStream.of(head),
                primes(tail(numbers).filter(n -> n % head != 0))
        );
    }

    //结合器的思想
    //它接受f和g作为参数，并返回一个函数。
    //实现的效果是先做f然后做g
    private static <A, B, C> Function<A, C> compose(Function<B, C> g, Function<A, B> f) {
        return x -> g.apply(f.apply(x));
    }

    //结合器思想的一个应用
    //这可以执行多次函数
    private static <A> Function<A, A> repeat(int n, Function<A, A> f) {
        return n == 0 ? x -> x : compose(f, repeat(n - 1, f));
    }

    public static void main(String[] args) {
        //开始尝试第一个函数式编程的例子
        System.out.println(subsets(Arrays.asList(1, 2, 4)));
        System.out.println(factorialIterative(20));
        System.out.println(factorialRecursive(20));
        System.out.println(factorialStream(20));
        System.out.println(factorialTailRecursive(20));

        //使用科里化的工厂函数
        //它会返回一个方法
        var convertCtoF = curriedConverter(9.0 / 5, 32);
        var convertUSDtoGBP = curriedConverter(0.6, 0);
        System.out.println("f:" + convertCtoF.applyAsDouble(20.0));
        System.out.println("US:" + convertUSDtoGBP.applyAsDouble(44));

        //这个时候调用第四步，就会发生异常
        //因为Stream只能执行一次
        try {
            primes(IntStream.rangeClosed(0, 50));
        } catch (Exception e) {
            e.printStackTrace();
        }

        //延迟调用stream
        //现在可以构造一个示例
        MyList<Integer> l = new MyLinkedList<>(5, new MyLinkedList<>(10, new Empty<>()));
        //现在再构建一个延迟调用的实例
        LazyList<Integer> numbers = LazyList.from(2);
        int two = numbers.head;
        int three = numbers.tail().head(); //每调用一次tail，就会生成一个新的节点，而这个新的生成节点是懒加载的
        int four = numbers.tail().tail().head();
        System.out.println(two + " " + three + " " + four);
        //现在有了自定义延迟加载的列表
        //就可以试试自定义延迟加载的质数了
        MyList<Integer> primeNumbers = LazyList.primes(LazyList.from(2));
        for (int i = 0; i < 20; i++) {
            primeNumbers = primeNumbers.tail();
            System.out.println("No." + i + " prime is " + primeNumbers.head());
        }
        //使用结合器
        //((10*2)*2)*2
        System.out.println(repeat(3, (Integer x) -> 2 * x).apply(10));

        //再Java中调用Scala
        UnderstandScala.helloBeer();
        UnderstandScala.rangeForeach();
        UnderstandScala.understandScala();

        //将streamForker用于实践
        //这是一个异步的操作，getResult会立即返回并交由future实现
        Stream<Dish> menuStream= java8_in_action.part2.Main.getList().stream();
        StreamForker.Results results= new StreamForker<>(menuStream).fork("shortMenu", s->s.map(Dish::getName).collect(Collectors.joining(", ")))
                .fork("totalCalories",s->s.mapToInt(Dish::getCalories).sum())
                .fork("mostCaloricDish",s-> s.reduce((d1, d2) -> d1.getCalories() > d2.getCalories() ? d1 : d2).get())
                .fork("dishesByType",s->s.collect(Collectors.groupingBy(Dish::getType)))
                .getResults();
        System.out.println("Short menu:" + results.get("shortMenu"));
        System.out.println("Total calories: "+results.get("totalCalories"));
        System.out.println("Most caloric dish: "+results.get("mostCaloricDish"));
        System.out.println("Dishes by type: "+results.get("dishesByType"));

    }

}
