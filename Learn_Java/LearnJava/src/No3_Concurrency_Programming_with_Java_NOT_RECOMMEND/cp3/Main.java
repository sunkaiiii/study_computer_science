package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.model.BankMarketing;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.model.Sample;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.paralle.KnnClassfier;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.paralle.KnnClassifierParallelGroup;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.paralle.KnnClassifierParallelIndividual;

import java.util.Date;
import java.util.List;
import java.util.function.BiFunction;

public class Main {

    public static void main(String[] args) {
        //这本书在书上给的代码是不全的
        //每次都得从他的GitHub上的项目拷贝代码
        //然后粘贴过来之后编译器还要提示很多警告
        //第二个用例并发服务器我决定不弄了
        //第一个用例的聚类算法也进行了一些简单的修改
        testSerial(args);
        testParallelIndividual(args);
        testParallelGroup(args);
    }

    private static void testParallelGroup(String[] args) {
        startTest(args, (list, k) -> new KnnClassifierParallelGroup(list, k, 1, true), "Parallel Classifier Group - K: ");
    }

    private static void testParallelIndividual(String[] args) {
        startTest(args, (list, k) -> new KnnClassifierParallelIndividual(list, k, 1, true), "Parallel Classifier Individual - K: ");
    }

    private static void testSerial(String[] args) {
        startTest(args, KnnClassfier::new, "SerialClassifier - K: ");
    }


    private static void startTest(String[] args, BiFunction<List<? extends Sample>, Integer, Classifier> function, String testName) {
        Loader loader = new Loader();
        List<BankMarketing> train = loader.load("src/No3_Concurrency_Programming_with_Java/cp3/knn/data/bank.data");
        System.out.println("Train: " + train.size());
        List<BankMarketing> test = loader.load("src/No3_Concurrency_Programming_with_Java/cp3/knn/data/bank.test");
        System.out.println("Test: " + test.size());
        double currentTime = 0d;
        int success = 0, mistakes = 0;

        int k = 10;
        if (args.length == 1) {
            k = Integer.parseInt(args[0]);
        }
        var classier = function.apply(train, k);
        try {
            Date start, end;
            start = new Date();
            for (BankMarketing example : test) {
                String tag = classier.classify(example);
                if (tag.equals(example.getTag())) {
                    success++;
                } else {
                    mistakes++;
                }
            }
            end = new Date();
            currentTime = end.getTime() - start.getTime();
        } catch (Exception e) {
            e.printStackTrace();
        }
        classier.destroy();
        showResult(currentTime, success, mistakes, k, testName);
    }

    private static void showResult(double currentTime, int success, int mistakes, int k, String s) {
        System.out.println("******************************************");
        System.out.println(s + k );
        System.out.println("Success: " + success);
        System.out.println("Mistakes: " + mistakes);
        System.out.println("Execution Time: " + (currentTime / 1000) + " seconds.");
        System.out.println("******************************************");
    }
}
