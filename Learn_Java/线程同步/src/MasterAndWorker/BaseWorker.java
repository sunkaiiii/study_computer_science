package MasterAndWorker;

import java.util.concurrent.Callable;

/**
 * Created by sunkai on 2017/12/20
 */
public abstract class BaseWorker implements Callable<Response> {
    protected Request request;
    public BaseWorker(Request request){
        this.request=request;
    }

    @Override
    public Response call() throws Exception { //实现Callable的接口
        if(request.data==null)
            return null;
        return doTask();
    }

    //所有的worker都要实现对应的方法
    protected abstract Response doTask() throws Exception;
}
