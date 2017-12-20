package MasterAndWorker;

/**
 * Created by sunkai on 2017/12/20
 */
public class Response {
    public Request request;
    public Object result;

    @Override
    public String toString() {
            return "Response [request=" + request + ", result=" + result + "]";
    }
}
