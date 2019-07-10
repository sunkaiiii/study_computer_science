package java8_in_action.part3;

import java.util.List;
import java.util.Random;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.Future;
import java.util.stream.Collectors;

public class Shop {
    private String shopName;
    private Random random=new Random(System.currentTimeMillis());

    public Shop(String shopName) {
        this.shopName=shopName;
    }

    public double getPrice(String product){
        return calculatePrice(product);
    }

    //同步方法显然无法令人接受
    //引入CompletableFuture使用异步方法
    public Future<Double> getPriceAsync(String product){
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
        return CompletableFuture.supplyAsync(()->calculatePrice(product));
    }
    public static void delay(){
        try{
            Thread.sleep(1000L); //模拟延迟
        }catch (InterruptedException e){
            throw  new RuntimeException(e);
        }
    }

    private double calculatePrice(String procut){
        delay();
        return random.nextDouble()*procut.charAt(0)+procut.charAt(1);
    }

    public static List<String> findPrices(List<Shop> shops,String product){
        return shops.stream().map(shop->String.format("%s price is %.2f",shop.shopName,shop.getPrice(product))).collect(Collectors.toList());
    }

    public static List<String> findPricesParalle(List<Shop> shops,String product){
        return shops.parallelStream().map(shop->String.format("%s price is %.2f",shop.shopName,shop.getPrice(product))).collect(Collectors.toList());
    }

    public static List<String> findPricesAsync(List<Shop> shops,String product){
        List<CompletableFuture<String>> priceFutures= shops.stream().map(shop->CompletableFuture.supplyAsync(()->
            String.format("%s price is %.2f",shop.shopName,shop.getPrice(product)))).collect(Collectors.toList());
        return priceFutures.stream().map(CompletableFuture::join).collect(Collectors.toList()); //join中的方法和get具有相同的意义，唯一的不同就是join不会抛出任何检测到的异常
        //注意到这里使用了两个stream流水线。而不是在同一个流水线上放置两个map操作。考虑到流操作之间的延迟特性
        //如果在单一流水线中处理流，法相不同商家的请求只能以同步、顺序执行的方式才会成功。

    }
}
