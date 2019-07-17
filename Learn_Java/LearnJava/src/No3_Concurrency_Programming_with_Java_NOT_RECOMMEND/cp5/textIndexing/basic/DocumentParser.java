package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.Normalizer;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Pattern;

public class DocumentParser {
    public Map<String, Integer> parse(String route) {
        Map<String, Integer> ret=new HashMap<String,Integer>();
        Path file= Paths.get(route);
        try {
            //逐行读取
            List<String> lines = Files.readAllLines(file);
            for (String line : lines) {
                parseLine(line,ret);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }


        return ret;

    }

    private static final Pattern PATTERN = Pattern.compile("\\P{IsAlphabetic}+");

    private void parseLine(String line, Map<String, Integer> ret) {
        //使用Pattern抽取单词
        //再用Normalizer类转换大小写
        for(String word: PATTERN.split(line)) {
            if(!word.isEmpty())
                ret.merge(Normalizer.normalize(word, Normalizer.Form.NFKD).toLowerCase(), 1, (a, b) -> a+b);
        }
    }

}
