package No3_Concurrency_Programming_with_Java.cp2;

import java.util.Random;

public class MatrixGenerator {
    public static double[][] generate(int rows,int colums){
        double[][] ret=new double[rows][colums];
        Random random=new Random();
        for(int i=0;i<rows;i++){
            for(int j=0;j<rows;j++){
                ret[i][j]= random.nextDouble()*10;
            }
        }
        return ret;
    }
}
