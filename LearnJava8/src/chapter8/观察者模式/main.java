package chapter8.观察者模式;

/**
 * Created by sunkai on 2017/12/14
 */
public class main {
    public static void main(String args[]){
        Moon moon=new Moon();
        //原始的方法
        moon.startSpying(new Nasa());
        moon.startSpying(new Aliens());
        moon.startSpying(new Nasa());
        moon.land("An asteroid");
        //使用lambda表达式添加一个匿名观察类,实现了接口
        moon.startSpying(name->{
            if(name.contains("asteroid"))
                System.out.println("this is lambda!");
        });
        moon.land("An asteroid");
        System.out.println();
        moon.land("Apollo");
    }
}
