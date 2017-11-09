package Design_Pattern.VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public class ErineModem implements Modem {
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
    public void accept(ModemVisitor v) {
        v.visit(this);
    }
    String configurationString=null;
}
