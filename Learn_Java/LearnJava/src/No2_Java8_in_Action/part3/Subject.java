package No2_Java8_in_Action.part3;

public interface Subject{
    void registerObserver(Observer o);
    void notifyObservers(String tweet);
}
