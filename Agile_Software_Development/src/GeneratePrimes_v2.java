/**
 * Created by sunkai on 2017/11/6
 */

//GeneratePrimes的第一个重构版本
public class GeneratePrimes_v2 {
    private static int a;
    private static boolean f[];
    private static int[] primes;
    private static int s;

    public static int[] generatePrimes(int maxValue) {
        if (maxValue < 2) {
            return new int[0];
        } else {
            initializeSieve(maxValue);
            sieve();
            loadPrimes();
            return primes;
        }
    }

    private static void loadPrimes() {
        int count = 0;
        int i;
        int j;
        for (i = 0; i < s; i++) {
            if (f[i])
                count++;
        }
        primes = new int[count];
        for (i = 0, j = 0; i < s; i++) {
            if (f[i])
                primes[j++] = i;
        }
    }

    private static void sieve() {
        int j;
        int i;
        for (i = 2; i < Math.sqrt(s) + 1; i++) {
            if (f[i])
                for (j = 2 * i; j < s; j += i) {
                    f[j] = false;
                }
        }
    }

    private static void initializeSieve(int maxValue) {
        s = maxValue + 1;
        f = new boolean[s];
        int i;
        for (i = 0; i < s; i++) {
            f[i] = true;
        }
        f[0] = f[1] = false;
    }
}
