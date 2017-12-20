package MasterAndWorker;

/**
 * Created by sunkai on 2017/12/20
 */
public class Request {
    public RequestType requestType;
    public String url;
    public Object data;

    enum RequestType{
        JSON,UPLOAD,IMAGE
    }

    @Override
    public String toString() {
        return  "Request [requestorType=" + requestType + ", url=" + url
                + ", data=" + data + "]";
    }
}
