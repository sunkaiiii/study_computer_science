package GeneratePrimes;

import java.util.Map;

/**
 * Created by sunkai on 2017/11/6
 */

//GeneratePrimes的第三个重构版本
//更改了f的变量名
//创建了一些新的函数
public class GeneratePrimes_v4 {
    private static boolean isCrossed[];
    private static int[] result;

    public static int[] generatePrimes(int maxValue) {
        if (maxValue < 2) {
            return new int[0];
        } else {
            initializeArrayOfIntegers(maxValue);
            crossOutMultiples();
            putUncroseedIntegerIntoResult();
            return result;
        }
    }

    private static void putUncroseedIntegerIntoResult() {
        int count = 0;
        int i;
        int j;
        for (i = 2; i < isCrossed.length; i++) {
            if (notCrossed(i))
                count++;
        }
        result = new int[count];
        for (i = 2, j = 0; i < isCrossed.length; i++) {
            if (notCrossed(i))
                result[j++] = i;
        }
    }

    private static void crossOutMultiples() {
        int maxPrimeFactor=calcMaxPrimeFactor();
        for (int i = 2; i <= maxPrimeFactor; i++) {
            if (notCrossed(i))
                crossOutMultiplesOf(i);
        }
    }

    private static int calcMaxPrimeFactor(){
        double maxPrimeFactor= Math.sqrt(isCrossed.length)+1;
        return (int)maxPrimeFactor;
    }

    private static void initializeArrayOfIntegers(int maxValue) {
        isCrossed = new boolean[maxValue + 1];
        for (int i = 0; i < isCrossed.length; i++) {
            isCrossed[i] = false;
        }
    }

    private static void crossOutMultiplesOf(int i){
        for(int multiple=i*2;multiple<isCrossed.length;multiple+=i)
            isCrossed[multiple]=true;
    }

    private static boolean notCrossed(int i){
        return isCrossed[i]==false;
    }
}
