package Entity;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

public class Album {
    public String name;
    public List<Track> trakcs;
    public List<Artist> musicians;

    public Stream getMusicians(){
        return musicians.stream();
    }
    public Artist getMainMusicians(){
        return musicians.get(0);
    }
    public String getName(){
        return name;
    }
    public Stream<Track> getTrakcs(){
        return trakcs.stream();
    }

    public Album(){
        name="";
        trakcs=new ArrayList<>();
        trakcs.add(new Track("",0));
        trakcs.add(new Track("",0));
        trakcs.add(new Track("",0));
        trakcs.add(new Track("",0));
        musicians=new ArrayList<>();
    }
}
