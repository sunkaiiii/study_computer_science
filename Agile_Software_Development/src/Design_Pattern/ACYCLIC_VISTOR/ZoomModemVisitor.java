package Design_Pattern.ACYCLIC_VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public class ZoomModemVisitor implements ModemVistor{
    public void visit(ZoomModem m){
        m.configurationString=42;
    }
}
