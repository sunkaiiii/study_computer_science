package Design_Pattern.NULL_OBJECT;

import java.util.Date;

/**
 * Created by sunkai on 2017/11/8
 */
public class TestEmplyee {

    public static void main(String args[]){
        Employee tom=DB.getEmployee("tom");
        Employee sam=DB.getEmployee("sam");
        System.out.println(tom.isTimeToPay(new Date()));
        System.out.println(sam.isTimeToPay(new Date()));
    }
}
