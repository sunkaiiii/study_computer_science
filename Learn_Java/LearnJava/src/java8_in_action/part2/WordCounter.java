package java8_in_action.part2;

public class WordCounter {
    //因为Java没有元组，创建一个新类来把状态封装起来
    private final int counter;
    private final boolean lastSpace;
    public WordCounter(int counter,boolean lastSpace){
        this.counter=counter;
        this.lastSpace=lastSpace;
    }

    public WordCounter accumulate(Character c){
        if(Character.isWhitespace(c)){
            return lastSpace?this:new WordCounter(counter,true);
        }else{
            return lastSpace?new WordCounter(counter+1,false):this;
        }
    }

    public WordCounter combine(WordCounter wordCounter){
        return new WordCounter(counter+wordCounter.counter,wordCounter.lastSpace);
    }
    public int getCounter(){
        return counter;
    }
}
