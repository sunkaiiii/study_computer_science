package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp7.search.paralle;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp7.search.basic.CensusData;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp7.search.basic.Filter;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp7.search.basic.FilterData;

import java.util.List;
import java.util.concurrent.CancellationException;
import java.util.concurrent.RecursiveTask;

public class IndividualTask extends RecursiveTask<CensusData> {

    private CensusData[] data;
    private int start, end, size;
    private TaskManager manager;
    private List<FilterData> filters;

    public IndividualTask(CensusData[] data, int start, int end, TaskManager manager, int size, List<FilterData> filters) {
        this.data = data;
        this.start = start;
        this.end = end;
        this.manager = manager;
        this.size = size;
        this.filters = filters;
    }

    @Override
    protected CensusData compute() {
        if (end - start <= size) { //当小于既定的阈值时候，使用串形调用
            for (int i = start; i < end && !Thread.currentThread()
                    .isInterrupted(); i++) {
                CensusData censusData = data[i];
                if (Filter.filter(censusData, filters)) {
                    System.out.println("Found: " + i);
                    manager.cancelTasks(this);
                    return censusData;
                }
            }
            return null;
        } else {
            int mid = (start + end) / 2;
            IndividualTask task1 = new IndividualTask(data, start, mid, manager,
                    size, filters);
            IndividualTask task2 = new IndividualTask(data, mid, end, manager,
                    size, filters);
            manager.addTask(task1);
            manager.addTask(task2);
            manager.deleteTask(this);
            task1.fork();
            task2.fork(); //在看那本Java8实战的时候，讲ForkJoinPool的哪一节提到了，fork调用一次就好。比如task2就可以在当前线程上继续弄，这样可以节省一次内存切换的开销
            task1.quietlyJoin();
            task2.quietlyJoin();
            manager.deleteTask(task1);
            manager.deleteTask(task2);
            try {
                CensusData res = task1.join();
                if (res != null)
                    return res;
                manager.deleteTask(task1);
            } catch (CancellationException ex) {
            }
            try {
                CensusData res = task2.join();
                if (res != null)
                    return res;
                manager.deleteTask(task2);
            } catch (CancellationException ex) {
            }
            return null;
        }
    }
}
