package Design_Pattern.STRATEGY;

/**
 * Created by sunkai on 2017/11/8
 */
public class ApplicationRunner {
    private Application itsApplication=null;

    public ApplicationRunner(Application app){
        itsApplication=app;
    }

    public void run(){
        itsApplication.init();
        while(!itsApplication.done()){
            itsApplication.idle();
        }
        itsApplication.cleanup();
    }
}
