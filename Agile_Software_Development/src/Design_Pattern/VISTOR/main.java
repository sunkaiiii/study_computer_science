package Design_Pattern.VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public class main {
    public static void main(String args[]){
        TestModemVisitor test=new TestModemVisitor();
        test.setUp();
        test.testErineModem();
        test.testHayesForUnix();
        test.testZoomForUnix();
    }
}
