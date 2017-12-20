package MasterAndWorker;

import java.util.HashMap;
import java.util.concurrent.*;

/**
 * Created by sunkai on 2017/12/20
 * 充当了一个master的角色，用于分配任务
 */
public class ExecutorLoader {
    //创建线程池
    private static final int CPU_COUNT=Runtime.getRuntime().availableProcessors();
    private static final int CORE_POLL_SIZE=4;
    private static final int MAXIMUM_POOL_SIZE=CPU_COUNT+1;
    private static final int KEEP_ALIVE_TIME=30;
    private static final LinkedBlockingDeque<Runnable> QUEUE=new LinkedBlockingDeque<>(128);
    private static final ThreadFactory THREAD_FACTORY=new ThreadFactory() {
        @Override
        public Thread newThread(Runnable r) {
            return new Thread(r);
        }
    };
    private static final ThreadPoolExecutor THREAD_POOL_EXECUTOR;
    private static final HashMap<String,Request> TASKS=new HashMap<>();

    static {
        ThreadPoolExecutor threadPoolExecutor=new ThreadPoolExecutor(CORE_POLL_SIZE,MAXIMUM_POOL_SIZE,KEEP_ALIVE_TIME, TimeUnit.SECONDS,QUEUE,THREAD_FACTORY);
        THREAD_POOL_EXECUTOR=threadPoolExecutor;
    }
    private Status status=Status.CREATE;

    //分配任务
    public synchronized void execute(final Request request,final LoadListener listener){
        if(status!=Status.CREATE){
            throw  new RuntimeException("status error");
        }

        status=Status.WORKING; //处理任务状态
        if(request==null)
            return;
        if(TASKS.get(request.url)!=null) //对于重复的任务，予以忽略
            return;
        TASKS.put(request.url,request);

        //将任务托付给Futer，Futer会将得到并持有返回值，他也实现了Runable
        FutureTask<Response> futureTask=new FutureTask<>(WorkerFactory.dispatchWorker(request)){
            @Override
            protected void done() { //当任务完成之后，会执行这个回调方法
                try{
                    Response response=get(); //通过get，就可以获得任务执行之后的返回值（包含在BaseWorker当中callable方法当中的返回值）
                    if(response!=null){
                        if(listener!=null){
                            listener.onSuccess(response);
                        }else{
                            listener.onFail(request);
                        }
                    }
                }catch (ExecutionException|InterruptedException e){
                    e.printStackTrace();
                }finally {
                    TASKS.remove(request.url);
                    status=Status.FINISH; //将状态置为完成
                }
            }
        };
        THREAD_POOL_EXECUTOR.execute(futureTask);
    }

    enum Status{
        CREATE,WORKING,FINISH
    }

}
