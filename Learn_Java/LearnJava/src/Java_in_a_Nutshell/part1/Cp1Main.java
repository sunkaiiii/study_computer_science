package Java_in_a_Nutshell.part1;

import java.io.File;

public class Cp1Main {
    interface ValueGetter {
        int getValue();
    }
    private void testClosure(){
        //java中一种闭包的实现方式
        ValueGetter[] getters=new ValueGetter[10];
        for(int i=0;i<10;i++){
            final int index=i;
            getters[index]=new ValueGetter() {
                @Override
                public int getValue() {
                    return index;
                }
            };
        }
        //局部类不在作用域中了，因此不能使用
        //但是数组中已经保存了这个类的10个引用
        //所以局部变量index依旧在方法的作用域当中
        for(ValueGetter getter:getters){
            System.out.println(getter.getValue());
        }
    }

    private void labmdaTest1(){
        //过滤器模式的lambda表达式
        File dir=new File("/src/Java_in_a_Nutshell.part1");
        String[] fileList=dir.list((f,s)->{return s.endsWith(".java");});
        if(fileList==null){
            return;
        }
        for(String file:fileList){
            System.out.println(file);
        }
    }

    private void memoryLeak(){
        int[] bigArray=new int[300000];
        //对bigArray做一些计算
        int result=compute(bigArray);
        //告知jvm回收bigArray
        bigArray=null;
        //因为程序在这里处理用户输入，会使得方法一直没有退出。
        //如果没有手动的把bigArray标记为null，就将会一直无法回收他
        //造成内存泄漏
        for(;;){
            handleInput(result);
        }
    }

    private void handleInput(int result) {
    }

    private int compute(int[] bigArray) {
        return 0;
    }

    public static void main(String[] args) {
        Cp1Main cp1Main=new Cp1Main();
        cp1Main.testClosure();
    }

}
