package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic;

import java.util.Map;

public class Document {

    private String fileName;
    private Map<String, Integer> voc;
    public String getFileName() {
        return fileName;
    }
    public void setFileName(String fileName) {
        this.fileName = fileName;
    }
    public Map<String, Integer> getVoc() {
        return voc;
    }
    public void setVoc(Map<String, Integer> voc) {
        this.voc = voc;
    }


}