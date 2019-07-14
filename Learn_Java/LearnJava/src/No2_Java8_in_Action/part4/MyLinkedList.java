package No2_Java8_in_Action.part4;

public class MyLinkedList<T> implements MyList<T> {
    private final T head;
    private final MyList<T> tail;
    public MyLinkedList(T head, MyList<T> tail){
        this.head=head;
        this.tail=tail;
    }

    public T head(){
        return head;
    }

    public MyList<T> tail(){
        return tail;
    }


    @Override
    public boolean isEmpty() {
        return false;
    }
}
