package MasterAndWorker;

/**
 * Created by sunkai on 2017/12/20
 */
public class MasterWorkerTest {
    static LoadListener listener=new LoadListener() {
        @Override
        public void onSuccess(Response response) {
            System.out.println(response);
        }

        @Override
        public void onFail(Request request) {
            System.out.println(request);
        }
    };

    public static void main(String[] args){
        Request request1=new Request();
        request1.requestType= Request.RequestType.IMAGE;
        request1.url="aaa";
        request1.data="图片请求";

        Request request2=new Request();
        request2.requestType= Request.RequestType.JSON;
        request2.url="bbb";
        request2.data="Json请求";

        Request request3=new Request();
        request3.requestType= Request.RequestType.UPLOAD;
        request3.url="ccc";
        request3.data="上传请求";

        new ExecutorLoader().execute(request1,listener);
        new ExecutorLoader().execute(request2,listener);
        new ExecutorLoader().execute(request3,listener);
    }
}
