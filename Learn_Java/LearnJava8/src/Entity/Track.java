package Entity;

public class Track {
    public String name;
    public int length;
    public Track(String name,int length){
        this.name=name;
        this.length=length;
    }
    public int getLength(){
        return length;
    }
}
