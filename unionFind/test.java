package unionFind;

public class test {
    public static void main(String args[]) {
        UF testUF = new UF(10);
        QuickUF testQuickUF = new QuickUF(10);
        WeightedQuickUnionUF weightUF=new WeightedQuickUnionUF(10);
        int a[][] = new int[][]{{4, 3}, {3, 8}, {6, 5}, {9, 4}, {2, 1}, {8, 9}, {5, 0}, {7, 2}, {6, 1}, {1, 0}, {6, 7}};
        for (int i = 0; i < 10; i++) {
            int p = a[i][0];
            int q = a[i][1];
            if (testUF.connected(p, q))
                continue;
            testUF.union(p, q);
            System.out.println(testUF.count() + "components");
        }
        for (int i = 0; i < 10; i++) {
            int p = a[i][0];
            int q = a[i][1];
            testQuickUF.union(p, q);
            System.out.println(testQuickUF.count() + "components");
        }
        for (int i = 0; i < 10; i++) {
            int p = a[i][0];
            int q = a[i][1];
            weightUF.union(p, q);
            System.out.println(weightUF.count() + "components");
        }
        testUF.show();
        int testp=2;
        int testq=6;
        System.out.println(testUF.connected(testp, testq));
        testQuickUF.show();
        System.out.println(testQuickUF.find(testp)==testQuickUF.find(testq));
        weightUF.show();
        System.out.println(weightUF.find(testp)==weightUF.find(testq));
    }
}

