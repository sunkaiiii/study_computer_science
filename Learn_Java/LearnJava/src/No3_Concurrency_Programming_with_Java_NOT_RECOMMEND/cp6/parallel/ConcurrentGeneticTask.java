package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.parallel;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.basic.GeneticOperators;

import java.util.Random;

public class ConcurrentGeneticTask implements Runnable {
    //写作执行遗传算法的任务
    private GeneticPhaser phaser;
    private SharedData data;
    private int numberOfGenerations;
    private boolean main;

    public ConcurrentGeneticTask(GeneticPhaser phaser, int
            numberOfGenerations, boolean main) {
        this.phaser = phaser;
        this.numberOfGenerations = numberOfGenerations;
        this.main = main;
        this.data = phaser.getData();
    }

    @Override
    public void run() {
        //这部分实现算法逻辑
        //它有一个生成指定代的循环
        //其他任务将使用arriveAndAwaitAdvance方法等待结束
        //我感觉用CompletableFuture更合适……
        Random rm = new Random(System.nanoTime());
        for (int i = 0; i < numberOfGenerations; i++) {
            if (main) {
                data.setSelected(GeneticOperators.selection(data
                        .getPopulation()));
            }
            phaser.arriveAndAwaitAdvance();
            //第二阶段是交叉阶段，使用SharedData类中存放的AtomicInteger变量索引获得种群数中的下一个位置
            //交叉生成两个新变体，因此要在种群数组中保留这两个位置
            int individualIndex;
            do {
                individualIndex = data.getIndex().getAndAdd(2);
                if (individualIndex < data.getPopulation().length) {
                    int secondIndividual = individualIndex++;
                    int p1Index = rm.nextInt(data.getSelected().length);
                    int p2Index;
                    do {
                        p2Index = rm.nextInt(data.getSelected().length);
                    } while (p1Index == p2Index);

                    var parent1 = data.getSelected()[p1Index];
                    var parent2 = data.getSelected()[p2Index];
                    var individual1 = data.getPopulation()[individualIndex];
                    var individual2 = data.getPopulation()[secondIndividual];
                    GeneticOperators.crossover(parent1, parent2, individual1, individual2);
                }
            } while (individualIndex < data.getPopulation().length);
            phaser.arriveAndAwaitAdvance();
        }
    }
}
