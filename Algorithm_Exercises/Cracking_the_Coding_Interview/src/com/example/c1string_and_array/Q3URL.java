package com.example.c1string_and_array;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class Q3URL {
    public String URLString(String originalString){
        Map<Character,Integer> map = new HashMap<>();
        for (char c : originalString.toCharArray()) {
            map.compute(c,(k,v)->v==null?1:v+1);
        }
        int numberOfBlank = map.getOrDefault(' ',0);
        char[] oldChar = originalString.toCharArray();
        char[] newChar = new char[originalString.length()+2*numberOfBlank];
        int newCharIndex = newChar.length-1;
        int oldCharIndex = oldChar.length-1;
        for (;oldCharIndex >= 0;oldCharIndex--){
            if(oldChar[oldCharIndex] == ' ')
            {
                newChar[newCharIndex] = '0';
                newChar[newCharIndex-1] = '2';
                newChar[newCharIndex-2] = '%';
                newCharIndex-=3;
            }else{
                newChar[newCharIndex] = oldChar[oldCharIndex];
                newCharIndex--;
            }
        }
        return new String(newChar);
    }

    public static void main(String[] args) {
        var program = new Q3URL();
        System.out.println(program.URLString("Mr John Smith"));
    }
}
