package Design_Pattern.NULL_OBJECT;

import java.util.Date;

/**
 * Created by sunkai on 2017/11/8
 */
public class Employee {
    public boolean isTimeToPay(Date payDate) {
        return true;
    }

    public void pay() {
    }

    public static final Employee NULL = new Employee() {
        public boolean isTimeToPay(Date payDate) {
            return false;
        }

        public void pay() {

        }
    };
}
