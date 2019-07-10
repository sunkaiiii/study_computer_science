package java8_in_action.part2;

import java.util.Spliterator;
import java.util.function.Consumer;

public class WordCounterSpliterator implements Spliterator<Character> {
    //因为默认的策略会打乱字符。
    //我们想要的效果是以单词为最小单元进行并行分配

    private final String string;
    private int currentChar=0;

    public WordCounterSpliterator(String string){
        this.string=string;
    }

    @Override
    public boolean tryAdvance(Consumer<? super Character> action) {
        action.accept(string.charAt(currentChar++)); //处理当前字符
        return currentChar<string.length(); //如果还有字符要处理，则返回true
    }

    @Override
    public Spliterator<Character> trySplit() {
        int currentSize=string.length()-currentChar;
        if(currentSize<10){
            return null;
        }

        for(int splitPos=currentSize/2+currentChar;splitPos<string.length();splitPos++){
            if(Character.isWhitespace(string.charAt(splitPos))){ //当找到空格的时候才拆分，保证每个词的完整性
                Spliterator<Character> spliterator=new WordCounterSpliterator(string.substring(currentChar,splitPos));
                currentChar=splitPos;
                return spliterator;
            }
        }
        return null;
    }

    @Override
    public long estimateSize() {
        return string.length()-currentChar;
    }

    @Override
    public int characteristics() {
        return ORDERED+SIZED+SUBSIZED+NONNULL+IMMUTABLE;
    }
}
