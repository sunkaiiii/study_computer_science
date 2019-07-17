package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp4;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.LinkedBlockingQueue;

public class NewsBuffer {
    private LinkedBlockingQueue<CommonInformationItem> buffer;
    private ConcurrentHashMap<String, String> storedItems;

    public NewsBuffer() {
        buffer = new LinkedBlockingQueue<>();
        storedItems = new ConcurrentHashMap<>();
    }

    public void add(CommonInformationItem item) {
        storedItems.compute(item.getId(), (id, oldSource) -> {
            if (oldSource == null) {
                buffer.add(item);
                return item.getSource();
            } else {
                System.out.println("Item " + item.getId() + " has been processed before");
                return oldSource;
            }
        });
    }

    public CommonInformationItem get() throws InterruptedException {
        return buffer.take();
    }
}
