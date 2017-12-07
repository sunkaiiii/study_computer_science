package chapter4;

import Entity.Album;
import Entity.Artist;

import java.util.IntSummaryStatistics;
import java.util.List;
import java.util.Optional;

public class main {
    public static void main(String args[]){
        //使用summaryStatics方法统计曲目长度
        Album album=new Album();
        printTrackLengthStatistics(album);

        //Optional对象,Option对象是可能为空的
        Optional<String> a=Optional.of("a");
        System.out.println(a.get());

        //Optional对象的一些工厂方法
        Optional emptyOptional=Optional.empty();
        Optional alsoEmpty=Optional.ofNullable(null); //将null转换为一个Optional对象
        System.out.println(emptyOptional.isPresent());
        System.out.println(a.isPresent());
        //使用orElse和orElseGet方法
        System.out.println("b"==emptyOptional.orElse("b")); //当对象为空的时候，提供一个备选值
        System.out.println("c"==emptyOptional.orElseGet(()->"c")); //提供一个Supplier对象，只有在Optional对象真正为空的时候才调用

    }

    public static void printTrackLengthStatistics(Album album){
        IntSummaryStatistics trackLengthStats=album.trakcs.stream().mapToInt(track->track.length).summaryStatistics();
        System.out.println(String.format("Max:%d,Min:%d,Ave:%f,Sum:%d",trackLengthStats.getMax(),trackLengthStats.getMin(),trackLengthStats.getAverage(),trackLengthStats.getSum()));
    }

    //现在有一个类
    public class Artists {
        private List<Artist> artists;

        public Artists(List<Artist> artists) {
            this.artists = artists;
        }

        public Artist getArtist(int index) {
            if (index < 0 || index >= artists.size()) {
                indexException(index);
            }
            return artists.get(index);
        }

        private void indexException(int index) {
            throw new IllegalArgumentException(index +
                    "doesn't correspond to an Artist");
        }

        public String getArtistName(int index) {
            try {
                Artist artist = getArtist(index);
                return artist.getName();
            } catch (IllegalArgumentException e) {
                return "unknown";
            }
        }
    }
    //重构他
    public class Artists_R{
        private List<Artist> artists;
        public Artists_R(List<Artist> artists){
            this.artists=artists;
        }
        public Optional<Artist> getArtist(int index){
            if(index<0||index>=artists.size())
                return Optional.empty();
            return Optional.of(artists.get(index));
        }
        public String getArtistName(int index){
            Optional<Artist> artist=getArtist(index);
            return artist.map(Artist::getName).orElse("unknow");
        }
    }
}
