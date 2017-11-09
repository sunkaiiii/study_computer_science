package Design_Pattern.ACYCLIC_VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public interface Modem {
    public void dial(String pno);
    public void hangup();
    public void send(char c);
    public char recv();
    public void accept(ModemVistor v);
}
