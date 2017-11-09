package Design_Pattern.ACYCLIC_VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public class TestModemVisitor {
    private ModemVistor v;
    private HayesModem m;
    private ZoomModem z;
    private ErnieModem e;

    public void setUp(){

        m=new HayesModem();
        z=new ZoomModem();
        e=new ErnieModem();
    }

    public void testHayesForUnix(){
        v=new HayewsModemVisitor();
        m.accept(v);
        System.out.println(m.configurationString);
    }

    public void testZoomForUnix(){
        v=new ZoomModemVisitor();
        z.accept(v);
        System.out.println(z.configurationString);
    }

    public void testErineModem(){
        v=new ErnieModemVisitor();
        e.accept(v);
        System.out.println(e.configurationString);
    }
}
