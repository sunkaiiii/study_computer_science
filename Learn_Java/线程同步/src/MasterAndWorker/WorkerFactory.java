package MasterAndWorker;

/**
 * Created by sunkai on 2017/12/20
 */

//创建工人的工厂类
public class WorkerFactory {
    public static BaseWorker dispatchWorker(Request request){
        BaseWorker worker=null;
        switch (request.requestType){
            case IMAGE:
                worker=new ImageWorker(request);
                break;
            case JSON:
                worker=new JsonWorker(request);
                break;
            case UPLOAD:
                worker=new UploadWorker(request);
                break;
            default:
                worker=new JsonWorker(request);
                break;
        }
        return worker;
    }
}
