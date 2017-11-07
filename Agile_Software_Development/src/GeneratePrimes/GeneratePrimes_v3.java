package GeneratePrimes;

/**
 * Created by sunkai on 2017/11/6
 */

//GeneratePrimes的第三个重构版本，噶进了方法的名字，替换了一些变量的名字
//使之更容易阅读
public class GeneratePrimes_v3 {
    private static boolean f[];
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
        for (i = 0; i < f.length; i++) {
            if (f[i])
                count++;
        }
        result = new int[count];
        for (i = 0, j = 0; i < f.length; i++) {
            if (f[i])
                result[j++] = i;
        }
    }

    private static void crossOutMultiples() {
        int j;
        int i;
        for (i = 2; i < Math.sqrt(f.length) + 1; i++) {
            if (f[i])
                for (j = 2 * i; j < f.length; j += i) {
                    f[j] = false;
                }
        }
    }

    private static void initializeArrayOfIntegers(int maxValue) {
        f = new boolean[maxValue+1];
        int i;
        for (i = 0; i < f.length; i++) {
            f[i] = true;
        }
        f[0] = f[1] = false;
    }
}
