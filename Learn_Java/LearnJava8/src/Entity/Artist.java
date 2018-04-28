package Entity;

import java.util.List;

public class Artist {
    public String name;
    public List<Artist> mumbers;
    public String origin;
    public Artist(String name,List<Artist> mumbers,String origin){
        this.name=name;
        this.mumbers=mumbers;
        this.origin=origin;
    }

    public String getName(){
        return name;
    }

    public List<Artist> getMembers(){
        return mumbers;
    }
    public Boolean isSolo(){
        return origin.equals("solo");
    }
}
