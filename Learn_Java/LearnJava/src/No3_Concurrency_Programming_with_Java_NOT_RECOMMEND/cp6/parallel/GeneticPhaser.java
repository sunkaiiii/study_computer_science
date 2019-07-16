package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp6.parallel;

import java.util.Arrays;
import java.util.concurrent.Phaser;

public class GeneticPhaser extends Phaser {
    public SharedData getData() {
        return data;
    }

    public void setData(SharedData data) {
        this.data = data;
    }

    //要重载OnAdvance方法。
    //在所有的参与方法都完成某个阶段且即将开始下一阶段时执行该方法
    //说真的……这个框架感觉并不如stream好用
    private SharedData data;
    public GeneticPhaser(int parties, SharedData data) {
        super(parties);
        this.data=data;
    }

    //onAdvance方法将接收分段器的阶段编号和已注册参与方的编码作为参数
    //算法只有三个阶段，将被多次执行
    //必须将分段器的阶段编号转换成遗传算法的阶段编号
    //如果余数为-，任务完成了选择阶段并且准备执行交叉阶段，进行初始化
    //如果余数为1，任务进行交叉阶段
    //如果为2，则进入选择阶段
    //需要注意的是，目前方法还只能由一个线程执行，还需要一个分段器
    @Override
    protected boolean onAdvance(int phase, int registeredParties) {
        int realPhase=phase%3;
        if(registeredParties>0){
            switch (realPhase){
                case 0:
                case 1:
                    data.getIndex().set(0);
                    break;
                case 2:
                    Arrays.sort(data.getPopulation());
                    if(data.getPopulation()[0].getValue()<data.getBest().getValue()){
                        data.setBest(data.getPopulation()[0]);
                    }
                    break;
            }
            return false;
        }
        return true;
    }
}
