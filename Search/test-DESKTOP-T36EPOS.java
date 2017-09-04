package Search;

        import StackAndQueue.Queue;

public class test {
    public static void main(String[] args) {
//        SequentialSearchST<Integer,String> test=new SequentialSearchST<>();
//        test.put(1,"123");
//        test.put(2,"1234");
//        System.out.println(test.get(1));

//        BinarySearchST<Integer,String> test=new BinarySearchST<>(15);
//        test.put(1,"123");
//        test.put(2,"1234");
//        System.out.println(test.get(1));

//        BST<String,Integer> bt=new BST<>();
//        bt.put("S",8);
//        bt.put("A",2);
//        bt.put("E",6);
//        bt.put("C",1);
//        bt.put("R",3);
//        bt.put("X",1);
//        bt.put("H",2);
//        bt.put("M",1);
//        System.out.println(bt.get("X"));
//        bt.show();
//        System.out.println();
//        System.out.println(bt.min());
//        System.out.println(bt.floor("C"));
//        System.out.println(bt.select(0));
//        System.out.println(bt.rank("C"));

//        bt.deleteMin();
//        bt.delete("E");
//        bt.show();

//        bt.mid_show();

//        RedBlackBST<String, String> rbt = new RedBlackBST<>();
//        rbt.put("S", "S");
//        rbt.show();
//        rbt.put("E", "E");
//        rbt.show();
//        rbt.put("A", "A");
//        rbt.show();
//        rbt.put("R", "R");
//        rbt.show();
//        rbt.put("C", "C");
//        rbt.show();
//        rbt.put("H", "H");
//        rbt.show();
//        rbt.put("X", "X");
//        rbt.show();
//        rbt.put("M", "M");
//        rbt.show();
//        rbt.put("P", "p");
//        rbt.show();
//        rbt.put("L", "L");
//        rbt.show();
//        rbt.put("K", "K");
//        rbt.show();

        SeparateChainingHashST<Integer,Integer> st=new SeparateChainingHashST<>();
        st.put(123,123);
        st.put(12421,214124);

        LinearProbingHashST<String,String> st2=new LinearProbingHashST<>();
        st2.put("!23","!23344");
        st2.put("214521","@!$125");
        System.out.println(st2.get("!23"));
    }
}
