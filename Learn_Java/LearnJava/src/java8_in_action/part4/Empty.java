package java8_in_action.part4;

import java.util.function.Predicate;

public class Empty<T> implements MyList<T> {
    public T head(){
        throw  new UnsupportedOperationException();
    }

    public MyList<T> tail(){
        throw new UnsupportedOperationException();
    }

}
