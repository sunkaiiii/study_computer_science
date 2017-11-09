package Design_Pattern.ACYCLIC_VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public class HayesModem implements Modem{
    @Override
    public void dial(String pno) {

    }

    @Override
    public void hangup() {

    }

    @Override
    public void send(char c) {

    }

    @Override
    public char recv() {
        return 0;
    }

    @Override
    public void accept(ModemVistor v) {
        try{
            HayewsModemVisitor hv=(HayewsModemVisitor)v;
            hv.visit(this);
        }catch (ClassCastException e){ e.printStackTrace();}
    }
    String configurationString=null;
}
