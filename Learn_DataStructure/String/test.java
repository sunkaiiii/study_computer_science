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
    private static String[] constructTrieST(){
        String[] a=new String[8];
        a[0]="she";
        a[1]="sells";
        a[2]="sea";
        a[3]="shells";
        a[4]="by";
        a[5]="the";
        a[6]="sea";
        a[7]="shore";
        return a;
    }
    public static void main(String[] args) {
//        String[]s=constructString();
        //LSD.sort(s,s[0].length());
        //MSD.sort(s);
//        Quick3string.sort(s);
//        for(String a:s){
//            System.out.println(a);
//        }

//        String[] a = constructTrieST();
//        TrieST trieST=new TrieST();
//        for(int i=0;i<a.length;i++){
//            trieST.put(a[i],i);
//    }
//        System.out.println(trieST.get("shells"));
//        for(Object s:trieST.keys()){
//            System.out.println(s);
//        }
//        for(Object s:trieST.keyWithPrefix("sh")){
//            System.out.println(s);
//        }
//        System.out.println(trieST.longestPrefixOf("shellsdshiafhw"));
//        TST tst=new TST();
//        for(int i=0;i<a.length;i++){
//            tst.put(a[i],i);
//        }
//        System.out.println(tst.get("shells"));


        KMP kmp=new KMP("asnflknvklnaiwotqiwotnoivnalkncenawlnweuhnbwentrwgbuiehv89awndjgl");
        System.out.println(kmp.search("wo"));
    }
}
