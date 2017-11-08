package Design_Pattern.TEMPLATE_METHOD;

/**
 * Created by sunkai on 2017/11/8
 */
public abstract class Application {
    private boolean isDone=false;
    protected abstract void init();
    protected abstract void idel();
    protected abstract void cleanup();

    protected void setDone(){
        isDone=true;
    }

    protected boolean done(){
        return isDone;
    }

    public void run(){
        init();
        while(!done()){
            idel();
        }
        cleanup();
    }
}
