package Design_Pattern.VISTOR;

/**
 * Created by sunkai on 2017/11/9
 */
public class UnixModemConfigurator implements ModemVisitor {
    @Override
    public void visit(ZoomModem modem) {
        modem.configurationString=42;
    }

    @Override
    public void visit(ErineModem modem) {
        modem.configurationString="C is too low";
    }

    @Override
    public void visit(HayesModem modem) {
        modem.configurationString="214124";
    }
}
