package chapter5;

import Entity.Album;
import Entity.Artist;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class main {
    public static void main(String argv[]){
        setToList();
        setToOrdderList();
        unorderSetMapToList();
        ListToTreeSet();

        List<Artist> artists=new ArrayList<>();
        artists.add(new Artist("sun",null,null));
        artists.add(new Artist("sun2",null,null));
        System.out.println(FormattingArtist(artists.stream()));
        main m=new main();
        System.out.println(m.fabiinaci(4));

    }

    //集合本身是无序的，因此生成的流也是无序的，因此不能保证
//    生成的List和原来的set是一样的顺序
    public static void setToList(){
        Set<Integer> numbers=new HashSet<>();
        numbers.add(10);
        numbers.add(11);
        numbers.add(12);
        numbers.add(13);
        numbers.stream().collect(Collectors.toList());
        System.out.println(numbers);
    }

    //经过排序之后，便是有序的了
    public static void setToOrdderList(){
        Set<Integer> numbers=new HashSet<>();
        numbers.add(10);
        numbers.add(11);
        numbers.add(12);
        numbers.add(13);
        List<Integer> sameOrder=numbers.stream().sorted().collect(Collectors.toList());
        System.out.println(sameOrder);
    }
    //经过一些值映射之后，映射后的值依旧不能保证有序
    public static void unorderSetMapToList(){
        Set<Integer> numbers=new HashSet<>();
        numbers.add(10);
        numbers.add(11);
        numbers.add(12);
        numbers.add(13);
        List<Integer> stillUnorderd=numbers.stream().map(x->x+1).collect(Collectors.toList());
        System.out.println(stillUnorderd);
    }

    public static void ListToTreeSet(){
        List<Integer> list=new ArrayList<>();
        list.add(10);
        list.add(11);
        list.add(12);
        list.add(13);
        Set<Integer> set=list.stream().collect(Collectors.toCollection(TreeSet::new));
        System.out.println(set);
    }

    //找出成员最多的乐队
    //使用maxBy，将艺术家映射为成员变量，然后定义一个比较器
    //并将比较器传入maxBy收集器
    public Optional<Artist> biggestGroup(Stream<Artist> artists){
        Function<Artist,Long> getCount=artist -> artist.getMembers().stream().count();
        return artists.collect(Collectors.maxBy(Comparator.comparing(getCount)));
    }

//    找出一组专辑曲目的平均数
    public static double averageNumberOfTracks(List<Album> albums){
        return albums.stream().collect(Collectors.averagingInt(album->album.trakcs.size()));
    }

    //将艺术家组成的流分成乐队和独唱歌手两部分
    public Map<Boolean,List<Artist>> bandsAndSolo(Stream<Artist> artists){
        return artists.collect(Collectors.partitioningBy(artist->artist.origin.equals("solo")));
    }
    //使用方法引用将艺术家组成的stream分成乐队和独唱歌手两部分
    //简写引用形式
    public Map<Boolean,List<Artist>> bandsAndSoloRef(Stream<Artist> artists){
        return artists.collect(Collectors.partitioningBy(Artist::isSolo));
    }

//    数据分组
//    使用主唱对专辑分组
    public Map<Artist,List<Album>> albumsByArtist(Stream<Album> albums){
        return albums.collect(Collectors.groupingBy(Album::getMainMusicians));
    }

    //使用流和收集器格式化艺术家姓名
    //以逗号间隔，左右括号为开始和结束链接
    public static String FormattingArtist(Stream<Artist> artists){
        return artists.map(Artist::getName).collect(Collectors.joining(",","[","]"));
    }

    //使用收集器计算每个艺术家的专辑数
    //告诉grouppingBy不用为每一个艺术家生成一个专辑列表，只需要对专辑计数即可
    //使用counting收集器
    public Map<Artist,Long> numberOfAlbums(Stream<Album> albums){
        return albums.collect(Collectors.groupingBy(Album::getMainMusicians,Collectors.counting()));
    }

    //使用收集器求每个艺术家的专辑名
    public static Map<Artist,List<String>> nameOfAlbumsNormal(Stream<Album> albums){
        Map<Artist,List<Album>> albumsByArtist=albums.collect(Collectors.groupingBy(Album::getMainMusicians));
        Map<Artist,List<String>> nameOfAlbums=new HashMap<>();
        for(Map.Entry<Artist,List<Album>> entry:albumsByArtist.entrySet()){
            nameOfAlbums.put(entry.getKey(),entry.getValue().stream().map(Album::getName).collect(Collectors.toList()));
        }
        return nameOfAlbums;
    }
    public static Map<Artist,List<String>> nameOfAlbums(Stream<Album> albums){
        return albums.collect(Collectors
                .groupingBy(Album::getMainMusicians
                        ,Collectors.mapping(Album::getName,Collectors.toList())));
    }

//    一个语法糖computeIfAbsent
    public Artist getAArtist(String name){
        return new Artist(name,null,null);
    }
    public Artist getArtist(String name){
        Map<String,Artist> cache=new HashMap<>(); //一个空的缓存
        return cache.computeIfAbsent(name,this::getAArtist);
    }

    //迭代map的新方式
    public void forEachMap(){
        Map<Artist,Integer> countOfAlbums=new HashMap<>();
        Map<Artist,List<String>> albumsByArtist=new HashMap<>();
        albumsByArtist.forEach(((artist, strings) -> {
            countOfAlbums.put(artist,strings.size());
        }));
    }


    //找出名字最长的艺术家
    //分别使用reduce和高阶函数实现
    public static Artist findLongestArtistByReduce(List<Artist> artistList){
        return artistList.stream().reduce(artistList.get(0),(longest,artist)->{
            if(artist.getName().length()>longest.getName().length())
                longest=artist;
            return longest;
        });
    }

    public static Artist findLongestArtist(List<Artist> artistList){
        return artistList.stream().collect(Collectors.maxBy(byNameLength)).orElseThrow(RuntimeException::new);
    }
    private static Comparator<Artist> byNameLength=Comparator.comparing(artist -> artist.getName().length());

    //计算每个单词出现的次数，并且格式化输出
    public static Map<String,Long> countApear(Stream<String> names){
        return names.collect(Collectors.groupingBy(name->name,Collectors.counting()));
    }

    private Map<Integer,Integer> fabonaci=new HashMap<>();
    public main(){
        fabonaci.put(1,1);
        fabonaci.put(2,1);
    }
    public Integer fabiinaci(int i){
        return fabonaci.computeIfAbsent(i,index->fabiinaci(index-1)+fabiinaci(index-2));
    }
}

