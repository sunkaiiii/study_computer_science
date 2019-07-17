package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedDeque;

public class IndexingFunctions {
    public static void updateInvertedIndex(Map<String, Integer> voc,
                                           Map<String, List<String>> invertedIndex, String fileName) {
        for (String word : voc.keySet()) {
            if (word.length() >= 3) {
                invertedIndex.computeIfAbsent(word, k -> new
                        ArrayList<>()).add(fileName);
            }
        }
    }

    public static void updateInvertedIndex(Map<String, Integer> voc,
                                     ConcurrentHashMap<String, ConcurrentLinkedDeque<String>>
                                             invertedIndex, String fileName) {
        for (String word : voc.keySet()) {
            if (word.length() >= 3) {
                invertedIndex.computeIfAbsent(word, k -> new
                        ConcurrentLinkedDeque<>()).add(fileName);
            }

        }
    }
}
