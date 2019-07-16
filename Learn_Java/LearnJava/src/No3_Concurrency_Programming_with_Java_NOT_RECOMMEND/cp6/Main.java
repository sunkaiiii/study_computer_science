package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.basic.DataLoader;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.basic.Individual;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.parallel.ConcurrentGeneticAlgorithm;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.serial.SerialGeneticAlgorithm;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.Date;

public class Main {
    public static void main(String[] args) throws IOException {
        startSerialSearch();
        startParalleSearch();
    }

    private static void startSerialSearch() throws IOException {
        startSearch(((generations, individuals, distanceMatrix) -> new SerialGeneticAlgorithm(distanceMatrix, generations, individuals).calculate()));
    }

    private static void startParalleSearch() throws IOException {
        startSearch(((generations, individuals, distanceMatrix) -> new ConcurrentGeneticAlgorithm(distanceMatrix, generations, individuals).calculate()));
    }

    private static void startSearch(AlgorithmGenerator generator) throws IOException {
        Date start, end;
        int generations = 1000;
        int individuals = 1000;
        for (String name : new String[]{"lau15_dist", "kn57_dist"}) {
            int[][] distanceMatrix = DataLoader.load(Paths.get("data",
                    name + ".txt"));
            start = new Date();
            var result = generator.calculator(generations, individuals, distanceMatrix);
            end = new Date();
            System.out.println("=======================================");
            System.out.println("Example:" + name);
            System.out.println("Generations: " + generations);
            System.out.println("Population: " + individuals);
            System.out.println("Execution Time: " + (end.getTime() -
                    start.getTime()));
            System.out.println("Best Individual: " + result);
            System.out.println("Total Distance: " + result.getValue());
            System.out.println("=======================================");
        }
    }

    interface AlgorithmGenerator {
        Individual calculator(int generations, int individuals, int[][] distanceMatrix);
    }
}
