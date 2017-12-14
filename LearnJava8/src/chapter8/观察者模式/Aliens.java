package chapter8.观察者模式;

/**
 * Created by sunkai on 2017/12/14
 */
public class Aliens implements LandingObserver {
    @Override
    public void observeLanding(String name) {
        if(name.contains("Apollo")){
            System.out.println("They're distracted,Lets invade earth!");
        }
    }
}
