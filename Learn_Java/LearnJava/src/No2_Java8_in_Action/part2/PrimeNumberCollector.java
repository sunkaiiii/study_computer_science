package No2_Java8_in_Action.part2;

import java.util.*;
import java.util.function.*;
import java.util.stream.Collector;

public class PrimeNumberCollector implements Collector<Integer, Map<Boolean,List<Integer>>,Map<Boolean, List<Integer>>> {
    @Override
    public Supplier<Map<Boolean, List<Integer>>> supplier() {
        return ()->new HashMap<>(){{
            put(true,new ArrayList<>());
            put(false,new ArrayList<>());
        }};
    }

    @Override
    public BiConsumer<Map<Boolean, List<Integer>>, Integer> accumulator() {
        //每一次累加都会把当前数字放入质数/非质数的列表
        return (acc,candidate)->{
            acc.get(isPrime(acc.get(true),candidate)).add(candidate);
        };
    }
    //找到与被测数字的平方根最接近的质数列表，去检验被除数。
    private boolean isPrime(List<Integer> primes, int candidate) {
        int candidateRoot = (int) Math.sqrt(candidate);
        return takewhile(primes, i -> i <= candidateRoot).stream().noneMatch(p -> candidate % p == 0);
    }

    //这里传入的是一个以求出的质数的列表
    private <A> List<A> takewhile(List<A> list, Predicate<A> p) {
        int i = 0;
        for (A item : list) {
            if (!p.test(item)) {
                return list.subList(0, i);
            }
            i++;
        }
        return list;
    }

    @Override
    public BinaryOperator<Map<Boolean, List<Integer>>> combiner() throws UnsupportedOperationException {
        //因为该算法本身是顺序的，所以不可能并行使用。
        //最好的办法就是抛出一个异常。
//        throw  new UnsupportedOperationException();
        return (map1,map2)->{
            map1.get(true).addAll(map2.get(true));
            map1.get(false).addAll(map2.get(false));
            return map1;
        };
    }

    @Override
    public Function<Map<Boolean, List<Integer>>, Map<Boolean, List<Integer>>> finisher() {
        return Function.identity();
    }

    @Override
    public Set<Characteristics> characteristics() {
        return Collections.unmodifiableSet(EnumSet.of(Characteristics.IDENTITY_FINISH));
    }
}
