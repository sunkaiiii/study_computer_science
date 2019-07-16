package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.parallel;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic.Document;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic.DocumentParser;

import java.io.File;
import java.util.Map;
import java.util.concurrent.Callable;

public class IndexingTask implements Callable<Document> {
    //解析一个文档的任务
    private File file;

    public IndexingTask(File file) {
        this.file = file;
    }

    @Override
    public Document call() throws Exception {
        DocumentParser parser = new DocumentParser();
        Map<String, Integer> voc = parser.parse(file.getAbsolutePath());
        Document document = new Document();
        document.setFileName(file.getName());
        document.setVoc(voc);
        return document;
    }
}
