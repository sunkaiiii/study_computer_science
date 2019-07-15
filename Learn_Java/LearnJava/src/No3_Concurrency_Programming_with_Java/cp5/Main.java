package No3_Concurrency_Programming_with_Java.cp5;

import No3_Concurrency_Programming_with_Java.cp5.serial.BestMatchingSerialCalculation;

import java.util.Date;

public class Main {
    public static void main(String[] args) {
        testSerial();
    }

    private static void testSerial() {
        Date startTime, endTime;
        var dictionary = WordsLoader.load("data/UK Advanced Cryptics Dictionary.txt");
        System.out.println("Dictionary Size: " + dictionary.size());
        startTime = new Date();
        var result = BestMatchingSerialCalculation.getBestMatchingWords("syzygies", dictionary);
        var results = result.getWords();
        endTime = new Date();
        System.out.println("Word:syzygies");
        System.out.println("Minum distance: " + result.getDistance());
        System.out.println("List of best matching words:" + results.size());
        results.forEach(System.out::println);
        System.out.println("Execution Time: " + (endTime.getTime() -
                startTime.getTime()));
    }
}
