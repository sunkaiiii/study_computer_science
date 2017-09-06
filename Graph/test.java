package Graph;

import StackAndQueue.Queue;
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
    private static final Diagraph constructDiagraph(){
        Diagraph diagraph=new Diagraph(13);
        diagraph.addEdge(4,2);
        diagraph.addEdge(2,3);
        diagraph.addEdge(3,2);
        diagraph.addEdge(6,0);
        diagraph.addEdge(0,1);
        diagraph.addEdge(2,0);
        diagraph.addEdge(11,12);
        diagraph.addEdge(12,9);
        diagraph.addEdge(9,10);
        diagraph.addEdge(9,11);
        diagraph.addEdge(8,9);
        diagraph.addEdge(10,12);
        diagraph.addEdge(11,4);
        diagraph.addEdge(4,3);
        diagraph.addEdge(3,5);
        diagraph.addEdge(7,8);
        diagraph.addEdge(8,7);
        diagraph.addEdge(5,4);
        diagraph.addEdge(0,5);
        diagraph.addEdge(6,4);
        diagraph.addEdge(6,9);
        diagraph.addEdge(7,6);
        return diagraph;
    }
    private static final EdgeWeightedGraph constructEdgeWeightGraph(){
        EdgeWeightedGraph edgeWeightedGraph=new EdgeWeightedGraph(8);
        edgeWeightedGraph.addEdge(new Edge(4,5,0.35));
        edgeWeightedGraph.addEdge(new Edge(4,7,0.37));
        edgeWeightedGraph.addEdge(new Edge(5,7,0.28));
        edgeWeightedGraph.addEdge(new Edge(0,7,0.16));
        edgeWeightedGraph.addEdge(new Edge(1,5,0.32));
        edgeWeightedGraph.addEdge(new Edge(0,4,0.38));
        edgeWeightedGraph.addEdge(new Edge(2,3,0.17));
        edgeWeightedGraph.addEdge(new Edge(1,7,0.19));
        edgeWeightedGraph.addEdge(new Edge(0,2,0.26));
        edgeWeightedGraph.addEdge(new Edge(1,2,0.36));
        edgeWeightedGraph.addEdge(new Edge(1,3,0.29));
        edgeWeightedGraph.addEdge(new Edge(2,7,0.34));
        edgeWeightedGraph.addEdge(new Edge(6,2,0.40));
        edgeWeightedGraph.addEdge(new Edge(3,6,0.52));
        edgeWeightedGraph.addEdge(new Edge(6,0,0.58));
        edgeWeightedGraph.addEdge(new Edge(6,4,0.93));
        return edgeWeightedGraph;
    }

    private static EdgeWeightedDiagraph constructEdgeWeightedDiagraph(){
        EdgeWeightedDiagraph edgeWeightedDiagraph=new EdgeWeightedDiagraph(8);
        edgeWeightedDiagraph.addEdge(new DirectedEdge(4,5,0.35));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(5,4,0.35));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(4,7,0.37));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(5,7,0.28));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(7,5,0.28));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(5,1,0.32));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(0,4,0.38));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(0,2,0.26));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(7,3,0.39));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(1,3,0.29));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(2,7,0.34));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(6,2,0.40));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(3,6,0.52));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(6,0,0.58));
        edgeWeightedDiagraph.addEdge(new DirectedEdge(6,4,0.93));
        return edgeWeightedDiagraph;
    }
    public static void main(String args[]) {
//        Graph graph = constructGraph();
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
//        CC cc = new CC(graph);
//        System.out.println(cc.connected(3, 6));
//        System.out.println(cc.count());
//        System.out.println(graph);


//        Diagraph diagraph=constructDiagraph();
//        System.out.println(diagraph);
//        DirectedDFS directedDFS=new DirectedDFS(diagraph,0);
//        System.out.println(directedDFS.marked(6));
//        DirectedCycle directedCycle=new DirectedCycle(diagraph);
//        System.out.println(directedCycle.hasCycle());
//        for(int w:directedCycle.cycle()){
//            System.out.println(w+" ");
//        }

//        DepthFIrstOrder depthFIrstOrder=new DepthFIrstOrder(diagraph);
//        for(int w:depthFIrstOrder.pre()){
//            System.out.print(w+" ");
//        }
//        System.out.println();
//        for(int w:depthFIrstOrder.post()){
//            System.out.print(w+" ");
//        }
//        System.out.println();
//        for(int w:depthFIrstOrder.reversePost()){
//            System.out.print(w+" ");
//        }

//        Topological topological=new Topological(diagraph);
//        System.out.println(topological.isDAG());

//        KosarajuSCC kosarajuSCC=new KosarajuSCC(diagraph);
//        System.out.println(kosarajuSCC.id(4));
//        System.out.println(kosarajuSCC.stronglyConnected(4,3));


//        EdgeWeightedGraph edgeWeightedGraph=constructEdgeWeightGraph();
//        for(Edge e:edgeWeightedGraph.adj(0)){
//            System.out.println(e);
//        }

//        LazyPrimMST lazyPrimMST=new LazyPrimMST(edgeWeightedGraph);
//        for(Edge e:lazyPrimMST.edges()){
//            System.out.println(e);
//        }

//        KruskalMST kruskalMST=new KruskalMST(edgeWeightedGraph);
//        for(Edge e:kruskalMST.edges()){
//            System.out.println(e);
//        }


        EdgeWeightedDiagraph edgeWeightedDiagraph=constructEdgeWeightedDiagraph();
    }
}
