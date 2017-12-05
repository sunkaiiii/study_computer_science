
import Entity.Track;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class main {
    public static void main(String args[]){
        List<String> list=new ArrayList<>();
        list.add("honkon");
        list.add("honkon");
        list.add("china");
        //使用stream
        System.out.println(list.stream().
                filter(location->location.equals("honkon"))
                .count());

        //collect的方法有stream里的值生成一个列表
        List<String> collected= Stream.of("a","b","c").collect(Collectors.toList());

        //将一组字符串由小写变为大写的原来写法
        List<String> collect=new ArrayList<>();
        for(String string:Stream.of("a","b","c").collect(Collectors.toList())){
            String uppercaseString=string.toUpperCase();
            collect.add(uppercaseString);
        }
        System.out.println(collect);
        //使用map的写法
        List<String> collect2=Stream.of("a","b","c").map(string->string.toUpperCase()).collect(Collectors.toList());
        System.out.println(collect2);


        //查找符合条件的字符串
        List<String> beginningWithNumbers=new ArrayList<>();
        for(String value:Stream.of("a","1abc","abc1").collect(Collectors.toList())){
            if(isDigit(value.charAt(0))){
                beginningWithNumbers.add(value);
            }
        }
        System.out.println(beginningWithNumbers);
        //函数式风格
        List<String> beginningWithNumbers2=Stream.of("a","1abc","abc1")
                .filter(value->isDigit(value.charAt(0)))
                .collect(Collectors.toList());
        System.out.println(beginningWithNumbers2);

        //包含多个列表的Stream，使用flatMap可以将多个stream连接成一个stream
        List<Integer> together=Stream.of(
                Stream.of(1,2).collect(Collectors.toList()),Stream.of(3,4).collect(Collectors.toList()))
                .flatMap(numbers->numbers.stream())
                .collect(Collectors.toList());
        System.out.println(together);


        //使用max和min
        List<Track> tracks=Stream.of(new Track("Bakai",524),new Track("Violets for your furs",378),new Track("Time was",451)).collect(Collectors.toList());
        Track shortestTrack=tracks.stream().min(Comparator.comparing(track -> track.length)).get();
        System.out.println(shortestTrack.name);

        //使用reduce求和,括号里第一个参数是初始值，element代表着stream里面每一个值
        //实际生产中，不宜使用这个方法
        int count=Stream.of(1,2,3).reduce(0,(acc,element)->acc+element);
        System.out.println(count);
    }
    private static boolean isDigit(char arg){
        return (arg>='0'&&arg<='9')?true:false;
    }

}
