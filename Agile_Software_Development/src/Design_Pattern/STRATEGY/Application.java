package Design_Pattern.STRATEGY;

/**
 * Created by sunkai on 2017/11/8
 */
public interface Application {
    void init();
    void idle();
    void cleanup();
    boolean done();
}
