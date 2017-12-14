package chapter8.观察者模式;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by sunkai on 2017/12/14
 */
public class Moon {
    private final List<LandingObserver> observers=new ArrayList<>();

    public void land(String name){
        for(LandingObserver observer:observers){
            observer.observeLanding(name);
        }
    }

    public void startSpying(LandingObserver observer){
        observers.add(observer);
    }
}
