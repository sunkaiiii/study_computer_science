package No3_Concurrency_Programming_with_Java.cp2;

public class SerialMultiplier {
    //串形版本的矩阵计算
    public static void multiply(double[][] matrix1,double[][] matrix2,double[][] result){
        int rows1=matrix1.length;
        int columns1=matrix1[0].length;
        int columns2=matrix2[0].length;

        for(int i=0;i<rows1;i++){
            for(int j=0;j<columns2;j++){
                result[i][j]=0;
                for(int k=0;k<columns1;k++){
                    result[i][j]+=matrix1[i][k]*matrix2[k][j];
                }
            }
        }
    }
}