package chapter8命令者模式;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Created by sunkai on 2017/12/12
 */
public class main {
    public static void main(String args[]){
        List<String> strings=new ArrayList<String>(Arrays.asList(
                new String("abc"),
                new String("13"),
                new String("bba"),
                new String("AFF")));
        elementFirstToUpperCaseLambdas(strings);

    }
    public static List<String> elementFirstToUpperCaseLambdas(List<String> words){
        return words.stream()
                .map(main::firstToUpperCase)
                .peek(eachString-> System.out.println(eachString)) //peek操作可以查看每一个值，而且还能继续操作流
                .collect(Collectors.<String>toList());
    }
    public static String firstToUpperCase(String value){
        char firstChar=Character.toUpperCase(value.charAt(0));
        return firstChar+value.substring(1);
    }
}
