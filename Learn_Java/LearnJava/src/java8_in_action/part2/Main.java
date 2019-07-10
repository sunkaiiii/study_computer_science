package java8_in_action.part2;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.concurrent.ForkJoinPool;
import java.util.stream.*;

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

        //把列表中的交易按交易人分组
        System.out.println(transactions.stream().collect(Collectors.groupingBy(Transaction::getTrader)));
    }

    private static void handleCollector() {
        var menu = getList();
        System.out.println(menu.stream().collect(Collectors.counting()));
        //等效可以写成这个代码
        System.out.println(menu.stream().count());

        //找到菜中能量最小的菜
        Comparator<Dish> dishCaloriesComparator = Comparator.comparingInt(Dish::getCalories);
        Optional<Dish> mostCalorieDish = menu.stream().collect(Collectors.maxBy(dishCaloriesComparator));

        //汇总操作
        int totalCalories = menu.stream().collect(Collectors.summingInt(Dish::getCalories));
        //计算平均能量
        double aveCalories = menu.stream().collect(Collectors.averagingInt(Dish::getCalories));
        System.out.println("total calories:" + totalCalories);
        System.out.println("average calories:" + aveCalories);
        //使用全部工厂类做一次全部的统计
        IntSummaryStatistics menuStatistics = menu.stream().collect(Collectors.summarizingInt(Dish::getCalories));
        System.out.println(menuStatistics);
        //连接字符串
        System.out.println(menu.stream().map(Dish::getName).collect(Collectors.joining()));
        //还可以使用joining的重载方法
        System.out.println(menu.stream().map(Dish::getName).collect(Collectors.joining(", ")));

        //以上的这些其实都是reducing方法的特化
        //如果不嫌麻烦，也可以直接使用reducing
        totalCalories = menu.stream().collect(Collectors.reducing(0, Dish::getCalories, (i, j) -> i + j));
        System.out.println(totalCalories);
        //当然最简单的方法是映射成intStream
        totalCalories = menu.stream().mapToInt(Dish::getCalories).sum();
        System.out.println(totalCalories);

        //使用groupingBy进行元素的.分组
        Map<Dish.Type, List<Dish>> dishesByType = menu.stream().collect(Collectors.groupingBy(Dish::getType));
        System.out.println(dishesByType);
        //使用多级分组
        Map<Dish.Type, Map<Dish.CALORIC_LEVEL, List<Dish>>> dishesByTypeCaloricLevel = menu.stream().collect(
                Collectors.groupingBy(Dish::getType,
                        Collectors.groupingBy(dish -> {
                            if (dish.getCalories() <= 400) {
                                return Dish.CALORIC_LEVEL.DIET;
                            } else if (dish.getCalories() <= 700) {
                                return Dish.CALORIC_LEVEL.NORMAL;
                            } else {
                                return Dish.CALORIC_LEVEL.HIGH;
                            }
                        }))
        );
        System.out.println(dishesByTypeCaloricLevel);
        //gourpingBy的第二个参数是可以传递任何类型的
        Map<Dish.Type, Long> typesCount = menu.stream().collect(Collectors.groupingBy(Dish::getType, Collectors.counting()));
        System.out.println(typesCount);
        //collectingAndThen可以在执行收集之后再进行下一步处理
        //先按照类型分类，然后找到每个分类中能量最大的那个项目
        Map<Dish.Type, Dish> mostCaloricByType = menu.stream().collect(Collectors.groupingBy(Dish::getType, Collectors.collectingAndThen(Collectors.maxBy(Comparator.comparingInt(Dish::getCalories)), Optional::get)));
        //收集器工作的时候，groupingBy是最外层，根据菜肴类型把菜单流分组
        //groupingBy收集器包裹着collectingAndThen收集器，因此分组操作得到的每个子流都用这第二个收集器做进一步规约
        //随后交由collectingAndThen收集器里面的第三个收集器maxBy处理
        //将由规约收集器进行处理。collectingAndThen收集器会对其结果应用Optional:get转换函数
        //将三个子流分别执行这一过程并转换而得到的三个值，也就似乎各个类型中热量最高的Dish，将成为groupingBy收集器返回的Map中与各个分类键相关联的值。
        System.out.println(mostCaloricByType);
        //对于每种类型Dish，菜单中有哪些CaloricLevel
        //可以把groupingBy和mapping收集器结合起来
        Map<Dish.Type, Set<Dish.CALORIC_LEVEL>> caloricLevelByType =
                menu.stream().collect(
                        Collectors.groupingBy(Dish::getType, Collectors.mapping(
                                dish -> {
                                    if (dish.getCalories() <= 400) {
                                        return Dish.CALORIC_LEVEL.DIET;
                                    } else if (dish.getCalories() <= 700) {
                                        return Dish.CALORIC_LEVEL.NORMAL;
                                    } else {
                                        return Dish.CALORIC_LEVEL.HIGH;
                                    }
                                }
                                , Collectors.toSet()))
                );
        //先进行Type的分组
        //然后对每组Type里的流使用Mapping进行变换
        //最后将变换好的流收集到Set当中。
        //还可以在toSet的收集器当中选用toCollection(HashSet::new)来指定生成的set的类型。
        System.out.println(caloricLevelByType);

        //分区是分组的一种特殊情况
        //仅仅使用true和false来区分
        Map<Boolean, List<Dish>> partitionedMenu =
                menu.stream().collect(Collectors.partitioningBy(Dish::isVegetarian));
        System.out.println(partitionedMenu);
        //利用重载版本使用谓词的非
        Map<Boolean, Map<Dish.Type, List<Dish>>> vegetarianDishesByType =
                menu.stream().collect(Collectors.partitioningBy(Dish::isVegetarian, Collectors.groupingBy(Dish::getType)));
        //这个版本当中产生了素食和非素食的流，然后在细分获得了二级的map
        System.out.println(vegetarianDishesByType);
        //写法是很灵活的，比如可以找到素食和非素食当中热量最高的菜
        Map<Boolean, Dish> maxCaloricPartitionedByVegetarian =
                menu.stream()
                        .collect(Collectors.partitioningBy(Dish::isVegetarian
                                , Collectors.collectingAndThen(
                                        Collectors.maxBy(Comparator.comparingInt(Dish::getCalories))
                                        , Optional::get)));
        System.out.println(maxCaloricPartitionedByVegetarian);

        //利用分区创建一个质数和非质数流
        Map<Boolean, List<Integer>> partitionPrime = IntStream.rangeClosed(2, 500).limit(20).boxed().collect(Collectors.partitioningBy(Main::isPrime));
        System.out.println(partitionPrime);

        //使用自定义收集器
        var dishes = menu.stream().collect(new ToListCollector<>());
        System.out.println(dishes);
        //也可以使用collect的重载方法
        //但是这种写法的可读性却没有自定义来得那么好。
        dishes = menu.stream().collect(ArrayList::new, List::add, List::addAll);
        System.out.println(dishes);

        //使用新编写的收集器来创建指数
        var primes = IntStream.rangeClosed(2, 500).limit(50).boxed().collect(new PrimeNumberCollector());
        System.out.println(primes);
    }

    private static boolean isPrime(int candidate) {
        return IntStream.rangeClosed(2, (int) Math.sqrt(candidate)).noneMatch(i -> candidate % i == 0);
    }


    private static void handleParraleStream() {
        //将顺序流转换为并行流
        System.out.println(Stream.iterate(1L, i -> i + 1).limit(5000L).parallel().reduce(0L, Long::sum));

        //测试分支/合并框架
        long[] numbers = LongStream.rangeClosed(1, 100).toArray();
        var task = new ForkJoinSumCalculator(numbers);
        System.out.println(new ForkJoinPool().invoke(task)); //在实际的生产中，new多个ForkJoinPool是没有意义的。一般都弄成单例。

        final String SENTENCE = " Nel   mezzo del cammin  di nostra  vita " + "mi  ritrovai in una  selva oscura" + " ché la  dritta via era   smarrita ";
        System.out.println(countWordsIteratively(SENTENCE));
        System.out.println(IntStream.range(0,SENTENCE.length()).mapToObj(SENTENCE::charAt).reduce(new WordCounter(0,true),WordCounter::accumulate,WordCounter::combine).getCounter());
        //如果使用并行流，会惊喜的发现答案不对了
        //原因是原始的字符串会在任意的地方拆分，而且顺序也会不对
        System.out.println(IntStream.range(0,SENTENCE.length()).mapToObj(SENTENCE::charAt).parallel().reduce(new WordCounter(0,true),WordCounter::accumulate,WordCounter::combine).getCounter());
        //这个时候需要运行新的splitor来处理并行流了
        Spliterator<Character> spliterator=new WordCounterSpliterator(SENTENCE);
        //使用自定义的splitor来让分割更加受控
        System.out.println(StreamSupport.stream(spliterator,true).reduce(new WordCounter(0,true),WordCounter::accumulate,WordCounter::combine).getCounter());
    }

    //一种传统的迭代数字统计方法
    private static int countWordsIteratively(String s){
        int counter=0;
        boolean lastSpace=true;
        for(char c:s.toCharArray()){
            if(Character.isWhitespace(c)){
                lastSpace=true;
            }else{
                if(lastSpace)
                    counter++;
                lastSpace=false;
            }
        }
        return counter;
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
                        System.out.print((int) i + ",");
                    }
                    System.out.println();
                }
        );

        //从文件中读取流，并查看有多少个不同的单词。
        long uniqueWords = 0;
        try (Stream<String> lines = Files.lines(Paths.get("/Users/sunkai/Documents/OneDrive/手机使用时长记录.txt"), Charset.defaultCharset())) {
            uniqueWords = lines.flatMap(line -> Arrays.stream(line.split(" "))).distinct().count();
            System.out.println(uniqueWords);
        } catch (IOException e) {
            e.printStackTrace();
        }


        //生成一个无限流
        Stream.iterate(0, n -> n + 2).limit(10).forEach(each -> System.out.print(each + " "));
        System.out.println();
        //第一种使用无限流生成斐波那契数列
        Stream.iterate(new int[]{0, 1}, a -> new int[]{a[1], a[0] + a[1]}).limit(10).map(array -> array[0]).forEach(each -> System.out.print(each + " "));

        //使用收集器
        handleCollector();

        //并行流
        handleParraleStream();
    }


}
