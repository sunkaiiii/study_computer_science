package No1_Java_in_a_Nutshell.part2;

import javax.net.ssl.HttpsURLConnection;
import java.io.*;
import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.nio.channels.Channel;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
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

    private void fileIO(){
        //oldStyle
        try(BufferedReader in=new BufferedReader(new FileReader("No1_Java_in_a_Nutshell/part2/Cp2Main.java"))){
            StringBuilder sb=new StringBuilder();
            String line;
            while((line=in.readLine())!=null){
                sb.append(line);
            }
            System.out.println(sb.toString());
        }catch (IOException e){
            e.printStackTrace();
        }
        //newStyle
        File inputFile=new File("Cp2Main.java");
        try(InputStream in=new FileInputStream(inputFile)){
            Files.copy(in, Paths.get("2.txt"));
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    private void httpRequest(){
        try{
            URL url=new URL("https://www.bbc.co.uk/search");
            var rawData="q=java";
            var encodeData= URLEncoder.encode(rawData,"ASCII");
            var contentType="application/x-www-form-urlencoded";

            HttpsURLConnection conn=(HttpsURLConnection)url.openConnection();
            conn.setInstanceFollowRedirects(false);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("content-Type",contentType);
            conn.setRequestProperty("content-Length",String.valueOf(encodeData.length()));

            conn.setDoOutput(true);
            OutputStream os=conn.getOutputStream();
            os.write(encodeData.getBytes());
            int response=conn.getResponseCode();
            if(response==HttpURLConnection.HTTP_MOVED_PERM||response==HttpURLConnection.HTTP_MOVED_TEMP){
                System.out.println("Moved to: "+conn.getHeaderField("Location"));
            }else{
                try(InputStream in=conn.getInputStream()){
                    Files.copy(in,Paths.get("bbc.txt"), StandardCopyOption.REPLACE_EXISTING);
                }catch (IOException e){
                    e.printStackTrace();
                }
            }
        } catch (IOException e){
            e.printStackTrace();
        }
    }

    @Deprecated
    private void reflect(){
        //这个方法可以找到类中所有标记为弃用的方法
        Class<?> clz=getClass();
        for(var m:clz.getMethods()){
            for(var a:m.getAnnotations()){
                if(a.annotationType()==Deprecated.class){
                    System.out.println(m.getName());
                }
            }
        }

        //在String对象上调用hashCode方法
        Object rcvr="a";
        try{
            Class<?>[] argTypes=new Class[]{};
            Object[] args=null;
            Method meth=rcvr.getClass().getMethod("hashCode",argTypes);
            Object ret=meth.invoke(rcvr,args);
            System.out.println(ret);
        }catch (IllegalArgumentException | NoSuchMethodException | SecurityException | IllegalAccessException | InvocationTargetException e){
            e.printStackTrace();
        }
    }

    private static Class<?> commonAncestor(Class<?> cl1, Class<?> cl2){
        //这个方法可以查找传入的两个类的共同的父类
        if(cl1==null||cl2==null)
            return null;
        if(cl1.equals(cl2))
            return cl1;
        if(cl1.isPrimitive()||cl2.isPrimitive())
            return null;
        List<Class<?>> ancestors=new ArrayList<>();
        Class<?> c=cl1;
        while(!c.equals(Object.class)){
            if(c.equals(cl2))
                return c;
            ancestors.add(c);
            c=c.getSuperclass();
        }
        c=cl2;
        while(!c.equals(Object.class)){
            for(Class<?> k:ancestors){
                if(c.equals(k))
                    return c;
            }
            c=c.getSuperclass();
        }
        return Object.class;
    }

    private void invocationHandler() throws IOException {
        InvocationHandler h=new InvocationHandler() {
            @Override
            public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
                var name=method.getName();
                System.out.println("Called as: "+name);
                switch (name){
                    case "isOpen":
                        return false;
                    case "close":
                        return null;
                }
                return null;
            }
        };

        Channel c=(Channel) Proxy.newProxyInstance(Channel.class.getClassLoader(),new Class[]{Channel.class},h);
        c.isOpen();
        c.close();
    }

    private void methodType(){
        MethodType m2Str=MethodType.methodType(String.class); //toString()
        MethodType mtParseInt=MethodType.methodType(Integer.class,String.class);
        //defineClass
        MethodType mtdeFClz=MethodType.methodType(Class.class,String.class,byte[].class,int.class,int.class);
        var l= MethodHandles.lookup();
        lookupDefineClass(l);

        //使用方法句柄的方式调用hashcode
        Object rcvr="a";
        try{
            MethodType mt=MethodType.methodType(int.class);
            var l2=MethodHandles.lookup();
            var mh=l2.findVirtual(rcvr.getClass(),"hashCode",mt);
            int ret;
            try{
                ret=(int)mh.invoke(rcvr);
                System.out.println(ret);
            }catch (Throwable t){
                t.printStackTrace();
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private void lookupDefineClass(MethodHandles.Lookup l){
        MethodType mt=MethodType.methodType(Class.class,String.class,byte[].class,int.class,int.class);
        try{
            MethodHandle mh=l.findVirtual(ClassLoader.class,"defineClass",mt);
            System.out.println(mh);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public static void main(String[] args){
        Cp2Main cp2Main=new Cp2Main();
        cp2Main.testStream();
        cp2Main.testRegex();
        System.out.println(0.2-0.3);
        cp2Main.fileIO();
        cp2Main.httpRequest();
        cp2Main.reflect();
        System.out.println(commonAncestor(cp2Main.getClass(),String.class));
        try {
            cp2Main.invocationHandler();
            cp2Main.methodType();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
