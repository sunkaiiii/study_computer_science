package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.basic;

public class Individual implements Comparable<Individual> {
    //Individual类存放了TSP问题的所有可能解
    //每个可能解都称作一个个体，将其描述为染色体。用一个数字表示


    private Integer[] chromosomes;

    private int value;


    public Individual(int size) {
        chromosomes = new Integer[size];
    }

    public Individual(Individual other) {
        chromosomes = other.getChromosomes().clone();
    }

    @Override
    public int compareTo(Individual o) {
        return Integer.compare(this.getValue(), o.getValue());
    }


    public Integer[] getChromosomes() {
        return chromosomes;
    }


    public void setChromosomes(Integer[] chromosomes) {
        this.chromosomes = chromosomes;
    }


    public int getValue() {
        return value;
    }


    public void setValue(int value) {
        this.value = value;
    }

    @Override
    public String toString() {
        String ret = "";
        for (Integer number : chromosomes) {
            ret += number + ";";
        }
        return ret;
    }
}
