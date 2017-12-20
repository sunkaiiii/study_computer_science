package MasterAndWorker;

/**
 * Created by sunkai on 2017/12/20
 */
public class ImageWorker extends BaseWorker {
    public ImageWorker(Request request){
        super(request);
    }

    @Override
    protected Response doTask() throws Exception {
        Thread.sleep(1500);
        Response response=new Response();
        response.request=request;
        response.result="下载图片的接口";
        return response;
    }
}
