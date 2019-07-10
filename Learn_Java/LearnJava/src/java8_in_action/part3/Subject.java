package java8_in_action.part3;

public interface Subject{
    void registerObserver(Observer o);
    void notifyObservers(String tweet);
}
