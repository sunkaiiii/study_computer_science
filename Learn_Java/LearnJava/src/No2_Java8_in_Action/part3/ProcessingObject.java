package No2_Java8_in_Action.part3;

public abstract class ProcessingObject<T> {
    //责任链模式的传统写法
    protected  ProcessingObject<T> successor;

    public void setSuccessor(ProcessingObject<T> successor) {
        this.successor = successor;
    }

    public T handle(T input){
        T r=handleWork(input);
        if(successor!=null){
            return successor.handle(r);
        }
        return r;
    }
    abstract protected T handleWork(T input);
}
