package String;

/**
 * Created by sunkai on 2017/9/12
 */
public class test {
    private static String[] constructString(){
        String[] a=new String[13];
        a[0]="4PGC938";
        a[1]="2IYE230";
        a[2]="3CI0720";
        a[3]="1ICK750";
        a[4]="10HV845";
        a[5]="4JZY524";
        a[6]="1ICK750";
        a[7]="3CI0720";
        a[8]="10HV845";
        a[9]="10HV845";
        a[10]="2RLA629";
        a[11]="2RLA630";
        a[12]="3ATW723";
        return a;
    }
    public static void main(String[] args){
        String[]s=constructString();
        //LSD.sort(s,s[0].length());
        //MSD.sort(s);
        Quick3string.sort(s);
        for(String a:s){
            System.out.println(a);
        }
    }
}
