package Design_Pattern.ACYCLIC_VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public class ZoomModem implements Modem{
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
            ZoomModemVisitor zv=(ZoomModemVisitor)v;
            zv.visit(this);
        }catch (ClassCastException e){e.printStackTrace();}
    }
    int configurationString=0;
}
