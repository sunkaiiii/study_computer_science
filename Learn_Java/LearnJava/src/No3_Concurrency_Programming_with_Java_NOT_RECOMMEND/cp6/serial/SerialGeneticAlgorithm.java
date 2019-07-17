package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.serial;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.basic.GeneticOperators;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.basic.Individual;

public class SerialGeneticAlgorithm {
    private int[][] distanceMatrix;

    private int numberOfGenerations;
    private int numberOfIndividuals;

    private int size;

    public SerialGeneticAlgorithm(int[][] distanceMatrix,
                                  int numberOfGenerations, int numberOfIndividuals) {
        this.distanceMatrix = distanceMatrix;
        this.numberOfGenerations = numberOfGenerations;
        this.numberOfIndividuals = numberOfIndividuals;
        size = distanceMatrix.length;
    }

    public Individual calculate() {
        //首先初始化，然后，评估初始种群来创建初始种族
        //然后评估种群取其最优个体作为算法的一个解
        Individual best;

        Individual[] population = GeneticOperators.initialize(
                numberOfIndividuals, size);
        GeneticOperators.evaluate(population, distanceMatrix);

        best = population[0]; //因为是经过排序的了，所以0号就是最优的那个。

        //开始交叉
        for (int i = 1; i <= numberOfGenerations; i++) {
            Individual[] selected = GeneticOperators.selection(population);
            population = GeneticOperators.crossover(selected,
                    numberOfIndividuals, size);
            GeneticOperators.evaluate(population, distanceMatrix); //如果新的要优于目前为止最好的个体，则替换。
            if (population[0].getValue() < best.getValue()) {
                best = population[0];
            }
        }

        return best;
    }
}
