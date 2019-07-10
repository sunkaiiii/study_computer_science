package java8_in_action.part3;


import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.function.Function;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {
    public static void main(String[] args) {
        showStrategy();
        showObserver();
        showProcessing();
        showHardnessOfDebug();
        debugWithPeek();
        defaultFunction();
        multiInherite();
        ApplyOptionalToAvoidNullPointerException();

        //使用异步API
        Shop shop = new Shop("Bestshop");
        long start = System.nanoTime();
        var futurePrice = shop.getPriceAsync("my favrouite product");
        long invocationTime = ((System.nanoTime()) - start) / 1_000_000;
        System.out.println("Invocation returned after " + invocationTime + " msecs");
        //doSomethingElse() 执行更多任务
        try {
            double price = futurePrice.get();
            System.out.printf("Price is %.2fn", price);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        long retrievalTime = ((System.nanoTime()) - start) / 1_000_000;
        System.out.println("Price returned after " + retrievalTime + " msecs");
        //同步方法在遍历时候要不断等待，这可能需要好几秒的时间
        //因为电脑最高线程有8个，所以这里创建8个让问题突显
        List<Shop> shops = IntStream.rangeClosed(1,8).mapToObj(i->new Shop(String.valueOf(i))).collect(Collectors.toList());
        start = System.nanoTime();
        System.out.println(Shop.findPrices(shops,"myPhone27S"));
        long duration = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Done in " + duration + " msecs");
        //使用并行流会好一些，但仍有改进空间
        start = System.nanoTime();
        System.out.println(Shop.findPricesParalle(shops,"myPhone27S"));
        duration = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Done in " + duration + " msecs");
        //使用CompletableFuture之后会发现它的执行时间要比并行流慢
        //原因在于并行流为每个线程都分配了一个任务
        //而线程池的大小正好等同于电脑CPU的核心数
        //所以8个任务正合适
        start = System.nanoTime();
        System.out.println(Shop.findPricesAsync(shops,"myPhone27S"));
        duration = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Done in " + duration + " msecs");
    }

    private static void ApplyOptionalToAvoidNullPointerException() {
        //使用Optional来创建更健壮的代码
        Optional<OptionalModel.Insurance> optionalInsurance = Optional.of(new OptionalModel.Insurance());
        Optional<String> name = optionalInsurance.map(OptionalModel.Insurance::getName); //如果有值的话就转换，没有的话就什么都不做
        //那么如何转换这个有问题的代码呢
        OptionalModel.Person person = new OptionalModel.Person();
        try {
            String getCarInsuranceName = person.getCar().get().getInsurance().get().getName();
            String getCarInsuranceNameSafe = Optional.ofNullable(person).flatMap(OptionalModel.Person::getCar).flatMap(OptionalModel.Car::getInsurance).map(OptionalModel.Insurance::getName).orElse("Unknow");//如果Optional的结果值为空，设置默认值
        } catch (Exception e) {
            e.printStackTrace();
        }
        //Optional的stream是很像的，也可以使用filter方法
        Optional<OptionalModel.Insurance> insuranceOptional = Optional.ofNullable(null);
        optionalInsurance.filter(insurance -> "CambridgeInsurace".equalsIgnoreCase(insurance.getName())).ifPresent(System.out::println);
    }


    private static void multiInherite() {
        //多继承的原则
        new MultiInherit.C().hello();
        new MultiInherit.D().hello();
        new MultiInherit.E().hello();
    }

    private static void defaultFunction() {
        List<Integer> numbers = Arrays.asList(3, 5, 1, 2, 6);
        //使用Java8引入的静态方法，它返回一个Comparator对象，并按照自然序列顺序对元素进行排序
        numbers.sort(Comparator.naturalOrder());
    }

    private static void debugWithPeek() {
        //使用peek方法进行日志调试
        List<Integer> result = IntStream.rangeClosed(0, 50)
                .boxed()
                .peek(x -> System.out.println("from stream " + x))
                .map(x -> x + 17)
                .peek(x -> System.out.println("after map: " + x))
                .filter(x -> x % 2 == 0)
                .peek(x -> System.out.println("after filter: " + x))
                .limit(3)
                .peek(x -> System.out.println("after limit: " + x))
                .collect(Collectors.toList());
        System.out.println(result);
    }

    private static void showHardnessOfDebug() {
        //故意创造一个异常情况
        //可以发现lambda表达式的栈跟踪可能非常困难
//        List<Point> points = Arrays.asList(new Point(12, 2), null);
//        points.stream().map(Point::getX).forEach(System.out::println);
    }

    private static void showProcessing() {
        //责任链模式的传统写法
        ProcessingObject<String> p1 = new ProcessorModel.HeaderTextProcessing();
        ProcessingObject<String> p2 = new ProcessorModel.SpellCheckerProcessing();
        p1.setSuccessor(p2);
        System.out.println(p1.handle("Aren't labdas really sexy?!!"));
        //lambda的写法避免类构造
        UnaryOperator<String> headerProcessing = text -> "From lambda " + text;
        UnaryOperator<String> spellCheckerProcessing = text -> text.replaceAll("labda", "lambda");
        Function<String, String> pipeline = headerProcessing.andThen(spellCheckerProcessing);
        System.out.println(pipeline.apply("Aren't labdas really sexy?!!"));
    }

    private static void showObserver() {
        //使用传统方法应用观察者模式
        ObserverModel observerModel = new ObserverModel();
        observerModel.registerObserver(new ObserverModel.NYTimes());
        observerModel.registerObserver(new ObserverModel.Guardian());
        observerModel.registerObserver(new ObserverModel.LeMonde());
        observerModel.notifyObservers("The queen said her favourite book is Java 8 in Action!");
        //使用lambda表达式替换僵化的代码
        observerModel.registerObserver((s) -> {
            if (s != null && s.contains("money")) {
                System.out.println("Breaking news in NY! " + s);
            }
        });
        observerModel.registerObserver((s) -> {
            if (s != null && s.contains("queen")) {
                System.out.println("Lambda news in London! " + s);
            }
        });
        observerModel.notifyObservers("The queen said her favourite book is Java 8 in Action!");
    }

    private static void showStrategy() {
        //使用传统的方式应用策略模式
        StrategyModel numbericModel = new StrategyModel(new StrategyModel.IsNumeric());
        StrategyModel lowerCaseModel = new StrategyModel(new StrategyModel.IsAllLowerCase());
        var b1 = numbericModel.validate("aaaa");
        var b2 = lowerCaseModel.validate("aaaa");
        System.out.println(b1);
        System.out.println(b2);
        //使用lambda表达式应用策略模式，免去了new一个实现接口的类
        numbericModel = new StrategyModel((s) -> s.matches("\\d+"));
        lowerCaseModel = new StrategyModel((s) -> s.matches("[a-z]+"));
        System.out.println(numbericModel.validate("aaaa"));
        System.out.println(lowerCaseModel.validate("aaaa"));
    }
}
