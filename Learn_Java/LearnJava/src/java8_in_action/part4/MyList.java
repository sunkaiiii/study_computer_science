package java8_in_action.part4;

import java.util.function.Predicate;

public interface MyList<T> {
    T head();
    MyList<T> tail();
    default MyList<T> filter(Predicate<T> p){
        return null;
    }
    default boolean isEmpty(){
        return true;
    }
}
