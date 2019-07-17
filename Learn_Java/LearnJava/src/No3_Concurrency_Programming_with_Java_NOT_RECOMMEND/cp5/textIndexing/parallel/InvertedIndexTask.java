package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.parallel;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic.Document;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic.IndexingFunctions;

import java.util.concurrent.*;

public class InvertedIndexTask implements Runnable {
    //获取由IndexingTask对象生成的Document对象。
    //并创建倒排索引。
    CompletionService<Document> completionService;
    private ConcurrentHashMap<String,
            ConcurrentLinkedDeque<String>> invertedIndex; //根据字符串返回一个存放文件名字符串的ConcurrentLinkedDeque

    public InvertedIndexTask(CompletionService<Document>
                                     completionService, ConcurrentHashMap<String,
            ConcurrentLinkedDeque<String>> invertedIndex) {
        this.completionService = completionService;
        this.invertedIndex = invertedIndex;
    }

    @Override
    public void run() {
        try {
            //通过take方法获取某一任务相关联的Future
            //在线程中断之前该循环一直运行
            //在线程中断之后，再次使用poll方法处理所有的future对象。
            while (!Thread.interrupted()) {
                try {
                    Document document = completionService.take().get();
                    IndexingFunctions.updateInvertedIndex(document.getVoc(), invertedIndex,
                            document.getFileName());
                } catch (InterruptedException e) {
                    break;
                }
            }
            while (true) {
                Future<Document> future = completionService.poll();
                if (future == null)
                    break;
                Document document = future.get();
                IndexingFunctions.updateInvertedIndex(document.getVoc(), invertedIndex,
                        document.getFileName());
            }
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }
}
