package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp4;

import java.util.Date;
import java.util.List;

public class NewsTask implements Runnable {
    public String getName() {
        return name;
    }

    //周期方法的执行任务
    private String name;
    private String url;
    private NewsBuffer buffer;

    public NewsTask(String name, String url, NewsBuffer buffer) {
        this.name = name;
        this.url = url;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        System.out.println(name + " :Running. " + new Date());
        RSSDataCapture capture = new RSSDataCapture(name);
        List<CommonInformationItem> items = capture.load(url);

        //获取到信息之后，就放入队列存到硬盘当中
        for (CommonInformationItem item : items) {
            buffer.add(item);
        }
    }
}
