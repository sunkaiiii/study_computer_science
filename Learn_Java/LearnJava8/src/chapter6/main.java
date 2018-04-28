package chapter6;

import Entity.Album;
import Entity.Artist;
import Entity.Track;

import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.IntStream;

/**
 * Created by sunkai on 2017/12/11
 */
public class main {
    public static void main(String args[]){
        double a[]=parallelInitialize(100);
        for(int i=0;i<a.length;i++){
            System.out.println(a[i]);
        }
    }

    //串行化计算曲目长度
    public int serialArraySum(List<Album> albums){
        return albums.stream().flatMap(Album::getTrakcs).mapToInt(Track::getLength).sum();
    }

    //并行化计算曲目长度
    public int parallelArraySum(List<Album> albums){
        return albums.parallelStream().flatMap(Album::getTrakcs).mapToInt(Track::getLength).sum();
    }

    //使用并行化数组操作初始化数组
    public static double[] parallelInitialize(int size){
        double[] values=new double[size];
        Arrays.parallelSetAll(values,i->i); //数组的下标和元素值是一样的
        return values;
    }

    //计算简单滑动平均数
    public static double[] simpleMovingAverage(double[] values,int n){
        double[] sums=Arrays.copyOf(values,values.length);
        Arrays.parallelPrefix(sums,Double::sum); //parallelPrefix对序列做累加，他会更新数组，将每一个元素替换为当前元素和前驱元素的和
        int start=n-1;
        return IntStream.range(start,sums.length).mapToDouble(i->{
            double prefix=i==start?0:sums[i-n];
            return (sums[i]-prefix)/n;
        }).toArray();
    }

    //将顺序求列表中数字的平方和改为并行
    public static int sequentialSumOfSquares(IntStream range){
//        顺序执行的
//        return range.map(x->x*x).sum();
        //并行执行的
        return range.parallel().map(x->x*x).sum();
    }

    //把列表中的数字相乘，然后再将所得结果乘以 5，该实现有一个缺陷
    public static int multiplyThrough(List<Integer> linkedListOfNumbers) {
//        有问题的
//        return linkedListOfNumbers.stream().reduce(5, (acc, x) -> x * acc);
        //修改的
        return 5*linkedListOfNumbers.stream().reduce(1,(acc,x)->x*acc);
    }

//    求列表元素的平方和，原始方式性能不高
    public int slowSumOfSquares(List<Integer> linkedListOfNumbers){
//        原始方式
//        return linkedListOfNumbers.parallelStream().map(x->x*x).reduce(0,(acc,x)->acc+x);

        //高效率方式，mapToInt会返回一个IntStream对象，其中包含的各种操作效率较高
        return linkedListOfNumbers.parallelStream().mapToInt(x->x*x).sum();
    }

}
