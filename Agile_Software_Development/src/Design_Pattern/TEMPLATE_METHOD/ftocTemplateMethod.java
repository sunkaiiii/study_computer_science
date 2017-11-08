package Design_Pattern.TEMPLATE_METHOD;

import java.io.*;

/**
 * Created by sunkai on 2017/11/8
 */
public class ftocTemplateMethod extends Application {
    private InputStreamReader isr;
    private BufferedReader br;

    public static void main(String args[]) throws Exception {
        (new ftocTemplateMethod()).run();
    }

    @Override
    protected void init() {
        isr = new InputStreamReader(System.in);
        br = new BufferedReader(isr);
    }

    @Override
    protected void idel() {
        String fahrString = readLineAndReturnNullIfError();
        if (null == fahrString || fahrString.length() == 0) {
            setDone();
        } else {
            double fasr = Double.parseDouble(fahrString);
            double celcius = 5.0 / 9.0 * (fasr - 32);
            System.out.println("F=" + fasr + ",C=" + celcius);

        }
    }

    protected void cleanup() {
        System.out.println("ftoc exit");
    }

    private String readLineAndReturnNullIfError() {
        String s;
        try {
            s = br.readLine();
        } catch (IOException e) {
            s = null;
        }
        return s;
    }
}
