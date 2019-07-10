package java8_in_action.part3;

import org.junit.jupiter.api.Test;

import java.util.Comparator;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class Point {
    private final int x;
    private final int y;

    //通过该字段，可以访问Comparator对象
    //用于测试使用
    private final static Comparator<Point> compareByXandThenY = Comparator.comparing(Point::getX).thenComparing(Point::getY);

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public Point moveRightBy(int x) {
        return new Point(this.x + x, this.y);
    }

    @Test
    public void testComparingTwoPoints() throws Exception {
        Point p1 = new Point(10, 15);
        Point p2 = new Point(10, 20);
        int result = Point.compareByXandThenY.compare(p1, p2);
        assertEquals(-1, result);
    }
}
