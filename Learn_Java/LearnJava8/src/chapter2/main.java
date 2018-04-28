package chapter2;

import javax.swing.*;
import java.util.function.BinaryOperator;
import java.util.function.Predicate;

public class main {
    public static void main(String[] args){
        //简单的lambda表达式
        Runnable noArguements=()-> System.out.println("Hello World");
        noArguements.run();
        //类型推断
        Predicate<Integer> atLeast5=x->x>5;
        System.out.println(atLeast5.test(6));
        BinaryOperator<Long> add=(x,y)->x+y;
        System.out.println(add.apply(4L,5L));

        //lambda实现的泛型接口
        Function<Integer,Boolean> func=x->x==1;
        System.out.println(func.apply(1));

        //JButton的lambda实现点击事件
        JButton button=new JButton();
        button.addActionListener(event-> System.out.println(event.getActionCommand()));
    }

    public interface Function<T,R>{
        R apply(T t);
    }
}
