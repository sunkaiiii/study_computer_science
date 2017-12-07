import Entity.Artist;

import java.util.Comparator;
import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class main {
    public static void main(String argv[]){

    }

    //找出成员最多的乐队
    //使用maxBy，将艺术家映射为成员变量，然后定义一个比较器
    //并将比较器传入maxBy收集器
    public Optional<Artist> biggestGroup(Stream<Artist> artists){
        Function<Artist,Long> getCount=artist -> artist.getMembers().stream().count();
        return artists.collect(Collectors.maxBy(Comparator.comparing(getCount)));
    }
}
