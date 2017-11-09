package Design_Pattern.VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public class TestModemVisitor {
    private UnixModemConfigurator v;
    private HayesModem m;
    private ZoomModem z;
    private ErineModem e;

    public void setUp(){
        v=new UnixModemConfigurator();
        m=new HayesModem();
        z=new ZoomModem();
        e=new ErineModem();
    }

    public void testHayesForUnix(){
        m.accept(v);
        System.out.println(m.configurationString);
    }

    public void testZoomForUnix(){
        z.accept(v);
        System.out.println(z.configurationString);
    }

    public void testErineModem(){
        e.accept(v);
        System.out.println(e.configurationString);
    }

}
