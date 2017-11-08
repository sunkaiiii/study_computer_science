package Design_Pattern.SIGLETON;

/**
 * Created by sunkai on 2017/11/8
 */
public class Singleton {
    private static Singleton theInstance=null;
    private Singleton(){}

    public static Singleton Instance(){
        if(theInstance==null){
            theInstance=new Singleton();
            return theInstance;
        }
        return theInstance;
    }
}
