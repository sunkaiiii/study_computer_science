package chapter3;

import Entity.Album;
import Entity.Artist;
import Entity.Track;

import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
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

        //编写一个求和函数，计算流中所有数的和
        System.out.println(addUp(Stream.of(1,2,3,4,5,6,7)));

        //编写一个函数，接受艺术家列表作为参数，返回一个字符串列表，其中包含艺术家的姓名和国籍
        List<Artist> artists=new ArrayList<>();
        artists.add(new Artist("bob",null,"UK"));
        artists.add(new Artist("Tom",null,"US"));
        System.out.println(getNameAndCountry(artists));

        //编写一个函数，接受专辑列表作为参数，返回一个有最少包含3首歌曲的专辑组成的列表
        List<Album> albums=new ArrayList<>();
        albums.add(new Album());
        System.out.println(getMuiltiTrackAlbum(getMuiltiTrackAlbum(albums)));

        //将外部迭代转为内部迭代
//        int totalMembers=0;
//        for(Artist artist:artists){
//            Stream<Artist> members=artist.mumbers.stream();
//            totalMembers+=members.count();
//
//        }
//        System.out.println(totalMembers);
//        //->转换
//        int totalNumbers=artists.stream()
//                .map(artist -> artist.mumbers.stream().count())
//                .reduce(0L,(result,membercount)->result+membercount)
//                .intValue();
//        System.out.println(totalNumbers);

        //在一个字符串列表中，找出包含最多小写字母的字符串
        List<String> strings=new ArrayList<>();
        strings.add("asd");
        strings.add("12q34");
        strings.add("!2");
        System.out.println(findMaxSmallString(strings));

    }

    public static int addUp(Stream<Integer> numbers){
        return numbers.reduce(0,(result,number)->result+number);
    }

    public static List<String> getNameAndCountry(List<Artist> artists){
        return artists.stream().map(artist -> artist.name+" "+artist.origin).collect(Collectors.toList());
    }

    public static List<Album> getMuiltiTrackAlbum(List<Album> albums){
        return albums.stream().filter(album -> album.trakcs.size()>3).collect(Collectors.toList());
    }

    public static String findMaxSmallString(List<String> strings){
        return strings.stream()
                .max(Comparator.comparing(eachString->eachString.chars()
                        .filter(Character::isLowerCase)
                        .count())).get();
    }


    public Set<String> findLongTracks(List<Album> albums){
        //原始代码
        Set<String> trackNames=new HashSet<>();
        for(Album album:albums){
            for(Track track:album.trakcs){
                if(track.length>60){
                    String name=track.name;
                    trackNames.add(name);
                }
            }
        }

        //重构之后的代码
        return albums.stream()
                .flatMap(album -> album.trakcs.stream())
                .filter(track -> track.length>60)
                .map(track -> track.name)
                .collect(Collectors.toSet());

    }

    private static boolean isDigit(char arg){
        return (arg>='0'&&arg<='9')?true:false;
    }
}
