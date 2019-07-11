package java8_in_action.part4;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.LongStream;

public class Main {

    private static List<List<Integer>> subsets(List<Integer> list) {
        if (list.isEmpty()) {
            List<List<Integer>> ans = new ArrayList<>();
            ans.add(Collections.emptyList());
            return ans;
        }
        var first = list.get(0);
        var rest = list.subList(1, list.size());
        var subans = subsets(rest);
        var subans2 = insertAll(first, subans);
        return concat(subans, subans2);
    }

    //函数式的方法
    //合并并返回一个新的对象
    private static List<List<Integer>> concat(List<List<Integer>> subans, List<List<Integer>> subans2) {
        List<List<Integer>> r = new ArrayList<>(subans);
        r.addAll(subans2);
        return r;
    }

    //函数式的方法
    //没有改变原始对象
    private static List<List<Integer>> insertAll(Integer first, List<List<Integer>> subans) {
        List<List<Integer>> result = new ArrayList<>();
        for (List<Integer> list : subans) {
            List<Integer> copyList = new ArrayList<>();
            copyList.add(first);
            copyList.addAll(list);
            result.add(copyList);
        }
        return result;
    }

    //迭代式阶乘计算
    private static int factorialIterative(int n) {
        int r = 1;
        for (int i = 1; i <= n; i++) {
            r *= i;
        }
        return r;
    }

    //递归式的阶乘计算
    private static long factorialRecursive(long n) {
        return n == 1 ? 1 : n * factorialRecursive(n - 1);
    }

    //基于Stream的阶乘
    private static long factorialStream(long n){
        return LongStream.rangeClosed(1,n).reduce(1,(a,b)->a*b);
    }

    private static long factorialTailRecursive(long n){
        return factorialHelper(1,n);
    }

    private static long factorialHelper(long i, long n) {
        return n==1?i:factorialHelper(i*n,n-1);
    }

    public static void main(String[] args) {
        //开始尝试第一个函数式编程的例子
        System.out.println(subsets(Arrays.asList(1, 2, 4)));
        System.out.println(factorialIterative(20));
        System.out.println(factorialRecursive(20));
        System.out.println(factorialStream(20));
        System.out.println(factorialTailRecursive(20));
    }

}
