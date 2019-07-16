package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.parallel;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.basic.Individual;

import java.util.concurrent.atomic.AtomicInteger;

public class SharedData {
    //这是一个与所有线程共享的数据结构
    //index是唯一被所有任务高效共享的属性


    private Individual[] population;
    private Individual[] selected;
    private AtomicInteger index;
    private Individual best;
    private int[][] distanceMatrix;

    public SharedData() {
        index = new AtomicInteger();
    }

    public Individual[] getPopulation() {
        return population;
    }

    public void setPopulation(Individual[] population) {
        this.population = population;
    }

    public Individual[] getSelected() {
        return selected;
    }

    public void setSelected(Individual[] selected) {
        this.selected = selected;
    }

    public AtomicInteger getIndex() {
        return index;
    }

    public void setIndex(AtomicInteger index) {
        this.index = index;
    }

    public Individual getBest() {
        return best;
    }

    public void setBest(Individual best) {
        this.best = best;
    }

    public int[][] getDistanceMatrix() {
        return distanceMatrix;
    }

    public void setDistanceMatrix(int[][] distanceMatrix) {
        this.distanceMatrix = distanceMatrix;
    }

}
