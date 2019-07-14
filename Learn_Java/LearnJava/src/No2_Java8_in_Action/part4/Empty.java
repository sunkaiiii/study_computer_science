package No2_Java8_in_Action.part4;

public class Empty<T> implements MyList<T> {
    public T head(){
        throw  new UnsupportedOperationException();
    }

    public MyList<T> tail(){
        throw new UnsupportedOperationException();
    }

}
