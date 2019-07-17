package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.parallel;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic.Document;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic.IndexingFunctions;

import java.util.List;
import java.util.concurrent.*;

public class MultipleInvertedIndexTask implements Runnable {
    CompletionService<List<Document>> completionService;
    private ConcurrentHashMap<String,
            ConcurrentLinkedDeque<String>> invertedIndex; //根据字符串返回一个存放文件名字符串的ConcurrentLinkedDeque

    public MultipleInvertedIndexTask(CompletionService<List<Document>>
                                             completionService, ConcurrentHashMap<String,
            ConcurrentLinkedDeque<String>> invertedIndex) {
        this.completionService = completionService;
        this.invertedIndex = invertedIndex;
    }

    @Override
    public void run() {
        try {
            while (!Thread.interrupted()) {
                try {
                    List<Document> documents = completionService.take().get();
                    for (Document document : documents) {
                        IndexingFunctions.updateInvertedIndex(document.getVoc(), invertedIndex,
                                document.getFileName());
                    }
                } catch (InterruptedException e) {
                    break;
                }
            }
            while (true) {
                Future<List<Document>> future = completionService.poll();
                if (future == null)
                    break;
                List<Document> documents = future.get();
                for (Document document : documents) {
                    IndexingFunctions.updateInvertedIndex(document.getVoc(), invertedIndex,
                            document.getFileName());
                }
            }
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }
}
