package Design_Pattern.MONOSTATE;

/**
 * Created by sunkai on 2017/11/8
 */
public class Monostate {
    private static int itsX=0;
    public Monostate(){}

    public void setX(int x)
    {
        itsX=x;
    }

    public int getX()
    {
        return itsX;
    }
}
