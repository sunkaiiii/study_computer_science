package MasterAndWorker;

/**
 * Created by sunkai on 2017/12/20
 */
public class UploadWorker extends BaseWorker {
    public UploadWorker(Request request){
        super(request);
    }

    @Override
    protected Response doTask() throws Exception {
        Thread.sleep(3000);
        Response response=new Response();
        response.request=request;
        response.result="上传数据的接口";
        return response;
    }
}
