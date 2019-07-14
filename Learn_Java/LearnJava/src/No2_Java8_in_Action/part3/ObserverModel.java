package No2_Java8_in_Action.part3;

import java.util.ArrayList;
import java.util.List;

public class ObserverModel implements Subject {
    public static class NYTimes implements Observer {
        @Override
        public void notify(String tweet) {
            if (tweet != null && tweet.contains("money")) {
                System.out.println("Breaking news in NY:" + tweet);
            }
        }
    }

    public static class Guardian implements Observer {
        @Override
        public void notify(String tweet) {
            if (tweet != null && tweet.contains("queen")) {
                System.out.println("Yet another news in London..." + tweet);
            }
        }
    }

    public static class LeMonde implements Observer {
        @Override
        public void notify(String tweet) {
            if (tweet != null && tweet.contains("wine")) {
                System.out.println("Today cheese, wine and news! " + tweet);
            }
        }
    }


    private final List<Observer> observers = new ArrayList<>();

    @Override
    public void registerObserver(Observer o) {
        this.observers.add(o);
    }

    @Override
    public void notifyObservers(String tweet) {
        observers.forEach(o -> o.notify(tweet));
    }
}
