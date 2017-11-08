package Design_Pattern.NULL_OBJECT;

/**
 * Created by sunkai on 2017/11/8
 */
public class DB {
    public static Employee getEmployee(String name)
    {
        if("tom".equals(name))
        {
            return new Employee();
        }
        else
        {
            return Employee.NULL;
        }
    }
}
