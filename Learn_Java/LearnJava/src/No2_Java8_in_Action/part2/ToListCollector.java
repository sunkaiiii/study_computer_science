package No2_Java8_in_Action.part2;

import java.util.*;
import java.util.function.BiConsumer;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.stream.Collector;

public class ToListCollector<T> implements Collector<T,List<T>, List<T>> {
    //建立新的结果容器。创建一个空的累加器
    @Override
    public Supplier<List<T>> supplier() {
        return ArrayList::new;
    }

    //将元素添加到结果累加器
    @Override
    public BiConsumer<List<T>, T> accumulator() {
        return List::add;
    }

    //在遍历完成后最后要执行的方法
    @Override
    public Function<List<T>, List<T>> finisher() {
        return Function.identity();
    }

    //定义了规约操作。对各个流的子部分进行并行处理的时候，如何合并。
    @Override
    public BinaryOperator<List<T>> combiner() {
        return (list1,list2)->{
            list1.addAll(list2);
            return list1;
        };
    }

//    收集器的行为
    @Override
    public Set<Characteristics> characteristics() {
        return Collections.unmodifiableSet(EnumSet.of(Characteristics.IDENTITY_FINISH,Characteristics.CONCURRENT));
    }
}
