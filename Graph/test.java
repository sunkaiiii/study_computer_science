package Graph;

import StackAndQueue.Stack;

import java.util.Scanner;

/**
 * Created by sunkai on 2017/9/4.
 */
public class test {
    private static final Graph constructGraph() {
        Graph graph = new Graph(13);
        graph.addEdge(0, 5);
        graph.addEdge(4, 3);
        graph.addEdge(0, 1);
        graph.addEdge(9, 12);
        graph.addEdge(6, 4);
        graph.addEdge(5, 4);
        graph.addEdge(0, 2);
        graph.addEdge(11, 12);
        graph.addEdge(9, 10);
        graph.addEdge(0, 6);
        graph.addEdge(7, 8);
        graph.addEdge(9, 11);
        graph.addEdge(5, 3);
        graph.addEdge(6, 7);
        graph.addEdge(7, 9);
        graph.addEdge(8, 9);
        graph.addEdge(4, 11);
        return graph;
    }

    public static void main(String args[]) {
        Graph graph = constructGraph();
//        System.out.println(graph);
//        DepthFirstSearch dfs = new DepthFirstSearch(graph, 9);
//        System.out.println(dfs.count());
//
//        BreadthFIrstPaths paths = new BreadthFIrstPaths(graph, 0);
//        System.out.println(paths.hasPathTo(3));
//        for (int p : paths.pathTo(3)) {
//            System.out.print(p + ",");
//        }
//
//        DepthFirstPaths paths = new DepthFirstPaths(graph, 0);
//        System.out.println(paths.hasPathTo(3));
//        for (int p : paths.pathTo(3)) {
//            System.out.print(p + ",");
//        }
        CC cc = new CC(graph);
        System.out.println(cc.connected(3, 6));
        System.out.println(cc.count());
        System.out.println(graph);
    }
}
