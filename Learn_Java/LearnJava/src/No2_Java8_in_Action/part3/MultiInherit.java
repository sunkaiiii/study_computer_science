package No2_Java8_in_Action.part3;

public class MultiInherit {
    public interface A{
        default void hello(){
            System.out.println("hello from A");
        }
    }

    public interface  B{
        default void hello(){
            System.out.println("hello from B");
        }
    }

    public static class E implements A,B{
        @Override
        public void hello() {
            A.super.hello(); //手动指定
        }
    }

    public static class D implements A{
        @Override
        public void hello() {
            System.out.println("hello from D");
        }
    }

    public static class C extends D implements A,B{
        //如果C包含了自己的hello，则使用C的
        //如果C所继承的类包含了hello的实现，则使用超类的
        //但如果同样都是A，B的默认方法，就需要指明使用哪个了
//        @Override
//        public void hello() {
//            System.out.println("hello from C");
//        }
    }
}
