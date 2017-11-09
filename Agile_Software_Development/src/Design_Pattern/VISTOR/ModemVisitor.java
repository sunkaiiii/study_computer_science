package Design_Pattern.VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public interface ModemVisitor {
    public void visit(HayesModem modem);
    public void visit(ZoomModem modem);
    public void visit(ErineModem modem);
}
