package Bowling;

/**
 * Created by sunkai on 2017/11/7
 */
public class test {
    private static Game g;

    private static void assertEquals(int lv, int rv) {
        System.out.println("lv:" + lv + " rv:" + rv + " " + (lv == rv));
    }

    public static void main(String args[]) {
        g = new Game();
        g.add(1);
        g.add(4);
        g.add(4);
        g.add(5);
        g.add(6);
        g.add(4);
        g.add(5);
        g.add(5);
        g.add(10);
        g.add(0);
        g.add(1);
        g.add(7);
        g.add(3);
        g.add(6);
        g.add(4);
        g.add(10);
        g.add(2);
        g.add(8);
        g.add(6);
        assertEquals(133, g.score());
    }
}
