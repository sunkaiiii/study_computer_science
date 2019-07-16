package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.serial;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic.DocumentParser;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic.IndexingFunctions;

import java.io.File;
import java.util.*;

public class SerialIndex {
    public static void serialProcess() {
        Date start, end;
        File source = new File("data");
        File[] files = source.listFiles();
        Map<String, List<String>> invertedIndex = new
                HashMap<>();
        start = new Date();
        for (File file : files) {
            DocumentParser parser = new DocumentParser();
            if (file.getName().endsWith(".txt")) {
                Map<String, Integer> voc = parser.parse(file.getAbsolutePath());
                IndexingFunctions.updateInvertedIndex(voc, invertedIndex, file.getName());
            }
        }
        end = new Date();
        System.out.println("Execution Time: " + (end.getTime() -
                start.getTime()));
        System.out.println("invertedIndex: " + invertedIndex.size());
    }

}
