package No2_Java8_in_Action.part3;


import java.time.*;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeFormatterBuilder;
import java.time.temporal.ChronoField;
import java.time.temporal.ChronoUnit;
import java.time.temporal.TemporalAdjusters;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.CompletableFuture;
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
        handleAsyncQuestions();
        newTimeClasses();
    }

    private static void newTimeClasses() {
        //创建一个LocalDate
        //使用静态工厂
        LocalDate date = LocalDate.of(2014, 3, 18);
        printLocalDateInfomation(date);
        //还可以从工厂方法从从系统时钟中获取当前日期
        LocalDate today = LocalDate.now();
        printLocalDateInfomation(today);
        //类似的，一天当中的时间可以使用LocalTime表示
        var time = LocalTime.of(13, 45, 20);
        printTimeInformation(time);
        //LocalTime和LocalDate都可以通过解析字符串来创建
        date = LocalDate.parse("2014-03-18");
        time = LocalTime.parse("13:45:22");
        printLocalDateInfomation(date);
        printTimeInformation(time);
        //合并日期时间的LocalDateTime
        var dt1 = LocalDateTime.of(2014, Month.MARCH, 18, 13, 45, 20);
        var dt2 = LocalDateTime.of(date, time);
        var dt3 = date.atTime(13, 45, 20);
        var dt4 = time.atDate(date);
        var convertTime = dt1.toLocalTime();
        //使用between方法获取两个时间的时间间隔
        var d1 = Duration.between(LocalTime.now(), LocalTime.of(12, 0, 0));
        var d2 = Duration.between(Instant.now(), Instant.ofEpochSecond(4));
        System.out.println(d1 + " " + d2);
        //如果要对年月日建模，可以使用period类
        var tenDays = Period.between(LocalDate.of(2014, 3, 8), LocalDate.of(2014, 3, 18));
        //还有很多别的方法
        var threeMinutes = Duration.ofMinutes(3);
        var threeMinutes2 = Duration.of(3, ChronoUnit.MINUTES);
        var tenDays2 = Period.ofDays(10);
        var threeWeeks = Period.ofWeeks(3);
        var twoYearSixMonthsOneDay = Period.of(2, 6, 1);

        //修改LocalDate对象。这会创建一个副本，不会修改原对象
        var date1 = LocalDate.of(2014, 3, 18);
        var date2 = date1.withYear(2011);
        var date3 = date2.withDayOfMonth(25);
        var date4 = date3.with(ChronoField.MONTH_OF_YEAR, 9);
        //还有加减乘除
        date1 = date1.plusWeeks(1);
        date2 = date2.minusYears(3);
        date3 = date3.plus(6, ChronoUnit.MONTHS);
        //使用TemporalAdjuster进行更加灵活的定制
        date4 = date1.with(TemporalAdjusters.nextOrSame(DayOfWeek.FRIDAY));
        //如果么有找到自己想要的TemporalAdjust接口
        //可以自行实现接口定制
        //该接口实现是日期向后移动一天；
        //如果当天是周六或者周日，则返回下一个周一
        date4 = date.with((temporal) -> {
            var dow = DayOfWeek.of(temporal.get(ChronoField.DAY_OF_WEEK));
            int dayToAdd = 1;
            if (dow == DayOfWeek.FRIDAY) {
                dayToAdd = 3;
            } else if (dow == DayOfWeek.SATURDAY) {
                dayToAdd = 2;
            }
            return temporal.plus(dayToAdd, ChronoUnit.DAYS);
        });

        //打印输出及解析日期-时间对象
        date= LocalDate.of(2014,3,18);
        var s1=date.format(DateTimeFormatter.ISO_LOCAL_DATE);
        var s2=date.format(DateTimeFormatter.BASIC_ISO_DATE);
        System.out.println(s1);
        System.out.println(s2);
        //那么反过来解析，也可以这么搞
        date1=LocalDate.parse("20140318",DateTimeFormatter.BASIC_ISO_DATE);
        //使用静态工厂方法，创造指定模式的格式器
        var formatter=DateTimeFormatter.ofPattern("dd/MM/yyyy");
        System.out.println(date1.format(formatter));
        date1=LocalDate.parse(date1.format(formatter),formatter);
        //如果还不满足，想要更加细粒度的控制
        //可以使用DateTimeFormatterBuilder
        var italianFormatter=new DateTimeFormatterBuilder()
                .appendText(ChronoField.DAY_OF_MONTH)
                .appendLiteral(". ")
                .appendText(ChronoField.MONTH_OF_YEAR)
                .appendLiteral(" ")
                .appendText(ChronoField.YEAR)
                .parseCaseInsensitive()
                .toFormatter();
        System.out.println(date1.format(italianFormatter));

        //处理时区问题
        var romeZone=ZoneId.of("Europe/Rome");
        var zt1=date.atStartOfDay(ZoneId.of("Europe/Rome"));
        var dateTime=LocalDateTime.of(2014,Month.MARCH,18,13,45);
        var zt2=dateTime.atZone(romeZone);
        var instant=Instant.now();
        var zdt3=instant.atZone(romeZone);
        //通过ZoneID，还可以将LocalDateTime转换为Instant
        var instantFromDateTime=dateTime.atZone(romeZone); //这句编译失败
        //也可以反向处理
        Instant instant1=Instant.now();
        var timeFromInstant=LocalDateTime.ofInstant(instant,romeZone);
        System.out.println(timeFromInstant);
        //ZoneOffSet表示时区时间的偏差
        var newYorkOffset=ZoneOffset.of("-05:00"); //这个不是很推荐使用
        OffsetDateTime dateTimeInNewYork=OffsetDateTime.of(dateTime,newYorkOffset);
    }

    private static void printTimeInformation(LocalTime time) {
        System.out.println("hour:" + time.getHour());
        System.out.println("minute:" + time.getMinute());
        System.out.println("second:" + time.getSecond());
    }

    private static void printLocalDateInfomation(LocalDate date) {
        System.out.println("year:" + date.getYear());
        System.out.println("month:" + date.getMonth());
        System.out.println("day:" + date.getDayOfMonth());
        System.out.println("week:" + date.getDayOfWeek());
        System.out.println("lengthOfMonth:" + date.lengthOfMonth());
        System.out.println("leep:" + date.isLeapYear());
    }

    private static void handleAsyncQuestions() {
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
        //因为电脑最高线程有8个，所以这里创建30个让问题突显
        List<Shop> shops = IntStream.rangeClosed(1, 1).mapToObj(i -> new Shop(String.valueOf(i))).collect(Collectors.toList());
        start = System.nanoTime();
        System.out.println(Shop.findPrices(shops, "myPhone27S"));
        long duration = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Done in " + duration + " msecs");
        //使用并行流会好一些，但仍有改进空间
        start = System.nanoTime();
        System.out.println(Shop.findPricesParalle(shops, "myPhone27S"));
        duration = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Done in " + duration + " msecs");
        //使用CompletableFuture之后会发现它的执行时间要比并行流慢
        //原因在于并行流为每个线程都分配了一个任务
        //而线程池的大小正好等同于电脑CPU的核心数
        start = System.nanoTime();
        System.out.println(Shop.findPricesAsync(shops, "myPhone27S"));
        duration = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Done in " + duration + " msecs");
        //使用自定义执行器，时间大大缩短
        start = System.nanoTime();
        System.out.println(Shop.advanceFindPricesAsync(shops, "myPhone27S"));
        duration = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Done in " + duration + " msecs");
        //以最简单的方式使用Discount服务的findPrices方法
        //会发现耗时惊人
        shops = IntStream.rangeClosed(1, 10).mapToObj(i -> new Shop(String.valueOf(i))).collect(Collectors.toList());
        start = System.nanoTime();
        System.out.println(Shop.findDiscountPrices(shops, "myPhone27S"));
        duration = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Done in " + duration + " msecs");
        //这时候就又需要completableFuture登场了
        start = System.nanoTime();
        System.out.println(Shop.advancedFindDiscountPrices(shops, "hahhaha"));
        duration = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Done in " + duration + " msecs");
        //响应式异步调用
        final long newstart = System.nanoTime();
        CompletableFuture[] futures = Shop.findPricesStream(shops, "asdad")
                .map(f -> f.thenAccept(s -> System.out.println(s + " (done in " + ((System.nanoTime() - newstart) / 1_000_000) + " msecs)"))).toArray(CompletableFuture[]::new);
        CompletableFuture.allOf(futures).join(); //allOf会等待所有的任务，如果使用anyOf，就只会等到一个。
        duration = (System.nanoTime() - newstart) / 1_000_000;
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
