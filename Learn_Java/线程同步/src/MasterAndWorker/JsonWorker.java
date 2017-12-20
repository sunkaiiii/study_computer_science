package MasterAndWorker;

/**
 * Created by sunkai on 2017/12/20
 */
public class JsonWorker extends BaseWorker {
    public JsonWorker(Request request){
        super(request);
    }

    @Override
    protected Response doTask() throws Exception {
        Thread.sleep(500);
        Response response=new Response();
        response.request=request;
        response.result="处理Json的接口";
        return response;
    }
}
