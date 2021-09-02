package com.example.c1string_and_array;

import java.util.HashMap;
import java.util.HashSet;

//Determine if a character is unique
//if Additional data structures are not allowed?
public class Q1CharacterUnique {
    public boolean isStringCharacterUnique(String st)
    {
        if(st==null || st.length() == 0)
        {
            return false;
        }

        if(st.length() == 1){
            return  true;
        }
        HashSet<Character> characterHashSet = new HashSet<>();
        for (char c : st.toCharArray()) {
            characterHashSet.add(c);
        }
        return characterHashSet.size() == st.length();
    }

    public boolean isStringCharacterUniqueWithoutDataStructure(String st)
    {
        if(st==null || st.length() == 0)
        {
            return false;
        }

        if(st.length() == 1){
            return  true;
        }

        long a = 0x0000000000000000;
        for (char c: st.toCharArray()){
            int currentValue = c-'a';
            if((a & (1L << currentValue)) > 0){
                return false;
            }
            a = (a | (1L<<currentValue));
        }
        return true;
    }

    public static void main(String[] args) {
        var program = new Q1CharacterUnique();
        var testString = "abcdefg";
        var testString2 = "abcdeag";
        System.out.println(program.isStringCharacterUniqueWithoutDataStructure(testString));
        System.out.println(program.isStringCharacterUnique(testString));
        System.out.println(program.isStringCharacterUniqueWithoutDataStructure(testString2));
        System.out.println(program.isStringCharacterUnique(testString2));
    }
}
