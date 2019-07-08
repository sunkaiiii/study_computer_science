package java8_in_action.cp2;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Main {
    private static List<Dish> getList() {
        return Arrays.asList(
                new Dish("pork", false, 800, Dish.Type.MEAT),
                new Dish("beef", false, 700, Dish.Type.MEAT),
                new Dish("chicken", false, 400, Dish.Type.MEAT),
                new Dish("french fries", true, 530, Dish.Type.OTHER),
                new Dish("rice", true, 350, Dish.Type.OTHER),
                new Dish("season fruit", true, 120, Dish.Type.OTHER),
                new Dish("pizza", true, 550, Dish.Type.OTHER),
                new Dish("prawns", false, 300, Dish.Type.FISH),
                new Dish("salmon", false, 450, Dish.Type.FISH));
    }

    private static List<Transaction> getTransactions() {
        Trader raoul = new Trader("Raoul", "Cambridge");
        Trader mario = new Trader("Mario", "Milan");
        Trader alan = new Trader("Alan", "Cambridge");
        Trader brian = new Trader("Brian", "Cambridge");
        return Arrays.asList(
                new Transaction(brian, 2011, 300),
                new Transaction(raoul, 2012, 1000),
                new Transaction(raoul, 2011, 400),
                new Transaction(mario, 2012, 710),
                new Transaction(mario, 2012, 700),
                new Transaction(alan, 2012, 950)
        );
    }

    //    (1) 找出2011年发生的所有交易，并按交易额排序（从低到高）。
//            (2) 交易员都在哪些不同的城市工作过？
//            (3) 查找所有来自于剑桥的交易员，并按姓名排序。
//            (4) 返回所有交易员的姓名字符串，按字母顺序排序。
//            (5) 有没有交易员是在米兰工作的？
//            (6) 打印生活在剑桥的交易员的所有交易额。
//            (7) 所有交易中，最高的交易额是多少？
//            (8) 找到交易额最小的交易。
    private static void handleTransaction() {
        var transactions = getTransactions();
        //1
        System.out.println(transactions.stream().filter(transaction -> transaction.getYear() == 2011).sorted(Comparator.comparing(Transaction::getValue)).collect(Collectors.toList()));
        //2
        System.out.println(transactions.stream().map(transaction -> transaction.getTrader().getCity()).distinct().collect(Collectors.toList()));
        //3
        System.out.println(transactions.stream().filter(transaction -> "Cambridge".equalsIgnoreCase(transaction.getTrader().getCity())).map(transaction -> transaction.getTrader().getName()).distinct().sorted(String::compareTo).collect(Collectors.toList()));
        //4
        System.out.println(transactions.stream().map(transaction -> transaction.getTrader().getName()).distinct().sorted(String::compareTo).collect(Collectors.toList()));
        //5
        System.out.println(transactions.stream().anyMatch(transaction -> "Milan".equalsIgnoreCase(transaction.getTrader().getCity())));
        //6
        System.out.println(transactions.stream().filter(transaction -> "Cambridge".equalsIgnoreCase(transaction.getTrader().getCity())).map(Transaction::getValue).reduce(0, Integer::sum));
        //7
        System.out.println(transactions.stream().map(Transaction::getValue).reduce(0, Integer::max));
        //8
        transactions.stream().min(Comparator.comparing(Transaction::getValue)).ifPresent(System.out::println);
    }

    public static void main(String[] args) {
        var menu = getList();

        var threeHighCaloricDishNames = menu.stream().filter(d -> d.getCalories() > 300)
                .map(Dish::getName)
                .limit(3) //只筛选前三个
                .collect(Collectors.toList());
        System.out.println(threeHighCaloricDishNames);
        //流的内部处理会让数据遍历只会出现一次
        System.out.println(menu.stream().filter(d -> {
            System.out.println("filtering" + d.getName());
            return d.getCalories() > 300;
        }).map(d -> {
            System.out.println("mapping" + d.getName());
            return d.getName();
        })
                .limit(3)
                .collect(Collectors.toList()));

        //给一个list，列出里面各不相同的字符
        List<String> words = Arrays.asList("hello", "world");
        //错误版本
        System.out.println(words.stream().map(word -> word.split("")).distinct().collect(Collectors.toList()));
        //一种解决方案，但仍不对
        System.out.println(words.stream().map(word -> word.split("")).map(Arrays::stream).distinct().collect(Collectors.toList()));
        //解决方案，使用flatMap
        System.out.println(words.stream().map(word -> word.split("")).flatMap(Arrays::stream).distinct().collect(Collectors.toList())); //flatMap方法关键就在于各个数组不是分别映射成不同的流，而是映射称了一个流的内容。

        //给定两个数字列表，如何返回所有的数对呢。
        List<Integer> a1 = Arrays.asList(1, 2, 3);
        List<Integer> a2 = Arrays.asList(4, 5);
        var result = a1.stream().flatMap(i -> a2.stream().map(j -> new int[]{i, j})).collect(Collectors.toList());
        result.forEach(ints -> {
            for (int i : ints) {
                System.out.print(i + ",");
            }
            System.out.println();
        });
        //给定两个数字列表，返回能被3整出的数对。
        System.out.println();
        var result2 = a1.stream().flatMap(i -> a2.stream().filter(j -> (i + j) % 3 == 0).map(j -> new int[]{i, j})).collect(Collectors.toList());
        result2.forEach(ints -> {
            for (int i : ints) {
                System.out.print(i + ",");
            }
            System.out.println();
        });

        //查找和匹配
        if (menu.stream().anyMatch(Dish::isVegetarian)) { //匹配一个元素
            System.out.println("anyMatch yes");
        }

        if (menu.stream().allMatch(d -> d.getCalories() < 1000)) {
            System.out.println("allMatch yes");
        }

        if (menu.stream().noneMatch(d -> d.getCalories() >= 1000)) {
            System.out.println("noneMatch yes");
        }

        //查找元素
        Optional<Dish> dish = menu.stream().filter(Dish::isVegetarian).findAny();
        //Optional类是一个容器类，代表一个值存在或者不存在。当ifPresent为真的时候，说明包含值。
        menu.stream().filter(Dish::isVegetarian).findAny().ifPresent(d -> System.out.println(d.getName()));

        //Stream的一个练习
        handleTransaction();

        //特化类型的Stream
        List<Integer> integers = Arrays.asList(1, 2, 3, 4, 5, 6);
        System.out.println(integers.stream().mapToInt(i -> i).max().orElse(-33)); //如果没有找到最大值，则按照默认的-33显示。也可在特化流当中使用boxed方法转换为一般的流。

        //在生成数据流的方法上，提供了静态方法
        IntStream evenNumbers = IntStream.rangeClosed(1, 100).filter(n -> n % 2 == 0); //1-100的偶数流
        System.out.println(evenNumbers.count());

        //生成勾股数
        var resultInts = IntStream
                .rangeClosed(1, 1000)
                .boxed()
                .flatMap(a -> IntStream.rangeClosed(1, 5000)
                        .filter(b -> Math.sqrt(a * a + b * b) % 1 == 0)
                        .mapToObj(b -> new int[]{a, b, (int) Math.sqrt(a * a + b * b)}));
        //这还不是最优的写法，因为要算两次平方根
        var betterResultInts = IntStream.rangeClosed(1, 1000).boxed().flatMap(a -> IntStream.rangeClosed(1, 1000).mapToObj(b -> new double[]{a, b, Math.sqrt(a * a + b * b)})).filter(a -> a[2] % 1 == 0);
        resultInts.limit(5).forEach(earchInts -> {
                    for (int i : earchInts) {
                        System.out.print(i + ",");
                    }
                    System.out.println();
                }
        );
        betterResultInts.limit(5).forEach(earchInts -> {
                    for (double i : earchInts) {
                        System.out.print((int)i + ",");
                    }
                    System.out.println();
                }
        );

        //从文件中读取流，并查看有多少个不同的单词。
        long uniqueWords=0;
        try(Stream<String> lines= Files.lines(Paths.get("/Users/sunkai/Documents/OneDrive/手机使用时长记录.txt"), Charset.defaultCharset())){
            uniqueWords=lines.flatMap(line->Arrays.stream(line.split(" "))).distinct().count();
            System.out.println(uniqueWords);
        }catch (IOException e){
            e.printStackTrace();
        }


        //生成一个无限流
        Stream.iterate(0,n->n+2).limit(10).forEach(each-> System.out.print(each+" "));
        System.out.println();
        //第一种使用无限流生成斐波那契数列
        Stream.iterate(new int[]{0,1},a->new int[]{a[1],a[0]+a[1]}).limit(10).map(array->array[0]).forEach(each-> System.out.print(each+" "));
    }
}
