/**
 * Created by sunkai on 2017/11/6
 */
public class test {
    private static void assertEquals(int lv,int rv)
    {
        System.out.println("lv:"+lv+" rv:"+rv+" "+(lv==rv));
    }
    public static void main(String[] args){
        int[] nullArray=GeneratePrimes.generatePrimes(0);
        assertEquals(nullArray.length,0);

        int[] minArray=GeneratePrimes.generatePrimes(2);
        assertEquals(minArray.length,1);
        assertEquals(minArray[0],2);

        int[] threeArray=GeneratePrimes.generatePrimes(3);
        assertEquals(threeArray.length,2);
        assertEquals(threeArray[0],2);
        assertEquals(threeArray[1],3);

        int[] centArray=GeneratePrimes.generatePrimes(100);
        assertEquals(centArray.length,25);
        assertEquals(centArray[24],97);
    }
}
