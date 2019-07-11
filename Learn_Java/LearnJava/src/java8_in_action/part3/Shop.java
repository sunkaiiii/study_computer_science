package java8_in_action.part3;

import java.util.List;
import java.util.Random;
import java.util.concurrent.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Shop {
    private String shopName;
    private static Random random = new Random(System.currentTimeMillis());

    Shop(String shopName) {
        this.shopName = shopName;
    }

    private double getPrice(String product) {
        return calculatePrice(product);
    }

    //同步方法显然无法令人接受
    //引入CompletableFuture使用异步方法
    Future<Double> getPriceAsync(String product) {
//        CompletableFuture<Double> futurePrice=new CompletableFuture<>();
//        new Thread(()->{
//            try {
//                double price = calculatePrice(product);
//                futurePrice.complete(price);
//            }catch (Exception ex){
//                futurePrice.completeExceptionally(ex); //使用future的方法抛出问题的原因
//            }
//        }).start();
//        return futurePrice;

        //除了上述这种Future的写法，还可以使用supplyAsync的工厂类创建
        //使用工厂类创建的future和上面的写的是完全一致的
        return CompletableFuture.supplyAsync(() -> calculatePrice(product));
    }

    private static void delay() {
        try {
            Thread.sleep(1000L); //模拟延迟
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    private double calculatePrice(String procut) {
        delay();
        return random.nextDouble() * procut.charAt(0) + procut.charAt(1);
    }

    private double calculatePriceWithRandomDelay(String procut) {
        randomDelay();
        return random.nextDouble() * procut.charAt(0) + procut.charAt(1);
    }

    static List<String> findPrices(List<Shop> shops, String product) {
        return shops.stream().map(shop -> String.format("%s price is %.2f", shop.shopName, shop.getPrice(product))).collect(Collectors.toList());
    }

    static List<String> findPricesParalle(List<Shop> shops, String product) {
        return shops.parallelStream().map(shop -> String.format("%s price is %.2f", shop.shopName, shop.getPrice(product))).collect(Collectors.toList());
    }

    static List<String> findPricesAsync(List<Shop> shops, String product) {
        List<CompletableFuture<String>> priceFutures = shops.stream().map(shop -> CompletableFuture.supplyAsync(() ->
                String.format("%s price is %.2f", shop.shopName, shop.getPrice(product)))).collect(Collectors.toList());
        return priceFutures.stream().map(CompletableFuture::join).collect(Collectors.toList()); //join中的方法和get具有相同的意义，唯一的不同就是join不会抛出任何检测到的异常
        //注意到这里使用了两个stream流水线。而不是在同一个流水线上放置两个map操作。考虑到流操作之间的延迟特性
        //如果在单一流水线中处理流，法相不同商家的请求只能以同步、顺序执行的方式才会成功。

    }

    static List<String> advanceFindPricesAsync(List<Shop> shops, String product) {
        //为方法定制的执行器
        final Executor executor = getExecutor(shops);
        List<CompletableFuture<String>> priceFutures = shops.stream().map(shop -> CompletableFuture.supplyAsync(() ->
                String.format("%s price is %.2f", shop.shopName, shop.getPrice(product)), executor)).collect(Collectors.toList());
        return priceFutures.stream().map(CompletableFuture::join).collect(Collectors.toList()); //join中的方法和get具有相同的意义，唯一的不同就是join不会抛出任何检测到的异常
        //注意到这里使用了两个stream流水线。而不是在同一个流水线上放置两个map操作。考虑到流操作之间的延迟特性
        //如果在单一流水线中处理流，法相不同商家的请求只能以同步、顺序执行的方式才会成功。

    }

    public enum Code {
        NONE(0), SILVER(5), GOLD(10), PLATINUM(15), DIAMOND(20);

        private final int percentage;
        private Random random = new Random(System.currentTimeMillis());

        Code(int percentage) {
            this.percentage = percentage;
        }
    }

    public String getDiscountPrice(String product) {
        double price = calculatePriceWithRandomDelay(product);
        Shop.Code code = Shop.Code.values()[random.nextInt(Shop.Code.values().length)];
        return String.format("%s:%.2f:%s", product, price, code);
    }

    private static String applyDiscount(Quote quote) {
        return quote.getShopName() + " price is " + Shop.apply(quote.getPrice(), quote.getDiscountCode());
    }

    private static double apply(double price, Code code) {
        randomDelay();
        return price * (100 - code.percentage) / 100;
    }

    static List<String> findDiscountPrices(List<Shop> shops, String product) {
        //这一步中，有两个异步操作
        //分别是getDiscountPrice当中的delay
        //和applyDiscount当中的delay
        return shops.stream()
                .map(shop -> shop.getDiscountPrice(product))
                .map(Quote::parse)
                .map(Shop::applyDiscount)
                .collect(Collectors.toList());
    }

    //这时候就需要CompletableFuture来实现异步操作了
    static List<String> advancedFindDiscountPrices(List<Shop> shops, String product) {
        final Executor executor = getExecutor(shops);
        List<CompletableFuture<String>> pricesFutures = shops.stream()
                .map(shop -> CompletableFuture.supplyAsync(() -> shop.getDiscountPrice(product), executor))
                .map(future -> future.thenApply(Quote::parse))
                .map(future -> future.thenCompose(quote -> CompletableFuture.supplyAsync(() -> applyDiscount(quote), executor)))
                .collect(Collectors.toList());
        return pricesFutures.stream().map(CompletableFuture::join).collect(Collectors.toList());

    }

    //合并两个独立的CompletableFuture对象
    //在获取折扣的时候顺便进行汇率转换操作
    static Future<Double> advancedTransforDiscountPrice(Shop shop, String product) {
        Future<Double> transforFuture = CompletableFuture
                .supplyAsync(() -> shop.getDiscountPrice(product))
                .thenCombine(CompletableFuture.supplyAsync(() -> getRate("eu", "us")), (price, rate) -> Double.valueOf(price) * rate); //创建两个独立的任务，并最后整合到一起
        return transforFuture;
    }

    private static double getRate(String typeA, String typeB) {
        if ("en".equalsIgnoreCase(typeA)) {
            return 1.2;
        } else if ("us".equalsIgnoreCase(typeB)) {
            return 1.4;
        }
        return 0.5;
    }

    /*以上的所有异步操作都是在等操作完成之后才返回
    而现在想要改进的效果是，只要有返回商品价格就在第一时间显示返回值。
    首先要避免的问题就是，等待一个创建包含了所有价格的List
    应该直接处理CompletableFuture流，这样每个任务完成的时候都可以单独进行处理
     */
    private static void randomDelay() {
        int delay = 500 + random.nextInt(2000);
        try {
            Thread.sleep(delay);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }


    //重构findPrices的方法返回的Future流
    static Stream<CompletableFuture<String>> findPricesStream(List<Shop> shops, String product) {
        final Executor executor = getExecutor(shops);
        return shops.stream()
                .map(shop -> CompletableFuture.supplyAsync(() -> shop.getDiscountPrice(product), executor))
                .map(future -> future.thenApply(Quote::parse))
                .map(future -> future.thenCompose(quote ->
                        CompletableFuture.supplyAsync(
                                () -> applyDiscount(quote), executor
                        )));
    }

    private static Executor getExecutor(List<Shop> shops) {
        return Executors.newFixedThreadPool(Math.min(shops.size(), 100), r -> {
            Thread t = new Thread(r);
            t.setDaemon(true); //使用守护线程——这种方式不会阻止程序的关停
            return t;
        });
    }
}
