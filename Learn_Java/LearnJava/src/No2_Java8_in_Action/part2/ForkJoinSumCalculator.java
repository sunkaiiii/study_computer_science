package No2_Java8_in_Action.part2;

import java.util.concurrent.RecursiveTask;

public class ForkJoinSumCalculator extends RecursiveTask<Long> {
    private final long[] numbers;
    private final int start;
    private final int end;

    public static final long THRESHOLD=10_000; //不再将任务分解为子任务的数组大小

    public ForkJoinSumCalculator(long[] numbers){
        this(numbers,0,numbers.length);
    }

    public ForkJoinSumCalculator(long[] numbers, int i, int length) {
        this.numbers=numbers;
        this.start=i;
        this.end=length;
    }

    @Override
    protected Long compute() {
        int length=end-start;
        if(length<=THRESHOLD){
            return computeSequentially();
        }
        var leftTask=new ForkJoinSumCalculator(numbers,start,start+length/2);
        var rightTask=new ForkJoinSumCalculator(numbers,start+length/2,end);
        leftTask.fork(); //创建一个子任务来为数组的前一半求和，利用另一个ForkJoinPool线程异步执行新创建的任务
        long rightResult=rightTask.compute(); //同步执行第二个子任务，有可能允许进一步的递归划分
        long leftResult=leftTask.join();
        return leftResult+rightResult;
    }

    private long computeSequentially(){
        long sum=0;
        for(int i=start;i<end;i++){
            sum+=numbers[i];
        }
        return sum;
    }
}
