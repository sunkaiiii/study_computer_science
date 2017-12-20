package MasterAndWorker;

/**
 * Created by sunkai on 2017/12/20
 */
public interface LoadListener {
    void onSuccess(Response response);
    void onFail(Request request);
}
