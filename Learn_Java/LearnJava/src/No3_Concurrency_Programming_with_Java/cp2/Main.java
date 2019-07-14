package No3_Concurrency_Programming_with_Java.cp2;

import java.io.File;
import java.util.Date;

public class Main {

    public static void main(String[] args) {
        var matrix1 = MatrixGenerator.generate(400, 400);
        var matrix2 = MatrixGenerator.generate(400, 400);
        var resultSerial = new double[matrix1.length][matrix2[0].length];
        Date start = new Date();
        SerialMultiplier.multiply(matrix1, matrix2, resultSerial);
        Date end = new Date();
        System.out.printf("Serial: %d%n", end.getTime() - start.getTime());

        var resultParalle = new double[matrix1.length][matrix2[0].length];
        start = new Date();
        ParallelIndividualMultiplier.multiply(matrix1, matrix2, resultParalle);
        end = new Date();
        System.out.printf("Parallel 1: %d%n", end.getTime() - start.getTime());

        var resultParalle2 = new double[matrix1.length][matrix2[0].length];
        start = new Date();
        ParallelRowMultiplier.multiply(matrix1, matrix2, resultParalle2);
        end = new Date();
        System.out.printf("Parallel 2: %d%n", end.getTime() - start.getTime());

        var resultParalle3 = new double[matrix1.length][matrix2[0].length];
        start = new Date();
        ParallelGroupMultiplier.multiply(matrix1, matrix2, resultParalle3);
        end = new Date();
        System.out.printf("Parallel 3: %d%n", end.getTime() - start.getTime());

        var fileName = "20190417_060721000_iOS.jpg";
        var file = new File("/");
        var result = new Result();
        start = new Date();
        SerialFileSearch.searchFiles(file, fileName, result);
        end = new Date();
        System.out.printf("Serial Search: %d%n", end.getTime() - start.getTime());

        start = new Date();
        ParallelGroupFileSearch.searchFiles(file, fileName, result);
        end = new Date();
        System.out.printf("Parallel Search: %d%n", end.getTime() - start.getTime());
    }
}
