package No2_Java8_in_Action.part4;

import java.util.function.Predicate;
import java.util.function.Supplier;

public class LazyList<T> implements MyList<T> {
    final T head;
    final Supplier<MyList<T>> tail;

    public LazyList(T head, Supplier<MyList<T>> tail) {
        this.head = head;
        this.tail = tail;
    }

    @Override
    public T head() {
        return head;
    }

    @Override
    public MyList<T> tail() {
        //在这个List当中，调用get方法会触发延迟列表的节点创建。
        return tail.get();
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    public static LazyList<Integer> from(int n) {
        return new LazyList<>(n, () -> from(n + 1));
    }

    //现在已经懂得了延迟生成数字
    //再看看延迟生成质数
    public static MyList<Integer> primes(MyList<Integer> numbers) {
        return new LazyList<>(
                numbers.head(), () -> primes(
                numbers.tail().filter(n -> n % numbers.head() != 0)
        )
        );
    }

    //在这里需要一个延迟加载器
    public MyList<T> filter(Predicate<T> p) {
        return isEmpty() ? this :
                p.test(head()) ?
                        new LazyList<>(head(), () -> tail().filter(p)) : //每次迭代都向下求值。找到符合条件的那个tail。如果不符合，则执行方法
                        tail().filter(p);
    }
}
