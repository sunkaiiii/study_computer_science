package cp2;

import java.util.Arrays;
import java.util.List;
import java.util.function.Predicate;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class Cp2Main {
    private void testStream(){
        final String[] input={"1","2","3","4","5"};
        final List<String> strings= Arrays.asList(input);
        final String search="3";
        final String three=strings.stream().filter(s->s.equalsIgnoreCase(search)).collect(Collectors.joining(", "));
        System.out.println(three);

        //prediczte接口的默认方法：or
        final Predicate<String> p=s->s.equalsIgnoreCase(search);
        final Predicate<String> combined=p.or(s->s.equalsIgnoreCase("4"));
        final String threeAndFour=strings.stream().filter(combined).collect(Collectors.joining(", "));
        System.out.println(threeAndFour);

        //stream API当中的map方法
        List<Integer> lengthList=strings.stream().map(String::length).collect(Collectors.toList());
        System.out.println(lengthList);

        var allString=strings.stream().reduce("",(x,y)->{ return x+","+y;});
        System.out.println(allString);
    }

    private void testRegex(){
        //正则表达式的实例
        Pattern p=Pattern.compile("colou?r");
        String styleUK="this is red colour";
        String styleUS="this is blue color";
        var mUK=p.matcher(styleUK);
        var mUS=p.matcher(styleUS);
        System.out.println("Matches UK spelling?"+mUK.find());
        System.out.println("Matches US spelling?"+mUS.find());

        var p2=Pattern.compile("organi[zs]ation");
        String styleUK2="This is an UK organisation";
        String styleUS2="This is an US organization";
        var mUK2=p2.matcher(styleUK2);
        var mUS2=p2.matcher(styleUS2);
        System.out.println("Matches UK spelling?"+mUK2.find());
        System.out.println("Matches US spelling?"+mUS2.find());

        //一些更复杂的正则表达式
        String pStr="\\d";//一个数字
        String text="Apollo 13";
        p=Pattern.compile(pStr);
        var m=p.matcher(text);
        System.out.println(pStr+" matches "+"? "+m.find());
        System.out.println(" ; match: "+m.group());

        pStr="[a..zA..Z]";//任意一个字母
        p=Pattern.compile(pStr);
        m=p.matcher(text);
        System.out.println(pStr+" matches "+"? "+m.find());
        System.out.println(" ; match: "+m.group());

        //任意个字母，但字母只能在a到j之间，大小不限
        pStr="([a..JA..J]*)";
        p=Pattern.compile(pStr);
        m=p.matcher(text);
        System.out.println(pStr+" matches "+"? "+m.find());
        System.out.println(" ; match: "+m.group());

        text="abacab";
        pStr="a....b";//a和b之间有四个字符
        p=Pattern.compile(pStr);
        m=p.matcher(text);
        System.out.println(pStr+" matches "+"? "+m.find());
        System.out.println(" ; match: "+m.group());

        //正则表达式与lambda表达式结合
        pStr="\\d";
        p=Pattern.compile(pStr);
        String[] strings={"Cat","Dog","Ice-9","99 Luftballoons"};
        List<String> ls=Arrays.asList(strings);
        List<String> containDigits=ls.stream().filter(p.asPredicate()).collect(Collectors.toList());
        System.out.println(containDigits);
    }

    public static void main(String[] args){
        Cp2Main cp2Main=new Cp2Main();
        cp2Main.testStream();
        cp2Main.testRegex();
        System.out.println(0.2-0.3);
    }
}
