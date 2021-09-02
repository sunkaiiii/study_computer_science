package com.example.c1string_and_array;

import java.util.HashMap;
import java.util.Map;

//Determine if the characters are mutually rearranged
public class Q2IsCharacterRearranged {
    public boolean testRearranged(String s1, String s2)
    {
        Map<Character,Integer> s1Map = new HashMap<>();
        Map<Character,Integer> s2Map = new HashMap<>();
        addValueIntoMap(s1,s1Map);
        addValueIntoMap(s2,s2Map);
        return s1Map.equals(s2Map);
    }

    private void addValueIntoMap(String s,Map<Character,Integer> map)
    {
        for (char c : s.toCharArray()) {
            map.compute(c,(k,v)->v==null?1:v+1);
        }
    }

    public static void main(String[] args) {
        var program = new Q2IsCharacterRearranged();
        String testString1 = "aabbccddeeffgg";
        String testString2 = "ggaabbccddeeff";
        String testString3 = "aabbddeehhccgg";
        System.out.println(program.testRearranged(testString1,testString2));
        System.out.println(program.testRearranged(testString1,testString3));
    }
}
