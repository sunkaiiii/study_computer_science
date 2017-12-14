package chapter8命令者模式;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by sunkai on 2017/12/12
 */
public class Macro {
    private final List<Action> actions;

    public Macro(){
        actions=new ArrayList<>();
    }

    public void record(Action action){
        actions.add(action);
    }

    public void run(){
        actions.forEach(Action::perform);
    }
    public static void main(String args[]){

    }
}
