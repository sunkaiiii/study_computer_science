package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.find_string;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.find_string.basic.BestMatchingData;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.find_string.basic.WordsLoader;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.find_string.paralle.BestMatchingAdvancedConcurrentCalculation;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.find_string.paralle.BestMatchingBasicConcurrentCalculation;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.find_string.serial.BestMatchingSerialCalculation;

import java.util.Date;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.function.Function;

public class Main {
    public static void main(String[] args) {
        testSerial();
        testParallelVersion1();
        testParallelVersion2();
    }


    private static void testSerial() {
        startTest((dictionary) -> BestMatchingSerialCalculation.getBestMatchingWords("syzygies", dictionary));
    }


    private static void testParallelVersion1() {
        startTest((dictionary) -> {
            try {
                return BestMatchingBasicConcurrentCalculation.getBestMatchingWords("systematic", dictionary);
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
            return null;
        });
    }

    private static void testParallelVersion2() {
        startTest((dictionary) -> {
            try {
                return BestMatchingAdvancedConcurrentCalculation.getBestMatchingWords("systematic", dictionary);
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
            return null;
        });
    }

    private static void startTest(Function<List<String>, BestMatchingData> function) {
        Date startTime, endTime;
        var dictionary = WordsLoader.load("data/UK Advanced Cryptics Dictionary.txt");
        System.out.println("Dictionary Size: " + dictionary.size());
        startTime = new Date();
        var result = function.apply(dictionary);
        var results = result.getWords();
        endTime = new Date();
        System.out.println("Word:syzygies");
        System.out.println("Minum distance: " + result.getDistance());
        System.out.println("List of best matching words:" + results.size());
        results.forEach(s -> System.out.print(s + ", "));
        System.out.println();
        System.out.println("Execution Time: " + (endTime.getTime() -
                startTime.getTime()));
    }
}
