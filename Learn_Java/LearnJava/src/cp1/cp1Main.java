package cp1;

import java.io.File;

public class cp1Main {
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
        File dir=new File("/src/cp1");
        String[] fileList=dir.list((f,s)->{return s.endsWith(".java");});
        if(fileList==null){
            return;
        }
        for(String file:fileList){
            System.out.println(file);
        }
    }
    public static void main(String[] args) {
        cp1Main cp1Main=new cp1Main();
        cp1Main.testClosure();
    }

}
