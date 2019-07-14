package No2_Java8_in_Action.part4;

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
