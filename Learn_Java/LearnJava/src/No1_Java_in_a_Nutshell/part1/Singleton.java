package No1_Java_in_a_Nutshell.part1;

//一个简单的线程安全的单例模式
public class Singleton {
    private final static Singleton instance=new Singleton();
    private static boolean initialised=false;

    private Singleton(){
        super();
    }

    private void init(){
        /*初始化操作*/
    }

    public static synchronized Singleton getInstance(){
        if(initialised){
            return instance;
        }
        instance.init();
        initialised=true;
        return instance;
    }
}
