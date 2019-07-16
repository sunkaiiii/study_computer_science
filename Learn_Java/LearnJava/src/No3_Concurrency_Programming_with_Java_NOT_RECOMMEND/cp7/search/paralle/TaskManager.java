package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp7.search.paralle;

import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.atomic.AtomicBoolean;

public class TaskManager {
    //此类用来控制任务的撤销。
    //包括fidnAny找到了满足的对象
    //或者findAny或findAll在某个任务中出现了未校验异常

    private Set<RecursiveTask> tasks;
    private AtomicBoolean cancelled;

    public TaskManager(){
        tasks=ConcurrentHashMap.newKeySet();
        cancelled=new AtomicBoolean(false);
    }
    public void addTask(RecursiveTask task){
        tasks.add(task);
    }

    public void cancelTasks(RecursiveTask sourceTask){
        if(cancelled.compareAndSet(false,true)){
            for(RecursiveTask task:tasks){
                if(task!=sourceTask){
                    if(cancelled.get()){
                        task.cancel(true);
                    }else{
                        tasks.add(task);
                    }
                }
            }
        }
    }
    public void deleteTask(RecursiveTask task){
        tasks.remove(task);
    }

}
