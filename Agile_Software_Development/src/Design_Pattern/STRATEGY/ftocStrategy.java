package Design_Pattern.STRATEGY;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Created by sunkai on 2017/11/8
 */
public class ftocStrategy implements Application {
    private InputStreamReader isr;
    private BufferedReader br;
    private boolean isDone=false;
    public static void main(String args[]) throws Exception {
        (new ApplicationRunner(new ftocStrategy())).run();
    }

    @Override
    public void init() {
        isr = new InputStreamReader(System.in);
        br = new BufferedReader(isr);
    }

    @Override
    public void idle() {
        String fahrString = readLineAndReturnNullIfError();
        if (null == fahrString || fahrString.length() == 0) {
            isDone=true;
        } else {
            double fasr = Double.parseDouble(fahrString);
            double celcius = 5.0 / 9.0 * (fasr - 32);
            System.out.println("F=" + fasr + ",C=" + celcius);

        }
    }
    @Override
    public void cleanup() {
        System.out.println("ftoc exit");
    }

    @Override
    public boolean done(){
        return isDone;
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
